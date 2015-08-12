/**
  ******************************************************************************
  * @file    FrameCommunicationProtocolClass.h
  * @author  IMS Systems Lab and Technical Marketing - MC Team
  * @version 3.0
  * @date    05-Apr-2011 11:34
  * @brief   This file contains interface of FrameCommunicationProtocol class      
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
#ifndef __FCPC_H
#define __FCPC_H

/** @addtogroup STM32F10x_PMSM_UI_Library
  * @{
  */

/** @addtogroup FrameCommunicationProtocol
  * @{
  */
  
/** @defgroup FrameCommunicationProtocol_class_exported_types Frame Communication Protocol class exported types
* @{
*/

/*Class name*/
typedef struct CFCP_t *CFCP;

#include "MC_type.h"

#include "PhysicalLayerCommunication_Class.h"

/* Exported constants --------------------------------------------------------*/
#define FRAME_ERROR_NONE              0x00
#define FRAME_ERROR_TRANSFER_ONGOING  0x01
#define FRAME_ERROR_WAITING_TRANSFER  0x02 
#define FRAME_ERROR_INVALID_PARAMETER 0x03 
#define FRAME_ERROR_TIME_OUT          0x04
#define FRAME_ERROR_INVALID_FRAME     0x05


#define FRAME_MAX_BUFFER_LENGTH  0xFF
#define FRAME_HEADER_SIZE        0x02
#define FRAME_CRC_SIZE           0x01
#define FRAME_MAX_SIZE           (FRAME_HEADER_SIZE + FRAME_MAX_BUFFER_LENGTH + FRAME_CRC_SIZE)

#define FRAME_ACK_SIZE           0x01
#define FRAME_ACK_CODE           0xFF

/* Exported types ------------------------------------------------------------*/
typedef void (*PFN_TIMEOUT)();

/* Exported types ------------------------------------------------------------*/
/** 
  * @brief  FrameCommunicationProtocol class parameters definition  
  */
typedef const struct
{
  // Parameters
  u32 TimeOutRXByte;
  u32 TimeOutTXByte;
  PFN_TIMEOUT RXTimeOutEvent;
  PFN_TIMEOUT TXTimeOutEvent;
} FCPParams_t, *pFCPParams_t;

#include "UserInterfaceClass.h"
#include "MotorControlProtocolClass.h"

/**
* @}
*/

/** @defgroup FrameCommunicationProtocol_class_exported_methods Frame Communication Protocol class exported methods
  * @{
  */

/*Methods*/
CFCP FCP_NewObject(pFCPParams_t pFCPParam);
void FCP_Init(CFCP this, CCOM oCOM);
void FCP_SetParent(CFCP this, CMCP_UI oMCP);
void Frame_ResetTX(CFCP this);                 
void Frame_ResetRX(CFCP this);                 
u8 Frame_Receive(CFCP this, u8 *code, u8 *buffer, u8 *size);
u8 Frame_Send(CFCP this, u8 code, u8 *buffer, u8 size);
void SendingFrame(CFCP this, u8 *buffer, u16 bytes);
void* ReceivingFrame(CFCP this, u8 *buffer, u16 size);
void FCPTimeOut(CFCP this);
void FCP_SendOverrunMeassage(CFCP this);
void FCP_SendTimeoutMeassage(CFCP this);

/**
  * @}
  */

/**
  * @}
  */

/**
  * @}
  */

#endif /* __FCPC_H */

/******************* (C) COPYRIGHT 2011 STMicroelectronics *****END OF FILE****/
