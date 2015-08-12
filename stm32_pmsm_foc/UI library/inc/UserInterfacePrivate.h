/**
  ******************************************************************************
  * @file    UserInterfacePrivate.h
  * @author  IMS Systems Lab and Technical Marketing - MC Team
  * @version 3.0
  * @date    05-Apr-2011 11:34
  * @brief   This file contains private definition of UserInterface class      
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
#ifndef __USERINTERFACEPRIVATE_H
#define __USERINTERFACEPRIVATE_H

/** @addtogroup STM32F10x_PMSM_UI_Library
  * @{
  */

/** @addtogroup UserInterface
  * @{
  */

/** @defgroup UserInterface_class_private_types UserInterface class private types
* @{
*/

/** 
  * @brief  UserInterface class members definition
  */
typedef struct
{
  uint8_t bDriveNum;      /*!< Total number of MC objects.*/
  CMCI* pMCI;             /*!< Pointer of MC interface list.*/
  CMCT* pMCT;             /*!< Pointer of MC tuning list.*/
  uint32_t* pUICfg;       /*!< Pointer of UI configuration list.*/
  uint8_t bSelectedDrive; /*!< Current selected MC object in the list.*/
}Vars_t,*pVars_t;

/** 
  * @brief  Redefinition of parameter structure
  */
typedef UserInterfaceParams_t Params_t, *pParams_t;

/**
  * @brief Virtual methods container
  */
typedef struct
{
	void (*pUI_DACInit)(CUI this);
  void (*pUI_DACExec)(CUI this);
  void (*pUI_DACChannelConfig)(CUI this, DAC_Channel_t bChannel, 
                               MC_Protocol_REG_t bVariable);
  void (*pUI_DACSetUserChannelValue)(CUI this, uint8_t bUserChNumber, 
                               int16_t hValue);
  int16_t (*pUI_DACGetUserChannelValue)(CUI this, uint8_t bUserChNumber);
}Methods_t,*pMethods_t;

/** 
  * @brief  Private UserInterface class definition 
  */
typedef struct
{
  Methods_t Methods_str;	/*!< Virtual methods container */
	Vars_t Vars_str; 		/*!< Class members container */
	pParams_t pParams_str;	/*!< Class parameters container */
	void *DerivedClass;		/*!< Pointer to derived class */
}_CUI_t, *_CUI;
/**
  * @}
  */
  
/**
  * @}
  */

/**
  * @}
  */

#endif /*__USERINTERFACEPRIVATE_H*/

/******************* (C) COPYRIGHT 2011 STMicroelectronics *****END OF FILE****/
