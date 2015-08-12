/**
  ******************************************************************************
  * @file    SystemNDriveParams.h
  * @author  IMS Systems Lab and Technical Marketing - MC Team
  * @version 3.0
  * @date    05-Apr-2011 11:34
  * @brief   This file contains System & Drive constant initialization      
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
#ifndef __SYSTEMNDRIVE_PARAMS_H
#define __SYSTEMNDRIVE_PARAMS_H

#include "Definitions.h"

#include "PMSM motor parameters.h"
#include "Power stage parameters.h"
#include "Drive parameters.h"
#include "Control stage parameters.h"
#include "Parameters conversion.h"

#include "PMSM motor 2 parameters.h"
#include "Power stage parameters motor 2.h"
#include "Drive parameters motor 2.h"
#include "Control stage parameters motor 2.h"
#include "Parameters conversion motor 2.h"
#include "stm32f10x_conf.h"

#ifdef DUALDRIVE

/**
  * @brief  PI / PID Speed loop parameters Motor 2
  */
PIParams_t PISpeedParamsM2 = 
{
  (int16_t)PID_SPEED_KP_DEFAULT2,  /*!< Default Kp gain, used to initialize Kp gain
                                     software variable*/
  (int16_t)PID_SPEED_KI_DEFAULT2,   /*!< Default Ki gain, used to initialize Ki gain
                                     software variable*/
  (uint16_t)SP_KPDIV2,               /*!< Kp gain divisor, used in conjuction with 
                                     Kp gain allows obtaining fractional values. 
                                     If FULL_MISRA_C_COMPLIANCY is not defined 
                                     the divisor is implemented through 
                                     algebrical right shifts to speed up PI 
                                     execution. Only in this case this parameter
                                     specifies the number of right shifts to be 
                                     executed */
  (uint16_t)SP_KIDIV2,               /*!< Ki gain divisor, used in conjuction with 
                                     Ki gain allows obtaining fractional values. 
                                     If FULL_MISRA_C_COMPLIANCY is not defined 
                                     the divisor is implemented through 
                                     algebrical right shifts to speed up PI 
                                     execution. Only in this case this parameter
                                     specifies the number of right shifts to be 
                                     executed */
  (int32_t)IQMAX2 * (int32_t)SP_KIDIV2,/*!< Upper limit used to saturate the integral 
                                     term given by Ki / Ki divisor * integral of
                                     process variable error */ 
  -(int32_t)IQMAX2 * (int32_t)SP_KIDIV2,/*!< Lower limit used to saturate the integral 
                                     term given by Ki / Ki divisor * integral of
                                     process variable error */    
  (int16_t)IQMAX2,                 /*!< Upper limit used to saturate the PI output 
                                     */ 
  -(int16_t)IQMAX2,                /*!< Lower limit used to saturate the PI output 
                                     */ 
};

/**
  * @brief  PI / PID Iq loop parameter Motor 2
  */
PIParams_t PIIqParamsM2 =
{
  (int16_t)PID_TORQUE_KP_DEFAULT2, /*!< Default Kp gain, used to initialize Kp gain
                                     software variable*/
  (int16_t)PID_TORQUE_KI_DEFAULT2, /*!< Default Ki gain, used to initialize Ki gain
                                     software variable*/
  (uint16_t)TF_KPDIV2,               /*!< Kp gain divisor, used in conjuction with 
                                     Kp gain allows obtaining fractional values. 
                                     If FULL_MISRA_C_COMPLIANCY is not defined 
                                     the divisor is implemented through 
                                     algebrical right shifts to speed up PI 
                                     execution. Only in this case this parameter
                                     specifies the number of right shifts to be 
                                     executed */
  (uint16_t)TF_KIDIV2,               /*!< Ki gain divisor, used in conjuction with 
                                     Ki gain allows obtaining fractional values. 
                                     If FULL_MISRA_C_COMPLIANCY is not defined 
                                     the divisor is implemented through 
                                     algebrical right shifts to speed up PI 
                                     execution. Only in this case this parameter
                                     specifies the number of right shifts to be 
                                     executed */
  (int32_t)S16_MAX * TF_KIDIV2,     /*!< Upper limit used to saturate the integral 
                                     term given by Ki / Ki divisor * integral of
                                     process variable error */ 
  (int32_t)S16_MIN * TF_KIDIV2,             /*!< Lower limit used to saturate the integral 
                                     term given by Ki / Ki divisor * integral of
                                     process variable error */    
  S16_MAX,                        /*!< Upper limit used to saturate the PI output 
                                     */ 
  -S16_MAX,                       /*!< Lower limit used to saturate the PI output 
                                     */ 
};

/**
  * @brief  PI / PID Id loop parameter Motor 2
  */
PIParams_t PIIdParamsM2 = 
{
  (int16_t)PID_FLUX_KP_DEFAULT2,    /*!< Default Kp gain, used to initialize Kp gain
                                    software variable*/
  (int16_t)PID_FLUX_KI_DEFAULT2,    /*!< Default Ki gain, used to initialize Ki gain
                                     software variable*/
  (uint16_t)TF_KPDIV2,              /*!< Kp gain divisor, used in conjuction with 
                                     Kp gain allows obtaining fractional values. 
                                     If FULL_MISRA_C_COMPLIANCY is not defined 
                                     the divisor is implemented through 
                                     algebrical right shifts to speed up PI 
                                     execution. Only in this case this parameter
                                     specifies the number of right shifts to be 
                                     executed */
  (uint16_t)TF_KIDIV2,              /*!< Ki gain divisor, used in conjuction with 
                                     Ki gain allows obtaining fractional values. 
                                     If FULL_MISRA_C_COMPLIANCY is not defined 
                                     the divisor is implemented through 
                                     algebrical right shifts to speed up PI 
                                     execution. Only in this case this parameter
                                     specifies the number of right shifts to be 
                                     executed */
  (int32_t)S16_MAX * TF_KIDIV2,             /*!< Upper limit used to saturate the integral 
                                     term given by Ki / Ki divisor * integral of
                                     process variable error */ 
  (int32_t)S16_MIN * TF_KIDIV2,             /*!< Lower limit used to saturate the integral 
                                     term given by Ki / Ki divisor * integral of
                                     process variable error */    
  S16_MAX,                       /*!< Upper limit used to saturate the PI output 
                                     */ 
  -S16_MAX,                      /*!< Lower limit used to saturate the PI output 
                                     */ 
};

/**
  * @brief  PI Flux Weakening control parameters Motor 2
  */
PIParams_t PIFluxWeakeningParamsM2 = 
{
  (int16_t)FW_KP_GAIN2,             /*!< Default Kp gain, used to initialize Kp gain
                                     software variable*/
  (int16_t)FW_KI_GAIN2,              /*!< Default Ki gain, used to initialize Ki gain
                                     software variable*/
  (uint16_t)FW_KPDIV2,              /*!< Kp gain divisor, used in conjuction with 
                                     Kp gain allows obtaining fractional values. 
                                     If FULL_MISRA_C_COMPLIANCY is not defined 
                                     the divisor is implemented through 
                                     algebrical right shifts to speed up PI 
                                     execution. Only in this case this parameter
                                     specifies the number of right shifts to be 
                                     executed */
  (uint16_t)FW_KIDIV2,              /*!< Ki gain divisor, used in conjuction with 
                                     Ki gain allows obtaining fractional values. 
                                     If FULL_MISRA_C_COMPLIANCY is not defined 
                                     the divisor is implemented through 
                                     algebrical right shifts to speed up PI 
                                     execution. Only in this case this parameter
                                     specifies the number of right shifts to be 
                                     executed */
  0,                              /*!< Upper limit used to saturate the integral 
                                     term given by Ki / Ki divisor * integral of
                                     process variable error */ 
  (int32_t)(-NOMINAL_CURRENT2) * (int32_t)FW_KIDIV2, /*!< Lower limit used to saturate the integral 
                                     term given by Ki / Ki divisor * integral of
                                     process variable error */    
  0,                            /*!< Upper limit used to saturate the PI output 
                                     */ 
  -S16_MAX,                     /*!< Lower limit used to saturate the PI output 
                                     */ 
};

/** 
  * @brief  SpeednTorque Controller parameters Motor 2 
  */
SpeednTorqCtrlParams_t SpeednTorqCtrlParamsM2 = 
{
  MEDIUM_FREQUENCY_TASK_RATE2, 		 /*!< Frequency on which the user updates 
                                             the torque reference calling 
                                             STC_CalcTorqueReference method 
                                             expressed in Hz */
  (uint16_t)(MAX_APPLICATION_SPEED2/6),  /*!< Application maximum positive value
                                             of rotor speed. It's expressed in 
                                             tenth of mechanical Hertz.*/
  (uint16_t)(MIN_APPLICATION_SPEED2/6),      /*!< Application minimum positive value
                                             of rotor speed. It's expressed in
                                             tenth of mechanical Hertz.*/
  (int16_t)(-MIN_APPLICATION_SPEED2/6),    /*!< Application maximum negative value
                                             of rotor speed. It's expressed in 
                                             tenth of mechanical Hertz.*/
  (int16_t)(-MAX_APPLICATION_SPEED2/6),/*!< Application minimum negative value
                                             of rotor speed. It's expressed in
                                             tenth of mechanical Hertz.*/
  (int16_t)NOMINAL_CURRENT2,		     /*!< Maximum positive value of motor 
                                             torque. This value represents 
                                             actually the maximum Iq current 
                                             expressed in digit.*/
  -(int16_t)NOMINAL_CURRENT2,                /*!< Maximum negative value of motor 
                                             torque. This value represents 
                                             actually the maximum Iq current 
                                             expressed in digit.*/
  DEFAULT_CONTROL_MODE2,                    /*!< Default STC modality.*/
  (int16_t)(DEFAULT_TARGET_SPEED_RPM2/6),  /*!< Default mechanical rotor speed 
                                             reference expressed in tenths of 
                                             HZ.*/
  (int16_t)DEFAULT_TORQUE_COMPONENT2,     /*!< Default motor torque reference. 
                                             This value represents actually the
                                             Iq current reference expressed in
                                             digit.*/
};

/** 
  * @brief  Current sensor parameters Motor 2 - base class
  */
PWMnCurrFdbkParams_t PWMnCurrFdbkParamsM2 = 
{
  PWM_PERIOD_CYCLES2,                 /*!< It contains the PWM period expressed
                                            in timer clock cycles unit: 
                                            hPWMPeriod = Timer Fclk / Fpwm    */
};
/** 
  * @brief  Current sensor parameters Dual Drive Motor 2 - three shunt, STM32F103 HIGH DENSITY
  */
R3_HD2Params_t R3_HD2ParamsDDM2 = 
{
  ADC_CLOCK_DIVIDER2,                         /*!<  APB2 clock prescaling factor for 
                                          ADC peripheral. It must be RCC_PCLK2_DivX
                                          x = 2, 4, 6, 8 */    
/* Dual MC parameters --------------------------------------------------------*/ 
  2,                                      /*!< Instance number. Necessary to 
                                             properly synchronize TIM8 with 
                                             TIM1 at peripheral initializations  
                                              */ 
  MAX_TWAIT2,                              /*!< It is used for switching the context 
                                           in dual MC. It contains biggest delay
                                           (expressed in counter ticks) between 
                                           the counter crest and ADC latest 
                                           trigger  */
  FREQ_RATIO,                              /*!< It is used in case of dual MC to 
                                           synchronize TIM1 and TIM8. It has 
                                           effect only on the second instanced 
                                           object and must be equal to the 
                                           ratio between the two PWM frequencies
                                           (higher/lower). Supported values are 
                                           1, 2 or 3 */  
  FREQ_RELATION2,                           /*!< When bFreqRatio is greather than 1
                                          this param is used to indicate if this 
                                          instance is the one with the highest 
                                          frequency. Allowed value are: HIGHER_FREQ
                                          or LOWER_FREQ */
  MC_IRQ_PWMNCURRFDBK_2,                     /*!< MC IRQ number used as TIMx Update 
                                           event */
/* Current reading A/D Conversions initialization -----------------------------*/ 
  PHASE_U_CURR_CHANNEL2,                  /*!< ADC channel used for conversion of 
                                           current Ia. It must be equal to  
                                           ADC_Channel_x x= 0, ..., 15*/
  PHASE_U_GPIO_PORT2,                  /*!< GPIO port used by hIaChannel. It must 
                                           be equal to GPIOx x= A, B, ...*/
  PHASE_U_GPIO_PIN2,                      /*!< GPIO pin used by hIaChannel. It must be 
                                          equal to GPIO_Pin_x x= 0, 1, ...*/ 
  SAMPLING_TIME_SEL2,               /*!< Sampling time used to convert hIaChannel. 
                                          It must be equal to ADC_SampleTime_xCycles5 
                                          x= 1, 7, ...*/ 
  PHASE_V_CURR_CHANNEL2,                  /*!< ADC channel used for conversion of 
                                           current Ib. It must be equal to 
                                           ADC_Channel_x x= 0, ..., 15*/  
  PHASE_V_GPIO_PORT2,                /*!< GPIO port used by hIbChannel. It must 
                                           be equal to GPIOx x= A, B, ...*/
  PHASE_V_GPIO_PIN2,                      /*!< GPIO pin used by hIaChannel. It must be 
                                          equal to GPIO_Pin_x x= 0, 1, ...*/
  SAMPLING_TIME_SEL2,                /*!< Sampling time used to convert hIbChannel. 
                                          It must be equal to ADC_SampleTime_xCycles5 
                                          x= 1, 7, ...*/
  PHASE_W_CURR_CHANNEL2,                  /*!< ADC channel used for conversion of 
                                           current Ia. It must be equal to  
                                           ADC_Channel_x x= 0, ..., 15*/
  PHASE_W_GPIO_PORT2,                /*!< GPIO port used by hIaChannel. It must 
                                           be equal to GPIOx x= A, B, ...*/
  PHASE_W_GPIO_PIN2,                      /*!< GPIO pin used by hIaChannel. It must be 
                                          equal to GPIO_Pin_x x= 0, 1, ...*/ 
  SAMPLING_TIME_SEL2,            /*!< Sampling time used to convert hIaChannel. 
                                          It must be equal to ADC_SampleTime_xCycles5 
                                          x= 1, 7, ...*/ 
  
/* PWM generation parameters --------------------------------------------------*/   
  DEAD_TIME_COUNTS2,
                                          /*!< Dead time in number of TIM clock
                                            cycles. If CHxN are enabled, it must
                                            contain the dead time to be generated
                                            by the microcontroller, otherwise it 
                                            expresses the maximum dead time 
                                            generated by driving network */
  REP_COUNTER2,                                  /*!< It expresses the number of PWM 
                                            periods to be elapsed before compare 
                                            registers are updated again. In 
                                            particular: 
                                            RepetitionCounter= (2* #PWM periods)-1*/
  TW_AFTER2,                             /*!< It is the sum of dead time plus max 
                                            value between rise time and noise time
                                            express in number of TIM clocks.*/
  TW_BEFORE2,                           /*!< It is the sampling time express in
                                            number of TIM clocks.*/ 
  PWM_TIMER_SELECTION2,                  /*!< It contains the pointer to the timer 
                                           used for PWM generation. */
/* PWM Driving signals initialization ----------------------------------------*/  

  PWM_TIMER_REMAPPING2,            /*!< Used only for instance #1, it 
                                       remaps TIM1 outputs. It must equal to 
                                       GPIO_PartialRemap_TIM1 or 
                                       GPIO_FullRemap_TIM1 or
                                       GPIO_NoRemap_TIM1 */
  PHASE_UH_POLARITY2,   	           /*!< Channel 1 (high side) output polarity, 
                                           it must be TIM_OCPolarity_High or 
                                           TIM_OCPolarity_Low */
  PHASE_UH_GPIO_PORT2,                                 /*!< Channel 1 (high side) GPIO output 
                                         port (if used, after re-mapping). 
                                         It must be GPIOx x= A, B, ...*/
  PHASE_UH_GPIO_PIN2,                       /*!< Channel 1 (high side) GPIO output pin 
                                          (if used, after re-mapping). It must be 
                                          GPIO_Pin_x x= 0, 1, ...*/  
  IDLE_UH_POLARITY2,              /*!< Channel 1 (high side) state (low or high)
                                            when TIM peripheral is in Idle state.
                                            It must be TIM_OCIdleState_Set or
                                            TIM_OCIdleState_Reset*/
                                            
  PHASE_VH_POLARITY2,               /*!< Channel 2 (high side) output polarity, 
                                           it must be TIM_OCPolarity_High or 
                                           TIM_OCPolarity_Low */ 
  PHASE_VH_GPIO_PORT2,                               /*!< Channel 2 (high side) GPIO output 
                                           port (if used, after re-mapping). 
                                           It must be GPIOx x= A, B, ...*/
  PHASE_VH_GPIO_PIN2,                       /*!< Channel 2 (high side) GPIO output pin 
                                          (if used, after re-mapping). It must be 
                                          GPIO_Pin_x x= 0, 1, ...*/
  IDLE_VH_POLARITY2,              /*!< Channel 2 (high side) state (low or high)
                                            when TIM peripheral is in Idle state.
                                            It must be TIM_OCIdleState_Set or
                                            TIM_OCIdleState_Reset*/    
 
  PHASE_WH_POLARITY2,            	 /*!< Channel 3 (high side) output polarity, 
                                           it must be TIM_OCPolarity_High or 
                                           TIM_OCPolarity_Low */  
  PHASE_WH_GPIO_PORT2,                               /*!< Channel 3 (high side) GPIO output 
                                           port (if used, after re-mapping). 
                                           It must be GPIOx x= A, B, ...*/
  PHASE_WH_GPIO_PIN2,                        /*!< Channel 3 (high side) GPIO output pin 
                                          (if used, after re-mapping). It must be 
                                          GPIO_Pin_x x= 0, 1, ...*/  
  IDLE_WH_POLARITY2,              /*!< Channel 3 (high side) state (low or high)
                                            when TIM peripheral is in Idle state.
                                            It must be TIM_OCIdleState_Set or
                                            TIM_OCIdleState_Reset*/  
  
  (FunctionalState)LOW_SIDE_SIGNALS_ENABLING2,  /*!< It enable/disable the PWM low side  
                                          driving signals. It must be either 
                                          equal to ENABLE or DISABLE */ 
  
  PHASE_UL_POLARITY2,               /*!< Channel 1N (low side) output polarity, 
                                           it must be TIM_OCNPolarity_High or 
                                           TIM_OCNPolarity_Low */
  PHASE_UL_GPIO_PORT2,                                 /*!< Channel 1N (low side) GPIO output 
                                           port (if used, after re-mapping). 
                                           It must be GPIOx x= A, B, ...*/
  PHASE_UL_GPIO_PIN2,                       /*!< Channel 1N (low side) GPIO output pin 
                                          (if used, after re-mapping). It must be 
                                          GPIO_Pin_x x= 0, 1, ...*/ 
  IDLE_UL_POLARITY2,              /*!< Channel 1N (low side) state (low or high)
                                            when TIM peripheral is in Idle state.
                                            It must be TIM_OCNIdleState_Set or
                                            TIM_OCNIdleState_Reset*/ 

  
  PHASE_VL_POLARITY2,                 /*!< Channel 2N (low side) output polarity, 
                                           it must be TIM_OCNPolarity_High or 
                                           TIM_OCNPolarity_Low */
  PHASE_VL_GPIO_PORT2,                                 /*!< Channel 2N (low side) GPIO output 
                                           port (if used, after re-mapping). 
                                           It must be GPIOx x= A, B, ...*/
  PHASE_VL_GPIO_PIN2,                     /*!< Channel 2N (low side) GPIO output pin 
                                          (if used, after re-mapping). It must be 
                                          GPIO_Pin_x x= 0, 1, ...*/ 
  IDLE_VL_POLARITY2,              /*!< Channel 2N (low side) state (low or high)
                                            when TIM peripheral is in Idle state.
                                            It must be TIM_OCNIdleState_Set or
                                            TIM_OCNIdleState_Reset*/ 
  
  PHASE_WL_POLARITY2,             /*!< Channel 3N (low side) output polarity, 
                                           it must be TIM_OCNPolarity_High or 
                                           TIM_OCNPolarity_Low */
  PHASE_WL_GPIO_PORT2,                               /*!< Channel 3N (low side)  GPIO output 
                                           port (if used, after re-mapping). 
                                           It must be GPIOx x= A, B, ...*/
  PHASE_WL_GPIO_PIN2,                    /*!< Channel 3N (low side)  GPIO output pin 
                                          (if used, after re-mapping). It must be 
                                          GPIO_Pin_x x= 0, 1, ...*/   
  IDLE_WL_POLARITY2,              /*!< Channel 3N (low side) state (low or high)
                                            when TIM peripheral is in Idle state.
                                            It must be TIM_OCNIdleState_Set or
                                            TIM_OCNIdleState_Reset*/ 
/* Emergency signal initialization ----------------------------------------*/  
 (FunctionalState)SW_OV_CURRENT_PROT_ENABLING2, /*!< It enable/disable the management of 
                                            an emergency input instantaneously 
                                            stopping PWM generation. It must be 
                                            either equal to ENABLE or DISABLE */  
  OVERCURR_FEEDBACK_POLARITY2,               /*!< Emergency Stop (BKIN) input polarity, 
                                           it must be TIM_BreakPolarity_Low or 
                                           TIM_BreakPolarity_High */
  EMERGENCY_STOP_GPIO_PORT2,             /*!< Emergency Stop (BKIN) GPIO input 
                                           port (if used, after re-mapping). 
                                           It must be GPIOx x= A, B, ...*/
  EMERGENCY_STOP_GPIO_PIN2,              /*!< Emergency Stop (BKIN) GPIO input pin 
                                         (if used, after re-mapping). It must be 
                                          GPIO_Pin_x x= 0, 1, ...*/        
};


/** 
  * @brief  Current sensor parameters Dual Drive Motor 2 - one shunt, STM32F103 HIGH DENSITY
  */
