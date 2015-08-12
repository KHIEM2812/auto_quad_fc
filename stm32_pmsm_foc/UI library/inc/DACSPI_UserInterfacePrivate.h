/**
  ******************************************************************************
  * @file    DACSPI_UserInterfacePrivate.h
  * @author  IMS Systems Lab and Technical Marketing - MC Team
  * @version 3.0
  * @date    05-Apr-2011 11:34
  * @brief   This file contains private definition of DACSPI class      
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
#ifndef __DACSPI_USERINTERFACEPRIVATE_H
#define __DACSPI_USERINTERFACEPRIVATE_H

/** @addtogroup STM32F10x_PMSM_UI_Library
  * @{
  */
  
/** @addtogroup DAC_SPI_UserInterface
  * @{
  */

/** @defgroup DACSPI_private_types DACSPI private types
* @{
*/

#define DAC_CH_NBR 2
#define DAC_CH_USER 2

/** 
  * @brief  DACSPI class members definition 
  */
typedef struct
{
  MC_Protocol_REG_t bChannel_variable[DAC_CH_NBR]; /*!< Array of codes of 
                                                        variables to be provided
                                                        in out to the related 
                                                        channel.*/
  int16_t hUserValue[DAC_CH_USER];                 /*!< Array of user defined 
                                                        DAC values.*/
}DVars_t,*pDVars_t;

/** 
  * @brief  Redefinition of parameter structure
  */
typedef DACSPIParams_t DParams_t, *pDParams_t; 

/** 
  * @brief Private DACSPI class definition 
  */
typedef struct
{
	DVars_t DVars_str;			/*!< Derived class members container */
	pDParams_t pDParams_str;	/*!< Derived class parameters container */
}_DCDACS_UI_t, *_DCDACS_UI;
/**
  * @}
  */
  
/**
  * @}
  */

/**
  * @}
  */

#endif /*__DACSPI_USERINTERFACEPRIVATE_H*/

/******************* (C) COPYRIGHT 2011 STMicroelectronics *****END OF FILE****/
