/**
  ******************************************************************************
  * @file    MCTasks.c
  * @author  IMS Systems Lab and Technical Marketing - MC Team
  * @version 3.0
  * @date    05-Apr-2011 11:34
  * @brief   This file implementes tasks definition
  ******************************************************************************
  * @<br>
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

#include "PIRegulatorClass.h"
#include "PID_PIRegulatorClass.h"
#include "DigitalOutputClass.h"
#include "MC_type.h"
#include "MC_Math.h"
#include "MCIRQHandlerClass.h"

#include "SpeednPosFdbkClass.h"
#include "STO_SpeednPosFdbkClass.h"
#include "ENCODER_SpeednPosFdbkClass.h"
#include "HALL_SpeednPosFdbkClass.h"
#include "STO_CORDIC_SpeednPosFdbkClass.h"
#include "VirtualSpeedSensor_SpeednPosFdbkClass.h"
#include "EncAlignCtrlClass.h"

#include "FOCDriveClass.h"
#include "SM_PMSM_FOCDriveClass.h"
#include "SMF_PMSM_FOCDriveClass.h"
#include "IMF_PMSM_FOCDriveClass.h"
#include "IMFF_PMSM_FOCDriveClass.h"
#include "OpenLoop_FOCDriveClass.h"

#include "PWMnCurrFdbkClass.h"
#include "R3_LM1_PWMnCurrFdbkClass.h"
#include "R3_HD2_PWMnCurrFdbkClass.h"
#include "R1_LM1_PWMnCurrFdbkClass.h"
#include "R1_VL1_PWMnCurrFdbkClass.h"
#include "R1_HD2_PWMnCurrFdbkClass.h"
#include "ICS_LM1_PWMnCurrFdbkClass.h"
#include "ICS_HD2_PWMnCurrFdbkClass.h"

#include "StateMachineClass.h"
#include "SpeednTorqCtrlClass.h"
#include "RevupCtrlClass.h"

#include "BusVoltageSensorClass.h"
#include "Rdivider_BusVoltageSensorClass.h"
#include "Virtual_BusVoltageSensorClass.h"

#include "DigitalOutputClass.h"

#include "TemperatureSensorClass.h"
#include "NTC_TemperatureSensorClass.h"
#include "Virtual_TemperatureSensorClass.h"

#include "MotorPowerMeasurementClass.h"
#include "PQD_MotorPowerMeasurementClass.h"

#include "MCInterfaceClass.h"
#include "MCInterfaceClassPrivate.h"
#include "MCTuningClass.h"
#include "MCTuningClassPrivate.h"

#include "SystemNDriveParams.h"

#include "MCTasks.h"

#define MC_TUNING_INTERFACE

/* Private define ------------------------------------------------------------*/
#define AUX_SPEED_FDBK_M1 (defined(VIEW_HALL_FEEDBACK) || defined(VIEW_ENCODER_FEEDBACK) || defined(AUX_STATE_OBSERVER_PLL) || defined(AUX_STATE_OBSERVER_CORDIC))
#define AUX_SPEED_FDBK_M2 (defined(VIEW_HALL_FEEDBACK2) || defined(VIEW_ENCODER_FEEDBACK2) || defined(AUX_STATE_OBSERVER_PLL2) || defined(AUX_STATE_OBSERVER_CORDIC2))

/* Private variables----------------------------------------------------------*/
CMCI oMCInterface[NBR_OF_MOTORS];
#ifdef MC_TUNING_INTERFACE
CMCT oMCTuning[NBR_OF_MOTORS];
#endif
CSTM oSTM[NBR_OF_MOTORS];
CFOC oFOC[NBR_OF_MOTORS];
CSTC oSTC[NBR_OF_MOTORS];
CPI oPIDSpeed[NBR_OF_MOTORS],oPIDIq[NBR_OF_MOTORS],oPIDId[NBR_OF_MOTORS];
CVBS oBusSensor[NBR_OF_MOTORS];
CTSNS oTemperatureSensor[NBR_OF_MOTORS];
CPWMC oCurrSensor[NBR_OF_MOTORS];  
CSPD oSpeedSensor[NBR_OF_MOTORS]; 
CDOUT oR_Brake[NBR_OF_MOTORS];
CDOUT oOCPDisabling[NBR_OF_MOTORS];

CMPM oMPM[NBR_OF_MOTORS];

#if AUX_SPEED_FDBK_M1
CSPD oSpeedSensorAux_M1;              /* only if auxiliary speed sensor on M1*/
#endif 
#if ((defined NO_SPEED_SENSORS)||(defined ENCODER)||(defined VIEW_ENCODER_FEEDBACK))
CSPD oVSS_M1;                         /* only if M1 is sensorless*/
#endif
#if (defined NO_SPEED_SENSORS)
CRUC oRUC_M1;                         /* only if M1 is sensorless*/
#endif
#if ((defined ENCODER)||(defined VIEW_ENCODER_FEEDBACK))
CEAC oEAC_M1;
#endif
CPI oPIFW_M1;                         /* only if M1 is FOC SMF, IMF, IMFF*/  

#ifdef DUALDRIVE
#if AUX_SPEED_FDBK_M2
CSPD oSpeedSensorAux_M2;              /* only if auxiliary speed sensor on M2*/  
#endif
#if ((defined NO_SPEED_SENSORS2)||(defined ENCODER2)||(defined VIEW_ENCODER_FEEDBACK2))
CSPD oVSS_M2;                         /* only if M2 is sensorless*/
#endif
#if (defined NO_SPEED_SENSORS2)
CRUC oRUC_M2;                         /* only if M2 is sensorless*/
#endif
#if ((defined ENCODER2)||(defined VIEW_ENCODER_FEEDBACK2))
CEAC oEAC_M2;
#endif
CPI oPIFW_M2;                         /* only if M2 is FOC SMF, IMF, IMFF*/   
#endif

static volatile uint8_t  bBootCapDelayCounterM1 = 0;
static volatile uint16_t hStopPermanencyCounterM1 = 0;
static volatile uint8_t  bBootCapDelayCounterM2 = 0;
static volatile uint16_t hStopPermanencyCounterM2 = 0;
static bool bHasBootCapCountingStartedM1 = FALSE;
static bool bHasBootCapCountingStartedM2 = FALSE;

/* Private functions ---------------------------------------------------------*/
static void TSK_LowFrequencyClock(void);
static void TSK_LowFrequencyTaskM1(void);
static void TSK_MediumFrequencyTaskM1(void);
static void TSK_SetChargeBootCapDelayM1(uint8_t SysTickCount);
static bool TSK_ChargeBootCapDelayHasElapsedM1(void);
static bool TSK_ChargeBootCapDelayHasStartedM1(void);
static void TSK_SetStopPermanencyTimeM1(uint16_t SysTickCount);
static bool TSK_StopPermanencyTimeHasElapsedM1(void);

#ifdef DUALDRIVE
static void TSK_LowFrequencyTaskM2(void);
static void TSK_MediumFrequencyTaskM2(void);
static void TSK_SetChargeBootCapDelayM2(uint8_t SysTickCount);
static bool TSK_ChargeBootCapDelayHasElapsedM2(void);
static bool TSK_ChargeBootCapDelayHasStartedM2(void);
static void TSK_SetStopPermanencyTimeM2(uint16_t SysTickCount);
static bool TSK_StopPermanencyTimeHasElapsedM2(void);
#define FOC_ARRAY_LENGHT 2
static void *FOC_array[FOC_ARRAY_LENGHT]={MC_NULL,MC_NULL};
static uint8_t FOC_array_head = 0; // Next obj to be executed
static uint8_t FOC_array_tail = 0; // Last arrived
#endif

/**
  * @brief  It initializes the whole MC core according to user defined 
  *         parameters.
  * @param  oMCIList pointer to the vector of MCInterface objects that will be
  *         created and initialized. The vector must have length equal to the 
  *         number of motor drives.
  * @param  oMCTList pointer to the vector of MCTuning objects that will be
  *         created and initialized. The vector must have length equal to the 
  *         number of motor drives.
  * @retval None
  */
