/**
  ******************************************************************************
  * @file    LCD_Interface.h
  * @author  IMS Systems Lab and Technical Marketing - MC Team
  * @version 3.0
  * @date    05-Apr-2011 11:34
  * @brief   Header of "LCD Interface" module
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

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __LCD_INTERFACE_H
#define __LCD_INTERFACE_H

/* Exported Defines ----------------------------------------------------------*/

#ifdef __cplusplus
 extern "C" {
#endif
   
#define this _this
#include "UserInterfaceClass.h"
#undef this

void LCDI_Init(CUI oUI, CUI oDAC, const char* s_fwVer);
void LCDI_UpdateAll(CUI oUI);
void LCDI_UpdateMeasured(CUI oUI);
void LCDI_Polling(void);
void LCDI_SetUIImportedFunctions(void* const* ImportedFunctions);

#ifdef __cplusplus
 }
#endif

#endif /* __LCD_INTERFACE_H */

/******************* (C) COPYRIGHT 2011 STMicroelectronics *****END OF FILE****/
