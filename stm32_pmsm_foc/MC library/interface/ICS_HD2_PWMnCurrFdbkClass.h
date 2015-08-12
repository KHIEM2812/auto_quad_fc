/**
  ******************************************************************************
  * @file    ICS_HD2_PWMnCurrFdbkClass.h
  * @author  IMS Systems Lab and Technical Marketing - MC Team
  * @version 3.0
  * @date    05-Apr-2011 11:34
  * @brief   This file contains interface of ICS_HD2 class      
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
#ifndef __ICS_HD2_PWMNCURRFDBKCLASS_H
#define __ICS_HD2_PWMNCURRFDBKCLASS_H


#define GPIO_NoRemap_TIM1 ((uint32_t)(0))
#define SHIFTED_TIMs      ((uint8_t) 1)
#define NO_SHIFTED_TIMs   ((uint8_t) 0)
#define HIGHER_FREQ        ((uint8_t) 1)
#define LOWER_FREQ         ((uint8_t) 2)

/** @addtogroup STM32F10x_PMSM_MC_Library
  * @{
  */
  
/** @addtogroup PWMnCurrFdbk_ICS_HD2
  * @{
  */

/** @defgroup ICS_HD2_class_exported_types ICS_HD2 class exported types
* @{
*/

/** 
  * @brief  Public ICS_HD2 class definition
  */
typedef struct CIHD2_PWMC_t *CIHD2_PWMC;

/** 
  * @brief  ICS_HD2 class parameters definition
  */
