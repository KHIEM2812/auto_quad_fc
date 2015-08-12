/**
  ******************************************************************************
  * @file    Drive parameters2.h
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
#ifndef __DRIVE_PARAMETERS_MOTOR2_H
#define __DRIVE_PARAMETERS_MOTOR2_H

/******** MAIN AND AUXILIARY SPEED/POSITION SENSOR(S) SETTINGS SECTION ********/
/*** Speed sensor selection ***/
#define STATE_OBSERVER_PLL2
/* #define STATE_OBSERVER_CORDIC2 */
/* #define ENCODER2 */
/* #define HALL_SENSORS2 */


/*** Auxiliary speed measurement selection ***/
/* #define AUX_STATE_OBSERVER_PLL2 */
/* #define AUX_STATE_OBSERVER_CORDIC2 */
/* #define AUX_ENCODER2 */
/* #define AUX_HALL_SENSORS2 */


/*** Speed measurement settings ***/
#define MAX_APPLICATION_SPEED2	       4000 /*!< rpm, mechanical */
#define MIN_APPLICATION_SPEED2	       0 /*!< rpm, mechanical,  
													   absolute value */
#define MEAS_ERRORS_BEFORE_FAULTS2 	  3 /*!< Number of speed  
													   measurement errors before 
													   main sensor goes in fault */						

/*** Encoder **********************/													   
#define ENC_MEAS_ERRORS_BEFORE_FAULTS2 3 /*!< Number of failed   
													   derived class specific speed 
													   measurements before main sensor  
													   goes in fault */
#define ENC_ICx_FILTER2	     		  50 /*!< Duration of input  
													   capture filter in CPU clock   
													   cycles in case of   
					                                   quadrature encoder main 
													   or auxiliary sensors in use */	
#define ENC_INVERT_SPEED2	          DISABLE  /*!< To be enabled for  
					                                    encoder (main or aux) if  
					                                    measured speed is opposite 
														to real one */																
#define ENC_AVERAGING_FIFO_DEPTH2	  16 /*!< depth of the FIFO used to 
														average mechanical speed in 
														0.1Hz resolution */
/****** Hall sensors ************/
#define HALL_MEAS_ERRORS_BEFORE_FAULTS2 3 /*!< Number of failed   
													   derived class specific speed 
													   measurements before main sensor  
													   goes in fault */
#define HALL_ICx_FILTER2	          94 /*!< Duration of input  
													   capture filter in CPU clock   
													   cycles in case of Hall sensors  
					                                   main or auxiliary sensors
													   in use */
#define HALL_AVERAGING_FIFO_DEPTH2	  6 /*!< depth of the FIFO used to 
														average mechanical speed in 
														0.1Hz resolution */													   
						
/****** State Observer + PLL ****/
#define VARIANCE_THRESHOLD2            0.063  /*!<Maximum accepted 
														variance on speed 
														estimates (percentage) */
/* State observer scaling factors F1 */                    
#define F12                            2048
#define F22                            16384

/* State observer constants */
#define GAIN12                         -3016
#define GAIN22                         18718
/*Only in case PLL is used, PLL gains */
#define PLL_KP_GAIN2                   266
#define PLL_KI_GAIN2                   11

#define OBS_MEAS_ERRORS_BEFORE_FAULTS2 3  /*!< Number of consecutive errors   
														on variance test before a speed 
														feedback error is reported */								
#define STO_FIFO_DEPTH_DPP2	           64  /*!< Depth of the FIFO used  
					                                    to average mechanical speed  
														in dpp format */
#define STO_FIFO_DEPTH_01HZ2           64  /*!< Depth of the FIFO used  
					                                    to average mechanical speed  
														in dpp format */	
#define BEMF_CONSISTENCY_TOL2              64   /* Parameter for B-emf 
                                                         amplitude-speed consistency */
#define BEMF_CONSISTENCY_GAIN2         64   /* Parameter for B-emf 
                                                          amplitude-speed consistency */        