void MCboot(CMCI oMCIList[NBR_OF_MOTORS],CMCT oMCTList[NBR_OF_MOTORS])
{
  FOCInitStruct_t FOCInitStructure[NBR_OF_MOTORS];
  IMF_PMSMInit_t PMSMInitStructureM1; /* only if M1 has FOC SMF, IMF, IMFF*/ 
  
  PQD_MPMInitStruct_t PQD_MPMInitStruct;
  
#ifdef MC_TUNING_INTERFACE
  MCTuningInitStruct_t MCTInitStruct;
#endif

#if (defined OPEN_LOOP) 
  oFOC[0] = (CFOC)OL_NewObject(&FOCDriveParamsM1,&OpenLoopFOC_ParamsM1); 
#elif ((defined FLUX_WEAKENING)&&(defined IPMSM_MTPA)&&(!defined FEED_FORWARD_CURRENT_REGULATION))   
  oFOC[0] = (CFOC)IMF_NewObject(&FOCDriveParamsM1,&IMF_PMSMParamsM1); /* drive configuration SM,SMF,IMF,IMFF, x_NewObject, x_PMSMParamsM1*/
#elif ((defined FLUX_WEAKENING)&&(defined IPMSM_MTPA)&&(defined FEED_FORWARD_CURRENT_REGULATION))
  oFOC[0] = (CFOC)IMFF_NewObject(&FOCDriveParamsM1,&IMFF_PMSMParamsM1); /* drive configuration SM,SMF,IMF,IMFF, x_NewObject, x_PMSMParamsM1*/ 
#elif ((defined FLUX_WEAKENING)&&(!defined IPMSM_MTPA)&&(!defined FEED_FORWARD_CURRENT_REGULATION))   
  oFOC[0] = (CFOC)SMF_NewObject(&FOCDriveParamsM1,&SMF_PMSMParamsM1); /* drive configuration SM,SMF,IMF,IMFF, x_NewObject, x_PMSMParamsM1*/
#elif ((!defined FLUX_WEAKENING)&&(!defined IPMSM_MTPA)&&(!defined FEED_FORWARD_CURRENT_REGULATION))
  oFOC[0] = (CFOC)SM_NewObject(&FOCDriveParamsM1,MC_NULL); /* drive configuration SM,SMF,IMF,IMFF, x_NewObject, x_PMSMParamsM1*/
#else
#error "Invalid boot: configuration not valid or to be assigned"
#endif  

#if ((defined STM32PERFORMANCE)&&(defined THREE_SHUNT)&&(defined SINGLEDRIVE))
  oCurrSensor[0] = (CPWMC)R3LM1_NewObject(&PWMnCurrFdbkParamsM1, &R3_LM1ParamsSD); /* current sensor R3LM1 R3HD2 R1LM1 R1HD2 R1VL1 ILM1 IHD2, x_New and xParamsM1*/
#elif ((defined STM32PERFORMANCE)&&(defined SINGLE_SHUNT)&&(defined SINGLEDRIVE))
  oCurrSensor[0] = (CPWMC)R1LM1_NewObject(&PWMnCurrFdbkParamsM1, &R1_LM1ParamsSD); /* current sensor R3LM1 R3HD2 R1LM1 R1HD2 R1VL1 ILM1 IHD2, x_New and xParamsM1*/
#elif ((defined STM32PERFORMANCE)&&(defined ICS_SENSORS)&&(defined SINGLEDRIVE))
  oCurrSensor[0] = (CPWMC)ILM1_NewObject(&PWMnCurrFdbkParamsM1, &ICS_LM1ParamsSD); /* current sensor R3LM1 R3HD2 R1LM1 R1HD2 R1VL1 ILM1 IHD2, x_New and xParamsM1*/  
#elif ((defined STM32VALUE)&&(defined SINGLE_SHUNT)&&(defined SINGLEDRIVE))  
  oCurrSensor[0] = (CPWMC)R1VL1_NewObject(&PWMnCurrFdbkParamsM1, &R1_VL1ParamsSD); /* current sensor R3LM1 R3HD2 R1LM1 R1HD2 R1VL1 ILM1 IHD2, x_New and xParamsM1*/
#elif ((defined STM32HD)&&(defined SINGLE_SHUNT))
  oCurrSensor[0] = (CPWMC)R1HD2_NewObject(&PWMnCurrFdbkParamsM1, &R1_HD2ParamsDDM1); /* current sensor R3LM1 R3HD2 R1LM1 R1HD2 R1VL1 ILM1 IHD2, x_New and xParamsM1*/
#elif ((defined STM32HD)&&(defined THREE_SHUNT))
  oCurrSensor[0] = (CPWMC)R3HD2_NewObject(&PWMnCurrFdbkParamsM1, &R3_HD2ParamsDDM1); /* current sensor R3LM1 R3HD2 R1LM1 R1HD2 R1VL1 ILM1 IHD2, x_New and xParamsM1*/
#elif ((defined STM32HD)&&(defined ICS_SENSORS))
  oCurrSensor[0] = (CPWMC)IHD2_NewObject(&PWMnCurrFdbkParamsM1, &ICS_HD2ParamsDDM1); /* current sensor R3LM1 R3HD2 R1LM1 R1HD2 R1VL1 ILM1 IHD2, x_New and xParamsM1*/
#else
#error "Invalid boot: configuration not valid or to be assigned"
#endif  

  PWMC_Init(oCurrSensor[0], oFOC[0]);  

#if ((HW_OV_CURRENT_PROT_BYPASS == ENABLE) && (ON_OVER_VOLTAGE == TURN_ON_LOW_SIDES))
  oOCPDisabling[0] = DOUT_NewObject(&DOUT_OCPDisablingParamsM1); 
  DOUT_Init(oOCPDisabling[0]);
#endif   
  
#ifdef DUALDRIVE
  SMF_PMSMInit_t PMSMInitStructureM2; /* only if M2 has FOC SMF, IMF, IMFF*/

#if (defined OPEN_LOOP2) 
  oFOC[1] = (CFOC)OL_NewObject(&FOCDriveParamsM2,&OpenLoopFOC_ParamsM2); 
#elif ((defined FLUX_WEAKENING2)&&(defined IPMSM_MTPA2)&&(!defined FEED_FORWARD_CURRENT_REGULATION2))   
  oFOC[1] = (CFOC)IMF_NewObject(&FOCDriveParamsM2,&IMF_PMSMParamsM2); /* drive configuration SM,SMF,IMF,IMFF, x_NewObject, x_PMSMParamsM2*/
#elif ((defined FLUX_WEAKENING2)&&(defined IPMSM_MTPA2)&&(defined FEED_FORWARD_CURRENT_REGULATION2))
  oFOC[1] = (CFOC)IMFF_NewObject(&FOCDriveParamsM2,&IMFF_PMSMParamsM2); /* drive configuration SM,SMF,IMF,IMFF, x_NewObject, x_PMSMParamsM2*/ 
#elif ((defined FLUX_WEAKENING2)&&(!defined IPMSM_MTPA2)&&(!defined FEED_FORWARD_CURRENT_REGULATION2))   
  oFOC[1] = (CFOC)SMF_NewObject(&FOCDriveParamsM2,&SMF_PMSMParamsM2); /* drive configuration SM,SMF,IMF,IMFF, x_NewObject, x_PMSMParamsM2*/
#elif ((!defined FLUX_WEAKENING2)&&(!defined IPMSM_MTPA2)&&(!defined FEED_FORWARD_CURRENT_REGULATION2))
  oFOC[1] = (CFOC)SM_NewObject(&FOCDriveParamsM2,MC_NULL); /* drive configuration SM,SMF,IMF,IMFF, x_NewObject, x_PMSMParamsM2*/
#else
#error "Invalid boot: configuration not valid or to be assigned"
#endif   

#if ((defined STM32HD)&&(defined SINGLE_SHUNT2))
  oCurrSensor[1] = (CPWMC)R1HD2_NewObject(&PWMnCurrFdbkParamsM2, &R1_HD2ParamsDDM2); /* current sensor R3HD2_New and R3HD2Params, R1HD2..*/  
#elif ((defined STM32HD)&&(defined THREE_SHUNT2))
  oCurrSensor[1] = (CPWMC)R3HD2_NewObject(&PWMnCurrFdbkParamsM2, &R3_HD2ParamsDDM2); /* current sensor R3HD2_New and R3HD2Params, R1HD2..*/    
#elif ((defined STM32HD)&&(defined ICS_SENSORS2))
  oCurrSensor[1] = (CPWMC)IHD2_NewObject(&PWMnCurrFdbkParamsM2, &ICS_HD2ParamsDDM2); /* current sensor R3LM2 R3HD2, x_New and xParamsM2*/
#else
#error "Invalid boot: configuration not valid or to be assigned"
#endif 
  
  PWMC_Init(oCurrSensor[1], oFOC[1]);
  
#if ((HW_OV_CURRENT_PROT_BYPASS2 == ENABLE) && (ON_OVER_VOLTAGE2 == TURN_ON_LOW_SIDES))
  oOCPDisabling[1] = DOUT_NewObject(&DOUT_OCPDisablingParamsM2); 
  DOUT_Init(oOCPDisabling[1]);
#endif 
  
#endif
  
#if ((defined STM32HD) && (defined THREE_SHUNT))
  R3HD2_StartTimers();
#elif ((defined STM32HD) && (defined SINGLE_SHUNT))
  R1HD2_StartTimers();
#elif ((defined STM32HD) && (defined ICS_SENSORS))
  IHD2_StartTimers();
#endif
  
  oSTM[0] = STM_NewObject();
  STM_Init(oSTM[0]);
  
  oPIDSpeed[0] = (CPI)PI_NewObject(&PISpeedParamsM1);
  PI_ObjectInit(oPIDSpeed[0]);  

#if (defined STATE_OBSERVER_PLL)
  oSpeedSensor[0] = (CSPD)STO_NewObject(&SpeednPosFdbkParamsM1,&STOParamsM1); /* speed sensor STO, ENC, HALL xNew and xParamsM1*/
#elif (defined STATE_OBSERVER_CORDIC)
  oSpeedSensor[0] = (CSPD)STO_CR_NewObject(&SpeednPosFdbkParamsM1,&STO_CORDICParamsM1); /* speed sensor STO, ENC, HALL xNew and xParamsM1*/  
#elif (defined ENCODER)
  oSpeedSensor[0] = (CSPD)ENC_NewObject(&SpeednPosFdbkParamsM1,&ENCParamsM1); /* speed sensor STO, ENC, HALL xNew and xParamsM1*/
#elif (defined HALL_SENSORS)
  oSpeedSensor[0] = (CSPD)HALL_NewObject(&SpeednPosFdbkParamsM1,&HALLParamsM1); /* speed sensor STO, ENC, HALL xNew and xParamsM1*/  
#endif  
  SPD_Init(oSpeedSensor[0]);
  
#if AUX_SPEED_FDBK_M1 
#if (defined AUX_STATE_OBSERVER_PLL)
  oSpeedSensorAux_M1 = (CSPD)STO_NewObject(&SpeednPosFdbkParamsM1,&STOParamsM1); /* aux speed sensor STO, ENC, HALL xNew and xParamsM1*/
#elif (defined AUX_STATE_OBSERVER_CORDIC)
  oSpeedSensorAux_M1 = (CSPD)STO_CR_NewObject(&SpeednPosFdbkParamsM1,&STO_CORDICParamsM1); /* aux speed sensor STO, ENC, HALL xNew and xParamsM1*/  
#elif (defined VIEW_ENCODER_FEEDBACK)
  oSpeedSensorAux_M1 = (CSPD)ENC_NewObject(&SpeednPosFdbkParamsM1,&ENCParamsM1); /* aux speed sensor STO, ENC, HALL xNew and xParamsM1*/
#elif (defined VIEW_HALL_FEEDBACK)
  oSpeedSensorAux_M1 = (CSPD)HALL_NewObject(&SpeednPosFdbkParamsM1,&HALLParamsM1); /* aux speed sensor STO, ENC, HALL xNew and xParamsM1*/  
#endif  
  SPD_Init(oSpeedSensorAux_M1);
#endif
  
  oSTC[0] = STC_NewObject(&SpeednTorqCtrlParamsM1);
  STC_Init(oSTC[0],oPIDSpeed[0],oSpeedSensor[0]);

#if ((defined NO_SPEED_SENSORS)||(defined ENCODER)||(defined VIEW_ENCODER_FEEDBACK))
  oVSS_M1 = (CSPD)VSS_NewObject(&SpeednPosFdbkParamsM1,&VirtualSpeedSensorParamsM1);
  SPD_Init(oVSS_M1);
#endif
#if (defined NO_SPEED_SENSORS)
  oRUC_M1 = RUC_NewObject(&RevupCtrlParamsM1);        /* only if sensorless*/
  RUC_Init(oRUC_M1,oSTC[0],(CVSS_SPD)oVSS_M1);        /* only if sensorless*/
#endif
#if ((defined ENCODER)||(defined VIEW_ENCODER_FEEDBACK))
  oEAC_M1 = (CEAC)EAC_NewObject(&EncAlignCtrlParamsM1);
#endif
#if (defined ENCODER)
  EAC_Init(oEAC_M1,oSTC[0],(CVSS_SPD)oVSS_M1,(CENC_SPD)oSpeedSensor[0]);
#endif  
#if (defined VIEW_ENCODER_FEEDBACK)
  EAC_Init(oEAC_M1,oSTC[0],(CVSS_SPD)oVSS_M1,(CENC_SPD)oSpeedSensorAux_M1);
#endif
  
  oPIDIq[0] = (CPI)PI_NewObject(&PIIqParamsM1);
  PI_ObjectInit(oPIDIq[0]); 
  
  oPIDId[0] = (CPI)PI_NewObject(&PIIdParamsM1);
  PI_ObjectInit(oPIDId[0]);   
  
#if defined BUS_VOLTAGE_MEASUREMENT
  oBusSensor[0] = (CVBS)RVBS_NewObject(&RealBusVoltageSensorParamsM1,
                                       &RdividerParamsM1); /* powerboard configuration: Rdivider or Virtual*/  
#else
  oBusSensor[0] = (CVBS)VVBS_NewObject(&VirtualBusVoltageSensorParamsM1,
                                       &VirtualBusParamsM1); /* powerboard configuration: Rdivider or Virtual*/    
#endif
  VBS_Init(oBusSensor[0],oCurrSensor[0]);
  
  oMPM[0] = (CMPM)PQD_NewObject(&PQD_MotorPowerMeasurementParamsM1);
  PQD_MPMInitStruct.oFOC = oFOC[0];
  PQD_MPMInitStruct.oVBS = oBusSensor[0];
  MPM_Init(oMPM[0],(pMPMInitStruct_t)&PQD_MPMInitStruct);
  
#if ON_OVER_VOLTAGE == TURN_ON_R_BRAKE
  oR_Brake[0] = DOUT_NewObject(&R_BrakeParamsM1); 
  DOUT_Init(oR_Brake[0]);
#endif 

  
#if defined HEAT_SINK_TEMPERATURE_MEASUREMENT
  oTemperatureSensor[0] = (CTSNS)NTC_NewObject(&RealTempSensorParamsM1,
                                               &NTCParamsM1); /* powerboard configuration: NTC or Virtual*/
#else
  oTemperatureSensor[0] = (CTSNS)VTS_NewObject(&VirtualTempSensorParamsM1,
                                               &VirtualTParamsM1); /* powerboard configuration: NTC or Virtual*/
#endif
  TSNS_Init(oTemperatureSensor[0],oCurrSensor[0]);  
  
 
  
  FOCInitStructure[0].oCurrSensor = oCurrSensor[0];
  FOCInitStructure[0].oSpdTrqController = oSTC[0];
  FOCInitStructure[0].oVbusSensor = oBusSensor[0];
  FOCInitStructure[0].oSpeedSensor = oSpeedSensor[0];
  FOCInitStructure[0].oPI_q = oPIDIq[0];
  FOCInitStructure[0].oPI_d = oPIDId[0];
  
  oPIFW_M1 = (CPI)PI_NewObject(&PIFluxWeakeningParamsM1);  /* only if FOC SMF, IMF, IMFF*/
  PI_ObjectInit(oPIFW_M1);     /* PI_ObjectInit or PID_ObjectInit*/   
  PMSMInitStructureM1.oFluxWeakeningPI = oPIFW_M1;     /* only if FOC SMF, IMF, IMFF*/
  PMSMInitStructureM1.oSpeedPI = oPIDSpeed[0]; /* only if FOC SMF, IMF, IMFF*/
  
  FOC_Init(oFOC[0],FOCInitStructure[0],&PMSMInitStructureM1); /* third parameter is PMSMInitStructureM1 if M1 has FOC SMF, IMF, IMFF otherwise is MC_NULL*/  

  oMCInterface[0] = MCI_NewObject(MC_NULL);
  MCI_Init(oMCInterface[0], oSTM[0], oSTC[0], oFOC[0]);
  MCI_ExecSpeedRamp(oMCInterface[0], 
                    STC_GetMecSpeedRef01HzDefault(oSTC[0]),0); /*First command to STC*/
  
  oMCIList[0] = oMCInterface[0];

#ifdef MC_TUNING_INTERFACE
  oMCTuning[0] = MCT_NewObject(MC_NULL);
  
  MCTInitStruct.oFOCDrive = oFOC[0];
  MCTInitStruct.oPIDSpeed = oPIDSpeed[0];
  MCTInitStruct.oPIDIq = oPIDIq[0];
  MCTInitStruct.oPIDId = oPIDId[0];
  MCTInitStruct.oPIDFluxWeakening = oPIFW_M1; /* only if M1 is FOC IMF / SMF / IMFF FOC*/
  MCTInitStruct.oPWMnCurrFdbk = oCurrSensor[0];
#if (defined NO_SPEED_SENSORS)  
  MCTInitStruct.oRevupCtrl = oRUC_M1;              /* only if M1 is sensorless*/
#else
  MCTInitStruct.oRevupCtrl = MC_NULL;              /* only if M1 is not sensorless*/
#endif
  MCTInitStruct.oSpeedSensorMain = oSpeedSensor[0];
#if (AUX_SPEED_FDBK_M1)
  MCTInitStruct.oSpeedSensorAux = oSpeedSensorAux_M1; /* only if M1 has auxiliary sensor oSpeedSensorAux_M1*/
#else
  MCTInitStruct.oSpeedSensorAux = MC_NULL;            /* only if M1 has auxiliary sensor oSpeedSensorAux_M1*/
#endif
#if (defined NO_SPEED_SENSORS)
  MCTInitStruct.oSpeedSensorVirtual = oVSS_M1;  /* only if M1 is sensorless*/
#endif
  MCTInitStruct.oSpeednTorqueCtrl = oSTC[0];
  MCTInitStruct.oStateMachine = oSTM[0];
  MCTInitStruct.oTemperatureSensor = oTemperatureSensor[0];
  MCTInitStruct.oBusVoltageSensor = oBusSensor[0];
  MCTInitStruct.oBrakeDigitalOutput = MC_NULL;   /* brake is defined, oBrakeM1*/
  MCTInitStruct.oNTCRelay = MC_NULL;             /* relay is defined, oRelayM1*/
  MCTInitStruct.oMPM = oMPM[0];

  MCT_Init(oMCTuning[0],MCTInitStruct);
  
  oMCTList[0] = oMCTuning[0];
#endif

#ifdef DUALDRIVE
  oSTM[1] = STM_NewObject();
  STM_Init(oSTM[1]);
  
  oPIDSpeed[1] = (CPI)PI_NewObject(&PISpeedParamsM2);
  PI_ObjectInit(oPIDSpeed[1]); 

#if (defined STATE_OBSERVER_PLL2) 
  oSpeedSensor[1] = (CSPD)STO_NewObject(&SpeednPosFdbkParamsM2,&STOParamsM2); /* speed sensor STO, ENC, HALL xNew and xParamsM2*/
#elif (defined STATE_OBSERVER_CORDIC2) 
  oSpeedSensor[1] = (CSPD)STO_CR_NewObject(&SpeednPosFdbkParamsM2,&STO_CORDICParamsM2); /* speed sensor STO, ENC, HALL xNew and xParamsM2*/  
#elif (defined ENCODER2)
  oSpeedSensor[1] = (CSPD)ENC_NewObject(&SpeednPosFdbkParamsM2,&ENCParamsM2); /* speed sensor STO, ENC, HALL xNew and xParamsM2*/
#elif (defined HALL_SENSORS2)
  oSpeedSensor[1] = (CSPD)HALL_NewObject(&SpeednPosFdbkParamsM2,&HALLParamsM2); /* speed sensor STO, ENC, HALL xNew and xParamsM2*/  
#else
#error "Invalid boot: configuration not valid or to be assigned"
#endif
  
  SPD_Init(oSpeedSensor[1]);
  
#if AUX_SPEED_FDBK_M2 
#if (defined AUX_STATE_OBSERVER_PLL2)
  oSpeedSensorAux_M2 = (CSPD)STO_NewObject(&SpeednPosFdbkParamsM2,&STOParamsM2); /* aux speed sensor STO, ENC, HALL xNew and xParamsM2*/
#elif (defined AUX_STATE_OBSERVER_CORDIC2)
  oSpeedSensorAux_M2 = (CSPD)STO_CR_NewObject(&SpeednPosFdbkParamsM2,&STO_CORDICParamsM2); /* aux speed sensor STO, ENC, HALL xNew and xParamsM2*/  
#elif (defined VIEW_ENCODER_FEEDBACK2)
  oSpeedSensorAux_M2 = (CSPD)ENC_NewObject(&SpeednPosFdbkParamsM1,&ENCParamsM1); /* aux speed sensor STO, ENC, HALL xNew and xParamsM2*/
#elif (defined VIEW_HALL_FEEDBACK2)
  oSpeedSensorAux_M2 = (CSPD)HALL_NewObject(&SpeednPosFdbkParamsM1,&HALLParamsM1); /* aux speed sensor STO, ENC, HALL xNew and xParamsM2*/  
#endif  
  SPD_Init(oSpeedSensorAux_M2);
#endif
  
  oSTC[1] = STC_NewObject(&SpeednTorqCtrlParamsM2);
  STC_Init(oSTC[1],oPIDSpeed[1],oSpeedSensor[1]);

#if ((defined NO_SPEED_SENSORS2)||(defined ENCODER2)||(defined VIEW_ENCODER_FEEDBACK2))
  oVSS_M2 = (CSPD)VSS_NewObject(&SpeednPosFdbkParamsM2,&VirtualSpeedSensorParamsM2);
  SPD_Init(oVSS_M2);                               
#endif
#if (defined NO_SPEED_SENSORS2)  
  oRUC_M2 = RUC_NewObject(&RevupCtrlParamsM2);        /* only if sensorless*/
  RUC_Init(oRUC_M2,oSTC[1],(CVSS_SPD)oVSS_M2);        /* only if sensorless*/
#endif
#if ((defined ENCODER2)||(defined VIEW_ENCODER_FEEDBACK2))  
  oEAC_M2 = (CEAC)EAC_NewObject(&EncAlignCtrlParamsM2);
#endif
#if (defined ENCODER2)
  EAC_Init(oEAC_M2,oSTC[1],(CVSS_SPD)oVSS_M2,(CENC_SPD)oSpeedSensor[1]);
#endif
#if (defined VIEW_ENCODER_FEEDBACK2)
  EAC_Init(oEAC_M2,oSTC[1],(CVSS_SPD)oVSS_M2,(CENC_SPD)oSpeedSensorAux_M2);
#endif  
  
  oPIDIq[1] = (CPI)PI_NewObject(&PIIqParamsM2);
  PI_ObjectInit(oPIDIq[1]);
  
  oPIDId[1] = (CPI)PI_NewObject(&PIIdParamsM2);
  PI_ObjectInit(oPIDId[1]);   

#if defined BUS_VOLTAGE_MEASUREMENT2
  oBusSensor[1] = (CVBS)RVBS_NewObject(&RealBusVoltageSensorParamsM2,
                                       &RdividerParamsM2); /* powerboard configuration: Rdivider or Virtual*/  
#else
  oBusSensor[1] = (CVBS)VVBS_NewObject(&VirtualBusVoltageSensorParamsM2,
                                       &VirtualBusParamsM2); /* powerboard configuration: Rdivider or Virtual*/    
#endif  
  VBS_Init(oBusSensor[1],oCurrSensor[0]);
  
  oMPM[1] = (CMPM)PQD_NewObject(&PQD_MotorPowerMeasurementParamsM2);
  PQD_MPMInitStruct.oFOC = oFOC[1];
  PQD_MPMInitStruct.oVBS = oBusSensor[1];
  MPM_Init(oMPM[1],(pMPMInitStruct_t)&PQD_MPMInitStruct);
  
#if ON_OVER_VOLTAGE2 == TURN_ON_R_BRAKE
  oR_Brake[1] = DOUT_NewObject(&R_BrakeParamsM2); 
  DOUT_Init(oR_Brake[1]);
#endif
  
#if defined HEAT_SINK_TEMPERATURE_MEASUREMENT2
  oTemperatureSensor[1] = (CTSNS)NTC_NewObject(&RealTempSensorParamsM2,
                                               &NTCParamsM2); /* powerboard configuration: NTC or Virtual*/
#else
  oTemperatureSensor[1] = (CTSNS)VTS_NewObject(&VirtualTempSensorParamsM2,
                                               &VirtualTParamsM2); /* powerboard configuration: NTC or Virtual*/
#endif
  
  TSNS_Init(oTemperatureSensor[1],oCurrSensor[0]);  
  
  FOCInitStructure[1].oCurrSensor = oCurrSensor[1];
  FOCInitStructure[1].oSpdTrqController = oSTC[1];
  FOCInitStructure[1].oVbusSensor = oBusSensor[1];
  FOCInitStructure[1].oSpeedSensor = oSpeedSensor[1];
  FOCInitStructure[1].oPI_q = oPIDIq[1];
  FOCInitStructure[1].oPI_d = oPIDId[1];
  
  oPIFW_M2 = (CPI)PI_NewObject(&PIFluxWeakeningParamsM2);  /* only if FOC SMF, IMF, IMFF*/
  PI_ObjectInit(oPIFW_M2);     /* PI_ObjectInit or PID_ObjectInit*/   
  PMSMInitStructureM2.oFluxWeakeningPI = oPIFW_M2;     /* only if FOC SMF, IMF, IMFF*/
  PMSMInitStructureM2.oSpeedPI = oPIDSpeed[1]; /* only if FOC SMF, IMF, IMFF*/
  
  FOC_Init(oFOC[1],FOCInitStructure[1],&PMSMInitStructureM2); /* third parameter according to FOC derived*/  
    
  oMCInterface[1] = MCI_NewObject(MC_NULL);
  MCI_Init(oMCInterface[1], oSTM[1], oSTC[1], oFOC[1]);
  MCI_ExecSpeedRamp(oMCInterface[1], 
                    STC_GetMecSpeedRef01HzDefault(oSTC[1]),0); /*First command to STC*/
  
  oMCIList[1] = oMCInterface[1]; 
    
#ifdef MC_TUNING_INTERFACE
  oMCTuning[1] = MCT_NewObject(MC_NULL);
  
  MCTInitStruct.oFOCDrive = oFOC[1];
  MCTInitStruct.oPIDSpeed = oPIDSpeed[1];
  MCTInitStruct.oPIDIq = oPIDIq[1];
  MCTInitStruct.oPIDId = oPIDId[1];
  MCTInitStruct.oPIDFluxWeakening = oPIFW_M2; /* only if M2 is FOC IMF / SMF / IMFF FOC*/
  MCTInitStruct.oPWMnCurrFdbk = oCurrSensor[1];
#if (defined NO_SPEED_SENSORS2)  
  MCTInitStruct.oRevupCtrl = oRUC_M2;              /* only if M2 is sensorless*/
#else
  MCTInitStruct.oRevupCtrl = MC_NULL;              /* only if M2 is not sensorless*/
#endif
  MCTInitStruct.oSpeedSensorMain = oSpeedSensor[1];
#if (AUX_SPEED_FDBK_M2)
  MCTInitStruct.oSpeedSensorAux = oSpeedSensorAux_M2; /* only if M2 has auxiliary sensor oSpeedSensorAux_M2*/
#else
  MCTInitStruct.oSpeedSensorAux = MC_NULL;            /* only if M2 has auxiliary sensor oSpeedSensorAux_M2*/
#endif

#if (defined NO_SPEED_SENSORS2)
  MCTInitStruct.oSpeedSensorVirtual = oVSS_M2;  /* only if M2 is sensorless*/
#endif
  MCTInitStruct.oSpeednTorqueCtrl = oSTC[1];
  MCTInitStruct.oStateMachine = oSTM[1];
  MCTInitStruct.oTemperatureSensor = oTemperatureSensor[1];
  MCTInitStruct.oBusVoltageSensor = oBusSensor[1];
  MCTInitStruct.oBrakeDigitalOutput = MC_NULL;   /* brake is defined, oBrakeM2*/
  MCTInitStruct.oNTCRelay = MC_NULL;             /* relay is defined, oRelayM2*/
  MCTInitStruct.oMPM = oMPM[1];

  MCT_Init(oMCTuning[1],MCTInitStruct);
  
  oMCTList[1] = oMCTuning[1];
#endif
#endif  
}

