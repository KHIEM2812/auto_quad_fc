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
  */ 

/* Includes ------------------------------------------------------------------*/
/* Pre-compiler coherency check */
#define PROJECT_CHK
#include "CrossCheck.h" 
#undef PROJECT_CHK

#if defined(PFC_ENABLED)
  #include "PIRegulatorClass.h"
#endif

#include "MCTuningClass.h"
#include "MCInterfaceClass.h"

#if defined(PFC_ENABLED)
  #include "PFCInit.h"
  #include "PFCApplication.h"
#endif

#include "MCTasks.h"
#include "Parameters conversion.h"
#ifdef DUALDRIVE
#include "Parameters conversion motor 2.h"
#endif
#include "Timebase.h"
#include "UITask.h"
#include "MCLibraryISRPriorityConf.h"

#include <stdio.h>

#if (defined(USE_STM32303C_EVAL))
#include "stm32303c_eval.h"
#else
#include "stm32_eval.h"
#endif

#define FIRMWARE_VERS "STM32 FOC SDK\0Ver.4.0.0"
const char s_fwVer[32] = FIRMWARE_VERS;

#ifdef __GNUC__
/* With GCC/RAISONANCE, small printf (option LD Linker->Libraries->Small printf
   set to 'Yes') calls __io_putchar() */
#define PUTCHAR_PROTOTYPE int __io_putchar(int ch)
#else
#define PUTCHAR_PROTOTYPE int fputc(int ch, FILE *f)
#endif /* __GNUC__ */

/* Uncomment the following line to enable the demo mode */
/* #define DEMOMODE */

/* DEMO MODE prototypes, variables, macros */
#if defined(DEMOMODE)

#define MANUAL_MODE 0x00
#define DEMO_MODE   0x01

static volatile uint8_t Mode = DEMO_MODE;

void Demo(void);
void TqSpeedMode_start(void);
#endif

#if defined(EXAMPLE_SPEEDMONITOR)
  void speedmonitor_start(void);
#endif
#if defined(EXAMPLE_POTENTIOMETER)
 void potentiometer_start(void);  
#endif   
#if defined(EXAMPLE_RAMP)
  void ramp_start(void);
#endif   
#if defined(EXAMPLE_PI)
  void NewPIval_start(void);
#endif    
#if defined(EXAMPLE_CONTROLMODE)
 void TqSpeedMode_start(void);
#endif 
    
/* Private function prototypes -----------------------------------------------*/

void SysTick_Configuration(void);

/* Private variables ---------------------------------------------------------*/

CMCI oMCI[MC_NUM];
CMCT oMCT[MC_NUM];  
uint32_t wConfig[MC_NUM] = {UI_CONFIG_M1,UI_CONFIG_M2};


/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/  

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
  
#if !defined(STM32F0XX)
  /*NVIC Priority group configuration.
    Default option is NVIC_PriorityGroup_3. 
  */
  NVIC_PriorityGroupConfig(NVIC_PriorityGroup_3);
#endif
  
  /*MCInterface and MCTuning boot*/
  MCboot(oMCI,oMCT);
  
  #if defined(PFC_ENABLED)
    PFC_Boot(oMCT[0],(CMCT)MC_NULL, (int16_t *)MC_NULL);
  #endif
    
  /*Systick configuration.*/
  SysTick_Configuration();
  
  /* Start here ***************************************************************/
  /* GUI, this section is present only if LCD, DAC or serial communication is */
  /* enabled.                                                                 */
#if (defined(LCD_FUNCTIONALITY) | defined(DAC_FUNCTIONALITY) | defined(SERIAL_COMMUNICATION))
  UI_TaskInit(UI_INIT_CFG,wConfig,MC_NUM,oMCI,oMCT,s_fwVer);
#endif  
  /* End here******************************************************************/  
  
  while(1)
  {        
#ifdef SERIAL_COMMUNICATION
    /* Start here ***********************************************************/
    /* GUI, this section is present only if serial communication is enabled.*/
    if (UI_SerialCommunicationTimeOutHasElapsed())
    {
      // Send timeout message
      Exec_UI_IRQ_Handler(UI_IRQ_USART,3,0); // Flag 3 = Send timeout error*/
    }
    /* End here**************************************************************/
#endif

#ifdef LCD_FUNCTIONALITY    
    /* Start here ***********************************************************/
    /* GUI, this section is present only if LCD is enabled.                 */
    if (UI_IdleTimeHasElapsed())
    {  
      UI_SetIdleTime(UI_TASK_OCCURENCE_TICKS);
      UI_LCDRefresh();
    }
    /* End here**************************************************************/  
#endif

/********************************   EXAMPLE AREA ******************************/
#if defined(EXAMPLE_POTENTIOMETER)
   potentiometer_start();  
#endif   
#if defined(EXAMPLE_RAMP)
   ramp_start();
#endif   
#if defined(EXAMPLE_PI)
   NewPIval_start();
#endif    
#if defined(EXAMPLE_CONTROLMODE)
   TqSpeedMode_start();
#endif
#if defined(EXAMPLE_SPEEDMONITOR)
   speedmonitor_start();
#endif
/*****************************************************************************/
  }
}
/**
  * @brief  Configures the SysTick.
  * @param  None
  * @retval None
  */
void SysTick_Configuration(void)
{
  /* Setup SysTick Timer for 500 usec interrupts  */
  if (SysTick_Config((SystemCoreClock) / SYS_TICK_FREQUENCY))
  { 
    /* Capture error */ 
    while (1);
  }
  
  NVIC_SetPriority(SysTick_IRQn, SYSTICK_PRIORITY);
  NVIC_SetPriority(PendSV_IRQn, PENDSV_PRIORITY);
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

/******************* (C) COPYRIGHT 2014 STMicroelectronics *****END OF FILE****/
