/**
  ******************************************************************************
  * @file    MotorControlProtocolClass.c
  * @author  IMS Systems Lab and Technical Marketing - MC Team
  * @version 3.0
  * @date    05-Apr-2011 11:34
  * @brief   Private implementation for MotorControlProtocol class
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
#include "UserInterfacePrivate.h"
#include "MotorControlProtocolClass.h"
#include "MotorControlProtocolPrivate.h"

/* Private define ------------------------------------------------------------*/
#define RET_BUFFER 0x02

#define ACK_NOERROR 0xF0
#define ACK_ERROR   0xFF

typedef enum ERROR_CODE_e
{
	ERROR_NONE = 0,
	ERROR_BAD_FRAME_ID,         /* 0x01 */
	ERROR_CODE_SET_READ_ONLY,   /* 0x02 */ 
	ERROR_CODE_GET_WRITE_ONLY,  /* 0x03 */
	ERROR_CODE_NO_TARGET_DRIVE, /* 0x04 */
	ERROR_CODE_WRONG_SET,       /* 0x05 */
	ERROR_CODE_CMD_ID,          /* 0x06 */
	ERROR_CODE_WRONG_CMD,       /* 0x07 */
	ERROR_CODE_OVERRUN,         /* 0x08 */
	ERROR_CODE_TIMEOUT,         /* 0x09 */
	ERROR_CODE_BAD_CRC          /* 0x0A */
} ERROR_CODE;

#ifdef MC_CLASS_DYNAMIC
  #include "stdlib.h" /* Used for dynamic allocation */
#else
  
  #define MAX_MCP_MCUI_NUM 1

  _DCMCP_t MCP_MCUIpool[MAX_MCP_MCUI_NUM];
  u8 MCP_MCUI_Allocated = 0;
#endif

/**
  * @brief  Creates an object of the class MotorControlProtocol
  * @param  pMCPParam: MotorControlProtocol parameters
  * @retval oMCP_MCUI: new MotorControlProtocol object
  */
CMCP_UI MCP_NewObject(pUserInterfaceParams_t pUserInterfaceParams, 
                      pMCPParams_t pMCPParams)
{
  _CUI _oUI;
  _DCMCP _oMCP;
  
  _oUI = (_CUI)UI_NewObject(pUserInterfaceParams);

  #ifdef MC_CLASS_DYNAMIC
    _oMCP = (_DCMCP)calloc(1,sizeof(_DCMCP_t));
  #else
    if (MCP_MCUI_Allocated  < MAX_MCP_MCUI_NUM)
    {
      _oMCP = &MCP_MCUIpool[MCP_MCUI_Allocated++];
    }
    else
    {
      _oMCP = MC_NULL;
    }
  #endif
  
  _oMCP->pDParams_str = pMCPParams;
  _oUI->DerivedClass = (void*)_oMCP;
  
  return ((CMCP_UI)_oUI);
}

void MCP_Init(CMCP_UI this, CFCP oFCP, CUI oDAC, const char* s_fwVer)
{
  _DCMCP _oMCP = (_DCMCP)(((_CUI)this)->DerivedClass);
  _oMCP->DVars_str.oFCP = oFCP;
  _oMCP->DVars_str.oDAC = oDAC;
  _oMCP->DVars_str.s_fwVer = s_fwVer;
  FCP_SetParent(oFCP, (CMCP_UI) this);

  MCP_WaitNextFrame(this);
}

void MCP_OnTimeOut(CMCP_UI this)
{
     MCP_WaitNextFrame(this);
}

void MCP_WaitNextFrame(CMCP_UI this)
{
  _DCMCP oMCP = (_DCMCP)(((_CUI)this)->DerivedClass);
  FCPTimeOut(oMCP->DVars_str.oFCP);
  oMCP->DVars_str.BufferSize = FRAME_MAX_BUFFER_LENGTH;
  Frame_Receive(oMCP->DVars_str.oFCP,MC_NULL, oMCP->DVars_str.BufferFrame, &(oMCP->DVars_str.BufferSize));
}

