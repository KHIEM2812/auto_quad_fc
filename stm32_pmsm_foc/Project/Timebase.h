/**
  ******************************************************************************
  * @file    Timebase.h
  * @author  IMS Systems Lab and Technical Marketing - MC Team
  * @version 3.0
  * @date    05-Apr-2011 11:34
  * @brief   This file defines booting function of MC library, single motor      
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
#ifndef __TIMEBASE_H
#define __TIMEBASE_H

/* Includes ------------------------------------------------------------------*/
#include "MC_type.h"

/** @addtogroup Timebase
  * @{
  */

/** @defgroup Timebase_exported_functions Timebase exported functions
  * @{
  */


/**
  * @brief  Use this function to know whether the user interface idle time 
  * has elapsed 
  * @param  none
  * @retval bool TRUE if time is elapsed, FALSE otherwise
  */
bool TB_UserInterfaceIdleTimeHasElapsed(void);

/**
  * @brief  It set a counter intended to be used for counting the user interface 
  *         idle time
  * @param  SysTickCount number of System ticks to be counted
  * @retval void
  */
void TB_SetUserInterfaceIdleTime(uint16_t SysTickCount);

/**
  * @brief  Use this function to know whether the serial communication timeout 
  * has elapsed 
  * @param  none
  * @retval bool TRUE if time is elapsed, FALSE otherwise
  */
bool TB_SerialCommunicationTimeOutHasElapsed(void);

/**
  * @brief  Use this function to stop the serial communication timeout 
  * counting. 
  * @param  none
  * @retval none
  */
void TB_SerialCommunicationTimeOutStop(void);

/**
  * @brief  It start the timeout for serial communication. 
  *         Each packet must be received before end of timeout. 
  *         Otherwise the message timeout is sent back.
  * @retval void
  */
void TB_SerialCommunicationTimeOutStart(void);

/**
  * @brief  It is the task scheduler and updates counters used by wait functions.
  *         Note: The tasks are not called by this function but -through the SVC 
  *         call handler- by TB_TaskExec.
  * @param  none
  * @retval none
  */
void TB_Scheduler(void);

/**
  * @brief  This function actually calls the Tasks managed by PendSV handler.
  * @param  none
  * @retval none
  */
void TB_PendSVTaskExec(void);

/**
  * @}
  */
  
/**
  * @}
  */

/**
  * @}
  */

#endif /* __MCBOOTSINGLEMOTOR_H */

/******************* (C) COPYRIGHT 2011 STMicroelectronics *****END OF FILE****/
