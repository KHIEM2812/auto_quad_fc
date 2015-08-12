/**
  ******************************************************************************
  * @file    MotorControlProtocolClass.h
  * @author  IMS Systems Lab and Technical Marketing - MC Team
  * @version 3.0
  * @date    05-Apr-2011 11:34
  * @brief   This file contains interface of MotorControlProtocol class      
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
#ifndef __MCP_MCUIC_H
#define __MCP_MCUIC_H

#include "MC_type.h"

/** @addtogroup STM32F10x_PMSM_UI_Library
  * @{
  */

/** @addtogroup MotorControlProtocol
  * @{
  */
  
/** @defgroup MotorControlProtocol_class_exported_types Motor Control Protocol class exported types
* @{
*/

///*Class name*/
typedef struct CMCP_UI_t *CMCP_UI;

#include "FrameCommunicationProtocolClass.h"

/* Exported types ------------------------------------------------------------*/
/** 
  * @brief  MotorControlProtocol class parameters definition  
  */
typedef const struct
{
  // Parameters 
  pFCPParams_t pFCPParams; // FCP
} MCPParams_t, *pMCPParams_t;

/**
* @}
*/

/** @defgroup MotorControlProtocol_class_exported_methods Motor Control Protocol class exported methods
  * @{
  */

/*Methods*/
CMCP_UI MCP_NewObject(pUserInterfaceParams_t pUserInterfaceParams,
                      pMCPParams_t pMCPParams);
void MCP_Init(CMCP_UI this, CFCP oFCP, CUI oDAC, const char* s_fwVer);
void MCP_OnTimeOut(CMCP_UI this);
void MCP_ReceivedFrame(CMCP_UI this, u8 Code, u8 *buffer, u8 Size);
void MCP_SentFrame(CMCP_UI this, u8 Code, u8 *buffer, u8 Size);
void MCP_WaitNextFrame(CMCP_UI this);
void MCP_SendOverrunMeassage(CMCP_UI this);
void MCP_SendTimeoutMeassage(CMCP_UI this);
void MCP_SendBadCRCMessage(CMCP_UI this);

/**
  * @}
  */

/**
  * @}
  */

/**
  * @}
  */

#endif /* __MCP_MCUIC_H */

/******************* (C) COPYRIGHT 2011 STMicroelectronics *****END OF FILE****/