R1_HD2Params_t R1_HD2ParamsDDM2 = 
{  
  ADC_CLOCK_DIVIDER2,          /*!<  APB2 clock prescaling factor for 
                                          ADC peripheral. It must be RCC_PCLK2_DivX
                                          x = 2, 4, 6, 8. Only the first instance 
                                          parameter is used to set the prescaling
                                          factor*/  

  MC_IRQ_PWMNCURRFDBK_2,                  /*!< MC IRQ number used for UPDATE event */
 
/* Instance number -----------------------------------------------------------*/ 
  2,                                    /*!< Instance number. Necessary to 
                                             properly synchronize PWM Timers and
                                             start peripheral clocks*/  
 M2FIRSTR1,                             /*!< Specifies whether this object is the first
                                             R1HD2 instance or not.*/
 FREQ_RATIO,                            /*!< It is used in case of dual MC to 
                                             synchronize TIM1 and TIM8. It has 
                                             effect only on the second instanced 
                                             object and must be equal to the 
                                             ratio between the two PWM frequencies
                                             (higher/lower). Supported values are 
                                             1, 2 or 3 */  
 FREQ_RELATION2,        			    /*!< When bFreqRatio is greather than 1
                                             this param is used to indicate if this 
                                             instance is the one with the highest 
                                             frequency. Allowed value are: HIGHER_FREQ
                                             or LOWER_FREQ */
 PWM_TIMER_SELECTION2,                  /*!< Timer used for PWM generation. It should be
                                              TIM1 or TIM8*/

/* Current reading A/D Conversions initialization -----------------------------*/ 
  PHASE_CURRENTS_CHANNEL2,                    /*!< ADC channel used for conversion of 
                                           current. It must be equal to  
                                           ADC_Channel_x x= 0, ..., 15*/
  PHASE_CURRENTS_GPIO_PORT2,                 /*!< GPIO port used by hIChannel. It must 
                                           be equal to GPIOx x= A, B, ...*/
  PHASE_CURRENTS_GPIO_PIN2,                       /*!< GPIO pin used by hIChannel. It must be 
                                          equal to GPIO_Pin_x x= 0, 1, ...*/ 
  SAMPLING_TIME_SEL2,              /*!< Sampling time used to convert hIChannel. 
                                          It must be equal to ADC_SampleTime_xCycles5 
                                          x= 1, 7, ...*/ 
  
/* PWM generation parameters --------------------------------------------------*/   
  DEAD_TIME_COUNTS2,                    /*!< Dead time in number of TIM clock
                                            cycles. If CHxN are enabled, it must
                                            contain the dead time to be generated
                                            by the microcontroller, otherwise it 
                                            expresses the maximum dead time 
                                            generated by driving network */
  REP_COUNTER2,                       /*!< It expresses the number of PWM 
                                            periods to be elapsed before compare 
                                            registers are updated again. In 
                                            particular: 
                                            RepetitionCounter= (2* #PWM periods)-1*/
  TAFTER2,     /*!< It must be equal to ((u16)(((DEADTIME_NS+((u16)(TRISE_NS)))*24ul)/1000ul))*/
  TBEFORE2,    /*!< It must be equal to (((u16)(((((u16)(SAMPLING_TIME_NS)))*24ul)/1000ul))+1)*/
  TMIN2,       /*!< It must be equal to (((u16)(((DEADTIME_NS+((u16)(TRISE_NS))+((u16)(SAMPLING_TIME_NS)))*24uL)/1000ul))+1)*/
  HTMIN2,      /*!< It must be equal to (u16)(TMIN >> 1)*/
  TSAMPLE2,    /*!< It must be equal to (u16)(((u16)(SAMPLING_TIME_NS) * 24uL)/1000uL)*/
  MAX_TRTS2,    /*!< It must be equal to 2*(u16)((((u16)(TRISE_NS)) * 24uL)/1000uL) if TRISE_NS > SAMPLING_TIME_NS
                             to 2*hTSample otherwise */
  
/* PWM Driving signals initialization ----------------------------------------*/  

  PWM_TIMER_REMAPPING2,            /*!< Used only for instance #1, it 
                                       remaps TIM1 outputs. It must equal to 
                                       GPIO_PartialRemap_TIM1 or 
                                       GPIO_FullRemap_TIM1 or
                                       GPIO_NoRemap_TIM1 */
  PHASE_UH_POLARITY2,   	           /*!< Channel 1 (high side) output polarity, 
                                           it must be TIM_OCPolarity_High or 
                                           TIM_OCPolarity_Low */
  PHASE_UH_GPIO_PORT2,                                 /*!< Channel 1 (high side) GPIO output 
                                         port (if used, after re-mapping). 
                                         It must be GPIOx x= A, B, ...*/
  PHASE_UH_GPIO_PIN2,                       /*!< Channel 1 (high side) GPIO output pin 
                                          (if used, after re-mapping). It must be 
                                          GPIO_Pin_x x= 0, 1, ...*/  
  IDLE_UH_POLARITY2,              /*!< Channel 1 (high side) state (low or high)
                                            when TIM peripheral is in Idle state.
                                            It must be TIM_OCIdleState_Set or
                                            TIM_OCIdleState_Reset*/
                                            
  PHASE_VH_POLARITY2,               /*!< Channel 2 (high side) output polarity, 
                                           it must be TIM_OCPolarity_High or 
                                           TIM_OCPolarity_Low */ 
  PHASE_VH_GPIO_PORT2,                               /*!< Channel 2 (high side) GPIO output 
                                           port (if used, after re-mapping). 
                                           It must be GPIOx x= A, B, ...*/
  PHASE_VH_GPIO_PIN2,                       /*!< Channel 2 (high side) GPIO output pin 
                                          (if used, after re-mapping). It must be 
                                          GPIO_Pin_x x= 0, 1, ...*/
  IDLE_VH_POLARITY2,              /*!< Channel 2 (high side) state (low or high)
                                            when TIM peripheral is in Idle state.
                                            It must be TIM_OCIdleState_Set or
                                            TIM_OCIdleState_Reset*/    
 
  PHASE_WH_POLARITY2,            	 /*!< Channel 3 (high side) output polarity, 
                                           it must be TIM_OCPolarity_High or 
                                           TIM_OCPolarity_Low */  
  PHASE_WH_GPIO_PORT2,                               /*!< Channel 3 (high side) GPIO output 
                                           port (if used, after re-mapping). 
                                           It must be GPIOx x= A, B, ...*/
  PHASE_WH_GPIO_PIN2,                        /*!< Channel 3 (high side) GPIO output pin 
                                          (if used, after re-mapping). It must be 
                                          GPIO_Pin_x x= 0, 1, ...*/  
  IDLE_WH_POLARITY2,              /*!< Channel 3 (high side) state (low or high)
                                            when TIM peripheral is in Idle state.
                                            It must be TIM_OCIdleState_Set or
                                            TIM_OCIdleState_Reset*/  
  
  (FunctionalState)LOW_SIDE_SIGNALS_ENABLING2,  /*!< It enable/disable the PWM low side  
                                          driving signals. It must be either 
                                          equal to ENABLE or DISABLE */ 
  
  PHASE_UL_POLARITY2,               /*!< Channel 1N (low side) output polarity, 
                                           it must be TIM_OCNPolarity_High or 
                                           TIM_OCNPolarity_Low */
  PHASE_UL_GPIO_PORT2,                                 /*!< Channel 1N (low side) GPIO output 
                                           port (if used, after re-mapping). 
                                           It must be GPIOx x= A, B, ...*/
  PHASE_UL_GPIO_PIN2,                       /*!< Channel 1N (low side) GPIO output pin 
                                          (if used, after re-mapping). It must be 
                                          GPIO_Pin_x x= 0, 1, ...*/ 
  IDLE_UL_POLARITY2,              /*!< Channel 1N (low side) state (low or high)
                                            when TIM peripheral is in Idle state.
                                            It must be TIM_OCNIdleState_Set or
                                            TIM_OCNIdleState_Reset*/ 

  
  PHASE_VL_POLARITY2,                 /*!< Channel 2N (low side) output polarity, 
                                           it must be TIM_OCNPolarity_High or 
                                           TIM_OCNPolarity_Low */
  PHASE_VL_GPIO_PORT2,                                 /*!< Channel 2N (low side) GPIO output 
                                           port (if used, after re-mapping). 
                                           It must be GPIOx x= A, B, ...*/
  PHASE_VL_GPIO_PIN2,                     /*!< Channel 2N (low side) GPIO output pin 
                                          (if used, after re-mapping). It must be 
                                          GPIO_Pin_x x= 0, 1, ...*/ 
  IDLE_VL_POLARITY2,              /*!< Channel 2N (low side) state (low or high)
                                            when TIM peripheral is in Idle state.
                                            It must be TIM_OCNIdleState_Set or
                                            TIM_OCNIdleState_Reset*/ 
  
  PHASE_WL_POLARITY2,             /*!< Channel 3N (low side) output polarity, 
                                           it must be TIM_OCNPolarity_High or 
                                           TIM_OCNPolarity_Low */
  PHASE_WL_GPIO_PORT2,                               /*!< Channel 3N (low side)  GPIO output 
                                           port (if used, after re-mapping). 
                                           It must be GPIOx x= A, B, ...*/
  PHASE_WL_GPIO_PIN2,                    /*!< Channel 3N (low side)  GPIO output pin 
                                          (if used, after re-mapping). It must be 
                                          GPIO_Pin_x x= 0, 1, ...*/   
  IDLE_WL_POLARITY2,              /*!< Channel 3N (low side) state (low or high)
                                            when TIM peripheral is in Idle state.
                                            It must be TIM_OCNIdleState_Set or
                                            TIM_OCNIdleState_Reset*/ 
/* Emergengy signal initialization ----------------------------------------*/  
 (FunctionalState)SW_OV_CURRENT_PROT_ENABLING2, /*!< It enable/disable the management of 
                                            an emergency input instantaneously 
                                            stopping PWM generation. It must be 
                                            either equal to ENABLE or DISABLE */  
  OVERCURR_FEEDBACK_POLARITY2,               /*!< Emergency Stop (BKIN) input polarity, 
                                           it must be TIM_BreakPolarity_Low or 
                                           TIM_BreakPolarity_High */
  EMERGENCY_STOP_GPIO_PORT2,             /*!< Emergency Stop (BKIN) GPIO input 
                                           port (if used, after re-mapping). 
                                           It must be GPIOx x= A, B, ...*/
  EMERGENCY_STOP_GPIO_PIN2              /*!< Emergency Stop (BKIN) GPIO input pin 
                                         (if used, after re-mapping). It must be 
                                          GPIO_Pin_x x= 0, 1, ...*/     
};



/** 
  * @brief  Current sensor parameters Dual Drive Motor 2 - ICS, STM32F103 HIGH 
                                                                          DENSITY
  */
ICS_HD2Params_t ICS_HD2ParamsDDM2 = {
  ADC_CLOCK_DIVIDER2,                         /*!< APB2 clock prescaling factor for 
                                          ADC peripheral. It must be RCC_PCLK2_DivX
                                          x = 2, 4, 6, 8 */  
/* Dual MC parameters --------------------------------------------------------*/ 
  2,                                 /*!< Instance number with reference to PWMC  
                                          base class. It is necessary to properly
                                          synchronize TIM8 with TIM1 at 
                                          peripheral initializations */ 
  MAX_TWAIT2,                               /*!< It is used for switching the context 
                                           in dual MC. It contains biggest delay
                                           (expressed in counter ticks) between 
                                           the counter crest and ADC latest 
                                           trigger  */
  FREQ_RATIO,                 /*!< It is used in case of dual MC to 
                                           synchronize TIM1 and TIM8. It has 
                                           effect only on the second instanced 
                                           object and must be equal to the 
                                           ratio between the two PWM frequencies
                                           (higher/lower). Supported values are 
                                           1, 2 or 3 */  
  FREQ_RELATION2,                           /*!< When bFreqRatio is greather than 1
                                          this param is used to indicate if this 
                                          instance is the one with the highest 
                                          frequency. Allowed value are: HIGHER_FREQ
                                          or LOWER_FREQ */
  MC_IRQ_PWMNCURRFDBK_2,                     /*!< MC IRQ number used as TIMx Update 
                                           event */
/* Current reading A/D Conversions initialization -----------------------------*/ 
  PHASE_U_CURR_CHANNEL2,                  /*!< ADC channel used for conversion of 
                                           current Ia. It must be equal to  
                                           ADC_Channel_x x= 0, ..., 15*/
  PHASE_U_GPIO_PORT2,                  /*!< GPIO port used by hIaChannel. It must 
                                           be equal to GPIOx x= A, B, ...*/
  PHASE_U_GPIO_PIN2,                      /*!< GPIO pin used by hIaChannel. It must be 
                                          equal to GPIO_Pin_x x= 0, 1, ...*/ 
  SAMPLING_TIME_SEL2,               /*!< Sampling time used to convert hIaChannel. 
                                          It must be equal to ADC_SampleTime_xCycles5 
                                          x= 1, 7, ...*/ 
  PHASE_V_CURR_CHANNEL2,                  /*!< ADC channel used for conversion of 
                                           current Ib. It must be equal to 
                                           ADC_Channel_x x= 0, ..., 15*/  
  PHASE_V_GPIO_PORT2,                /*!< GPIO port used by hIbChannel. It must 
                                           be equal to GPIOx x= A, B, ...*/
  PHASE_V_GPIO_PIN2,                      /*!< GPIO pin used by hIaChannel. It must be 
                                          equal to GPIO_Pin_x x= 0, 1, ...*/
  SAMPLING_TIME_SEL2,                /*!< Sampling time used to convert hIbChannel. 
                                          It must be equal to ADC_SampleTime_xCycles5 
                                          x= 1, 7, ...*/
/* PWM generation parameters --------------------------------------------------*/   
  DEAD_TIME_COUNTS2,
                                          /*!< Dead time in number of TIM clock
                                            cycles. If CHxN are enabled, it must
                                            contain the dead time to be generated
                                            by the microcontroller, otherwise it 
                                            expresses the maximum dead time 
                                            generated by driving network */
  REP_COUNTER2,                                  /*!< It expresses the number of PWM 
                                            periods to be elapsed before compare 
                                            registers are updated again. In 
                                            particular: 
                                            RepetitionCounter= (2* #PWM periods)-1*/
  PWM_TIMER_SELECTION2,                  /*!< It contains the pointer to the timer 
                                           used for PWM generation. */
/* PWM Driving signals initialization ----------------------------------------*/  

  PWM_TIMER_REMAPPING2,            /*!< Used only for instance #1, it 
                                       remaps TIM1 outputs. It must equal to 
                                       GPIO_PartialRemap_TIM1 or 
                                       GPIO_FullRemap_TIM1 or
                                       GPIO_NoRemap_TIM1 */
  PHASE_UH_POLARITY2,   	           /*!< Channel 1 (high side) output polarity, 
                                           it must be TIM_OCPolarity_High or 
                                           TIM_OCPolarity_Low */
  PHASE_UH_GPIO_PORT2,                                 /*!< Channel 1 (high side) GPIO output 
                                         port (if used, after re-mapping). 
                                         It must be GPIOx x= A, B, ...*/
  PHASE_UH_GPIO_PIN2,                       /*!< Channel 1 (high side) GPIO output pin 
                                          (if used, after re-mapping). It must be 
                                          GPIO_Pin_x x= 0, 1, ...*/  
  IDLE_UH_POLARITY2,              /*!< Channel 1 (high side) state (low or high)
                                            when TIM peripheral is in Idle state.
                                            It must be TIM_OCIdleState_Set or
                                            TIM_OCIdleState_Reset*/
                                            
  PHASE_VH_POLARITY2,               /*!< Channel 2 (high side) output polarity, 
                                           it must be TIM_OCPolarity_High or 
                                           TIM_OCPolarity_Low */ 
  PHASE_VH_GPIO_PORT2,                               /*!< Channel 2 (high side) GPIO output 
                                           port (if used, after re-mapping). 
                                           It must be GPIOx x= A, B, ...*/
  PHASE_VH_GPIO_PIN2,                       /*!< Channel 2 (high side) GPIO output pin 
                                          (if used, after re-mapping). It must be 
                                          GPIO_Pin_x x= 0, 1, ...*/
  IDLE_VH_POLARITY2,              /*!< Channel 2 (high side) state (low or high)
                                            when TIM peripheral is in Idle state.
                                            It must be TIM_OCIdleState_Set or
                                            TIM_OCIdleState_Reset*/    
 
  PHASE_WH_POLARITY2,            	 /*!< Channel 3 (high side) output polarity, 
                                           it must be TIM_OCPolarity_High or 
                                           TIM_OCPolarity_Low */  
  PHASE_WH_GPIO_PORT2,                               /*!< Channel 3 (high side) GPIO output 
                                           port (if used, after re-mapping). 
                                           It must be GPIOx x= A, B, ...*/
  PHASE_WH_GPIO_PIN2,                        /*!< Channel 3 (high side) GPIO output pin 
                                          (if used, after re-mapping). It must be 
                                          GPIO_Pin_x x= 0, 1, ...*/  
  IDLE_WH_POLARITY2,              /*!< Channel 3 (high side) state (low or high)
                                            when TIM peripheral is in Idle state.
                                            It must be TIM_OCIdleState_Set or
                                            TIM_OCIdleState_Reset*/  
  
  (FunctionalState)LOW_SIDE_SIGNALS_ENABLING2,  /*!< It enable/disable the PWM low side  
                                          driving signals. It must be either 
                                          equal to ENABLE or DISABLE */ 
  
  PHASE_UL_POLARITY2,               /*!< Channel 1N (low side) output polarity, 
                                           it must be TIM_OCNPolarity_High or 
                                           TIM_OCNPolarity_Low */
  PHASE_UL_GPIO_PORT2,                                 /*!< Channel 1N (low side) GPIO output 
                                           port (if used, after re-mapping). 
                                           It must be GPIOx x= A, B, ...*/
  PHASE_UL_GPIO_PIN2,                       /*!< Channel 1N (low side) GPIO output pin 
                                          (if used, after re-mapping). It must be 
                                          GPIO_Pin_x x= 0, 1, ...*/ 
  IDLE_UL_POLARITY2,              /*!< Channel 1N (low side) state (low or high)
                                            when TIM peripheral is in Idle state.
                                            It must be TIM_OCNIdleState_Set or
                                            TIM_OCNIdleState_Reset*/ 

  
  PHASE_VL_POLARITY2,                 /*!< Channel 2N (low side) output polarity, 
                                           it must be TIM_OCNPolarity_High or 
                                           TIM_OCNPolarity_Low */
  PHASE_VL_GPIO_PORT2,                                 /*!< Channel 2N (low side) GPIO output 
                                           port (if used, after re-mapping). 
                                           It must be GPIOx x= A, B, ...*/
  PHASE_VL_GPIO_PIN2,                     /*!< Channel 2N (low side) GPIO output pin 
                                          (if used, after re-mapping). It must be 
                                          GPIO_Pin_x x= 0, 1, ...*/ 
  IDLE_VL_POLARITY2,              /*!< Channel 2N (low side) state (low or high)
                                            when TIM peripheral is in Idle state.
                                            It must be TIM_OCNIdleState_Set or
                                            TIM_OCNIdleState_Reset*/ 
  
  PHASE_WL_POLARITY2,             /*!< Channel 3N (low side) output polarity, 
                                           it must be TIM_OCNPolarity_High or 
                                           TIM_OCNPolarity_Low */
  PHASE_WL_GPIO_PORT2,                               /*!< Channel 3N (low side)  GPIO output 
                                           port (if used, after re-mapping). 
                                           It must be GPIOx x= A, B, ...*/
  PHASE_WL_GPIO_PIN2,                    /*!< Channel 3N (low side)  GPIO output pin 
                                          (if used, after re-mapping). It must be 
                                          GPIO_Pin_x x= 0, 1, ...*/   
  IDLE_WL_POLARITY2,              /*!< Channel 3N (low side) state (low or high)
                                            when TIM peripheral is in Idle state.
                                            It must be TIM_OCNIdleState_Set or
                                            TIM_OCNIdleState_Reset*/ 
/* Emergengy signal initialization ----------------------------------------*/  
 (FunctionalState)SW_OV_CURRENT_PROT_ENABLING2, /*!< It enable/disable the management of 
                                            an emergency input instantaneously 
                                            stopping PWM generation. It must be 
                                            either equal to ENABLE or DISABLE */  
  OVERCURR_FEEDBACK_POLARITY2,               /*!< Emergency Stop (BKIN) input polarity, 
                                           it must be TIM_BreakPolarity_Low or 
                                           TIM_BreakPolarity_High */
  EMERGENCY_STOP_GPIO_PORT2,             /*!< Emergency Stop (BKIN) GPIO input 
                                           port (if used, after re-mapping). 
                                           It must be GPIOx x= A, B, ...*/
  EMERGENCY_STOP_GPIO_PIN2              /*!< Emergency Stop (BKIN) GPIO input pin 
                                         (if used, after re-mapping). It must be 
                                          GPIO_Pin_x x= 0, 1, ...*/     
};

/** 
  * @brief  SpeedNPosition sensor parameters Motor 2 - Base Class
  */
SpeednPosFdbkParams_t SpeednPosFdbkParamsM2 =
{
  POLE_PAIR_NUM2,                /*!< Coefficient used to transform electrical to
                               mechanical quantities and viceversa. It usually
                               coincides with motor pole pairs number*/
 (uint16_t)(1.15*MAX_APPLICATION_SPEED2/6), /*< Maximum value of measured speed that is
                                          considered to be valid. It's expressed
                                          in tenth of mechanical Hertz.*/
 (uint16_t)(MIN_APPLICATION_SPEED2/6),/*< Minimum value of measured speed that is
                                        considered to be valid. It's expressed
                                        in tenth of mechanical Hertz.*/
  MEAS_ERRORS_BEFORE_FAULTS2,            /*< Maximum value of not valid measurements
                                        before an error is reported.*/
  65535,                                 /*< Maximum value of measured acceleration
                                        that is considered to be valid. It's
                                        expressed in 01HzP (tenth of Hertz per
                                        speed calculation period)*/
  TF_REGULATION_RATE2,                    /*< Frequency on which the user will request
                                    a measurement of the rotor electrical angle.
                                    It's also used to convert measured speed from
                                    tenth of Hz to dpp and viceversa.*/
};

/** 
  * @brief  SpeedNPosition sensor parameters Motor 2 - State Observer + PLL
  */
STOParams_t STOParamsM2 = 
{
   C12,                                /*!< State observer constant C1, it can 
                                           be computed as F1 * Rs(ohm)/(Ls[H] * 
                                           State observer execution rate [Hz])*/
   C22,                               /*!<  Variable containing state observer 
                                           constant C2, it can be computed as 
                                           F1 * K1/ State observer execution 
                                           rate [Hz] being K1 one of the two 
                                           observer gains   */   
   C32,                                /*!< State observer constant C3, it can 
                                           be computed as F1 * Max application 
                                           speed [rpm] * Motor B-emf constant 
                                           [Vllrms/krpm] * sqrt(2)/ (Ls [H] *
                                           max measurable current (A) * State 
                                           observer execution rate [Hz])*/ 
   C42,                                /*!< State Observer constant C4, it can 
                                           be computed as K2 * max measurable 
                                           current (A) / (Max application speed 
                                           [rpm] * Motor B-emf constant 
                                           [Vllrms/krpm] * sqrt(2) * F2 * State 
                                           observer execution rate [Hz]) being 
                                           K2 one of the two observer gains  */
   C52,                                /*!< State Observer constant C5, it can 
                                           be computed as F1 * max measurable 
                                           voltage / (2 * Ls [Hz] * max 
                                           measurable current * State observer 
                                           execution rate [Hz]) */
   F12,                                /*!< State observer scaling factor F1 */
   F22,                                /*!< State observer scaling factor F2 */
   {
     PLL_KP_GAIN2,               /*!< Default Kp gain, used to initialize Kp gain
                                     software variable*/
     PLL_KI_GAIN2,               /*!< Default Ki gain, used to initialize Ki gain
                                     software variable*/
     16384,                       /*!< Kp gain divisor, used in conjuction with 
                                     Kp gain allows obtaining fractional values. 
                                     If FULL_MISRA_C_COMPLIANCY is not defined 
                                     the divisor is implemented through 
                                     algebrical right shifts to speed up PI 
                                     execution. Only in this case this parameter
                                     specifies the number of right shifts to be 
                                     executed */
     65535,                     /*!< Ki gain divisor, used in conjuction with 
                                     Ki gain allows obtaining fractional values. 
                                     If FULL_MISRA_C_COMPLIANCY is not defined 
                                     the divisor is implemented through 
                                     algebrical right shifts to speed up PI 
                                     execution. Only in this case this parameter
                                     specifies the number of right shifts to be 
                                     executed */
     S32_MAX,                   /*!< Upper limit used to saturate the integral 
                                     term given by Ki / Ki divisor * integral of
                                     process variable error */ 
     -S32_MAX,                  /*!< Lower limit used to saturate the integral 
                                     term given by Ki / Ki divisor * integral of
                                     process variable error */    
     S16_MAX,                   /*!< Upper limit used to saturate the PI output 
                                     */ 
     -S16_MAX                   /*!< Lower limit used to saturate the PI output 
                                     */ 
   },                                 /*!< It contains the parameters of the PI
                                           object necessary for PLL 
                                           implementation */
   STO_FIFO_DEPTH_01HZ2,              /*!< Depth of FIFO used to average 
                                           estimated speed exported by 
                                           SPD_GetAvrgMecSpeed01Hz. It 
                                           must be an integer number between 1 
                                           and 64 */  
   STO_FIFO_DEPTH_DPP2,               /*!< Depth of FIFO used for both averaging 
                                           estimated speed exported by 
                                           SPD_GetElSpeedDpp and state 
                                           observer equations. It must be an 
                                           integer number between 1 and
                                           bSpeedBufferSize01Hz */       
   PERCENTAGE_FACTOR2,                /*!< Parameter expressing the maximum 
                                           allowed variance of speed estimation 
                                           */ 
   SPEED_BAND_UPPER_LIMIT2,           /*!< It expresses how much estimated speed
                                           can exceed forced stator electrical 
                                           frequency during start-up without 
                                           being considered wrong. The 
                                           measurement unit is 1/16 of forced 
                                           speed */
  SPEED_BAND_LOWER_LIMIT2,                                /*!< It expresses how much estimated speed
                                           can be below forced stator electrical 
                                           frequency during start-up without 
                                           being considered wrong. The 
                                           measurement unit is 1/16 of forced 
                                           speed */
   OBS_MINIMUM_SPEED2,                     /*!< Minimum mechanical speed (expressed in 
                                          01Hz required to validate the start-up
                                          */
    NB_CONSECUTIVE_TESTS2,  			   /*!< Number of consecutive tests on speed */

   OBS_MEAS_ERRORS_BEFORE_FAULTS2,            /*!< Number of reliability failed 
                                           consecutive tests before a speed 
                                           check fault is returned to base class 
                                           */
  BEMF_CONSISTENCY_TOL2,                     /*!< Degree of consistency of the observed
                                           back-emfs, it must be an integer
                                           number ranging from 1 (very high 
                                           consistency) down to 64 (very poor
                                           consistency) */
  BEMF_CONSISTENCY_GAIN2,               /*!< Gain to be applied when checking
                                           back-emfs consistency; default value
                                           is 64 (neutral), max value 105
                                           (x1,64 amplification), min value 1
                                           (/64 attenuation) */
  (uint16_t)(MAX_APPLICATION_SPEED2*1.15/6.0)  /*!< Maximum positive value
                                             of rotor speed. It's expressed in 
                                             tenth of mechanical Hertz. It can be
                                             x1.1 greater than max application*/  
};

/** 
  * @brief  SpeedNPosition sensor parameters Motor 2 - State Observer + CORDIC
  */
