/**
  ******************************************************************************
  * @file    SM_PMSM_FOCDriveClass.h
  * @author  IMS Systems Lab and Technical Marketing - MC Team
  * @version 3.0
  * @date    05-Apr-2011 11:34
  * @brief   This file contains interface of SM_PMSM class      
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
#ifndef __SM_PMSM_FOCDRIVECLASS_H
#define __SM_PMSM_FOCDRIVECLASS_H

/** @addtogroup STM32F10x_PMSM_MC_Library
  * @{
  */
  
/** @addtogroup FOCDrive_SM_PMSM
  * @{
  */

/** @defgroup SM_PMSM_class_exported_types SM_PMSM class exported types
* @{
*/

/** 
  * @brief  Public SM_PMSM class definition
  */
typedef struct CSM_FOC_t *CSM_FOC;

/** 
  * @brief  SM_PMSM class parameters definition
  */
typedef const void SM_PMSMParams_t, *pSM_PMSMParams_t;

/**
  * @}
  */

/** @defgroup SM_PMSM_class_exported_methods SM_PMSM class exported methods
  * @{
  */
  
/**
  * @brief  Creates an object of the class SM_PMSM
  * @param  pFOCDriveParams pointer to an FOCDrive parameters structure
  * @param  pSM_PMSMParams pointer to an SM_PMSM parameters structure
  * @retval CSM_FOC new instance of SM_PMSM object
  */
CSM_FOC SM_NewObject(pFOCDriveParams_t pFOCDriveParams, pSM_PMSMParams_t pSM_PMSMParams);

/**
  * @}
  */
  
/**
  * @}
  */

/**
  * @}
  */

#endif /*__SM_PMSM_FOCDRIVECLASS_H*/

/******************* (C) COPYRIGHT 2011 STMicroelectronics *****END OF FILE****/
