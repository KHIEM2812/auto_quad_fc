/**
  ******************************************************************************
  * @file    MCInterfaceClassPrivate.h
  * @author  IMS Systems Lab and Technical Marketing - MC Team
  * @version 3.0
  * @date    05-Apr-2011 11:34
  * @brief   This file contains private interface of MCInterface class      
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
#ifndef __MCINTERFACECLASSPRIVATE_H
#define __MCINTERFACECLASSPRIVATE_H

/** @addtogroup STM32F10x_PMSM_MC_Interface
  * @{
  */

/** @addtogroup MCInterface
  * @{
  */

/** @defgroup MCInterface_class_private_methods MCInterface class private methods
  * @{
  */

/**
  * @brief  Creates an object of the class MCInterface
  * @param  pMCInterfaceParams pointer to an MCInterface parameters structure
  * @retval CMCI new instance of MCInterface object
  */
CMCI MCI_NewObject(pMCInterfaceParams_t pMCInterfaceParams);

/**
  * @brief  Initializes all the object variables, usually it has to be called 
  *         once right after object creation. It is also used to assign the 
  *         state machine object, the speed and torque controller, and the FOC
  *         drive object to be used by MC Interface.
  * @param  this related object of class CMCI.
  * @param  oSTM the state machine object used by the MCI.
  * @param  oSTC the speed and torque controller used by the MCI.
  * @param  oFOC the FOC drive object used by the MCI.
  * @retval none.
  */
void MCI_Init(CMCI this, CSTM oSTM, CSTC oSTC, CFOC oFOC);

/**
  * @brief  This is usually a method managed by task. It must be called 
  *         periodically in order to check the status of the related oSTM object
  *         and eventually to execute the buffered command if the condition 
  *         occurs.
  * @param  this related object of class CMCI.
  * @retval none.
  */
void MCI_UpdateCommand(CMCI this);
/**
  * @}
  */
  
/**
  * @}
  */

/**
  * @}
  */

#endif /*__MCINTERFACECLASSPRIVATE_H*/

/******************* (C) COPYRIGHT 2011 STMicroelectronics *****END OF FILE****/
