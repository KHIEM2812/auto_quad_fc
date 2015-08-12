/**
  ******************************************************************************
  * @file    PMSM motor parameters.h
  * @author  IMS Systems Lab and Technical Marketing - MC Team
  * @version 3.0
  * @date    05-Apr-2011 11:34
  * @brief   This file contains motor parameters needed by STM32 PMSM MC FW  
  *          library v3.0
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
#ifndef __PMSM_MOTOR2_PARAMETERS_H
#define __PMSM_MOTOR2_PARAMETERS_H

/***************** MOTOR ELECTRICAL PARAMETERS  ******************************/
#define POLE_PAIR_NUM2            2  /* Number of motor pole pairs */
#define RS2               0.35            /* Stator resistance , ohm*/
#define LS2                       0.00060  /* Stator inductance , H */

/* When using Id = 0, NOMINAL_CURRENT is utilized to saturate the output of the 
   PID for speed regulation (i.e. reference torque). 
   Transformation of real currents (A) into s16 format must be done accordingly with 
   formula:
   Phase current (s16 0-to-peak) = (Phase current (A 0-to-peak)* 32767 * Rshunt *
                                   *Amplifying network gain)/(MCU supply voltage/2)
*/

#define NOMINAL_CURRENT2         25322  
#define MOTOR_MAX_SPEED_RPM2     6000   /*!< Maximum rated speed  */
#define MOTOR_VOLTAGE_CONSTANT2      4.0   	  /*!< Volts RMS ph-ph /kRPM */
#define ID_DEMAG2                -25322   /*!< Demagnetization current */

/***************** MOTOR SENSORS PARAMETERS  ******************************/
/* Motor sensors parameters are always generated but really meaningful only 
   if the corresponding sensor is actually present in the motor         */

/*** Hall sensors ***/
#define HALL_SENSORS_AVAILABLE2  TRUE
#define HALL_SENSORS_PLACEMENT2  DEGREES_120 /*!<Define here the  
                                                 mechanical position of the sensors                    
                                                 with reference to an electrical cycle. 
                                                 It can be either DEGREES_120 or 
                                                 DEGREES_60 */

#define HALL_PHASE_SHIFT2 (s16) 300 /*!< Define here in degrees the 
                                          electrical phase shift between the 
										  low to high transition of signal H1 
										  and the maximum of the Bemf induced 
										  on phase A */
/*** Quadrature encoder ***/ 
#define ENCODER_AVAILABLE2      TRUE 
#define ENCODER_PPR2           400  /*!< Number of pulses per 
                                          revolution */
 
#endif /*__PMSM_MOTOR2_PARAMETERS_H*/

/******************* (C) COPYRIGHT 2011 STMicroelectronics *****END OF FILE****/
