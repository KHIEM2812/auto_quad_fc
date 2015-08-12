/**
  ******************************************************************************
  * @file    USART_PhysicalLayerCommunication_Class.h
  * @author  IMS Systems Lab and Technical Marketing - MC Team
  * @version 3.0
  * @date    05-Apr-2011 11:34
  * @brief   This file contains interface of USART Physical Layer Communication class      
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
#ifndef __USART_PLC_H
#define __USART_PLC_H

#include "MC_type.h"

/** @addtogroup STM32F10x_PMSM_UI_Library
  * @{
  */

/** @addtogroup USART_PhysicalCommunicationLayer
  * @{
  */
  
/** @defgroup USART_COM_class_exported_types USART physical layer communication class exported types
* @{
*/

/* Exported types ------------------------------------------------------------*/
/** 
  * @brief  UserInterface class parameters definition  
  */
typedef const struct
{
  // Hardware settings
  USART_TypeDef* USART;
  unsigned char USART_APB;
  uint32_t USART_REMAP;
  GPIO_TypeDef* USART_GPIO;
  uint32_t USART_CLK;
  uint32_t USART_GPIO_CLK;
  uint16_t USART_RxPin;
  uint16_t USART_TxPin;
  uint8_t USART_IRQn;
  uint8_t IRQno;
  // Usart Structure
  USART_InitTypeDef* USART_InitStructure;
  // NVIC Structure
  NVIC_InitTypeDef* NVIC_InitStructure;
}USARTParams_t, *pUSARTParams_t;

/* Exported constants --------------------------------------------------------*/

/** 
  * @brief  Public UserInterface class definition 
  */
typedef struct CUSART_COM_t *CUSART_COM;

/**
* @}
*/

/** @defgroup USART_COM_class_exported_methods USART physical layer communication class exported methods
  * @{
  */

/*Methods*/
CUSART_COM USART_NewObject(pUSARTParams_t pUSARTParams);

/**
  * @}
  */

/**
  * @}
  */

/**
  * @}
  */

#endif /* __USART_PLC_H */

/******************* (C) COPYRIGHT 2011 STMicroelectronics *****END OF FILE****/
