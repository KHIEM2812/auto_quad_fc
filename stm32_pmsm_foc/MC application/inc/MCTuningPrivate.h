/**
  ******************************************************************************
  * @file    MCTuningPrivate.h
  * @author  IMS Systems Lab and Technical Marketing - MC Team
  * @version 3.0
  * @date    05-Apr-2011 11:34
  * @brief   This file contains private definition of MCTuning class      
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
#ifndef __MCTUNINGPRIVATE_H
#define __MCTUNINGPRIVATE_H

/** @addtogroup STM32F10x_PMSM_MC_Interface
  * @{
  */

/** @addtogroup MCTuning
  * @{
  */

/** @defgroup MCTuning_class_private_types MCTuning class private types
* @{
*/

/** 
  * @brief  MCTuning class members definition
  */
typedef struct
{
	MCTuningInitStruct_t MCTuningInitStruct;
}Vars_t,*pVars_t;

/** 
  * @brief  Redefinition of parameter structure
  */
typedef MCTuningParams_t Params_t, *pParams_t;

/** 
  * @brief  Private MCTuning class definition 
  */
typedef struct
{
	Vars_t Vars_str; 		/*!< Class members container */
	pParams_t pParams_str;	/*!< Class parameters container */
}_CMCT_t, *_CMCT;
/**
  * @}
  */
  
/**
  * @}
  */

/**
  * @}
  */

#endif /*__MCTUNINGPRIVATE_H*/

/******************* (C) COPYRIGHT 2011 STMicroelectronics *****END OF FILE****/
