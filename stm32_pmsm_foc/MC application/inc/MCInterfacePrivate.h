/**
  ******************************************************************************
  * @file    MCInterfacePrivate.h
  * @author  IMS Systems Lab and Technical Marketing - MC Team
  * @version 3.0
  * @date    05-Apr-2011 11:34
  * @brief   This file contains private definition of MCInterface class      
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
#ifndef __MCINTERFACEPRIVATE_H
#define __MCINTERFACEPRIVATE_H

/** @addtogroup STM32F10x_PMSM_MC_Interface
  * @{
  */

/** @addtogroup MCInterface
  * @{
  */

/** @defgroup MCInterface_class_private_types MCInterface class private types
* @{
*/

/** 
  * @brief  MCInterface class members definition
  */
typedef struct
{
	CSTM oSTM; /*!< State machine object used by MCI.*/
	CSTC oSTC; /*!< Speed and torque controller object used by MCI.*/
	CFOC oFOC; /*!< FOC drive object used by MCI.*/
	bool (*pActions)(CMCI this, int16_t hParam1, uint16_t hParam2); 
             /*!< Pointer to the private MCI function to be called when the 
                  buffered command condition occurs.*/
	int16_t hParam1; 
             /*!< First parameter related to the buffered command.*/
	uint16_t hParam2; 
             /*!< Second parameter related to the buffered command.*/
	uint16_t hTrigState; 
             /*!< Bit field containing the states, of the related oSTM object, 
                  that can trigger the buffered command.*/
	CommandState_t CommandState; 
             /*!< The status of the buffered command.*/	
}Vars_t,*pVars_t;

/** 
  * @brief  Redefinition of parameter structure
  */
typedef MCInterfaceParams_t Params_t, *pParams_t;

/** 
  * @brief  Private MCInterface class definition 
  */
typedef struct
{
	Vars_t Vars_str; 		/*!< Class members container */
	pParams_t pParams_str;	/*!< Class parameters container */
}_CMCI_t, *_CMCI;
/**
  * @}
  */
  
/**
  * @}
  */

/**
  * @}
  */

#endif /*__MCINTERFACEPRIVATE_H*/

/******************* (C) COPYRIGHT 2011 STMicroelectronics *****END OF FILE****/
