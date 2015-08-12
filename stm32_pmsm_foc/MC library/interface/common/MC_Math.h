/**
  ******************************************************************************
  * @file    MC_Math.h
  * @author  IMS Systems Lab and Technical Marketing - MC Team
  * @version 3.0
  * @date    05-Apr-2011 11:34
  * @brief   This file contains interface of MC Math module  
  ******************************************************************************
  * @copy
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
#ifndef __MC_MATH_H
#define __MC_MATH_H

/* Includes ------------------------------------------------------------------*/
#include "MC_type.h"

/** @addtogroup STM32F10x_PMSM_MC_Library
  * @{
  */

/** @addtogroup MC_Math
  * @{
  */

/** @defgroup MC_Math_exported_types MC Mathemical exported types
  * @{
  */

/** 
  * @brief  Trigonometrical functions type definition 
  */
  typedef struct
  {
    s16 hCos;
    s16 hSin;
  } Trig_Components;

/**
  * @}
  */

/** @defgroup MC_Math_Exported_Functions MC Math exported functions
  * @{
  */

/**
  * @brief  This function transforms stator currents Ia and qIb (which are 
  *         directed along axes each displaced by 120 degrees) into currents 
  *         Ialpha and Ibeta in a stationary qd reference frame.
  *                               Ialpha = Ia
  *                       Ibeta = -(2*Ib+Ia)/sqrt(3)
  * @param  Curr_Input: stator current Ia and Ib in Curr_Components format
  * @retval Stator current Ialpha and Ibeta in Curr_Components format
  */
Curr_Components MCM_Clarke(Curr_Components Curr_Input);

/**
  * @brief  This function transforms stator currents Ialpha and Ibeta, which 
  *         belong to a stationary qd reference frame, to a rotor flux 
  *         synchronous reference frame (properly oriented), so as Iq and Id.
  *                   Id= Ialpha *sin(theta)+qIbeta *cos(Theta)
  *                   Iq=qIalpha *cos(Theta)-qIbeta *sin(Theta)            
  * @param  Curr_Input: stator current Ialpha and Ibeta in Curr_Components format
  * @param  Theta: rotating frame angular position in q1.15 format
  * @retval Stator current Iq and Id in Curr_Components format
  */
Curr_Components MCM_Park(Curr_Components Curr_Input, int16_t Theta);

/**
  * @brief  This function transforms stator voltage qVq and qVd, that belong to 
  *         a rotor flux synchronous rotating frame, to a stationary reference 
  *         frame, so as to obtain qValpha and qVbeta:
  *                  Valfa= Vq*Cos(theta)+ Vd*Sin(theta)
  *                  Vbeta=-Vq*Sin(theta)+ Vd*Cos(theta)     
  * @param  Curr_Input: stator voltage Vq and Vd in Volt_Components format
  * @param  Theta: rotating frame angular position in q1.15 format
  * @retval Stator voltage Valpha and Vbeta in Volt_Components format
  */
Volt_Components MCM_Rev_Park(Volt_Components Volt_Input, int16_t Theta);


/**
  * @brief  This function returns cosine and sine functions of the angle fed in 
  *         input
  * @param  hAngle: angle in q1.15 format
  * @retval Trig_Components Cos(angle) and Sin(angle) in Trig_Components format
  */
Trig_Components MCM_Trig_Functions(int16_t hAngle);

/**
  * @brief  It calculates the square root of a non-negative s32. It returns 0 
  *         for negative s32.
  * @param  Input int32_t number
  * @retval int32_t Square root of Input (0 if Input<0)
  */
int32_t MCM_Sqrt(int32_t wInput);
/**
  * @}
  */

/**
  * @}
  */

/**
  * @}
  */
#endif /*__MC_MATH_H*/
/******************* (C) COPYRIGHT 2011 STMicroelectronics *****END OF FILE****/
