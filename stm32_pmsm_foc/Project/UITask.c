/**
  ******************************************************************************
  * @file    UITask.c 
  * @author  IMS Systems Lab and Technical Marketing - MC Team
  * @version 3.0
  * @date    05-Apr-2011 11:34
  * @brief   This file implementes user interface tasks definition 
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

/* Includes ------------------------------------------------------------------*/
#include "UITask.h"
#include "USARTParams.h"
#include "UIExportedFunctions.h"
#include "Parameters conversion.h"
#include "Parameters conversion motor 2.h"

#define OPT_DACX  0x20 /*!<Bit field indicating that the UI uses SPI AD7303 DAC.*/

CLCD_UI oLCD = MC_NULL;

CUSART_COM oUSART = MC_NULL;
CFCP oFCP = MC_NULL;
CMCP_UI oMCP = MC_NULL;

CUI oDAC = MC_NULL;

#if defined(STM32F10X_MD)
#define VECT_TABLE_BASE 0x08013800
#endif

#if defined(STM32F10X_MD_VL)
#define VECT_TABLE_BASE 0x08013800
#endif

#if defined(STM32F10X_HD)
#define VECT_TABLE_BASE 0x08070000
#endif

// Setup the exported functions see UIExportedFunctions.h enum.
void* const exportedFunctions[EF_UI_NUMBERS] =
{
  (void*)(&UI_GetReg),
  (void*)(&UI_ExecSpeedRamp),
  (void*)(&UI_SetReg),
  (void*)(&UI_ExecCmd),
  (void*)(&UI_GetSelectedMCConfig),
  (void*)(&UI_SetRevupData),
  (void*)(&UI_GetRevupData),
  (void*)(&UI_DACChannelConfig),
  (void*)(&UI_SetCurrentReferences)
};