void MCP_SentFrame(CMCP_UI this, u8 Code, u8 *buffer, u8 Size)
{
    MCP_WaitNextFrame(this);
}

void MCP_ReceivedFrame(CMCP_UI this, u8 Code, u8 *buffer, u8 Size)
{
  _DCMCP oMCP = (_DCMCP)(((_CUI)this)->DerivedClass);
  bool RequireAck = TRUE;
  bool bNoError = FALSE; // Default is error
  u8 bErrorCode;
  
  switch (Code)
  {
  case MC_PROTOCOL_CODE_SET_REG:
    {
      MC_Protocol_REG_t bRegID = (MC_Protocol_REG_t)buffer[0];
      bErrorCode = ERROR_CODE_WRONG_SET;
      
      switch (bRegID)
      {
      case MC_PROTOCOL_REG_TARGET_MOTOR:
      case MC_PROTOCOL_REG_CONTROL_MODE:
        {
          bNoError = UI_SetReg((CUI)this, bRegID, buffer[1]);
        }
        break;
        
      case MC_PROTOCOL_REG_DAC_OUT1:
        {
          UI_DACChannelConfig(oMCP->DVars_str.oDAC, DAC_CH0, (MC_Protocol_REG_t)buffer[1]);
          bNoError = TRUE; /* No check inside class return always true*/
        }
        break;
        
      case MC_PROTOCOL_REG_DAC_OUT2:
        {
          UI_DACChannelConfig(oMCP->DVars_str.oDAC, DAC_CH1, (MC_Protocol_REG_t)buffer[1]);
          bNoError = TRUE; /* No check inside class return always true*/
        }
        break;
        
      case MC_PROTOCOL_REG_SPEED_REF:
        {
          bNoError = UI_SetReg((CUI)this, bRegID, *(s32*)&buffer[1]);
        }
        break;
      case MC_PROTOCOL_REG_TORQUE_REF:
      case MC_PROTOCOL_REG_FLUX_REF:  
        {
          bNoError = UI_SetReg((CUI)this, bRegID, *(s16*)&buffer[1]);
        }
        break;
        
      case MC_PROTOCOL_REG_SPEED_KP:
      case MC_PROTOCOL_REG_SPEED_KI:
      case MC_PROTOCOL_REG_SPEED_KD:
      case MC_PROTOCOL_REG_TORQUE_KP:
      case MC_PROTOCOL_REG_TORQUE_KI:
      case MC_PROTOCOL_REG_TORQUE_KD:
      case MC_PROTOCOL_REG_FLUX_KP:
      case MC_PROTOCOL_REG_FLUX_KI:
      case MC_PROTOCOL_REG_FLUX_KD:
      case MC_PROTOCOL_REG_PLL_KI:
      case MC_PROTOCOL_REG_PLL_KP:
      case MC_PROTOCOL_REG_FLUXWK_KP:
      case MC_PROTOCOL_REG_FLUXWK_KI:
      case MC_PROTOCOL_REG_FLUXWK_BUS:
        {
          bNoError = UI_SetReg((CUI)this, bRegID, *(u16*)&buffer[1]);
        }
        break;
        
      case MC_PROTOCOL_REG_OBSERVER_C1:
      case MC_PROTOCOL_REG_OBSERVER_C2:  
        {
          bNoError = UI_SetReg((CUI)this, bRegID, *(s32*)&buffer[1]);
        }
        break;
        
      default:
        {
          bErrorCode = ERROR_CODE_SET_READ_ONLY;
        }
        break;
      }      
    }
    break;
  case MC_PROTOCOL_CODE_GET_REG:
    {
      MC_Protocol_REG_t bRegID = (MC_Protocol_REG_t)buffer[0];
      
      switch (bRegID)
      {
      case MC_PROTOCOL_REG_TARGET_MOTOR:
      case MC_PROTOCOL_REG_STATUS:
      case MC_PROTOCOL_REG_CONTROL_MODE:
        {
          int32_t value = UI_GetReg((CUI)this, bRegID);
          Frame_Send(oMCP->DVars_str.oFCP,ACK_NOERROR, (u8*)(&value), 1);
          bNoError = TRUE;
        }
        break;
        
      case MC_PROTOCOL_REG_DAC_OUT1:
      case MC_PROTOCOL_REG_DAC_OUT2:
        {
          bErrorCode = ERROR_CODE_GET_WRITE_ONLY; /* Not implemented */
        }
        break;
      
      case MC_PROTOCOL_REG_SPEED_KP:
      case MC_PROTOCOL_REG_SPEED_KI:
      case MC_PROTOCOL_REG_SPEED_KD:
      case MC_PROTOCOL_REG_TORQUE_REF:
      case MC_PROTOCOL_REG_TORQUE_KP:
      case MC_PROTOCOL_REG_TORQUE_KI:
      case MC_PROTOCOL_REG_TORQUE_KD:
      case MC_PROTOCOL_REG_FLUX_REF:
      case MC_PROTOCOL_REG_FLUX_KP:
      case MC_PROTOCOL_REG_FLUX_KI:
      case MC_PROTOCOL_REG_FLUX_KD:
      case MC_PROTOCOL_REG_OBSERVER_C1:
      case MC_PROTOCOL_REG_OBSERVER_C2:
      case MC_PROTOCOL_REG_OBSERVER_CR_C1:
      case MC_PROTOCOL_REG_OBSERVER_CR_C2:
      case MC_PROTOCOL_REG_PLL_KP:
      case MC_PROTOCOL_REG_PLL_KI:
      case MC_PROTOCOL_REG_FLUXWK_KP:
      case MC_PROTOCOL_REG_FLUXWK_KI:
      case MC_PROTOCOL_REG_FLUXWK_BUS:
      case MC_PROTOCOL_REG_BUS_VOLTAGE:
      case MC_PROTOCOL_REG_HEATS_TEMP:
      case MC_PROTOCOL_REG_MOTOR_POWER:
      case MC_PROTOCOL_REG_TORQUE_MEAS:
      case MC_PROTOCOL_REG_FLUX_MEAS:
      case MC_PROTOCOL_REG_FLUXWK_BUS_MEAS:
        {
          int32_t value = UI_GetReg((CUI)this, bRegID);
          Frame_Send(oMCP->DVars_str.oFCP,ACK_NOERROR, (u8*)(&value), 2);
          bNoError = TRUE;
        }
        
      case MC_PROTOCOL_REG_FLAGS:
      case MC_PROTOCOL_REG_SPEED_REF:
      case MC_PROTOCOL_REG_SPEED_MEAS:
        {
          int32_t value = UI_GetReg((CUI)this, bRegID);
          Frame_Send(oMCP->DVars_str.oFCP,ACK_NOERROR, (u8*)(&value), 4);
          bNoError = TRUE;
        }
        break;
        
      default:
        bErrorCode = ERROR_CODE_GET_WRITE_ONLY;
        break;
      }
    }
    break;
  case MC_PROTOCOL_CODE_EXECUTE_CMD:
    {
      u8 bCmdID = buffer[0];
      bErrorCode = ERROR_CODE_WRONG_CMD;
      bNoError = UI_ExecCmd((CUI)this,bCmdID);
    }
    break;
  case MC_PROTOCOL_CODE_LOAD_FROMADDR:
    {
      u32 wMemDumpBase;
      u16 hOffset;
      u8 bSize = buffer[2];
      hOffset = buffer[1];
      hOffset <<= 8;
      hOffset += buffer[0];
      wMemDumpBase = 0x20000000;
      wMemDumpBase += hOffset;
      
      // Send buffer
      Frame_Send(oMCP->DVars_str.oFCP,ACK_NOERROR, (u8*)wMemDumpBase, bSize);
      
      RequireAck = FALSE;
    }
    break;
  case MC_PROTOCOL_CODE_STORE_TOADDR:
    {
      u32 wMemDumpBase;
      u16 hOffset;
      u8 bSize = buffer[2];
      u8 i;
      u8* p;
      
      hOffset = buffer[1];
      hOffset <<= 8;
      hOffset += buffer[0];
      wMemDumpBase = 0x20000000;
      wMemDumpBase += hOffset;
      
      // Read buffer
      p = (u8*)wMemDumpBase;
      for (i = 0; i < bSize; i++)
      {
        p[i] = buffer[i + 3];
      }
      
      bNoError = TRUE;
      
    }
    break;
  case MC_PROTOCOL_CODE_GET_BOARD_INFO:
    {
      unsigned char i;
      u8 outBuff[32];
      /* Version */
      outBuff[0] = 'B';
      outBuff[1] = '1';
      outBuff[2] = '0';
      for (i = 0; i<29; i++)
      {
        outBuff[3+i] = oMCP->DVars_str.s_fwVer[i];
      }
      Frame_Send(oMCP->DVars_str.oFCP,ACK_NOERROR, outBuff, 32);
      bNoError = TRUE;
    }
    break;
  case MC_PROTOCOL_CODE_SET_RAMP:
    bNoError = UI_ExecSpeedRamp((CUI)this, *(s32*)&buffer[0],*(u16*)&buffer[4]);
    break;
  case MC_PROTOCOL_CODE_GET_REVUP_DATA:
    {
      unsigned char outBuff[8];
      uint16_t Durationms;
      int16_t FinalMecSpeed01Hz;
      int16_t FinalTorque;
      UI_GetRevupData((CUI)this, buffer[0], &Durationms, &FinalMecSpeed01Hz, &FinalTorque);
      *(u16*)&outBuff[6] = Durationms;
      *(s32*)&outBuff[0] = ((int32_t)FinalMecSpeed01Hz * 6);
      *(s16*)&outBuff[4] = FinalTorque;
      Frame_Send(oMCP->DVars_str.oFCP,ACK_NOERROR, outBuff, 8);
    }
    break;
  case MC_PROTOCOL_CODE_SET_REVUP_DATA:
    {
      int32_t FinalMecSpeed01Hz = *(s32*)&buffer[1] / 6;
      bNoError = UI_SetRevupData((CUI)this, buffer[0], *(u16*)&buffer[7], FinalMecSpeed01Hz, *(s16*)&buffer[5]); 
    }
    break;
    
  case MC_PROTOCOL_CODE_SET_CURRENT_REF:
    UI_SetCurrentReferences((CUI)this, *(s16*)&buffer[0], *(s16*)&buffer[2]);
    bNoError = TRUE;
    break;
    
  default:
    {
      bErrorCode = ERROR_BAD_FRAME_ID;
    }
    break;
  }
  
  if (RequireAck)
  {
    if (bNoError)
    {
      Frame_Send(oMCP->DVars_str.oFCP,ACK_NOERROR, MC_NULL, 0);
    }
    else
    {
      Frame_Send(oMCP->DVars_str.oFCP,ACK_ERROR, &bErrorCode, 1);
    }
  }
}

void MCP_SendOverrunMeassage(CMCP_UI this)
{
  _DCMCP oMCP = (_DCMCP)(((_CUI)this)->DerivedClass);
  u8 bErrorCode = ERROR_CODE_OVERRUN;
  Frame_Send(oMCP->DVars_str.oFCP,ACK_ERROR, &bErrorCode, 1);
}

void MCP_SendTimeoutMeassage(CMCP_UI this)
{
  _DCMCP oMCP = (_DCMCP)(((_CUI)this)->DerivedClass);
  u8 bErrorCode = ERROR_CODE_TIMEOUT;
  Frame_Send(oMCP->DVars_str.oFCP,ACK_ERROR, &bErrorCode, 1);
}

void MCP_SendBadCRCMessage(CMCP_UI this)
{
  _DCMCP oMCP = (_DCMCP)(((_CUI)this)->DerivedClass);
  u8 bErrorCode = ERROR_CODE_BAD_CRC;
  Frame_Send(oMCP->DVars_str.oFCP,ACK_ERROR, &bErrorCode, 1);
}

/******************* (C) COPYRIGHT 2011 STMicroelectronics *****END OF FILE****/
