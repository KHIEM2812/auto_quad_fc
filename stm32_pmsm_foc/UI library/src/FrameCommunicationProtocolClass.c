/**
  ******************************************************************************
  * @file    FrameCommunicationProtocolClass.c
  * @author  IMS Systems Lab and Technical Marketing - MC Team
  * @version 3.0
  * @date    05-Apr-2011 11:34
  * @brief   Private implementation for FrameCommunicationProtocol class
  ******************************************************************************
  * @copy
  *
  * THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
  * WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE
  * TIME. AS A RESULT, STMICROELECTRONICS SHALL NOT BE HELD LIABLE FOR ANY
  * DIRECT, INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING
  * FROM THE CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE
  * CODING INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
  *
  * <h2><center>&copy; COPYRIGHT 2011 STMicroelectronics</center></h2>
  */

/* Includes ------------------------------------------------------------------*/
#include "UserInterfaceClass.h"
#include "MotorControlProtocolClass.h"

#include "FrameCommunicationProtocolClass.h"
#include "FrameCommunicationProtocolPrivate.h"

/* Private function prototypes -----------------------------------------------*/
u8 CalcCRC(PFrameData_t pFrame);
u8 IsFrameValid(PFrameData_t pFrame);
void FrameTimeOutConfiguration(_CFCP _oFCP);

#ifdef MC_CLASS_DYNAMIC
  #include "stdlib.h" /* Used for dynamic allocation */
#else
  
  #define MAX_FCP_NUM 1

  _CFCP_t FCPpool[MAX_FCP_NUM];
  u8 FCP_Allocated = 0;
#endif

/**
  * @brief  Creates an object of the class FrameCommunicationProtocol
  * @param  pSensorParam: Physical Layer parameters
  * @retval oFCP: new Physical Layer object
  */
CFCP FCP_NewObject(pFCPParams_t pFCPParam)
{
  _CFCP _oFCP;
  
  #ifdef MC_CLASS_DYNAMIC
    _oFCP = (_CFCP)calloc(1,sizeof(_CFCP_t));
  #else
    if (FCP_Allocated  < MAX_FCP_NUM)
    {
      _oFCP = &FCPpool[FCP_Allocated++];
    }
    else
    {
      _oFCP = MC_NULL;
    }
  #endif

  FrameTimeOutConfiguration(_oFCP);
  _oFCP->Vars_str.frameTransmitionRX.OnTimeOutByte = pFCPParam->RXTimeOutEvent;
  _oFCP->Vars_str.frameTransmitionTX.OnTimeOutByte = pFCPParam->TXTimeOutEvent;
    
  return ((CFCP)_oFCP);
}

void FCP_Init(CFCP this, CCOM oCOM)
{
  _CFCP _oFCP = ((_CFCP)this);
  _oFCP->Vars_str.oCOM = oCOM;
  COM_SetParent(oCOM, (CFCP)_oFCP);
  
  Frame_ResetTX((CFCP)_oFCP);
  Frame_ResetRX((CFCP)_oFCP);
}

void FCP_SetParent(CFCP this, CMCP_UI oMCP)
{
  ((_CFCP)this)->Vars_str.parent = oMCP;
}

void Frame_ResetTX(CFCP this)
{
  ((_CFCP)this)->Vars_str.frameTransmitionTX.State = FCP_IDLE;
  COM_ResetTX((CCOM)(((_CFCP)this)->Vars_str.oCOM));
}

void Frame_ResetRX(CFCP this)
{
  COM_ResetRX((CCOM)(((_CFCP)this)->Vars_str.oCOM));
  ((_CFCP)this)->Vars_str.frameTransmitionRX.State = FCP_IDLE;
}

