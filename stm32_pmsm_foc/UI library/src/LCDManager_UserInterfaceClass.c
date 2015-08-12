/**
  ******************************************************************************
  * @file    LCDManager_UserInterfaceClass.c
  * @author  IMS Systems Lab and Technical Marketing - MC Team
  * @version 3.0
  * @date    05-Apr-2011 11:34
  * @brief   This file contains private impelementation of LCDManager class      
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
#include "LCDManager_UserInterfaceClass.h"
#include "LCDManager_UserInterfacePrivate.h"
#include "LCDIExportedFunctions.h"

#define DCLASS_VARS  &(((_DCLCD_UI)(((_CUI) this)->DerivedClass))->DVars_str)

#ifdef MC_CLASS_DYNAMIC
	#include "stdlib.h" /* Used for dynamic allocation */
#else
	#include "MC_type.h"
	#define MAX_LCD_UI_NUM 1u

	_DCLCD_UI_t LCD_UIpool[MAX_LCD_UI_NUM];
	unsigned char LCD_UI_Allocated = 0u;
#endif

/**
  * @brief  Creates an object of the class LCDManager
  * @param  pUserInterfaceParams pointer to an UserInterface parameters structure
  * @param  pLCDManagerParams pointer to an LCDManager parameters structure
  * @retval CLCD_UI new instance of LCDManager object
  */
CLCD_UI LCD_NewObject(pUserInterfaceParams_t pUserInterfaceParams, pLCDManagerParams_t pLCDManagerParams)
{
	_CUI _oUserInterface;
	_DCLCD_UI _oLCDManager;

	_oUserInterface = (_CUI)UI_NewObject(pUserInterfaceParams);

	#ifdef MC_CLASS_DYNAMIC
		_oLCDManager = (_DCLCD_UI)calloc(1u,sizeof(_DCLCD_UI_t));
	#else
		if (LCD_UI_Allocated  < MAX_LCD_UI_NUM)
		{
			_oLCDManager = &LCD_UIpool[LCD_UI_Allocated++];
		}
		else
		{
			_oLCDManager = MC_NULL;
		}
	#endif
  
	_oLCDManager->pDParams_str = pLCDManagerParams;
	_oUserInterface->DerivedClass = (void*)_oLCDManager;
  
	return ((CLCD_UI)_oUserInterface);
}

/** @addtogroup STM32F10x_PMSM_UI_Library
  * @{
  */
  
/** @addtogroup LCD_Manager_UserInterface
  * @{
  */

/** @defgroup LCDManager_class_private_methods LCDManager class private methods
* @{
*/

/**
  * @}
  */
  
/**
  * @}
  */

/**
  * @}
  */

void* const* g_ImportedFunctions = MC_NULL;

/**
  * @brief  Initialization of LCD object. It must be called after the UI_Init.
  * @param  this related object of class CLCD_UI.
  * @param  oDAC related DAC object upcasted to CUI. It can be MC_NULL.
  * @param  s_fwVer String contating firmware version.
  * @retval none.
  */
void LCD_Init(CLCD_UI this, CUI oDAC, const char* s_fwVer)
{
  //LCDI_Init((CUI)this, oDAC);
  pLCDI_Init_t pLCDI_Init = (pLCDI_Init_t)(g_ImportedFunctions[EF_LCDI_Init]);
  (*pLCDI_Init)((CUI)this, oDAC, s_fwVer);
}

/**
  * @brief  Execute the LCD execution and refreshing. It must be called 
  *         periodically.
  * @param  this related object of class CLCD_UI.
  * @retval none.
  */
void LCD_Exec(CLCD_UI this)
{
  //LCDI_Polling();
  pLCDI_Polling_t pLCDI_Polling = (pLCDI_Polling_t)(g_ImportedFunctions[EF_LCDI_Polling]);  
  (*pLCDI_Polling)();
}

/**
  * @brief  It is used to force a refresh of all LCD values.
  * @param  this related object of class CLCD.
  * @retval none.
  */
void LCD_UpdateAll(CLCD_UI this)
{
  //LCDI_UpdateAll((CUI)this);
  pLCDI_UpdateAll_t pLCDI_UpdateAll = (pLCDI_UpdateAll_t)(g_ImportedFunctions[EF_LCDI_UpdateAll]);
  (*pLCDI_UpdateAll)((CUI)this);
}

/**
  * @brief  It is used to force a refresh of only measured LCD values.
  * @param  this related object of class CLCD.
  * @retval none.
  */
void LCD_UpdateMeasured(CLCD_UI this)
{
  //LCDI_UpdateMeasured((CUI)this);
  pLCDI_UpdateMeasured_t pLCDI_UpdateMeasured = (pLCDI_UpdateMeasured_t)(g_ImportedFunctions[EF_LCDI_UpdateMeasured]);
  (*pLCDI_UpdateMeasured)((CUI)this);
}

/**
  * @brief  It is used to store the LCDI Imported functions.
  * @param  void** List of imported functions.
  * @retval none.
  */
void LCD_SetLCDIImportedFunctions(void* const* ImportedFunctions)
{
  g_ImportedFunctions = ImportedFunctions;
}

/******************* (C) COPYRIGHT 2011 STMicroelectronics *****END OF FILE****/
