/**
  ******************************************************************************
  * @file    DAC_UserInterfaceClass.c
  * @author  IMS Systems Lab and Technical Marketing - MC Team
  * @version 3.0
  * @date    05-Apr-2011 11:34
  * @brief   This file contains private impelementation of DAC class      
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

/* Includes ------------------------------------------------------------------*/
#include "UserInterfaceClass.h"
#include "UserInterfacePrivate.h"
#include "DAC_UserInterfaceClass.h"
#include "DAC_UserInterfacePrivate.h"

#ifdef MC_CLASS_DYNAMIC
	#include "stdlib.h" /* Used for dynamic allocation */
#else
	#include "MC_type.h"
	#define MAX_DAC_UI_NUM 1u

	_DCDAC_UI_t DAC_UIpool[MAX_DAC_UI_NUM];
	unsigned char DAC_UI_Allocated = 0u;
#endif
  
#define DACOFF 32768

static void DAC_Init_(CUI this);
static void DAC_Exec(CUI this);
static void DAC_ChannelConfig(CUI this, DAC_Channel_t bChannel, 
                              MC_Protocol_REG_t bVariable);
static void DAC_SetUserChannelValue(CUI this, uint8_t bUserChNumber, 
                              int16_t hValue);
static int16_t DAC_GetUserChannelValue(CUI this, uint8_t bUserChNumber);

/**
  * @brief  Creates an object of the class DAC
  * @param  pUserInterfaceParams pointer to an UserInterface parameters structure
  * @param  pDACParams pointer to an DAC parameters structure
  * @retval CDAC_UI new instance of DAC object
  */
CDAC_UI DAC_NewObject(pUserInterfaceParams_t pUserInterfaceParams, pDACParams_t pDACParams)
{
	_CUI _oUserInterface;
	_DCDAC_UI _oDAC;

	_oUserInterface = (_CUI)UI_NewObject(pUserInterfaceParams);

	#ifdef MC_CLASS_DYNAMIC
		_oDAC = (_DCDAC_UI)calloc(1u,sizeof(_DCDAC_UI_t));
	#else
		if (DAC_UI_Allocated  < MAX_DAC_UI_NUM)
		{
			_oDAC = &DAC_UIpool[DAC_UI_Allocated++];
		}
		else
		{
			_oDAC = MC_NULL;
		}
	#endif
  
	_oDAC->pDParams_str = pDACParams;
	_oUserInterface->DerivedClass = (void*)_oDAC;
  
	_oUserInterface->Methods_str.pUI_DACInit = &DAC_Init_;
  _oUserInterface->Methods_str.pUI_DACExec = &DAC_Exec;
  _oUserInterface->Methods_str.pUI_DACChannelConfig = &DAC_ChannelConfig;
  _oUserInterface->Methods_str.pUI_DACSetUserChannelValue = 
                                                      &DAC_SetUserChannelValue;
  _oUserInterface->Methods_str.pUI_DACGetUserChannelValue = 
                                                      &DAC_GetUserChannelValue;

	return ((CDAC_UI)_oUserInterface);
}

/** @addtogroup STM32F10x_PMSM_UI_Library
  * @{
  */
  
/** @addtogroup DAC_UserInterface
  * @{
  */

/** @defgroup DAC_class_private_methods DAC class private methods
* @{
*/

/**
  * @brief  Hardware and software initialization of the DAC object. This is the
  *         implementation of the virtual function.
  * @param  this related object of class UI. It must be a DACx_UI object casted
  *         to CUI otherwise the DACInit method will have no effect.
  * @retval none.
  */
