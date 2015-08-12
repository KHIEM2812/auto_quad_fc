/**
  ******************************************************************************
  * @file    PMSM motor parameters.h
  * @author  IMS Systems Lab and Technical Marketing - MC Team
  * @version 3.0
  * @date    05-Apr-2011 11:34
  * @brief   This file contains motor parameters needed by STM32 PMSM MC FW  
  *	         library v3.0
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
#ifndef __POWER_STAGE_PARAMETERS_MOTOR2_H
#define __POWER_STAGE_PARAMETERS_MOTOR2_H

/************* PWM Driving signals section **************/
#define PHASE_UH_POLARITY2  H_ACTIVE_HIGH 
#define PHASE_VH_POLARITY2  H_ACTIVE_HIGH 
#define PHASE_WH_POLARITY2  H_ACTIVE_HIGH 

#define HW_COMPLEMENTED_LOW_SIDE2     DISABLE 

#define PHASE_UL_POLARITY2  L_ACTIVE_HIGH  
#define PHASE_VL_POLARITY2  L_ACTIVE_HIGH 
#define PHASE_WL_POLARITY2  L_ACTIVE_HIGH 

#define HW_DEAD_TIME_NS2              100 /*!< Dead-time inserted 
                                                         by HW if low side signals 
							    are not used */

/********** Inrush current limiter signal section *******/
#define INRUSH_CURR_LIMITER_POLARITY2  DOUT_ACTIVE_HIGH

/******* Dissipative brake driving signal section *******/
#define DISSIPATIVE_BRAKE_POLARITY2    DOUT_ACTIVE_HIGH

/*********** Bus voltage sensing section ****************/
#define VBUS_PARTITIONING_FACTOR2     0.0080 /*!< It expresses how 
                                                       much the Vbus is attenuated  
                                                       before being converted into 
                                          digital value */
#define NOMINAL_BUS_VOLTAGE_V2        22 
/******** Current reading parameters section ******/
/*** Topology ***/
#define THREE_SHUNT2
/* #define SINGLE_SHUNT2 */
/* #define ICS_SENSORS2 */


#define RSHUNT2                       0.220

/*  ICSs gains in case of isolated current sensors,
        amplification gain for shunts based sensing */
#define AMPLIFICATION_GAIN2           2.76 

/*** Noise parameters ***/
#define TNOISE_NS2  2550
#define TRISE_NS2   2550
   
/*********** Over-current protection section ************/   
#define OVERCURR_FEEDBACK_POLARITY2        EMSTOP_ACTIVE_LOW
#define OVERCURR_PROTECTION_HW_DISABLING2  DOUT_ACTIVE_HIGH
   
/************ Temperature sensing section ***************/
/* V[V]=V0+dV/dT[V/Celsius]*(T-T0)[Celsius]*/
#define V0_V2                         0.290 /*!< in Volts */
#define T0_C2                         25.0 /*!< in Celsius degrees */
#define dV_dT2                        0.025 /*!< V/Celsius degrees */
#define T_MAX2                        70 /*!< Sensor measured 
                                                         temperature at maximum 
                                                         power stage working 
                                                         temperature, Celsius degrees */
#endif /*__POWER_STAGE_PARAMETERS_H*/
/******************* (C) COPYRIGHT 2011 STMicroelectronics *****END OF FILE****/
