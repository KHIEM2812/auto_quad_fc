/**
  ******************************************************************************
  * @file    main.c 
  * @author  STMicroelectronics - System Lab - MC Team
  * @version 4.0.0
  * @date    28-May-2014 10:45
  * @brief   Main program body
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; COPYRIGHT 2014 STMicroelectronics</center></h2>
  *
  * Licensed under MCD-ST Liberty SW License Agreement V2, (the "License");
  * You may not use this file except in compliance with the License.
  * You may obtain a copy of the License at:
  *
  *        http://www.st.com/software_license_agreement_liberty_v2
  *
  * Unless required by applicable law or agreed to in writing, software 
  * distributed under the License is distributed on an "AS IS" BASIS, 
  * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
  * See the License for the specific language governing permissions and
  * limitations under the License.
  *
  ******************************************************************************
  * Unless required by applicable law or agreed to in writing, software 
  * distributed under the License is distributed on an "AS IS" BASIS, 
  * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
  * See the License for the specific language governing permissions and
  * limitations under the License.
  *
  ******************************************************************************
  */ 

/* Includes ------------------------------------------------------------------*/
/* Pre-compiler coherency check */
#define PROJECT_CHK
#include "CrossCheck.h" 
#undef PROJECT_CHK

#include "MCTuningClass.h"
#include "MCInterfaceClass.h"
#include "MCTasks.h"
#include "Parameters conversion.h"
#include "Parameters conversion motor 2.h"
#include "Timebase.h"
#include "UITask.h"

#include <stdio.h>

#include "FreeRTOS.h"
#include "task.h"

#include "stm32_eval.h"
#ifdef USE_STM32100B_EVAL
 #include "stm32100b_eval_lcd.h"
#elif defined USE_STM3210B_EVAL
 #include "stm3210b_eval_lcd.h"
#elif defined USE_STM3210E_EVAL
 #include "stm3210e_eval_lcd.h"
#elif defined USE_STM3210C_EVAL
 #include "stm3210c_eval_lcd.h"
#endif

#define FIRMWARE_VERS_RTOS "STM32 FOC SDK\0Ver.4.0.0 - Free RTOS"
const char s_fwVer[] = FIRMWARE_VERS_RTOS;

/* Private function prototypes -----------------------------------------------*/
#ifdef __GNUC__
/* With GCC/RAISONANCE, small printf (option LD Linker->Libraries->Small printf
   set to 'Yes') calls __io_putchar() */
#define PUTCHAR_PROTOTYPE int __io_putchar(int ch)
#else
#define PUTCHAR_PROTOTYPE int fputc(int ch, FILE *f)
#endif /* __GNUC__ */

/* Private function prototypes -----------------------------------------------*/
void LowFrequencyTaskCode( void * pvParameters );
void MediumFrequencyTaskCode( void * pvParameters );
void HighFrequencyTaskCode( void * pvParameters );
void SafetyProcessingTaskCode( void * pvParameters );
void UI_TaskCode( void * pvParameters );
void SerialComTimeout_TaskCode( void * pvParameters );
void vApplicationStackOverflowHook( xTaskHandle *pxTask, signed portCHAR *pcTaskName );
void vApplicationIdleHook( void );

#ifdef SERIAL_COMMUNICATION
xTaskHandle xSerialComTimeoutHandle;
#endif

CMCI oMCI[MC_NUM];
CMCT oMCT[MC_NUM];  
uint32_t wConfig[MC_NUM] = {UI_CONFIG_M1,UI_CONFIG_M2};

/* Private functions ---------------------------------------------------------*/

/**
  * @brief  Main program.
  * @param  None
  * @retval None
  */
