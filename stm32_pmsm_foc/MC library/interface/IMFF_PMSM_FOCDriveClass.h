/**
  ******************************************************************************
  * @file    IMFF_PMSM_FOCDriveClass.h
  * @author  IMS Systems Lab and Technical Marketing - MC Team
  * @version 3.0
  * @date    05-Apr-2011 11:34
  * @brief   This file contains interface of IMFF_PMSM class      
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
#ifndef __IMFF_PMSM_FOCDRIVECLASS_H
#define __IMFF_PMSM_FOCDRIVECLASS_H

/** @addtogroup STM32F10x_PMSM_MC_Library
  * @{
  */
  
/** @addtogroup FOCDrive_IMFF_PMSM
  * @{
  */

/** @defgroup IMFF_PMSM_class_exported_types IMFF_PMSM class exported types
* @{
*/

/** 
  * @brief IMFF_PMSM class init structure type definition
  */
typedef struct
{
  CPI oFluxWeakeningPI;
  CPI oSpeedPI;  
}IMFF_PMSMInit_t;

/** 
  * @brief  Public IMFF_PMSM class definition
  */
typedef struct CIMFF_FOC_t *CIMFF_FOC;

/** 
  * @brief  IMFF_PMSM class parameters definition
  */
typedef const struct
{
  /* MTPA parameters */
  int16_t  hSegDiv;               /*!< Segment divisor */
  int32_t  wAngCoeff[8];          /*!< Angular coefficients table */
  int32_t  wOffset[8];            /*!< Offsets table */

  /* Flux Weakening parameters */
  uint16_t hDefaultFW_V_Ref;      /*!< Default flux weakening voltage reference,
                                  tenth of percentage points*/
  int16_t  hDemagCurrent;         /*!< Demagnetization current in s16A: 
                                    Current(Amp) = [Current(s16A) * Vdd micro]/ 
                                    [65536 * Rshunt * Aop] */
  int32_t  wNominalSqCurr;        /*!< Squared motor nominal current in (s16A)^2 
                                      where: 
                                    Current(Amp) = [Current(s16A) * Vdd micro]/ 
                                    [65536 * Rshunt * Aop] */
  uint16_t hVqdLowPassFilterBW;   /*!< Use this parameter to configure the Vqd 
                                      first order software filter bandwidth. 
                                      hVqdLowPassFilterBW = FOC_CurrController 
                                      call rate [Hz]/ FilterBandwidth[Hz] in 
                                      case FULL_MISRA_COMPLIANCY is defined. 
                                      On the contrary, if FULL_MISRA_COMPLIANCY 
                                      is not defined, hVqdLowPassFilterBW is 
                                      equal to log with base two of previous 
                                      definition */ 
  int32_t  wConstant_1D;          /*!< Feed forward constant for d axes */
  int32_t  wConstant_1Q;          /*!< Feed forward constant for q axes */
  int32_t  wConstant_2;           /*!< Constant used by Feed-Forward algorithm*/
}IMFF_PMSMParams_t, *pIMFF_PMSMParams_t;

/**
  * @}
  */

/** @defgroup IMFF_PMSM_class_exported_methods IMFF_PMSM class exported methods
  * @{
  */
  
/**
  * @brief  Creates an object of the class IMFF_PMSM
  * @param  pFOCDriveParams pointer to an FOCDrive parameters structure
  * @param  pIMFF_PMSMParams pointer to an IMFF_PMSM parameters structure
  * @retval CIMFF_FOC new instance of IMFF_PMSM object
  */
CIMFF_FOC IMFF_NewObject(pFOCDriveParams_t pFOCDriveParams, pIMFF_PMSMParams_t 
                                                               pIMFF_PMSMParams);
/**
  * @brief  Use this method to set a new value for the voltage reference used by 
  *         flux weakening algorithm
  * @param  this related object of class CIMFF_FOC
  * @param  uint16_t New target voltage value, expressend in tenth of percentage
  *         points of available voltage
* @retval none
  */
void IMFF_SetVref(CIMFF_FOC this, uint16_t hNewVref);

/**
  * @brief  It returns the present value of target voltage used by flux 
  *         weakening algorihtm
  * @param  this related object of class CIMFF_FOC
  * @retval int16_t Present target voltage value expressed in tenth of 
  *         percentage points of available voltage
  */
uint16_t IMFF_GetVref(CIMFF_FOC this);

/**
  * @brief  It returns the present value of voltage actually used by flux 
  *         weakening algorihtm
  * @param  this related object of class CIMFF_FOC
  * @retval int16_t Present averaged phase stator voltage value, expressed 
  *         in s16V (0-to-peak), where 
  *         PhaseVoltage(V) = [PhaseVoltage(s16A) * Vbus(V)] /[sqrt(3) *32767]
  *         N.B. A more precise estimation is obtained subtracting from Vbus the
  *              voltage drop on switches
  */
int16_t IMFF_GetAvVAmplitude(CIMFF_FOC this);

/**
  * @brief  It returns the measure of present voltage actually used by flux 
  *         weakening algorihtm as percentage of available voltage.
  * @param  this related object of class CIMFF_FOC
  * @retval uint16_t Present averaged phase stator voltage value, expressed in 
  *         tenth of percentage points of available voltage
  */
uint16_t IMFF_GetAvVPercentage(CIMFF_FOC this);
/**
  * @}
  */
  
/**
  * @}
  */

/**
  * @}
  */

#endif /*__IMFF_PMSM_FOCDRIVECLASS_H*/

/******************* (C) COPYRIGHT 2011 STMicroelectronics *****END OF FILE****/
