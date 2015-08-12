/**
  ******************************************************************************
  * @file    USARTParams.h
  * @author  IMS Systems Lab and Technical Marketing - MC Team
  * @version 3.0
  * @date    05-Apr-2011 11:34
  * @brief   This file contains USART constant parameters definition
  ******************************************************************************
  * <br>
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

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __USART_PARAMS_H
#define __USART_PARAMS_H
#include "Parameters conversion.h"

/*************************  USART REMAPPING  *********************/
#define USART1_NO_REMAP  0
#define USART1_REMAP     1

/*************************  USART REMAPPING  *********************/

#include "USART_PhysicalLayerCommunication_Class.h"
#include "UIIRQHandlerClass.h"

#define UI_IRQ_USART            0u  /*!< Reserved for UIClass serial communication.*/ 

#define USART_PRE_EMPTION_PRIORITY 2
#define USART_SUB_PRIORITY 1

#if (USART1_REMAPPING == USART1_NO_REMAP)
#define USART1_GPIO_REMAP   0
#define USART1_GPIO_PORT    GPIOA
#define USART1_TX_GPIO_PIN  GPIO_Pin_9
#define USART1_RX_GPIO_PIN  GPIO_Pin_10
#else
#define USART1_GPIO_REMAP   GPIO_Remap_USART1
#define USART1_GPIO_PORT    GPIOB
#define USART1_TX_GPIO_PIN  GPIO_Pin_6
#define USART1_RX_GPIO_PIN  GPIO_Pin_7
#endif

const NVIC_InitTypeDef NVICInitHW_str =
{
  USART1_IRQn,  // NVIC_IRQChannel
  USART_PRE_EMPTION_PRIORITY,            // NVIC_IRQChannelPreemptionPriority
  USART_SUB_PRIORITY,            // NVIC_IRQChannelSubPriority
  (FunctionalState)(ENABLE)        // NVIC_IRQChannelCmd
};

const USART_InitTypeDef USARTInitHW_str = 
{
  115200,                         //USART_BaudRate
  USART_WordLength_8b,            //USART_WordLength
  USART_StopBits_1,               //USART_StopBits
  USART_Parity_No,                //USART_Parity
  USART_Mode_Rx | USART_Mode_Tx,  //USART_Mode
  USART_HardwareFlowControl_None  //USART_HardwareFlowControl
};

//Eval board settings USART1
USARTParams_t USARTParams_str = 
{
  USART1,                 // USART
  2,                      // USART_APB
  USART1_GPIO_REMAP,      // USART_REMAP 0 = None or GPIO_Remap_USART1 ...
  USART1_GPIO_PORT,       // USART_GPIO
  RCC_APB2Periph_USART1,  // USART_CLK
  RCC_APB2Periph_GPIOA,   // USART_GPIO_CLK
  USART1_RX_GPIO_PIN,     // USART_RxPin
  USART1_TX_GPIO_PIN,     // USART_TxPin
  USART1_IRQn,            // USART_IRQn
  UI_IRQ_USART,           // IRQ Number
  (USART_InitTypeDef*)(&USARTInitHW_str),       // USART_InitStructure
  (NVIC_InitTypeDef*)(&NVICInitHW_str)         // NVIC_InitStructure
};

FCPParams_t FrameParams_str =
{
  5000,             // TimeOutRXByte
  1000,             // TimeOutTXByte
  MC_NULL,             // RXTimeOutEvent
  MC_NULL              // TXTimeOutEvent
};

MCPParams_t MCPParams = 
{
  &FrameParams_str // pFCPParams
};

#endif /* __USART_PARAMS_H */

/******************* (C) COPYRIGHT 2011 STMicroelectronics *****END OF FILE****/
