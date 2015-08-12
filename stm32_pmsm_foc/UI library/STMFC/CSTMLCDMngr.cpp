/**
  ******************************************************************************
  * @file    CSTMLCDMngr.cpp
  * @author  Systems Lab & Techincal Marketing (SDD Group)
  * @version V0.0.1
  * @date    04/26/2010
  * @brief   This file provides all the function to work with the LCD using the
  *          standard driver of STEval boards
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
  * <h2><center>&copy; COPYRIGHT 2010 STMicroelectronics</center></h2>
  */ 

#include "CSTMLCDMngr.h"

#define LCD_ILI9320        0x9320
#define LCD_HX8312         0x8312
#define LCD_SPFD5408       0x5408

static uint16_t m_Width = LCD_PIXEL_WIDTH;
//static uint16_t m_Height = LCD_PIXEL_HEIGHT;

#if (defined(USE_STM3210B_EVAL) || defined(USE_STM32100B_EVAL))
extern __IO uint32_t LCDType;
#endif

void CSTMLCDMngr::Init()
{
  /* Initialize the LCD */
#ifdef USE_STM32100B_EVAL
  STM32100B_LCD_Init();
#elif defined USE_STM3210B_EVAL
  STM3210B_LCD_Init();
#elif defined USE_STM3210E_EVAL
  STM3210E_LCD_Init();
#elif defined USE_STM3210C_EVAL
  STM3210C_LCD_Init();
#endif

  LCD_Clear(White);

  LCD_SetBackColor(White);
  LCD_SetTextColor(Black);

}

void CSTMLCDMngr::Clear(uint16_t rgb)
{
  LCD_Clear(rgb);
}

void CSTMLCDMngr::DrawChar(uint16_t Xpos, uint16_t Ypos, char cChar)
{
  uint16_t refcolumn = m_Width - 1 - Xpos; 
  
  if (((refcolumn + 1) & 0xFFFF) >= LCD_GetFont()->Width)
  {
    if (LCD_GetFont()->Width == 6 && LCD_GetFont()->Height == 8)
    {
      DrawCharOrizontal(Ypos, refcolumn, &LCD_GetFont()->table[(cChar - 32) * LCD_GetFont()->Width]);      
    }
    else
    {
      LCD_DisplayChar(Ypos, refcolumn, cChar);
    }
  }
}

void CSTMLCDMngr::DrawText(uint16_t Xpos, uint16_t Ypos, char *lpzText)
{
   
  /* Send the string character by character on lCD */
  while (*lpzText != 0) 
  {
    /* Display one character on LCD */
    DrawChar(Xpos, Ypos, *lpzText);
    /* Decrement the column position by 16 */
    Xpos += LCD_GetFont()->Width;
    /* Point on the next character */
    lpzText++;
  }
}
  
void CSTMLCDMngr::DrawLine(uint16_t Xpos, uint16_t Ypos, uint16_t Length, uint8_t Direction, uint16_t rgb)
{
    uint16_t XposLocal = m_Width - 1 - Xpos;
    uint16_t oldColor, oldColor_temp;

    LCD_GetColors(&oldColor, &oldColor_temp);
    LCD_SetTextColor(rgb);
    if (Length > 0)
    {
      LCD_DrawLine(Ypos, XposLocal, Length - 1, Direction);
    }
    
    LCD_SetTextColor(oldColor);
}

void CSTMLCDMngr::DrawRect(uint16_t Xpos, uint16_t Ypos, uint16_t Width, uint16_t Height, uint16_t rgb)
{
  uint16_t XposLocal = m_Width - 1 - Xpos;
  uint16_t oldColor, oldColor_temp;

  if (Width > 0 && Height > 0)
  {
    LCD_GetColors(&oldColor, &oldColor_temp);
    LCD_SetTextColor(rgb);
    
    LCD_DrawLine(Ypos, XposLocal, Width -1, LCD_DIR_HORIZONTAL);
    LCD_DrawLine((Ypos + Height - 1), XposLocal, Width -1, LCD_DIR_HORIZONTAL);
    
    LCD_DrawLine(Ypos, XposLocal, Height-1, LCD_DIR_VERTICAL);
    LCD_DrawLine(Ypos, (XposLocal - (Width - 1)), Height, LCD_DIR_VERTICAL);
      
    LCD_SetTextColor(oldColor);
  }
}

void CSTMLCDMngr::DrawFillRect(uint16_t Xpos, uint16_t Ypos, uint16_t Width, uint16_t Height, uint16_t rgb)
{
  uint16_t XposLocal = m_Width - 1 - Xpos;
  uint16_t oldColor, oldColor_temp;
  
  if (Width > 0)
  {
    LCD_GetColors(&oldColor, &oldColor_temp);
    LCD_SetTextColor(rgb);  
    
    while(Height--)
    {
      LCD_DrawLine(Ypos++, XposLocal, Width, LCD_DIR_HORIZONTAL);
    }
    LCD_SetTextColor(oldColor);
  }
  
}