/**
  * @brief  It executes some of the control duties on Motor 1 and - if available -  
  *         Motor 2 accordingly with the present state of its state machine. 
  *         In particular, duties not requiring a very precise timing and/or 
  *         needing a low refresh rate are here executed
  * @param  None
  * @retval None
  */
void TSK_LowFrequencyTask(void)
{
  TSK_LowFrequencyClock();
  TSK_LowFrequencyTaskM1();
#ifdef DUALDRIVE
  TSK_LowFrequencyTaskM2();
#endif
}

/**
* @brief  It executes some of the control duties on Motor 1 and - if available -  
*         Motor 2 accordingly with the present state of its state machine. 
*         In particular, duties requiring a specific timing 
*         (e.g. speed controller(s)) are here executed
* @param  None
* @retval None
*/
void TSK_MediumFrequencyTask(void)
{
  TSK_MediumFrequencyTaskM1();
#ifdef DUALDRIVE  
  TSK_MediumFrequencyTaskM2();
#endif  
}
  
/**
  * @brief  It executes some of the control duties on Motor 1 accordingly with  
  *         the present state of its state machine. In particular, duties not 
  *         requiring a very precise timing and/or needing a low refresh rate
  *         are here executed
  * @param  None
  * @retval void
  */
void TSK_LowFrequencyTaskM1(void)
{
  State_t StateM1;
  
  MCI_UpdateCommand(oMCInterface[0]);
  
  StateM1 = STM_GetState(oSTM[0]);
  switch(StateM1)
  {
  case IDLE_START:
    if (!TSK_ChargeBootCapDelayHasStartedM1())
    {
      FOC_Clear(oFOC[0]);
#if (defined NO_SPEED_SENSORS)      
      FOC_SetDriveInput(oFOC[0],EXTERNAL);  /*  only for sensorless*/
      FOC_SetSpeedSensor(oFOC[0],oVSS_M1);  	/*  only for sensorless */
#endif
      PWMC_TurnOnLowSides(oCurrSensor[0]); 
      TSK_SetChargeBootCapDelayM1(1);
    }
    else
      if (TSK_ChargeBootCapDelayHasElapsedM1())
      {
        PWMC_SwitchOffPWM(oCurrSensor[0]);
#if (defined NO_SPEED_SENSORS)        
        RUC_Clear(oRUC_M1,MCI_GetImposedMotorDirection(oMCInterface[0]));/*  only for sensorless */
#endif
#if (defined (NO_SPEED_SENSORS) || defined(HALL_SENSORS) || defined(ENCODER))
        SPD_Clear(oSpeedSensor[0]); 		/*  only for sensorless/hall/encoder main*/
#endif
#if (defined(AUX_STATE_OBSERVER_PLL) || defined(AUX_STATE_OBSERVER_CORDIC) || defined(VIEW_HALL_FEEDBACK) || defined(VIEW_ENCODER_FEEDBACK))
        SPD_Clear(oSpeedSensorAux_M1); 		/*  only for sensorless/hall main/auxiliary*/
#endif        
        PWMC_CurrentReadingCalibr(oCurrSensor[0]);
      
        if(STM_NextState(oSTM[0], START) == FALSE)
        {
          STM_FaultProcessing(oSTM[0], MC_SW_ERROR, 0);
        }
        else        
        {
          FOC_Clear(oFOC[0]);
          PWMC_SwitchOnPWM(oCurrSensor[0]); 
        }
      }
    break;
#if ((defined ENCODER)||(defined VIEW_ENCODER_FEEDBACK)) /*  only for encoder*/
  case IDLE_ALIGNMENT:
    if (!TSK_ChargeBootCapDelayHasStartedM1())
    {  	
      FOC_Clear(oFOC[0]);
      PWMC_TurnOnLowSides(oCurrSensor[0]); 
      TSK_SetChargeBootCapDelayM1(1);
    }
    else
      if (TSK_ChargeBootCapDelayHasElapsedM1())
      {
        PWMC_SwitchOffPWM(oCurrSensor[0]);
        PWMC_CurrentReadingCalibr(oCurrSensor[0]);
        
        FOC_Clear(oFOC[0]);
        FOC_SetDriveInput(oFOC[0],EXTERNAL);       
        FOC_SetSpeedSensor(oFOC[0],oVSS_M1);
        EAC_StartAlignment(oEAC_M1);
        PWMC_SwitchOnPWM(oCurrSensor[0]);
        
        if(STM_NextState(oSTM[0], ALIGNMENT) == FALSE)
        {
          STM_FaultProcessing(oSTM[0], MC_SW_ERROR, 0);
        }
      }
    break;
#endif
  case ANY_STOP:
    PWMC_SwitchOffPWM(oCurrSensor[0]); 
    TSK_SetStopPermanencyTimeM1(40);
    if(STM_NextState(oSTM[0], STOP) == FALSE)
    {
      STM_FaultProcessing(oSTM[0], MC_SW_ERROR, 0);
    }
    break;
  case STOP:
    if(TSK_StopPermanencyTimeHasElapsedM1())
    {
      if(STM_NextState(oSTM[0], STOP_IDLE) == FALSE)
      {
        STM_FaultProcessing(oSTM[0], MC_SW_ERROR, 0);
      }
    }
    break;
  case STOP_IDLE:
#if (defined NO_SPEED_SENSORS)    
    RUC_Clear(oRUC_M1,MCI_GetImposedMotorDirection(oMCInterface[0]));/*  only for sensorless */
    FOC_SetSpeedSensor(oFOC[0],oVSS_M1);  	/*  sensor-less */
#endif
    if(STM_NextState(oSTM[0], IDLE) == FALSE)
    {
      STM_FaultProcessing(oSTM[0], MC_SW_ERROR, 0);
    }
    break;
  default:
    break;
  }
}

