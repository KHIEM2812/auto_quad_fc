/**
  ******************************************************************************
  * @file    Control stage parameters.h
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
#ifndef __DEFINITIONS_H
#define __DEFINITIONS_H

#define	DEGREES_120 0u
#define	DEGREES_60 1u

#define ENABLE   1
#define DISABLE  0
#define TURN_ON  1
#define TURN_OFF 0
#define INRUSH_ACTIVE   1
#define INRUSH_INACTIVE 0

#define TURN_OFF_PWM      0
#define TURN_ON_R_BRAKE   1  
#define TURN_ON_LOW_SIDES 2

//#define STM32VALUE            1
//#define STM32PERFORMANCEMD    2
//#define STM32PERFORMANCEHD    3
//#define STM32PERFORMANCELD    4				
#define VFQFPN36  1
#define VFQFPN48  2
#define LQFP48    3
#define LQFP64    4
#define LQFP100   5
#define LQFP144   6
#define WLCSP64   7
#define LFBGA100  8
#define	LFBGA144  9
#define BGA100    10
#define BGA64     11
#define TFBGA64   12

#define HIGHEST_FREQ 2
#define LOWEST_FREQ 1

#define HALL_TIM2 2
#define HALL_TIM3 3
#define HALL_TIM4 4
#define HALL_TIM5 5

#define ENC_TIM2 2
#define ENC_TIM3 3
#define ENC_TIM4 4
#define ENC_TIM5 5


#endif /*__DEFINITIONS_H*/
/**************** (c) 2007  STMicroelectronics ********************************/
/******************* (C) COPYRIGHT 2011 STMicroelectronics *****END OF FILE****/
