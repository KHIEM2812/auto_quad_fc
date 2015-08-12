/**
  ******************************************************************************
  * @file    PID_PIRegulatorClass.h
  * @author  IMS Systems Lab and Technical Marketing - MC Team
  * @version 3.0
  * @date    05-Apr-2011 11:34
  * @brief   This file contains interface of Derived class      
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
#ifndef __PID_PICLASS_H
#define __PID_PICLASS_H

/** @addtogroup STM32F10x_PMSM_MC_Library
  * @{
  */
  
/** @addtogroup PI_regulator_PID
  * @{
  */

/** @defgroup PID_class_exported_types PID regulator class exported types
* @{
*/

/** 
  * @brief  Public PID class definition
  */
typedef struct CPID_PI_t *CPID_PI;

/** 
  * @brief  PID class parameters definition
  */
typedef const struct
{
  int16_t hDefKdGain;           /*!< Default Kd gain, used to initialize Kd 
                                     gain software variable */
  uint16_t hKdDivisor;          /*!< Kd gain divisor, used in conjuction with 
                                     Kd gain allows obtaining fractional values. 
                                     If FULL_MISRA_C_COMPLIANCY is not defined 
                                     the divisor is implemented through 
                                     algebrical right shifts to speed up PI 
                                     execution. Only in this case this parameter
                                     specifies the number of right shifts to be 
                                     executed */
}PIDParams_t, *pPIDParams_t;
/**
  * @}
  */

/** @defgroup PID_class_exported_methods PID class exported methods
  * @{
  */
  
/**
  * @brief  Creates an object of the derived class PID
  * @param  pPIParams_t pointer to PI regulator class parameters structure
  * @param  pPIDParams_t pointer to a PID Derived class parameters structure
  * @retval CPID_PI new instance of derived class object
  */
CPID_PI PID_NewObject(pPIParams_t pPIParam,
                                  pPIDParams_t pPIDParam);
/**
  * @brief  It initiliazes all the object variables, usually it has to be called 
  *         once right after object creation
  * @param  CPID_PI PID regulator object
  * @retval None
  */
void PID_ObjectInit(CPID_PI this);

/**
  * @brief  It set a new value into the PID Previous error variable required to 
  *         compute derivative term
  * @param  CPID_PI PID regulator object
  * @param  int32_t New integral term value
  * @retval None
  */
void PID_SetPrevError(CPID_PI this, int32_t wPrevProcessVarError);

/**
  * @brief  It updates the Kd gain 
  * @param  CPID_PI PID regulator object
  * @param  int16_t New Kd gain
  * @retval None
  */
void PID_SetKD(CPID_PI this, int16_t hKdGain);

/**
  * @brief  It returns the Kd gain of the PID object passed 
  * @param  CPID_PI PID regulator object
  * @retval int16_t Kd gain
  */
int16_t PID_GetKD(CPID_PI this);

/**
  * @brief  It returns the Kd gain divisor of the PID object passed 
  * @param  CPID_PI PID regulator object
  * @retval int16_t Kd gain
  */
uint16_t PID_GetKDDivisor(CPID_PI this);

/**
  * @brief  This function compute the output of a PID regulator sum of its 
  *         proportional, integral and derivative terms
  * @param  CPID_PI PID regulator object
  * @param  Present process variable error, intended as the 
  *         reference value minus the present process variable value
  * @retval int16_t PID output
  */
int16_t PID_Controller(CPID_PI  this, int32_t wProcessVarError); 
/**
  * @}
  */
  
/**
  * @}
  */

/**
  * @}
  */

#endif /*__PID_PICLASS_H*/

/******************* (C) COPYRIGHT 2011 STMicroelectronics *****END OF FILE****/
