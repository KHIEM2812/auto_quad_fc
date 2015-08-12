/**
  ******************************************************************************
  * @file    LCDIExportedFunctions.h
  * @author  IMS Systems Lab and Technical Marketing - MC Team
  * @version 3.0
  * @date    05-Apr-2011 11:34
  * @brief   This file contains the definitions of LCDI exported functions      
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
#ifndef __LCDIEXPORTEDFUNCTIONS_H
#define __LCDIEXPORTEDFUNCTIONS_H

enum {
  EF_LCDI_Init,
  EF_LCDI_UpdateMeasured,
  EF_LCDI_UpdateAll,
  EF_LCDI_Polling,
  EF_LCDI_NUMBERS
};

typedef void (*pLCDI_Init_t) (CUI,CUI,const char*);
typedef void (*pLCDI_Polling_t) (void);
typedef void (*pLCDI_UpdateMeasured_t) (CUI);
typedef void (*pLCDI_UpdateAll_t) (CUI oUI);

#endif /*__LCDIEXPORTEDFUNCTIONS_H*/
/******************* (C) COPYRIGHT 2011 STMicroelectronics *****END OF FILE****/