STO_CORDICParams_t STO_CORDICParamsM2 = 
{
   CORD_C12,                                /*!< State observer constant C1, it can 
                                           be computed as F1 * Rs(ohm)/(Ls[H] * 
                                           State observer execution rate [Hz])*/
   CORD_C22,                               /*!<  Variable containing state observer 
                                           constant C2, it can be computed as 
                                           F1 * K1/ State observer execution 
                                           rate [Hz] being K1 one of the two 
                                           observer gains   */   
   CORD_C32,                                /*!< State observer constant C3, it can 
                                           be computed as F1 * Max application 
                                           speed [rpm] * Motor B-emf constant 
                                           [Vllrms/krpm] * sqrt(2)/ (Ls [H] *
                                           max measurable current (A) * State 
                                           observer execution rate [Hz])*/ 
   CORD_C42,                                /*!< State Observer constant C4, it can 
                                           be computed as K2 * max measurable 
                                           current (A) / (Max application speed 
                                           [rpm] * Motor B-emf constant 
                                           [Vllrms/krpm] * sqrt(2) * F2 * State 
                                           observer execution rate [Hz]) being 
                                           K2 one of the two observer gains  */
   CORD_C52,                                /*!< State Observer constant C5, it can 
                                           be computed as F1 * max measurable 
                                           voltage / (2 * Ls [Hz] * max 
                                           measurable current * State observer 
                                           execution rate [Hz]) */
   CORD_F12,                                /*!< State observer scaling factor F1 */
   CORD_F22,                                /*!< State observer scaling factor F2 */
   CORD_FIFO_DEPTH_01HZ2,              /*!< Depth of FIFO used to average 
                                           estimated speed exported by 
                                           SPD_GetAvrgMecSpeed01Hz. It 
                                           must be an integer number between 1 
                                           and 64 */  
   CORD_FIFO_DEPTH_DPP2,               /*!< Depth of FIFO used for both averaging 
                                           estimated speed exported by 
                                           SPD_GetElSpeedDpp and state 
                                           observer equations. It must be an 
                                           integer number between 1 and
                                           bSpeedBufferSize01Hz */       
  CORD_PERCENTAGE_FACTOR2,                /*!< Parameter expressing the maximum 
                                           allowed variance of speed estimation 
                                           */ 
  SPEED_BAND_UPPER_LIMIT2,           /*!< It expresses how much estimated speed
                                           can exceed forced stator electrical 
                                           frequency during start-up without 
                                           being considered wrong. The 
                                           measurement unit is 1/16 of forced 
                                           speed */
  SPEED_BAND_LOWER_LIMIT2,              /*!< It expresses how much estimated speed
                                           can be below forced stator electrical 
                                           frequency during start-up without 
                                           being considered wrong. The 
                                           measurement unit is 1/16 of forced 
                                           speed */
  OBS_MINIMUM_SPEED2,                     /*!< Minimum mechanical speed (expressed in 
                                          01Hz required to validate the start-up
                                          */
   NB_CONSECUTIVE_TESTS2,            /*!< Number of consecutive tests on speed */

   CORD_MEAS_ERRORS_BEFORE_FAULTS2,            /*!< Number of reliability failed 
                                           consecutive tests before a speed 
                                           check fault is returned to base class 
                                           */
   CORD_MAX_ACCEL_DPPP2,             /*!< maximum instantaneous electrical
                                         acceleration (dpp per control period) */
   CORD_BEMF_CONSISTENCY_TOL2,                 /*!< Degree of consistency of the observed
                                           back-emfs, it must be an integer
                                           number ranging from 1 (very high 
                                           consistency) down to 64 (very poor
                                           consistency) */
  CORD_BEMF_CONSISTENCY_GAIN2,            /*!< Gain to be applied when checking
                                           back-emfs consistency; default value
                                           is 64 (neutral), max value 105
                                           (x1,64 amplification), min value 1
                                           (/64 attenuation) */
  (uint16_t)(MAX_APPLICATION_SPEED2*1.15/6.0)  /*!< Maximum positive value
                                             of rotor speed. It's expressed in 
                                             tenth of mechanical Hertz. It can be
                                             x1.1 greater than max application*/                                          
};

/** 
  * @brief  SpeedNPosition sensor parameters Motor 2 - Virtual Sensor
  */
VirtualSpeedSensorParams_t VirtualSpeedSensorParamsM2 = 
{
  MEDIUM_FREQUENCY_TASK_RATE2,  	      /*!< Frequency (Hz) at which motor speed is to 
                                      be computed. It must be equal to the frequency
                                      at which function SPD_CalcAvrgMecSpeed01Hz
                                      is called.*/
  (int16_t)(TF_REGULATION_RATE2*TRANSITION_DURATION2/1000.0), 
					/*< Number of steps to perform 
                             the transition phase from CVSS_SPD to other CSPD;
                             if the Transition PHase should last TPH milliseconds,
                             and the FOC Execution Frequency is set to FEF kHz,
                             then hTransitionSteps = TPH * FEF*/                                      
};

/** 
  * @brief  RevUp controller parameters Motor 2
  */
RUCPhasesParams_t Phase5_M2 = 
{
  (uint16_t)PHASE5_DURATION2,     /*!< Duration of the rev up phase expressed in
                                       milliseconds.*/
  (int16_t)(PHASE5_FINAL_SPEED_RPM2/6),/*!< Mechanical speed expressed in 0.1Hz assumed
                                     by VSS at the end of the rev up phase.*/
  (int16_t)PHASE5_FINAL_CURRENT2,  /*!< Motor torque reference imposed by STC at the
                                     end of rev up phase. This value represents
                                     actually the Iq current expressed in digit.*/
  MC_NULL
};
RUCPhasesParams_t Phase4_M2 = 
{
  (uint16_t)PHASE4_DURATION2,     /*!< Duration of the rev up phase expressed in
                                       milliseconds.*/
  (int16_t)(PHASE4_FINAL_SPEED_RPM2/6),/*!< Mechanical speed expressed in 0.1Hz assumed
                                     by VSS at the end of the rev up phase.*/
  (int16_t)PHASE4_FINAL_CURRENT2,   /*!< Motor torque reference imposed by STC at the
                                     end of rev up phase. This value represents
                                     actually the Iq current expressed in digit.*/
  (void*)&Phase5_M2
};

RUCPhasesParams_t Phase3_M2 = 
{
  (uint16_t)PHASE3_DURATION2,     /*!< Duration of the rev up phase expressed in
                                       milliseconds.*/
  (int16_t)(PHASE3_FINAL_SPEED_RPM2/6),/*!< Mechanical speed expressed in 0.1Hz assumed
                                     by VSS at the end of the rev up phase.*/
  (int16_t)PHASE3_FINAL_CURRENT2,   /*!< Motor torque reference imposed by STC at the
                                     end of rev up phase. This value represents
                                     actually the Iq current expressed in digit.*/
  (void*)&Phase4_M2
};

RUCPhasesParams_t Phase2_M2 = 
{
  (uint16_t)PHASE2_DURATION2,     /*!< Duration of the rev up phase expressed in
                                       milliseconds.*/
  (int16_t)(PHASE2_FINAL_SPEED_RPM2/6),/*!< Mechanical speed expressed in 0.1Hz assumed
                                     by VSS at the end of the rev up phase.*/
  (int16_t)PHASE2_FINAL_CURRENT2,   /*!< Motor torque reference imposed by STC at the
                                     end of rev up phase. This value represents
                                     actually the Iq current expressed in digit.*/
  (void*)&Phase3_M2
};

RUCPhasesParams_t Phase1_M2 = 
{
  (uint16_t)PHASE1_DURATION2,     /*!< Duration of the rev up phase expressed in
                                       milliseconds.*/
  (int16_t)(PHASE1_FINAL_SPEED_RPM2/6),/*!< Mechanical speed expressed in 0.1Hz assumed
                                     by VSS at the end of the rev up phase.*/
  (int16_t)PHASE1_FINAL_CURRENT2,   /*!< Motor torque reference imposed by STC at the
                                     end of rev up phase. This value represents
                                     actually the Iq current expressed in digit.*/
  (void*)&Phase2_M2
};

RevupCtrlParams_t RevupCtrlParamsM2 =
{
  MEDIUM_FREQUENCY_TASK_RATE2, /*!< Frequency expressed in Hz at which the user
                                 clocks the RUC calling RUC_Exec method */
 (int16_t)((int32_t)(STARTING_ANGLE_DEG2)* 65536/360),    /*!< Starting angle of programmed rev up.*/
  &Phase1_M2,                /*!< Pointer of the first element of 
                                     phase params that constitute the programmed 
                                     rev up. Each element is of type 
                                     RUCPhasesParams_t.*/
  FIRST_SLESS_ALGO_PHASE2                                     
};

/** 
  * @brief  SpeedNPosition sensor parameters Motor 2 - Encoder
  */
ENCODERParams_t ENCParamsM2 =
{
  /* SW Settings */
  MC_IRQ_SPEEDNPOSFDBK_2, /*!< MC IRQ number used for TIMx capture update event.*/
  
  ENCODER_PPR2*4,		  /*!< Number of pulses per revolution, provided by each
                              of the two encoder signals, multiplied by 4 */
  (FunctionalState)ENC_INVERT_SPEED2,	
                              /*!< To be enabled if measured speed is opposite
                              to real one (ENABLE/DISABLE)*/  
  10*MEDIUM_FREQUENCY_TASK_RATE2, /*!< Frequency (01Hz) at which motor speed is to be
                                   computed. It must be equal to the frequency
                                   at which function SPD_CalcAvrgMecSpeed01Hz
                                   is called.*/
  
  ENC_AVERAGING_FIFO_DEPTH2, /*!< Size of the buffer used to calculate the average 
                             speed. It must be <= 16.*/
  
  ENC_IC_FILTER2,	   /*!< Time filter applied to validate ENCODER sensor
                                capture. This value defines the frequency 
                                used to sample ENCODER sensors input and the 
                                length of the digital filter applied. 
                                The digital filter is made of an event 
                                counter in which N events are needed to 
                                validate a transition on the input.
                                0000: No filter, sampling is done at fCK_INT.
                                0001: fSAMPLING=fCK_INT , N=2. 
                                0010: fSAMPLING=fCK_INT , N=4.
                                0011: fSAMPLING=fCK_INT , N=8. 
                                0100: fSAMPLING=fCK_INT/2, N=6.
                                0101: fSAMPLING=fCK_INT/2, N=8.
                                0110: fSAMPLING=fCK_INT/4, N=6.
                                0111: fSAMPLING=fCK_INT/4, N=8.
                                1000: fSAMPLING=fCK_INT/8, N=6.
                                1001: fSAMPLING=fCK_INT/8, N=8.
                                1010: fSAMPLING=fCK_INT/16, N=5.
                                1011: fSAMPLING=fCK_INT/16, N=6.
                                1100: fSAMPLING=fCK_INT/16, N=8.
                                1101: fSAMPLING=fCK_INT/32, N=5.
                                1110: fSAMPLING=fCK_INT/32, N=6.
                                1111: fSAMPLING=fCK_INT/32, N=8 */
  /* HW Settings */
  ENC_TIMER2,	    /*!< Timer used for ENCODER sensor management.*/
  
  ENC_RCC_PERIPHERAL2,        /*!< RCC Clock related to timer TIMx. 
                                     (Ex. RCC_APB1Periph_TIM2).*/
  
  ENC_IRQ_CHANNEL2,        /*!< IRQ Channel related to TIMx. 
                                (Ex. TIM2_IRQChannel).*/
  
  ENC_TIMER_REMAPPING2,		 /*!< It remaps TIMx outputs. It must equal to 
                                GPIO_PartialRemap_TIMx, GPIO_FullRemap_TIMx or 
                                GPIO_NoRemap_TIMx according the HW availability*/
  
  ENC_A_GPIO_PORT2,        /*!< ENCODER sensor A channel GPIO input port (if used, 
                              after re-mapping). It must be GPIOx x= A, B, ...*/
  
  ENC_A_GPIO_PIN2,       /*!< ENCODER sensor A channel GPIO input pin (if used, 
                              after re-mapping). It must be GPIO_Pin_x x=0,1,.*/
  
  ENC_B_GPIO_PORT2,	 /*!< ENCODER sensor B channel GPIO input port (if used, 
                              after re-mapping). It must be GPIOx x= A, B, ...*/
  
  ENC_B_GPIO_PIN2,       /*!< ENCODER sensor B channel GPIO input pin (if used, 
                              after re-mapping). It must be GPIO_Pin_x x= 0,1,.*/
  
};

/** 
  * @brief  Encoder Alignment Controller parameters Motor 2
  */
EncAlignCtrlParams_t EncAlignCtrlParamsM2 =
{
  MEDIUM_FREQUENCY_TASK_RATE2, /*!< Frequency
                                 expressed in Hz at which the user 
                                 clocks the EAC calling EAC_Exec method */
  FINAL_I_ALIGNMENT2,              /*!< Motor torque reference imposed by STC at the 
                                 end of programmed alignment. This value 
                                 represents actually the Iq current expressed in
                                 digit.*/
  ALIGNMENT_ANGLE_S162,      /*!< Mechanical angle of programmed alignment 
                                 expressed in s16degrees.*/
  T_ALIGNMENT2               /*!< Duration of the programmed alignment expressed
                                 in milliseconds.*/
};

/** 
  * @brief  SpeedNPosition sensor parameters Motor 2 - HALL
  */
HALLParams_t HALLParamsM2 =
{
  /* SW Settings */
  MC_IRQ_SPEEDNPOSFDBK_2,   /*!< MC IRQ number used for TIMx capture update event.*/

  HALL_SENSORS_PLACEMENT2,   /*!< Define here the mechanical position of the sensors 
                             with reference to an electrical cycle.
                             Allowed values are: DEGREES_120 or DEGREES_60.*/
  
  (int16_t)(HALL_PHASE_SHIFT2 * 65536/360),
                            /*!< Define here in s16degree the electrical phase shift 
                             between the low to high transition of signal H1 and
                             the maximum of the Bemf induced on phase A.*/
  
  MEDIUM_FREQUENCY_TASK_RATE2, /*!< Frequency (Hz) at which motor speed is to 
                             be computed. It must be equal to the frequency
                             at which function SPD_CalcAvrgMecSpeed01Hz
                             is called.*/
  
  HALL_AVERAGING_FIFO_DEPTH2, /*!< Size of the buffer used to calculate the average 
                             speed. It must be less than 18.*/
  
  HALL_IC_FILTER2,         /*!< Time filter applied to validate HALL sensor capture.
                             This value defines the frequency used to sample 
                             HALL sensors input and the length of the digital
                             filter applied. The digital filter is made of an 
                             event counter in which N events are needed to 
                             validate a transition on the input.
                                0000: No filter, sampling is done at fCK_INT.
                                0001: fSAMPLING=fCK_INT , N=2. 
                                0010: fSAMPLING=fCK_INT , N=4.
                                0011: fSAMPLING=fCK_INT , N=8. 
                                0100: fSAMPLING=fCK_INT/2, N=6.
                                0101: fSAMPLING=fCK_INT/2, N=8.
                                0110: fSAMPLING=fCK_INT/4, N=6.
                                0111: fSAMPLING=fCK_INT/4, N=8.
                                1000: fSAMPLING=fCK_INT/8, N=6.
                                1001: fSAMPLING=fCK_INT/8, N=8.
                                1010: fSAMPLING=fCK_INT/16, N=5.
                                1011: fSAMPLING=fCK_INT/16, N=6.
                                1100: fSAMPLING=fCK_INT/16, N=8.
                                1101: fSAMPLING=fCK_INT/32, N=5.
                                1110: fSAMPLING=fCK_INT/32, N=6.
                                1111: fSAMPLING=fCK_INT/32, N=8 */
								
  /* HW Settings */
  HALL_TIM_CLK2,          /*!< Timer clock frequency express in Hz.*/

  HALL_TIMER2,        /*!< Timer used for HALL sensor management.*/
  
  HALL_RCC_PERIPHERAL2, 
                        /*!< RCC Clock related to timer TIMx. 
                             (Ex. RCC_APB1Periph_TIM2).*/
  
  HALL_IRQ_CHANNEL2,            /*!< IRQ Channle related to TIMx. 
                             (Ex. TIM2_IRQChannel).*/
  
  HALL_TIMER_REMAPPING2, 
                        /*!< It remaps TIMx outputs. It must equal to 
                             GPIO_PartialRemap_TIMx, GPIO_FullRemap_TIMx or 
                             GPIO_NoRemap_TIMx according the HW availability.*/
  
  H1_GPIO_PORT2, 
                        /*!< HALL sensor H1 channel GPIO input port (if used, 
                             after re-mapping). It must be GPIOx x= A, B, ...*/
  
  H1_GPIO_PIN2,           /*!< HALL sensor H1 channel GPIO output pin (if used, 
                             after re-mapping). It must be GPIO_Pin_x x= 0, 1, 
                             ...*/
  
  H2_GPIO_PORT2, 
                        /*!< HALL sensor H2 channel GPIO input port (if used, 
                             after re-mapping). It must be GPIOx x= A, B, ...*/
  
  H2_GPIO_PIN2,           /*!< HALL sensor H2 channel GPIO output pin (if used, 
                             after re-mapping). It must be GPIO_Pin_x x= 0, 1, 
                             ...*/
  
  H3_GPIO_PORT2, 
                        /*!< HALL sensor H3 channel GPIO input port (if used, 
                             after re-mapping). It must be GPIOx x= A, B, ...*/
  
  H3_GPIO_PIN2            /*!< HALL sensor H3 channel GPIO output pin (if used, 
                             after re-mapping). It must be GPIO_Pin_x x= 0, 1, 
                             ...*/
};


/** 
  * @brief  Real Bus Voltage sensor parameters Motor 2 - Base class
  */
BusVoltageSensorParams_t RealBusVoltageSensorParamsM2 =
{
  REAL_SENSOR,                   /*!< It contains the information about the type 
                                   of instanced bus voltage sensor object.  
                                   It can be equal to REAL_SENSOR or 
                                   VIRTUAL_SENSOR */
  (uint16_t)(3.3/BUS_ADC_CONV_RATIO2),  /*!< It is used to convert bus voltage from 
                                   u16Volts into real Volts (V). 
                                   1 u16Volt = 65536/hConversionFactor Volts
                                   For real sensors hConversionFactor it's 
                                   equal to the product between the expected MCU
                                   voltage and the partioning network 
                                   attenuation. For virtual sensors it is
                                   assumed to be equal to 500 */
};

/** 
  * @brief  Virtual Bus Voltage sensor parameters Motor 2 - Base class
  */
BusVoltageSensorParams_t VirtualBusVoltageSensorParamsM2 =
{
  VIRTUAL_SENSOR,                   /*!< It contains the information about the type 
                                   of instanced bus voltage sensor object.  
                                   It can be equal to REAL_SENSOR or 
                                   VIRTUAL_SENSOR */
  500                              /*!< It is used to convert bus voltage from 
                                   u16Volts into real Volts (V). 
                                   1 u16Volt = 65536/hConversionFactor Volts
                                   For real sensors hConversionFactor it's 
                                   equal to the product between the expected MCU
                                   voltage and the partioning network 
                                   attenuation. For virtual sensors it is
                                   assumed to be equal to 500 */
};

/** 
  * @brief  Bus Voltage sensor parameters Motor 2 - Rdivider
  */
RdividerParams_t RdividerParamsM2 =
{
  VBUS_CHANNEL2,           /*!< ADC channel used for conversion of 
                                         bus voltage. It must be equal to  
                                         ADC_Channel_x x= 0, ..., 15*/
  VBUS_GPIO_PORT2, /*!< GPIO port used by bVbusADChannel. 
                                         It must be equal to GPIOx x= A, B, ...*/                                                                             
  VBUS_GPIO_PIN2,  /*!< GPIO pin used by bVbusChannel. It must  
                                         be equal to GPIO_Pin_x x= 0, 1, ...*/ 
  VBUS_SAMPLING_TIME2,              /*!< Sampling time used for bVbusChannel AD
                                         conversion. It must be equal to  
                                         ADC_SampleTime_xCycles5 x= 1, 7, ...*/  
  VBUS_SW_FILTER_BW_FACTOR2,         /*!< Use this number to configure the Vbus 
                                         first order software filter bandwidth. 
                                         hLowPassFilterBW = VBS_CalcBusReading 
                                         call rate [Hz]/ FilterBandwidth[Hz] */   
  OVERVOLTAGE_THRESHOLD_d2,         /*!< It represents the over voltage protection
                                         intervention threshold. To be expressed 
                                         in digit through formula:
                                         hOverVoltageThreshold (digit) = 
                                         Over Voltage Threshold (V) * 65536 
                                                          / hConversionFactor */
  UNDERVOLTAGE_THRESHOLD_d2,        /*!< It represents the under voltage protection
                                         intervention threshold. To be expressed 
                                         in digit through formula:                                         
                                         hUnderVoltageThreshold (digit) = 
                                         Under Voltage Threshold (V) * 65536 
                                                          / hConversionFactor */
};

/** 
  * @brief  Virtual Bus Voltage sensor parameters Motor 2 - VirtualParams
  */
VirtualParams_t VirtualBusParamsM2 =
{
  1+(NOMINAL_BUS_VOLTAGE_V2*65536)/500 /*!< Expected Vbus voltage expressed in 
                                           digit*/ 
};

/** 
  * @brief  Real temperature sensor parameters Motor 2 - Base class  
  */
TempSensorParams_t RealTempSensorParamsM2=
{
  REAL_SENSOR,                   /*!< It contains the information about the type 
                                   of instanced temperature sensor object.  
                                   It can be equal to REAL_SENSOR or 
                                   VIRTUAL_SENSOR */
};

/** 
  * @brief  Virtual temperature sensor parameters Motor 2 - Base class  
  */
TempSensorParams_t VirtualTempSensorParamsM2=
{
  VIRTUAL_SENSOR,                   /*!< It contains the information about the type 
                                   of instanced temperature sensor object.  
                                   It can be equal to REAL_SENSOR or 
                                   VIRTUAL_SENSOR */
};

/** 
  * @brief  Temperature sensor parameters Motor 2 - NTC  
  */
NTCParams_t NTCParamsM2 =
{
  TEMP_FDBK_CHANNEL2,                       /*!< ADC channel used for conversion of 
                                         bus voltage. It must be equal to  
                                         ADC_Channel_x x= 0, ..., 15*/
  TEMP_FDBK_GPIO_PORT2,                  /*!< GPIO port used by bVbusADChannel. 
                                         It must be equal to GPIOx x= A, B, ...*/                                                                             
  TEMP_FDBK_GPIO_PIN2,                       /*!< GPIO pin used by bVbusChannel. It must  
                                         be equal to GPIO_Pin_x x= 0, 1, ...*/ 
  TEMP_SAMPLING_TIME2,                  /*!< Sampling time used for bVbusChannel AD
                                         conversion. It must be equal to  
                                         ADC_SampleTime_xCycles5 x= 1, 7, ...*/  
  TEMP_SW_FILTER_BW_FACTOR2,       /*!< Use this number to configure the   
                                         temperature first order software filter
                                         bandwidth                                                                                
                                         hLowPassFilterBW = TSNS_CalcBusReading 
                                         call rate [Hz]/ FilterBandwidth[Hz] */
  (uint16_t)(OV_TEMPERATURE_THRESHOLD_d2),       /*!< It represents the over voltage protection 
                                         intervention threshold. To be expressed 
                                         in u16Celsius through formula:
                                         hOverTempThreshold [u16Celsius] = 
                                         (V0[V]+dV/dT[V/°C]*(OverTempThreshold[°C] 
                                          - T0[°C]))* 65536 / MCU supply voltage */
  (uint16_t)(OV_TEMPERATURE_THRESHOLD_d2 - OV_TEMPERATURE_HYSTERESIS_d2), 
				  	                /*!< It represents the temperature 
                                         expressed in u16Celsius below which an 
                                         active over temperature fault is cleared
                                         hOverTempDeactThreshold[u16Celsius]=
                                         (V0[V]+dV/dT[V/°C]*(OverTempDeactThresh[°C] 
                                          - T0[°C]))* 65536 / MCU supply voltage*/
  (uint16_t)MCU_SUPPLY_VOLTAGE/dV_dT2,         /*!< It is equal to MCU supply voltage [V] /
                                          dV/dT [V/°C] and represents the NTC 
                                          sensitivity */
  (uint16_t)(V0_V2 *65536/ MCU_SUPPLY_VOLTAGE), /*!< It is equal to V0*65536/MCU supply 
                                          voltage where V0 is used to convert the 
                                          temperature into Volts 
                                          V[V]=V0+dV/dT[V/°C]*(T-T0)[°C]      */
  T0_C2,                                /*!< It is equal to T0 [°C], used to convert 
                                          the temperature into Volts 
                                          V[V]=V0+dV/dT[V/°C]*(T-T0)[°C]*/
};
/** 
  * @brief  Temperature sensor parameters Motor 2 - NTC  
  */
VirtualTParams_t VirtualTParamsM2=
{
  555,  /*!< Value returned by base class method TSNS_GetAvTemp_d */
  VIRTUAL_HEAT_SINK_TEMPERATURE_VALUE   /*!< Expected temperature in degrees 
                                      (value returned by base class 
                                      method TSNS_GetAvTemp_C) */                                                                                                           
};

/** 
  * @brief  FOCDrive class parameters Motor 2 - Base Class  
  */
FOCDriveParams_t FOCDriveParamsM2 =
{
  MAX_MODULE2,                           /*!< Circle limitation maximum allowed 
                                          module */
  MMITABLE2,                             /*!< Circle limitation table */
  START_INDEX2,                          /*!< Circle limitation table indexing 
                                           start */
  1                                       /*!< FOC object instance number, only used
                                           for multiple motor control. It must be 0 
                                           for motor 1 and 1 for motor2  */
};

