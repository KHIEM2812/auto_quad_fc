/**
  ******************************************************************************
  * @file    Rdivider_BusVoltageSensorClass.h
  * @author  IMS Systems Lab and Technical Marketing - MC Team
  * @version 3.0
  * @date    05-Apr-2011 11:34
  * @brief   This file contains interface of Rdivider class      
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
#ifndef __RDIVIDER_BUSVOLTAGESENSORCLASS_H
#define __RDIVIDER_BUSVOLTAGESENSORCLASS_H

/** @addtogroup STM32F10x_PMSM_MC_Library
  * @{
  */
  
/** @addtogroup BusVoltageSensor_Rdivider
  * @{
  */

/** @defgroup Rdivider_class_exported_types Rdivider class exported types
* @{
*/

/** 
  * @brief  Public Rdivider class definition
  */
typedef struct CRVBS_VBS_t *CRVBS_VBS;

/** 
  * @brief  Rdivider class parameters definition
  */
typedef const struct
{
  uint8_t bVbusADChannel;           /*!< ADC channel used for conversion of 
                                         bus voltage. It must be equal to  
                                         ADC_Channel_x x= 0, ..., 15*/
  GPIO_TypeDef* hVbusPort;          /*!< GPIO port used by bVbusADChannel. 
                                         It must be equal to GPIOx x= A, B, ...*/                                                                             
  uint16_t hVbusPin;                /*!< GPIO pin used by bVbusChannel. It must  
                                         be equal to GPIO_Pin_x x= 0, 1, ...*/ 
  uint8_t bVbusSamplingTime;        /*!< Sampling time used for bVbusChannel AD
                                         conversion. It must be equal to  
                                         ADC_SampleTime_xCycles5 x= 1, 7, ...*/  
  uint16_t hLowPassFilterBW;        /*!< Use this number to configure the Vbus 
                                         first order software filter bandwidth. 
                                         hLowPassFilterBW = VBS_CalcBusReading 
                                         call rate [Hz]/ FilterBandwidth[Hz] */   
  uint16_t hOverVoltageThreshold;   /*!< It represents the over voltage protection 
                                         intervention threshold. To be expressed 
                                         in digital value through formula:
                                         hOverVoltageThreshold (digital value) = 
                                         Over Voltage Threshold (V) * 65536 
                                                          / hConversionFactor */
  uint16_t hUnderVoltageThreshold;  /*!< It represents the under voltage protection 
                                         intervention threshold. To be expressed 
                                         in digital value through formula:                                         
                                         hUnderVoltageThreshold (digital value)= 
                                         Under Voltage Threshold (V) * 65536 
                                                          / hConversionFactor */
}RdividerParams_t, *pRdividerParams_t;
/**
  * @}
  */

/** @defgroup Rdivider_class_exported_methods Rdivider class exported methods
  * @{
  */
  
/**
  * @brief  Creates an object of the class Rdivider
  * @param  pBusVoltageSensorParams pointer to an BusVoltageSensor parameters 
  *         structure
  * @param  pRdividerParams pointer to an Rdivider parameters structure
  * @retval CRVBS_VBS new instance of Rdivider object
  */
CRVBS_VBS RVBS_NewObject(pBusVoltageSensorParams_t pBusVoltageSensorParams, 
                                             pRdividerParams_t pRdividerParams);

/**
  * @}
  */
  
/**
  * @}
  */

/**
  * @}
  */

#endif /*__RDIVIDER_BUSVOLTAGESENSORCLASS_H*/
/******************* (C) COPYRIGHT 2011 STMicroelectronics *****END OF FILE****/