int main(void)
{
  /*!< At this stage the microcontroller clock setting is already configured, 
       this is done through SystemInit() function which is called from startup
       file (startup_stm32f10x_xx.s) before to branch to application main.
       To reconfigure the default setting of SystemInit() function, refer to
       system_stm32f10x.c file
     */
  
  /*NVIC Priority group configuration.
    Default option is NVIC_PriorityGroup_3. The sole alternative option,
    left to user choice, is NVIC_PriorityGroup_2*/
  NVIC_PriorityGroupConfig(NVIC_PriorityGroup_3);
  
  /*MCInterface and MCTuning boot*/
  MCboot(oMCI,oMCT);
  
  #if defined(PFC_ENABLED)
    PFC_Boot(oMCT[0],(CMCT)MC_NULL, (int16_t *)MC_NULL);
  #endif
  
  /* Start here ***************************************************************/
  /* GUI, this section is present only if LCD, DAC or serial communication is */
  /* enabled.                                                                 */
#if (defined(LCD_FUNCTIONALITY) | defined(DAC_FUNCTIONALITY) | defined(SERIAL_COMMUNICATION))
  UI_TaskInit(UI_INIT_CFG,wConfig,MC_NUM,oMCI,oMCT,s_fwVer);
#endif 
  /* End here******************************************************************/
  
  /* Spawn the task. */
  xTaskCreate(MediumFrequencyTaskCode, ( signed char * ) "MF_Task", 64, NULL, 
                                          ( tskIDLE_PRIORITY + 3 ), ( xTaskHandle * ) NULL );

  xTaskCreate(SafetyProcessingTaskCode, ( signed char * ) "Safety", 64, NULL, 
                                          ( tskIDLE_PRIORITY + 4 ), ( xTaskHandle * ) NULL );    

#ifdef LCD_FUNCTIONALITY
  portBASE_TYPE retVal = xTaskCreate(UI_TaskCode, ( signed char * ) "UI_Task", 256, NULL, 
                                          ( tskIDLE_PRIORITY + 1 ), ( xTaskHandle * ) NULL ); 
#endif

  /* Start the scheduler. */
  vTaskStartScheduler();
  
  while(1)
  {    

  }
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *   where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t* file, uint32_t line)
{ 
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */

  /* Infinite loop */
  while (1)
  {
  }
}
#endif

void MediumFrequencyTaskCode( void * pvParameters )
{
  portTickType xLastWakeTime;
  
  // Initialise the xLastWakeTime variable with the current time.
  xLastWakeTime = xTaskGetTickCount();
  
  for( ;; )
  {
    // Wait for the next cycle.
    vTaskDelayUntil( &xLastWakeTime, 1);
    // Perform action here.
    MC_Scheduler();
  }
  
}


void SafetyProcessingTaskCode( void * pvParameters )
{
  portTickType xLastWakeTime;
  
  // Initialise the xLastWakeTime variable with the current time.
  xLastWakeTime = xTaskGetTickCount();
  
  for( ;; )
  {
    // Wait for the next cycle.
    vTaskDelayUntil( &xLastWakeTime, 1);
    // Perform action here.
    TSK_SafetyTask();
  }
}

#ifdef LCD_FUNCTIONALITY
void UI_TaskCode( void * pvParameters )
{
  portTickType xLastWakeTime;
  
  // Initialise the xLastWakeTime variable with the current time.
  xLastWakeTime = xTaskGetTickCount();
  
  for( ;; )
  {
    // Wait for the next cycle.
    vTaskDelayUntil( &xLastWakeTime, UI_TASK_OCCURENCE_TICKS+1);
    // Perform action here.
    UI_LCDRefresh();

  }
}
#endif

#ifdef SERIAL_COMMUNICATION
void SerialComTimeout_TaskCode( void * pvParameters )
{
  portTickType xLastWakeTime;
  
  // Initialise the xLastWakeTime variable with the current time.
  xLastWakeTime = xTaskGetTickCount();
  
  // Wait timeout.
  vTaskDelayUntil( &xLastWakeTime, SERIALCOM_TIMEOUT_OCCURENCE_TICKS+1);
  
  // Send timeout message
  Exec_UI_IRQ_Handler(UI_IRQ_USART,3,0); // Flag 3 = Send timeout error*/
  
  // Destroy itself
  xSerialComTimeoutHandle = NULL;
  vTaskDelete(NULL); 
}

/**
  * @brief  It start the timeout for serial communication. 
  *         Each packet must be received before end of timeout. 
  *         Otherwise the message timeout is sent back.
  * @retval void
  */
void UI_SerialCommunicationTimeOutStart(void)
{
  /* Spawn the task. */
  if (xSerialComTimeoutHandle == NULL)
  {
    xTaskCreate(SerialComTimeout_TaskCode, ( signed char * ) "SerialComTimeout_Task", 64, NULL, 
                ( tskIDLE_PRIORITY + 1 ), &xSerialComTimeoutHandle ); 
  }
}

/**
  * @brief  Use this function to stop the serial communication timeout 
  * counting. 
  * @param  none
  * @retval none
  */
void UI_SerialCommunicationTimeOutStop(void)
{
  if (xSerialComTimeoutHandle != NULL)
  {
    // Destroy timeout
    vTaskDelete(xSerialComTimeoutHandle);
    xSerialComTimeoutHandle = NULL;
  }  
}
#endif

void vApplicationStackOverflowHook( xTaskHandle *pxTask, signed portCHAR *pcTaskName )
{
/* Insert here your debug code */
}

void vApplicationIdleHook( void )
{
/* Insert here your background code */
}
/******************* (C) COPYRIGHT 2014 STMicroelectronics *****END OF FILE****/