/** 
  * @brief  SMF_PMSM class parameters Motor 2 - Derived Class
  */
SMF_PMSMParams_t SMF_PMSMParamsM2 = 
{
  (int16_t)FW_VOLTAGE_REF2,               /*!< Default flux weakening voltage reference,
                                       tenth of percentage points*/
  ID_DEMAG2,                     /*!< Demagnetization current in s16A: 
                                    Current(Amp) = [Current(s16A) * Vdd micro]/ 
                                    [65536 * Rshunt * Aop] */
  ((int32_t)NOMINAL_CURRENT2*(int32_t)NOMINAL_CURRENT2), /*!< Squared motor nominal current in (s16A)^2 
                                       where: 
                                     Current(Amp) = [Current(s16A) * Vdd micro]/ 
                                     [65536 * Rshunt * Aop] */
  VQD_SW_FILTER_BW_FACTOR2,       /*!< Use this parameter to configure the Vqd 
                                      first order software filter bandwidth. 
                                      hVqdLowPassFilterBW = FOC_CurrController 
                                      call rate [Hz]/ FilterBandwidth[Hz] in 
                                      case FULL_MISRA_COMPLIANCY is defined. 
                                      On the contrary, if FULL_MISRA_COMPLIANCY 
                                      is not defined, hVqdLowPassFilterBW is 
                                      equal to log with base two of previous 
                                     definition */ 
};

/** 
  * @brief  IMF_PMSM class parameters Motor 2 - Derived Class
  */
IMF_PMSMParams_t IMF_PMSMParamsM2 = 
{
  /* MTPA parameters */
  (int16_t)SEGDIV2,   /*!< Segment divisor */
  ANGC2,     /*!< Angular coefficients table */
  OFST2,      /*!< Offsets table */
  
  /* Flux Weakening parameters */
  (int16_t)FW_VOLTAGE_REF2,    /*!< Default flux weakening voltage reference,
                                  tenth of percentage points*/  
  ID_DEMAG2,                   /*!< Demagnetization current in s16A: 
                                    Current(Amp) = [Current(s16A) * Vdd micro]/ 
                                    [65536 * Rshunt * Aop] */
 (int32_t)NOMINAL_CURRENT2 * (int32_t)NOMINAL_CURRENT2, /*!< Squared motor nominal current in (s16A)^2 
                                      where: 
                                    Current(Amp) = [Current(s16A) * Vdd micro]/ 
                                    [65536 * Rshunt * Aop] */
  VQD_SW_FILTER_BW_FACTOR2       /*!< Use this parameter to configure the Vqd 
                                      first order software filter bandwidth. 
                                      hVqdLowPassFilterBW = FOC_CurrController 
                                      call rate [Hz]/ FilterBandwidth[Hz] in 
                                      case FULL_MISRA_COMPLIANCY is defined. 
                                      On the contrary, if FULL_MISRA_COMPLIANCY 
                                      is not defined, hVqdLowPassFilterBW is 
                                      equal to log with base two of previous 
                                      definition */
};
/** 
  * @brief  IMFF_PMSM class parameters Motor 2 - Derived Class
  */
IMFF_PMSMParams_t IMFF_PMSMParamsM2 =
{
  /* MTPA parameters */
  (int16_t)SEGDIV2,               /*!< Segment divisor */
  ANGC2,                          /*!< Angular coefficients table */
  OFST2,                          /*!< Offsets table */

  /* Flux Weakening parameters */
  (int16_t)FW_VOLTAGE_REF2,    /*!< Default flux weakening voltage reference,
                                  tenth of percentage points*/
  ID_DEMAG2,                   /*!< Demagnetization current in s16A: 
                                    Current(Amp) = [Current(s16A) * Vdd micro]/ 
                                    [65536 * Rshunt * Aop] */
 (int32_t)NOMINAL_CURRENT2 * (int32_t)NOMINAL_CURRENT2,       /*!< Squared motor nominal current in (s16A)^2 
                                      where: 
                                    Current(Amp) = [Current(s16A) * Vdd micro]/ 
                                    [65536 * Rshunt * Aop] */
  VQD_SW_FILTER_BW_FACTOR2,       /*!< Use this parameter to configure the Vqd 
                                      first order software filter bandwidth. 
                                      hVqdLowPassFilterBW = FOC_CurrController 
                                      call rate [Hz]/ FilterBandwidth[Hz] in 
                                      case FULL_MISRA_COMPLIANCY is defined. 
                                      On the contrary, if FULL_MISRA_COMPLIANCY 
                                      is not defined, hVqdLowPassFilterBW is 
                                      equal to log with base two of previous 
                                      definition */ 
  (int32_t)CONSTANT1_D2,         /*!< Feed forward constant for d axes */
  (int32_t)CONSTANT1_Q2,         /*!< Feed forward constant for q axes */
  (int32_t)CONSTANT2_QD2         /*!< Constant used by Feed-Forward algorithm*/
};

OL_FOCParams_t OpenLoopFOC_ParamsM2=
{
  OPEN_LOOP_VOLTAGE_d2
};


DigitalOutputParams_t R_BrakeParamsM2 =
{
  R_BRAKE_GPIO_PORT2,       /*!< GPIO output port. It must be equal
		                      	to GPIOx x= A, B, ...*/
  R_BRAKE_GPIO_PIN2,       /*!< GPIO output pin. It must be equal to
                                     	GPIO_Pin_x x= 0, 1, ...*/  
  DISSIPATIVE_BRAKE_POLARITY2        /*!< GPIO output polarity. It must be equal 
                                     	to DOutputActiveHigh or DOutputActiveLow */ 
};

DigitalOutputParams_t DOUT_OCPDisablingParamsM2 =
{
  OV_CURR_BYPASS_GPIO_PORT2,       /*!< GPIO output port. It must be equal
			to GPIOx x= A, B, ...*/
  OV_CURR_BYPASS_GPIO_PIN2,             /*!< GPIO output pin. It must be equal to
                                     	GPIO_Pin_x x= 0, 1, ...*/  
  OVERCURR_FEEDBACK_POLARITY2        /*!< GPIO output polarity. It must be equal 
                                     	to DOutputActiveHigh or DOutputActiveLow */ 
};
#endif

/****************************************************************************/
/*    MOTOR1  */

#ifdef SINGLEDRIVE
#define NBR_OF_MOTORS 1
#else
#define NBR_OF_MOTORS 2
#endif

/**
  * @brief  PI / PID Speed loop parameters Motor 1
  */
PIParams_t PISpeedParamsM1 =
{
  (int16_t)PID_SPEED_KP_DEFAULT,  /*!< Default Kp gain, used to initialize Kp gain
                                     software variable*/
  (int16_t)PID_SPEED_KI_DEFAULT,   /*!< Default Ki gain, used to initialize Ki gain
                                     software variable*/
  (uint16_t)SP_KPDIV,               /*!< Kp gain divisor, used in conjuction with 
                                     Kp gain allows obtaining fractional values. 
                                     If FULL_MISRA_C_COMPLIANCY is not defined 
                                     the divisor is implemented through 
                                     algebrical right shifts to speed up PI 
                                     execution. Only in this case this parameter
                                     specifies the number of right shifts to be 
                                     executed */
  (uint16_t)SP_KIDIV,               /*!< Ki gain divisor, used in conjuction with 
                                     Ki gain allows obtaining fractional values. 
                                     If FULL_MISRA_C_COMPLIANCY is not defined 
                                     the divisor is implemented through 
                                     algebrical right shifts to speed up PI 
                                     execution. Only in this case this parameter
                                     specifies the number of right shifts to be 
                                     executed */
  (int32_t)IQMAX * (int32_t)SP_KIDIV,/*!< Upper limit used to saturate the integral 
                                     term given by Ki / Ki divisor * integral of
                                     process variable error */ 
  -(int32_t)IQMAX * (int32_t)SP_KIDIV,/*!< Lower limit used to saturate the integral 
                                     term given by Ki / Ki divisor * integral of
                                     process variable error */    
  (int16_t)IQMAX,                 /*!< Upper limit used to saturate the PI output 
                                     */ 
  -(int16_t)IQMAX,                /*!< Lower limit used to saturate the PI output 
                                     */ 
};


/**
  * @brief  PI / PID Iq loop parameters Motor 1
  */
PIParams_t PIIqParamsM1 =
{
  (int16_t)PID_TORQUE_KP_DEFAULT, /*!< Default Kp gain, used to initialize Kp gain
                                     software variable*/
  (int16_t)PID_TORQUE_KI_DEFAULT, /*!< Default Ki gain, used to initialize Ki gain
                                     software variable*/
  (uint16_t)TF_KPDIV,               /*!< Kp gain divisor, used in conjuction with 
                                     Kp gain allows obtaining fractional values. 
                                     If FULL_MISRA_C_COMPLIANCY is not defined 
                                     the divisor is implemented through 
                                     algebrical right shifts to speed up PI 
                                     execution. Only in this case this parameter
                                     specifies the number of right shifts to be 
                                     executed */
  (uint16_t)TF_KIDIV,               /*!< Ki gain divisor, used in conjuction with 
                                     Ki gain allows obtaining fractional values. 
                                     If FULL_MISRA_C_COMPLIANCY is not defined 
                                     the divisor is implemented through 
                                     algebrical right shifts to speed up PI 
                                     execution. Only in this case this parameter
                                     specifies the number of right shifts to be 
                                     executed */
  (int32_t)S16_MAX * TF_KIDIV,     /*!< Upper limit used to saturate the integral 
                                     term given by Ki / Ki divisor * integral of
                                     process variable error */ 
  (int32_t)S16_MIN * TF_KIDIV,             /*!< Lower limit used to saturate the integral 
                                     term given by Ki / Ki divisor * integral of
                                     process variable error */    
  S16_MAX,                        /*!< Upper limit used to saturate the PI output 
                                     */ 
  -S16_MAX,                       /*!< Lower limit used to saturate the PI output 
                                     */ 
};


/**
  * @brief  PI / PID Id loop parameters Motor 1
  */
PIParams_t PIIdParamsM1 =
{
  (int16_t)PID_FLUX_KP_DEFAULT,    /*!< Default Kp gain, used to initialize Kp gain
                                    software variable*/
  (int16_t)PID_FLUX_KI_DEFAULT,    /*!< Default Ki gain, used to initialize Ki gain
                                     software variable*/
  (uint16_t)TF_KPDIV,              /*!< Kp gain divisor, used in conjuction with 
                                     Kp gain allows obtaining fractional values. 
                                     If FULL_MISRA_C_COMPLIANCY is not defined 
                                     the divisor is implemented through 
                                     algebrical right shifts to speed up PI 
                                     execution. Only in this case this parameter
                                     specifies the number of right shifts to be 
                                     executed */
  (uint16_t)TF_KIDIV,              /*!< Ki gain divisor, used in conjuction with 
                                     Ki gain allows obtaining fractional values. 
                                     If FULL_MISRA_C_COMPLIANCY is not defined 
                                     the divisor is implemented through 
                                     algebrical right shifts to speed up PI 
                                     execution. Only in this case this parameter
                                     specifies the number of right shifts to be 
                                     executed */
  (int32_t)S16_MAX * TF_KIDIV,             /*!< Upper limit used to saturate the integral 
                                     term given by Ki / Ki divisor * integral of
                                     process variable error */ 
  (int32_t)S16_MIN * TF_KIDIV,             /*!< Lower limit used to saturate the integral 
                                     term given by Ki / Ki divisor * integral of
                                     process variable error */    
  S16_MAX,                       /*!< Upper limit used to saturate the PI output 
                                     */ 
  -S16_MAX,                      /*!< Lower limit used to saturate the PI output 
                                     */ 
};

/**
  * @brief  PI Flux Weakening control parameters Motor 1
  */
PIParams_t PIFluxWeakeningParamsM1 =
{
  (int16_t)FW_KP_GAIN,             /*!< Default Kp gain, used to initialize Kp gain
                                     software variable*/
  (int16_t)FW_KI_GAIN,             /*!< Default Ki gain, used to initialize Ki gain
                                     software variable*/
  (uint16_t)FW_KPDIV,              /*!< Kp gain divisor, used in conjuction with 
                                     Kp gain allows obtaining fractional values. 
                                     If FULL_MISRA_C_COMPLIANCY is not defined 
                                     the divisor is implemented through 
                                     algebrical right shifts to speed up PI 
                                     execution. Only in this case this parameter
                                     specifies the number of right shifts to be 
                                     executed */
  (uint16_t)FW_KIDIV,               /*!< Ki gain divisor, used in conjuction with 
                                     Ki gain allows obtaining fractional values. 
                                     If FULL_MISRA_C_COMPLIANCY is not defined 
                                     the divisor is implemented through 
                                     algebrical right shifts to speed up PI 
                                     execution. Only in this case this parameter
                                     specifies the number of right shifts to be 
                                     executed */
  0,                              /*!< Upper limit used to saturate the integral 
                                     term given by Ki / Ki divisor * integral of
                                     process variable error */ 
  (int32_t)(-NOMINAL_CURRENT) * (int32_t)FW_KIDIV, /*!< Lower limit used to saturate the integral 
                                     term given by Ki / Ki divisor * integral of
                                     process variable error */    
  0,                            /*!< Upper limit used to saturate the PI output 
                                     */ 
  -S16_MAX,                     /*!< Lower limit used to saturate the PI output 
                                     */ 
};



/** 
  * @brief  SpeednTorque Controller parameters Motor 1 
  */
SpeednTorqCtrlParams_t SpeednTorqCtrlParamsM1 =
{
  MEDIUM_FREQUENCY_TASK_RATE, 	         /*!< Frequency on which the user updates 
                                             the torque reference calling 
                                             STC_CalcTorqueReference method 
                                             expressed in Hz */
  (uint16_t)(MAX_APPLICATION_SPEED/6),  /*!< Application maximum positive value
                                             of rotor speed. It's expressed in 
                                             tenth of mechanical Hertz.*/
  (uint16_t)(MIN_APPLICATION_SPEED/6),      /*!< Application minimum positive value
                                             of rotor speed. It's expressed in
                                             tenth of mechanical Hertz.*/
  (int16_t)(-MIN_APPLICATION_SPEED/6),    /*!< Application maximum negative value
                                             of rotor speed. It's expressed in 
                                             tenth of mechanical Hertz.*/
  (int16_t)(-MAX_APPLICATION_SPEED/6),/*!< Application minimum negative value
                                             of rotor speed. It's expressed in
                                             tenth of mechanical Hertz.*/
  (int16_t)NOMINAL_CURRENT,		     /*!< Maximum positive value of motor 
                                             torque. This value represents 
                                             actually the maximum Iq current 
                                             expressed in digit.*/
  -(int16_t)NOMINAL_CURRENT,                 /*!< Maximum negative value of motor 
                                             torque. This value represents 
                                             actually the maximum Iq current 
                                             expressed in digit.*/
  DEFAULT_CONTROL_MODE,                     /*!< Default STC modality.*/
  (int16_t)(DEFAULT_TARGET_SPEED_RPM/6),    /*!< Default mechanical rotor speed 
                                             reference expressed in tenths of 
                                             HZ.*/
  (int16_t)DEFAULT_TORQUE_COMPONENT,        /*!< Default motor torque reference. 
                                             This value represents actually the
                                             Iq current reference expressed in
                                             digit.*/
};


/** 
  * @brief  Current sensor parameters Motor 1 - base class
  */
PWMnCurrFdbkParams_t PWMnCurrFdbkParamsM1 = 
{
  PWM_PERIOD_CYCLES,                 /*!< It contains the PWM period expressed
                                            in timer clock cycles unit: 
                                            hPWMPeriod = Timer Fclk / Fpwm    */
};

/** 
  * @brief  Current sensor parameters Single Drive - three shunt, STM32F103 LOW/MEDIUM DENSITY
  */
R3_LM1Params_t R3_LM1ParamsSD =
{
  ADC_CLOCK_DIVIDER,                         /*!<  APB2 clock prescaling factor for 
                                          ADC peripheral. It must be RCC_PCLK2_DivX
                                          x = 2, 4, 6, 8 */    
/* Current reading A/D Conversions initialization -----------------------------*/ 
  PHASE_U_CURR_CHANNEL,                  /*!< ADC channel used for conversion of 
                                           current Ia. It must be equal to  
                                           ADC_Channel_x x= 0, ..., 15*/
  PHASE_U_GPIO_PORT,                  /*!< GPIO port used by hIaChannel. It must 
                                           be equal to GPIOx x= A, B, ...*/
  PHASE_U_GPIO_PIN,                      /*!< GPIO pin used by hIaChannel. It must be 
                                          equal to GPIO_Pin_x x= 0, 1, ...*/ 
  SAMPLING_TIME_SEL,               /*!< Sampling time used to convert hIaChannel. 
                                          It must be equal to ADC_SampleTime_xCycles5 
                                          x= 1, 7, ...*/ 
  PHASE_V_CURR_CHANNEL,                  /*!< ADC channel used for conversion of 
                                           current Ib. It must be equal to 
                                           ADC_Channel_x x= 0, ..., 15*/  
  PHASE_V_GPIO_PORT,                /*!< GPIO port used by hIbChannel. It must 
                                           be equal to GPIOx x= A, B, ...*/
  PHASE_V_GPIO_PIN,                      /*!< GPIO pin used by hIaChannel. It must be 
                                          equal to GPIO_Pin_x x= 0, 1, ...*/
  SAMPLING_TIME_SEL,                /*!< Sampling time used to convert hIbChannel. 
                                          It must be equal to ADC_SampleTime_xCycles5 
                                          x= 1, 7, ...*/
  PHASE_W_CURR_CHANNEL,                  /*!< ADC channel used for conversion of 
                                           current Ia. It must be equal to  
                                           ADC_Channel_x x= 0, ..., 15*/
  PHASE_W_GPIO_PORT,                /*!< GPIO port used by hIaChannel. It must 
                                           be equal to GPIOx x= A, B, ...*/
  PHASE_W_GPIO_PIN,                      /*!< GPIO pin used by hIaChannel. It must be 
                                          equal to GPIO_Pin_x x= 0, 1, ...*/ 
  SAMPLING_TIME_SEL,            /*!< Sampling time used to convert hIaChannel. 
                                          It must be equal to ADC_SampleTime_xCycles5 
                                          x= 1, 7, ...*/ 
  
/* PWM generation parameters --------------------------------------------------*/   
  DEAD_TIME_COUNTS,
                                       /*!< Dead time in number of TIM clock
                                         cycles. If CHxN are enabled, it must
                                         contain the dead time to be generated
                                         by the microcontroller, otherwise it 
                                         expresses the maximum dead time 
                                         generated by driving network */
  REP_COUNTER,                           /*!< It expresses the number of PWM 
                                         periods to be elapsed before compare 
                                         registers are updated again. In 
                                         particular: 
                                         RepetitionCounter= (2* #PWM periods)-1*/
  TW_AFTER,                            /*!< It is the sum of dead time plus max 
                                         value between rise time and noise time
                                         express in number of TIM clocks.*/
  TW_BEFORE,                           /*!< It is the sampling time express in
                                          number of TIM clocks.*/ 
  PWM_TIMER_SELECTION,                 /*!< It contains the pointer to the timer 
                                          used for PWM generation. */
/* PWM Driving signals initialization ----------------------------------------*/  

  PWM_TIMER_REMAPPING,                        /*!< Used only for instance #1, it 
                                           remaps TIM1 outputs. It must equal to 
                                           GPIO_PartialRemap_TIM1 or 
                                           GPIO_FullRemap_TIM1 or
                                           GPIO_NoRemap_TIM1 */
  PHASE_UH_POLARITY,   	           /*!< Channel 1 (high side) output polarity, 
                                           it must be TIM_OCPolarity_High or 
                                           TIM_OCPolarity_Low */
  PHASE_UH_GPIO_PORT,                                 /*!< Channel 1 (high side) GPIO output 
                                         port (if used, after re-mapping). 
                                         It must be GPIOx x= A, B, ...*/
  PHASE_UH_GPIO_PIN,                       /*!< Channel 1 (high side) GPIO output pin 
                                          (if used, after re-mapping). It must be 
                                          GPIO_Pin_x x= 0, 1, ...*/  
  IDLE_UH_POLARITY,              /*!< Channel 1 (high side) state (low or high)
                                            when TIM peripheral is in Idle state.
                                            It must be TIM_OCIdleState_Set or
                                            TIM_OCIdleState_Reset*/
                                            
  PHASE_VH_POLARITY,               /*!< Channel 2 (high side) output polarity, 
                                           it must be TIM_OCPolarity_High or 
                                           TIM_OCPolarity_Low */ 
  PHASE_VH_GPIO_PORT,                               /*!< Channel 2 (high side) GPIO output 
                                           port (if used, after re-mapping). 
                                           It must be GPIOx x= A, B, ...*/
  PHASE_VH_GPIO_PIN,                       /*!< Channel 2 (high side) GPIO output pin 
                                          (if used, after re-mapping). It must be 
                                          GPIO_Pin_x x= 0, 1, ...*/
  IDLE_VH_POLARITY,              /*!< Channel 2 (high side) state (low or high)
                                            when TIM peripheral is in Idle state.
                                            It must be TIM_OCIdleState_Set or
                                            TIM_OCIdleState_Reset*/    
 
  PHASE_WH_POLARITY,            	 /*!< Channel 3 (high side) output polarity, 
                                           it must be TIM_OCPolarity_High or 
                                           TIM_OCPolarity_Low */  
  PHASE_WH_GPIO_PORT,                               /*!< Channel 3 (high side) GPIO output 
                                           port (if used, after re-mapping). 
                                           It must be GPIOx x= A, B, ...*/
  PHASE_WH_GPIO_PIN,                        /*!< Channel 3 (high side) GPIO output pin 
                                          (if used, after re-mapping). It must be 
                                          GPIO_Pin_x x= 0, 1, ...*/  
  IDLE_WH_POLARITY,              /*!< Channel 3 (high side) state (low or high)
                                            when TIM peripheral is in Idle state.
                                            It must be TIM_OCIdleState_Set or
                                            TIM_OCIdleState_Reset*/  
  
  (FunctionalState)LOW_SIDE_SIGNALS_ENABLING,  /*!< It enable/disable the PWM low side  
                                          driving signals. It must be either 
                                          equal to ENABLE or DISABLE */ 
  
  PHASE_UL_POLARITY,               /*!< Channel 1N (low side) output polarity, 
                                           it must be TIM_OCNPolarity_High or 
                                           TIM_OCNPolarity_Low */
  PHASE_UL_GPIO_PORT,                                 /*!< Channel 1N (low side) GPIO output 
                                           port (if used, after re-mapping). 
                                           It must be GPIOx x= A, B, ...*/
  PHASE_UL_GPIO_PIN,                       /*!< Channel 1N (low side) GPIO output pin 
                                          (if used, after re-mapping). It must be 
                                          GPIO_Pin_x x= 0, 1, ...*/ 
  IDLE_UL_POLARITY,              /*!< Channel 1N (low side) state (low or high)
                                            when TIM peripheral is in Idle state.
                                            It must be TIM_OCNIdleState_Set or
                                            TIM_OCNIdleState_Reset*/ 

  
  PHASE_VL_POLARITY,                 /*!< Channel 2N (low side) output polarity, 
                                           it must be TIM_OCNPolarity_High or 
                                           TIM_OCNPolarity_Low */
  PHASE_VL_GPIO_PORT,                                 /*!< Channel 2N (low side) GPIO output 
                                           port (if used, after re-mapping). 
                                           It must be GPIOx x= A, B, ...*/
  PHASE_VL_GPIO_PIN,                     /*!< Channel 2N (low side) GPIO output pin 
                                          (if used, after re-mapping). It must be 
                                          GPIO_Pin_x x= 0, 1, ...*/ 
  IDLE_VL_POLARITY,              /*!< Channel 2N (low side) state (low or high)
                                            when TIM peripheral is in Idle state.
                                            It must be TIM_OCNIdleState_Set or
                                            TIM_OCNIdleState_Reset*/ 
  
  PHASE_WL_POLARITY,             /*!< Channel 3N (low side) output polarity, 
                                           it must be TIM_OCNPolarity_High or 
                                           TIM_OCNPolarity_Low */
  PHASE_WL_GPIO_PORT,                               /*!< Channel 3N (low side)  GPIO output 
                                           port (if used, after re-mapping). 
                                           It must be GPIOx x= A, B, ...*/
  PHASE_WL_GPIO_PIN,                    /*!< Channel 3N (low side)  GPIO output pin 
                                          (if used, after re-mapping). It must be 
                                          GPIO_Pin_x x= 0, 1, ...*/   
  IDLE_WL_POLARITY,              /*!< Channel 3N (low side) state (low or high)
                                            when TIM peripheral is in Idle state.
                                            It must be TIM_OCNIdleState_Set or
                                            TIM_OCNIdleState_Reset*/ 
/* PWM Driving signals initialization ----------------------------------------*/  
 (FunctionalState)SW_OV_CURRENT_PROT_ENABLING, /*!< It enable/disable the management of 
                                            an emergency input instantaneously 
                                            stopping PWM generation. It must be 
                                            either equal to ENABLE or DISABLE */  
  OVERCURR_FEEDBACK_POLARITY,               /*!< Emergency Stop (BKIN) input polarity, 
                                           it must be TIM_BreakPolarity_Low or 
                                           TIM_BreakPolarity_High */
  EMERGENCY_STOP_GPIO_PORT,             /*!< Emergency Stop (BKIN) GPIO input 
                                           port (if used, after re-mapping). 
                                           It must be GPIOx x= A, B, ...*/
  EMERGENCY_STOP_GPIO_PIN,              /*!< Emergency Stop (BKIN) GPIO input pin 
                                         (if used, after re-mapping). It must be 
                                          GPIO_Pin_x x= 0, 1, ...*/     
};

