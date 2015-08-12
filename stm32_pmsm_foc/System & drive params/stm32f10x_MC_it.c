/**
  ******************************************************************************
  * @file    stm32f10x_MC_it.c 
  * @author  ST Motor Control Workbench ver.0.9.11.0
  * @version 3.0
  * @date    05-Apr-2011 11:34
  * @brief   Main Interrupt Service Routines.
  *          This file provides template for all exceptions handler and 
  *          peripherals interrupt service routine, related to Motor Control
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
#include "MCIRQHandlerClass.h"
#include "UIIRQHandlerClass.h"
#include "MCInterfaceClass.h"
#include "MCTuningClass.h"
#include "MC_type.h"
#include "MCTasks.h"
#include "UITask.h"
#include "Parameters conversion.h"
#include "Parameters conversion motor 2.h"

/** @addtogroup STM32F10x_StdPeriph_Template
  * @{
  */

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/******************************************************************************/
/*                 STM32F10x Peripherals Interrupt Handlers                   */
/*  Add here the Interrupt Handler for the used peripheral(s) (PPP), for the  */
/*  available peripheral interrupt handler's name please refer to the startup */
/*  file (startup_stm32f10x_xx.s).                                            */
/******************************************************************************/

// STMCWB TESTING TOKEN 1 ROW H5
/**
  * @brief  This function handles ADC1/ADC2 interrupt request.
  * @param  None
  * @retval None
  */
void ADC1_2_IRQHandler(void)
{
ADC1->SR &= ~(u32)(ADC_FLAG_JEOC | ADC_FLAG_JSTRT);
#ifdef DAC_FUNCTIONALITY
  UI_DACUpdate(TSK_HighFrequencyTask());  /*GUI, this section is present only if DAC is enabled*/
#else
  TSK_HighFrequencyTask();          /*GUI, this section is present only if DAC is disabled*/
#endif 
}
// STMCWB TESTING END


// STMCWB TESTING TOKEN 2 ROW 
// don't generate
// STMCWB TESTING END


// STMCWB TESTING TOKEN 3 ROW H7
/**
  * @brief  This function handles TIM1 Update interrupt request.
  * @param  None
  * @retval None
  */
void TIM1_UP_IRQHandler(void)
{
TIM1->SR = (uint16_t)(~TIM_FLAG_Update);
Exec_IRQ_Handler(MC_IRQ_PWMNCURRFDBK_1,0);
}
// STMCWB TESTING END


// STMCWB TESTING TOKEN 4 ROW 
// don't generate
// STMCWB TESTING END


// STMCWB TESTING TOKEN 5 ROW 
// don't generate
// STMCWB TESTING END


// STMCWB TESTING TOKEN 6 ROW 
// don't generate
// STMCWB TESTING END


// STMCWB TESTING TOKEN 7 ROW 
// don't generate
// STMCWB TESTING END


// STMCWB TESTING TOKEN 8 ROW 
// don't generate
// STMCWB TESTING END


// STMCWB TESTING TOKEN 9 ROW 
// don't generate
// STMCWB TESTING END


// STMCWB TESTING TOKEN 10 ROW 
// don't generate
// STMCWB TESTING END


#ifdef SERIAL_COMMUNICATION
/*Start here***********************************************************/
/*GUI, this section is present only if serial communication is enabled*/
/**
  * @brief  This function handles USART1 interrupt request.
  * @param  None
  * @retval None
  */
void USART1_IRQHandler(void)
{
  typedef void* (*pExec_UI_IRQ_Handler_t) (unsigned char bIRQAddr, 
                                                            unsigned char flag);
  uint16_t hUSART_SR = USART1->SR;
  uint16_t hUSART_DR = USART1->DR;
  
  if (hUSART_SR & USART_SR_ORE) /* Overrun error occurs before SR access */
  {
    /* Send Overrun message */
    TB_SerialCommunicationTimeOutStop();
    Exec_UI_IRQ_Handler(UI_IRQ_USART,2,0); /* Flag 2 = Send overrun error*/
  }
  else if (USART1->SR & USART_SR_ORE) // Overrun error occurs after SR access and before DR access
  {
    /* Send Overrun message */
    TB_SerialCommunicationTimeOutStop();
    Exec_UI_IRQ_Handler(UI_IRQ_USART,2,0); /* Flag 2 = Send overrun error */
    USART1->DR;
  }
  else if (hUSART_SR & USART_SR_RXNE) /* Valid data received */
  {
    uint16_t retVal;
    retVal = *(uint16_t*)(Exec_UI_IRQ_Handler(UI_IRQ_USART,0,hUSART_DR)); /* Flag 0 = RX */
    if (retVal == 1)
    {
      TB_SerialCommunicationTimeOutStart();
    }
    if (retVal == 2)
    {
      TB_SerialCommunicationTimeOutStop();
    }
  }
    
  if(USART_GetITStatus(USART1, USART_IT_TXE) != RESET)
  {   
    Exec_UI_IRQ_Handler(UI_IRQ_USART,1,0); /* Flag 1 = TX */
  }
  
}
/*End here***********************************************************/
#endif

/**
  * @brief  This function handles PPP interrupt request.
  * @param  None
  * @retval None
  */
/*void PPP_IRQHandler(void)
{
}*/

/**
  * @}
  */

/******************* (C) COPYRIGHT 2011 STMicroelectronics *****END OF FILE****/
