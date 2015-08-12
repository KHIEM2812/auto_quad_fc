/**
  ******************************************************************************
  * @file    NTC_TemperatureSensorClass.h
  * @author  IMS Systems Lab and Technical Marketing - MC Team
  * @version 3.0
  * @date    05-Apr-2011 11:34
  * @brief   This file contains interface of NTC class      
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
#ifndef __NTC_TEMPERATURESENSORCLASS_H
#define __NTC_TEMPERATURESENSORCLASS_H

/** @addtogroup STM32F10x_PMSM_MC_Library
  * @{
  */
  
/** @addtogroup TemperatureSensor_NTC
  * @{
  */

/** @defgroup NTC_class_exported_types NTC class exported types
* @{
*/

/** 
  * @brief  Public NTC class definition
  */
typedef struct CNTC_TSNS_t *CNTC_TSNS;

/** 
  * @brief  NTC class parameters definition
  */
typedef const struct
{
  uint8_t bTsensADChannel;           /*!< ADC channel used for conversion of 
                                         temperature sensor output. It must be   
                                         equal to ADC_Channel_x x= 0, ..., 15*/
  GPIO_TypeDef* hTsensPort;          /*!< GPIO port used by bVbusADChannel. 
                                         It must be equal to GPIOx x= A, B, ...*/                                                                             
  uint16_t hTsensPin;                /*!< GPIO pin used by bVbusChannel. It must  
                                         be equal to GPIO_Pin_x x= 0, 1, ...*/ 
  uint8_t bTsensSamplingTime;        /*!< Sampling time used for bVbusChannel AD
                                         conversion. It must be equal to  
                                         ADC_SampleTime_xCycles5 x= 1, 7, ...*/  
  uint16_t hLowPassFilterBW;         /*!< Use this number to configure the   
                                         temperature first order software filter
                                         bandwidth                                                                                
                                         hLowPassFilterBW = TSNS_CalcBusReading 
                                         call rate [Hz]/ FilterBandwidth[Hz] */
  uint16_t hOverTempThreshold;       /*!< It represents the over voltage protection 
                                         intervention threshold. To be expressed 
                                         in u16Celsius through formula:
                                         hOverTempThreshold [u16Celsius] = 
                                         (V0[V]+dV/dT[V/°C]*(OverTempThreshold[°C] 
                                          - T0[°C]))* 65536 / MCU supply voltage */
  uint16_t hOverTempDeactThreshold;  /*!< It represents the temperature 
                                         expressed in u16Celsius below which an 
                                         active over temperature fault is cleared
                                         hOverTempDeactThreshold[u16Celsius]=
                                         (V0[V]+dV/dT[V/°C]*(OverTempDeactThresh[°C] 
                                          - T0[°C]))* 65536 / MCU supply voltage*/
  int16_t hSensitivity;              /*!< It is equal to MCU supply voltage [V] /
                                          dV/dT [V/°C] and represents the NTC 
                                          sensitivity */
  uint32_t wV0;                       /*!< It is equal to V0*65536/MCU supply 
                                          voltage where V0 is used to convert the 
                                          temperature into Volts 
                                          V[V]=V0+dV/dT[V/°C]*(T-T0)[°C]      */
  uint16_t hT0;                       /*!< It is equal to T0 [°C], used to convert 
                                          the temperature into Volts 
                                          V[V]=V0+dV/dT[V/°C]*(T-T0)[°C]*/
}NTCParams_t, *pNTCParams_t;
/**
  * @}
  */

/** @defgroup NTC_class_exported_methods NTC class exported methods
  * @{
  */
  
/**
  * @brief  Creates an object of the class NTC
  * @param  pTempSensorParams pointer to an TemperatureSensor parameters 
  *         structure
  * @param  pNTCParams pointer to an NTC parameters structure
  * @retval CNTC_TSNS new instance of NTC object
  */
CNTC_TSNS NTC_NewObject(pTempSensorParams_t pTempSensorParams, 
                                             pNTCParams_t pNTCParams);

/**
  * @}
  */
  
/**
  * @}
  */

/**
  * @}
  */

#endif /*__NTC_TEMPERATURESENSORCLASS_H*/
/******************* (C) COPYRIGHT 2011 STMicroelectronics *****END OF FILE****/