#ifdef DUALDRIVE

/**
  * @brief  It executes some of the control duties on Motor 2 accordingly with  
  *         the present state of its state machine. In particular, duties not 
  *         requiring a very precise timing and/or needing a low refresh rate
  *         are here executed
  * @param  None
  * @retval void
  */
void TSK_LowFrequencyTaskM2(void)
{
  State_t StateM2;
  
  MCI_UpdateCommand(oMCInterface[1]);
  
  StateM2 = STM_GetState(oSTM[1]);
  switch(StateM2)
  {
  case IDLE_START:
    if (!TSK_ChargeBootCapDelayHasStartedM2())
    {
      FOC_Clear(oFOC[1]);
#if (defined NO_SPEED_SENSORS2)
      FOC_SetDriveInput(oFOC[1],EXTERNAL);      /*  only for sensorless*/
      FOC_SetSpeedSensor(oFOC[1],oVSS_M2);  	/*  only for sensorless */
#endif
      PWMC_TurnOnLowSides(oCurrSensor[1]); 
      TSK_SetChargeBootCapDelayM2(1);
    }
    else
      if (TSK_ChargeBootCapDelayHasElapsedM2())
      {
        PWMC_SwitchOffPWM(oCurrSensor[1]);
#if (defined NO_SPEED_SENSORS2)        
        RUC_Clear(oRUC_M2,MCI_GetImposedMotorDirection(oMCInterface[1]));/*  only for sensorless */
#endif
#if (defined (NO_SPEED_SENSORS2) || defined(HALL_SENSORS2) || defined(ENCODER2))
        SPD_Clear(oSpeedSensor[1]); 		/*  only for sensorless/hall/encoder main*/
#endif
#if (defined(AUX_STATE_OBSERVER_PLL2) || defined(AUX_STATE_OBSERVER_CORDIC2) || defined(VIEW_HALL_FEEDBACK2) || defined(VIEW_ENCODER_FEEDBACK2))        
        SPD_Clear(oSpeedSensorAux_M2); 		/*  only for sensorless/hall main/auxiliary*/
#endif        
        PWMC_CurrentReadingCalibr(oCurrSensor[1]);
        
        if(STM_NextState(oSTM[1], START) == FALSE)
        {
          STM_FaultProcessing(oSTM[1], MC_SW_ERROR, 0);
        }
        else        
        {
          FOC_Clear(oFOC[1]);
          PWMC_SwitchOnPWM(oCurrSensor[1]); 
        }
      }
    break;
#if ((defined ENCODER2)||(defined VIEW_ENCODER_FEEDBACK2)) /*  only for encoder*/
  case IDLE_ALIGNMENT:
    if (!TSK_ChargeBootCapDelayHasStartedM2())
    {  	
      FOC_Clear(oFOC[1]);
      PWMC_TurnOnLowSides(oCurrSensor[1]); 
      TSK_SetChargeBootCapDelayM2(1);
    }
    else
      if (TSK_ChargeBootCapDelayHasElapsedM2())
      {
        PWMC_SwitchOffPWM(oCurrSensor[1]);
        PWMC_CurrentReadingCalibr(oCurrSensor[1]);
        
        FOC_Clear(oFOC[1]);
        FOC_SetDriveInput(oFOC[1],EXTERNAL);       
        FOC_SetSpeedSensor(oFOC[1],oVSS_M2);
        EAC_StartAlignment(oEAC_M2);
        PWMC_SwitchOnPWM(oCurrSensor[1]);
        
        if(STM_NextState(oSTM[1], ALIGNMENT) == FALSE)
        {
          STM_FaultProcessing(oSTM[1], MC_SW_ERROR, 0);
        }
      }
    break;
#endif    
  case ANY_STOP:
    PWMC_SwitchOffPWM(oCurrSensor[1]); 
    TSK_SetStopPermanencyTimeM2(40);
    if(STM_NextState(oSTM[1], STOP) == FALSE)
    {
      STM_FaultProcessing(oSTM[1], MC_SW_ERROR, 0);
    }
    break;
  case STOP:
    if(TSK_StopPermanencyTimeHasElapsedM2())
    {
      if(STM_NextState(oSTM[1], STOP_IDLE) == FALSE)
      {
        STM_FaultProcessing(oSTM[1], MC_SW_ERROR, 0);
      }
    }
    break;
  case STOP_IDLE:
#if (defined NO_SPEED_SENSORS2)    
    RUC_Clear(oRUC_M2,MCI_GetImposedMotorDirection(oMCInterface[1])); /*  only for sensorless */
    FOC_SetSpeedSensor(oFOC[1],oVSS_M2);  	/*  sensor-less */
#endif
    if(STM_NextState(oSTM[1], IDLE) == FALSE)
    {
      STM_FaultProcessing(oSTM[1], MC_SW_ERROR, 0);
    }
    break;
  default:
    break;
  }
}