/****** State Observer + CORDIC ***/
#define CORD_VARIANCE_THRESHOLD2       0.063  /*!<Maximum accepted 
														variance on speed 
														estimates (percentage) */														
#define CORD_F12                       2048
#define CORD_F22                       16384

/* State observer constants */
#define CORD_GAIN12                    -3016
#define CORD_GAIN22                    18718

#define CORD_MEAS_ERRORS_BEFORE_FAULTS2 3  /*!< Number of consecutive errors   
														on variance test before a speed 
														feedback error is reported */
#define CORD_FIFO_DEPTH_DPP2	       64  /*!< Depth of the FIFO used  
					                                    to average mechanical speed  
														in dpp format */
#define CORD_FIFO_DEPTH_01HZ2	       64  /*!< Depth of the FIFO used  
					                                    to average mechanical speed  
														in dpp format */	
#define CORD_MAX_ACCEL_DPPP2            30  /*!< Maximum instantaneous 
														electrical acceleration (dpp 
														per control period) */
#define CORD_BEMF_CONSISTENCY_TOL2          64  /* Parameter for B-emf 
                                                          amplitude-speed consistency */
#define CORD_BEMF_CONSISTENCY_GAIN2     64  /* Parameter for B-emf 
                                                          amplitude-speed consistency */

/**************************    DRIVE SETTINGS SECTION   **********************/
/* Dual drive specific parameters */
#define FREQ_RATIO                      1  /* Higher PWM frequency/lower PWM frequency */  
#define FREQ_RELATION                   HIGHEST_FREQ  /* It refers to motor 1 and can be 
															 HIGHEST_FREQ or LOWEST frequency depending 
															 on motor 1 and 2 frequency relationship */
#define FREQ_RELATION2                  LOWEST_FREQ   /* It refers to motor 2 and can be 
															 HIGHEST_FREQ or LOWEST frequency depending 
															 on motor 1 and 2 frequency relationship */

/* PWM generation and current reading */


#define PWM_FREQUENCY2 	               16000

#define MAX_MODULATION_95_PER_CENT2

#define LOW_SIDE_SIGNALS_ENABLING2      ENABLE

#define SW_DEADTIME_NS2                800 /*!< Dead-time to be inserted  
														by FW, only if low side 
														signals are enabled */
#define HIGH_SIDE_IDLE_STATE2	       TURN_OFF /*!< TURN_OFF, TURN_ON */
#define LOW_SIDE_IDLE_STATE2	       TURN_OFF/*!< TURN_OFF, TURN_ON */
											  
#define CURR_SAMPLING_TIME2             1	/*!< Sampling time duration  
														in ADC clock cycles (1 for  
														1.5, 7 for 7.5, ...) */

/* Torque and flux regulation loops */
#define REGULATION_EXECUTION_RATE2     1 /*!< Number of PWM cycles */     

/* Gains values for torque and flux control loops */
#define PID_TORQUE_KP_DEFAULT2         3643      
#define PID_TORQUE_KI_DEFAULT2         531
#define PID_TORQUE_KD_DEFAULT2         100
#define PID_FLUX_KP_DEFAULT2           3643
#define PID_FLUX_KI_DEFAULT2           531
#define PID_FLUX_KD_DEFAULT2           100

/* Torque/Flux control loop gains dividers*/
#define TF_KPDIV2                      4096
#define TF_KIDIV2                      16384
#define TF_KDDIV2                      8192
#define TFDIFFERENTIAL_TERM_ENABLING2  DISABLE

/* Speed control loop */ 
#define SPEED_LOOP_FREQUENCY_HZ2        500 /*!<Execution rate of speed   
						                                regulation loop (Hz) */
