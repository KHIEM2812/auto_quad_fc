/**
  ******************************************************************************
  * @file    UIIRQClass.c
  * @author  IMS Systems Lab and Technical Marketing - MC Team
  * @version 3.0
  * @date    05-Apr-2011 11:34
  * @brief   User Interface IRQ handler class
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

#include "UIIRQHandlerClass.h"
#include "UIIRQHandlerPrivate.h"

/* Definition of MC IRQ Table */
#define MAX_UI_IRQ_NUM 1
_CUIIRQ oUI_IRQTable[MAX_UI_IRQ_NUM];

void Set_UI_IRQ_Handler(unsigned char bIRQAddr, _CUIIRQ oIRQ)
{
  oUI_IRQTable[bIRQAddr] = oIRQ;
}

void* Exec_UI_IRQ_Handler(unsigned char bIRQAddr, unsigned char flag, unsigned short rx_data)
{  
  return(oUI_IRQTable[bIRQAddr]->pIRQ_Handler((void*)(oUI_IRQTable)[bIRQAddr], flag, rx_data));
}

/******************* (C) COPYRIGHT 2011 STMicroelectronics *****END OF FILE****/
