/**
  ******************************************************************************
  * @file    Control stage parameters.h
  * @author  ST Motor Control Workbench ver.0.9.11.0
  * @version 3.0
  * @date    05-Apr-2011 11:34
  * @brief   This file contains motor parameters needed by STM32 PMSM MC FW  
  *                 library v3.0
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
#ifndef __CONTROL_STAGE_PARAMETERS_H
#define __CONTROL_STAGE_PARAMETERS_H

/***************************** MCU SELECTION SECTION **************************/
#define STM32PERFORMANCEMD  /* STM32PERFORMANCEMD or STM32VALUELD or STM32VALUEMD or 
                                          STM32PERFORMANCEHD*/
#define PACKAGE_SELECTION     LQFP100   /*VFQFPN36, VFQFPN48, LQFP48, LQFP64,  
                                                 LQFP100, LQFP144, WLCSP64, LFBGA100, 
                                                 LFBGA144, BGA100, BGA64, TFBGA64*/
/***************************** MCU supply voltage *****************************/
#define MCU_SUPPLY_VOLTAGE    3.30

/***************************** CLOCK SETTINGS SECTION *************************/
#define CLOCK_SOURCE          EXTERNAL  /* EXTERNAL or INTERNAL */

/* #define CPU_CLK_24_MHZ */
/* #define CPU_CLK_48_MHZ */
/* #define CPU_CLK_56_MHZ */
#define CPU_CLK_72_MHZ

                         
/************************ DIGITAL I/O DEFINITION SECTION  *********************/
/* PWM Timer section */
#define PWM_TIMER_SELECTION               PWM_TIM1 /* PWM_TIM1 or PWM_TIM8 */ 
#define PWM_TIMER_REMAPPING               PWM_FULL_REMAP /* PWM_NO_REMAP,  
                                                           PWM_FULL_REMAP, 
                                                           PWM_PARTIAL_REMAP */
#define PHASE_UH_GPIO_PORT                GPIOE                                                                            
#define PHASE_UH_GPIO_PIN                 GPIO_Pin_9                                                                        
#define PHASE_VH_GPIO_PORT                GPIOE                                                                                                                                                    
#define PHASE_VH_GPIO_PIN                 GPIO_Pin_11
#define PHASE_WH_GPIO_PORT                GPIOE                                                                         
#define PHASE_WH_GPIO_PIN                 GPIO_Pin_13
#define PHASE_UL_GPIO_PORT                GPIOE                                                                        
#define PHASE_UL_GPIO_PIN                 GPIO_Pin_8
#define PHASE_VL_GPIO_PORT                GPIOE                                                                
#define PHASE_VL_GPIO_PIN                 GPIO_Pin_10
#define PHASE_WL_GPIO_PORT                GPIOE                                                        
#define PHASE_WL_GPIO_PIN                 GPIO_Pin_12
#define EMERGENCY_STOP_GPIO_PORT          GPIOE
#define EMERGENCY_STOP_GPIO_PIN           GPIO_Pin_15

/* Hall timer section */
#define HALL_TIMER_SELECTION              HALL_TIM2  /* HALL_TIM2...HALL_TIM5 */ 
#define HALL_TIMER_REMAPPING              NO_REMAP_TIM2  /* NO_REMAP, FULL_REMAP, 
                                                            PARTIAL_REMAP */
#define H1_GPIO_PORT                      GPIOA
#define H2_GPIO_PORT                      GPIOA
#define H3_GPIO_PORT                      GPIOA

#define H1_GPIO_PIN                       GPIO_Pin_0
#define H2_GPIO_PIN                       GPIO_Pin_1
#define H3_GPIO_PIN                       GPIO_Pin_2

/* Encoder timer selection */
#define ENC_TIMER_SELECTION               ENC_TIM2  /* ENC_TIM2...HALL_TIM5 */ 
#define ENC_TIMER_REMAPPING               NO_REMAP_TIM2  /* NO_REMAP, FULL_REMAP, 
                                                            PARTIAL_REMAP */
#define ENC_A_GPIO_PORT                   GPIOA
#define ENC_B_GPIO_PORT                   GPIOA
#define ENC_A_GPIO_PIN                    GPIO_Pin_0
#define ENC_B_GPIO_PIN                    GPIO_Pin_1

/* Digital Outputs */
#define R_BRAKE_GPIO_PORT                  GPIOD
#define R_BRAKE_GPIO_PIN                   GPIO_Pin_13
#define OV_CURR_BYPASS_GPIO_PORT           GPIOD        
#define OV_CURR_BYPASS_GPIO_PIN            GPIO_Pin_13
#define INRUSH_CURRLIMIT_GPIO_PORT         GPIOD
#define INRUSH_CURRLIMIT_GPIO_PIN          GPIO_Pin_10

/************************ ANALOG I/O DEFINITION SECTION  *********************/
/** Currents reading  **/
/* Only for three shunt resistors and ICS cases */
#define PHASE_U_CURR_ADC                ADC1_2
#define PHASE_U_CURR_CHANNEL            ADC_Channel_11
#define PHASE_U_GPIO_PORT               GPIOC
#define PHASE_U_GPIO_PIN                GPIO_Pin_1
#define PHASE_V_CURR_ADC                ADC1_2
#define PHASE_V_CURR_CHANNEL            ADC_Channel_12
#define PHASE_V_GPIO_PORT               GPIOC
#define PHASE_V_GPIO_PIN                GPIO_Pin_2
/* Only for three shunts case */
#define PHASE_W_CURR_ADC                ADC1_2
#define PHASE_W_CURR_CHANNEL            ADC_Channel_13
#define PHASE_W_GPIO_PORT               GPIOC
#define PHASE_W_GPIO_PIN                GPIO_Pin_3       
/* Only for 1 shunt resistor case */
#define PHASE_CURRENTS_ADC              ADC1_2
#define PHASE_CURRENTS_CHANNEL          ADC_Channel_12
#define PHASE_CURRENTS_GPIO_PORT        GPIOC
#define PHASE_CURRENTS_GPIO_PIN         GPIO_Pin_2    

/** Bus and temperature readings **/
#define VBUS_ADC                        ADC1_2
#define VBUS_CHANNEL                    ADC_Channel_3
#define VBUS_GPIO_PORT                  GPIOA
#define VBUS_GPIO_PIN                   GPIO_Pin_3   

#define TEMP_FDBK_ADC                   ADC1_2                  
#define TEMP_FDBK_CHANNEL               ADC_Channel_10
#define TEMP_FDBK_GPIO_PORT             GPIOC
#define TEMP_FDBK_GPIO_PIN              GPIO_Pin_0  

/* Serial communication */
#define USART1_REMAPPING                USART1_NO_REMAP   /* USART1_NO_REMAP, USART1_REMAP */


#endif /*__CONTROL_STAGE_PARAMETERS_H*/
/******************* (C) COPYRIGHT 2011 STMicroelectronics *****END OF FILE****/