#define PID_SPEED_KP_DEFAULT2           1000
#define PID_SPEED_KI_DEFAULT2           700
#define PID_SPEED_KD_DEFAULT2           0
/* Speed PID parameter dividers */
#define SP_KPDIV2                       16
#define SP_KIDIV2                       256
#define SP_KDDIV2                       16
#define SPD_DIFFERENTIAL_TERM_ENABLING2 DISABLE

/* Default settings */
#define DEFAULT_CONTROL_MODE2           STC_SPEED_MODE /*!< STC_TORQUE_MODE or 
														STC_SPEED_MODE */  
#define DEFAULT_TARGET_SPEED_RPM2       1500
#define DEFAULT_TORQUE_COMPONENT2       0
#define DEFAULT_FLUX_COMPONENT2	        0

/**************************    FIRMWARE PROTECTIONS SECTION   *****************/
#define OV_VOLTAGE_PROT_ENABLING2       ENABLE
#define UV_VOLTAGE_PROT_ENABLING2   	ENABLE
#define OV_VOLTAGE_THRESHOLD_V2		   32 /*!< Over-voltage 
													    threshold */
#define UD_VOLTAGE_THRESHOLD_V2		   18 /*!< Under-voltage 
														threshold */
#define ON_OVER_VOLTAGE2			   TURN_OFF_PWM /*!< TURN_OFF_PWM, 
                                                         TURN_ON_R_BRAKE or 
														TURN_ON_LOW_SIDES */
#define R_BRAKE_SWITCH_OFF_THRES_V2	   250

#define OV_TEMPERATURE_PROT_ENABLING2   ENABLE
#define OV_TEMPERATURE_THRESHOLD_C2	    70 /*!< Celsius degrees */
#define OV_TEMPERATURE_HYSTERESIS_C2	10 /*!< Celsius degrees */

#define SW_OV_CURRENT_PROT_ENABLING2	ENABLE /*!< Over-current detection 
                                                        enabling */
#define HW_OV_CURRENT_PROT_BYPASS2	    DISABLE /*!< In case ON_OVER_VOLTAGE  
                                                        is set to TURN_ON_LOW_SIDES
														this feature may be used to
 														bypass HW over-current
														protection (if supported by 
														power stage) */
/******************************   START-UP PARAMETERS   **********************/
/* Encoder alignment */
#define ALIGNMENT_DURATION2	           700 /*!< milliseconds */
#define ALIGNMENT_ANGLE_DEG2            90 /*!< degrees [0...359] */
#define FINAL_I_ALIGNMENT2              23513 /*!< s16A */
// With ALIGNMENT_ANGLE_DEG equal to 90 degrees, final alignment 
// phase current = (FINAL_I_ALIGNMENT * 1.65/ Av)/(32767 * Rshunt)  
// being Av the voltage gain between Rshunt and A/D input

/* Sensor-less rev-up sequence */
#define STARTING_ANGLE_DEG2             0  /*!< degrees [0...359] */
/* Phase 1 */
#define PHASE1_DURATION2		        0 /*milliseconds */
#define PHASE1_FINAL_SPEED_RPM2	        0  /* rpm */
#define PHASE1_FINAL_CURRENT2	        0
/* Phase 2 */
#define PHASE2_DURATION2		        0   /*milliseconds */
#define PHASE2_FINAL_SPEED_RPM2	        0   /* rpm */
#define PHASE2_FINAL_CURRENT2	        0
/* Phase 3 */
#define PHASE3_DURATION2		        350   /*milliseconds */
#define PHASE3_FINAL_SPEED_RPM2	        630   /* rpm */
#define PHASE3_FINAL_CURRENT2	        8440
/* Phase 4 */
#define PHASE4_DURATION2		        1150   /*milliseconds */
#define PHASE4_FINAL_SPEED_RPM2	        2700  /* rpm */
#define PHASE4_FINAL_CURRENT2	        8440
/* Phase 5 */
#define PHASE5_DURATION2		        0   /* milliseconds */
#define PHASE5_FINAL_SPEED_RPM2	        2700   /* rpm */
#define PHASE5_FINAL_CURRENT2	        8440

