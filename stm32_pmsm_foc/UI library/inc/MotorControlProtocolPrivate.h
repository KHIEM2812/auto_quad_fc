/**
  ******************************************************************************
  * @file    MotorControlProtocolPrivate.h
  * @author  IMS Systems Lab and Technical Marketing - MC Team
  * @version 3.0
  * @date    05-Apr-2011 11:34
  * @brief   Private definition for MotorControlProtocol class
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
#ifndef __MCP_MCUI_H
#define __MCP_MCUI_H

typedef struct
{
  // Derived Class variables 
  CFCP oFCP;
  u8 BufferFrame[FRAME_MAX_BUFFER_LENGTH];
  u8 BufferSize;
  const char *s_fwVer;
  CUI oDAC;
}DVars_t,*pDVars_t;

typedef MCPParams_t DParams_t, *pDParams_t; 

typedef struct
{
  DVars_t DVars_str;
  pDParams_t pDParams_str;
}_DCMCP_t, *_DCMCP;

#endif /* __MCP_MCUI_H */

/******************* (C) COPYRIGHT 2011 STMicroelectronics *****END OF FILE****/