#endif //DUALDRIVE LF

/**
  * @brief  It executes some of the control duties on Motor 1 accordingly with  
  *         the present state of its state machine. In particular, duties 
  *         requiring a specific timing (e.g. speed controller) are here 
  *         executed
  * @param  None
  * @retval void
  */
void TSK_MediumFrequencyTaskM1(void)
{
  State_t StateM1;
  bool IsSpeedReliable;
  int16_t wAux = 0;
  
  IsSpeedReliable = SPD_CalcAvrgMecSpeed01Hz(oSpeedSensor[0],&wAux);
#if (defined(VIEW_HALL_FEEDBACK)||defined(VIEW_ENCODER_FEEDBACK)||defined(AUX_STATE_OBSERVER_PLL)||defined(AUX_STATE_OBSERVER_CORDIC))
  SPD_CalcAvrgMecSpeed01Hz(oSpeedSensorAux_M1,&wAux);  /*  Only if Aux sensored is enabled */
#endif
  
  MPM_CalcElMotorPower(oMPM[0]);
  
  StateM1 = STM_GetState(oSTM[0]);
  switch(StateM1)
  {
  case START:
    /* only for sensor-less control */
#if (defined NO_SPEED_SENSORS)    
    {     
      int16_t hForcedMecSpeed01Hz;
      Curr_Components IqdRef;
      bool StartUpTransitionEnded;
      bool StartUpDoTransition;
      
      if(!RUC_Exec(oRUC_M1))
      {
       STM_FaultProcessing(oSTM[0], MC_START_UP, 0);  /*Time allowed for startup has ended*/ 
      }
      
      StartUpTransitionEnded = SPD_CalcAvrgMecSpeed01Hz(oVSS_M1,&hForcedMecSpeed01Hz);
      
      IqdRef.qI_Component1 = STC_CalcTorqueReference(oSTC[0], MC_NULL);
      IqdRef.qI_Component2 = 0;
      FOC_SetIqdref(oFOC[0],IqdRef);
      
#if (defined(STATE_OBSERVER_PLL))
      StartUpDoTransition = VSPD_SetStartTransition(oVSS_M1,STO_IsObserverConverged((CSTO_SPD)oSpeedSensor[0],hForcedMecSpeed01Hz));
#elif (defined(STATE_OBSERVER_CORDIC))
      StartUpDoTransition = VSPD_SetStartTransition(oVSS_M1,STO_CR_IsObserverConverged((CSTO_CR_SPD)oSpeedSensor[0],hForcedMecSpeed01Hz));
#endif
      
      if (StartUpDoTransition == FALSE)
      {
        StartUpTransitionEnded = TRUE;
      }
      
      if (StartUpTransitionEnded == TRUE)
      {
        {      
          Curr_Components StatorCurrent;
          StatorCurrent = FOC_GetIalphabeta(oFOC[0]);
          StatorCurrent = MCM_Park(StatorCurrent, SPD_GetElAngle(oSpeedSensor[0]));
          PI_SetIntegralTerm(oPIDSpeed[0],(int32_t)StatorCurrent.qI_Component1*PI_GetKIDivisor(oPIDSpeed[0])); 
        }        
        if(STM_NextState(oSTM[0], START_RUN) == FALSE)
        {
          STM_FaultProcessing(oSTM[0], MC_SW_ERROR, 0);
        }
      }
    }
#endif
    /* only for sensored*/
#if ((defined ENCODER)||(defined HALL_SENSORS))
        if(STM_NextState(oSTM[0], START_RUN) == FALSE)
        {
          STM_FaultProcessing(oSTM[0], MC_SW_ERROR, 0);
        }
#endif
    break;
#if ((defined ENCODER)||(defined VIEW_ENCODER_FEEDBACK))
  case ALIGNMENT:
    if(!EAC_Exec(oEAC_M1))
    {
      Curr_Components IqdRef;
      IqdRef.qI_Component1 = 0;
      IqdRef.qI_Component2 = STC_CalcTorqueReference(oSTC[0], MC_NULL);
      FOC_SetIqdref(oFOC[0],IqdRef);	
    }
    else
    {
      PWMC_SwitchOffPWM(oCurrSensor[0]);
      STC_SetControlMode(oSTC[0], STC_SPEED_MODE);
      FOC_SetSpeedSensor(oFOC[0],oSpeedSensor[0]);
      if(STM_NextState(oSTM[0], ANY_STOP) == FALSE)
      {
        STM_FaultProcessing(oSTM[0], MC_SW_ERROR, 0);
      }
    }    
    break;    
#endif
  case START_RUN:
    /* only for sensor-less control */
#if (defined NO_SPEED_SENSORS)
    MCI_UpdateCommand(oMCInterface[0]);
    FOC_SetSpeedSensor(oFOC[0],oSpeedSensor[0]);  /*Observer has converged*/
#endif
    FOC_CalcCurrRef(oFOC[0]);
    if(STM_NextState(oSTM[0], RUN) == FALSE)
    {
      STM_FaultProcessing(oSTM[0], MC_SW_ERROR, 0);
    }
    break;
  case RUN:
    FOC_CalcCurrRef(oFOC[0]);
    if(!IsSpeedReliable)
    {
      STM_FaultProcessing(oSTM[0], MC_SPEED_FDBK, 0);
    }
    break;
  default:
    break;    
  }
}

#ifdef DUALDRIVE
/**
  * @brief  It executes some of the control duties on Motor 2 accordingly with  
  *         the present state of its state machine. In particular, duties 
  *         requiring a specific timing (e.g. speed controller(s)) are here 
  *         executed
  * @param  None
  * @retval void
  */