static void DAC_Init_(CUI this)
{  
  GPIO_InitTypeDef GPIO_InitStructure; 
  DAC_InitTypeDef DAC_InitStructure;
  
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_DAC, ENABLE);
  
  /* DAC Configuration */
  DAC_DeInit();
  DAC_InitStructure.DAC_Trigger = DAC_Trigger_Software;
  DAC_InitStructure.DAC_WaveGeneration = DAC_WaveGeneration_None;
  DAC_InitStructure.DAC_OutputBuffer = DAC_OutputBuffer_Disable;
  DAC_InitStructure.DAC_LFSRUnmask_TriangleAmplitude=DAC_TriangleAmplitude_1;
  DAC_Init(DAC_Channel_1, &DAC_InitStructure);
  DAC_Init(DAC_Channel_2, &DAC_InitStructure);
  /* Enable DAC Channel1 */
  DAC_Cmd(DAC_Channel_1, ENABLE);
  /* Enable DAC Channel2 */
  DAC_Cmd(DAC_Channel_2, ENABLE);
    
  /* Enable GPIOA */
  RCC_APB2PeriphClockCmd( RCC_APB2Periph_GPIOA, ENABLE);
  
  /* Configure DAC Output Pin */
  GPIO_StructInit(&GPIO_InitStructure);
  /* GPIOA Configuration: PA4, PA5 Channel Output */
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4 | GPIO_Pin_5;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(GPIOA, &GPIO_InitStructure);
}

/**
  * @brief  This method is used to update the DAC outputs. The selected 
  *         variables will be provided in the related output channels. This is 
  *         the implementation of the virtual function.
  * @param  this related object of class UI. It must be a DACx_UI object casted
  *         to CUI otherwise the DACInit method will have no effect.
  * @retval none.
  */
static void DAC_Exec(CUI this)
{
	MC_Protocol_REG_t bCh1_var,bCh2_var;
  bCh1_var = ((_DCDAC_UI)(((_CUI)this)->DerivedClass))->
    DVars_str.bChannel_variable[DAC_CH0];
  bCh2_var = ((_DCDAC_UI)(((_CUI)this)->DerivedClass))->
    DVars_str.bChannel_variable[DAC_CH1];
  
  DAC_SetDualChannelData(DAC_Align_12b_L,
                  DACOFF + ((int16_t)UI_GetReg(this,bCh2_var)),
                  DACOFF + ((int16_t)UI_GetReg(this,bCh1_var)));
  
  DAC_DualSoftwareTriggerCmd(ENABLE);
  
}

/**
  * @brief  This method is used to set up the DAC outputs. The selected
  *         variables will be provided in the related output channels after next
  *         DACExec. This is the implementation of the virtual function.
  * @param  this related object of class UI. It must be a DACx_UI object casted
  *         to CUI otherwise the DACInit method will have no effect.
  * @param  bChannel the DAC channel to be programmed. It must be one of the 
  *         exported channels Ex. DAC_CH0.
  * @param  bVariable the variables to be provided in out through the selected
  *         channel. It must be one of the exported UI register Ex. 
  *         MC_PROTOCOL_REG_I_A.
  * @retval none.
  */
static void DAC_ChannelConfig(CUI this, DAC_Channel_t bChannel, 
                              MC_Protocol_REG_t bVariable)
{
  ((_DCDAC_UI)(((_CUI)this)->DerivedClass))->
    DVars_str.bChannel_variable[bChannel] = bVariable;
}

/**
  * @brief  This method is used to set the value of the "User DAC channel".
  *         This is the implementation of the virtual function.
  * @param  this related object of class UI. It must be a DACx_UI object casted
  *         to CUI otherwise the DACInit method will have no effect.
  * @param  bUserChNumber the "User DAC channel" to be programmed.
  * @param  hValue the value to be put in output.
  * @retval none.
  */
void DAC_SetUserChannelValue(CUI this, uint8_t bUserChNumber, 
                              int16_t hValue)
{
  ((_DCDAC_UI)(((_CUI)this)->DerivedClass))->
    DVars_str.hUserValue[bUserChNumber] = hValue;
}

/**
  * @brief  This method is used to get the value of the "User DAC channel".
  *         This is the implementation of the virtual function.
  * @param  this related object of class UI. It must be a DACx_UI object casted
  *         to CUI otherwise the DACInit method will have no effect.
  * @param  bUserChNumber the "User DAC channel" to be programmed.
  * @retval none.
  */
int16_t DAC_GetUserChannelValue(CUI this, uint8_t bUserChNumber)
{
  return ((_DCDAC_UI)(((_CUI)this)->DerivedClass))->
    DVars_str.hUserValue[bUserChNumber];
}
/**
  * @}
  */
  
/**
  * @}
  */

/**
  * @}
  */

/******************* (C) COPYRIGHT 2011 STMicroelectronics *****END OF FILE****/