typedef const struct
{
  uint32_t wADC_Clock_Divider;       /*!< APB2 clock prescaling factor for 
                                          ADC peripheral. It must be RCC_PCLK2_DivX
                                          x = 2, 4, 6, 8 */  
  
/* Dual MC parameters --------------------------------------------------------*/ 
  uint8_t bInstanceNbr;              /*!< Instance number with reference to PWMC  
                                          base class. It is necessary to properly
                                          synchronize TIM8 with TIM1 at 
                                          peripheral initializations */ 
  uint16_t Tw;                       /*!< It is used for switching the context 
                                           in dual MC. It contains biggest delay
                                           (expressed in counter ticks) between 
                                           the counter crest and ADC latest 
                                           trigger  */
  uint8_t  bFreqRatio;               /*!< It is used in case of dual MC to 
                                           synchronize TIM1 and TIM8. It has 
                                           effect only on the second instanced 
                                           object and must be equal to the 
                                           ratio between the two PWM frequencies
                                           (higher/lower). Supported values are 
                                           1, 2 or 3 */  
  uint8_t  bIsHigherFreqTim;         /*!< When bFreqRatio is greather than 1
                                          this param is used to indicate if this 
                                          instance is the one with the highest 
                                          frequency. Allowed value are: HIGHER_FREQ
                                          or LOWER_FREQ */
  uint8_t  IRQnb;                    /*!< MC IRQ number used as TIMx Update 
                                           event */
/* Current reading A/D Conversions initialization -----------------------------*/ 
  uint8_t bIaChannel;                  /*!< ADC channel used for conversion of 
                                           current Ia. It must be equal to  
                                           ADC_Channel_x x= 0, ..., 15*/
  GPIO_TypeDef* hIaPort;                /*!< GPIO port used by bIaChannel. It must 
                                           be equal to GPIOx x= A, B, ...*/
  uint16_t hIaPin;                      /*!< GPIO pin used by bIaChannel. It must be 
                                          equal to GPIO_Pin_x x= 0, 1, ...*/ 
  uint8_t b_IaSamplingTime;            /*!< Sampling time used to convert bIaChannel. 
                                          It must be equal to ADC_SampleTime_xCycles5 
                                          x= 1, 7, ...*/ 
  uint8_t bIbChannel;                  /*!< ADC channel used for conversion of 
                                           current Ib. It must be equal to 
                                           ADC_Channel_x x= 0, ..., 15*/  
  GPIO_TypeDef* hIbPort;                /*!< GPIO port used by bIbChannel. It must 
                                           be equal to GPIOx x= A, B, ...*/
  uint16_t hIbPin;                      /*!< GPIO pin used by bIbChannel. It must be 
                                          equal to GPIO_Pin_x x= 0, 1, ...*/
  uint8_t b_IbSamplingTime;               /*!< Sampling time used to convert bIbChannel. 
                                          It must be equal to ADC_SampleTime_xCycles5 
                                          x= 1, 7, ...*/ 
  
/* PWM generation parameters --------------------------------------------------*/   
  uint16_t hDeadTime;                  /*!< Dead time in number of TIM clock
                                            cycles. If CHxN are enabled, it must
                                            contain the dead time to be generated
                                            by the microcontroller, otherwise it 
                                            expresses the maximum dead time 
                                            generated by driving network */
  uint8_t  bRepetitionCounter;         /*!< It expresses the number of PWM 
                                           periods to be elapsed before compare 
                                           registers are updated again. In 
                                           particular: 
                                           RepetitionCounter= (2* #PWM periods)-1
                                         */   
  TIM_TypeDef*  TIMx;                   /*!< It contains the pointer to the timer 
                                           used for PWM generation. It must 
                                           equal to TIM1 if bInstanceNbr is 
                                           equal to 1, to TIM8 otherwise */
/* PWM Driving signals initialization ----------------------------------------*/  

  uint32_t wTIM1Remapping;            /*!< Used only for TIM1, it 
                                           remaps its outputs. It must equal to 
                                           GPIO_PartialRemap_TIM1 or 
                                           GPIO_FullRemap_TIM1 or
                                           GPIO_NoRemap_TIM1 */
  uint16_t hCh1Polarity;              /*!< Channel 1 (high side) output polarity, 
                                           it must be TIM_OCPolarity_High or 
                                           TIM_OCPolarity_Low */
  GPIO_TypeDef* hCh1Port;               /*!< Channel 1 (high side) GPIO output 
                                         port (if used, after re-mapping). 
                                         It must be GPIOx x= A, B, ...*/
  uint16_t hCh1Pin;                    /*!< Channel 1 (high side) GPIO output pin 
                                          (if used, after re-mapping). It must be 
                                          GPIO_Pin_x x= 0, 1, ...*/  
  uint16_t hCh1IdleState;              /*!< Channel 1 (high side) state (low or high)
                                            when TIM peripheral is in Idle state.
                                            It must be TIM_OCIdleState_Set or
                                            TIM_OCIdleState_Reset*/  
  
  
  uint16_t hCh2Polarity;               /*!< Channel 2 (high side) output polarity, 
                                           it must be TIM_OCPolarity_High or 
                                           TIM_OCPolarity_Low */ 
  GPIO_TypeDef* hCh2Port;               /*!< Channel 2 (high side) GPIO output 
                                           port (if used, after re-mapping). 
                                           It must be GPIOx x= A, B, ...*/
  uint16_t hCh2Pin;                    /*!< Channel 2 (high side) GPIO output pin 
                                          (if used, after re-mapping). It must be 
                                          GPIO_Pin_x x= 0, 1, ...*/
  uint16_t hCh2IdleState;              /*!< Channel 2 (high side) state (low or high)
                                            when TIM peripheral is in Idle state.
                                            It must be TIM_OCIdleState_Set or
                                            TIM_OCIdleState_Reset*/    
 
  uint16_t hCh3Polarity;       /*!< Channel 3 (high side) output polarity, 
                                           it must be TIM_OCPolarity_High or 
                                           TIM_OCPolarity_Low */  
  GPIO_TypeDef* hCh3Port;               /*!< Channel 3 (high side) GPIO output 
                                           port (if used, after re-mapping). 
                                           It must be GPIOx x= A, B, ...*/
  uint16_t hCh3Pin;                    /*!< Channel 3 (high side) GPIO output pin 
                                          (if used, after re-mapping). It must be 
                                          GPIO_Pin_x x= 0, 1, ...*/  
  uint16_t hCh3IdleState;              /*!< Channel 3 (high side) state (low or high)
                                            when TIM peripheral is in Idle state.
                                            It must be TIM_OCIdleState_Set or
                                            TIM_OCIdleState_Reset*/  
  
  FunctionalState LowSideOutputs;       /*!< It enable/disable the PWM low side  
                                          driving signals. It must be either 
                                          equal to ENABLE or DISABLE */ 
  
  uint16_t hCh1NPolarity;               /*!< Channel 1N (low side) output polarity, 
                                           it must be TIM_OCNPolarity_High or 
                                           TIM_OCNPolarity_Low */
  GPIO_TypeDef* hCh1NPort;               /*!< Channel 1N (low side) GPIO output 
                                           port (if used, after re-mapping). 
                                           It must be GPIOx x= A, B, ...*/
  uint16_t hCh1NPin;                    /*!< Channel 1N (low side) GPIO output pin 
                                          (if used, after re-mapping). It must be 
                                          GPIO_Pin_x x= 0, 1, ...*/ 
  uint16_t hCh1NIdleState;              /*!< Channel 1N (low side) state (low or high)
                                            when TIM peripheral is in Idle state.
                                            It must be TIM_OCNIdleState_Set or
                                            TIM_OCNIdleState_Reset*/ 

  
  uint16_t hCh2NPolarity;                 /*!< Channel 2N (low side) output polarity, 
                                           it must be TIM_OCNPolarity_High or 
                                           TIM_OCNPolarity_Low */
  GPIO_TypeDef* hCh2NPort;               /*!< Channel 2N (low side) GPIO output 
                                           port (if used, after re-mapping). 
                                           It must be GPIOx x= A, B, ...*/
  uint16_t hCh2NPin;                     /*!< Channel 2N (low side) GPIO output pin 
                                          (if used, after re-mapping). It must be 
                                          GPIO_Pin_x x= 0, 1, ...*/ 
  uint16_t hCh2NIdleState;              /*!< Channel 2N (low side) state (low or high)
                                            when TIM peripheral is in Idle state.
                                            It must be TIM_OCNIdleState_Set or
                                            TIM_OCNIdleState_Reset*/ 
  
  uint16_t hCh3NPolarity;          /*!< Channel 3N (low side) output polarity, 
                                           it must be TIM_OCNPolarity_High or 
                                           TIM_OCNPolarity_Low */
  GPIO_TypeDef* hCh3NPort;               /*!< Channel 3N (low side)  GPIO output 
                                           port (if used, after re-mapping). 
                                           It must be GPIOx x= A, B, ...*/
  uint16_t hCh3NPin;                    /*!< Channel 3N (low side)  GPIO output pin 
                                          (if used, after re-mapping). It must be 
                                          GPIO_Pin_x x= 0, 1, ...*/   
  uint16_t hCh3NIdleState;              /*!< Channel 3N (low side) state (low or high)
                                            when TIM peripheral is in Idle state.
                                            It must be TIM_OCNIdleState_Set or
                                            TIM_OCNIdleState_Reset*/ 
/* Emergency input signal initialization -------------------------------------*/  
  FunctionalState EmergencyStop;        /*!< It enable/disable the management of 
                                            an emergency input instantaneously 
                                            stopping PWM generation. It must be 
                                            either equal to ENABLE or DISABLE */  
  uint16_t hBKINPolarity;               /*!< Emergency Stop (BKIN) input polarity, 
                                           it must be TIM_BreakPolarity_Low or 
                                           TIM_BreakPolarity_High */
  GPIO_TypeDef* hBKINPort;               /*!< Emergency Stop (BKIN) GPIO input 
                                           port (if used, after re-mapping). 
                                           It must be GPIOx x= A, B, ...*/
  uint16_t hBKINPin;                    /*!< Emergency Stop (BKIN) GPIO input pin 
                                          (if used, after re-mapping). It must be 
                                          GPIO_Pin_x x= 0, 1, ...*/     
}ICS_HD2Params_t, *pICS_HD2Params_t;
/**
  * @}
  */