void TSK_MediumFrequencyTaskM2(void)
{
  State_t StateM2;
  bool IsSpeedReliable;
  int16_t wAux = 0;
  
  IsSpeedReliable = SPD_CalcAvrgMecSpeed01Hz(oSpeedSensor[1],&wAux);  
#if (defined(VIEW_HALL_FEEDBACK2)||defined(VIEW_ENCODER_FEEDBACK2)||defined(AUX_STATE_OBSERVER_PLL2)||defined(AUX_STATE_OBSERVER_CORDIC2))
  SPD_CalcAvrgMecSpeed01Hz(oSpeedSensorAux_M2,&wAux);  /*  Only if Aux sensored is enabled */
#endif
  
  MPM_CalcElMotorPower(oMPM[1]);
  
  StateM2 = STM_GetState(oSTM[1]);
  switch(StateM2)
  {
  case START:
    /* only for sensor-less control */
#if (defined NO_SPEED_SENSORS2)    
    {     
      int16_t hForcedMecSpeed01Hz;
      Curr_Components IqdRef;
      bool StartUpTransitionEnded;
      bool StartUpDoTransition;
      
      if(!RUC_Exec(oRUC_M2))
      {
       STM_FaultProcessing(oSTM[1], MC_START_UP, 0);  /*Time allowed for startup has ended*/ 
      }
      
      StartUpTransitionEnded = SPD_CalcAvrgMecSpeed01Hz(oVSS_M2,&hForcedMecSpeed01Hz);
      
      IqdRef.qI_Component1 = STC_CalcTorqueReference(oSTC[1], MC_NULL);
      IqdRef.qI_Component2 = 0;
      FOC_SetIqdref(oFOC[1],IqdRef);
      
#if (defined(STATE_OBSERVER_PLL2))
      StartUpDoTransition = VSPD_SetStartTransition(oVSS_M2,STO_IsObserverConverged((CSTO_SPD)oSpeedSensor[1],hForcedMecSpeed01Hz));
#elif (defined(STATE_OBSERVER_CORDIC2))
      StartUpDoTransition = VSPD_SetStartTransition(oVSS_M2,STO_CR_IsObserverConverged((CSTO_CR_SPD)oSpeedSensor[1],hForcedMecSpeed01Hz));
#endif
      
      if (StartUpDoTransition == FALSE)
      {
        StartUpTransitionEnded = TRUE;
      }      
      
      if (StartUpTransitionEnded == TRUE)
      {
        {      
          Curr_Components StatorCurrent;
          StatorCurrent = FOC_GetIalphabeta(oFOC[1]);
          StatorCurrent = MCM_Park(StatorCurrent, SPD_GetElAngle(oSpeedSensor[1]));
          PI_SetIntegralTerm(oPIDSpeed[1],(int32_t)StatorCurrent.qI_Component1*PI_GetKIDivisor(oPIDSpeed[1])); 
        }        
        if(STM_NextState(oSTM[1], START_RUN) == FALSE)
        {
          STM_FaultProcessing(oSTM[1], MC_SW_ERROR, 0);
        }
      }
    }
#endif
    /* only for sensored*/
#if ((defined ENCODER2)||(defined HALL_SENSORS2))
        if(STM_NextState(oSTM[1], START_RUN) == FALSE)
        {
          STM_FaultProcessing(oSTM[1], MC_SW_ERROR, 0);
        }
#endif    
    break;
#if ((defined ENCODER2)||(defined VIEW_ENCODER_FEEDBACK2)) /*  only for encoder*/
  case ALIGNMENT:
    if(!EAC_Exec(oEAC_M2))
    {
      Curr_Components IqdRef;
      IqdRef.qI_Component1 = 0;
      IqdRef.qI_Component2 = STC_CalcTorqueReference(oSTC[1], MC_NULL);
      FOC_SetIqdref(oFOC[1],IqdRef);	
    }
    else
    {
      PWMC_SwitchOffPWM(oCurrSensor[1]);
      STC_SetControlMode(oSTC[1], STC_SPEED_MODE);
      FOC_SetSpeedSensor(oFOC[1],oSpeedSensor[1]);
      if(STM_NextState(oSTM[1], ANY_STOP) == FALSE)
      {
        STM_FaultProcessing(oSTM[1], MC_SW_ERROR, 0);
      }
    }    
    break;    
#endif    
  case START_RUN:
    /* only for sensor-less control */
#if (defined NO_SPEED_SENSORS2)    
    MCI_UpdateCommand(oMCInterface[1]);
    FOC_SetSpeedSensor(oFOC[1],oSpeedSensor[1]);  /*Observer has converged*/
#endif

    FOC_CalcCurrRef(oFOC[1]);
    if(STM_NextState(oSTM[1], RUN) == FALSE)
    {
      STM_FaultProcessing(oSTM[1], MC_SW_ERROR, 0);
    }
    break;
  case RUN:
    FOC_CalcCurrRef(oFOC[1]);
    if(!IsSpeedReliable)
    {
      STM_FaultProcessing(oSTM[1], MC_SPEED_FDBK, 0);
    }
    break;
  default:
    break;    
  }
}
#endif

/**
  * @brief  Accordingly with the present state(s) of the state machine(s), it 
  *         executes those motor control duties requiring a high frequency rate
  *         and a precise timing (e.g. FOC current control loop)
  * @param  None
  * @retval uint8_t It return the motor instance number of last executed FOC.
  */
