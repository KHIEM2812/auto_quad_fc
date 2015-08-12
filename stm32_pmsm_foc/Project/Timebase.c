/**
  ******************************************************************************
  * @file    Timebase.c 
  * @author  IMS Systems Lab and Technical Marketing - MC Team
  * @version 3.0
  * @date    05-Apr-2011 11:34
  * @brief   This file implements the time base utilized for running MC tasks
  ******************************************************************************
  * @copy
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

/* Includes ------------------------------------------------------------------*/
#include "Timebase.h"
#include "MCTuningClass.h"
#include "MCInterfaceClass.h"
#include "MCTasks.h"
#include "Parameters conversion.h"

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
static volatile uint8_t  bMFTaskCounter;
static volatile uint8_t  bLFTaskCounter;
static volatile uint8_t  bUITaskCounter;
static volatile uint8_t  bCOMTimeoutCounter;
static volatile uint8_t  bSafetyTaskCounter;
static volatile uint8_t  LFTaskPending;

/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/


/**
  * @brief  Use this function to know whether the user interface idle time 
  * has elapsed 
  * @param  none
  * @retval bool TRUE if time is elapsed, FALSE otherwise
  */
bool TB_UserInterfaceIdleTimeHasElapsed(void)
{
  bool retVal = FALSE;
  if (bUITaskCounter == 0u)
  {
    retVal = TRUE;
  }
  return (retVal);
}

/**
  * @brief  It set a counter intended to be used for counting the user interface 
  *         idle time
  * @param  SysTickCount number of System ticks to be counted
  * @retval void
  */
void TB_SetUserInterfaceIdleTime(uint16_t SysTickCount)
{
  bUITaskCounter = SysTickCount;
}

/**
  * @brief  Use this function to know whether the serial communication timeout 
  * has elapsed 
  * @param  none
  * @retval bool TRUE if time is elapsed, FALSE otherwise
  */
bool TB_SerialCommunicationTimeOutHasElapsed(void)
{
  bool retVal = FALSE;
  if (bCOMTimeoutCounter == 1u)
  {
    bCOMTimeoutCounter = 0u;
    retVal = TRUE;
  }
  return (retVal);
}

#ifndef FREE_RTOS
/**
  * @brief  Use this function to stop the serial communication timeout 
  * counting. 
  * @param  none
  * @retval none
  */
void TB_SerialCommunicationTimeOutStop(void)
{
  bCOMTimeoutCounter = 0u;
}
#endif

#ifndef FREE_RTOS
/**
  * @brief  It start the timeout for serial communication. 
  *         Each packet must be received before end of timeout. 
  *         Otherwise the message timeout is sent back.
  * @retval void
  */
void TB_SerialCommunicationTimeOutStart(void)
{
  bCOMTimeoutCounter = SERIALCOM_TIMEOUT_OCCURENCE_TICKS;
}
#endif

/**
  * @brief  It is the task scheduler and updates counters used by wait functions.
  *         Note: The tasks are not called by this function but -through the SVC 
  *         call handler- by TB_TaskExec.
  * @param  none
  * @retval none
  */
void TB_Scheduler(void)
{
  if(bSafetyTaskCounter != 0u)
  {
    bSafetyTaskCounter--;
  }   
  else
  {
    TSK_SafetyTask();
    bSafetyTaskCounter = SAFETY_TASK_OCCURENCE_TICKS;
  }
  
  if(bMFTaskCounter > 0u)
  {
    bMFTaskCounter--;
  }   
  else
  {
    TSK_MediumFrequencyTask();
    bMFTaskCounter = MF_TASK_OCCURENCE_TICKS;
  }
  
  if(bLFTaskCounter > 0u)
  {
    bLFTaskCounter--;
  }   
  else
  {
    if (LFTaskPending == 0)
    {
      LFTaskPending++;
      SCB->ICSR |= SCB_ICSR_PENDSVSET; /* pSVC call */
      bLFTaskCounter = LF_TASK_OCCURENCE_TICKS;
    }
  }
  
  if(bUITaskCounter > 0u)
  {
    bUITaskCounter--;
  }
  
  if(bCOMTimeoutCounter > 1u)
  {
    bCOMTimeoutCounter--;
  }
}

/**
  * @brief  This function actually calls the Tasks managed by PendSV handler.
  * @param  none
  * @retval none
  */
void TB_PendSVTaskExec(void)
{
  if (LFTaskPending == 1)
  {
    TSK_LowFrequencyTask();
    LFTaskPending--;
  }
}
/******************* (C) COPYRIGHT 2011 STMicroelectronics *****END OF FILE****/