/** 
  * @brief  Current sensor parameters Single Drive - one shunt, STM32F103 LOW/MEDIUM DENSITY
  */
R1_LM1Params_t R1_LM1ParamsSD =
{  

  ADC_CLOCK_DIVIDER,                 /*!<  APB2 clock prescaling factor for 
                                          ADC peripheral. It must be RCC_PCLK2_DivX
                                          x = 2, 4, 6, 8 */
  MC_IRQ_PWMNCURRFDBK_1,             /*!< MC IRQ number used for TIM1 Update event 
                                       and for DMA TC event.*/										  
/* Current reading A/D Conversions initialization -----------------------------*/ 

  PHASE_CURRENTS_CHANNEL,                  /*!< ADC channel used for conversion of 
                                           current Ib. It must be equal to 
                                           ADC_Channel_x x= 0, ..., 15*/  
  PHASE_CURRENTS_GPIO_PORT,                /*!< GPIO port used by hIbChannel. It must 
                                           be equal to GPIOx x= A, B, ...*/
  PHASE_CURRENTS_GPIO_PIN,                      /*!< GPIO pin used by hIaChannel. It must be 
                                          equal to GPIO_Pin_x x= 0, 1, ...*/
  SAMPLING_TIME_SEL,                /*!< Sampling time used to convert hIbChannel. 
                                          It must be equal to ADC_SampleTime_xCycles5 
                                          x= 1, 7, ...*/
/* PWM generation parameters --------------------------------------------------*/   
  DEAD_TIME_COUNTS,                 /*!< Dead time in number of TIM clock
                                         cycles. If CHxN are enabled, it must
                                         contain the dead time to be generated
                                         by the microcontroller, otherwise it 
                                         expresses the maximum dead time 
                                         generated by driving network */
  REP_COUNTER,                      /*!< It expresses the number of PWM 
                                       periods to be elapsed before compare 
                                       registers are updated again. In 
                                       particular: 
                                       RepetitionCounter= (2* PWM periods) -1*/   
  TAFTER,                         /*!< It is the sum of dead time plus rise time
                                       express in number of TIM clocks.*/
  TBEFORE,                            /*!< */ 
  TMIN,                            /*!< It is the sum of dead time plus rise time
                                       plus sampling time express in numbers of
                                       TIM clocks.*/
  HTMIN,                          /*!< It is the half of hTMin value.*/
  TSAMPLE,                        /*!< It is the sampling time express in 
                                       numbers of TIM clocks.*/
  MAX_TRTS,                       /*!< It is the maximum between twice of rise
                                       time express in number of TIM clocks and
                                       twice of sampling time express in numbers
                                       of TIM clocks.*/
  
/* PWM Driving signals initialization ----------------------------------------*/  

  R1_PWM_AUX_TIM,                 /*!< Auxiliary timer used for single shunt ADC
                                       triggering. It should be TIM3 or TIM4.*/
  PWM_TIMER_REMAPPING,            /*!< Used only for instance #1, it 
                                       remaps TIM1 outputs. It must equal to 
                                       GPIO_PartialRemap_TIM1 or 
                                       GPIO_FullRemap_TIM1 or
                                       GPIO_NoRemap_TIM1 */
  PHASE_UH_POLARITY,   	           /*!< Channel 1 (high side) output polarity, 
                                           it must be TIM_OCPolarity_High or 
                                           TIM_OCPolarity_Low */
  PHASE_UH_GPIO_PORT,                                 /*!< Channel 1 (high side) GPIO output 
                                         port (if used, after re-mapping). 
                                         It must be GPIOx x= A, B, ...*/
  PHASE_UH_GPIO_PIN,                       /*!< Channel 1 (high side) GPIO output pin 
                                          (if used, after re-mapping). It must be 
                                          GPIO_Pin_x x= 0, 1, ...*/  
  IDLE_UH_POLARITY,              /*!< Channel 1 (high side) state (low or high)
                                            when TIM peripheral is in Idle state.
                                            It must be TIM_OCIdleState_Set or
                                            TIM_OCIdleState_Reset*/
                                            
  PHASE_VH_POLARITY,               /*!< Channel 2 (high side) output polarity, 
                                           it must be TIM_OCPolarity_High or 
                                           TIM_OCPolarity_Low */ 
  PHASE_VH_GPIO_PORT,                               /*!< Channel 2 (high side) GPIO output 
                                           port (if used, after re-mapping). 
                                           It must be GPIOx x= A, B, ...*/
  PHASE_VH_GPIO_PIN,                       /*!< Channel 2 (high side) GPIO output pin 
                                          (if used, after re-mapping). It must be 
                                          GPIO_Pin_x x= 0, 1, ...*/
  IDLE_VH_POLARITY,              /*!< Channel 2 (high side) state (low or high)
                                            when TIM peripheral is in Idle state.
                                            It must be TIM_OCIdleState_Set or
                                            TIM_OCIdleState_Reset*/    
 
  PHASE_WH_POLARITY,            	 /*!< Channel 3 (high side) output polarity, 
                                           it must be TIM_OCPolarity_High or 
                                           TIM_OCPolarity_Low */  
  PHASE_WH_GPIO_PORT,                               /*!< Channel 3 (high side) GPIO output 
                                           port (if used, after re-mapping). 
                                           It must be GPIOx x= A, B, ...*/
  PHASE_WH_GPIO_PIN,                        /*!< Channel 3 (high side) GPIO output pin 
                                          (if used, after re-mapping). It must be 
                                          GPIO_Pin_x x= 0, 1, ...*/  
  IDLE_WH_POLARITY,              /*!< Channel 3 (high side) state (low or high)
                                            when TIM peripheral is in Idle state.
                                            It must be TIM_OCIdleState_Set or
                                            TIM_OCIdleState_Reset*/  
  
  (FunctionalState)LOW_SIDE_SIGNALS_ENABLING,  /*!< It enable/disable the PWM low side  
                                          driving signals. It must be either 
                                          equal to ENABLE or DISABLE */ 
  
  PHASE_UL_POLARITY,               /*!< Channel 1N (low side) output polarity, 
                                           it must be TIM_OCNPolarity_High or 
                                           TIM_OCNPolarity_Low */
  PHASE_UL_GPIO_PORT,                                 /*!< Channel 1N (low side) GPIO output 
                                           port (if used, after re-mapping). 
                                           It must be GPIOx x= A, B, ...*/
  PHASE_UL_GPIO_PIN,                       /*!< Channel 1N (low side) GPIO output pin 
                                          (if used, after re-mapping). It must be 
                                          GPIO_Pin_x x= 0, 1, ...*/ 
  IDLE_UL_POLARITY,              /*!< Channel 1N (low side) state (low or high)
                                            when TIM peripheral is in Idle state.
                                            It must be TIM_OCNIdleState_Set or
                                            TIM_OCNIdleState_Reset*/ 

  
  PHASE_VL_POLARITY,                 /*!< Channel 2N (low side) output polarity, 
                                           it must be TIM_OCNPolarity_High or 
                                           TIM_OCNPolarity_Low */
  PHASE_VL_GPIO_PORT,                                 /*!< Channel 2N (low side) GPIO output 
                                           port (if used, after re-mapping). 
                                           It must be GPIOx x= A, B, ...*/
  PHASE_VL_GPIO_PIN,                     /*!< Channel 2N (low side) GPIO output pin 
                                          (if used, after re-mapping). It must be 
                                          GPIO_Pin_x x= 0, 1, ...*/ 
  IDLE_VL_POLARITY,              /*!< Channel 2N (low side) state (low or high)
                                            when TIM peripheral is in Idle state.
                                            It must be TIM_OCNIdleState_Set or
                                            TIM_OCNIdleState_Reset*/ 
  
  PHASE_WL_POLARITY,             /*!< Channel 3N (low side) output polarity, 
                                           it must be TIM_OCNPolarity_High or 
                                           TIM_OCNPolarity_Low */
  PHASE_WL_GPIO_PORT,                               /*!< Channel 3N (low side)  GPIO output 
                                           port (if used, after re-mapping). 
                                           It must be GPIOx x= A, B, ...*/
  PHASE_WL_GPIO_PIN,                    /*!< Channel 3N (low side)  GPIO output pin 
                                          (if used, after re-mapping). It must be 
                                          GPIO_Pin_x x= 0, 1, ...*/   
  IDLE_WL_POLARITY,              /*!< Channel 3N (low side) state (low or high)
                                            when TIM peripheral is in Idle state.
                                            It must be TIM_OCNIdleState_Set or
                                            TIM_OCNIdleState_Reset*/ 
/* PWM Driving signals initialization ----------------------------------------*/  
 (FunctionalState)SW_OV_CURRENT_PROT_ENABLING, /*!< It enable/disable the management of 
                                            an emergency input instantaneously 
                                            stopping PWM generation. It must be 
                                            either equal to ENABLE or DISABLE */  
  OVERCURR_FEEDBACK_POLARITY,               /*!< Emergency Stop (BKIN) input polarity, 
                                           it must be TIM_BreakPolarity_Low or 
                                           TIM_BreakPolarity_High */
  EMERGENCY_STOP_GPIO_PORT,             /*!< Emergency Stop (BKIN) GPIO input 
                                           port (if used, after re-mapping). 
                                           It must be GPIOx x= A, B, ...*/
  EMERGENCY_STOP_GPIO_PIN,              /*!< Emergency Stop (BKIN) GPIO input pin 
                                         (if used, after re-mapping). It must be 
                                          GPIO_Pin_x x= 0, 1, ...*/     
  
};

/** 
  * @brief  Current sensor parameters Single Drive - one shunt, STM32F100
  */
R1_VL1Params_t R1_VL1ParamsSD = 
{  
  ADC_CLOCK_DIVIDER,                 /*!<  APB2 clock prescaling factor for 
                                          ADC peripheral. It must be RCC_PCLK2_DivX
                                          x = 2, 4, 6, 8 */
  MC_IRQ_PWMNCURRFDBK_1,             /*!< MC IRQ number used for TIM1 Update event 
                                       and for DMA TC event.*/										  
/* Current reading A/D Conversions initialization -----------------------------*/ 

  PHASE_CURRENTS_CHANNEL,                  /*!< ADC channel used for conversion of 
                                           current Ib. It must be equal to 
                                           ADC_Channel_x x= 0, ..., 15*/  
  PHASE_CURRENTS_GPIO_PORT,                /*!< GPIO port used by hIbChannel. It must 
                                           be equal to GPIOx x= A, B, ...*/
  PHASE_CURRENTS_GPIO_PIN,                      /*!< GPIO pin used by hIaChannel. It must be 
                                          equal to GPIO_Pin_x x= 0, 1, ...*/
  SAMPLING_TIME_SEL,                /*!< Sampling time used to convert hIbChannel. 
                                          It must be equal to ADC_SampleTime_xCycles5 
                                          x= 1, 7, ...*/
/* PWM generation parameters --------------------------------------------------*/   
  DEAD_TIME_COUNTS,                  /*!< Dead time in number of TIM clock
                                            cycles. If CHxN are enabled, it must
                                            contain the dead time to be generated
                                            by the microcontroller, otherwise it 
                                            expresses the maximum dead time 
                                            generated by driving network 
                                            It must be equal to (u16)((DEADTIME_NS * 24uL)/1000uL)*/
  REP_COUNTER,              /*!< It expresses the number of PWM 
                                           periods to be elapsed before compare 
                                           registers are updated again. In 
                                           particular: 
                                           RepetitionCounter= (2* #PWM periods) -1
                                         */   
  TAFTER,     /*!< It must be equal to ((u16)(((DEADTIME_NS+((u16)(TRISE_NS)))*24ul)/1000ul))*/
  TBEFORE,    /*!< It must be equal to (((u16)(((((u16)(SAMPLING_TIME_NS)))*24ul)/1000ul))+1)*/
  TMIN,       /*!< It must be equal to (((u16)(((DEADTIME_NS+((u16)(TRISE_NS))+((u16)(SAMPLING_TIME_NS)))*24uL)/1000ul))+1)*/
  HTMIN,      /*!< It must be equal to (u16)(TMIN >> 1)*/
  TSAMPLE,    /*!< It must be equal to (u16)(((u16)(SAMPLING_TIME_NS) * 24uL)/1000uL)*/
  MAX_TRTS,    /*!< It must be equal to 2*(u16)((((u16)(TRISE_NS)) * 24uL)/1000uL) if TRISE_NS > SAMPLING_TIME_NS
                             to 2*hTSample otherwise */
  
/* PWM Driving signals initialization ----------------------------------------*/  

  R1_PWM_AUX_TIM,                 /*!< Auxiliary timer used for single shunt ADC
                                       triggering. It should be TIM3 or TIM4.*/   
  PWM_TIMER_REMAPPING,            /*!< Used only for instance #1, it 
                                       remaps TIM1 outputs. It must equal to 
                                       GPIO_PartialRemap_TIM1 or 
                                       GPIO_FullRemap_TIM1 or
                                       GPIO_NoRemap_TIM1 */
  PHASE_UH_POLARITY,   	           /*!< Channel 1 (high side) output polarity, 
                                        it must be TIM_OCPolarity_High or 
                                        TIM_OCPolarity_Low */
  PHASE_UH_GPIO_PORT,              /*!< Channel 1 (high side) GPIO output 
                                        port (if used, after re-mapping). 
                                        It must be GPIOx x= A, B, ...*/
  PHASE_UH_GPIO_PIN,               /*!< Channel 1 (high side) GPIO output pin 
                                        (if used, after re-mapping). It must be 
                                        GPIO_Pin_x x= 0, 1, ...*/  
  IDLE_UH_POLARITY,                /*!< Channel 1 (high side) state (low or high)
                                        when TIM peripheral is in Idle state.
                                        It must be TIM_OCIdleState_Set or
                                        TIM_OCIdleState_Reset*/                    

  PHASE_VH_POLARITY,               /*!< Channel 2 (high side) output polarity, 
                                        it must be TIM_OCPolarity_High or 
                                        TIM_OCPolarity_Low */ 
  PHASE_VH_GPIO_PORT,              /*!< Channel 2 (high side) GPIO output 
                                        port (if used, after re-mapping). 
                                        It must be GPIOx x= A, B, ...*/
  PHASE_VH_GPIO_PIN,               /*!< Channel 2 (high side) GPIO output pin 
                                        (if used, after re-mapping). It must be 
                                        GPIO_Pin_x x= 0, 1, ...*/
  IDLE_VH_POLARITY,                /*!< Channel 2 (high side) state (low or high)
                                        when TIM peripheral is in Idle state.
                                        It must be TIM_OCIdleState_Set or
                                        TIM_OCIdleState_Reset*/    
  PHASE_WH_POLARITY,               /*!< Channel 3 (high side) output polarity, 
                                         it must be TIM_OCPolarity_High or 
                                         TIM_OCPolarity_Low */  
  PHASE_WH_GPIO_PORT,              /*!< Channel 3 (high side) GPIO output 
                                        port (if used, after re-mapping). 
                                        It must be GPIOx x= A, B, ...*/
  PHASE_WH_GPIO_PIN,               /*!< Channel 3 (high side) GPIO output pin 
                                        (if used, after re-mapping). It must be 
                                        GPIO_Pin_x x= 0, 1, ...*/  
  IDLE_WH_POLARITY,                /*!< Channel 3 (high side) state (low or high)
                                        when TIM peripheral is in Idle state.
                                        It must be TIM_OCIdleState_Set or
                                        TIM_OCIdleState_Reset*/  
  (FunctionalState)LOW_SIDE_SIGNALS_ENABLING,  
                                   /*!< It enable/disable the PWM low side  
                                        driving signals. It must be either 
                                        equal to ENABLE or DISABLE */ 
  PHASE_UL_POLARITY,               /*!< Channel 1N (low side) output polarity, 
                                         it must be TIM_OCNPolarity_High or 
                                         TIM_OCNPolarity_Low */
  PHASE_UL_GPIO_PORT,              /*!< Channel 1N (low side) GPIO output 
                                        port (if used, after re-mapping). 
                                        It must be GPIOx x= A, B, ...*/
  PHASE_UL_GPIO_PIN,               /*!< Channel 1N (low side) GPIO output pin 
                                        (if used, after re-mapping). It must be 
                                        GPIO_Pin_x x= 0, 1, ...*/ 
  IDLE_UL_POLARITY,                 /*!< Channel 1N (low side) state (low or high)
                                         when TIM peripheral is in Idle state.
                                         It must be TIM_OCNIdleState_Set or
                                         TIM_OCNIdleState_Reset*/ 

  
  PHASE_VL_POLARITY,                /*!< Channel 2N (low side) output polarity, 
                                         it must be TIM_OCNPolarity_High or 
                                         TIM_OCNPolarity_Low */
  PHASE_VL_GPIO_PORT,               /*!< Channel 2N (low side) GPIO output 
                                         port (if used, after re-mapping). 
                                         It must be GPIOx x= A, B, ...*/
  PHASE_VL_GPIO_PIN,                /*!< Channel 2N (low side) GPIO output pin 
                                         (if used, after re-mapping). It must be 
                                          GPIO_Pin_x x= 0, 1, ...*/ 
  IDLE_VL_POLARITY,                 /*!< Channel 2N (low side) state (low or high)
                                          when TIM peripheral is in Idle state.
                                          It must be TIM_OCNIdleState_Set or
                                          TIM_OCNIdleState_Reset*/ 
  
  PHASE_WL_POLARITY,                /*!< Channel 3N (low side) output polarity, 
                                         it must be TIM_OCNPolarity_High or 
                                         TIM_OCNPolarity_Low */
  PHASE_WL_GPIO_PORT,               /*!< Channel 3N (low side)  GPIO output 
                                         port (if used, after re-mapping). 
                                         It must be GPIOx x= A, B, ...*/
  PHASE_WL_GPIO_PIN,                /*!< Channel 3N (low side)  GPIO output pin 
                                          (if used, after re-mapping). It must be 
                                          GPIO_Pin_x x= 0, 1, ...*/   
  IDLE_WL_POLARITY,                 /*!< Channel 3N (low side) state (low or high)
                                         when TIM peripheral is in Idle state.
                                         It must be TIM_OCNIdleState_Set or
                                         TIM_OCNIdleState_Reset*/ 
/* PWM Driving signals initialization ----------------------------------------*/  
 (FunctionalState)SW_OV_CURRENT_PROT_ENABLING, /*!< It enable/disable the management of 
                                         an emergency input instantaneously 
                                         stopping PWM generation. It must be 
                                         either equal to ENABLE or DISABLE */  
  OVERCURR_FEEDBACK_POLARITY,         /*!< Emergency Stop (BKIN) input polarity, 
                                           it must be TIM_BreakPolarity_Low or 
                                           TIM_BreakPolarity_High */
  EMERGENCY_STOP_GPIO_PORT,           /*!< Emergency Stop (BKIN) GPIO input 
                                           port (if used, after re-mapping). 
                                           It must be GPIOx x= A, B, ...*/
  EMERGENCY_STOP_GPIO_PIN,            /*!< Emergency Stop (BKIN) GPIO input pin 
                                           (if used, after re-mapping). It must be 
                                           GPIO_Pin_x x= 0, 1, ...*/     
};

/** 
  * @brief  Current sensor parameters Single Drive - ICS, STM32F103 LOW/MEDIUM DENSITY
  */
ICS_LM1Params_t ICS_LM1ParamsSD =
{
  ADC_CLOCK_DIVIDER,                         /*!<  APB2 clock prescaling factor for 
                                          ADC peripheral. It must be RCC_PCLK2_DivX
                                          x = 2, 4, 6, 8 */    
/* Current reading A/D Conversions initialization -----------------------------*/ 
  PHASE_U_CURR_CHANNEL,                  /*!< ADC channel used for conversion of 
                                           current Ia. It must be equal to  
                                           ADC_Channel_x x= 0, ..., 15*/
  PHASE_U_GPIO_PORT,                  /*!< GPIO port used by hIaChannel. It must 
                                           be equal to GPIOx x= A, B, ...*/
  PHASE_U_GPIO_PIN,                      /*!< GPIO pin used by hIaChannel. It must be 
                                          equal to GPIO_Pin_x x= 0, 1, ...*/ 
  SAMPLING_TIME_SEL,               /*!< Sampling time used to convert hIaChannel. 
                                          It must be equal to ADC_SampleTime_xCycles5 
                                          x= 1, 7, ...*/ 
  PHASE_V_CURR_CHANNEL,                  /*!< ADC channel used for conversion of 
                                           current Ib. It must be equal to 
                                           ADC_Channel_x x= 0, ..., 15*/  
  PHASE_V_GPIO_PORT,                /*!< GPIO port used by hIbChannel. It must 
                                           be equal to GPIOx x= A, B, ...*/
  PHASE_V_GPIO_PIN,                      /*!< GPIO pin used by hIaChannel. It must be 
                                          equal to GPIO_Pin_x x= 0, 1, ...*/
  SAMPLING_TIME_SEL,                /*!< Sampling time used to convert hIbChannel. 
                                          It must be equal to ADC_SampleTime_xCycles5 
                                          x= 1, 7, ...*/

/* PWM generation parameters --------------------------------------------------*/   
  DEAD_TIME_COUNTS,
                                       /*!< Dead time in number of TIM clock
                                         cycles. If CHxN are enabled, it must
                                         contain the dead time to be generated
                                         by the microcontroller, otherwise it 
                                         expresses the maximum dead time 
                                         generated by driving network */
  REP_COUNTER,                           /*!< It expresses the number of PWM 
                                         periods to be elapsed before compare 
                                         registers are updated again. In 
                                         particular: 
                                         RepetitionCounter= (2* #PWM periods)-1 */
  PWM_TIMER_SELECTION,                 /*!< It contains the pointer to the timer 
                                          used for PWM generation. */
/* PWM Driving signals initialization ----------------------------------------*/  

  PWM_TIMER_REMAPPING,                /*!< Used only for instance #1, it 
                                           remaps TIM1 outputs. It must equal to 
                                           GPIO_PartialRemap_TIM1 or 
                                           GPIO_FullRemap_TIM1 or
                                           GPIO_NoRemap_TIM1 */
  PHASE_UH_POLARITY,   	              /*!< Channel 1 (high side) output polarity, 
                                           it must be TIM_OCPolarity_High or 
                                           TIM_OCPolarity_Low */
  PHASE_UH_GPIO_PORT,                 /*!< Channel 1 (high side) GPIO output 
                                          port (if used, after re-mapping). 
                                          It must be GPIOx x= A, B, ...*/
  PHASE_UH_GPIO_PIN,                 /*!< Channel 1 (high side) GPIO output pin 
                                          (if used, after re-mapping). It must be 
                                           GPIO_Pin_x x= 0, 1, ...*/  
  IDLE_UH_POLARITY,                  /*!< Channel 1 (high side) state (low or high)
                                          when TIM peripheral is in Idle state.
                                          It must be TIM_OCIdleState_Set or
                                          TIM_OCIdleState_Reset*/
                                            
  PHASE_VH_POLARITY,                /*!< Channel 2 (high side) output polarity, 
                                         it must be TIM_OCPolarity_High or 
                                         TIM_OCPolarity_Low */ 
  PHASE_VH_GPIO_PORT,                /*!< Channel 2 (high side) GPIO output 
                                          port (if used, after re-mapping). 
                                          It must be GPIOx x= A, B, ...*/
  PHASE_VH_GPIO_PIN,                 /*!< Channel 2 (high side) GPIO output pin 
                                          (if used, after re-mapping). It must be 
                                          GPIO_Pin_x x= 0, 1, ...*/
  IDLE_VH_POLARITY,                  /*!< Channel 2 (high side) state (low or high)
                                            when TIM peripheral is in Idle state.
                                            It must be TIM_OCIdleState_Set or
                                            TIM_OCIdleState_Reset*/    
 
  PHASE_WH_POLARITY,            	   /*!< Channel 3 (high side) output polarity, 
                                           it must be TIM_OCPolarity_High or 
                                           TIM_OCPolarity_Low */  
  PHASE_WH_GPIO_PORT,                  /*!< Channel 3 (high side) GPIO output 
                                           port (if used, after re-mapping). 
                                           It must be GPIOx x= A, B, ...*/
  PHASE_WH_GPIO_PIN,                   /*!< Channel 3 (high side) GPIO output pin 
                                          (if used, after re-mapping). It must be 
                                          GPIO_Pin_x x= 0, 1, ...*/  
  IDLE_WH_POLARITY,                    /*!< Channel 3 (high side) state (low or high)
                                            when TIM peripheral is in Idle state.
                                            It must be TIM_OCIdleState_Set or
                                            TIM_OCIdleState_Reset*/  
  
  (FunctionalState)LOW_SIDE_SIGNALS_ENABLING,  /*!< It enable/disable the PWM low side  
                                          driving signals. It must be either 
                                          equal to ENABLE or DISABLE */ 
  
  PHASE_UL_POLARITY,               /*!< Channel 1N (low side) output polarity, 
                                           it must be TIM_OCNPolarity_High or 
                                           TIM_OCNPolarity_Low */
  PHASE_UL_GPIO_PORT,                                 /*!< Channel 1N (low side) GPIO output 
                                           port (if used, after re-mapping). 
                                           It must be GPIOx x= A, B, ...*/
  PHASE_UL_GPIO_PIN,                       /*!< Channel 1N (low side) GPIO output pin 
                                          (if used, after re-mapping). It must be 
                                          GPIO_Pin_x x= 0, 1, ...*/ 
  IDLE_UL_POLARITY,              /*!< Channel 1N (low side) state (low or high)
                                            when TIM peripheral is in Idle state.
                                            It must be TIM_OCNIdleState_Set or
                                            TIM_OCNIdleState_Reset*/ 

  
  PHASE_VL_POLARITY,                  /*!< Channel 2N (low side) output polarity, 
                                           it must be TIM_OCNPolarity_High or 
                                           TIM_OCNPolarity_Low */
  PHASE_VL_GPIO_PORT,                 /*!< Channel 2N (low side) GPIO output 
                                           port (if used, after re-mapping). 
                                           It must be GPIOx x= A, B, ...*/
  PHASE_VL_GPIO_PIN,                  /*!< Channel 2N (low side) GPIO output pin 
                                           (if used, after re-mapping). It must be 
                                           GPIO_Pin_x x= 0, 1, ...*/ 
  IDLE_VL_POLARITY,                   /*!< Channel 2N (low side) state (low or high)
                                            when TIM peripheral is in Idle state.
                                            It must be TIM_OCNIdleState_Set or
                                            TIM_OCNIdleState_Reset*/ 
  
  PHASE_WL_POLARITY,                  /*!< Channel 3N (low side) output polarity, 
                                           it must be TIM_OCNPolarity_High or 
                                           TIM_OCNPolarity_Low */
  PHASE_WL_GPIO_PORT,                 /*!< Channel 3N (low side)  GPIO output 
                                           port (if used, after re-mapping). 
                                           It must be GPIOx x= A, B, ...*/
  PHASE_WL_GPIO_PIN,                  /*!< Channel 3N (low side)  GPIO output pin 
                                          (if used, after re-mapping). It must be 
                                          GPIO_Pin_x x= 0, 1, ...*/   
  IDLE_WL_POLARITY,                   /*!< Channel 3N (low side) state (low or high)
                                            when TIM peripheral is in Idle state.
                                            It must be TIM_OCNIdleState_Set or
                                            TIM_OCNIdleState_Reset*/ 
/* PWM Driving signals initialization ----------------------------------------*/  
 (FunctionalState)SW_OV_CURRENT_PROT_ENABLING, /*!< It enable/disable the management of 
                                            an emergency input instantaneously 
                                            stopping PWM generation. It must be 
                                            either equal to ENABLE or DISABLE */  
  OVERCURR_FEEDBACK_POLARITY,               /*!< Emergency Stop (BKIN) input polarity, 
                                           it must be TIM_BreakPolarity_Low or 
                                           TIM_BreakPolarity_High */
  EMERGENCY_STOP_GPIO_PORT,             /*!< Emergency Stop (BKIN) GPIO input 
                                           port (if used, after re-mapping). 
                                           It must be GPIOx x= A, B, ...*/
  EMERGENCY_STOP_GPIO_PIN,              /*!< Emergency Stop (BKIN) GPIO input pin 
                                         (if used, after re-mapping). It must be 
                                          GPIO_Pin_x x= 0, 1, ...*/     
};


