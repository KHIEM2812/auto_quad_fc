/**
  ******************************************************************************
  * @file    USART_F0XX_PhysicalLayerCommunication_Class.c
  * @author  STMicroelectronics - System Lab - MC Team
  * @version 4.0.0
  * @date    28-May-2014 10:45
  * @brief   Private implementation for Physical Layer Communication for F0XX
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; COPYRIGHT 2014 STMicroelectronics</center></h2>
  *
  * Licensed under MCD-ST Liberty SW License Agreement V2, (the "License");
  * You may not use this file except in compliance with the License.
  * You may obtain a copy of the License at:
  *
  *        http://www.st.com/software_license_agreement_liberty_v2
  *
  * Unless required by applicable law or agreed to in writing, software 
  * distributed under the License is distributed on an "AS IS" BASIS, 
  * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
  * See the License for the specific language governing permissions and
  * limitations under the License.
  *
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#define PROJECT_CHK
#include "CrossCheck.h" 
#undef PROJECT_CHK

#include "MC_Type.h"
#include "Parameters conversion.h"

#include "PhysicalLayerCommunication_Class.h"
#include "PhysicalLayerCommunication_Private.h"
#include "USART_PhysicalLayerCommunication_Class.h"
#include "USART_PhysicalLayerCommunication_Private.h"
#include "UIIRQHandlerPrivate.h"

#if (defined(STM32F051x))
#define DMACH DMA1_Channel3
#define DMAREMAP
#elif ((defined(STM32F050x)) || (defined(STM32F030x)))
#define DMACH DMA1_Channel5
#define DMAREMAP SYSCFG_DMAChannelRemapConfig(SYSCFG_DMARemap_USART1Rx,(FunctionalState)(ENABLE))
#else
#error "Invalid configuration: MCU definition in Control stage parameters.h"
#endif

#ifdef MC_CLASS_DYNAMIC
  #include "stdlib.h" /* Used for dynamic allocation */
#else
  
  #define MAX_USART_COM_NUM 1

  _CUSART_t USART_COMpool[MAX_USART_COM_NUM];
  uint8_t USART_COM_Allocated = 0;
#endif

/* Private function prototypes -----------------------------------------------*/
void USART_HWInit(pUSARTParams_t pUSARTParams);
void* USART_IRQ_Handler(void* this,unsigned char flags, unsigned short rx_data);
static void USART_StartReceive(CCOM this);
static void USART_StartTransmit(CCOM this);
static uint16_t USART_GPIOPin2Source(uint16_t GPIO_Pin);
static uint8_t USART_AF(GPIO_TypeDef* GPIOx);

#define DMA_BUFF 10u
#define DMA_TIMEOUT 5300
uint8_t PL_receive_buffer[DMA_BUFF];
#define RDR_OFFSET 0x24u
#define USART1_RDR_Address USART1_BASE + RDR_OFFSET

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
  Set_UI_IRQ_Handler(pUSARTParams->bUIIRQn, (_CUIIRQ)_oCOM);
  
  //Init Struct communication
  COM_ResetTX((CCOM)_oCOM);
  COM_ResetRX((CCOM)_oCOM);
  
  USART_HWInit(pUSARTParams);
  
  return ((CUSART_COM)_oCOM);
}

