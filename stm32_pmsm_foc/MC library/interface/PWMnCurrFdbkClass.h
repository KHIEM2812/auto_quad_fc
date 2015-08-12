/**
  ******************************************************************************
  * @file    PWMnCurrFdbkClass.h
  * @author  IMS Systems Lab and Technical Marketing - MC Team
  * @version 3.0
  * @date    05-Apr-2011 11:34
  * @brief   This file contains interface of PWMnCurrFdbk class      
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
#ifndef __PWMNCURRFDBKCLASS_H
#define __PWMNCURRFDBKCLASS_H

/* Includes ------------------------------------------------------------------*/
#include "MC_type.h"

/** @addtogroup STM32F10x_PMSM_MC_Library
  * @{
  */

/** @addtogroup PWMnCurrFdbk
  * @{
  */


/** @defgroup PWMnCurrFdbk_class_exported_types PWMnCurrFdbk class exported types
* @{
*/

/** 
  * @brief  Public PWMnCurrFdbk class definition 
  */
typedef struct CPWMC_t *CPWMC;

/** 
  * @brief  PWMnCurrFdbk class parameters definition  
  */
typedef const struct
{
  uint16_t hPWMperiod;                 /*!< It contains the PWM period expressed
                                            in timer clock cycles unit: 
                                            hPWMPeriod = Timer Fclk / Fpwm    */
}PWMnCurrFdbkParams_t, *pPWMnCurrFdbkParams_t;
  
/**
* @}
*/

/** @defgroup PWMnCurrFdbk_class_exported_methods PWMnCurrFdbk class exported methods
  * @{
  */

/**
  * @brief  Initiliaze all the object variables and MCU peripherals, usually 
  *         it has to be called once right after object creation.
  *         Note: All the GPIOx port peripherals clocks are here enabled.
  *         Note: If the derived class is IHD2, R1HD2 or R3HD2 it is required
  *               to call the specific xxx_StartTimers method after the
  *               PWMC_Init call.
  * @param  this PWM 'n Current feedback object
  * @param  pDrive Pointer to 'Drive' class object related to PWMnCurrClass 
                   object. It will be returned by the MC TIMx update IRQ handler
  * @retval none
  */
void PWMC_Init(CPWMC this, void *pDrive);

/**
* @brief  It is used to get the motor phase current in Curr_Components format 
          as read by AD converter.
* @param  this: PWM 'n Current feedback object
* @param  pStator_Currents Pointer to the struct that will receive motor current
*         of phase A and B in Curr_Components format.
* @retval none.
*/
void PWMC_GetPhaseCurrents(CPWMC this,Curr_Components* pStator_Currents);

/**
  * @brief  It converts input voltage components Valfa, beta into duty cycles 
  *         and feed it to the inverter
  * @param  this: PWM 'n Current feedback object
  * @param  Valfa_beta: Voltage Components in alfa beta reference frame
  * @retval It returns the code error 'MC_FOC_DURATION' if any, 'MC_NO_ERROR' 
  *         otherwise. These error codes are defined in MC_type.h
  */
uint16_t PWMC_SetPhaseVoltage(CPWMC this, Volt_Components Valfa_beta);

/**
  * @brief  It switch off the PWM generation, setting to inactive the outputs
  * @param  this: PWM 'n Current feedback object
  * @retval none
  */
void PWMC_SwitchOffPWM(CPWMC this);

/**
  * @brief  It switch on the PWM generation
  * @param  this: PWM 'n Current feedback object
  * @retval None
  */
void PWMC_SwitchOnPWM(CPWMC this);

/**
  * @brief  It calibrates ADC current conversions by reading the offset voltage
  *         present on ADC pins when no motor current is flowing. It's suggested
  *         to call this function before each motor start-up
  * @param  this: PWM 'n Current feedback object
  * @retval None
  */
void PWMC_CurrentReadingCalibr(CPWMC this);

/**
  * @brief  It turns on low sides. This function is intended to be used for
  *         charging boot capacitors of driving section. It has to be called each 
  *         motor start-up when using high voltage drivers
  * @param  this: PWM 'n Current feedback object
  * @retval None
  */

void PWMC_TurnOnLowSides(CPWMC this);

/**
* @brief  Execute a regular conversion using ADC1. 
*         The function is not re-entrant (can't executed twice at the same time)
*         It returns 0xFFFF in case of conversion error.
* @param  this related object of class CPWMC, ADC channel to be converted
* @param  bChannel ADC channel used for the regular conversion
* @retval It returns converted value or oxFFFF for conversion error
*/
uint16_t PWMC_ExecRegularConv(CPWMC this, uint8_t bChannel);

/**
* @brief  It sets the specified sampling time for the specified ADC channel
*         on ADC1. It must be called once for each channel utilized by user
* @param  this related object of class CPWMC
* @param  ADConv_struct struct containing ADC channel and sampling time
* @retval none
*/
void PWMC_ADC_SetSamplingTime(CPWMC this, ADConv_t ADConv_struct);

/**
* @brief  It is used to check if an overcurrent occurred since last call.
* @param  this related object of class CPWMC
* @retval uint16_t It returns MC_BREAK_IN whether an overcurrent has been 
*                  detected since last method call, MC_NO_FAULTS otherwise.
*/
uint16_t PWMC_CheckOverCurrent(CPWMC this);
/**
  * @}
  */
  
/**
  * @}
  */

/**
  * @}
  */

#endif /* __PWMNCURRFDBKCLASS_H */

/******************* (C) COPYRIGHT 2011 STMicroelectronics *****END OF FILE****/
