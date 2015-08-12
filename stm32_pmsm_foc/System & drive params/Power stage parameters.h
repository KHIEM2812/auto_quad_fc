/**
  ******************************************************************************
  * @file    Power stage parameters.h
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
#ifndef __POWER_STAGE_PARAMETERS_H
#define __POWER_STAGE_PARAMETERS_H

/************* PWM Driving signals section **************/
#define PHASE_UH_POLARITY             H_ACTIVE_HIGH 
#define PHASE_VH_POLARITY             H_ACTIVE_HIGH 
#define PHASE_WH_POLARITY             H_ACTIVE_HIGH 

#define HW_COMPLEMENTED_LOW_SIDE      DISABLE 

#define PHASE_UL_POLARITY             L_ACTIVE_HIGH 
#define PHASE_VL_POLARITY             L_ACTIVE_HIGH 
#define PHASE_WL_POLARITY             L_ACTIVE_HIGH 

#define HW_DEAD_TIME_NS              100 /*!< Dead-time inserted 
                                                         by HW if low side signals 
                                                         are not used */
/********** Inrush current limiter signal section *******/
#define INRUSH_CURR_LIMITER_POLARITY  DOUT_ACTIVE_HIGH 

/******* Dissipative brake driving signal section *******/
#define DISSIPATIVE_BRAKE_POLARITY    DOUT_ACTIVE_HIGH 

/*********** Bus voltage sensing section ****************/
#define VBUS_PARTITIONING_FACTOR      0.0080 /*!< It expresses how 
                                                       much the Vbus is attenuated  
                                                       before being converted into 
                                                       digital value */
#define NOMINAL_BUS_VOLTAGE_V         22 
/******** Current reading parameters section ******/
/*** Topology ***/
#define THREE_SHUNT
/* #define SINGLE_SHUNT */
/* #define ICS_SENSORS */
 

#define RSHUNT                        0.220 

/*  ICSs gains in case of isolated current sensors,
        amplification gain for shunts based sensing */
#define AMPLIFICATION_GAIN            2.76 

/*** Noise parameters ***/
#define TNOISE_NS                     2550 
#define TRISE_NS                      2550 
   
/*********** Over-current protection section ************/   
#define OVERCURR_FEEDBACK_POLARITY       EMSTOP_ACTIVE_LOW 
#define OVERCURR_PROTECTION_HW_DISABLING  DOUT_ACTIVE_HIGH 
   
/************ Temperature sensing section ***************/
/* V[V]=V0+dV/dT[V/Celsius]*(T-T0)[Celsius]*/
#define V0_V                          0.290 /*!< in Volts */
#define T0_C                          25.0 /*!< in Celsius degrees */
#define dV_dT                         0.025 /*!< V/Celsius degrees */
#define T_MAX                         70 /*!< Sensor measured 
                                                       temperature at maximum 
                                                       power stage working 
                                                       temperature, Celsius degrees */
#endif /*__POWER_STAGE_PARAMETERS_H*/
/******************* (C) COPYRIGHT 2011 STMicroelectronics *****END OF FILE****/