/** 
  * @brief  Current sensor parameters Dual Drive Motor 1 - three shunt, STM32F103 HIGH DENSITY
  */
R3_HD2Params_t R3_HD2ParamsDDM1 = 
{
  ADC_CLOCK_DIVIDER,                       /*!<  APB2 clock prescaling factor for 
                                          ADC peripheral. It must be RCC_PCLK2_DivX
                                          x = 2, 4, 6, 8 */    
/* Dual MC parameters --------------------------------------------------------*/ 
  1,                                    /*!< Instance number. Necessary to 
                                             properly synchronize TIM8 with 
                                             TIM1 at peripheral initializations  
                                              */ 
  MAX_TWAIT,                            /*!< It is used for switching the context 
                                           in dual MC. It contains biggest delay
                                           (expressed in counter ticks) between 
                                           the counter crest and ADC latest 
                                           trigger  */
 FREQ_RATIO,                                    /*!< It is used in case of dual MC to 
                                           synchronize TIM1 and TIM8. It has 
                                           effect only on the second instanced 
                                           object and must be equal to the 
                                           ratio between the two PWM frequencies
                                           (higher/lower). Supported values are 
                                           1, 2 or 3 */  
  FREQ_RELATION,                           /*!< When bFreqRatio is greather than 1
                                          this param is used to indicate if this 
                                          instance is the one with the highest 
                                          frequency. Allowed value are: HIGHER_FREQ
                                          or LOWER_FREQ */
  MC_IRQ_PWMNCURRFDBK_1,                     /*!< MC IRQ number used as TIMx Update 
                                           event */
/* Current reading A/D Conversions initialization -----------------------------*/ 
  PHASE_U_CURR_CHANNEL,                  /*!< ADC channel used for conversion of 
                                           current Ia. It must be equal to  
                                           ADC_Channel_x x= 0, ..., 15*/
  PHASE_U_GPIO_PORT,                  /*!< GPIO port used by hIaChannel. It must 
                                           be equal to GPIOx x= A, B, ...*/
  PHASE_U_GPIO_PIN,                      /*!< GPIO pin used by hIaChannel. It must be 
                                          equal to GPIO_Pin_x x= 0, 1, ...*/ 
  SAMPLING_TIME_SEL,               /*!< Sampling time used to convert hIaChannel. 
                                          It must be equal to ADC_SampleTime_xCycles5 
                                          x= 1, 7, ...*/ 
  PHASE_V_CURR_CHANNEL,                  /*!< ADC channel used for conversion of 
                                           current Ib. It must be equal to 
                                           ADC_Channel_x x= 0, ..., 15*/  
  PHASE_V_GPIO_PORT,                /*!< GPIO port used by hIbChannel. It must 
                                           be equal to GPIOx x= A, B, ...*/
  PHASE_V_GPIO_PIN,                      /*!< GPIO pin used by hIaChannel. It must be 
                                          equal to GPIO_Pin_x x= 0, 1, ...*/
  SAMPLING_TIME_SEL,                /*!< Sampling time used to convert hIbChannel. 
                                          It must be equal to ADC_SampleTime_xCycles5 
                                          x= 1, 7, ...*/
  PHASE_W_CURR_CHANNEL,                  /*!< ADC channel used for conversion of 
                                           current Ia. It must be equal to  
                                           ADC_Channel_x x= 0, ..., 15*/
  PHASE_W_GPIO_PORT,                /*!< GPIO port used by hIaChannel. It must 
                                           be equal to GPIOx x= A, B, ...*/
  PHASE_W_GPIO_PIN,                      /*!< GPIO pin used by hIaChannel. It must be 
                                          equal to GPIO_Pin_x x= 0, 1, ...*/ 
  SAMPLING_TIME_SEL,            /*!< Sampling time used to convert hIaChannel. 
                                          It must be equal to ADC_SampleTime_xCycles5 
                                          x= 1, 7, ...*/ 
  
/* PWM generation parameters --------------------------------------------------*/   
  DEAD_TIME_COUNTS,                    /*!< Dead time in number of TIM clock
                                            cycles. If CHxN are enabled, it must
                                            contain the dead time to be generated
                                            by the microcontroller, otherwise it 
                                            expresses the maximum dead time 
                                            generated by driving network */
  REP_COUNTER,                         /*!< It expresses the number of PWM 
                                            periods to be elapsed before compare 
                                            registers are updated again. In 
                                            particular: 
                                            RepetitionCounter= (2* #PWM periods)-1*/
  TW_AFTER,                             /*!< It is the sum of dead time plus max 
                                            value between rise time and noise time
                                            express in number of TIM clocks.*/
  TW_BEFORE,                           /*!< It is the sampling time express in
                                            number of TIM clocks.*/ 
  PWM_TIMER_SELECTION,                               /*!< It contains the pointer to the timer 
                                           used for PWM generation. */
/* PWM Driving signals initialization ----------------------------------------*/  

  PWM_TIMER_REMAPPING,                        /*!< Used only for instance #1, it 
                                           remaps TIM1 outputs. It must equal to 
                                           GPIO_PartialRemap_TIM1 or 
                                           GPIO_FullRemap_TIM1 or
                                           GPIO_NoRemap_TIM1 */
  PHASE_UH_POLARITY,   	              /*!< Channel 1 (high side) output polarity, 
                                           it must be TIM_OCPolarity_High or 
                                           TIM_OCPolarity_Low */
  PHASE_UH_GPIO_PORT,                 /*!< Channel 1 (high side) GPIO output 
                                           port (if used, after re-mapping). 
                                           It must be GPIOx x= A, B, ...*/
  PHASE_UH_GPIO_PIN,                  /*!< Channel 1 (high side) GPIO output pin 
                                          (if used, after re-mapping). It must be 
                                           GPIO_Pin_x x= 0, 1, ...*/  
  IDLE_UH_POLARITY,                   /*!< Channel 1 (high side) state (low or high)
                                            when TIM peripheral is in Idle state.
                                            It must be TIM_OCIdleState_Set or
                                            TIM_OCIdleState_Reset*/
                                            
  PHASE_VH_POLARITY,                   /*!< Channel 2 (high side) output polarity, 
                                           it must be TIM_OCPolarity_High or 
                                           TIM_OCPolarity_Low */ 
  PHASE_VH_GPIO_PORT,                               /*!< Channel 2 (high side) GPIO output 
                                           port (if used, after re-mapping). 
                                           It must be GPIOx x= A, B, ...*/
  PHASE_VH_GPIO_PIN,                       /*!< Channel 2 (high side) GPIO output pin 
                                          (if used, after re-mapping). It must be 
                                          GPIO_Pin_x x= 0, 1, ...*/
  IDLE_VH_POLARITY,              /*!< Channel 2 (high side) state (low or high)
                                            when TIM peripheral is in Idle state.
                                            It must be TIM_OCIdleState_Set or
                                            TIM_OCIdleState_Reset*/    
 
  PHASE_WH_POLARITY,            	 /*!< Channel 3 (high side) output polarity, 
                                           it must be TIM_OCPolarity_High or 
                                           TIM_OCPolarity_Low */  
  PHASE_WH_GPIO_PORT,                               /*!< Channel 3 (high side) GPIO output 
                                           port (if used, after re-mapping). 
                                           It must be GPIOx x= A, B, ...*/
  PHASE_WH_GPIO_PIN,                        /*!< Channel 3 (high side) GPIO output pin 
                                          (if used, after re-mapping). It must be 
                                          GPIO_Pin_x x= 0, 1, ...*/  
  IDLE_WH_POLARITY,              /*!< Channel 3 (high side) state (low or high)
                                            when TIM peripheral is in Idle state.
                                            It must be TIM_OCIdleState_Set or
                                            TIM_OCIdleState_Reset*/  
  
  (FunctionalState)LOW_SIDE_SIGNALS_ENABLING,  /*!< It enable/disable the PWM low side  
                                          driving signals. It must be either 
                                          equal to ENABLE or DISABLE */ 
  
  PHASE_UL_POLARITY,               /*!< Channel 1N (low side) output polarity, 
                                           it must be TIM_OCNPolarity_High or 
                                           TIM_OCNPolarity_Low */
  PHASE_UL_GPIO_PORT,                                 /*!< Channel 1N (low side) GPIO output 
                                           port (if used, after re-mapping). 
                                           It must be GPIOx x= A, B, ...*/
  PHASE_UL_GPIO_PIN,                       /*!< Channel 1N (low side) GPIO output pin 
                                          (if used, after re-mapping). It must be 
                                          GPIO_Pin_x x= 0, 1, ...*/ 
  IDLE_UL_POLARITY,              /*!< Channel 1N (low side) state (low or high)
                                            when TIM peripheral is in Idle state.
                                            It must be TIM_OCNIdleState_Set or
                                            TIM_OCNIdleState_Reset*/ 

  
  PHASE_VL_POLARITY,                 /*!< Channel 2N (low side) output polarity, 
                                           it must be TIM_OCNPolarity_High or 
                                           TIM_OCNPolarity_Low */
  PHASE_VL_GPIO_PORT,                                 /*!< Channel 2N (low side) GPIO output 
                                           port (if used, after re-mapping). 
                                           It must be GPIOx x= A, B, ...*/
  PHASE_VL_GPIO_PIN,                     /*!< Channel 2N (low side) GPIO output pin 
                                          (if used, after re-mapping). It must be 
                                          GPIO_Pin_x x= 0, 1, ...*/ 
  IDLE_VL_POLARITY,              /*!< Channel 2N (low side) state (low or high)
                                            when TIM peripheral is in Idle state.
                                            It must be TIM_OCNIdleState_Set or
                                            TIM_OCNIdleState_Reset*/ 
  
  PHASE_WL_POLARITY,             /*!< Channel 3N (low side) output polarity, 
                                           it must be TIM_OCNPolarity_High or 
                                           TIM_OCNPolarity_Low */
  PHASE_WL_GPIO_PORT,                               /*!< Channel 3N (low side)  GPIO output 
                                           port (if used, after re-mapping). 
                                           It must be GPIOx x= A, B, ...*/
  PHASE_WL_GPIO_PIN,                    /*!< Channel 3N (low side)  GPIO output pin 
                                          (if used, after re-mapping). It must be 
                                          GPIO_Pin_x x= 0, 1, ...*/   
  IDLE_WL_POLARITY,              /*!< Channel 3N (low side) state (low or high)
                                            when TIM peripheral is in Idle state.
                                            It must be TIM_OCNIdleState_Set or
                                            TIM_OCNIdleState_Reset*/   
/* PWM Driving signals initialization ----------------------------------------*/  
 (FunctionalState)SW_OV_CURRENT_PROT_ENABLING, /*!< It enable/disable the management of 
                                            an emergency input instantaneously 
                                            stopping PWM generation. It must be 
                                            either equal to ENABLE or DISABLE */  
  OVERCURR_FEEDBACK_POLARITY,               /*!< Emergency Stop (BKIN) input polarity, 
                                           it must be TIM_BreakPolarity_Low or 
                                           TIM_BreakPolarity_High */
  EMERGENCY_STOP_GPIO_PORT,             /*!< Emergency Stop (BKIN) GPIO input 
                                           port (if used, after re-mapping). 
                                           It must be GPIOx x= A, B, ...*/
  EMERGENCY_STOP_GPIO_PIN,              /*!< Emergency Stop (BKIN) GPIO input pin 
                                         (if used, after re-mapping). It must be 
                                          GPIO_Pin_x x= 0, 1, ...*/     
};


/** 
  * @brief  Current sensor parameters Dual Drive Motor 1 - one shunt, STM32F103 HIGH DENSITY
  */
R1_HD2Params_t R1_HD2ParamsDDM1 = 
{  
  ADC_CLOCK_DIVIDER,                /*!<  APB2 clock prescaling factor for 
                                          ADC peripheral. It must be RCC_PCLK2_DivX
                                          x = 2, 4, 6, 8. Only the first instance 
                                          parameter is used to set the prescaling
                                          factor*/  

  MC_IRQ_PWMNCURRFDBK_1,              /*!< MC IRQ number used for UPDATE event */
 
/* Instance number -----------------------------------------------------------*/ 
  1,                                    /*!< Instance number. Necessary to 
                                             properly synchronize PWM Timers and
                                             start peripheral clocks*/  
 TRUE,                             /*!< Specifies whether this object is the first
                                             R1HD2 instance or not.*/
 FREQ_RATIO,                            /*!< It is used in case of dual MC to 
                                             synchronize TIM1 and TIM8. It has 
                                             effect only on the second instanced 
                                             object and must be equal to the 
                                             ratio between the two PWM frequencies
                                             (higher/lower). Supported values are 
                                             1, 2 or 3 */  
 FREQ_RELATION,        			    /*!< When bFreqRatio is greather than 1
                                             this param is used to indicate if this 
                                             instance is the one with the highest 
                                             frequency. Allowed value are: HIGHER_FREQ
                                             or LOWER_FREQ */
 PWM_TIMER_SELECTION,                  /*!< Timer used for PWM generation. It should be
                                              TIM1 or TIM8*/

  
  /* Current reading A/D Conversions initialization --------------------------*/ 
  PHASE_CURRENTS_CHANNEL,                /*!< ADC channel used for conversion of 
                                       current. It must be equal to  
                                       ADC_Channel_x x= 0, ..., 15*/
  PHASE_CURRENTS_GPIO_PORT,                  /*!< GPIO port used by hIChannel. It must 
                                       be equal to GPIOx x= A, B, ...*/
  PHASE_CURRENTS_GPIO_PIN,                   /*!< GPIO pin used by hIChannel. It must be 
                                       equal to GPIO_Pin_x x= 0, 1, ...*/ 
  SAMPLING_TIME_SEL,        /*!< Sampling time used to convert hIChannel. 
                                       It must be equal to ADC_SampleTime_xCycles5 
                                       x= 1, 7, ...*/ 
  
/* PWM generation parameters --------------------------------------------------*/   
  DEAD_TIME_COUNTS,                    /*!< Dead time in number of TIM clock
                                            cycles. If CHxN are enabled, it must
                                            contain the dead time to be generated
                                            by the microcontroller, otherwise it 
                                            expresses the maximum dead time 
                                            generated by driving network */
  REP_COUNTER,                         /*!< It expresses the number of PWM 
                                            periods to be elapsed before compare 
                                            registers are updated again. In 
                                            particular: 
                                            RepetitionCounter= (2* #PWM periods)-1*/
  TAFTER,                         /*!< It is the sum of dead time plus rise time
                                       express in number of TIM clocks.*/
  TBEFORE,                            /*!< */ 
  TMIN,                            /*!< It is the sum of dead time plus rise time
                                       plus sampling time express in numbers of
                                       TIM clocks.*/
  HTMIN,                          /*!< It is the half of hTMin value.*/
  TSAMPLE,                        /*!< It is the sampling time express in 
                                       numbers of TIM clocks.*/
  MAX_TRTS,                       /*!< It is the maximum between twice of rise
                                       time express in number of TIM clocks and
                                       twice of sampling time express in numbers
                                       of TIM clocks.*/
  
/* PWM Driving signals initialization ----------------------------------------*/  
  PWM_TIMER_REMAPPING,                /*!< Used only for instance #1, it 
                                           remaps TIM1 outputs. It must equal to 
                                           GPIO_PartialRemap_TIM1 or 
                                           GPIO_FullRemap_TIM1 or
                                           GPIO_NoRemap_TIM1 */
  PHASE_UH_POLARITY,   	              /*!< Channel 1 (high side) output polarity, 
                                           it must be TIM_OCPolarity_High or 
                                           TIM_OCPolarity_Low */
  PHASE_UH_GPIO_PORT,                 /*!< Channel 1 (high side) GPIO output 
                                          port (if used, after re-mapping). 
                                          It must be GPIOx x= A, B, ...*/
  PHASE_UH_GPIO_PIN,                 /*!< Channel 1 (high side) GPIO output pin 
                                          (if used, after re-mapping). It must be 
                                          GPIO_Pin_x x= 0, 1, ...*/  
  IDLE_UH_POLARITY,                  /*!< Channel 1 (high side) state (low or high)
                                            when TIM peripheral is in Idle state.
                                            It must be TIM_OCIdleState_Set or
                                            TIM_OCIdleState_Reset*/
                                            
  PHASE_VH_POLARITY,                 /*!< Channel 2 (high side) output polarity, 
                                           it must be TIM_OCPolarity_High or 
                                           TIM_OCPolarity_Low */ 
  PHASE_VH_GPIO_PORT,                  /*!< Channel 2 (high side) GPIO output 
                                           port (if used, after re-mapping). 
                                           It must be GPIOx x= A, B, ...*/
  PHASE_VH_GPIO_PIN,                   /*!< Channel 2 (high side) GPIO output pin 
                                          (if used, after re-mapping). It must be 
                                          GPIO_Pin_x x= 0, 1, ...*/
  IDLE_VH_POLARITY,                    /*!< Channel 2 (high side) state (low or high)
                                            when TIM peripheral is in Idle state.
                                            It must be TIM_OCIdleState_Set or
                                            TIM_OCIdleState_Reset*/    
 
  PHASE_WH_POLARITY,            	 /*!< Channel 3 (high side) output polarity, 
                                           it must be TIM_OCPolarity_High or 
                                           TIM_OCPolarity_Low */  
  PHASE_WH_GPIO_PORT,                               /*!< Channel 3 (high side) GPIO output 
                                           port (if used, after re-mapping). 
                                           It must be GPIOx x= A, B, ...*/
  PHASE_WH_GPIO_PIN,                        /*!< Channel 3 (high side) GPIO output pin 
                                          (if used, after re-mapping). It must be 
                                          GPIO_Pin_x x= 0, 1, ...*/  
  IDLE_WH_POLARITY,              /*!< Channel 3 (high side) state (low or high)
                                            when TIM peripheral is in Idle state.
                                            It must be TIM_OCIdleState_Set or
                                            TIM_OCIdleState_Reset*/  
  
  (FunctionalState)LOW_SIDE_SIGNALS_ENABLING,  /*!< It enable/disable the PWM low side  
                                          driving signals. It must be either 
                                          equal to ENABLE or DISABLE */ 
  
  PHASE_UL_POLARITY,               /*!< Channel 1N (low side) output polarity, 
                                           it must be TIM_OCNPolarity_High or 
                                           TIM_OCNPolarity_Low */
  PHASE_UL_GPIO_PORT,                                 /*!< Channel 1N (low side) GPIO output 
                                           port (if used, after re-mapping). 
                                           It must be GPIOx x= A, B, ...*/
  PHASE_UL_GPIO_PIN,                       /*!< Channel 1N (low side) GPIO output pin 
                                          (if used, after re-mapping). It must be 
                                          GPIO_Pin_x x= 0, 1, ...*/ 
  IDLE_UL_POLARITY,              /*!< Channel 1N (low side) state (low or high)
                                            when TIM peripheral is in Idle state.
                                            It must be TIM_OCNIdleState_Set or
                                            TIM_OCNIdleState_Reset*/ 

  
  PHASE_VL_POLARITY,                 /*!< Channel 2N (low side) output polarity, 
                                           it must be TIM_OCNPolarity_High or 
                                           TIM_OCNPolarity_Low */
  PHASE_VL_GPIO_PORT,                                 /*!< Channel 2N (low side) GPIO output 
                                           port (if used, after re-mapping). 
                                           It must be GPIOx x= A, B, ...*/
  PHASE_VL_GPIO_PIN,                     /*!< Channel 2N (low side) GPIO output pin 
                                          (if used, after re-mapping). It must be 
                                          GPIO_Pin_x x= 0, 1, ...*/ 
  IDLE_VL_POLARITY,              /*!< Channel 2N (low side) state (low or high)
                                            when TIM peripheral is in Idle state.
                                            It must be TIM_OCNIdleState_Set or
                                            TIM_OCNIdleState_Reset*/ 
  
  PHASE_WL_POLARITY,             /*!< Channel 3N (low side) output polarity, 
                                           it must be TIM_OCNPolarity_High or 
                                           TIM_OCNPolarity_Low */
  PHASE_WL_GPIO_PORT,                               /*!< Channel 3N (low side)  GPIO output 
                                           port (if used, after re-mapping). 
                                           It must be GPIOx x= A, B, ...*/
  PHASE_WL_GPIO_PIN,                    /*!< Channel 3N (low side)  GPIO output pin 
                                          (if used, after re-mapping). It must be 
                                          GPIO_Pin_x x= 0, 1, ...*/   
  IDLE_WL_POLARITY,              /*!< Channel 3N (low side) state (low or high)
                                            when TIM peripheral is in Idle state.
                                            It must be TIM_OCNIdleState_Set or
                                            TIM_OCNIdleState_Reset*/ 
/* PWM Driving signals initialization ----------------------------------------*/  
 (FunctionalState)SW_OV_CURRENT_PROT_ENABLING, /*!< It enable/disable the management of 
                                            an emergency input instantaneously 
                                            stopping PWM generation. It must be 
                                            either equal to ENABLE or DISABLE */  
  OVERCURR_FEEDBACK_POLARITY,               /*!< Emergency Stop (BKIN) input polarity, 
                                           it must be TIM_BreakPolarity_Low or 
                                           TIM_BreakPolarity_High */
  EMERGENCY_STOP_GPIO_PORT,             /*!< Emergency Stop (BKIN) GPIO input 
                                           port (if used, after re-mapping). 
                                           It must be GPIOx x= A, B, ...*/
  EMERGENCY_STOP_GPIO_PIN,              /*!< Emergency Stop (BKIN) GPIO input pin 
                                         (if used, after re-mapping). It must be 
                                          GPIO_Pin_x x= 0, 1, ...*/   
};