/*

1)#define _RGB16BIT565(r,g,b) ((b%32) + ((g%64) << 6) + ((r%32) << 11))  
2)#define _RGB16BIT565(r,g,b) ((b&0x1F) + ((g&0x3F) << 6) + ((r&0x1F) << 11))  

3)#define _RGB16BIT565(r,g,b) ((b>>3) | ((g>>2) << 5) | ((r>>3) << 11))  

void Bitmap_Convert(BITMAP_FILE_PTR bitmap, UCHAR * buffer16bit)
{
	int n_padding = 0;
	int image_size = (bitmap->bitmapinfoheader.biSizeImage)/3;
	
	UCHAR	blue	= NULL, 
			green	= NULL,
			red		= NULL;
	USHORT	color	= NULL;

	for(int index = 0; index<=image_size; index++)
	{
		n_padding = index * 3;

		blue	= (bitmap->buffer[n_padding]);
		green	= (bitmap->buffer[n_padding + 1]);
		red		= (bitmap->buffer[n_padding + 2]);

		//color += _RGB16BIT565(red, green, blue);

		color = _RGB16BIT565(red, green, blue);
	}

	buffer16bit = (UCHAR *)color;
}

*/

#if !defined USE_STM3210E_EVAL
void CSTMLCDMngr::DrawBitmap16(uint16_t *pBufferImage, uint16_t Xpos, uint16_t Ypos, uint16_t Width, uint16_t Height)
{
  uint32_t index = 0, i = 0;
  uint16_t Xaddress = Ypos + Height;
  uint16_t Yaddress = m_Width - 1 - Xpos;
  
//  Xaddress = Xpos;
  
  LCD_SetCursor(Xaddress, Yaddress);

  
  for(index = 0; index < Height; index++)
  {
    if((LCDType == LCD_ILI9320) || (LCDType == LCD_SPFD5408))
    {
      LCD_WriteReg(LCD_REG_3, 0x1008);
      LCD_WriteRAM_Prepare(); /* Prepare to write GRAM */
    }

    for(i = 0; i < Width; i++)
    {
        LCD_WriteRAM(pBufferImage[i + index * Width]);
    }
    if((LCDType == LCD_ILI9320) || (LCDType == LCD_SPFD5408))
    {
      LCD_CtrlLinesWrite(LCD_NCS_GPIO_PORT, LCD_NCS_PIN, Bit_SET);
    }  
    Xaddress--;
    LCD_SetCursor(Xaddress, Yaddress);
  }
  
  if((LCDType == LCD_ILI9320) || (LCDType == LCD_SPFD5408))
  {
    /* Set GRAM write direction and BGR = 1 */
    /* I/D = 01 (Horizontal : increment, Vertical : decrement) */
    /* AM = 1 (address is updated in vertical writing direction) */
    LCD_WriteReg(LCD_REG_3, 0x1018);
  }

}
#endif

void CSTMLCDMngr::DrawCharOrizontal(uint8_t Xpos, uint16_t Ypos, const uint16_t *c)
{
  uint8_t index = 0, i = 0;
  uint8_t Xaddress = 0;
  uint16_t LocTextColor = 0, LocBackColor = 0; 

  LCD_GetColors(&LocTextColor, &LocBackColor);
    
  Xaddress = Xpos;
  
  LCD_SetCursor(Xaddress, Ypos);
  
  for(index = 0; index < LCD_GetFont()->Height; index++)
  {

#if (defined(USE_STM3210B_EVAL) || defined(USE_STM32100B_EVAL))
    if((LCDType == LCD_ILI9320) || (LCDType == LCD_SPFD5408))
    {
      LCD_WriteRAM_Prepare(); /* Prepare to write GRAM */
    }
#endif
    
#if (defined(USE_STM3210C_EVAL))
    LCD_WriteRAM_Prepare(); /* Prepare to write GRAM */
#endif
    
    for(i = 0; i <  LCD_GetFont()->Width; i++)
    {
      if(!(c[i] & (0x1 << index)))
      {
        LCD_WriteRAM(LocBackColor);
      }
      else
      {
        LCD_WriteRAM(LocTextColor);
      }
    }
    
#if (defined(USE_STM3210B_EVAL) || defined(USE_STM32100B_EVAL))
    if((LCDType == LCD_ILI9320) || (LCDType == LCD_SPFD5408))
    {
      LCD_CtrlLinesWrite(LCD_NCS_GPIO_PORT, LCD_NCS_PIN, Bit_SET);
    }  
#endif
    
#if (defined(USE_STM3210C_EVAL))
    LCD_CtrlLinesWrite(LCD_NCS_GPIO_PORT, LCD_NCS_PIN, Bit_SET);
#endif
    
    Xaddress++;
    LCD_SetCursor(Xaddress, Ypos);
  }
}
