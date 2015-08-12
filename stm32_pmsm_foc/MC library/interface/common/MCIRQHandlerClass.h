/**
  ******************************************************************************
  * @file    MCIRQHandlerClass.h
  * @author  IMS Systems Lab and Technical Marketing - MC Team
  * @version 3.0
  * @date    05-Apr-2011 11:34
  * @brief   This file contains interface of FOCDrive class      
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
#ifndef __MC_IRQHANDLERCLASS_H
#define __MC_IRQHANDLERCLASS_H

/** @addtogroup STM32F10x_PMSM_MC_Library
  * @{
  */
  
/** @addtogroup MCIRQ_Handler
  * @{
  */

/** @defgroup MC_IRQHandler_exported_definitions MCIRQ_Handler module exported definitions
  * @{
  */

/** 
  * @brief  MC IRQ interrupts addresses inside MC vector table 
  */
#define MC_IRQ_PWMNCURRFDBK_1   0u  /*!< Reserved for PWMnCurrFdbk first instance.*/
#define MC_IRQ_PWMNCURRFDBK_2   1u  /*!< Reserved for PWMnCurrFdbk second instance.*/
#define MC_IRQ_SPEEDNPOSFDBK_1  2u  /*!< Reserved for SpeednPosFdbk first instance.*/
#define MC_IRQ_SPEEDNPOSFDBK_2  3u  /*!< Reserved for SpeednPosFdbk second instance.*/

/**
* @}
*/

/** @defgroup MC_IRQHandler_exported_functions MCIRQ Handler module exported functions
  * @{
  */

/**
  * @brief Start the execution of the MC_IRQ at bIRQAddr position inside MC 
  *        vector table
  * @param bIRQAddr MC IRQ position inside MC vector table
  * @param flag parameter passed to the MC interrupt, for instance to identify 
  *             the event request the MC ISR execution
  * @retval pvoid pointer to Drive object related to the interrupt
  */
void* Exec_IRQ_Handler(unsigned char bIRQAddr, unsigned char flag);

/**
* @}
*/

/**
* @}
*/

/**
* @}
*/
#endif /* __MC_IRQHANDLERCLASS_H */

/******************* (C) COPYRIGHT 2011 STMicroelectronics *****END OF FILE****/