u8 Frame_Receive(CFCP this, u8 *code, u8 *buffer, u8 *size)
{
  u8 nRet;
  u8 i;

  ((_CFCP)this)->Vars_str.frameTransmitionRX.FrameTransferError = FRAME_ERROR_NONE;

  nRet = FRAME_ERROR_TRANSFER_ONGOING;
  if (((_CFCP)this)->Vars_str.frameTransmitionRX.State == FCP_IDLE)
  {
    ((_CFCP)this)->Vars_str.frameTransmitionRX.Frame.Code = 0x00;
    ((_CFCP)this)->Vars_str.frameTransmitionRX.Frame.Size = 0x00;

    for (i=0; i < FRAME_MAX_BUFFER_LENGTH; i++)
      ((_CFCP)this)->Vars_str.frameTransmitionRX.Frame.Buffer[i] = 0x00;

    ((_CFCP)this)->Vars_str.frameTransmitionRX.State = TRANSFERING_HEADER;

    COM_ReceiveBuffer((CCOM)(((_CFCP)this)->Vars_str.oCOM),(u8*)&(((_CFCP)this)->Vars_str.frameTransmitionRX).Frame, FRAME_MAX_SIZE); // ReceivingFrame
    
    nRet = FRAME_ERROR_WAITING_TRANSFER;    
  }
  return nRet;
}

u8 Frame_Send(CFCP this, u8 code, u8 *buffer, u8 size)
{
  u8 nRet, idx;

  nRet = FRAME_ERROR_TRANSFER_ONGOING;
  if (((_CFCP)this)->Vars_str.frameTransmitionTX.State == FCP_IDLE)
  {
    ((_CFCP)this)->Vars_str.frameTransmitionTX.Frame.Code = code;
    ((_CFCP)this)->Vars_str.frameTransmitionTX.Frame.Size = size;
    
    for (idx=0; idx < size; idx++)
      ((_CFCP)this)->Vars_str.frameTransmitionTX.Frame.Buffer[idx] = buffer[idx];
    
    ((_CFCP)this)->Vars_str.frameTransmitionTX.Frame.Buffer[size] = CalcCRC((PFrameData_t)&(((_CFCP)this)->Vars_str.frameTransmitionTX.Frame));

    ((_CFCP)this)->Vars_str.frameTransmitionTX.State = TRANSFERING_BUFFER;

    COM_SendBuffer((CCOM)(((_CFCP)this)->Vars_str.oCOM),(u8 *)&(((_CFCP)this)->Vars_str.frameTransmitionTX.Frame), ((_CFCP)this)->Vars_str.frameTransmitionTX.Frame.Size + FRAME_HEADER_SIZE + FRAME_CRC_SIZE); // SendingFrame
    
    nRet = FRAME_ERROR_WAITING_TRANSFER;
  }
  
  return nRet;
}