/** @defgroup ICS_HD2_class_exported_methods ICS_HD2 class exported 
  *           methods
  * @{
  */
  
/**
  * @brief  Creates an object of the class ICS_HD2
  * @param  pPWMnCurrFdbkParams pointer to an PWMnCurrFdbk parameters structure
  * @param  pICS_HD2Params pointer to an ICS_HD2 parameters structure
  * @retval CIHD2_PWMC new instance of ICS_HD2 object
  */
CIHD2_PWMC IHD2_NewObject(pPWMnCurrFdbkParams_t pPWMnCurrFdbkParams, 
                                              pICS_HD2Params_t pICS_HD2Params);

/**
  * @brief  It perform the start of all the timers required by the control. 
            It utilizes TIM2 as temporary timer to achieve synchronization between 
            PWM signals.
            When this function is called, TIM1 and/or TIM8 must be in frozen state
            with CNT, ARR, REP RATE and trigger correctly set (these setting are 
            usually performed in the Init method accordingly with the configuration)
  * @param  none
  * @retval none
  */
void IHD2_StartTimers(void);

/**
  * @}
  */
  
/**
  * @}
  */

/**
  * @}
  */

#endif /*__ICS_HD2_PWMNCURRFDBKCLASS_H*/

/******************* (C) COPYRIGHT 2011 STMicroelectronics *****END OF FILE****/