void UI_TaskInit(uint8_t cfg, uint32_t* pUICfg, uint8_t bMCNum, CMCI oMCIList[],
                 CMCT oMCTList[],const char* s_fwVer)
{  
#if (defined(DAC_FUNCTIONALITY))
  if (cfg & OPT_DACT)
  {
    oDAC = (CUI)DACT_NewObject(MC_NULL,MC_NULL);
    
    UI_Init((CUI)oDAC, bMCNum, oMCIList, oMCTList, pUICfg); // Init UI and link MC obj
    UI_DACInit((CUI)oDAC); // Init DAC
    UI_DACChannelConfig((CUI)oDAC, DAC_CH0, MC_PROTOCOL_REG_I_A);
    UI_DACChannelConfig((CUI)oDAC, DAC_CH1, MC_PROTOCOL_REG_I_B);  
  }
  
  if (cfg & OPT_DAC)
  {
    oDAC = (CUI)DAC_NewObject(MC_NULL,MC_NULL);
    
    UI_Init((CUI)oDAC, bMCNum, oMCIList, oMCTList, pUICfg); // Init UI and link MC obj
    UI_DACInit((CUI)oDAC); // Init DAC
    UI_DACChannelConfig((CUI)oDAC, DAC_CH0, MC_PROTOCOL_REG_I_A);
    UI_DACChannelConfig((CUI)oDAC, DAC_CH1, MC_PROTOCOL_REG_I_B);  
  }
  
  if (cfg & OPT_DACS)
  {
    oDAC = (CUI)DACS_NewObject(MC_NULL,MC_NULL);
    
    UI_Init((CUI)oDAC, bMCNum, oMCIList, oMCTList, pUICfg); // Init UI and link MC obj
    UI_DACInit((CUI)oDAC); // Init DAC
    UI_DACChannelConfig((CUI)oDAC, DAC_CH0, MC_PROTOCOL_REG_I_A);
    UI_DACChannelConfig((CUI)oDAC, DAC_CH1, MC_PROTOCOL_REG_I_B);  
  }
  
  if (cfg & OPT_DACX)
  {
    oDAC = (CUI)DACX_NewObject(MC_NULL,MC_NULL);
    
    UI_Init((CUI)oDAC, bMCNum, oMCIList, oMCTList, pUICfg); // Init UI and link MC obj
    UI_DACInit((CUI)oDAC); // Init DAC
    UI_DACChannelConfig((CUI)oDAC, DAC_CH0, MC_PROTOCOL_REG_I_A);
    UI_DACChannelConfig((CUI)oDAC, DAC_CH1, MC_PROTOCOL_REG_I_B);  
  }
#endif
  
#if (defined(LCD_FUNCTIONALITY))
  if (cfg & OPT_LCD)
  {
    #define LCDI_Code_Addr   VECT_TABLE_BASE + 0x08 // Vect base + 0x08
    #define LCDI_Entry_Addr  VECT_TABLE_BASE + 0x0C // Vect base + 0x0C

    // Check the presence of LCD UI code
    uint32_t* pLCDI_Code = (uint32_t*)(LCDI_Code_Addr);
    uint32_t LCDI_Code = *pLCDI_Code;
    if (LCDI_Code == 0x1A525D)
    {
      // Call LCD UI entry point
      uint32_t* pLCDI_Entry = (uint32_t*)(LCDI_Entry_Addr);
      typedef void* const* (*pLCDI_Entry_t) (void* const*);
      pLCDI_Entry_t pLCDI_EntryFunc = (pLCDI_Entry_t)(*pLCDI_Entry);
      LCD_SetLCDIImportedFunctions((*pLCDI_EntryFunc)(exportedFunctions));
      
      oLCD = LCD_NewObject(MC_NULL, MC_NULL);
      
      UI_Init((CUI)oLCD, bMCNum, oMCIList, oMCTList, pUICfg); // Init UI and link MC obj  
      LCD_Init(oLCD, (CUI)oDAC, s_fwVer); // Initialize object it must be called after UI_Init (See Interface)
      LCD_Exec(oLCD); // Shows welcome message
    }
    else
    {
      while (1); // Error LCDI code not correctly flashed;
    }
  }
#endif
  
#if (defined(SERIAL_COMMUNICATION))
  if (cfg & OPT_COM)
  {
    oMCP = MCP_NewObject(MC_NULL,&MCPParams);
    oUSART = USART_NewObject(&USARTParams_str);
    oFCP = FCP_NewObject(&FrameParams_str);

    FCP_Init(oFCP, (CCOM)oUSART);
    MCP_Init(oMCP, oFCP, oDAC, s_fwVer);
    UI_Init((CUI)oMCP, bMCNum, oMCIList, oMCTList, pUICfg); // Init UI and link MC obj
  }  
#endif
}

#define LCD_WELCOME_MESSAGE_DURATION_MS 1000
#define LCD_WELCOME_MESSAGE_DURATION_UI_TICKS (LCD_WELCOME_MESSAGE_DURATION_MS * UI_TASK_FREQUENCY_HZ) / 1000
static uint16_t LCD_welcome_message_UI_counter = LCD_WELCOME_MESSAGE_DURATION_UI_TICKS;

void UI_LCDRefresh(void)
{
    if (LCD_welcome_message_UI_counter == 0)
    {
      LCD_Exec(oLCD);
      LCD_UpdateMeasured(oLCD);
    }
    else
    {
      LCD_welcome_message_UI_counter--;
    }
}

void UI_DACUpdate(uint8_t bMotorNbr)
{
  if (UI_GetSelectedMC((CUI)oDAC) == bMotorNbr)
  {
    UI_DACExec((CUI)oDAC); // Exec DAC update
  }
}

CLCD_UI GetLCD(void)
{
  return oLCD;
}

CMCP_UI GetMCP(void)
{
  return oMCP;
}

CUI GetDAC(void)
{
  return oDAC;
}

/******************* (C) COPYRIGHT 2011 STMicroelectronics *****END OF FILE****/