/** 
  * @brief  Current sensor parameters Dual Drive Motor 1 - ICS, STM32F103 HIGH DENSITY
  */
ICS_HD2Params_t ICS_HD2ParamsDDM1 = {
  ADC_CLOCK_DIVIDER,                /*!< APB2 clock prescaling factor for 
                                          ADC peripheral. It must be RCC_PCLK2_DivX
                                          x = 2, 4, 6, 8 */  
  
/* Dual MC parameters --------------------------------------------------------*/ 
  1,                                 /*!< Instance number with reference to PWMC  
                                          base class. It is necessary to properly
                                          synchronize TIM8 with TIM1 at 
                                          peripheral initializations */ 
  MAX_TWAIT,                               /*!< It is used for switching the context 
                                           in dual MC. It contains biggest delay
                                           (expressed in counter ticks) between 
                                           the counter crest and ADC latest 
                                           trigger  */
  FREQ_RATIO,                 /*!< It is used in case of dual MC to 
                                           synchronize TIM1 and TIM8. It has 
                                           effect only on the second instanced 
                                           object and must be equal to the 
                                           ratio between the two PWM frequencies
                                           (higher/lower). Supported values are 
                                           1, 2 or 3 */  
  FREQ_RELATION,                           /*!< When bFreqRatio is greather than 1
                                          this param is used to indicate if this 
                                          instance is the one with the highest 
                                          frequency. Allowed value are: HIGHER_FREQ
                                          or LOWER_FREQ */
  MC_IRQ_PWMNCURRFDBK_1,                     /*!< MC IRQ number used as TIMx Update 
                                           event */
/* Current reading A/D Conversions initialization -----------------------------*/ 
  PHASE_U_CURR_CHANNEL,                  /*!< ADC channel used for conversion of 
                                           current Ia. It must be equal to  
                                           ADC_Channel_x x= 0, ..., 15*/
  PHASE_U_GPIO_PORT,                  /*!< GPIO port used by hIaChannel. It must 
                                           be equal to GPIOx x= A, B, ...*/
  PHASE_U_GPIO_PIN,                      /*!< GPIO pin used by hIaChannel. It must be 
                                          equal to GPIO_Pin_x x= 0, 1, ...*/ 
  SAMPLING_TIME_SEL,               /*!< Sampling time used to convert hIaChannel. 
                                          It must be equal to ADC_SampleTime_xCycles5 
                                          x= 1, 7, ...*/ 
  PHASE_V_CURR_CHANNEL,                  /*!< ADC channel used for conversion of 
                                           current Ib. It must be equal to 
                                           ADC_Channel_x x= 0, ..., 15*/  
  PHASE_V_GPIO_PORT,                /*!< GPIO port used by hIbChannel. It must 
                                           be equal to GPIOx x= A, B, ...*/
  PHASE_V_GPIO_PIN,                      /*!< GPIO pin used by hIaChannel. It must be 
                                          equal to GPIO_Pin_x x= 0, 1, ...*/
  SAMPLING_TIME_SEL,                /*!< Sampling time used to convert hIbChannel. 
                                          It must be equal to ADC_SampleTime_xCycles5 
                                          x= 1, 7, ...*/
/* PWM generation parameters --------------------------------------------------*/   
  DEAD_TIME_COUNTS,
                                          /*!< Dead time in number of TIM clock
                                            cycles. If CHxN are enabled, it must
                                            contain the dead time to be generated
                                            by the microcontroller, otherwise it 
                                            expresses the maximum dead time 
                                            generated by driving network */
  REP_COUNTER,                                  /*!< It expresses the number of PWM 
                                            periods to be elapsed before compare 
                                            registers are updated again. In 
                                            particular: 
                                            RepetitionCounter= (2* #PWM periods)-1*/
  PWM_TIMER_SELECTION,                  /*!< It contains the pointer to the timer 
                                           used for PWM generation. */
/* PWM Driving signals initialization ----------------------------------------*/  

  PWM_TIMER_REMAPPING,            /*!< Used only for instance #1, it 
                                       remaps TIM1 outputs. It must equal to 
                                       GPIO_PartialRemap_TIM1 or 
                                       GPIO_FullRemap_TIM1 or
                                       GPIO_NoRemap_TIM1 */
  PHASE_UH_POLARITY,   	           /*!< Channel 1 (high side) output polarity, 
                                           it must be TIM_OCPolarity_High or 
                                           TIM_OCPolarity_Low */
  PHASE_UH_GPIO_PORT,                                 /*!< Channel 1 (high side) GPIO output 
                                         port (if used, after re-mapping). 
                                         It must be GPIOx x= A, B, ...*/
  PHASE_UH_GPIO_PIN,                       /*!< Channel 1 (high side) GPIO output pin 
                                          (if used, after re-mapping). It must be 
                                          GPIO_Pin_x x= 0, 1, ...*/  
  IDLE_UH_POLARITY,              /*!< Channel 1 (high side) state (low or high)
                                            when TIM peripheral is in Idle state.
                                            It must be TIM_OCIdleState_Set or
                                            TIM_OCIdleState_Reset*/
                                            
  PHASE_VH_POLARITY,               /*!< Channel 2 (high side) output polarity, 
                                           it must be TIM_OCPolarity_High or 
                                           TIM_OCPolarity_Low */ 
  PHASE_VH_GPIO_PORT,                               /*!< Channel 2 (high side) GPIO output 
                                           port (if used, after re-mapping). 
                                           It must be GPIOx x= A, B, ...*/
  PHASE_VH_GPIO_PIN,                       /*!< Channel 2 (high side) GPIO output pin 
                                          (if used, after re-mapping). It must be 
                                          GPIO_Pin_x x= 0, 1, ...*/
  IDLE_VH_POLARITY,              /*!< Channel 2 (high side) state (low or high)
                                            when TIM peripheral is in Idle state.
                                            It must be TIM_OCIdleState_Set or
                                            TIM_OCIdleState_Reset*/    
 
  PHASE_WH_POLARITY,            	 /*!< Channel 3 (high side) output polarity, 
                                           it must be TIM_OCPolarity_High or 
                                           TIM_OCPolarity_Low */  
  PHASE_WH_GPIO_PORT,                               /*!< Channel 3 (high side) GPIO output 
                                           port (if used, after re-mapping). 
                                           It must be GPIOx x= A, B, ...*/
  PHASE_WH_GPIO_PIN,                        /*!< Channel 3 (high side) GPIO output pin 
                                          (if used, after re-mapping). It must be 
                                          GPIO_Pin_x x= 0, 1, ...*/  
  IDLE_WH_POLARITY,              /*!< Channel 3 (high side) state (low or high)
                                            when TIM peripheral is in Idle state.
                                            It must be TIM_OCIdleState_Set or
                                            TIM_OCIdleState_Reset*/  
  
  (FunctionalState)LOW_SIDE_SIGNALS_ENABLING,  /*!< It enable/disable the PWM low side  
                                          driving signals. It must be either 
                                          equal to ENABLE or DISABLE */ 
  
  PHASE_UL_POLARITY,               /*!< Channel 1N (low side) output polarity, 
                                           it must be TIM_OCNPolarity_High or 
                                           TIM_OCNPolarity_Low */
  PHASE_UL_GPIO_PORT,                                 /*!< Channel 1N (low side) GPIO output 
                                           port (if used, after re-mapping). 
                                           It must be GPIOx x= A, B, ...*/
  PHASE_UL_GPIO_PIN,                       /*!< Channel 1N (low side) GPIO output pin 
                                          (if used, after re-mapping). It must be 
                                          GPIO_Pin_x x= 0, 1, ...*/ 
  IDLE_UL_POLARITY,              /*!< Channel 1N (low side) state (low or high)
                                            when TIM peripheral is in Idle state.
                                            It must be TIM_OCNIdleState_Set or
                                            TIM_OCNIdleState_Reset*/ 

  
  PHASE_VL_POLARITY,                 /*!< Channel 2N (low side) output polarity, 
                                           it must be TIM_OCNPolarity_High or 
                                           TIM_OCNPolarity_Low */
  PHASE_VL_GPIO_PORT,                                 /*!< Channel 2N (low side) GPIO output 
                                           port (if used, after re-mapping). 
                                           It must be GPIOx x= A, B, ...*/
  PHASE_VL_GPIO_PIN,                     /*!< Channel 2N (low side) GPIO output pin 
                                          (if used, after re-mapping). It must be 
                                          GPIO_Pin_x x= 0, 1, ...*/ 
  IDLE_VL_POLARITY,              /*!< Channel 2N (low side) state (low or high)
                                            when TIM peripheral is in Idle state.
                                            It must be TIM_OCNIdleState_Set or
                                            TIM_OCNIdleState_Reset*/ 
  
  PHASE_WL_POLARITY,             /*!< Channel 3N (low side) output polarity, 
                                           it must be TIM_OCNPolarity_High or 
                                           TIM_OCNPolarity_Low */
  PHASE_WL_GPIO_PORT,                               /*!< Channel 3N (low side)  GPIO output 
                                           port (if used, after re-mapping). 
                                           It must be GPIOx x= A, B, ...*/
  PHASE_WL_GPIO_PIN,                    /*!< Channel 3N (low side)  GPIO output pin 
                                          (if used, after re-mapping). It must be 
                                          GPIO_Pin_x x= 0, 1, ...*/   
  IDLE_WL_POLARITY,              /*!< Channel 3N (low side) state (low or high)
                                            when TIM peripheral is in Idle state.
                                            It must be TIM_OCNIdleState_Set or
                                            TIM_OCNIdleState_Reset*/ 
/* Emergengy signal initialization ----------------------------------------*/  
 (FunctionalState)SW_OV_CURRENT_PROT_ENABLING, /*!< It enable/disable the management of 
                                            an emergency input instantaneously 
                                            stopping PWM generation. It must be 
                                            either equal to ENABLE or DISABLE */  
  OVERCURR_FEEDBACK_POLARITY,               /*!< Emergency Stop (BKIN) input polarity, 
                                           it must be TIM_BreakPolarity_Low or 
                                           TIM_BreakPolarity_High */
  EMERGENCY_STOP_GPIO_PORT,             /*!< Emergency Stop (BKIN) GPIO input 
                                           port (if used, after re-mapping). 
                                           It must be GPIOx x= A, B, ...*/
  EMERGENCY_STOP_GPIO_PIN              /*!< Emergency Stop (BKIN) GPIO input pin 
                                         (if used, after re-mapping). It must be 
                                          GPIO_Pin_x x= 0, 1, ...*/     
};


/** 
  * @brief  SpeedNPosition sensor parameters Motor 1 - Base Class
  */
SpeednPosFdbkParams_t SpeednPosFdbkParamsM1 =
{
  POLE_PAIR_NUM,                /*!< Coefficient used to transform electrical to
                               mechanical quantities and viceversa. It usually
                               coincides with motor pole pairs number*/
 (uint16_t)(1.15*MAX_APPLICATION_SPEED/6), /*< Maximum value of measured speed that is
                                          considered to be valid. It's expressed
                                          in tenth of mechanical Hertz.*/
 (uint16_t)(MIN_APPLICATION_SPEED/6),/*< Minimum value of measured speed that is
                                        considered to be valid. It's expressed
                                        in tenth of mechanical Hertz.*/
  MEAS_ERRORS_BEFORE_FAULTS,            /*< Maximum value of not valid measurements
                                        before an error is reported.*/
  65535,                                 /*< Maximum value of measured acceleration
                                        that is considered to be valid. It's
                                        expressed in 01HzP (tenth of Hertz per
                                        speed calculation period)*/
  TF_REGULATION_RATE,                    /*< Frequency on which the user will request
                                    a measurement of the rotor electrical angle.
                                    It's also used to convert measured speed from
                                    tenth of Hz to dpp and viceversa.*/
};

/** 
  * @brief  SpeedNPosition sensor parameters Motor 1 - State Observer + PLL
  */
STOParams_t STOParamsM1 =
{
   C1,                                /*!< State observer constant C1, it can 
                                           be computed as F1 * Rs(ohm)/(Ls[H] * 
                                           State observer execution rate [Hz])*/
   C2,                               /*!<  Variable containing state observer 
                                           constant C2, it can be computed as 
                                           F1 * K1/ State observer execution 
                                           rate [Hz] being K1 one of the two 
                                           observer gains   */   
   C3,                                /*!< State observer constant C3, it can 
                                           be computed as F1 * Max application 
                                           speed [rpm] * Motor B-emf constant 
                                           [Vllrms/krpm] * sqrt(2)/ (Ls [H] *
                                           max measurable current (A) * State 
                                           observer execution rate [Hz])*/ 
   C4,                                /*!< State Observer constant C4, it can 
                                           be computed as K2 * max measurable 
                                           current (A) / (Max application speed 
                                           [rpm] * Motor B-emf constant 
                                           [Vllrms/krpm] * sqrt(2) * F2 * State 
                                           observer execution rate [Hz]) being 
                                           K2 one of the two observer gains  */
   C5,                                /*!< State Observer constant C5, it can 
                                           be computed as F1 * max measurable 
                                           voltage / (2 * Ls [Hz] * max 
                                           measurable current * State observer 
                                           execution rate [Hz]) */
   F1,                                /*!< State observer scaling factor F1 */
   F2,                                /*!< State observer scaling factor F2 */ 									 
	{
     PLL_KP_GAIN,               /*!< Default Kp gain, used to initialize Kp gain
                                     software variable*/
     PLL_KI_GAIN,               /*!< Default Ki gain, used to initialize Ki gain
                                     software variable*/
     16384,                       /*!< Kp gain divisor, used in conjuction with 
                                     Kp gain allows obtaining fractional values. 
                                     If FULL_MISRA_C_COMPLIANCY is not defined 
                                     the divisor is implemented through 
                                     algebrical right shifts to speed up PI 
                                     execution. Only in this case this parameter
                                     specifies the number of right shifts to be 
                                     executed */
     65535,                     /*!< Ki gain divisor, used in conjuction with 
                                     Ki gain allows obtaining fractional values. 
                                     If FULL_MISRA_C_COMPLIANCY is not defined 
                                     the divisor is implemented through 
                                     algebrical right shifts to speed up PI 
                                     execution. Only in this case this parameter
                                     specifies the number of right shifts to be 
                                     executed */
     S32_MAX,                   /*!< Upper limit used to saturate the integral 
                                     term given by Ki / Ki divisor * integral of
                                     process variable error */ 
     -S32_MAX,                  /*!< Lower limit used to saturate the integral 
                                     term given by Ki / Ki divisor * integral of
                                     process variable error */    
     S16_MAX,                   /*!< Upper limit used to saturate the PI output 
                                     */ 
     -S16_MAX                   /*!< Lower limit used to saturate the PI output 
                                     */ 
   },      			/*!< It contains the parameters of the PI
                                     object necessary for PLL 
                                     implementation */
                          
   STO_FIFO_DEPTH_01HZ,              /*!< Depth of FIFO used to average 
                                           estimated speed exported by 
                                           SPD_GetAvrgMecSpeed01Hz. It 
                                           must be an integer number between 1 
                                           and 64 */  
   STO_FIFO_DEPTH_DPP,               /*!< Depth of FIFO used for both averaging 
                                           estimated speed exported by 
                                           SPD_GetElSpeedDpp and state 
                                           observer equations. It must be an 
                                           integer number between 1 and
                                           bSpeedBufferSize01Hz */       
   PERCENTAGE_FACTOR,                /*!< Parameter expressing the maximum 
                                           allowed variance of speed estimation 
                                           */ 
   SPEED_BAND_UPPER_LIMIT,           /*!< It expresses how much estimated speed
                                           can exceed forced stator electrical 
                                           frequency during start-up without 
                                           being considered wrong. The 
                                           measurement unit is 1/16 of forced 
                                           speed */
   SPEED_BAND_LOWER_LIMIT,             /*!< It expresses how much estimated speed
                                           can be below forced stator electrical 
                                           frequency during start-up without 
                                           being considered wrong. The 
                                           measurement unit is 1/16 of forced 
                                           speed */
   OBS_MINIMUM_SPEED,                  /*!< Minimum mechanical speed (expressed in 
                                          01Hz required to validate the start-up
                                          */
   NB_CONSECUTIVE_TESTS,  	       /*!< Number of consecutive tests on speed 
                                           consistency to be passed before 
                                           validating the start-up */
   OBS_MEAS_ERRORS_BEFORE_FAULTS,        /*!< Number of reliability failed 
                                           consecutive tests before a speed 
                                           check fault is returned to base class 
                                           */
  BEMF_CONSISTENCY_TOL,                    /*!< Degree of consistency of the observed
                                           back-emfs, it must be an integer
                                           number ranging from 1 (very high 
                                           consistency) down to 64 (very poor
                                           consistency) */
  BEMF_CONSISTENCY_GAIN,               /*!< Gain to be applied when checking
                                           back-emfs consistency; default value
                                           is 64 (neutral), max value 105
                                           (x1,64 amplification), min value 1
                                           (/64 attenuation) */
  (uint16_t)(MAX_APPLICATION_SPEED*1.15/6.0)  /*!< Maximum positive value
                                             of rotor speed. It's expressed in 
                                             tenth of mechanical Hertz. It can be
                                             x1.1 greater than max application*/   
};

/** 
  * @brief  SpeedNPosition sensor parameters Motor 1 - State Observer + CORDIC
  */
STO_CORDICParams_t STO_CORDICParamsM1 =
{
   CORD_C1,                                /*!< State observer constant C1, it can 
                                           be computed as F1 * Rs(ohm)/(Ls[H] * 
                                           State observer execution rate [Hz])*/
   CORD_C2,                          /*!<  Variable containing state observer 
                                           constant C2, it can be computed as 
                                           F1 * K1/ State observer execution 
                                           rate [Hz] being K1 one of the two 
                                           observer gains   */   
   CORD_C3,                                /*!< State observer constant C3, it can 
                                           be computed as F1 * Max application 
                                           speed [rpm] * Motor B-emf constant 
                                           [Vllrms/krpm] * sqrt(2)/ (Ls [H] *
                                           max measurable current (A) * State 
                                           observer execution rate [Hz])*/ 
   CORD_C4,                           /*!< State Observer constant C4, it can 
                                           be computed as K2 * max measurable 
                                           current (A) / (Max application speed 
                                           [rpm] * Motor B-emf constant 
                                           [Vllrms/krpm] * sqrt(2) * F2 * State 
                                           observer execution rate [Hz]) being 
                                           K2 one of the two observer gains  */
   CORD_C5,                                /*!< State Observer constant C5, it can 
                                           be computed as F1 * max measurable 
                                           voltage / (2 * Ls [Hz] * max 
                                           measurable current * State observer 
                                           execution rate [Hz]) */
   CORD_F1,                                /*!< State observer scaling factor F1 */
   CORD_F2,                                /*!< State observer scaling factor F2 */
   CORD_FIFO_DEPTH_01HZ,              /*!< Depth of FIFO used to average 
                                           estimated speed exported by 
                                           SPD_GetAvrgMecSpeed01Hz. It 
                                           must be an integer number between 1 
                                           and 64 */  
   CORD_FIFO_DEPTH_DPP,               /*!< Depth of FIFO used for both averaging 
                                           estimated speed exported by 
                                           SPD_GetElSpeedDpp and state 
                                           observer equations. It must be an 
                                           integer number between 1 and
                                           bSpeedBufferSize01Hz */       
   CORD_PERCENTAGE_FACTOR,                /*!< Parameter expressing the maximum 
                                           allowed variance of speed estimation 
                                           */ 
   SPEED_BAND_UPPER_LIMIT,           /*!< It expresses how much estimated speed
                                           can exceed forced stator electrical 
                                           frequency during start-up without 
                                           being considered wrong. The 
                                           measurement unit is 1/16 of forced 
                                           speed */
   SPEED_BAND_LOWER_LIMIT,            /*!< It expresses how much estimated speed
                                           can be below forced stator electrical 
                                           frequency during start-up without 
                                           being considered wrong. The 
                                           measurement unit is 1/16 of forced 
                                           speed */
  OBS_MINIMUM_SPEED,                  /*!< Minimum mechanical speed (expressed in 
                                           01Hz required to validate the start-up
                                           */
  NB_CONSECUTIVE_TESTS,  		      /*!< Number of consecutive tests on speed 
                                           consistency to be passed before 
                                           validating the start-up */
  CORD_MEAS_ERRORS_BEFORE_FAULTS,      /*!< Number of reliability failed 
                                           consecutive tests before a speed 
                                           check fault is returned to base class 
                                           */             
  CORD_MAX_ACCEL_DPPP,                 /*!< maximum instantaneous electrical
                                         acceleration (dpp per control period) */                                           
  CORD_BEMF_CONSISTENCY_TOL,                    /*!< Degree of consistency of the observed
                                           back-emfs, it must be an integer
                                           number ranging from 1 (very high 
                                           consistency) down to 64 (very poor
                                           consistency) */
  CORD_BEMF_CONSISTENCY_GAIN,               /*!< Gain to be applied when checking
                                           back-emfs consistency; default value
                                           is 64 (neutral), max value 105
                                           (x1,64 amplification), min value 1
                                           (/64 attenuation) */
  (uint16_t)(MAX_APPLICATION_SPEED*1.15/6.0)  /*!< Maximum positive value
                                             of rotor speed. It's expressed in 
                                             tenth of mechanical Hertz. It can be
                                             x1.1 greater than max application*/                                           
};

/** 
  * @brief  SpeedNPosition sensor parameters Motor 1 - Virtual Sensor
  */
VirtualSpeedSensorParams_t VirtualSpeedSensorParamsM1 =
{
  MEDIUM_FREQUENCY_TASK_RATE,      /*!< Frequency (Hz) at which motor speed is to 
                                      be computed. It must be equal to the frequency
                                      at which function SPD_CalcAvrgMecSpeed01Hz
                                      is called.*/
  (int16_t)(TF_REGULATION_RATE * TRANSITION_DURATION/ 1000.0), 
                             /* Number of steps to perform 
                             the transition phase from CVSS_SPD to other CSPD;
                             if the Transition PHase should last TPH milliseconds,
                             and the FOC Execution Frequency is set to FEF kHz,
                             then hTransitionSteps = TPH * FEF. If set to zero, 
                             it disables soft transition. It's recommended to 
                             set TPH as multiple of medium frequency task period
                             */
};

/** 
  * @brief  RevUp controller parameters Motor 1
  */
RUCPhasesParams_t Phase5_M1 = 
{
  (uint16_t)PHASE5_DURATION,        /*!< Duration of the rev up phase expressed in
                                       milliseconds.*/
  (int16_t)(PHASE5_FINAL_SPEED_RPM/6),/*!< Mechanical speed expressed in 0.1Hz assumed
                                     by VSS at the end of the rev up phase.*/
  (int16_t)PHASE5_FINAL_CURRENT,     /*!< Motor torque reference imposed by STC at the
                                     end of rev up phase. This value represents
                                     actually the Iq current expressed in digit.*/
  MC_NULL
};

  
RUCPhasesParams_t Phase4_M1 = 
{
  (uint16_t)PHASE4_DURATION,       /*!< Duration of the rev up phase expressed in
                                       milliseconds.*/
  (int16_t)(PHASE4_FINAL_SPEED_RPM/6),/*!< Mechanical speed expressed in 0.1Hz assumed
                                     by VSS at the end of the rev up phase.*/
  (int16_t)PHASE4_FINAL_CURRENT,   /*!< Motor torque reference imposed by STC at the
                                     end of rev up phase. This value represents
                                     actually the Iq current expressed in digit.*/
    (void*)&Phase5_M1
};

RUCPhasesParams_t Phase3_M1 = 
{
  (uint16_t)PHASE3_DURATION,       /*!< Duration of the rev up phase expressed in
                                       milliseconds.*/
  (int16_t)(PHASE3_FINAL_SPEED_RPM/6), /*!< Mechanical speed expressed in 0.1Hz assumed
                                     by VSS at the end of the rev up phase.*/
  (int16_t)PHASE3_FINAL_CURRENT, /*!< Motor torque reference imposed by STC at the
                                     end of rev up phase. This value represents
                                     actually the Iq current expressed in digit.*/
  (void*)&Phase4_M1
};

RUCPhasesParams_t Phase2_M1 = 
{
  (uint16_t)PHASE2_DURATION,      /*!< Duration of the rev up phase expressed in
                                       milliseconds.*/
  (int16_t)(PHASE2_FINAL_SPEED_RPM/6),/*!< Mechanical speed expressed in 0.1Hz assumed
                                     by VSS at the end of the rev up phase.*/
  (int16_t)PHASE2_FINAL_CURRENT,    /*!< Motor torque reference imposed by STC at the
                                     end of rev up phase. This value represents
                                     actually the Iq current expressed in digit.*/
  (void*)&Phase3_M1
};

