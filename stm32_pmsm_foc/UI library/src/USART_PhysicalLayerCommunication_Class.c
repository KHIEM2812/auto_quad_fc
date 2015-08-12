/**
  ******************************************************************************
  * @file    USART_PhysicalLayerCommunication_Class.c
  * @author  IMS Systems Lab and Technical Marketing - MC Team
  * @version 3.0
  * @date    05-Apr-2011 11:34
  * @brief   Private implementation for Physical Layer Communication
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

#include "PhysicalLayerCommunication_Class.h"
#include "PhysicalLayerCommunication_Private.h"
#include "USART_PhysicalLayerCommunication_Class.h"
#include "USART_PhysicalLayerCommunication_Private.h"
#include "UIIRQHandlerPrivate.h"

#ifdef MC_CLASS_DYNAMIC
  #include "stdlib.h" /* Used for dynamic allocation */
#else
  
  #define MAX_USART_COM_NUM 1

  _CUSART_t USART_COMpool[MAX_USART_COM_NUM];
  u8 USART_COM_Allocated = 0;
#endif

/* Private function prototypes -----------------------------------------------*/
void USART_HWInit(pUSARTParams_t pUSARTParams);
void* USART_IRQ_Handler(void* this,unsigned char flags, unsigned short rx_data);
static void USART_StartReceive(CCOM this);
static void USART_StartTransmit(CCOM this);

/**
  * @brief  Creates an object of the class "Physical Layer Communication"
  * @param  pSensorParam: Physical Layer parameters
  * @retval oCOM: new Physical Layer object
  */
CUSART_COM USART_NewObject(pUSARTParams_t pUSARTParams)
{
  _CCOM _oCOM;
  _CUSART _oUSART;
  
  _oCOM = (_CCOM)COM_NewObject();

  #ifdef MC_CLASS_DYNAMIC
    _oUSART = (_CUSART)calloc(1,sizeof(_CUSART_t));
  #else
    if (USART_COM_Allocated  < MAX_USART_COM_NUM)
    {
      _oUSART = &USART_COMpool[USART_COM_Allocated++];
    }
    else
    {
      _oUSART = MC_NULL;
    }
  #endif
  
  _oUSART->pDParams_str = pUSARTParams;
  _oCOM->DerivedClass = (void*)_oUSART;
  _oCOM->Methods_str.pStartReceive = &USART_StartReceive;
  _oCOM->Methods_str.pStartTransmit = &USART_StartTransmit;
  
  _oCOM->Methods_str.pIRQ_Handler = &USART_IRQ_Handler;
  Set_UI_IRQ_Handler(pUSARTParams->IRQno, (_CUIIRQ)_oCOM);
  
  //Init Struct communication
  COM_ResetTX((CCOM)_oCOM);
  COM_ResetRX((CCOM)_oCOM);
  
  USART_HWInit(pUSARTParams);
  
  return ((CUSART_COM)_oCOM);
}

void USART_HWInit(pUSARTParams_t pUSARTParams)
{
  GPIO_InitTypeDef GPIO_InitStructure;
  
  // Enable USART GPIO clock
  RCC_APB2PeriphClockCmd(pUSARTParams->USART_GPIO_CLK, ENABLE);
  
  // Enable USART clock
  if (pUSARTParams->USART_APB == 1)
  {
    RCC_APB1PeriphClockCmd(pUSARTParams->USART_CLK, ENABLE);
  }
  else
  {
    RCC_APB2PeriphClockCmd(pUSARTParams->USART_CLK, ENABLE);
  }  
  
  // USART Init structure
  /* Configure USART */
  USART_Init(pUSARTParams->USART, pUSARTParams->USART_InitStructure);
    
  /* Configures the GPIO ports for USART. */
  if (pUSARTParams->USART_REMAP != 0)
  {
    /* Enable USART AFIO clock if remapped */
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);
    
    /* Enable the USART Pins Software Remapping */
    GPIO_PinRemapConfig(pUSARTParams->USART_REMAP , ENABLE);
  }
  
  /* Configure Rx as input floating */
  GPIO_InitStructure.GPIO_Pin = pUSARTParams->USART_RxPin;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
  GPIO_Init(pUSARTParams->USART_GPIO, &GPIO_InitStructure);
    
  /* Configure Tx as alternate function push-pull */
  GPIO_InitStructure.GPIO_Pin = pUSARTParams->USART_TxPin;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
  GPIO_Init(pUSARTParams->USART_GPIO, &GPIO_InitStructure);
  
  if (pUSARTParams->NVIC_InitStructure->NVIC_IRQChannelCmd == ENABLE)
  {
    /* Enable USART Receive and Transmit interrupts */
    if ((pUSARTParams->USART_InitStructure->USART_Mode & USART_Mode_Rx) == USART_Mode_Rx)
    {
      USART_ITConfig(pUSARTParams->USART, USART_IT_RXNE, ENABLE);
    }
    if ((pUSARTParams->USART_InitStructure->USART_Mode & USART_Mode_Tx) == USART_Mode_Tx)
    {
      //USART_ITConfig(pUSARTParams->USART, USART_IT_TXE, ENABLE);
      USART_ITConfig(pUSARTParams->USART, USART_IT_TXE, DISABLE);
    }
    /* Enable the USARTy Interrupt */
    NVIC_Init(pUSARTParams->NVIC_InitStructure);
  }
  
  /* Enable the USART */
  USART_Cmd(pUSARTParams->USART, ENABLE);
}

