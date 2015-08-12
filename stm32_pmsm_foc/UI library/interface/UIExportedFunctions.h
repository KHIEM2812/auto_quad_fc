/**
  ******************************************************************************
  * @file    UIExportedFunctions.h
  * @author  IMS Systems Lab and Technical Marketing - MC Team
  * @version 3.0
  * @date    05-Apr-2011 11:34
  * @brief   This file contains the definitions of UI exported functions      
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
#ifndef __UIEXPORTEDFUNCTIONS_H
#define __UIEXPORTEDFUNCTIONS_H

enum {
EF_UI_GetReg,
EF_UI_ExecSpeedRamp,
EF_UI_SetReg,
EF_UI_ExecCmd,
EF_UI_GetSelectedMCConfig,
EF_UI_SetRevupData,
EF_UI_GetRevupData,
EF_UI_DACChannelConfig,
EF_UI_SetCurrentReferences,
EF_UI_NUMBERS
};

typedef int32_t (*pUI_GetReg_t) (CUI,MC_Protocol_REG_t);
typedef bool (*pUI_ExecSpeedRamp_t)(CUI,int32_t,uint16_t);
typedef bool (*pUI_SetReg_t)(CUI,MC_Protocol_REG_t,int32_t);
typedef bool (*pUI_ExecCmd_t)(CUI,uint8_t);
typedef uint32_t (*pUI_GetSelectedMCConfig_t)(CUI);
typedef bool (*pUI_SetRevupData_t)(CUI,uint8_t,uint16_t,int16_t,int16_t);
typedef bool (*pUI_GetRevupData_t)(CUI,uint8_t,uint16_t*,int16_t*,int16_t*);
typedef void (*pUI_DACChannelConfig_t)(CUI,DAC_Channel_t,MC_Protocol_REG_t);
typedef void (*pUI_SetCurrentReferences_t)(CUI,int16_t,int16_t); 

#endif /*__UIEXPORTEDFUNCTIONS_H*/
/******************* (C) COPYRIGHT 2011 STMicroelectronics *****END OF FILE****/