/*******************************************************************************
* Function Name  : FrameTimeOutConfiguration
* Description    : This function Configuration for timer7 to manage the timeout
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void FrameTimeOutConfiguration(_CFCP _oFCP)
{  
  _oFCP->Vars_str.frameTransmitionRX.FrameTransferError = FRAME_ERROR_NONE;
  _oFCP->Vars_str.frameTransmitionTX.FrameTransferError = FRAME_ERROR_NONE;
}

// Private functions

u8 CalcCRC(PFrameData_t pFrame)
{
  u8 nCRC = 0;
  u16 nSum = 0;
  u8 idx;

  if(MC_NULL != pFrame)
  { 
    nSum += pFrame->Code;
    nSum += pFrame->Size;
    for(idx = 0; idx < (pFrame->Size); idx++)
    {
      nSum += pFrame->Buffer[idx];
    }
    nCRC = (u8)(nSum & 0xFF) ; // Low Byte of nSum
    nCRC += (u8) (nSum >> 8) ; // High Byte of nSum
  }

  return nCRC ;
}

const uint16_t Usart_Timeout_none = 0;
const uint16_t Usart_Timeout_start = 1;
const uint16_t Usart_Timeout_stop = 2;

void* ReceivingFrame(CFCP this, u8 *buffer, u16 size)
{
  void* pRetVal = (void *)(&Usart_Timeout_none);
  if (size == 1)  //First Byte received
  {
    pRetVal = (void *)(&Usart_Timeout_start);
  }
  switch(((_CFCP)this)->Vars_str.frameTransmitionRX.State)
  {
    case TRANSFERING_HEADER:
    {
      if (size == FRAME_HEADER_SIZE)
      {
        //Receive DATA BUFFER
        if (((_CFCP)this)->Vars_str.frameTransmitionRX.Frame.Size > 0 )
        {
          ((_CFCP)this)->Vars_str.frameTransmitionRX.State = TRANSFERING_BUFFER;
        }
        else
        {
          ((_CFCP)this)->Vars_str.frameTransmitionRX.State = TRANSFERING_CRC;
        }
      }
      break;
    }
    case TRANSFERING_BUFFER:
    {
      //Receive CRC
      if ((((_CFCP)this)->Vars_str.frameTransmitionRX.Frame.Size + FRAME_HEADER_SIZE) == size)
        ((_CFCP)this)->Vars_str.frameTransmitionRX.State = TRANSFERING_CRC;

      break;
    }
    case TRANSFERING_CRC:
    {
        if (size == (((_CFCP)this)->Vars_str.frameTransmitionRX.Frame.Size + FRAME_HEADER_SIZE + FRAME_CRC_SIZE))
        {
          pRetVal = (void *)(&Usart_Timeout_stop);
          ((_CFCP)this)->Vars_str.frameTransmitionRX.State = FCP_IDLE;
          USART_ITConfig(USART1, USART_IT_RXNE, DISABLE);
          
         
          ((_CFCP)this)->Vars_str.frameTransmitionRX.FrameTransferError = FRAME_ERROR_INVALID_FRAME;
          if (IsFrameValid((PFrameData_t)&(((_CFCP)this)->Vars_str.frameTransmitionRX.Frame)))
          {
            ((_CFCP)this)->Vars_str.frameTransmitionRX.FrameTransferError = FRAME_ERROR_NONE;

            MCP_ReceivedFrame(((_CFCP)this)->Vars_str.parent,(u8)((_CFCP)this)->Vars_str.frameTransmitionRX.Frame.Code, (u8 *)((_CFCP)this)->Vars_str.frameTransmitionRX.Frame.Buffer, (u8)((_CFCP)this)->Vars_str.frameTransmitionRX.Frame.Size);
          }
          else
          {
            MCP_SendBadCRCMessage(((_CFCP)this)->Vars_str.parent);
          }
        }
        break;
    }
  }
  return pRetVal;
}

void SendingFrame(CFCP this, u8 *buffer, u16 size)
{
    if (size == ((_CFCP)this)->Vars_str.frameTransmitionTX.Frame.Size + FRAME_HEADER_SIZE + FRAME_CRC_SIZE)
      ((_CFCP)this)->Vars_str.frameTransmitionTX.State = FCP_IDLE;

    MCP_SentFrame(((_CFCP)this)->Vars_str.parent, ((_CFCP)this)->Vars_str.frameTransmitionTX.Frame.Code, 
                                         (u8 *)((_CFCP)this)->Vars_str.frameTransmitionTX.Frame.Buffer, 
                                         ((_CFCP)this)->Vars_str.frameTransmitionTX.Frame.Size);
        
    //    Frame_ResetTX();
}

u8 IsFrameValid(PFrameData_t pFrame)
{
  if (pFrame)
    return CalcCRC(pFrame) == pFrame->Buffer[pFrame->Size];
  else
    return 0;
}

void FCPTimeOut(CFCP this)
{
  _CFCP _oFCP = ((_CFCP)this);
  _oFCP->Vars_str.frameTransmitionRX.FrameTransferError = FRAME_ERROR_TIME_OUT;
  Frame_ResetRX((CFCP)_oFCP);
}

void FCP_SendOverrunMeassage(CFCP this)
{
  MCP_SendOverrunMeassage(((_CFCP)this)->Vars_str.parent);
}

void FCP_SendTimeoutMeassage(CFCP this)
{
  MCP_SendTimeoutMeassage(((_CFCP)this)->Vars_str.parent);
}

/******************* (C) COPYRIGHT 2011 STMicroelectronics *****END OF FILE****/
