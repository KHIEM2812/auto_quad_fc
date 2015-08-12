/**
  ******************************************************************************
  * @file    FrameCommunicationProtocolPrivate.h
  * @author  IMS Systems Lab and Technical Marketing - MC Team
  * @version 3.0
  * @date    05-Apr-2011 11:34
  * @brief   Private definition for FrameCommunicationProtocol
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
#ifndef __FCP_H
#define __FCP_H

/* Includes ------------------------------------------------------------------*/
#include "FrameCommunicationProtocolClass.h"

/* Private typedef -----------------------------------------------------------*/
typedef enum FrameTransmitionState_e
{
  FCP_IDLE,
  TRANSFERING_HEADER,
  TRANSFERING_BUFFER,
  TRANSFERING_CRC,
  TRANSFER_COMPLETE,
} FrameTransmitionState_t;

typedef struct Framedata_s
{ 
    u8 Code;
    u8 Size;  
    u8 Buffer[FRAME_MAX_BUFFER_LENGTH];
    u8 nCRC;
} FrameData_t, *PFrameData_t;

typedef struct FrameTransmition_s
{
    FrameData_t Frame;
    FrameTransmitionState_t State;
    PFN_TIMEOUT OnTimeOutByte;
    u16 FrameTransferError;
} FrameTransmition_t;

typedef struct
{
  // Class variables
  CMCP_UI parent;
  CCOM oCOM; // COM
  FrameTransmition_t frameTransmitionTX;
  FrameTransmition_t frameTransmitionRX;
} Vars_t,*pVars_t;

/* Params re-definition ------------------------------------------------------*/
typedef FCPParams_t Params_t, *pParams_t; 

/* Virtual Methods -----------------------------------------------------------*/
typedef struct
{
  // Class virtual methods TBD
  void (*pVReset)(CFCP this);
}Methods_t,*pMethods_t;

typedef struct
{
  Methods_t Methods_str; /*execution of virtual methods*/
  void *DerivedClass;
  Vars_t Vars_str;
  pParams_t pParams_str;
}_CFCP_t, *_CFCP;

#endif /* __FCP_H */

/******************* (C) COPYRIGHT 2011 STMicroelectronics *****END OF FILE****/