/*******************************************************************************
* Function Name  : USART_IRQ_Handler
* Description    : Interrupt function for the serial communication
* Input          : none 
* Return         : none
*******************************************************************************/
void* USART_IRQ_Handler(void* this,unsigned char flags, unsigned short rx_data)
{
  void* pRetVal = MC_NULL;
  if (flags == 0) // Flag 0 = RX
  {
    /* Read one byte from the receive data register */
    if (((_CCOM)this)->Vars_str.PL_Data.RX.Buffer != MC_NULL && 
        ((_CCOM)this)->Vars_str.PL_Data.RX.BufferTransfer < ((_CCOM)this)->Vars_str.PL_Data.RX.BufferCount)
    {
      ((_CCOM)this)->Vars_str.PL_Data.RX.Buffer[((_CCOM)this)->Vars_str.PL_Data.RX.BufferTransfer++] = (uint16_t)(rx_data & (uint16_t)0x01FF);
            
      pRetVal = ReceivingFrame(((_CCOM)this)->Vars_str.parent,((_CCOM)this)->Vars_str.PL_Data.RX.Buffer,((_CCOM)this)->Vars_str.PL_Data.RX.BufferTransfer);
    }
  }
  
  if (flags == 1) // Flag 1 = TX
  {
    /* Write one byte to the transmit data register */
    USART_SendData(((_CUSART)(((_CCOM)this)->DerivedClass))->pDParams_str->USART, ((_CCOM)this)->Vars_str.PL_Data.TX.Buffer[((_CCOM)this)->Vars_str.PL_Data.TX.BufferTransfer++]);                   
    
    if (((_CCOM)this)->Vars_str.PL_Data.TX.BufferCount <= ((_CCOM)this)->Vars_str.PL_Data.TX.BufferTransfer)
    {
      /* Disable the USART Transfer interrupt */
      USART_ITConfig(((_CUSART)(((_CCOM)this)->DerivedClass))->pDParams_str->USART, USART_IT_TXE, DISABLE);
  
      SendingFrame(((_CCOM)this)->Vars_str.parent,((_CCOM)this)->Vars_str.PL_Data.TX.Buffer, ((_CCOM)this)->Vars_str.PL_Data.TX.BufferTransfer);

      //Init communication for next transfer;
      //PL_ResetTX();
    }
  }
  if (flags == 2) // Flag 2 = Send overrun error
  {
    FCP_SendOverrunMeassage(((_CCOM)this)->Vars_str.parent);
  }
  if (flags == 3) // Flag 3 = Send timeout error
  {
    FCP_SendTimeoutMeassage(((_CCOM)this)->Vars_str.parent);
  }
  return pRetVal;
}

/**
  * @brief  Start receive from the channel (IRQ enabling implementation)
  * @param  this: COM object 
  * @retval None
  */
static void USART_StartReceive(CCOM this)
{
  USART_ITConfig(((_CUSART)(((_CCOM)this)->DerivedClass))->pDParams_str->USART, USART_IT_RXNE, ENABLE);
}

/**
  * @brief  Start transmit to the channel (IRQ enabling implementation)
  * @param  this: COM object 
  * @retval None
  */
static void USART_StartTransmit(CCOM this)
{
  USART_ITConfig(((_CUSART)(((_CCOM)this)->DerivedClass))->pDParams_str->USART, USART_IT_TXE, ENABLE);
}
/******************* (C) COPYRIGHT 2011 STMicroelectronics *****END OF FILE****/