#define ENABLE_SL_ALGO_FROM_PHASE2      3
/* Observer start-up output conditions  */
#define OBS_MINIMUM_SPEED_RPM2         580
#define NB_CONSECUTIVE_TESTS2          2 /* Corresponding to 
														former NB_CONSECUTIVE_TESTS/
														(TF_REGULATION_RATE/
														MEDIUM_FREQUENCY_TASK_RATE) */
#define SPEED_BAND_UPPER_LIMIT2  	   17 /*!< It expresses how much 
														estimated speed can exceed 
														forced stator electrical 
														without being considered wrong. 
														In 1/16 of forced speed */
#define SPEED_BAND_LOWER_LIMIT2  	   16  /*!< It expresses how much 
														estimated speed can be below 
														forced stator electrical 
														without being considered wrong. 
                                                        in 1/16 of forced speed */        
#define TRANSITION_DURATION2           100  /* Switch over duration, ms */                                                        
/******************************   ADDITIONAL FEATURES   **********************/
#define  BUS_VOLTAGE_READING2          ENABLE
#define  VBUS_ADC_SAMPLING_TIME2        28

#define  TEMPERATURE_READING2          ENABLE
#define  TEMP_ADC_SAMPLING_TIME2       13

#define  OPEN_LOOP_FOC2                     DISABLE
#define  OPEN_LOOP_VOLTAGE_d2               10000  /*!< Three Phase voltage amplitude
                                                      in s16 format */
#define  OPEN_LOOP_SPEED_RPM2	    	   100   /*!< Final forced speed in rpm */
#define  OPEN_LOOP_SPEED_RAMP_DURATION_MS2  1000  /*!< 0-to-Final speed ramp duration  */   

#define  FLUX_WEAKENING_ENABLING2	   ENABLE

#define  FW_VOLTAGE_REF2               985 /*!<Vs reference, tenth 
														of a percent */
#define  FW_KP_GAIN2                    3000 /*!< Default Kp gain */
#define  FW_KI_GAIN2                    5000 /*!< Default Ki gain */
#define  FW_KPDIV2                      32768      
								/*!< Kp gain divisor.If FULL_MISRA_C_COMPLIANCY
								is not defined the divisor is implemented through       
								algebrical right shifts to speed up PIs execution. 
								Only in this case this parameter specifies the 
								number of right shifts to be executed */
#define  FW_KIDIV2    				   32768
								/*!< Ki gain divisor.If FULL_MISRA_C_COMPLIANCY
								is not defined the divisor is implemented through       
								algebrical right shifts to speed up PIs execution. 
								Only in this case this parameter specifies the 
								number of right shifts to be executed */
/*  Feed-forward parameters */
#define FEED_FORWARD_CURRENT_REG_ENABLING2 DISABLE
#define CONSTANT1_Q2                    6510
#define CONSTANT1_D2                    6510
#define CONSTANT2_QD2                   7783

/*  Maximum Torque Per Ampere strategy parameters */
#define MTPA_ENABLING2    	           DISABLE
#define IQMAX2                         25322
#define SEGDIV2                        0
#define ANGC2                          {0,0,0,0,0,0,0,0}
#define OFST2                          {0,0,0,0,0,0,0,0}

/* Inrush current limiter parameters */
#define INRUSH_CURRLIMIT_ENABLING2     DISABLE
#define INRUSH_CURRLIMIT_AT_POWER_ON2  INACTIVE  /*ACTIVE or INACTIVE*/
#define INRUSH_CURRLIMIT_CHANGE_AFTER_MS21000  /* milliseconds */		

/******************************** DEBUG ADD-ONs *******************************/
#define DAC_FUNCTIONALITY2			   ENABLE

#endif /*__DRIVE_PARAMETERS_MOTOR2_H*/
/******************* (C) COPYRIGHT 2011 STMicroelectronics *****END OF FILE****/
