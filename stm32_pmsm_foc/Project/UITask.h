/**
  ******************************************************************************
  * @file    UITask.h
  * @author  IMS Systems Lab and Technical Marketing - MC Team
  * @version 3.0
  * @date    05-Apr-2011 11:34
  * @brief   Interface of UITask module      
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
#ifndef __UITASK_H
#define __UITASK_H

#include "UserInterfaceClass.h"
#include "DAC_UserInterfaceClass.h"
#include "DACRCTIMER_UserInterfaceClass.h"
#include "DACSPI_UserInterfaceClass.h"
#include "DACSPIAD7303_UserInterfaceClass.h"
#include "LCDManager_UserInterfaceClass.h"
#include "MotorControlProtocolClass.h"
#include "FrameCommunicationProtocolClass.h"
#include "PhysicalLayerCommunication_Class.h"
#include "USART_PhysicalLayerCommunication_Class.h"
#include "UIIRQHandlerClass.h"

/* Private definition ---------------------------------------------------------*/
void UI_TaskInit(uint8_t cfg, uint32_t* pUICfg, uint8_t bMCNum, CMCI oMCIList[],
                 CMCT oMCTList[],const char* s_fwVer);
void UI_LCDRefresh(void);
void UI_DACUpdate(uint8_t bMotorNbr);
CLCD_UI GetLCD(void);
CMCP_UI GetMCP(void);
CUI GetDAC(void);

#endif /* __UITASK_H */

/******************* (C) COPYRIGHT 2011 STMicroelectronics *****END OF FILE****/
