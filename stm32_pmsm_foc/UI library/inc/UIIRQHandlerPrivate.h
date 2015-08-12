/**
  ******************************************************************************
  * @file    UIIRQHandlerPrivate.h
  * @author  IMS Systems Lab and Technical Marketing - MC Team
  * @version 3.0
  * @date    05-Apr-2011 11:34
  * @brief   UI IRQ handler class private definition
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
#ifndef __UI_IRQHANDLERPRIVATE_H
#define __UI_IRQHANDLERPRIVATE_H

/*private:*/
/*Class name*/
typedef struct
{
  void* (*pIRQ_Handler)(void *this, unsigned char flag, unsigned short rx_data);
}_CUIIRQ_t,*_CUIIRQ;

/*Methods*/
void Set_UI_IRQ_Handler(unsigned char bIRQAddr,_CUIIRQ oIRQ);

#endif /* __UI_IRQHANDLERPRIVATE_H */

/******************* (C) COPYRIGHT 2011 STMicroelectronics *****END OF FILE****/
