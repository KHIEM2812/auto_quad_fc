/**
  ******************************************************************************
  * @file    LCDManager_UserInterfaceClass.h
  * @author  IMS Systems Lab and Technical Marketing - MC Team
  * @version 3.0
  * @date    05-Apr-2011 11:34
  * @brief   This file contains interface of LCDManager class      
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
#ifndef __LCDMANAGER_USERINTERFACECLASS_H
#define __LCDMANAGER_USERINTERFACECLASS_H

/** @addtogroup STM32F10x_PMSM_UI_Library
  * @{
  */
  
/** @addtogroup LCD_Manager_UserInterface
  * @{
  */

/** @defgroup LCDManager_class_exported_types LCDManager class exported types
* @{
*/

/** 
  * @brief  Public LCDManager class definition
  */
typedef struct CLCD_UI_t *CLCD_UI;

/** 
  * @brief  LCDManager class parameters definition
  */
typedef const void LCDManagerParams_t, *pLCDManagerParams_t;
/**
  * @}
  */

/** @defgroup LCDManager_class_exported_methods LCDManager class exported methods
  * @{
  */
  
/**
  * @brief  Creates an object of the class LCDManager
  * @param  pUserInterfaceParams pointer to an UserInterface parameters structure
  * @param  pLCDManagerParams pointer to an LCDManager parameters structure
  * @retval CLCD_UI new instance of LCDManager object
  */
CLCD_UI LCD_NewObject(pUserInterfaceParams_t pUserInterfaceParams, 
                      pLCDManagerParams_t pLCDManagerParams);

/**
  * @brief  Initialization of LCD object. It must be called after the UI_Init.
  * @param  this related object of class CLCD_UI.
  * @param  oDAC related DAC object upcasted to CUI. It can be MC_NULL.
  * @param  s_fwVer String contating firmware version.
  * @retval none.
  */
void LCD_Init(CLCD_UI this, CUI oDAC, const char* s_fwVer);

/**
  * @brief  Execute the LCD execution and refreshing. It must be called 
  *         periodically.
  * @param  this related object of class CLCD_UI.
  * @retval none.
  */
void LCD_Exec(CLCD_UI this);

/**
  * @brief  It is used to force a refresh of all LCD values.
  * @param  this related object of class CLCD_UI.
  * @retval none.
  */
void LCD_UpdateAll(CLCD_UI this);

/**
  * @brief  It is used to force a refresh of only measured LCD values.
  * @param  this related object of class CLCD_UI.
  * @retval none.
  */
void LCD_UpdateMeasured(CLCD_UI this);

/**
  * @}
  */
  
/**
  * @}
  */

/**
  * @}
  */

/**
  * @brief  It is used to store the LCDI Imported functions.
  * @param  void** List of imported functions.
  * @retval none.
  */
void LCD_SetLCDIImportedFunctions(void* const* ImportedFunctions);

#endif /*__LCDMANAGER_USERINTERFACECLASS_H*/

/******************* (C) COPYRIGHT 2011 STMicroelectronics *****END OF FILE****/
