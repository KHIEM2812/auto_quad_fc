/**
  ******************************************************************************
  * @file    main.c 
  * @author  IMS Systems Lab and Technical Marketing - MC Team
  * @version 3.0
  * @date    05-Apr-2011 11:34
  * @brief   Main program body
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
#include "MCTuningClass.h"
#include "MCInterfaceClass.h"
#include "MCTasks.h"
#include "Parameters conversion.h"
#include "Parameters conversion motor 2.h"
#include "Timebase.h"
#include "UITask.h"

#include <stdio.h>

#include "stm32_eval.h"
#ifdef USE_STM32100B_EVAL
 #include "stm32100b_eval_lcd.h"
#elif defined USE_STM3210B_EVAL
 #include "stm3210b_eval_lcd.h"
#elif defined USE_STM3210E_EVAL
 #include "stm3210e_eval_lcd.h"
 #warning "If using STM3210E-EVAL, please be informed that - on that board - PA6 is shared between TIM8 BKIN and SPI1 MISO, which means that it’s not possible to enable both Overcurrent protection and LCD UI."
#elif defined USE_STM3210C_EVAL
 #include "stm3210c_eval_lcd.h"
#endif

#if ((defined(STM32PERFORMANCELD) || defined(STM32VALUELD)) && (LCD_JOYSTICK_BUTTON_FUNCTIONALITY == ENABLE))
#error "Invalid configuration: MCU definition in Control stage parameters.h, LD devices not compatible with LCD manager"
#endif

#if (defined(STM32PERFORMANCE) && !defined(STM32F10X_MD))
#error "Invalid configuration: MCU definition in Control stage parameters.h not compatible with selected board"
#endif

#if (defined(STM32VALUE) && !defined(STM32F10X_MD_VL))
#error "Invalid configuration: MCU definition in Control stage parameters.h not compatible with selected board"
#endif

#if (defined(STM32HD) && !defined(STM32F10X_HD))
#error "Invalid configuration: MCU definition in Control stage parameters.h not compatible with selected board"
#endif

#if (defined(STM32VALUE) && !defined(CPU_CLK_24_MHZ))
#error "Invalid configuration: MCU frequency definition in Control stage parameters.h not compatible with selected MCU"
#endif

#define FIRMWARE_VERS "STM32 FOC Lib 3.0\0Ver.3.0"
const char s_fwVer[32] = FIRMWARE_VERS;

#ifdef __GNUC__
/* With GCC/RAISONANCE, small printf (option LD Linker->Libraries->Small printf
   set to 'Yes') calls __io_putchar() */
#define PUTCHAR_PROTOTYPE int __io_putchar(int ch)
#else
#define PUTCHAR_PROTOTYPE int fputc(int ch, FILE *f)
#endif /* __GNUC__ */

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
  
  /*NVIC Priority group configuration.
    Default option is NVIC_PriorityGroup_3. The sole alternative option,
    left to user choice, is NVIC_PriorityGroup_2*/
  NVIC_PriorityGroupConfig(NVIC_PriorityGroup_3);
  
  /*MCInterface and MCTuning boot*/
  MCboot(oMCI,oMCT);
  
  /* Start here ***************************************************************/
  /* GUI, this section is present only if LCD, DAC or serial communication is */
  /* enabled.                                                                 */
#if (defined(LCD_FUNCTIONALITY) | defined(DAC_FUNCTIONALITY) | defined(SERIAL_COMMUNICATION))
  UI_TaskInit(UI_INIT_CFG,wConfig,MC_NUM,oMCI,oMCT,s_fwVer);
#endif  
  /* End here******************************************************************/
  
  /*Systick configuration.*/
  SysTick_Configuration();
          
  while(1)
  {        
#ifdef SERIAL_COMMUNICATION
    /* Start here ***********************************************************/
    /* GUI, this section is present only if serial communication is enabled.*/
    if (TB_SerialCommunicationTimeOutHasElapsed())
    {
      // Send timeout message
      Exec_UI_IRQ_Handler(UI_IRQ_USART,3,0); // Flag 3 = Send timeout error*/
    }
    /* End here**************************************************************/
#endif

#ifdef LCD_FUNCTIONALITY    
    /* Start here ***********************************************************/
    /* GUI, this section is present only if LCD is enabled.                 */
    if (TB_UserInterfaceIdleTimeHasElapsed())
    {  
      TB_SetUserInterfaceIdleTime(UI_TASK_OCCURENCE_TICKS);
      UI_LCDRefresh();
    }
    /* End here**************************************************************/  
#endif

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

  NVIC_SetPriority(SysTick_IRQn, 0x6);
  NVIC_SetPriority(PendSV_IRQn, 0x8);
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

/******************* (C) COPYRIGHT 2011 STMicroelectronics *****END OF FILE****/
