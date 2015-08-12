/**
  ******************************************************************************
  * @file    PhysicalLayerCommunication_Class.h
  * @author  IMS Systems Lab and Technical Marketing - MC Team
  * @version 3.0
  * @date    05-Apr-2011 11:34
  * @brief   This file contains interface of Physical Layer Communication class      
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
#ifndef __PLC_H
#define __PLC_H

/** @addtogroup STM32F10x_PMSM_UI_Library
  * @{
  */

/** @addtogroup PhysicalLayerCommunication
  * @{
  */
  
/** @defgroup PhysicalLayerCommunication_class_exported_types Physical Layer Communication class exported types
* @{
*/

/*Class name*/
typedef struct CCOM_t *CCOM;

#include "MC_type.h"
#include "FrameCommunicationProtocolClass.h"

/* Exported types ------------------------------------------------------------*/

/**
* @}
*/

/** @defgroup PhysicalLayerCommunication_class_exported_methods Physical Layer Communication class exported methods
  * @{
  */

/*Methods*/
CCOM COM_NewObject(void);
void COM_SetParent(CCOM this, CFCP oFCP); // FCP
void COM_ResetTX(CCOM this);
void COM_ResetRX(CCOM this);
void COM_SendBuffer(CCOM this,u8 *pBuffer, u16 sizeToSend);
void COM_ReceiveBuffer(CCOM this,u8 *pBuffer, u16 sizeToReceive);
void COM_StartReceive(CCOM this); /* executed by derived classes */
void COM_StartTransmit(CCOM this); /* executed by derived classes */

/**
  * @}
  */

/**
  * @}
  */

/**
  * @}
  */

#endif /* __PLC_H */

/******************* (C) COPYRIGHT 2011 STMicroelectronics *****END OF FILE****/