void USART_HWInit(pUSARTParams_t pUSARTParams)
{
  GPIO_InitTypeDef GPIO_InitStructure;
  DMA_InitTypeDef DMA_InitStructure;
  
  /* Enable USART clock: UASRT1 -> APB2, USART2-5 -> APB1 */
  if (pUSARTParams->wUSARTClockSource == RCC_APB2Periph_USART1)
  {
    RCC_APB2PeriphClockCmd(pUSARTParams->wUSARTClockSource, (FunctionalState)(ENABLE));
  }
  else
  {
    RCC_APB1PeriphClockCmd(pUSARTParams->wUSARTClockSource, (FunctionalState)(ENABLE));
  }  
  
  /* USART Init structure */
  /* Configure USART */
  USART_Init(pUSARTParams->USARTx, pUSARTParams->USART_InitStructure);
  
  GPIO_PinAFConfig(pUSARTParams->hRxPort, USART_GPIOPin2Source(pUSARTParams->hRxPin), USART_AF(pUSARTParams->hRxPort));
  GPIO_PinAFConfig(pUSARTParams->hTxPort, USART_GPIOPin2Source(pUSARTParams->hTxPin), USART_AF(pUSARTParams->hRxPort));
  
  /* Configure Rx, Tx pins */
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  
  GPIO_InitStructure.GPIO_Pin = pUSARTParams->hRxPin;
  GPIO_Init(pUSARTParams->hRxPort, &GPIO_InitStructure);
  
  GPIO_InitStructure.GPIO_Pin = pUSARTParams->hTxPin;
  GPIO_Init(pUSARTParams->hTxPort, &GPIO_InitStructure);
  
  if (pUSARTParams->NVIC_InitStructure->NVIC_IRQChannelCmd == ENABLE)
  {
    /* Enable USART Receive and Transmit interrupts */
    if ((pUSARTParams->USART_InitStructure->USART_Mode & USART_Mode_Rx) == USART_Mode_Rx)
    {
      USART_ITConfig(pUSARTParams->USARTx, USART_IT_RXNE, (FunctionalState)(ENABLE));
    }
    if ((pUSARTParams->USART_InitStructure->USART_Mode & USART_Mode_Tx) == USART_Mode_Tx)
    {
      USART_ITConfig(pUSARTParams->USARTx, USART_IT_TXE, (FunctionalState)(DISABLE));
    }
    /* Enable the USARTy Interrupt */
    NVIC_Init(pUSARTParams->NVIC_InitStructure);
  }
  
  /* Enable the USART */
  USART_Cmd(pUSARTParams->USARTx, (FunctionalState)(ENABLE));
  
  /* DMA Event related to USART RX */
  /* Note: Only USART1 can be used with DMA */
  /* Enable DMA clock */
  RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1, (FunctionalState)(ENABLE));
  /* DMA channel configuration ----------------------------------------------*/
  DMA_DeInit(DMACH);
  DMA_InitStructure.DMA_PeripheralBaseAddr = (uint32_t)USART1_RDR_Address; // Test
  DMA_InitStructure.DMA_MemoryBaseAddr = (uint32_t)(PL_receive_buffer);
  DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralSRC;
  DMA_InitStructure.DMA_BufferSize = DMA_BUFF;
  DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
  DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;
  DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte;
  DMA_InitStructure.DMA_MemoryDataSize = DMA_PeripheralDataSize_Byte;
  DMA_InitStructure.DMA_Mode = DMA_Mode_Normal;
  DMA_InitStructure.DMA_Priority = DMA_Priority_Low;
  DMA_InitStructure.DMA_M2M = DMA_M2M_Disable;
  DMA_Init(DMACH, &DMA_InitStructure);
  /* Enable DMA Channel */
  DMA_Cmd(DMACH, (FunctionalState)(ENABLE));
  DMAREMAP;
  USART_DMACmd(pUSARTParams->USARTx,USART_DMAReq_Rx,(FunctionalState)(ENABLE));
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
    uint8_t i;
    uint16_t hDMAcnt,hDMATimeoutCnt = 0;
    bool DMAComplete = FALSE;
		
    /* If no DMA occurs return */
    if (DMA_GetCurrDataCounter(DMACH) == DMA_BUFF)
    {
      return pRetVal;
    }
    /* Wait untill DMA complete or timeout */
    while (!DMAComplete)
    {
      hDMAcnt = DMA_GetCurrDataCounter(DMACH);
      if ((hDMAcnt < (DMA_BUFF - 1)) && (hDMAcnt == (DMA_BUFF - 3 - PL_receive_buffer[1])))
      {
        DMAComplete = TRUE;
      }
      else
      {
        if (hDMATimeoutCnt < DMA_TIMEOUT)
        {
          hDMATimeoutCnt++;
        }
        else
        {
          FCP_SendTimeoutMeassage(((_CCOM)this)->Vars_str.parent);
          /* Reset DMA */
          DMA_Cmd(DMACH,(FunctionalState)(DISABLE));
          DMA_SetCurrDataCounter(DMACH,DMA_BUFF);
          DMA_Cmd(DMACH,(FunctionalState)(ENABLE));
          return pRetVal;
        }
      }
    }
    
    for (i = 0; i < DMA_BUFF - hDMAcnt; i++)
    {
      /* Read one byte from the receive data register */
      if (((_CCOM)this)->Vars_str.PL_Data.RX.Buffer != MC_NULL && 
          ((_CCOM)this)->Vars_str.PL_Data.RX.BufferTransfer < ((_CCOM)this)->Vars_str.PL_Data.RX.BufferCount)
      {
        ((_CCOM)this)->Vars_str.PL_Data.RX.Buffer[((_CCOM)this)->Vars_str.PL_Data.RX.BufferTransfer++] = PL_receive_buffer[i];
        
        pRetVal = ReceivingFrame(((_CCOM)this)->Vars_str.parent,((_CCOM)this)->Vars_str.PL_Data.RX.Buffer,((_CCOM)this)->Vars_str.PL_Data.RX.BufferTransfer);
      }
    }
    /* Reset DMA */
    DMA_Cmd(DMACH,(FunctionalState)(DISABLE));
    DMA_SetCurrDataCounter(DMACH,DMA_BUFF);
    DMA_Cmd(DMACH,(FunctionalState)(ENABLE));
  }
  
  if (flags == 1) // Flag 1 = TX
  {
    /* Write one byte to the transmit data register */
    USART_SendData(((_CUSART)(((_CCOM)this)->DerivedClass))->pDParams_str->USARTx, ((_CCOM)this)->Vars_str.PL_Data.TX.Buffer[((_CCOM)this)->Vars_str.PL_Data.TX.BufferTransfer++]);                   
    
    if (((_CCOM)this)->Vars_str.PL_Data.TX.BufferCount <= ((_CCOM)this)->Vars_str.PL_Data.TX.BufferTransfer)
    {
      /* Disable the USART Transfer interrupt */
      USART_ITConfig(((_CUSART)(((_CCOM)this)->DerivedClass))->pDParams_str->USARTx, USART_IT_TXE, (FunctionalState)(DISABLE));
  
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
  USART_ITConfig(((_CUSART)(((_CCOM)this)->DerivedClass))->pDParams_str->USARTx, USART_IT_RXNE, (FunctionalState)(ENABLE));
}

/**
  * @brief  Start transmit to the channel (IRQ enabling implementation)
  * @param  this: COM object 
  * @retval None
  */
static void USART_StartTransmit(CCOM this)
{
  USART_ITConfig(((_CUSART)(((_CCOM)this)->DerivedClass))->pDParams_str->USARTx, USART_IT_TXE, (FunctionalState)(ENABLE));
}

/**
  * @brief  It is an internal function used to compute the GPIO Source 
  *         value starting from GPIO pin value. The GPIO Source value 
  *         is used for AF remapping.
  * @param  GPIO_Pin Pin value to be converted.
  * @retval uint16_t The GPIO pin source value converted.
  */
static uint16_t USART_GPIOPin2Source(uint16_t GPIO_Pin)
{
  uint16_t hRetVal;
  switch (GPIO_Pin)
  {
  case GPIO_Pin_0:
    {
      hRetVal = GPIO_PinSource0;
      break;
    }
  case GPIO_Pin_1:
    {
      hRetVal = GPIO_PinSource1;
      break;
    }
  case GPIO_Pin_2:
    {
      hRetVal = GPIO_PinSource2;
      break;
    }
  case GPIO_Pin_3:
    {
      hRetVal = GPIO_PinSource3;
      break;
    }
  case GPIO_Pin_4:
    {
      hRetVal = GPIO_PinSource4;
      break;
    }
  case GPIO_Pin_5:
    {
      hRetVal = GPIO_PinSource5;
      break;
    }
  case GPIO_Pin_6:
    {
      hRetVal = GPIO_PinSource6;
      break;
    }
  case GPIO_Pin_7:
    {
      hRetVal = GPIO_PinSource7;
      break;
    }
  case GPIO_Pin_8:
    {
      hRetVal = GPIO_PinSource8;
      break;
    }
  case GPIO_Pin_9:
    {
      hRetVal = GPIO_PinSource9;
      break;
    }
  case GPIO_Pin_10:
    {
      hRetVal = GPIO_PinSource10;
      break;
    }
  case GPIO_Pin_11:
    {
      hRetVal = GPIO_PinSource11;
      break;
    }
  case GPIO_Pin_12:
    {
      hRetVal = GPIO_PinSource12;
      break;
    }
  case GPIO_Pin_13:
    {
      hRetVal = GPIO_PinSource13;
      break;
    }
  case GPIO_Pin_14:
    {
      hRetVal = GPIO_PinSource14;
      break;
    }
  case GPIO_Pin_15:
    {
      hRetVal = GPIO_PinSource15;
      break;
    }
  default:
    {
      hRetVal = 0u;
      break;
    }
  }
  return hRetVal;
}

static uint8_t USART_AF(GPIO_TypeDef* GPIOx)
{
  uint8_t hRetVal = 0u;
  if (GPIOx == GPIOA)
  {
    hRetVal = GPIO_AF_1;
  }
  else
  {
    hRetVal = GPIO_AF_0;
  }
  return hRetVal;
}

/******************* (C) COPYRIGHT 2014 STMicroelectronics *****END OF FILE****/