RUCPhasesParams_t Phase1_M1 = 
{
  (uint16_t)PHASE1_DURATION,     /*!< Duration of the rev up phase expressed in
                                       milliseconds.*/
  (int16_t)(PHASE1_FINAL_SPEED_RPM/6),/*!< Mechanical speed expressed in 0.1Hz assumed
                                     by VSS at the end of the rev up phase.*/
  (int16_t)PHASE1_FINAL_CURRENT,  /*!< Motor torque reference imposed by STC at the
                                     end of rev up phase. This value represents
                                     actually the Iq current expressed in digit.*/
  (void*)&Phase2_M1
};

RevupCtrlParams_t RevupCtrlParamsM1 =
{
  MEDIUM_FREQUENCY_TASK_RATE,         /*!< Frequency expressed in Hz at which the user
                                 clocks the RUC calling RUC_Exec method */
  (int16_t)((int32_t)(STARTING_ANGLE_DEG)* 65536/360),
								/*!< Starting angle of programmed rev up.*/
  &Phase1_M1,                /*!< Pointer of the first element of 
                                     phase params that constitute the programmed 
                                     rev up. Each element is of type 
                                     RUCPhasesParams_t.*/
  FIRST_SLESS_ALGO_PHASE                                     
};

/** 
  * @brief  SpeedNPosition sensor parameters Motor 1 - Encoder
  */
ENCODERParams_t ENCParamsM1 =
{
  /* SW Settings */
  MC_IRQ_SPEEDNPOSFDBK_1, /*!< MC IRQ number used for TIMx capture update event.*/
  
  ENCODER_PPR*4,		  /*!< Number of pulses per revolution, provided by each
                              of the two encoder signals, multiplied by 4 */
  (FunctionalState)ENC_INVERT_SPEED, /*!< To be enabled if measured speed is opposite
                              to real one (ENABLE/DISABLE)*/
  
  10*MEDIUM_FREQUENCY_TASK_RATE, /*!< Frequency (01Hz) at which motor speed is to be
                                   computed. It must be equal to the frequency
                                   at which function SPD_CalcAvrgMecSpeed01Hz
                                   is called.*/
  
  ENC_AVERAGING_FIFO_DEPTH,  /*!< Size of the buffer used to calculate the average 
                             speed. It must be <= 16.*/
  
  ENC_IC_FILTER,	   /*!< Time filter applied to validate ENCODER sensor
                                capture. This value defines the frequency 
                                used to sample ENCODER sensors input and the 
                                length of the digital filter applied. 
                                The digital filter is made of an event 
                                counter in which N events are needed to 
                                validate a transition on the input.
                                0000: No filter, sampling is done at fCK_INT.
                                0001: fSAMPLING=fCK_INT , N=2. 
                                0010: fSAMPLING=fCK_INT , N=4.
                                0011: fSAMPLING=fCK_INT , N=8. 
                                0100: fSAMPLING=fCK_INT/2, N=6.
                                0101: fSAMPLING=fCK_INT/2, N=8.
                                0110: fSAMPLING=fCK_INT/4, N=6.
                                0111: fSAMPLING=fCK_INT/4, N=8.
                                1000: fSAMPLING=fCK_INT/8, N=6.
                                1001: fSAMPLING=fCK_INT/8, N=8.
                                1010: fSAMPLING=fCK_INT/16, N=5.
                                1011: fSAMPLING=fCK_INT/16, N=6.
                                1100: fSAMPLING=fCK_INT/16, N=8.
                                1101: fSAMPLING=fCK_INT/32, N=5.
                                1110: fSAMPLING=fCK_INT/32, N=6.
                                1111: fSAMPLING=fCK_INT/32, N=8 */
  /* HW Settings */
  ENC_TIMER,	    /*!< Timer used for ENCODER sensor management.*/
  
  ENC_RCC_PERIPHERAL,        /*!< RCC Clock related to timer TIMx. 
                                     (Ex. RCC_APB1Periph_TIM2).*/
  
  ENC_IRQ_CHANNEL,        /*!< IRQ Channel related to TIMx. 
                                (Ex. TIM2_IRQChannel).*/
  
  ENC_TIMER_REMAPPING,		 /*!< It remaps TIMx outputs. It must equal to 
                                GPIO_PartialRemap_TIMx, GPIO_FullRemap_TIMx or 
                                GPIO_NoRemap_TIMx according the HW availability*/
  
  ENC_A_GPIO_PORT,        /*!< ENCODER sensor A channel GPIO input port (if used, 
                              after re-mapping). It must be GPIOx x= A, B, ...*/
  
  ENC_A_GPIO_PIN,       /*!< ENCODER sensor A channel GPIO input pin (if used, 
                              after re-mapping). It must be GPIO_Pin_x x=0,1,.*/
  
  ENC_B_GPIO_PORT,	 /*!< ENCODER sensor B channel GPIO input port (if used, 
                              after re-mapping). It must be GPIOx x= A, B, ...*/
  
  ENC_B_GPIO_PIN,       /*!< ENCODER sensor B channel GPIO input pin (if used, 
                              after re-mapping). It must be GPIO_Pin_x x= 0,1,.*/
  
};

/** 
  * @brief  Encoder Alignment Controller parameters Motor 1
  */
EncAlignCtrlParams_t EncAlignCtrlParamsM1 =
{
  MEDIUM_FREQUENCY_TASK_RATE, /*!< Frequency
                                 expressed in Hz at which the user 
                                 clocks the EAC calling EAC_Exec method */
  FINAL_I_ALIGNMENT,              /*!< Motor torque reference imposed by STC at the 
                                 end of programmed alignment. This value 
                                 represents actually the Iq current expressed in
                                 digit.*/
  ALIGNMENT_ANGLE_S16,      /*!< Mechanical angle of programmed alignment 
                                 expressed in s16degrees.*/
  T_ALIGNMENT               /*!< Duration of the programmed alignment expressed
                                 in milliseconds.*/
};

/** 
  * @brief  SpeedNPosition sensor parameters Motor 1 - HALL
  */
HALLParams_t HALLParamsM1 =
{
  /* SW Settings */
  MC_IRQ_SPEEDNPOSFDBK_1,   /*!< MC IRQ number used for TIMx capture update event.*/

  HALL_SENSORS_PLACEMENT,  
                        /*!< Define here the mechanical position of the sensors 
                             with reference to an electrical cycle.
                             Allowed values are: DEGREES_120 or DEGREES_60.*/
  
  (int16_t)(HALL_PHASE_SHIFT * 65536/360),  
                        /*!< Define here in s16degree the electrical phase shift 
                             between the low to high transition of signal H1 and
                             the maximum of the Bemf induced on phase A.*/
  
  MEDIUM_FREQUENCY_TASK_RATE, /*!< Frequency (Hz) at which motor speed is to 
                             be computed. It must be equal to the frequency
                             at which function SPD_CalcAvrgMecSpeed01Hz
                             is called.*/
  
  HALL_AVERAGING_FIFO_DEPTH,  /*!< Size of the buffer used to calculate the average 
                             speed. It must be less than 18.*/
  
  HALL_IC_FILTER,         /*!< Time filter applied to validate HALL sensor capture.
                             This value defines the frequency used to sample 
                             HALL sensors input and the length of the digital
                             filter applied. The digital filter is made of an 
                             event counter in which N events are needed to 
                             validate a transition on the input.
                                0000: No filter, sampling is done at fCK_INT.
                                0001: fSAMPLING=fCK_INT , N=2. 
                                0010: fSAMPLING=fCK_INT , N=4.
                                0011: fSAMPLING=fCK_INT , N=8. 
                                0100: fSAMPLING=fCK_INT/2, N=6.
                                0101: fSAMPLING=fCK_INT/2, N=8.
                                0110: fSAMPLING=fCK_INT/4, N=6.
                                0111: fSAMPLING=fCK_INT/4, N=8.
                                1000: fSAMPLING=fCK_INT/8, N=6.
                                1001: fSAMPLING=fCK_INT/8, N=8.
                                1010: fSAMPLING=fCK_INT/16, N=5.
                                1011: fSAMPLING=fCK_INT/16, N=6.
                                1100: fSAMPLING=fCK_INT/16, N=8.
                                1101: fSAMPLING=fCK_INT/32, N=5.
                                1110: fSAMPLING=fCK_INT/32, N=6.
                                1111: fSAMPLING=fCK_INT/32, N=8 */
								
  /* HW Settings */
  HALL_TIM_CLK,          /*!< Timer clock frequency express in Hz.*/

  HALL_TIMER,        /*!< Timer used for HALL sensor management.*/
  
  HALL_RCC_PERIPHERAL, 
                        /*!< RCC Clock related to timer TIMx. 
                             (Ex. RCC_APB1Periph_TIM2).*/
  
  HALL_IRQ_CHANNEL,            /*!< IRQ Channle related to TIMx. 
                             (Ex. TIM2_IRQChannel).*/
  
  HALL_TIMER_REMAPPING, 
                        /*!< It remaps TIMx outputs. It must equal to 
                             GPIO_PartialRemap_TIMx, GPIO_FullRemap_TIMx or 
                             GPIO_NoRemap_TIMx according the HW availability.*/
  
  H1_GPIO_PORT, 
                        /*!< HALL sensor H1 channel GPIO input port (if used, 
                             after re-mapping). It must be GPIOx x= A, B, ...*/
  
  H1_GPIO_PIN,           /*!< HALL sensor H1 channel GPIO output pin (if used, 
                             after re-mapping). It must be GPIO_Pin_x x= 0, 1, 
                             ...*/
  
  H2_GPIO_PORT, 
                        /*!< HALL sensor H2 channel GPIO input port (if used, 
                             after re-mapping). It must be GPIOx x= A, B, ...*/
  
  H2_GPIO_PIN,           /*!< HALL sensor H2 channel GPIO output pin (if used, 
                             after re-mapping). It must be GPIO_Pin_x x= 0, 1, 
                             ...*/
  
  H3_GPIO_PORT, 
                        /*!< HALL sensor H3 channel GPIO input port (if used, 
                             after re-mapping). It must be GPIOx x= A, B, ...*/
  
  H3_GPIO_PIN            /*!< HALL sensor H3 channel GPIO output pin (if used, 
                             after re-mapping). It must be GPIO_Pin_x x= 0, 1, 
                             ...*/
};
/** 
  * @brief  Real Bus Voltage sensor parameters Motor 1 - Base class
  */
BusVoltageSensorParams_t RealBusVoltageSensorParamsM1 =
{
  REAL_SENSOR,                   /*!< It contains the information about the type 
                                   of instanced bus voltage sensor object.  
                                   It can be equal to REAL_SENSOR or 
                                   VIRTUAL_SENSOR */
  (uint16_t)(3.3/BUS_ADC_CONV_RATIO),  /*!< It is used to convert bus voltage from 
                                   u16Volts into real Volts (V). 
                                   1 u16Volt = 65536/hConversionFactor Volts
                                   For real sensors hConversionFactor it's 
                                   equal to the product between the expected MCU
                                   voltage and the partioning network 
                                   attenuation. For virtual sensors it is
                                   assumed to be equal to 500 */
};

/** 
  * @brief  Virtual Bus Voltage sensor parameters Motor 1 - Base class
  */
BusVoltageSensorParams_t VirtualBusVoltageSensorParamsM1 =
{
  VIRTUAL_SENSOR,                   /*!< It contains the information about the type 
                                   of instanced bus voltage sensor object.  
                                   It can be equal to REAL_SENSOR or 
                                   VIRTUAL_SENSOR */
  500                              /*!< It is used to convert bus voltage from 
                                   u16Volts into real Volts (V). 
                                   1 u16Volt = 65536/hConversionFactor Volts
                                   For real sensors hConversionFactor it's 
                                   equal to the product between the expected MCU
                                   voltage and the partioning network 
                                   attenuation. For virtual sensors it is
                                   assumed to be equal to 500 */
};

/** 
  * @brief  Bus Voltage sensor parameters Motor 1 - Rdivider
  */
RdividerParams_t RdividerParamsM1 =
{
  VBUS_CHANNEL,                    /*!< ADC channel used for conversion of 
                                         bus voltage. It must be equal to  
                                         ADC_Channel_x x= 0, ..., 15*/
  VBUS_GPIO_PORT,                  /*!< GPIO port used by bVbusADChannel. 
                                         It must be equal to GPIOx x= A, B, ...*/                                                                             
  VBUS_GPIO_PIN,                   /*!< GPIO pin used by bVbusChannel. It must  
                                         be equal to GPIO_Pin_x x= 0, 1, ...*/ 
  VBUS_SAMPLING_TIME,         /*!< Sampling time used for bVbusChannel AD
                                         conversion. It must be equal to  
                                         ADC_SampleTime_xCycles5 x= 1, 7, ...*/  
  VBUS_SW_FILTER_BW_FACTOR,         /*!< Use this number to configure the Vbus 
                                         first order software filter bandwidth. 
                                         hLowPassFilterBW = VBS_CalcBusReading 
                                         call rate [Hz]/ FilterBandwidth[Hz] */   
  OVERVOLTAGE_THRESHOLD_d,          /*!< It represents the over voltage protection
                                         intervention threshold. To be expressed 
                                         in digit through formula:
                                         hOverVoltageThreshold (digit) = 
                                         Over Voltage Threshold (V) * 65536 
                                                          / hConversionFactor */
  UNDERVOLTAGE_THRESHOLD_d,        /*!< It represents the under voltage protection
                                         intervention threshold. To be expressed 
                                         in digit through formula:                                         
                                         hUnderVoltageThreshold (digit) = 
                                         Under Voltage Threshold (V) * 65536 
                                                          / hConversionFactor */
};

/** 
  * @brief  Virtual Bus Voltage sensor parameters Motor 1 - VirtualParams
  */
VirtualParams_t VirtualBusParamsM1 =
{
  1+(NOMINAL_BUS_VOLTAGE_V*65536)/500 /*!< Expected Vbus voltage expressed in 
                                           digit*/ 
};




/** 
  * @brief  Real temperature sensor parameters Motor 1 - Base class  
  */
TempSensorParams_t RealTempSensorParamsM1 =
{
  REAL_SENSOR,                   /*!< It contains the information about the type 
                                   of instanced temperature sensor object.  
                                   It can be equal to REAL_SENSOR or 
                                   VIRTUAL_SENSOR */
};

/** 
  * @brief  Virtual temperature sensor parameters Motor 1 - Base class  
  */
TempSensorParams_t VirtualTempSensorParamsM1 =
{
  VIRTUAL_SENSOR,                   /*!< It contains the information about the type 
                                   of instanced temperature sensor object.  
                                   It can be equal to REAL_SENSOR or 
                                   VIRTUAL_SENSOR */
};

/** 
  * @brief  Temperature sensor parameters Motor 1 - NTC  
  */
NTCParams_t NTCParamsM1 =
{
  TEMP_FDBK_CHANNEL,                       /*!< ADC channel used for conversion of 
                                         bus voltage. It must be equal to  
                                         ADC_Channel_x x= 0, ..., 15*/
  TEMP_FDBK_GPIO_PORT,                                 /*!< GPIO port used by bVbusADChannel. 
                                         It must be equal to GPIOx x= A, B, ...*/                                                                             
  TEMP_FDBK_GPIO_PIN,                       /*!< GPIO pin used by bVbusChannel. It must  
                                         be equal to GPIO_Pin_x x= 0, 1, ...*/ 
  TEMP_SAMPLING_TIME,         /*!< Sampling time used for bVbusChannel AD
                                         conversion. It must be equal to  
                                         ADC_SampleTime_xCycles5 x= 1, 7, ...*/  
  TEMP_SW_FILTER_BW_FACTOR,       /*!< Use this number to configure the   
                                         temperature first order software filter
                                         bandwidth                                                                                
                                         hLowPassFilterBW = TSNS_CalcBusReading 
                                         call rate [Hz]/ FilterBandwidth[Hz] */
  (uint16_t)(OV_TEMPERATURE_THRESHOLD_d),/*!< It represents the over voltage protection 
                                         intervention threshold. To be expressed 
                                         in u16Celsius through formula:
                                         hOverTempThreshold [u16Celsius] = 
                                         (V0[V]+dV/dT[V/°C]*(OverTempThreshold[°C] 
                                          - T0[°C]))* 65536 / MCU supply voltage */
  (uint16_t)(OV_TEMPERATURE_THRESHOLD_d - OV_TEMPERATURE_HYSTERESIS_d), 
					 /*!< It represents the temperature 
                                         expressed in u16Celsius below which an 
                                         active over temperature fault is cleared
                                         hOverTempDeactThreshold[u16Celsius]=
                                         (V0[V]+dV/dT[V/°C]*(OverTempDeactThresh[°C] 
                                          - T0[°C]))* 65536 / MCU supply voltage*/
  (uint16_t)(MCU_SUPPLY_VOLTAGE/dV_dT),         /*!< It is equal to MCU supply voltage [V] /
                                          dV/dT [V/°C] and represents the NTC 
                                          sensitivity */
  (uint16_t)(V0_V *65536/ MCU_SUPPLY_VOLTAGE), /*!< It is equal to V0*65536/MCU supply 
                                          voltage where V0 is used to convert the 
                                          temperature into Volts 
                                          V[V]=V0+dV/dT[V/°C]*(T-T0)[°C]      */
  T0_C,                                /*!< It is equal to T0 [°C], used to convert 
                                          the temperature into Volts 
                                          V[V]=V0+dV/dT[V/°C]*(T-T0)[°C]*/
};

/** 
  * @brief  Temperature sensor parameters Motor 1 - NTC  
  */
VirtualTParams_t VirtualTParamsM1=
{
  555,  /*!< Value returned by base class method TSNS_GetAvTemp_d */
  VIRTUAL_HEAT_SINK_TEMPERATURE_VALUE   /*!< Expected temperature in degrees 
                                        (value returned by base class 
                                        method TSNS_GetAvTemp_C) */
};




/** 
  * @brief  FOCDrive class parameters Motor 1 - Base Class  
  */
FOCDriveParams_t FOCDriveParamsM1 =
{
  MAX_MODULE,                           /*!< Circle limitation maximum allowed 
                                          module */
  MMITABLE,                             /*!< Circle limitation table */
  START_INDEX,                          /*!< Circle limitation table indexing 
                                           start */
  0,            /*!< FOC object instance number, only used
                                           for multiple motor control */                                           
};

/** 
  * @brief  SMF_PMSM class parameters Motor 1 - Derived Class
  */
SMF_PMSMParams_t SMF_PMSMParamsM1 = 
{
  (int16_t)FW_VOLTAGE_REF,     /*!< Default flux weakening voltage reference,
                                       tenth of percentage points*/
  ID_DEMAG,                     /*!< Demagnetization current in s16A: 
                                    Current(Amp) = [Current(s16A) * Vdd micro]/ 
                                    [65536 * Rshunt * Aop] */
  ((int32_t)NOMINAL_CURRENT*(int32_t)NOMINAL_CURRENT), /*!< Squared motor nominal current in (s16A)^2 
                                       where: 
                                     Current(Amp) = [Current(s16A) * Vdd micro]/ 
                                     [65536 * Rshunt * Aop] */
  VQD_SW_FILTER_BW_FACTOR,       /*!< Use this parameter to configure the Vqd 
                                      first order software filter bandwidth. 
                                      hVqdLowPassFilterBW = FOC_CurrController 
                                      call rate [Hz]/ FilterBandwidth[Hz] in 
                                      case FULL_MISRA_COMPLIANCY is defined. 
                                      On the contrary, if FULL_MISRA_COMPLIANCY 
                                      is not defined, hVqdLowPassFilterBW is 
                                      equal to log with base two of previous 
                                      definition */  
};

/** 
  * @brief  IMF_PMSM class parameters Motor 1 - Derived Class
  */
IMF_PMSMParams_t IMF_PMSMParamsM1 = 
{
  /* MTPA parameters */
  (int16_t)SEGDIV,        /*!< Segment divisor */
  ANGC,                   /*!< Angular coefficients table */
  OFST,                   /*!< Offsets table */
  
  /* Flux Weakening parameters */
  (int16_t)FW_VOLTAGE_REF,    /*!< Default flux weakening voltage reference,
                                  tenth of percentage points*/  
  ID_DEMAG,                   /*!< Demagnetization current in s16A: 
                                    Current(Amp) = [Current(s16A) * Vdd micro]/ 
                                    [65536 * Rshunt * Aop] */
 (int32_t)NOMINAL_CURRENT * (int32_t)NOMINAL_CURRENT, /*!< Squared motor nominal current in (s16A)^2 
                                      where: 
                                    Current(Amp) = [Current(s16A) * Vdd micro]/ 
                                    [65536 * Rshunt * Aop] */
  VQD_SW_FILTER_BW_FACTOR       /*!< Use this parameter to configure the Vqd 
                                      first order software filter bandwidth. 
                                      hVqdLowPassFilterBW = FOC_CurrController 
                                      call rate [Hz]/ FilterBandwidth[Hz] in 
                                      case FULL_MISRA_COMPLIANCY is defined. 
                                      On the contrary, if FULL_MISRA_COMPLIANCY 
                                      is not defined, hVqdLowPassFilterBW is 
                                      equal to log with base two of previous 
                                      definition */
};

/** 
  * @brief  IMFF_PMSM class parameters Motor 1 - Derived Class
  */
IMFF_PMSMParams_t IMFF_PMSMParamsM1 =
{
  /* MTPA parameters */
  (int16_t)SEGDIV,               /*!< Segment divisor */
  ANGC,                          /*!< Angular coefficients table */
  OFST,                          /*!< Offsets table */

  /* Flux Weakening parameters */
  (int16_t)FW_VOLTAGE_REF,   /*!< Default flux weakening voltage reference,
                                  tenth of percentage points*/
  ID_DEMAG,                   /*!< Demagnetization current in s16A: 
                                    Current(Amp) = [Current(s16A) * Vdd micro]/ 
                                    [65536 * Rshunt * Aop] */
 (int32_t)NOMINAL_CURRENT * (int32_t)NOMINAL_CURRENT,       /*!< Squared motor nominal current in (s16A)^2 
                                      where: 
                                    Current(Amp) = [Current(s16A) * Vdd micro]/ 
                                    [65536 * Rshunt * Aop] */
  VQD_SW_FILTER_BW_FACTOR,       /*!< Use this parameter to configure the Vqd 
                                      first order software filter bandwidth. 
                                      hVqdLowPassFilterBW = FOC_CurrController 
                                      call rate [Hz]/ FilterBandwidth[Hz] in 
                                      case FULL_MISRA_COMPLIANCY is defined. 
                                      On the contrary, if FULL_MISRA_COMPLIANCY 
                                      is not defined, hVqdLowPassFilterBW is 
                                      equal to log with base two of previous 
                                      definition */ 
  (int32_t)CONSTANT1_D,          /*!< Feed forward constant for d axes */
  (int32_t)CONSTANT1_Q,          /*!< Feed forward constant for q axes */
  (int32_t)CONSTANT2_QD          /*!< Constant used by Feed-Forward algorithm*/
};


OL_FOCParams_t OpenLoopFOC_ParamsM1=
{
  OPEN_LOOP_VOLTAGE_d
};


DigitalOutputParams_t R_BrakeParamsM1 =
{
  R_BRAKE_GPIO_PORT,       /*!< GPIO output port. It must be equal
		                      	to GPIOx x= A, B, ...*/
  R_BRAKE_GPIO_PIN,        /*!< GPIO output pin. It must be equal to
                              	GPIO_Pin_x x= 0, 1, ...*/  
  DISSIPATIVE_BRAKE_POLARITY /*!< GPIO output polarity. It must be equal 
                               	to DOutputActiveHigh or DOutputActiveLow */ };

DigitalOutputParams_t DOUT_OCPDisablingParamsM1 =
{
  OV_CURR_BYPASS_GPIO_PORT,       /*!< GPIO output port. It must be equal
			                          to GPIOx x= A, B, ...*/
  OV_CURR_BYPASS_GPIO_PIN,        /*!< GPIO output pin. It must be equal to
                                   	   GPIO_Pin_x x= 0, 1, ...*/  
  OVERCURR_FEEDBACK_POLARITY      /*!< GPIO output polarity. It must be equal 
                                   	   to DOutputActiveHigh or DOutputActiveLow */ 
};

PQDParams_t PQD_MotorPowerMeasurementParamsM1 =
{
  PQD_CONVERSION_FACTOR/*!< It is the conversion factor used to convert the 
                           variables expressed in digit into variables expressed 
                           in physical measurement unit. It is used to convert
                           the power in watts. It must be equal to 
                           (1000 * 3 * Vddµ)/(sqrt(3) * CurrentAmpGain) */
};

PQDParams_t PQD_MotorPowerMeasurementParamsM2 =
{
  PQD_CONVERSION_FACTOR2/*!< It is the conversion factor used to convert the 
                           variables expressed in digit into variables expressed 
                           in physical measurement unit. It is used to convert
                           the power in watts. It must be equal to 
                           (1000 * 3 * Vddµ)/(sqrt(3) * Rshunt * Aop) */
};

#endif /* __SYSTEMNDRIVE_PARAMS_H */
/******************* (C) COPYRIGHT 2011 STMicroelectronics *****END OF FILE****/