uint8_t TSK_HighFrequencyTask(void)
{ 
  uint8_t bMotorNbr = 0;
  uint16_t hFOCreturn;
  
#ifdef SINGLEDRIVE

#if (defined NO_SPEED_SENSORS)
  uint16_t hState;  /*  only if sensorless main*/
#endif
#if ((defined STATE_OBSERVER_PLL)||(defined AUX_STATE_OBSERVER_PLL))
  Observer_Inputs_t STO_Inputs; /*  only if sensorless main/aux*/
  bool IsAccelerationStageReached;
#endif
#if ((defined STATE_OBSERVER_CORDIC)||(defined AUX_STATE_OBSERVER_CORDIC))
  STO_CR_Observer_Inputs_t STO_CR_Inputs; /*  only if sensorless main/aux*/
#endif
  
#if ((defined ENCODER)||(defined HALL_SENSORS))
    SPD_CalcAngle(oSpeedSensor[0],MC_NULL);   /* if not sensorless then 2nd parameter is MC_NULL*/    
#endif
#if ((defined VIEW_ENCODER_FEEDBACK)||(defined VIEW_HALL_FEEDBACK))    
    SPD_CalcAngle(oSpeedSensorAux_M1,MC_NULL);  /*  only if auxiliary sensor is enabled */  
#endif

#if ((defined STATE_OBSERVER_PLL)||(defined AUX_STATE_OBSERVER_PLL))
  STO_Inputs.Valfa_beta = FOC_GetValphabeta(oFOC[0]);  /* only if sensorless*/
#endif
#if ((defined STATE_OBSERVER_CORDIC)||(defined AUX_STATE_OBSERVER_CORDIC))
  STO_CR_Inputs.Valfa_beta = FOC_GetValphabeta(oFOC[0]);  /* only if sensorless*/
#endif  
  
  hFOCreturn = FOC_CurrController(oFOC[0]);
  
  if(hFOCreturn == MC_FOC_DURATION)
  {
    STM_FaultProcessing(oSTM[0], MC_FOC_DURATION, 0); 
  }
  else
  {
#if ((defined STATE_OBSERVER_PLL)||(defined AUX_STATE_OBSERVER_PLL))
    STO_Inputs.Ialfa_beta = FOC_GetIalphabeta(oFOC[0]); /*  only if sensorless*/
    
    STO_Inputs.Vbus = VBS_GetAvBusVoltage_d(oBusSensor[0]); /*  only for sensorless*/
#endif    
#if ((defined STATE_OBSERVER_CORDIC)||(defined AUX_STATE_OBSERVER_CORDIC))
    STO_CR_Inputs.Ialfa_beta = FOC_GetIalphabeta(oFOC[0]); /*  only if sensorless*/
    
    STO_CR_Inputs.Vbus = VBS_GetAvBusVoltage_d(oBusSensor[0]); /*  only for sensorless*/    
#endif    
#if (defined STATE_OBSERVER_PLL)
    IsAccelerationStageReached = RUC_FirstAccelerationStageReached(oRUC_M1);
    
    SPD_CalcAngle(oSpeedSensor[0],&STO_Inputs);   /* if not sensorless then 2nd parameter is MC_NULL*/

    STO_CalcAvrgElSpeedDpp((CSTO_SPD) oSpeedSensor[0]); /*  Only in case of Sensor-less */    
    
    if (IsAccelerationStageReached == FALSE)
    {
      STO_ResetPLL((CSTO_SPD)oSpeedSensor[0]);
    }   
    
    hState = STM_GetState(oSTM[0]);
    if((hState == START) || (hState == START_RUN)) /*  only for sensor-less*/
    {
      int16_t hObsAngle;
      hObsAngle = SPD_GetElAngle(oSpeedSensor[0]);
      SPD_CalcAngle(oVSS_M1,&hObsAngle);
    }
#endif
#if (defined STATE_OBSERVER_CORDIC)
    SPD_CalcAngle(oSpeedSensor[0],&STO_CR_Inputs);   /* if not sensorless then 2nd parameter is MC_NULL*/
    
    STO_CR_CalcAvrgElSpeedDpp((CSTO_CR_SPD) oSpeedSensor[0]); /*  Only in case of Sensor-less */
    
    hState = STM_GetState(oSTM[0]);
    if((hState == START) || (hState == START_RUN)) /*  only for sensor-less*/
    {
      int16_t hObsAngle;
      hObsAngle = SPD_GetElAngle(oSpeedSensor[0]);      
      SPD_CalcAngle(oVSS_M1,&hObsAngle);  
    }
#endif    
#if (defined(AUX_STATE_OBSERVER_PLL))
    SPD_CalcAngle(oSpeedSensorAux_M1,&STO_Inputs);   /* if not sensorless then 2nd parameter is MC_NULL*/
    
    STO_CalcAvrgElSpeedDpp((CSTO_SPD) oSpeedSensorAux_M1); /*  Only in case of Sensor-less auxiliary*/
#endif
#if (defined(AUX_STATE_OBSERVER_CORDIC))
    SPD_CalcAngle(oSpeedSensorAux_M1,&STO_CR_Inputs);   /* if not sensorless then 2nd parameter is MC_NULL*/
    
    STO_CR_CalcAvrgElSpeedDpp((CSTO_CR_SPD) oSpeedSensorAux_M1); /*  Only in case of Sensor-less auxiliary*/
#endif    
  }
#else //DUALDRIVE

#if ((defined NO_SPEED_SENSORS)||(defined NO_SPEED_SENSORS2))
  uint16_t hState;  /*  only if, at least, one of the two motors is sensorless main*/
#endif
#if ((defined STATE_OBSERVER_PLL)||(defined AUX_STATE_OBSERVER_PLL)||(defined STATE_OBSERVER_PLL2)||(defined AUX_STATE_OBSERVER_PLL2))
  Observer_Inputs_t STO_Inputs; /*  only if sensorless main/aux*/
  bool IsAccelerationStageReached;
#endif
#if ((defined STATE_OBSERVER_CORDIC)||(defined AUX_STATE_OBSERVER_CORDIC)||(defined STATE_OBSERVER_CORDIC2)||(defined AUX_STATE_OBSERVER_CORDIC2))
  STO_CR_Observer_Inputs_t STO_CR_Inputs; /*  only if sensorless main/aux*/
#endif  
  
  CFOC oFOCexec = (CFOC)FOC_array[FOC_array_head];
  bMotorNbr = FOC_GetInstanceNumber(oFOCexec);
  
  if (bMotorNbr == 0)
  {
#if ((defined STATE_OBSERVER_PLL)||(defined AUX_STATE_OBSERVER_PLL))
  STO_Inputs.Valfa_beta = FOC_GetValphabeta(oFOCexec);  /* only if motor0 is sensorless*/
#endif
#if ((defined STATE_OBSERVER_CORDIC)||(defined AUX_STATE_OBSERVER_CORDIC))
  STO_CR_Inputs.Valfa_beta = FOC_GetValphabeta(oFOCexec);  /* only if motor0 is sensorless*/
#endif
    
#if ((defined ENCODER)||(defined HALL_SENSORS))
    SPD_CalcAngle(oSpeedSensor[bMotorNbr],MC_NULL);   /* if not sensorless then 2nd parameter is MC_NULL*/
#endif
#if ((defined VIEW_ENCODER_FEEDBACK)||(defined VIEW_HALL_FEEDBACK))
    SPD_CalcAngle(oSpeedSensorAux_M1,MC_NULL);  /*  only if auxiliary sensor is enabled */
#endif
  }
  else
  {
#if ((defined STATE_OBSERVER_PLL2)||(defined AUX_STATE_OBSERVER_PLL2))
    STO_Inputs.Valfa_beta = FOC_GetValphabeta(oFOCexec);  /* only if motor1 is sensorless*/
#endif
#if ((defined STATE_OBSERVER_CORDIC2)||(defined AUX_STATE_OBSERVER_CORDIC2))
    STO_CR_Inputs.Valfa_beta = FOC_GetValphabeta(oFOCexec);  /* only if motor1 is sensorless*/
#endif    
    
#if ((defined ENCODER2)||(defined HALL_SENSORS2))
    SPD_CalcAngle(oSpeedSensor[bMotorNbr],MC_NULL);   /* if not sensorless then 2nd parameter is MC_NULL*/
#endif    
#if ((defined VIEW_ENCODER_FEEDBACK2)||(defined VIEW_HALL_FEEDBACK2))
    SPD_CalcAngle(oSpeedSensorAux_M2,MC_NULL);  /*  only if auxiliary sensor is enabled */
#endif
  }
  
  hFOCreturn = FOC_CurrController(oFOCexec);
  
  if(hFOCreturn == MC_FOC_DURATION)
  {
    STM_FaultProcessing(oSTM[bMotorNbr], MC_FOC_DURATION, 0); 
  }
  else
  {
    if (bMotorNbr == 0)
    {
#if ((defined STATE_OBSERVER_PLL)||(defined AUX_STATE_OBSERVER_PLL))
      STO_Inputs.Ialfa_beta = FOC_GetIalphabeta(oFOCexec);  /* only if motor0 is sensorless*/  
      
      STO_Inputs.Vbus = VBS_GetAvBusVoltage_d(oBusSensor[bMotorNbr]); /*  only for sensorless*/
#endif
#if ((defined STATE_OBSERVER_CORDIC)||(defined AUX_STATE_OBSERVER_CORDIC))
      STO_CR_Inputs.Ialfa_beta = FOC_GetIalphabeta(oFOCexec);  /* only if motor0 is sensorless*/  
      
      STO_CR_Inputs.Vbus = VBS_GetAvBusVoltage_d(oBusSensor[bMotorNbr]); /*  only for sensorless*/
#endif      
#if (defined STATE_OBSERVER_PLL)
      
      IsAccelerationStageReached = RUC_FirstAccelerationStageReached(oRUC_M1);
      
      SPD_CalcAngle(oSpeedSensor[bMotorNbr],&STO_Inputs);   /* if not sensorless then 2nd parameter is MC_NULL*/
      
      STO_CalcAvrgElSpeedDpp((CSTO_SPD) oSpeedSensor[bMotorNbr]); /*  Only in case of Sensor-less */
      
      if (IsAccelerationStageReached == FALSE)
      {
        STO_ResetPLL((CSTO_SPD)oSpeedSensor[bMotorNbr]);
      }    
      
      hState = STM_GetState(oSTM[bMotorNbr]);
      if((hState == START) || (hState == START_RUN)) /*  only for sensor-less*/
      {
        int16_t hObsAngle;
        hObsAngle = SPD_GetElAngle(oSpeedSensor[bMotorNbr]);        
        SPD_CalcAngle(oVSS_M1,&hObsAngle);  
      }
#endif
#if (defined STATE_OBSERVER_CORDIC)
      SPD_CalcAngle(oSpeedSensor[bMotorNbr],&STO_CR_Inputs);   /* if not sensorless then 2nd parameter is MC_NULL*/
      
      STO_CR_CalcAvrgElSpeedDpp((CSTO_CR_SPD) oSpeedSensor[bMotorNbr]); /*  Only in case of Sensor-less */
      
      hState = STM_GetState(oSTM[bMotorNbr]);
      if((hState == START) || (hState == START_RUN)) /*  only for sensor-less*/
      {
        int16_t hObsAngle;
        hObsAngle = SPD_GetElAngle(oSpeedSensor[bMotorNbr]);        
        SPD_CalcAngle(oVSS_M1,&hObsAngle);  
      }
#endif      
#if (defined(AUX_STATE_OBSERVER_PLL))
      SPD_CalcAngle(oSpeedSensorAux_M1,&STO_Inputs);   /* if not sensorless then 2nd parameter is MC_NULL*/
      
      STO_CalcAvrgElSpeedDpp((CSTO_SPD) oSpeedSensorAux_M1); /*  Only in case of Sensor-less */
#endif
#if (defined(AUX_STATE_OBSERVER_CORDIC))
      SPD_CalcAngle(oSpeedSensorAux_M1,&STO_CR_Inputs);   /* if not sensorless then 2nd parameter is MC_NULL*/
      
      STO_CR_CalcAvrgElSpeedDpp((CSTO_CR_SPD) oSpeedSensorAux_M1); /*  Only in case of Sensor-less */
#endif       
    }
    else
    {
#if ((defined STATE_OBSERVER_PLL2)||(defined AUX_STATE_OBSERVER_PLL2))
      STO_Inputs.Ialfa_beta = FOC_GetIalphabeta(oFOCexec);  /* only if motor1 is sensorless*/  
      
      STO_Inputs.Vbus = VBS_GetAvBusVoltage_d(oBusSensor[bMotorNbr]); /*  only for sensorless*/
#endif
#if ((defined STATE_OBSERVER_CORDIC2)||(defined AUX_STATE_OBSERVER_CORDIC2))
      STO_CR_Inputs.Ialfa_beta = FOC_GetIalphabeta(oFOCexec);  /* only if motor1 is sensorless*/  
      
      STO_CR_Inputs.Vbus = VBS_GetAvBusVoltage_d(oBusSensor[bMotorNbr]); /*  only for sensorless*/
#endif      
#if (defined STATE_OBSERVER_PLL2)
      
      IsAccelerationStageReached = RUC_FirstAccelerationStageReached(oRUC_M2);
      
      SPD_CalcAngle(oSpeedSensor[bMotorNbr],&STO_Inputs);   /* if not sensorless then 2nd parameter is MC_NULL*/
      
      STO_CalcAvrgElSpeedDpp((CSTO_SPD) oSpeedSensor[bMotorNbr]); /*  Only in case of Sensor-less */
      
      if (IsAccelerationStageReached == FALSE)
      {
        STO_ResetPLL((CSTO_SPD)oSpeedSensor[bMotorNbr]);
      }       
      
      hState = STM_GetState(oSTM[bMotorNbr]);
      if((hState == START) || (hState == START_RUN)) /*  only for sensor-less*/
      {
        int16_t hObsAngle;
        hObsAngle = SPD_GetElAngle(oSpeedSensor[bMotorNbr]);
        SPD_CalcAngle(oVSS_M2,&hObsAngle);
      }      
#endif
#if (defined STATE_OBSERVER_CORDIC2)
      SPD_CalcAngle(oSpeedSensor[bMotorNbr],&STO_CR_Inputs);   /* if not sensorless then 2nd parameter is MC_NULL*/
      
      STO_CR_CalcAvrgElSpeedDpp((CSTO_CR_SPD) oSpeedSensor[bMotorNbr]); /*  Only in case of Sensor-less */
      
      hState = STM_GetState(oSTM[bMotorNbr]);
      if((hState == START) || (hState == START_RUN)) /*  only for sensor-less*/
      {
        int16_t hObsAngle;
        hObsAngle = SPD_GetElAngle(oSpeedSensor[bMotorNbr]);        
        SPD_CalcAngle(oVSS_M2,&hObsAngle);
      }      
#endif      
#if (defined(AUX_STATE_OBSERVER_PLL2))
      SPD_CalcAngle(oSpeedSensorAux_M2,&STO_Inputs);   /* if not sensorless then 2nd parameter is MC_NULL*/
      
      STO_CalcAvrgElSpeedDpp((CSTO_SPD) oSpeedSensorAux_M2); /*  Only in case of Sensor-less */
#endif
#if (defined(AUX_STATE_OBSERVER_CORDIC2))
      SPD_CalcAngle(oSpeedSensorAux_M2,&STO_CR_Inputs);   /* if not sensorless then 2nd parameter is MC_NULL*/
      
      STO_CR_CalcAvrgElSpeedDpp((CSTO_CR_SPD) oSpeedSensorAux_M2); /*  Only in case of Sensor-less */
#endif      
    }    
  }
  
  FOC_array_head++;
  if (FOC_array_head == FOC_ARRAY_LENGHT)
  {
    FOC_array_head = 0;
  }
  
#endif
  
  return bMotorNbr;
}

/**
  * @brief  It executes safety checks (e.g. bus voltage and temperature) for all
  *         drive instances. Faults flags are also here updated     
  * @param  None
  * @retval None
  */
