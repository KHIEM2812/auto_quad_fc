/**
  ******************************************************************************
  * @file    MCTasks.h
  * @author  IMS Systems Lab and Technical Marketing - MC Team
  * @version 3.0
  * @date    05-Apr-2011 11:34
  * @brief   This file implementes tasks definition
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
#ifndef __MCTASKS_H
#define __MCTASKS_H

/* Includes ------------------------------------------------------------------*/

/** @addtogroup STM32F10x_PMSM_MC_Interface
  * @{
  */

/** @addtogroup MCTasks
  * @{
  */
  
/** @defgroup MCboot_exported_methods MCTasks exported methods
  * @{
  */

/**
  * @brief  It initializes the whole MC core according to user defined 
  *         parameters.
  * @param  oMCIList pointer to the vector of MCInterface objects that will be
  *         created and initialized. The vector must have length equal to the 
  *         number of motor drives.
  * @param  oMCTList pointer to the vector of MCTuning objects that will be
  *         created and initialized. The vector must have length equal to the 
  *         number of motor drives.
  * @retval None
  */
void MCboot(CMCI oMCIList[],CMCT oMCTList[]);

/**
  * @brief  It executes some of the control duties on Motor 1 and - if available -  
  *         Motor 2 accordingly with the present state of its state machine. 
  *         In particular, duties not requiring a very precise timing and/or 
  *         needing a low refresh rate are here executed
  * @param  None
  * @retval None
  */
void TSK_LowFrequencyTask(void);

/**
  * @brief  It executes some of the control duties on Motor 1 and - if available -  
  *         Motor 2 accordingly with the present state of its state machine. 
  *         In particular, duties requiring a specific timing 
  *         (e.g. speed controller(s)) are here executed
  * @param  None
  * @retval None
  */
void TSK_MediumFrequencyTask(void);

/**
  * @brief  It executes safety checks (e.g. bus voltage and temperature) for all
  *         drive instances. Faults flags are also here updated     
  * @param  None
  * @retval None
  */
void TSK_SafetyTask(void);

/**
  * @brief  Accordingly with the present state(s) of the state machine(s), it 
  *         executes those motor control duties requiring a high frequency rate
  *         and a precise timing (e.g. FOC current control loop)
  * @param  None
  * @retval uint8_t It return the motor instance number of last executed FOC.
  */
uint8_t TSK_HighFrequencyTask(void);

/**
  * @brief  This function is called by TIMx_UP_IRQHandler in case of dual MC and
  *         it allows to reserve half PWM period in advance the FOC execution on
  *         ADC ISR
  * @param  oDrive pointer to a CFOC object
  * @retval None
  */
void TSK_DualDriveFIFOUpdate(void *oDrive);

/**
  * @brief  This function must be called after MCboot and returns all the 
  *         instances of MCInterface.
  * @param  oMCIList pointer to the vector of MCInterface objects previously 
  *         instantiated by MCboot function. The vector must have length equal 
  *         to the number of motor drives.
  * @retval None.
  */
void GetMCIList(CMCI oMCIList[]);

/**
  * @brief  This function must be called after MCboot and returns all the 
  *         instances of MCTuning.
  * @param  oMCTList pointer to the vector of MCTuning objects previously 
  *         instantiated by MCboot function. The vector must have length equal 
  *         to the number of motor drives.
  * @retval None.
  */
void GetMCTList(CMCT oMCTList[]);

/**
  * @}
  */
  
/**
  * @}
  */

/**
  * @}
  */

#endif /* __MCTASKS_H */

/******************* (C) COPYRIGHT 2011 STMicroelectronics *****END OF FILE****/
