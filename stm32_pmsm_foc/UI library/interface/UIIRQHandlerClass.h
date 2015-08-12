/**
  ******************************************************************************
  * @file    UIIRQHandlerClass.h
  * @author  IMS Systems Lab and Technical Marketing - MC Team
  * @version 3.0
  * @date    05-Apr-2011 11:34
  * @brief   This file contains interface of UI IRQ handler class      
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
#ifndef __UI_IRQHANDLERCLASS_H
#define __UI_IRQHANDLERCLASS_H

/** @addtogroup STM32F10x_PMSM_UI_Library
  * @{
  */

/** @addtogroup UserInterface_IRQHandler
  * @{
  */
  
/** @defgroup UserInterface_class_exported_types UserInterface class exported types
* @{
*/

/* MC IRQ Addresses */
#define UI_IRQ_USART            0u  /*!< Reserved for UIClass serial communication.*/ 

/**
* @}
*/

/** @defgroup UserInterface_class_exported_methods UserInterface class exported methods
  * @{
  */

/*Methods*/
void* Exec_UI_IRQ_Handler(unsigned char bIRQAddr, unsigned char flag, unsigned short rx_data);

/**
  * @}
  */

/**
  * @}
  */

/**
  * @}
  */

#endif /* __UI_IRQHANDLERCLASS_H */

/******************* (C) COPYRIGHT 2011 STMicroelectronics *****END OF FILE****/
