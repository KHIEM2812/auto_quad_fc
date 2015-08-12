/**
  ******************************************************************************
  * @file    main.c 
  * @author  IMS Systems Lab and Technical Marketing - MC Team
  * @version 3.0
  * @date    05-Apr-2011 11:34
  * @brief   User interface main program body
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
#include "LCD_Interface.h"
#include "LCDIExportedFunctions.h"

// Setup the exported functions see LCDIExportedFunctions.h enum.
void* const exportedFunctions[EF_LCDI_NUMBERS] =
{
  (void*)(&LCDI_Init),
  (void*)(&LCDI_UpdateMeasured),
  (void*)(&LCDI_UpdateAll),
  (void*)(&LCDI_Polling)
};

#define HardFault_Handler 0xABCDEF12

/* IAR dependent */
extern void __iar_data_init3(void);

void main (void)
{
  /* Don't run application from here. Just flash the code and use MC project. */
}

/**
  * @brief  This function is used as entry point for LCD UI.
  * @param  void** List of imported functions.
  * @retval void** List of exported functions.
  */
void* const* LCDI_Entry(void** ImportedFunctions)
{
  /* Init globals variables and objects */
  __iar_data_init3(); /* IAR dependent */
  
  LCDI_SetUIImportedFunctions(ImportedFunctions);
  return exportedFunctions;
}
/******************* (C) COPYRIGHT 2011 STMicroelectronics *****END OF FILE****/