void TSK_SafetyTask(void)
{
  uint16_t CodeReturn;
  uint16_t OverVoltageFlag;
#if (ON_OVER_VOLTAGE == TURN_ON_LOW_SIDES)  
  uint16_t OverVoltFlagOccurred;
  static  uint16_t PrevOverVoltFlagOccurred;
  static  uint16_t PrevOverVoltageFlag =MC_NO_FAULTS;
#endif
  
  OverVoltageFlag = (STM_GetFaultState(oSTM[0])>>16);
  OverVoltageFlag &= MC_OVER_VOLT;  

#if (ON_OVER_VOLTAGE == TURN_ON_LOW_SIDES)
  OverVoltFlagOccurred = (uint16_t)(STM_GetFaultState(oSTM[0]));
  OverVoltFlagOccurred &= MC_OVER_VOLT;     
  if ((OverVoltageFlag != MC_OVER_VOLT) && (OverVoltFlagOccurred!= MC_OVER_VOLT))
#endif   
      
  {     
    switch (STM_GetState(oSTM[0]))
    {
    case FAULT_NOW:   
      PWMC_SwitchOffPWM(oCurrSensor[0]);
      break;
    case FAULT_OVER:
      PWMC_SwitchOffPWM(oCurrSensor[0]);
      break;
    default:
      break;    
    }
  }

#if (ON_OVER_VOLTAGE == TURN_ON_LOW_SIDES)    
  if((PrevOverVoltFlagOccurred == MC_OVER_VOLT) && (OverVoltFlagOccurred != MC_OVER_VOLT))
  {
#if (HW_OV_CURRENT_PROT_BYPASS == ENABLE)
    DOUT_SetOutputState(oOCPDisabling[0], INACTIVE);
#endif   
   PWMC_SwitchOffPWM(oCurrSensor[0]);  
  }
  PrevOverVoltFlagOccurred = OverVoltFlagOccurred;    
#endif
      
  CodeReturn = TSNS_CalcAvTemp(oTemperatureSensor[0]);
  CodeReturn |= PWMC_CheckOverCurrent(oCurrSensor[0]);
  OverVoltageFlag = VBS_CalcAvVbus(oBusSensor[0]); 

#if (ON_OVER_VOLTAGE == TURN_ON_R_BRAKE) 
  if (OverVoltageFlag == MC_OVER_VOLT)
  {
    DOUT_SetOutputState(oR_Brake[0], ACTIVE); 
  }
  else
  {
    if (OverVoltageFlag == MC_UNDER_VOLT)
    {
      CodeReturn |=OverVoltageFlag;
    } 
    DOUT_SetOutputState(oR_Brake[0], INACTIVE);   
  }
#elif (ON_OVER_VOLTAGE == TURN_ON_LOW_SIDES)
  
  if (OverVoltageFlag == MC_OVER_VOLT)
  {
    if(PrevOverVoltageFlag != MC_OVER_VOLT)
    {
      PWMC_SwitchOffPWM(oCurrSensor[0]);
#if (HW_OV_CURRENT_PROT_BYPASS == ENABLE)
      DOUT_SetOutputState(oOCPDisabling[0], ACTIVE);
#endif 
    }    
  PWMC_TurnOnLowSides(oCurrSensor[0]);
  }  
  PrevOverVoltageFlag = OverVoltageFlag;
  
  CodeReturn |= OverVoltageFlag;
#else /* TURN_OFF_PWM  */
  CodeReturn |= OverVoltageFlag;
#endif  
  
  STM_FaultProcessing(oSTM[0], CodeReturn, ~CodeReturn);
  
#ifdef DUALDRIVE
  
  {
    uint16_t CodeReturn2;
    uint16_t OverVoltageFlag2;
#if (ON_OVER_VOLTAGE2 == TURN_ON_LOW_SIDES)  
    uint16_t OverVoltFlagOccurred2;
    static  uint16_t PrevOverVoltFlagOccurred2;
    static  uint16_t PrevOverVoltageFlag2 =MC_NO_FAULTS;    
#endif
    
    OverVoltageFlag2 = (STM_GetFaultState(oSTM[1])>>16);
    OverVoltageFlag2 &= MC_OVER_VOLT;  
    
#if (ON_OVER_VOLTAGE2 == TURN_ON_LOW_SIDES)
    OverVoltFlagOccurred2 = (uint16_t)(STM_GetFaultState(oSTM[1]));
    OverVoltFlagOccurred2 &= MC_OVER_VOLT;     
    if ((OverVoltageFlag2 != MC_OVER_VOLT) && (OverVoltFlagOccurred2!= MC_OVER_VOLT))
#endif   
      
    {     
      switch (STM_GetState(oSTM[1]))
      {
      case FAULT_NOW:   
        PWMC_SwitchOffPWM(oCurrSensor[1]);
        break;
      case FAULT_OVER:
        PWMC_SwitchOffPWM(oCurrSensor[1]);
        break;
      default:
        break;    
      }
    }
    
#if (ON_OVER_VOLTAGE2 == TURN_ON_LOW_SIDES)    
    if((PrevOverVoltFlagOccurred2 == MC_OVER_VOLT) && (OverVoltFlagOccurred2 != MC_OVER_VOLT))
    {
#if (HW_OV_CURRENT_PROT_BYPASS2 == ENABLE)
      DOUT_SetOutputState(oOCPDisabling[1], INACTIVE);
#endif        
      PWMC_SwitchOffPWM(oCurrSensor[1]);  
    }
    PrevOverVoltFlagOccurred2 = OverVoltFlagOccurred2;    
#endif
    
    CodeReturn2 = TSNS_CalcAvTemp(oTemperatureSensor[1]);
    CodeReturn2 |= PWMC_CheckOverCurrent(oCurrSensor[1]);
    OverVoltageFlag2 = VBS_CalcAvVbus(oBusSensor[1]); 
    
#if (ON_OVER_VOLTAGE2 == TURN_ON_R_BRAKE) 
    if (OverVoltageFlag2 == MC_OVER_VOLT)
    {
      DOUT_SetOutputState(oR_Brake[1], ACTIVE); 
    }
    else
    {
      DOUT_SetOutputState(oR_Brake[1], INACTIVE);   
    }
#elif (ON_OVER_VOLTAGE2 == TURN_ON_LOW_SIDES)
 
    if (OverVoltageFlag2 == MC_OVER_VOLT)
    {
      if(PrevOverVoltageFlag2 != MC_OVER_VOLT)
      {
        PWMC_SwitchOffPWM(oCurrSensor[1]);
      }
#if (HW_OV_CURRENT_PROT_BYPASS2 == ENABLE)
      DOUT_SetOutputState(oOCPDisabling[1], ACTIVE);
#endif        
      PWMC_TurnOnLowSides(oCurrSensor[1]); 
    }  
    PrevOverVoltageFlag2 = OverVoltageFlag2; 
    CodeReturn2 |= OverVoltageFlag2;
#else /* TURN_OFF_PWM  */
    CodeReturn2 |= OverVoltageFlag2;
#endif  
    
    STM_FaultProcessing(oSTM[1], CodeReturn2, ~CodeReturn2);
  }
#endif
}

/**
* @brief  It counts delaies utileized in low frequency tasks. Accuracy of time 
*         counting is given by LF_TASK_OCCURENCE_TICKS
* @param  None
* @retval void
*/
void TSK_LowFrequencyClock(void)
{
  if(bBootCapDelayCounterM1 > 0u)
  {
    bBootCapDelayCounterM1--;    
  } 
  if(hStopPermanencyCounterM1 > 0u)
  {
    hStopPermanencyCounterM1--;    
  }
#ifdef DUALDRIVE
  if(bBootCapDelayCounterM2 > 0u)
  {
    bBootCapDelayCounterM2--;    
  }
  if(hStopPermanencyCounterM2 > 0u)
  {
    hStopPermanencyCounterM2--;    
  }
#endif  
}

/**
  * @brief  It set a counter intended to be used for counting the delay required 
  *         for drivers boot capacitors charging of motor 1
  * @param  LowFrequencyTickCount number of Low frequency clock ticks to be counted
  * @retval void
  */
void TSK_SetChargeBootCapDelayM1(uint8_t LowFrequencyTickCount)
{
   bBootCapDelayCounterM1 = LowFrequencyTickCount; 
   bHasBootCapCountingStartedM1 = TRUE;
}

/**
  * @brief  It set a counter intended to be used for counting the delay required 
  *         for drivers boot capacitors charging of motor 2
  * @param  LowFrequencyTickCount number of Low frequency clock ticks to be counted
  * @retval void
  */
void TSK_SetChargeBootCapDelayM2(uint8_t LowFrequencyTickCount)
{
   bBootCapDelayCounterM2 = LowFrequencyTickCount; 
   bHasBootCapCountingStartedM2 = TRUE;   
}

/**
  * @brief  Use this function to know whether the time required to charge boot 
  *         capacitors of motor 1 has elapsed
  * @param  none
  * @retval bool TRUE if time has elapsed, FALSE otherwise
  */
bool TSK_ChargeBootCapDelayHasElapsedM1(void)
{
  bool retVal = FALSE;
  if (bBootCapDelayCounterM1 == 0)
  {
    retVal = TRUE;
    bHasBootCapCountingStartedM1 = FALSE;
  }
  return (retVal);
}

/**
  * @brief  Use this function to know whether the time required to charge boot 
  *         capacitors of motor 2 has elapsed
  * @param  none
  * @retval bool TRUE if time has elapsed, FALSE otherwise
  */
bool TSK_ChargeBootCapDelayHasElapsedM2(void)
{
  bool retVal = FALSE;
  if (bBootCapDelayCounterM2 == 0)
  {
    retVal = TRUE;
    bHasBootCapCountingStartedM2 = FALSE;
  }
  return (retVal);
}

/**
  * @brief  Use this function to know whether the timespan required to charge boot 
  *         capacitors for Motor 1 has started
  * @param  none
  * @retval bool TRUE if counting has started, FALSE otherwise
  */
bool TSK_ChargeBootCapDelayHasStartedM1(void)
{
return(bHasBootCapCountingStartedM1);
}

/**
  * @brief  Use this function to know whether the timespan required to charge boot 
  *         capacitors for Motor 2has started
  * @param  none
  * @retval bool TRUE if counting has started, FALSE otherwise
  */
bool TSK_ChargeBootCapDelayHasStartedM2(void)
{
return(bHasBootCapCountingStartedM2);
}

/**
  * @brief  It set a counter intended to be used for counting the permanency 
  *         time in STOP state of motor 1
  * @param  SysTickCount number of System ticks to be counted
  * @retval void
  */
void TSK_SetStopPermanencyTimeM1(uint16_t SysTickCount)
{
  hStopPermanencyCounterM1 = SysTickCount;  
}

/**
  * @brief  It set a counter intended to be used for counting the permanency 
  *         time in STOP state of motor 2
  * @param  SysTickCount number of System ticks to be counted
  * @retval void
  */
void TSK_SetStopPermanencyTimeM2(uint16_t SysTickCount)
{
  hStopPermanencyCounterM2 = SysTickCount;  
}

/**
  * @brief  Use this function to know whether the permanency time in STOP state 
  *         of motor 1 has elapsed
  * @param  none
  * @retval bool TRUE if time is elapsed, FALSE otherwise
  */
bool TSK_StopPermanencyTimeHasElapsedM1(void)
{
  bool retVal = FALSE;
  if (hStopPermanencyCounterM1 == 0)
  {
    retVal = TRUE;
  }
  return (retVal);
}

/**
  * @brief  Use this function to know whether the permanency time in STOP state 
  *         of motor 2 has elapsed
  * @param  none
  * @retval bool TRUE if time is elapsed, FALSE otherwise
  */
bool TSK_StopPermanencyTimeHasElapsedM2(void)
{
  bool retVal = FALSE;
  if (hStopPermanencyCounterM2 == 0)
  {
    retVal = TRUE;
  }
  return (retVal);
}

#ifdef DUALDRIVE
/**
  * @brief  This function is called by TIMx_UP_IRQHandler in case of dual MC and
  *         it allows to reserve half PWM period in advance the FOC execution on
  *         ADC ISR
  * @param  oDrive pointer to a CFOC object
  * @retval None
  */
void TSK_DualDriveFIFOUpdate(void *oDrive)
{
  FOC_array[FOC_array_tail] = oDrive;
  FOC_array_tail++;
  if (FOC_array_tail == FOC_ARRAY_LENGHT)
  {
    FOC_array_tail = 0;
  }
}
#endif

/**
  * @brief  This function must be called after MCboot and returns all the 
  *         instances of MCInterface.
  * @param  oMCIList pointer to the vector of MCInterface objects previously 
  *         instantiated by MCboot function. The vector must have length equal 
  *         to the number of motor drives.
  * @retval None.
  */
void GetMCIList(CMCI oMCIList[])
{
  oMCIList[0] = oMCInterface[0];
  
#ifdef DUALDRIVE
  oMCIList[1] = oMCInterface[1];
#endif
}

/**
  * @brief  This function must be called after MCboot and returns all the 
  *         instances of MCTuning.
  * @param  oMCTList pointer to the vector of MCTuning objects previously 
  *         instantiated by MCboot function. The vector must have length equal 
  *         to the number of motor drives.
  * @retval None.
  */
void GetMCTList(CMCT oMCTList[])
{
  oMCTList[0] = oMCTuning[0];
  
#ifdef DUALDRIVE
  oMCTList[1] = oMCTuning[1];
#endif
}

/******************* (C) COPYRIGHT 2011 STMicroelectronics *****END OF FILE****/
