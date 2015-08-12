/**
  ******************************************************************************
  * @file    PhysicalLayerCommunication_Private.h
  * @author  IMS Systems Lab and Technical Marketing - MC Team
  * @version 3.0
  * @date    05-Apr-2011 11:34
  * @brief   Private definition for Physical Layer Communication
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
#ifndef __COM_H
#define __COM_H

#include "PhysicalLayerCommunication_Class.h"

/* Private typedef -----------------------------------------------------------*/
typedef struct DataSend_s
{
  u8 *Buffer;
  u16 BufferCount;
  u16 BufferTransfer;
} DataSend_t;

typedef struct DataCommunication_s
{
  DataSend_t RX;
  DataSend_t TX;
} DataCommunication_t;

typedef struct
{
  DataCommunication_t PL_Data;
  CFCP parent;
}Vars_t,*pVars_t;

typedef struct
{
  void* (*pIRQ_Handler)(void *this, unsigned char flag, unsigned short rx_data);
  void (*pStartReceive)(CCOM this);
  void (*pStartTransmit)(CCOM this);
}Methods_t,*pMethods_t;

typedef struct
{
  Methods_t Methods_str; /*execution of virtual methods*/
  void *DerivedClass;
  Vars_t Vars_str;
}_CCOM_t, *_CCOM;

#endif /* __COM_H */

/******************* (C) COPYRIGHT 2011 STMicroelectronics *****END OF FILE****/
