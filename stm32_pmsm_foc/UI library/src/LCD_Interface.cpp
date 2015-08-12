/**
  ******************************************************************************
  * @file    LCD_Interface.cpp
  * @author  IMS Systems Lab and Technical Marketing - MC Team
  * @version 3.0
  * @date    05-Apr-2011 11:34
  * @brief   Implementation of LCD interface
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
#include "LCD_Interface.h"
#include "STMFC.h"
#include "UIExportedFunctions.h"
#include "Parameters conversion.h"
#include "Drive parameters.h"
#include "images.h"

/******************************************************************************/
/* Check-up of the configuration validity*/

#if (defined(STM32PERFORMANCELD) || defined(STM32VALUELD))
#error "Invalid configuration: MCU definition in Control stage parameters.h, LD devices not compatible with LCD manager"
#endif

#if (defined(STM32PERFORMANCEMD) && !defined(STM32F10X_MD))
#error "Invalid configuration: MCU definition in Control stage parameters.h not compatible with selected board"
#endif

#if (defined(STM32VALUEMD) && !defined(STM32F10X_MD_VL))
#error "Invalid configuration: MCU definition in Control stage parameters.h not compatible with selected board"
#endif

#if (defined(STM32PERFORMANCEHD) && !defined(STM32F10X_HD))
#error "Invalid configuration: MCU definition in Control stage parameters.h not compatible with selected board"
#endif

#if (defined(DUALDRIVE) && !defined(STM32F10X_HD))
#error "Invalid configuration: DUALDRIVE definition in Drive parameters.h is not supported by selected MCU"
#endif

#if (defined(STM32VALUE) && !defined(CPU_CLK_24_MHZ))
#error "Invalid configuration: MCU frequency definition in Control stage parameters.h not compatible with selected MCU"
#endif
/******************************************************************************/

/*******************************************************************************
 *****************Edit here the LCD_Interface Configuration*********************
 ******************************************************************************/

#if ((!defined(SINGLEDRIVE)) && (!defined(DUALDRIVE)))
#error "Invalid configuration!"
#endif
#if defined(SINGLEDRIVE)
  #define LCD_UI_SINGLE
#endif
#if defined(DUALDRIVE)
  #define LCD_UI_DUAL
#endif

/* Comment to disable the Start/Stop function with the Key button */
#define ENABLE_START_STOP_BUTTON

#define LCDMANAGER_VERS "LCD manager ver: 1.0"
const char s_LCDfwVer[32] = LCDMANAGER_VERS;

/*********Do not modify beyond this line **************************************/

#ifdef LCD_UI_SINGLE
  #define MC_NBR 1
#endif
#ifdef LCD_UI_DUAL
  #define MC_NBR 2
  #include "string.h"
#endif

#include "math.h"

#define LightGrey 0xC618

#define GUI_SPEED_MODE 0
#define GUI_TORQUE_MODE 1

#define M1 0
#define M2 1

#ifdef LCD_UI_DUAL
char buff[17] = "";
const char *gs_fwVer;
#endif

/*** Private function prototypes ***/
void LCDI_ShowPage1(void);
void LCDI_ShowPage2(void);
void LCDI_ShowPage3(void);
void LCDI_ShowPage4(void);
void LCDI_ShowPage5(void);
void LCDI_ShowPage6(void);
void LCDI_ShowPage7(void);
void LCDI_CreateCommon(void);
void LCDI_ReleaseAllCtrl(void);
void OnIntText_ChangeValue(HANDLE_WIN hWin, uint32_t wParam);
#ifdef LCD_UI_DUAL
void LCDI_SetStatusLabel(void);
void OnGUI_MotorSel_ChangeValue(HANDLE_WIN hWin, uint32_t wParam);
#endif
void OnGUI_Currents_Input_ChangeValue(HANDLE_WIN hWin, uint32_t wParam);

void OnMainFrm_ChangePage(HANDLE_WIN hWin, uint32_t wParam);

void OnGUI_CtrlMode_ChangeText(HANDLE_WIN hWin, uint32_t wParam);
void OnGUI_DAC_Chx_ChangeText(HANDLE_WIN hWin, uint32_t wParam);
void OnGUI_IqIdPIDGainsLink(HANDLE_WIN hWin, uint32_t wParam);

void OnGUI_IqKP_ChangeValue(HANDLE_WIN hWin, uint32_t wParam);
void OnGUI_IqKI_ChangeValue(HANDLE_WIN hWin, uint32_t wParam);
void OnGUI_IqKD_ChangeValue(HANDLE_WIN hWin, uint32_t wParam);
void OnGUI_Iq_Ref_ChangeValue(HANDLE_WIN hWin, uint32_t wParam);
void OnGUI_Id_Ref_ChangeValue(HANDLE_WIN hWin, uint32_t wParam);
void OnGUI_RUC_Stage_ChangeValue(HANDLE_WIN hWin, uint32_t wParam);
void OnGUI_RUC_Duration_ChangeValue(HANDLE_WIN hWin, uint32_t wParam);
void OnGUI_RUC_FinalSpeed_ChangeValue(HANDLE_WIN hWin, uint32_t wParam);
void OnGUI_RUC_FinalToruqe_ChangeValue(HANDLE_WIN hWin, uint32_t wParam);

void OnGUI_FaultAck_Click(HANDLE_WIN hWin, uint32_t wParam);
void OnGUI_SpeedRampExec_Click(HANDLE_WIN hWin, uint32_t wParam);
void OnGUI_EncoderAlign_Click(HANDLE_WIN hWin, uint32_t wParam);
void OnGUI_StartStop_Click(HANDLE_WIN hWin, uint32_t wParam);
#ifdef LCD_UI_DUAL
void OnGUI_FaultAck_M1_Click(HANDLE_WIN hWin, uint32_t wParam);
void OnGUI_FaultAck_M2_Click(HANDLE_WIN hWin, uint32_t wParam);
void OnGUI_SpeedRampExec_M1_Click(HANDLE_WIN hWin, uint32_t wParam);
void OnGUI_SpeedRampExec_M2_Click(HANDLE_WIN hWin, uint32_t wParam);
void OnGUI_StartStop_M1_Click(HANDLE_WIN hWin, uint32_t wParam);
void OnGUI_StartStop_M2_Click(HANDLE_WIN hWin, uint32_t wParam);
void OnGUI_StartBoth_Click(HANDLE_WIN hWin, uint32_t wParam);
void OnGUI_ExecBothRamp_Click(HANDLE_WIN hWin, uint32_t wParam);
void OnGUI_Iq_Ref_ChangeValue_M1(HANDLE_WIN hWin, uint32_t wParam);
void OnGUI_Id_Ref_ChangeValue_M1(HANDLE_WIN hWin, uint32_t wParam);
void OnGUI_Iq_Ref_ChangeValue_M2(HANDLE_WIN hWin, uint32_t wParam);
void OnGUI_Id_Ref_ChangeValue_M2(HANDLE_WIN hWin, uint32_t wParam);
#endif

void LCDI_UpdateCurrentRefLabels(void);
void LCDI_UpdateCurrentRefData(void);
void LCDI_UpdateSelectedMC(CUI oUI, uint8_t bSel);
void LCDI_UpdateSelectedRUCData(CUI oUI, uint8_t bSel, uint8_t bStage);
void LCDI_GetSelectedRUCData(CUI oUI, uint8_t bSel, uint8_t bStage);

uint8_t FindStr(const char* str);

/*Graphics components initialization*/
CSTMWinMainForm MainFrm("", CRect(0,0,320,240), White, Blue, &Font8x12_Ex);
CSTMWinPage Page1(&MainFrm.m_WorkArea);
CSTMWinPage Page2(&MainFrm.m_WorkArea);
#ifdef LCD_UI_DUAL
CSTMWinPage Page3(&MainFrm.m_WorkArea);
#endif
CSTMWinPage Page4(&MainFrm.m_WorkArea);
CSTMWinPage Page5(&MainFrm.m_WorkArea);
CSTMWinPage Page6(&MainFrm.m_WorkArea);
CSTMWinPage Page7(&MainFrm.m_WorkArea);

// Configuration and debug page
#ifdef LCD_UI_DUAL
const char* const GUI_MotorSelTxt[] = {
  "1", 
  "2",
  NULL};
CSTMCombo* pGUI_MotorSel;
#endif
const char * const GUI_CtrlModeTxt[] = {
  "Speed ", 
  "Torque", 
  NULL};

CSTMCombo* pGUI_CtrlMode;

const char * const GUI_DAC_ChTxt_SL[] = {
  "Ia               ","Ib               ",
  "Ialpha           ","Ibeta            ","Iq               ",
  "Id               ","Iq ref           ","Id ref           ",
  "Vq               ","Vd               ","Valpha           ",
  "Vbeta            ",
  "Obs. El Angle    ","Obs. Rotor Speed ","Obs. Ialpha      ",
  "Obs. Ibeta       ","Obs. B-emf alpha ","Obs. B-emf beta  ",
  "Exp. B-emf level ","Obs. B-emf level ",
  "User 1           ","User 2           ", NULL};

const MC_Protocol_REG_t GUI_DAC_ChID_SLPLL[] = {
  MC_PROTOCOL_REG_I_A,
  MC_PROTOCOL_REG_I_B,
  MC_PROTOCOL_REG_I_ALPHA,
  MC_PROTOCOL_REG_I_BETA,
  MC_PROTOCOL_REG_I_Q,
  MC_PROTOCOL_REG_I_D,
  MC_PROTOCOL_REG_I_Q_REF,
  MC_PROTOCOL_REG_I_D_REF,
  MC_PROTOCOL_REG_V_Q,
  MC_PROTOCOL_REG_V_D,
  MC_PROTOCOL_REG_V_ALPHA,
  MC_PROTOCOL_REG_V_BETA,
  MC_PROTOCOL_REG_OBS_EL_ANGLE,
  MC_PROTOCOL_REG_OBS_ROT_SPEED,
  MC_PROTOCOL_REG_OBS_I_ALPHA,
  MC_PROTOCOL_REG_OBS_I_BETA,
  MC_PROTOCOL_REG_OBS_BEMF_ALPHA,
  MC_PROTOCOL_REG_OBS_BEMF_BETA,
  MC_PROTOCOL_REG_EST_BEMF_LEVEL,
  MC_PROTOCOL_REG_OBS_BEMF_LEVEL,
  MC_PROTOCOL_REG_DAC_USER1,
  MC_PROTOCOL_REG_DAC_USER2
};

const MC_Protocol_REG_t GUI_DAC_ChID_SLCR[] = {
  MC_PROTOCOL_REG_I_A,
  MC_PROTOCOL_REG_I_B,
  MC_PROTOCOL_REG_I_ALPHA,
  MC_PROTOCOL_REG_I_BETA,
  MC_PROTOCOL_REG_I_Q,
  MC_PROTOCOL_REG_I_D,
  MC_PROTOCOL_REG_I_Q_REF,
  MC_PROTOCOL_REG_I_D_REF,
  MC_PROTOCOL_REG_V_Q,
  MC_PROTOCOL_REG_V_D,
  MC_PROTOCOL_REG_V_ALPHA,
  MC_PROTOCOL_REG_V_BETA,
  MC_PROTOCOL_REG_OBS_CR_EL_ANGLE,
  MC_PROTOCOL_REG_OBS_CR_ROT_SPEED,
  MC_PROTOCOL_REG_OBS_CR_I_ALPHA,
  MC_PROTOCOL_REG_OBS_CR_I_BETA,
  MC_PROTOCOL_REG_OBS_CR_BEMF_ALPHA,
  MC_PROTOCOL_REG_OBS_CR_BEMF_BETA,
  MC_PROTOCOL_REG_EST_CR_BEMF_LEVEL,
  MC_PROTOCOL_REG_OBS_CR_BEMF_LEVEL,
  MC_PROTOCOL_REG_DAC_USER1,
  MC_PROTOCOL_REG_DAC_USER2
};

const char * const GUI_DAC_ChTxt_SL_SL[] = {
  "Ia               ","Ib               ",
  "Ialpha           ","Ibeta            ","Iq               ",
  "Id               ","Iq ref           ","Id ref           ",
  "Vq               ","Vd               ","Valpha           ",
  "Vbeta            ",
  "Obs. El Ang.(PLL)","Obs. Rot.Spd(PLL)","Obs. Ialpha (PLL)",
  "Obs. Ibeta  (PLL)","Obs. Bemf a.(PLL)","Obs. Bemf b.(PLL)",
  "Exp. Bemf l.(PLL)","Obs. Bemf l.(PLL)",
  "Obs. El Ang. (CR)","Obs. Rot.Spd (CR)","Obs. Ialpha  (CR)",
  "Obs. Ibeta   (CR)","Obs. Bemf a. (CR)","Obs. Bemf b. (CR)",
  "Exp. Bemf l. (CR)","Obs. Bemf l. (CR)",
  "User 1           ","User 2           ", NULL};

const MC_Protocol_REG_t GUI_DAC_ChID_SL_SL[] = {
  MC_PROTOCOL_REG_I_A,
  MC_PROTOCOL_REG_I_B,
  MC_PROTOCOL_REG_I_ALPHA,
  MC_PROTOCOL_REG_I_BETA,
  MC_PROTOCOL_REG_I_Q,
  MC_PROTOCOL_REG_I_D,
  MC_PROTOCOL_REG_I_Q_REF,
  MC_PROTOCOL_REG_I_D_REF,
  MC_PROTOCOL_REG_V_Q,
  MC_PROTOCOL_REG_V_D,
  MC_PROTOCOL_REG_V_ALPHA,
  MC_PROTOCOL_REG_V_BETA,
  MC_PROTOCOL_REG_OBS_EL_ANGLE,
  MC_PROTOCOL_REG_OBS_ROT_SPEED,
  MC_PROTOCOL_REG_OBS_I_ALPHA,
  MC_PROTOCOL_REG_OBS_I_BETA,
  MC_PROTOCOL_REG_OBS_BEMF_ALPHA,
  MC_PROTOCOL_REG_OBS_BEMF_BETA,
  MC_PROTOCOL_REG_EST_BEMF_LEVEL,
  MC_PROTOCOL_REG_OBS_BEMF_LEVEL,
  MC_PROTOCOL_REG_OBS_CR_EL_ANGLE,
  MC_PROTOCOL_REG_OBS_CR_ROT_SPEED,
  MC_PROTOCOL_REG_OBS_CR_I_ALPHA,
  MC_PROTOCOL_REG_OBS_CR_I_BETA,
  MC_PROTOCOL_REG_OBS_CR_BEMF_ALPHA,
  MC_PROTOCOL_REG_OBS_CR_BEMF_BETA,
  MC_PROTOCOL_REG_EST_CR_BEMF_LEVEL,
  MC_PROTOCOL_REG_OBS_CR_BEMF_LEVEL,
  MC_PROTOCOL_REG_DAC_USER1,
  MC_PROTOCOL_REG_DAC_USER2
};

const char * const GUI_DAC_ChTxt_SR[] = {
  "Ia               ","Ib               ",
  "Ialpha           ","Ibeta            ","Iq               ",
  "Id               ","Iq ref           ","Id ref           ",
  "Vq               ","Vd               ","Valpha           ",
  "Vbeta            ","Meas. El Angle   ","Meas. Rotor Speed",
  "User 1           ","User 2           ", NULL};

const MC_Protocol_REG_t GUI_DAC_ChID_SR[] = {
  MC_PROTOCOL_REG_I_A,
  MC_PROTOCOL_REG_I_B,
  MC_PROTOCOL_REG_I_ALPHA,
  MC_PROTOCOL_REG_I_BETA,
  MC_PROTOCOL_REG_I_Q,
  MC_PROTOCOL_REG_I_D,
  MC_PROTOCOL_REG_I_Q_REF,
  MC_PROTOCOL_REG_I_D_REF,
  MC_PROTOCOL_REG_V_Q,
  MC_PROTOCOL_REG_V_D,
  MC_PROTOCOL_REG_V_ALPHA,
  MC_PROTOCOL_REG_V_BETA,
  MC_PROTOCOL_REG_MEAS_EL_ANGLE,
  MC_PROTOCOL_REG_MEAS_ROT_SPEED,
  MC_PROTOCOL_REG_DAC_USER1,
  MC_PROTOCOL_REG_DAC_USER2
};

const char * const GUI_DAC_ChTxt_SL_SR[] = {
  "Ia               ","Ib               ",
  "Ialpha           ","Ibeta            ","Iq               ",
  "Id               ","Iq ref           ","Id ref           ",
  "Vq               ","Vd               ","Valpha           ",
  "Vbeta            ","Meas. El Angle   ","Meas. Rotor Speed",
  "Obs. El Angle    ","Obs. Rotor Speed ","Obs. Ialpha      ",
  "Obs. Ibeta       ","Obs. B-emf alpha ","Obs. B-emf beta  ",
  "Exp. B-emf level ","Obs. B-emf level ",
  "User 1           ","User 2           ", NULL};

const MC_Protocol_REG_t GUI_DAC_ChID_SLPLL_SR[] = {
  MC_PROTOCOL_REG_I_A,
  MC_PROTOCOL_REG_I_B,
  MC_PROTOCOL_REG_I_ALPHA,
  MC_PROTOCOL_REG_I_BETA,
  MC_PROTOCOL_REG_I_Q,
  MC_PROTOCOL_REG_I_D,
  MC_PROTOCOL_REG_I_Q_REF,
  MC_PROTOCOL_REG_I_D_REF,
  MC_PROTOCOL_REG_V_Q,
  MC_PROTOCOL_REG_V_D,
  MC_PROTOCOL_REG_V_ALPHA,
  MC_PROTOCOL_REG_V_BETA,
  MC_PROTOCOL_REG_MEAS_EL_ANGLE,
  MC_PROTOCOL_REG_MEAS_ROT_SPEED,
  MC_PROTOCOL_REG_OBS_EL_ANGLE,
  MC_PROTOCOL_REG_OBS_ROT_SPEED,
  MC_PROTOCOL_REG_OBS_I_ALPHA,
  MC_PROTOCOL_REG_OBS_I_BETA,
  MC_PROTOCOL_REG_OBS_BEMF_ALPHA,
  MC_PROTOCOL_REG_OBS_BEMF_BETA,
  MC_PROTOCOL_REG_EST_BEMF_LEVEL,
  MC_PROTOCOL_REG_OBS_BEMF_LEVEL,
  MC_PROTOCOL_REG_DAC_USER1,
  MC_PROTOCOL_REG_DAC_USER2
};

const MC_Protocol_REG_t GUI_DAC_ChID_SLCR_SR[] = {
  MC_PROTOCOL_REG_I_A,
  MC_PROTOCOL_REG_I_B,
  MC_PROTOCOL_REG_I_ALPHA,
  MC_PROTOCOL_REG_I_BETA,
  MC_PROTOCOL_REG_I_Q,
  MC_PROTOCOL_REG_I_D,
  MC_PROTOCOL_REG_I_Q_REF,
  MC_PROTOCOL_REG_I_D_REF,
  MC_PROTOCOL_REG_V_Q,
  MC_PROTOCOL_REG_V_D,
  MC_PROTOCOL_REG_V_ALPHA,
  MC_PROTOCOL_REG_V_BETA,
  MC_PROTOCOL_REG_MEAS_EL_ANGLE,
  MC_PROTOCOL_REG_MEAS_ROT_SPEED,
  MC_PROTOCOL_REG_OBS_CR_EL_ANGLE,
  MC_PROTOCOL_REG_OBS_CR_ROT_SPEED,
  MC_PROTOCOL_REG_OBS_CR_I_ALPHA,
  MC_PROTOCOL_REG_OBS_CR_I_BETA,
  MC_PROTOCOL_REG_OBS_CR_BEMF_ALPHA,
  MC_PROTOCOL_REG_OBS_CR_BEMF_BETA,
  MC_PROTOCOL_REG_EST_CR_BEMF_LEVEL,
  MC_PROTOCOL_REG_OBS_CR_BEMF_LEVEL,
  MC_PROTOCOL_REG_DAC_USER1,
  MC_PROTOCOL_REG_DAC_USER2
};

/* These configuration are related with the GUI_DAC_ChTxt and GUI_DAC_ChID arrays.
   It is used by LCDI_GetDACConfig function in order to proper set the DAC text and variables.*/
typedef enum 
{
  GUI_DAC_CFG_Invalid,
  GUI_DAC_CFG_SLPLL,
  GUI_DAC_CFG_SLCR,
  GUI_DAC_CFG_SR,
  GUI_DAC_CFG_SLPLL_SR,
  GUI_DAC_CFG_SLCR_SR,
  GUI_DAC_CFG_SL_SL
} DAC_Config_t, *PDAC_Config_t;

DAC_Config_t LCDI_GetDACConfig(CUI oUI);

const char * const * const GUI_DAC_ChTxt[] =
{
  NULL,
  GUI_DAC_ChTxt_SL,
  GUI_DAC_ChTxt_SL,
  GUI_DAC_ChTxt_SR,
  GUI_DAC_ChTxt_SL_SR,
  GUI_DAC_ChTxt_SL_SR,
  GUI_DAC_ChTxt_SL_SL
};

const MC_Protocol_REG_t * const GUI_DAC_ChID[]=
{
  NULL,
  GUI_DAC_ChID_SLPLL,
  GUI_DAC_ChID_SLCR,
  GUI_DAC_ChID_SR,
  GUI_DAC_ChID_SLPLL_SR,
  GUI_DAC_ChID_SLCR_SR,
  GUI_DAC_ChID_SL_SL
};

CSTMCombo* pGUI_DAC_Ch1;
CSTMCombo* pGUI_DAC_Ch2;

CSTMEditInt* pGUI_DC_BUS;
CSTMEditInt* pGUI_Temp;

CSTMLabel* pGUI_Overcurrent;
CSTMLabel* pGUI_RevupFail;
CSTMLabel* pGUI_SpeedFdbk;
CSTMLabel* pGUI_SW_Error;
CSTMLabel* pGUI_UnderVolt;
CSTMLabel* pGUI_OverVolt;
CSTMLabel* pGUI_OverTemp;
CSTMButton* pGUI_FaultAck;

#ifdef LCD_UI_DUAL
// Dual control panel
CSTMEditInt32* pGUI_SpeedTarget_M1;
CSTMEditInt* pGUI_Iq_Ref_M1;
CSTMEditInt32* pGUI_SpeedMeasured_M1;
CSTMEditInt* pGUI_SpeedRampDuration_M1;
CSTMEditInt* pGUI_Id_Ref_M1;
CSTMButton* pGUI_SpeedRampExec_M1;
CSTMEditInt32* pGUI_SpeedTarget_M2;
CSTMEditInt* pGUI_Iq_Ref_M2;
CSTMEditInt32* pGUI_SpeedMeasured_M2;
CSTMEditInt* pGUI_SpeedRampDuration_M2;
CSTMEditInt* pGUI_Id_Ref_M2;
CSTMButton* pGUI_SpeedRampExec_M2;
CSTMButton* pGUI_StartStop_M1;
CSTMButton* pGUI_FaultAck_M1;
CSTMButton* pGUI_StartStop_M2;
CSTMButton* pGUI_FaultAck_M2;
CSTMButton* pGUI_StartBoth;
CSTMButton* pGUI_ExecBothRamp;
#endif

// Speed controller
CSTMEditInt32* pGUI_SpeedTarget;
CSTMEditInt* pGUI_SpeedRampDuration;
CSTMButton* pGUI_SpeedRampExec;
// Monitor
CSTMEditInt* pGUI_SpeedKP;
CSTMEditInt* pGUI_SpeedKI;
CSTMEditInt* pGUI_SpeedKD;
CSTMEditInt* pGUI_FW_BUSTarget;
CSTMEditInt* pGUI_FW_BUSMeasured;
CSTMEditInt* pGUI_FW_KP;
CSTMEditInt* pGUI_FW_KI;

// Current controllers
CSTMLabel* pLabel2_5;
CSTMEditInt* pGUI_Iq_Ref;
CSTMEditInt* pGUI_Iq_Meas;
CSTMLabel* pLabel4_5;
CSTMEditInt* pGUI_Id_Ref;
CSTMEditInt* pGUI_Id_Meas;
CSTMEditInt* pGUI_IqKP;
CSTMEditInt* pGUI_IqKI;
CSTMLabel* pLabel10_5;
CSTMEditInt* pGUI_IqKD;
CSTMEditInt* pGUI_IdKP;
CSTMEditInt* pGUI_IdKI;
CSTMLabel* pLabel13_5;
CSTMEditInt* pGUI_IdKD;
CSTMCheckBox* pGUI_IqIdPIDGainsLink;
const char * const GUI_Currents_InputTxt[] = {
  "Iq/Id", 
  "Am/Ep", 
  NULL};
CSTMCombo* pGUI_Currents_Input;

// Sensorless tuning
CSTMEditInt* pGUI_STO_C1;
CSTMEditInt* pGUI_STO_C2;
CSTMEditInt* pGUI_STO_PLL_KP;
CSTMEditInt* pGUI_STO_PLL_KI;
CSTMEditInt* pGUI_RUC_Duration;
CSTMEditInt* pGUI_RUC_FinalSpeed;
CSTMEditInt* pGUI_RUC_FinalToruqe;
CSTMEditInt* pGUI_RUC_Stage;

// Encoder tuning
CSTMButton*	pGUI_EncoderAlign;

// Commons
CSTMGroup* pGUI_SpeedMonitor;
CSTMLabel* pLabel6_4;
CSTMEditInt32* pGUI_SpeedMeasured;
CSTMButton* pGUI_StartStop;
CSTMLabel* pLabel7_4;

// UI object
CUI g_oUI,g_oDAC;

// Numeric control
typedef enum {
  GUI_DC_BUS	,
  GUI_Temp	,
  GUI_SpeedRampDuration	,
  GUI_SpeedKP	,
  GUI_SpeedKI	,
  GUI_SpeedKD	,
  GUI_FW_BUSTarget	,
  GUI_FW_BUSMeasured	,
  GUI_FW_KP	,
  GUI_FW_KI	,
  GUI_Iq_Ref	,
  GUI_Iq_Meas	,
  GUI_Id_Ref	,
  GUI_Id_Meas	,
  GUI_IqKP	,
  GUI_IqKI	,
  GUI_IqKD	,
  GUI_IdKP	,
  GUI_IdKI	,
  GUI_IdKD	,
  GUI_STO_C1	,
  GUI_STO_C2	,
  GUI_STO_CR_C1	,
  GUI_STO_CR_C2	,
  GUI_STO_PLL_KP	,
  GUI_STO_PLL_KI	,
  GUI_RUC_Duration	,
  GUI_RUC_FinalSpeed	,
  GUI_RUC_FinalToruqe	,
  GUI_RUC_Stage ,
  GUI_I_Ref ,
  GUI_Eps_Ref ,
  NUMERIC_DATA_ELEMENT
} GUI_Values_t;

typedef enum {
  GUI_CtrlMode	,
  GUI_DAC_Ch1	,
  GUI_DAC_Ch2	,
  GUI_Currents_Input	,
  GUI_IqIdPIDGainsLink	,
  GUI_Overcurrent	,
  GUI_RevupFail	,
  GUI_SpeedFdbk	,
  GUI_SW_Error	,
  GUI_UnderVolt	,
  GUI_OverVolt	,
  GUI_OverTemp	,
  NUMERIC_DATA_ELEMENT_U8
} GUI_Values8_t;

typedef enum {
  GUI_SpeedTarget	,
  GUI_SpeedMeasured	,
  NUMERIC_DATA_ELEMENT_S32
} GUI_Values32_t;

int32_t NumericData32[MC_NBR][NUMERIC_DATA_ELEMENT_S32];
int16_t NumericData[MC_NBR][NUMERIC_DATA_ELEMENT];
uint8_t NumericDataU8[MC_NBR][NUMERIC_DATA_ELEMENT_U8];
uint8_t MotorSel = 0;

#define MEASURED_VALUES_NUM 5
const GUI_Values_t MeasuredValues[] = {
  GUI_DC_BUS,
  GUI_Temp,
  GUI_FW_BUSMeasured,
  GUI_Iq_Meas,
  GUI_Id_Meas
};

#define MEASURED_VALUES32_NUM 1
const GUI_Values32_t MeasuredValues32[] = {
  GUI_SpeedMeasured,
};

const MC_Protocol_REG_t ID_Code32[] = {
  MC_PROTOCOL_REG_UNDEFINED	,
  MC_PROTOCOL_REG_SPEED_MEAS  
};

const MC_Protocol_REG_t ID_Code[] = {
  MC_PROTOCOL_REG_BUS_VOLTAGE	,
  MC_PROTOCOL_REG_HEATS_TEMP	,
  MC_PROTOCOL_REG_UNDEFINED	,
  MC_PROTOCOL_REG_SPEED_KP	,
  MC_PROTOCOL_REG_SPEED_KI	,
  MC_PROTOCOL_REG_SPEED_KD	,
  MC_PROTOCOL_REG_FLUXWK_BUS	,
  MC_PROTOCOL_REG_FLUXWK_BUS_MEAS	,
  MC_PROTOCOL_REG_FLUXWK_KP	,
  MC_PROTOCOL_REG_FLUXWK_KI	,
  MC_PROTOCOL_REG_TORQUE_REF	,
  MC_PROTOCOL_REG_TORQUE_MEAS	,
  MC_PROTOCOL_REG_FLUX_REF	,
  MC_PROTOCOL_REG_FLUX_MEAS	,
  MC_PROTOCOL_REG_TORQUE_KP	,
  MC_PROTOCOL_REG_TORQUE_KI	,
  MC_PROTOCOL_REG_TORQUE_KD	,
  MC_PROTOCOL_REG_FLUX_KP	,
  MC_PROTOCOL_REG_FLUX_KI	,
  MC_PROTOCOL_REG_FLUX_KD	,
  MC_PROTOCOL_REG_OBSERVER_C1	,
  MC_PROTOCOL_REG_OBSERVER_C2	,
  MC_PROTOCOL_REG_OBSERVER_CR_C1,
  MC_PROTOCOL_REG_OBSERVER_CR_C2,
  MC_PROTOCOL_REG_PLL_KP	,
  MC_PROTOCOL_REG_PLL_KI	,
  MC_PROTOCOL_REG_UNDEFINED	,
  MC_PROTOCOL_REG_UNDEFINED	,
  MC_PROTOCOL_REG_UNDEFINED	,
  MC_PROTOCOL_REG_UNDEFINED	,
  MC_PROTOCOL_REG_UNDEFINED	,
  MC_PROTOCOL_REG_UNDEFINED ,
  MC_PROTOCOL_REG_UNDEFINED
};

enum {
  GUI_NO_FAULT,
  GUI_FAULT_CONDITION,
  GUI_FAULT_OCCURRED
};

const uint16_t GUI_Fault_Color_Code[] = {
LightGrey,  //  GUI_NO_FAULT
Red,        //  GUI_FAULT_CONDITION
Blue        //  GUI_FAULT_OCCURRED
};

void* const* g_ImportedFunctions;

#define pUI_GetReg ((pUI_GetReg_t)(g_ImportedFunctions[EF_UI_GetReg]))
#define pUI_ExecSpeedRamp ((pUI_ExecSpeedRamp_t)(g_ImportedFunctions[EF_UI_ExecSpeedRamp]))
#define pUI_SetReg ((pUI_SetReg_t)(g_ImportedFunctions[EF_UI_SetReg]))
#define pUI_ExecCmd ((pUI_ExecCmd_t)(g_ImportedFunctions[EF_UI_ExecCmd]))
#define pUI_GetSelectedMCConfig ((pUI_GetSelectedMCConfig_t)(g_ImportedFunctions[EF_UI_GetSelectedMCConfig]))
#define pUI_SetRevupData ((pUI_SetRevupData_t)(g_ImportedFunctions[EF_UI_SetRevupData]))
#define pUI_GetRevupData ((pUI_GetRevupData_t)(g_ImportedFunctions[EF_UI_GetRevupData]))
#define pUI_DACChannelConfig ((pUI_DACChannelConfig_t)(g_ImportedFunctions[EF_UI_DACChannelConfig]))
#define pUI_SetCurrentReferences ((pUI_SetCurrentReferences_t)(g_ImportedFunctions[EF_UI_SetCurrentReferences]))

/**
  * @brief  It is used to Get RUC values.
  * @param  oUI related object of class CUI.
  * @param  bSel Selected MC
  * @param  bStage Ruc stage.
  * @retval none.
  */
void LCDI_GetSelectedRUCData(CUI oUI, uint8_t bSel, uint8_t bStage)
{
  (*pUI_GetRevupData)(oUI, bStage, (uint16_t*)&NumericData[bSel][GUI_RUC_Duration],
                               &NumericData[bSel][GUI_RUC_FinalSpeed],
                               &NumericData[bSel][GUI_RUC_FinalToruqe]);
   NumericData[bSel][GUI_RUC_FinalSpeed] *= 6;
}

/**
  * @brief  It is used to Set RUC values.
  * @param  oUI related object of class CUI.
  * @param  bSel Selected MC
  * @param  bStage Ruc stage.
  * @retval none.
  */
void LCDI_SetSelectedRUCData(CUI oUI, uint8_t bSel, uint8_t bStage)
{
  (*pUI_SetRevupData)(oUI, bStage, NumericData[bSel][GUI_RUC_Duration],
                               NumericData[bSel][GUI_RUC_FinalSpeed]/6,
                               NumericData[bSel][GUI_RUC_FinalToruqe]);
}

/**
  * @brief  It is used to update all values of GUI controls.
  * @param  oUI related object of class CUI.
  * @retval none.
  */
void LCDI_UpdateSelectedMC(CUI oUI, uint8_t bSel)
{
  uint8_t i;
  for (i = 0; i < NUMERIC_DATA_ELEMENT; i++)
  {
    if (ID_Code[i] != MC_PROTOCOL_REG_UNDEFINED)
    {
      int32_t val = (*pUI_GetReg)(oUI,ID_Code[i]);
      if (val != GUI_ERROR_CODE)
      {
        NumericData[bSel][i] = (int16_t)val;
      }
    }
  }

  NumericData32[bSel][GUI_SpeedTarget] = (*pUI_GetReg)(oUI,MC_PROTOCOL_REG_SPEED_REF);
  
  LCDI_GetSelectedRUCData(oUI, bSel, NumericData[bSel][GUI_RUC_Stage]);
}

/**
  * @brief  It is used to update all values of GUI controls.
  * @param  oUI related object of class CUI.
  * @retval none.
  */
void LCDI_UpdateAll(CUI oUI)
{
#ifdef LCD_UI_DUAL
  uint8_t bMotorSelTMP = (*pUI_GetReg)(oUI,MC_PROTOCOL_REG_TARGET_MOTOR);
  
  (*pUI_SetReg)(oUI,MC_PROTOCOL_REG_TARGET_MOTOR,M1);
#endif
  
  LCDI_UpdateSelectedMC(oUI,M1);
    
#ifdef LCD_UI_DUAL
  if ((*pUI_SetReg)(oUI,MC_PROTOCOL_REG_TARGET_MOTOR,M2))
  {  
    LCDI_UpdateSelectedMC(oUI,M2);
    (*pUI_SetReg)(oUI,MC_PROTOCOL_REG_TARGET_MOTOR,bMotorSelTMP);
  }
#endif
}

/**
  * @brief  It is used to update and visually refresh only measured quantities.
  * @param  oUI related object of class CUI.
  * @retval none.
  */
void LCDI_UpdateMeasured(CUI oUI)
{
  uint8_t i;
  uint8_t num = MEASURED_VALUES_NUM;
  // Update 16 bit values
  for (i = 0; i < num; i++)
  {
      NumericData[MotorSel][MeasuredValues[i]] = (*pUI_GetReg)(oUI,ID_Code[MeasuredValues[i]]); 
  }
  // Update 32 bit values
  num = MEASURED_VALUES32_NUM;
  for (i = 0; i < num; i++)
  {
      NumericData32[MotorSel][MeasuredValues32[i]] = (*pUI_GetReg)(oUI,ID_Code32[MeasuredValues32[i]]); 
  }
  
  // Update Iqd reference in speed mode
  if (NumericDataU8[MotorSel][GUI_CtrlMode] == GUI_SPEED_MODE)
  {
      NumericData[MotorSel][GUI_Iq_Ref] = (*pUI_GetReg)(oUI,MC_PROTOCOL_REG_TORQUE_REF);
      NumericData[MotorSel][GUI_Id_Ref] = (*pUI_GetReg)(oUI,MC_PROTOCOL_REG_FLUX_REF);
      
      if (NumericDataU8[MotorSel][GUI_Currents_Input] == 1)
      {
        if ((NumericData[MotorSel][GUI_Iq_Ref] == 0) && (NumericData[MotorSel][GUI_Id_Ref] == 0))
        {
          NumericData[MotorSel][GUI_I_Ref] = 0;
          NumericData[MotorSel][GUI_Eps_Ref] = 90;
        }
        else
        {
          NumericData[MotorSel][GUI_I_Ref] = (int16_t)(sqrt((float)(NumericData[MotorSel][GUI_Iq_Ref]*NumericData[MotorSel][GUI_Iq_Ref] +
                                                                    NumericData[MotorSel][GUI_Id_Ref]*NumericData[MotorSel][GUI_Id_Ref])));
          NumericData[MotorSel][GUI_Eps_Ref] = (int16_t)(180 * atan2((float)(NumericData[MotorSel][GUI_Iq_Ref]),(float)(NumericData[MotorSel][GUI_Id_Ref]))/3.14);
        }
      }
      
      if (pGUI_Iq_Ref)
      {
        pGUI_Iq_Ref->RefreshAsync();
      }
      if (pGUI_Id_Ref)
      {
        pGUI_Id_Ref->RefreshAsync();
      }      
  }
  
  // Check fault
  uint32_t Flags = (*pUI_GetReg)(oUI,MC_PROTOCOL_REG_FLAGS);
  uint16_t FaultOccurred  = (uint16_t)(Flags);
  uint16_t FaultCondition = (uint16_t)(Flags >> 16);
  
#ifdef LCD_UI_SINGLE
  /* When a fault occurs and until it is not acknowledged the LCD is brought to
     the fault page.*/
  if ((FaultOccurred)||(FaultCondition))
  {    
    if (MainFrm.GetActivePageNumber() != 1)
    {
      MainFrm.SetActivePage(1);
    }
  }
#endif
  
  if (pGUI_FaultAck)
  {
    if ((FaultOccurred)&&(!FaultCondition))
    {
      pGUI_FaultAck->SetTextColor(Black);
      pGUI_FaultAck->SetFocusable(true);
      
      /* When it is present the focus is brought to the Fault Ack button */
      if (Page2.GetActiveControl() != pGUI_FaultAck)
      {
        Page2.SetActiveControl(0);
      }
              
      pGUI_FaultAck->RefreshAsync();   
    }
    else
    {
      /* Remove the focus on Fault Ack button if it focused */
      if (Page2.GetActiveControl() == pGUI_FaultAck)
      {
        Page2.SetActiveNextControl();
      }
      
      if (pGUI_FaultAck->GetTextColor() != LightGrey)
      {
        pGUI_FaultAck->SetTextColor(LightGrey);
        pGUI_FaultAck->SetFocusable(false);
        pGUI_FaultAck->RefreshAsync();
      }
    }   
  }
  
#ifdef LCD_UI_DUAL
  // Store actual motor
  uint8_t bMotorSelTMP = (*pUI_GetReg)(g_oUI,MC_PROTOCOL_REG_TARGET_MOTOR);
  (*pUI_SetReg)(g_oUI,MC_PROTOCOL_REG_TARGET_MOTOR,M1);
  // Check fault M1
  uint32_t Flags_M1 = (*pUI_GetReg)(oUI,MC_PROTOCOL_REG_FLAGS);
  State_t StateM1 = (State_t)((*pUI_GetReg)(oUI,MC_PROTOCOL_REG_STATUS));
  uint16_t FaultOccurred_M1  = (uint16_t)(Flags_M1);
  uint16_t FaultCondition_M1 = (uint16_t)(Flags_M1 >> 16);
  // Faultack management M1
  if (pGUI_FaultAck_M1)
  {
    if ((FaultOccurred_M1)&&(!FaultCondition_M1))
    {
      pGUI_FaultAck_M1->SetTextColor(Black);
      pGUI_FaultAck_M1->SetFocusable(true);      
      pGUI_FaultAck_M1->RefreshAsync();   
    }
    else
    {
      /* Remove the focus on Fault Ack button if it focused */
      if (Page3.GetActiveControl() == pGUI_FaultAck_M1)
      {
        Page3.SetActiveNextControl();
      }
      if (pGUI_FaultAck_M1->GetTextColor() != LightGrey)
      {
        pGUI_FaultAck_M1->SetTextColor(LightGrey);
        pGUI_FaultAck_M1->SetFocusable(false);
        pGUI_FaultAck_M1->RefreshAsync();
      }
    }   
  }
  // Start/Stop management M1
  if (pGUI_StartStop_M1)
  {
    if ((FaultOccurred_M1)||(FaultCondition_M1))
    {
      /* Remove the focus on Fault Ack button if it focused */
      if (Page3.GetActiveControl() == pGUI_StartStop_M1)
      {
        Page3.SetActiveNextControl();
      }

      if (pGUI_StartStop_M1->GetTextColor() != LightGrey)
      {
        pGUI_StartStop_M1->SetTextColor(LightGrey);
        pGUI_StartStop_M1->SetFocusable(false);      
        pGUI_StartStop_M1->RefreshAsync();   
      }      
    }
    else
    {
      if (pGUI_StartStop_M1->GetTextColor() != Black)
      {
        pGUI_StartStop_M1->SetTextColor(Black);
        pGUI_StartStop_M1->SetFocusable(true);      
        pGUI_StartStop_M1->RefreshAsync();
      }
    }   
  }
  // Check fault M2
  (*pUI_SetReg)(g_oUI,MC_PROTOCOL_REG_TARGET_MOTOR,M2);
  uint32_t Flags_M2 = (*pUI_GetReg)(oUI,MC_PROTOCOL_REG_FLAGS);
  State_t StateM2 = (State_t)((*pUI_GetReg)(oUI,MC_PROTOCOL_REG_STATUS));
  uint16_t FaultOccurred_M2  = (uint16_t)(Flags_M2);
  uint16_t FaultCondition_M2 = (uint16_t)(Flags_M2 >> 16);
  // Faultack management M2
  if (pGUI_FaultAck_M2)
  {
    if ((FaultOccurred_M2)&&(!FaultCondition_M2))
    {
      pGUI_FaultAck_M2->SetTextColor(Black);
      pGUI_FaultAck_M2->SetFocusable(true);      
      pGUI_FaultAck_M2->RefreshAsync();   
    }
    else
    {
      /* Remove the focus on Fault Ack button if it focused */
      if (Page3.GetActiveControl() == pGUI_FaultAck_M2)
      {
        Page3.SetActiveNextControl();
      }
      if (pGUI_FaultAck_M2->GetTextColor() != LightGrey)
      {
        pGUI_FaultAck_M2->SetTextColor(LightGrey);
        pGUI_FaultAck_M2->SetFocusable(false);
        pGUI_FaultAck_M2->RefreshAsync();
      }      
    }   
  }
  // Start/Stop management M2
  if (pGUI_StartStop_M2)
  {
    if ((FaultOccurred_M2)||(FaultCondition_M2))
    {
      /* Remove the focus on Fault Ack button if it focused */
      if (Page3.GetActiveControl() == pGUI_StartStop_M2)
      {
        Page3.SetActiveNextControl();
      }

      if (pGUI_StartStop_M2->GetTextColor() != LightGrey)
      {
        pGUI_StartStop_M2->SetTextColor(LightGrey);
        pGUI_StartStop_M2->SetFocusable(false);      
        pGUI_StartStop_M2->RefreshAsync();   
      }
    }
    else
    {
      if (pGUI_StartStop_M2->GetTextColor() != Black)
      {
        pGUI_StartStop_M2->SetTextColor(Black);
        pGUI_StartStop_M2->SetFocusable(true);      
        pGUI_StartStop_M2->RefreshAsync();
      }
    }   
  }
  (*pUI_SetReg)(g_oUI,MC_PROTOCOL_REG_TARGET_MOTOR, bMotorSelTMP);
  /* When a fault occurs and until it is not acknowledged the LCD is brought to
     the dual page or fault page.*/
  if ((FaultOccurred_M1)||(FaultCondition_M1)||
      (FaultOccurred_M2)||(FaultCondition_M2))
  {    
    if ((MainFrm.GetActivePageNumber() != 1) &&
        (MainFrm.GetActivePageNumber() != 2))
    {
      MainFrm.SetActivePage(1);
    }
    if (MainFrm.GetActivePageNumber() == 1)
    {
      static uint16_t hErrorMessageCounter = 0u;
      if ((MotorSel == M1) && ((FaultOccurred_M2)||(FaultCondition_M2)))
      {
        if (hErrorMessageCounter == 0)
        {
          pGUI_MotorSel->SetSelectedIndex(M2);
          OnGUI_MotorSel_ChangeValue(MC_NULL,0);
          pGUI_MotorSel->SetEdit(false);
        }
      } else
      if ((MotorSel == M2) && ((FaultOccurred_M1)||(FaultCondition_M1)))
      {
        if (hErrorMessageCounter == 0)
        {
          pGUI_MotorSel->SetSelectedIndex(M1);
          OnGUI_MotorSel_ChangeValue(MC_NULL,0);
          pGUI_MotorSel->SetEdit(false);
        }
      }
      if (hErrorMessageCounter == 0)
      {
        hErrorMessageCounter = 30u; // Error message time xx * LCD Clock
      }
      else
      {
        hErrorMessageCounter--;
      }
    }
  }
  if (pGUI_StartBoth)
  {
    if (((StateM1 == IDLE) && (StateM2 == IDLE)) ||
       ((StateM1 == RUN) && (StateM2 == RUN)))
    {
      if (pGUI_StartBoth->GetTextColor() != Black)
      {
        // Enables Start Both
        pGUI_StartBoth->SetTextColor(Black);
        pGUI_StartBoth->SetFocusable(true);
        pGUI_StartBoth->RefreshAsync();
      }
    }
    else
    {
      /* Remove the focus on Fault Ack button if it focused */
      if (Page3.GetActiveControl() == pGUI_StartBoth)
      {
        Page3.SetActiveNextControl();
      }
      
      if (pGUI_StartBoth->GetTextColor() != LightGrey)
      {
        // Disables Start Both
        pGUI_StartBoth->SetTextColor(LightGrey);
        pGUI_StartBoth->SetFocusable(false);
        pGUI_StartBoth->RefreshAsync();
      }
    }
  }
#endif

  NumericDataU8[MotorSel][GUI_Overcurrent] = GUI_NO_FAULT;
  if (FaultOccurred & MC_BREAK_IN)
  {
    NumericDataU8[MotorSel][GUI_Overcurrent] = GUI_FAULT_OCCURRED;
  }
  if (FaultCondition & MC_BREAK_IN)
  {
    NumericDataU8[MotorSel][GUI_Overcurrent] = GUI_FAULT_CONDITION;
  }
  
  NumericDataU8[MotorSel][GUI_RevupFail] = GUI_NO_FAULT;
  if (FaultOccurred & MC_START_UP)
  {
    NumericDataU8[MotorSel][GUI_RevupFail] = GUI_FAULT_OCCURRED;
  }
  if (FaultCondition & MC_START_UP)
  {
    NumericDataU8[MotorSel][GUI_RevupFail] = GUI_FAULT_CONDITION;
  }
  
  NumericDataU8[MotorSel][GUI_SpeedFdbk] = GUI_NO_FAULT;
  if (FaultOccurred & MC_SPEED_FDBK)
  {
    NumericDataU8[MotorSel][GUI_SpeedFdbk] = GUI_FAULT_OCCURRED;
  }
  if (FaultCondition & MC_SPEED_FDBK)
  {
    NumericDataU8[MotorSel][GUI_SpeedFdbk] = GUI_FAULT_CONDITION;
  }
  
  NumericDataU8[MotorSel][GUI_SW_Error] = GUI_NO_FAULT;
  if (FaultOccurred & MC_FOC_DURATION)
  {
    NumericDataU8[MotorSel][GUI_SW_Error] = GUI_FAULT_OCCURRED;
  }
  if (FaultCondition & MC_FOC_DURATION)
  {
    NumericDataU8[MotorSel][GUI_SW_Error] = GUI_FAULT_CONDITION;
  }
  if (FaultOccurred & MC_SW_ERROR)
  {
    NumericDataU8[MotorSel][GUI_SW_Error] = GUI_FAULT_OCCURRED;
  }
  if (FaultCondition & MC_SW_ERROR)
  {
    NumericDataU8[MotorSel][GUI_SW_Error] = GUI_FAULT_CONDITION;
  }
  
  NumericDataU8[MotorSel][GUI_UnderVolt] = GUI_NO_FAULT;
  if (FaultOccurred & MC_UNDER_VOLT)
  {
    NumericDataU8[MotorSel][GUI_UnderVolt] = GUI_FAULT_OCCURRED;
  }
  if (FaultCondition & MC_UNDER_VOLT)
  {
    NumericDataU8[MotorSel][GUI_UnderVolt] = GUI_FAULT_CONDITION;
  }
  
  NumericDataU8[MotorSel][GUI_OverVolt] = GUI_NO_FAULT;
  if (FaultOccurred & MC_OVER_VOLT)
  {
    NumericDataU8[MotorSel][GUI_OverVolt] = GUI_FAULT_OCCURRED;
  }
  if (FaultCondition & MC_OVER_VOLT)
  {
    NumericDataU8[MotorSel][GUI_OverVolt] = GUI_FAULT_CONDITION;
  }
  
  NumericDataU8[MotorSel][GUI_OverTemp] = GUI_NO_FAULT;
  if (FaultOccurred & MC_OVER_TEMP)
  {
    NumericDataU8[MotorSel][GUI_OverTemp] = GUI_FAULT_OCCURRED;
  }
  if (FaultCondition & MC_OVER_TEMP)
  {
    NumericDataU8[MotorSel][GUI_OverTemp] = GUI_FAULT_CONDITION;
  }
    
  if (pGUI_FaultAck)
  {
    if (pGUI_Overcurrent->GetTextColor() != GUI_Fault_Color_Code[NumericDataU8[MotorSel][GUI_Overcurrent]])
    {
      pGUI_Overcurrent->SetTextColor(GUI_Fault_Color_Code[NumericDataU8[MotorSel][GUI_Overcurrent]]);
      pGUI_Overcurrent->RefreshAsync();
    }
    if (pGUI_RevupFail->GetTextColor() != GUI_Fault_Color_Code[NumericDataU8[MotorSel][GUI_RevupFail]])
    {
      pGUI_RevupFail->SetTextColor(GUI_Fault_Color_Code[NumericDataU8[MotorSel][GUI_RevupFail]]);
      pGUI_RevupFail->RefreshAsync();
    }
    if (pGUI_SpeedFdbk->GetTextColor() != GUI_Fault_Color_Code[NumericDataU8[MotorSel][GUI_SpeedFdbk]])
    {
      pGUI_SpeedFdbk->SetTextColor(GUI_Fault_Color_Code[NumericDataU8[MotorSel][GUI_SpeedFdbk]]);
      pGUI_SpeedFdbk->RefreshAsync();
    }
    if (pGUI_SW_Error->GetTextColor() != GUI_Fault_Color_Code[NumericDataU8[MotorSel][GUI_SW_Error]])
    {
      pGUI_SW_Error->SetTextColor(GUI_Fault_Color_Code[NumericDataU8[MotorSel][GUI_SW_Error]]);
      pGUI_SW_Error->RefreshAsync();
    }
    if (pGUI_UnderVolt->GetTextColor() != GUI_Fault_Color_Code[NumericDataU8[MotorSel][GUI_UnderVolt]])
    {
      pGUI_UnderVolt->SetTextColor(GUI_Fault_Color_Code[NumericDataU8[MotorSel][GUI_UnderVolt]]);
      pGUI_UnderVolt->RefreshAsync();
    }
    if (pGUI_OverVolt->GetTextColor() != GUI_Fault_Color_Code[NumericDataU8[MotorSel][GUI_OverVolt]])
    {
      pGUI_OverVolt->SetTextColor(GUI_Fault_Color_Code[NumericDataU8[MotorSel][GUI_OverVolt]]);
      pGUI_OverVolt->RefreshAsync();
    }
    if (pGUI_OverTemp->GetTextColor() != GUI_Fault_Color_Code[NumericDataU8[MotorSel][GUI_OverTemp]])
    {
      pGUI_OverTemp->SetTextColor(GUI_Fault_Color_Code[NumericDataU8[MotorSel][GUI_OverTemp]]);
      pGUI_OverTemp->RefreshAsync();
    }
  }
  
  if (pGUI_DC_BUS)
  {
    pGUI_DC_BUS->RefreshAsync();
  }
  if (pGUI_Temp)
  {
    pGUI_Temp->RefreshAsync();
  }
  if (pGUI_SpeedMeasured)
  {
    pGUI_SpeedMeasured->RefreshAsync();
  }
  if (pGUI_FW_BUSMeasured)
  {
    pGUI_FW_BUSMeasured->RefreshAsync();
  }
  if (pGUI_Iq_Meas)
  {
    pGUI_Iq_Meas->RefreshAsync();
  }
  if (pGUI_Id_Meas)
  {
    pGUI_Id_Meas->RefreshAsync();
  }
#ifdef LCD_UI_DUAL
  bMotorSelTMP = (*pUI_GetReg)(oUI,MC_PROTOCOL_REG_TARGET_MOTOR);
  
  (*pUI_SetReg)(oUI,MC_PROTOCOL_REG_TARGET_MOTOR,M1);
  NumericData32[M1][GUI_SpeedMeasured] = (*pUI_GetReg)(oUI,MC_PROTOCOL_REG_SPEED_MEAS);
  
  if ((*pUI_SetReg)(oUI,MC_PROTOCOL_REG_TARGET_MOTOR,M2))
  {
    NumericData32[M2][GUI_SpeedMeasured] = (*pUI_GetReg)(oUI,MC_PROTOCOL_REG_SPEED_MEAS);
    (*pUI_SetReg)(oUI,MC_PROTOCOL_REG_TARGET_MOTOR,bMotorSelTMP);
  }
  
  if (pGUI_SpeedMeasured_M1)
  {
    pGUI_SpeedMeasured_M1->RefreshAsync();
  }
  if (pGUI_SpeedMeasured_M2)
  {
    pGUI_SpeedMeasured_M2->RefreshAsync();
  }  
#endif
}

/**
  * @brief  It is used to store the UI Imported functions.
  * @param  void** List of imported functions.
  * @retval none.
  */
void LCDI_SetUIImportedFunctions(void* const* ImportedFunctions)
{
//  pUI_GetReg = (pUI_GetReg_t)(ImportedFunctions[IF_UI_GetReg]);
//  pUI_ExecSpeedRamp = (pUI_ExecSpeedRamp_t)(ImportedFunctions[IF_UI_ExecSpeedRamp]);
//  pUI_SetReg = (pUI_SetReg_t)(ImportedFunctions[IF_UI_SetReg]);
//  pUI_ExecCmd = (pUI_ExecCmd_t)(ImportedFunctions[IF_UI_ExecCmd]);
//  pUI_GetSelectedMCConfig = (pUI_GetSelectedMCConfig_t)(ImportedFunctions[IF_UI_GetSelectedMCConfig]);
//  pUI_SetRevupData = (pUI_SetRevupData_t)(ImportedFunctions[IF_UI_SetRevupData]);
//  pUI_GetRevupData = (pUI_GetRevupData_t)(ImportedFunctions[IF_UI_GetRevupData]);
//  pUI_DACChannelConfig = (pUI_DACChannelConfig_t)(ImportedFunctions[IF_UI_DACChannelConfig]);
  g_ImportedFunctions = ImportedFunctions;
}

uint8_t FindStr(const char* str)
{
  uint8_t index = 0;
  while (str[index++] != 0);
  return index;
}

/**
  * @brief  It is used to create, initialize all page and numerical GUI values.
  *         Initial page will be visualized.
  * @param  oUI related object of class CUI.
  * @param  oDAC related DAC object upcasted to CUI. It can be MC_NULL.
  * @param  s_fwVer String contating firmware version.
  * @retval none.
  */
void LCDI_Init(CUI oUI, CUI oDAC, const char* s_fwVer)
{    
  g_oUI = oUI;
  g_oDAC = oDAC;
  
  MainFrm.SetCaption((char*)s_fwVer);
#ifdef LCD_UI_SINGLE
  MainFrm.SetStatusLabel((char*)(&s_fwVer[FindStr(s_fwVer)]));
#else
  gs_fwVer = s_fwVer;
#endif
  
  /*Configuration of object*/
  MainFrm.AddPage((CSTMWin *)&Page1);
  MainFrm.AddPage((CSTMWin *)&Page2);
#ifdef LCD_UI_DUAL
  MainFrm.AddPage((CSTMWin *)&Page3);
#endif
  MainFrm.AddPage((CSTMWin *)&Page4);
  MainFrm.AddPage((CSTMWin *)&Page5);
  MainFrm.AddPage((CSTMWin *)&Page6);
  MainFrm.AddPage((CSTMWin *)&Page7);
  
  /* Numerical data initialization */
  MotorSel = 0;
  
  /* Set the current control mode according the configuration */
#ifdef LCD_UI_DUAL  
  uint8_t bMotorSelTMP = (*pUI_GetReg)(g_oUI,MC_PROTOCOL_REG_TARGET_MOTOR);
  (*pUI_SetReg)(g_oUI,MC_PROTOCOL_REG_TARGET_MOTOR,M1);
#endif
  
  STC_Modality_t STCmode = (STC_Modality_t)(*pUI_GetReg)(g_oUI,MC_PROTOCOL_REG_CONTROL_MODE);
  if (STCmode == STC_SPEED_MODE)
  {
    NumericDataU8[M1][GUI_CtrlMode] = GUI_SPEED_MODE;
    Page4.SetVisualizable(true);
  }
  else
  {
    NumericDataU8[M1][GUI_CtrlMode] = GUI_TORQUE_MODE;
    Page4.SetVisualizable(false);
  }
  
  NumericDataU8[M1][GUI_DAC_Ch1] = 0;
  NumericDataU8[M1][GUI_DAC_Ch2] = 1;
  NumericDataU8[M1][GUI_Currents_Input] = 0;
  NumericDataU8[M1][GUI_IqIdPIDGainsLink] = false;
  NumericDataU8[M1][GUI_Overcurrent] =  GUI_NO_FAULT;
  NumericDataU8[M1][GUI_RevupFail] =    GUI_NO_FAULT;
  NumericDataU8[M1][GUI_SpeedFdbk] =    GUI_NO_FAULT;
  NumericDataU8[M1][GUI_SW_Error] =     GUI_NO_FAULT;
  NumericDataU8[M1][GUI_UnderVolt] =    GUI_NO_FAULT;
  NumericDataU8[M1][GUI_OverVolt] =     GUI_NO_FAULT;
  NumericDataU8[M1][GUI_OverTemp] =     GUI_NO_FAULT;
  
#ifdef LCD_UI_DUAL
  (*pUI_SetReg)(g_oUI,MC_PROTOCOL_REG_TARGET_MOTOR,M2);
  STCmode = (STC_Modality_t)(*pUI_GetReg)(g_oUI,MC_PROTOCOL_REG_CONTROL_MODE);
  if (STCmode == STC_SPEED_MODE)
  {
    NumericDataU8[M2][GUI_CtrlMode] = GUI_SPEED_MODE;
  }
  else
  {
    NumericDataU8[M2][GUI_CtrlMode] = GUI_TORQUE_MODE;
  }
  (*pUI_SetReg)(g_oUI,MC_PROTOCOL_REG_TARGET_MOTOR,bMotorSelTMP);
  
  NumericDataU8[M2][GUI_DAC_Ch1] = 0;
  NumericDataU8[M2][GUI_DAC_Ch2] = 1;
  NumericDataU8[M2][GUI_Currents_Input] = 0;
  NumericDataU8[M2][GUI_IqIdPIDGainsLink] = false;
  NumericDataU8[M2][GUI_Overcurrent] =  GUI_NO_FAULT;
  NumericDataU8[M2][GUI_RevupFail] =    GUI_NO_FAULT;
  NumericDataU8[M2][GUI_SpeedFdbk] =    GUI_NO_FAULT;
  NumericDataU8[M2][GUI_SW_Error] =     GUI_NO_FAULT;
  NumericDataU8[M2][GUI_UnderVolt] =    GUI_NO_FAULT;
  NumericDataU8[M2][GUI_OverVolt] =     GUI_NO_FAULT;
  NumericDataU8[M2][GUI_OverTemp] =     GUI_NO_FAULT;
#endif
  
  LCDI_UpdateAll(oUI);
  
  EVNT_EDIT_ON_CHANGEPAGE(MainFrm,OnMainFrm_ChangePage);
  
  MainFrm.SetActivePage(0);  
  
  uint32_t hUICfg = (*pUI_GetSelectedMCConfig)(oUI);
  if ((MAIN_SCFG_VALUE(hUICfg) == UI_SCODE_STO_PLL) ||
      (AUX_SCFG_VALUE(hUICfg) == UI_SCODE_STO_PLL))
  {
     Page6.SetVisualizable(true);
  }
  else
  {
    Page6.SetVisualizable(false);
  }
  if ((MAIN_SCFG_VALUE(hUICfg) == UI_SCODE_STO_CR) ||
      (AUX_SCFG_VALUE(hUICfg) == UI_SCODE_STO_CR))
  {
     Page7.SetVisualizable(true);
  }
  else
  {
    Page7.SetVisualizable(false);
  }
  
#ifdef ENABLE_START_STOP_BUTTON
  /* Init PB Key input (Start/Stop button) */
  STM_EVAL_PBInit(BUTTON_KEY,BUTTON_MODE_GPIO);
#endif
  
}

/**
  * @brief  It is used to retrieve the DAC configuration from UI configuration.
  * @param  oUI related object of class CUI.
  * @retval DAC_Config_t The related DAC configuration, see definition.
  */
DAC_Config_t LCDI_GetDACConfig(CUI oUI)
{
  DAC_Config_t DAC_CFG = GUI_DAC_CFG_Invalid;
  uint32_t hUICfg = (*pUI_GetSelectedMCConfig)(oUI);
  if (AUX_SCFG_VALUE(hUICfg) == UI_SCODE_NONE)
  {
    if (MAIN_SCFG_VALUE(hUICfg) == UI_SCODE_STO_PLL)
    {
      DAC_CFG = GUI_DAC_CFG_SLPLL;
    }
    if (MAIN_SCFG_VALUE(hUICfg) == UI_SCODE_STO_CR)
    {
      DAC_CFG = GUI_DAC_CFG_SLCR;
    }
    if ((MAIN_SCFG_VALUE(hUICfg) == UI_SCODE_HALL) || (MAIN_SCFG_VALUE(hUICfg) == UI_SCODE_ENC))
    {
      DAC_CFG = GUI_DAC_CFG_SR;
    }
  }
  else
  {
    if (((MAIN_SCFG_VALUE(hUICfg) == UI_SCODE_STO_PLL) && (AUX_SCFG_VALUE(hUICfg) == UI_SCODE_STO_CR)) ||
        ((MAIN_SCFG_VALUE(hUICfg) == UI_SCODE_STO_CR) && (AUX_SCFG_VALUE(hUICfg) == UI_SCODE_STO_PLL)))
    {
      DAC_CFG = GUI_DAC_CFG_SL_SL;
    }
    if (((MAIN_SCFG_VALUE(hUICfg) == UI_SCODE_STO_PLL) && ((AUX_SCFG_VALUE(hUICfg) == UI_SCODE_ENC) || (AUX_SCFG_VALUE(hUICfg) == UI_SCODE_HALL))) ||
        ((AUX_SCFG_VALUE(hUICfg) == UI_SCODE_STO_PLL) && ((MAIN_SCFG_VALUE(hUICfg) == UI_SCODE_ENC) || (MAIN_SCFG_VALUE(hUICfg) == UI_SCODE_HALL))))
    {
      DAC_CFG = GUI_DAC_CFG_SLPLL_SR;
    }
    if (((MAIN_SCFG_VALUE(hUICfg) == UI_SCODE_STO_CR) && ((AUX_SCFG_VALUE(hUICfg) == UI_SCODE_ENC) || (AUX_SCFG_VALUE(hUICfg) == UI_SCODE_HALL))) ||
        ((AUX_SCFG_VALUE(hUICfg) == UI_SCODE_STO_CR) && ((MAIN_SCFG_VALUE(hUICfg) == UI_SCODE_ENC) || (MAIN_SCFG_VALUE(hUICfg) == UI_SCODE_HALL))))
    {
      DAC_CFG = GUI_DAC_CFG_SLCR_SR;
    }
  }
  return DAC_CFG;
}

/**
  * @brief  It is used to refresh GUI it have to be called continuously.
  * @retval none.
  */
void LCDI_Polling()
{
  MainFrm.MainWinUpdate();
  
#ifdef ENABLE_START_STOP_BUTTON
  
  /* Chek status of Start/Stop button and performs debounce management */
  static uint16_t hKeyButtonDebounceCounter = 0u;
  if ((STM_EVAL_PBGetState(BUTTON_KEY) == Bit_RESET) &&
      (hKeyButtonDebounceCounter == 0))
  {
#ifdef LCD_UI_SINGLE
    OnGUI_StartStop_Click(NULL,0);
#endif
#ifdef LCD_UI_DUAL
    uint8_t bMotorSelTMP = (*pUI_GetReg)(g_oUI,MC_PROTOCOL_REG_TARGET_MOTOR);
    (*pUI_SetReg)(g_oUI,MC_PROTOCOL_REG_TARGET_MOTOR,M1);
    (*pUI_ExecCmd)(g_oUI,MC_PROTOCOL_CMD_STOP_MOTOR);
    (*pUI_SetReg)(g_oUI,MC_PROTOCOL_REG_TARGET_MOTOR,M2);
    (*pUI_ExecCmd)(g_oUI,MC_PROTOCOL_CMD_STOP_MOTOR);
    (*pUI_SetReg)(g_oUI,MC_PROTOCOL_REG_TARGET_MOTOR, bMotorSelTMP);
#endif
    hKeyButtonDebounceCounter = 4u; // Debounce time xx * LCD Clock
  }
  if (hKeyButtonDebounceCounter > 0)
  {
    hKeyButtonDebounceCounter--;
  }
#endif
  
}

void OnIntText_ChangeValue(HANDLE_WIN hWin, uint32_t wParam)
{
  uint32_t Addr;
  Addr = (uint32_t)(((CSTMEditInt*)hWin)->GetIntAddress());
  Addr -= (uint32_t)(NumericData[MotorSel]);
  Addr >>= 1;
  if (ID_Code[(uint8_t)Addr] != MC_PROTOCOL_REG_UNDEFINED)
  {
    (*pUI_SetReg)(g_oUI,ID_Code[(uint8_t)Addr],wParam);
  }
}

void OnGUI_IqKP_ChangeValue(HANDLE_WIN hWin, uint32_t wParam)
{
  OnIntText_ChangeValue(hWin,wParam);
  if (NumericDataU8[MotorSel][GUI_IqIdPIDGainsLink])
  {
    NumericData[MotorSel][GUI_IdKP] = wParam;
    pGUI_IdKP->SetIntValue(wParam);
    pGUI_IdKP->RefreshAsync();
  }
}

void OnGUI_IqKI_ChangeValue(HANDLE_WIN hWin, uint32_t wParam)
{
  OnIntText_ChangeValue(hWin,wParam);
  if (NumericDataU8[MotorSel][GUI_IqIdPIDGainsLink])
  {
    NumericData[MotorSel][GUI_IdKI] = wParam;
    pGUI_IdKI->SetIntValue(wParam);
    pGUI_IdKI->RefreshAsync();
  }
}

void OnGUI_IqKD_ChangeValue(HANDLE_WIN hWin, uint32_t wParam)
{
  OnIntText_ChangeValue(hWin,wParam);
  if (NumericDataU8[MotorSel][GUI_IqIdPIDGainsLink])
  {
    if (pGUI_IdKD)
    {
      NumericData[MotorSel][GUI_IdKD] = wParam;
      pGUI_IdKD->SetIntValue(wParam);
      pGUI_IdKD->RefreshAsync();
    }
  }
}

void OnGUI_Iq_Ref_ChangeValue(HANDLE_WIN hWin, uint32_t wParam)
{
  switch (NumericDataU8[MotorSel][GUI_Currents_Input])
  {
    case 0:
      (*pUI_SetCurrentReferences)(g_oUI,NumericData[MotorSel][GUI_Iq_Ref],NumericData[MotorSel][GUI_Id_Ref]);
      break;
    case 1:
      (*pUI_SetCurrentReferences)(g_oUI,(int16_t)(NumericData[MotorSel][GUI_I_Ref]*sin((NumericData[MotorSel][GUI_Eps_Ref]*3.14)/180)),
                                  (int16_t)(NumericData[MotorSel][GUI_I_Ref]*cos((NumericData[MotorSel][GUI_Eps_Ref]*3.14)/180)));
#ifdef LCD_UI_DUAL
      /* Update NumericData[MotorSel][GUI_Iq_Ref] and NumericData[MotorSel][GUI_Id_Ref] required by page 3 */
      NumericData[MotorSel][GUI_Iq_Ref] = (int16_t)(NumericData[MotorSel][GUI_I_Ref]*sin((NumericData[MotorSel][GUI_Eps_Ref]*3.14)/180));
      NumericData[MotorSel][GUI_Id_Ref] =  (int16_t)(NumericData[MotorSel][GUI_I_Ref]*cos((NumericData[MotorSel][GUI_Eps_Ref]*3.14)/180));
#endif
       break;
     
  }
}

void OnGUI_Id_Ref_ChangeValue(HANDLE_WIN hWin, uint32_t wParam)
{
  switch (NumericDataU8[MotorSel][GUI_Currents_Input])
  {
  case 0:
    if (NumericDataU8[MotorSel][GUI_CtrlMode] == GUI_SPEED_MODE)
    {
      if ((*pUI_GetSelectedMCConfig)(g_oUI) & UI_CFGOPT_SETIDINSPDMODE) // Set Iqd ref in speed mode
      {
        (*pUI_SetReg)(g_oUI,MC_PROTOCOL_REG_IQ_SPEEDMODE,(int16_t)(NumericData[MotorSel][GUI_Id_Ref]));
      }
    }
    else
    {
      (*pUI_SetCurrentReferences)(g_oUI,NumericData[MotorSel][GUI_Iq_Ref],NumericData[MotorSel][GUI_Id_Ref]);
    }
    break;
  case 1:
      (*pUI_SetCurrentReferences)(g_oUI,(int16_t)(NumericData[MotorSel][GUI_I_Ref]*sin((NumericData[MotorSel][GUI_Eps_Ref]*3.14)/180)),
                                  (int16_t)(NumericData[MotorSel][GUI_I_Ref]*cos((NumericData[MotorSel][GUI_Eps_Ref]*3.14)/180)));
       
#ifdef LCD_UI_DUAL
      /* Update NumericData[MotorSel][GUI_Iq_Ref] and NumericData[MotorSel][GUI_Id_Ref] required by page 3 */
      NumericData[MotorSel][GUI_Iq_Ref] = (int16_t)(NumericData[MotorSel][GUI_I_Ref]*sin((NumericData[MotorSel][GUI_Eps_Ref]*3.14)/180));
      NumericData[MotorSel][GUI_Id_Ref] =  (int16_t)(NumericData[MotorSel][GUI_I_Ref]*cos((NumericData[MotorSel][GUI_Eps_Ref]*3.14)/180));
#endif
       
    break;
  }
}

#ifdef LCD_UI_DUAL
void OnGUI_Iq_Ref_ChangeValue_M1(HANDLE_WIN hWin, uint32_t wParam)
{
  uint8_t bMotorSelTMP = (*pUI_GetReg)(g_oUI,MC_PROTOCOL_REG_TARGET_MOTOR);
  (*pUI_SetReg)(g_oUI,MC_PROTOCOL_REG_TARGET_MOTOR,M1);
  
  (*pUI_SetCurrentReferences)(g_oUI,NumericData[M1][GUI_Iq_Ref],NumericData[M1][GUI_Id_Ref]);
  
  /* Update NumericData[M1][GUI_I_Ref] and NumericData[M1][GUI_Eps_Ref] required by page 5 */  
  NumericData[M1][GUI_I_Ref] = (int16_t)(sqrt((float)(NumericData[M1][GUI_Iq_Ref]*NumericData[M1][GUI_Iq_Ref] +
                                                      NumericData[M1][GUI_Id_Ref]*NumericData[M1][GUI_Id_Ref])));
  NumericData[M1][GUI_Eps_Ref] = (int16_t)(180 * atan2((float)(NumericData[M1][GUI_Iq_Ref]),(float)(NumericData[M1][GUI_Id_Ref]))/3.14);
  
  (*pUI_SetReg)(g_oUI,MC_PROTOCOL_REG_TARGET_MOTOR, bMotorSelTMP);
}

void OnGUI_Id_Ref_ChangeValue_M1(HANDLE_WIN hWin, uint32_t wParam)
{
  uint8_t bMotorSelTMP = (*pUI_GetReg)(g_oUI,MC_PROTOCOL_REG_TARGET_MOTOR);
  (*pUI_SetReg)(g_oUI,MC_PROTOCOL_REG_TARGET_MOTOR,M1);

  if (NumericDataU8[M1][GUI_CtrlMode] == GUI_SPEED_MODE)
  {
    if ((*pUI_GetSelectedMCConfig)(g_oUI) & UI_CFGOPT_SETIDINSPDMODE) // Set Iqd ref in speed mode
    {
      (*pUI_SetReg)(g_oUI,MC_PROTOCOL_REG_IQ_SPEEDMODE,(int16_t)(NumericData[M1][GUI_Id_Ref]));
    }
  }
  else
  {
    (*pUI_SetCurrentReferences)(g_oUI,NumericData[M1][GUI_Iq_Ref],NumericData[M1][GUI_Id_Ref]);
  }
  
  /* Update NumericData[M1][GUI_I_Ref] and NumericData[M1][GUI_Eps_Ref] required by page 5 */  
  NumericData[M1][GUI_I_Ref] = (int16_t)(sqrt((float)(NumericData[M1][GUI_Iq_Ref]*NumericData[M1][GUI_Iq_Ref] +
                                                      NumericData[M1][GUI_Id_Ref]*NumericData[M1][GUI_Id_Ref])));
  NumericData[M1][GUI_Eps_Ref] = (int16_t)(180 * atan2((float)(NumericData[M1][GUI_Iq_Ref]),(float)(NumericData[M1][GUI_Id_Ref]))/3.14);
  
  (*pUI_SetReg)(g_oUI,MC_PROTOCOL_REG_TARGET_MOTOR, bMotorSelTMP);
}

void OnGUI_Iq_Ref_ChangeValue_M2(HANDLE_WIN hWin, uint32_t wParam)
{
  uint8_t bMotorSelTMP = (*pUI_GetReg)(g_oUI,MC_PROTOCOL_REG_TARGET_MOTOR);
  (*pUI_SetReg)(g_oUI,MC_PROTOCOL_REG_TARGET_MOTOR,M2);

  (*pUI_SetCurrentReferences)(g_oUI,NumericData[M2][GUI_Iq_Ref],NumericData[M2][GUI_Id_Ref]);
  
  /* Update NumericData[M1][GUI_I_Ref] and NumericData[M1][GUI_Eps_Ref] required by page 5 */  
  NumericData[M2][GUI_I_Ref] = (int16_t)(sqrt((float)(NumericData[M2][GUI_Iq_Ref]*NumericData[M2][GUI_Iq_Ref] +
                                                      NumericData[M2][GUI_Id_Ref]*NumericData[M2][GUI_Id_Ref])));
  NumericData[M2][GUI_Eps_Ref] = (int16_t)(180 * atan2((float)(NumericData[M2][GUI_Iq_Ref]),(float)(NumericData[M2][GUI_Id_Ref]))/3.14);
  
  (*pUI_SetReg)(g_oUI,MC_PROTOCOL_REG_TARGET_MOTOR, bMotorSelTMP);
}

void OnGUI_Id_Ref_ChangeValue_M2(HANDLE_WIN hWin, uint32_t wParam)
{
  uint8_t bMotorSelTMP = (*pUI_GetReg)(g_oUI,MC_PROTOCOL_REG_TARGET_MOTOR);
  (*pUI_SetReg)(g_oUI,MC_PROTOCOL_REG_TARGET_MOTOR,M2);

  if (NumericDataU8[M2][GUI_CtrlMode] == GUI_SPEED_MODE)
  {
    if ((*pUI_GetSelectedMCConfig)(g_oUI) & UI_CFGOPT_SETIDINSPDMODE) // Set Iqd ref in speed mode
    {
      (*pUI_SetReg)(g_oUI,MC_PROTOCOL_REG_IQ_SPEEDMODE,(int16_t)(NumericData[M2][GUI_Id_Ref]));
    }
  }
  else
  {
    (*pUI_SetCurrentReferences)(g_oUI,NumericData[M2][GUI_Iq_Ref],NumericData[M2][GUI_Id_Ref]);
  }
  
  /* Update NumericData[M1][GUI_I_Ref] and NumericData[M1][GUI_Eps_Ref] required by page 5 */  
  NumericData[M2][GUI_I_Ref] = (int16_t)(sqrt((float)(NumericData[M2][GUI_Iq_Ref]*NumericData[M2][GUI_Iq_Ref] +
                                                      NumericData[M2][GUI_Id_Ref]*NumericData[M2][GUI_Id_Ref])));
  NumericData[M2][GUI_Eps_Ref] = (int16_t)(180 * atan2((float)(NumericData[M2][GUI_Iq_Ref]),(float)(NumericData[M2][GUI_Id_Ref]))/3.14);
  
  (*pUI_SetReg)(g_oUI,MC_PROTOCOL_REG_TARGET_MOTOR, bMotorSelTMP);
}
#endif

void OnGUI_RUC_Stage_ChangeValue(HANDLE_WIN hWin, uint32_t wParam)
{
  NumericData[MotorSel][GUI_RUC_Stage] = wParam;
  
  // Update RUC Data
  LCDI_GetSelectedRUCData(g_oUI, MotorSel, NumericData[MotorSel][GUI_RUC_Stage]);
  pGUI_RUC_Duration->RefreshAsync();
  pGUI_RUC_FinalSpeed->RefreshAsync();
  pGUI_RUC_FinalToruqe->RefreshAsync();
}

void OnGUI_RUC_Duration_ChangeValue(HANDLE_WIN hWin, uint32_t wParam)
{
  NumericData[MotorSel][GUI_RUC_Duration] = wParam;
  LCDI_SetSelectedRUCData(g_oUI, MotorSel, NumericData[MotorSel][GUI_RUC_Stage]);
}

void OnGUI_RUC_FinalSpeed_ChangeValue(HANDLE_WIN hWin, uint32_t wParam)
{
  NumericData[MotorSel][GUI_RUC_FinalSpeed] = wParam;
  LCDI_SetSelectedRUCData(g_oUI, MotorSel, NumericData[MotorSel][GUI_RUC_Stage]);
}

void OnGUI_RUC_FinalToruqe_ChangeValue(HANDLE_WIN hWin, uint32_t wParam)
{
  NumericData[MotorSel][GUI_RUC_FinalToruqe] = wParam;
  LCDI_SetSelectedRUCData(g_oUI, MotorSel, NumericData[MotorSel][GUI_RUC_Stage]);
}

#ifdef LCD_UI_DUAL
void LCDI_SetStatusLabel(void)
{
  sprintf(buff, "Motor selected: %1d", MotorSel + 1);
  MainFrm.SetStatusLabel(buff);
}

void OnGUI_MotorSel_ChangeValue(HANDLE_WIN hWin, uint32_t wParam)
{
  uint16_t newVal = pGUI_MotorSel->GetSelectedIndex();
   
  if ((*pUI_SetReg)(g_oUI,MC_PROTOCOL_REG_TARGET_MOTOR,newVal))
  {
    MotorSel = newVal;
    
    // Update data
    LCDI_UpdateSelectedMC(g_oUI,newVal);
    
    MainFrm.SetActivePage(MainFrm.GetActivePageNumber()); // Page refresh
    MainFrm.GetActivePage()->SetActiveControl(4);
    pGUI_MotorSel->SetFocus(true);
    pGUI_MotorSel->SetEdit(true);
    pGUI_MotorSel->RefreshAsync();
    // Update the visibility of speed page
    if (NumericDataU8[MotorSel][GUI_CtrlMode] == GUI_TORQUE_MODE)
    {
      Page4.SetVisualizable(false);
    }
    else
    {
      Page4.SetVisualizable(true);
    }

    uint32_t hUICfg = (*pUI_GetSelectedMCConfig)(g_oUI);
    if ((MAIN_SCFG_VALUE(hUICfg) == UI_SCODE_STO_PLL) ||
        (AUX_SCFG_VALUE(hUICfg) == UI_SCODE_STO_PLL))
    {
      Page6.SetVisualizable(true);
    }
    else
    {
      Page6.SetVisualizable(false);
    }
    if ((MAIN_SCFG_VALUE(hUICfg) == UI_SCODE_STO_CR) ||
        (AUX_SCFG_VALUE(hUICfg) == UI_SCODE_STO_CR))
    {
      Page7.SetVisualizable(true);
    }
    else
    {
      Page7.SetVisualizable(false);
    }
    
    if (g_oDAC)
    {
      // Update DAC selected motor
      (*pUI_SetReg)(g_oDAC,MC_PROTOCOL_REG_TARGET_MOTOR,newVal);
    }
  }
  else
  {
    pGUI_MotorSel->SetSelectedIndex(MotorSel);
  }
}
#endif

void LCDI_UpdateCurrentRefLabels(void)
{
  switch (NumericDataU8[MotorSel][GUI_Currents_Input])
  {
  case 0:
    pLabel2_5->SetText("Iq ref.");
    pLabel4_5->SetText("Id ref.");
    pGUI_Iq_Ref->SetIntAddress(&NumericData[MotorSel][GUI_Iq_Ref]);
    pGUI_Id_Ref->SetIntAddress(&NumericData[MotorSel][GUI_Id_Ref]);
    pGUI_Iq_Ref->SetBounds(S16_MIN,S16_MAX);  // Iq
    pGUI_Id_Ref->SetBounds(S16_MIN,S16_MAX);  // Id

    if (NumericDataU8[MotorSel][GUI_CtrlMode] == GUI_SPEED_MODE)
    {
      if (!((*pUI_GetSelectedMCConfig)(g_oUI) & UI_CFGOPT_SETIDINSPDMODE))
      {
        pGUI_Id_Ref->SetFocusable(false);
      }
      else
      {
        pGUI_Id_Ref->SetFocusable(true);
      }
    }
    else
    {
      pGUI_Id_Ref->SetFocusable(true);
    }
    
    break;
  case 1:
    pLabel2_5->SetText("Amp.   ");
    pLabel4_5->SetText("Eps.Deg");
    pGUI_Iq_Ref->SetIntAddress(&NumericData[MotorSel][GUI_I_Ref]);
    pGUI_Id_Ref->SetIntAddress(&NumericData[MotorSel][GUI_Eps_Ref]);
    pGUI_Iq_Ref->SetBounds(0,S16_MAX);  // Amplitude
    pGUI_Id_Ref->SetBounds(0,359);      // Phase
    
    if (NumericDataU8[MotorSel][GUI_CtrlMode] == GUI_SPEED_MODE)
    {
      pGUI_Id_Ref->SetFocusable(false);
    }
    else
    {
      pGUI_Id_Ref->SetFocusable(true);
    }

    break;
  }
  pGUI_Iq_Ref->RefreshAsync();
  pGUI_Id_Ref->RefreshAsync();
}

void LCDI_UpdateCurrentRefData(void)
{
  switch (NumericDataU8[MotorSel][GUI_Currents_Input])
  {
  case 0:
    NumericData[MotorSel][GUI_Iq_Ref] = (int16_t)(NumericData[MotorSel][GUI_I_Ref]*sin((NumericData[MotorSel][GUI_Eps_Ref]*3.14)/180));
    NumericData[MotorSel][GUI_Id_Ref] = (int16_t)(NumericData[MotorSel][GUI_I_Ref]*cos((NumericData[MotorSel][GUI_Eps_Ref]*3.14)/180));
    break;
  case 1:
    if ((NumericData[MotorSel][GUI_Iq_Ref] == 0) && (NumericData[MotorSel][GUI_Id_Ref] == 0))
    {
      NumericData[MotorSel][GUI_I_Ref] = 0;
      NumericData[MotorSel][GUI_Eps_Ref] = 90;
    }
    else
    {
      NumericData[MotorSel][GUI_I_Ref] = (int16_t)(sqrt((float)(NumericData[MotorSel][GUI_Iq_Ref]*NumericData[MotorSel][GUI_Iq_Ref] +
                                                                NumericData[MotorSel][GUI_Id_Ref]*NumericData[MotorSel][GUI_Id_Ref])));
      NumericData[MotorSel][GUI_Eps_Ref] = (int16_t)(180 * atan2((float)(NumericData[MotorSel][GUI_Iq_Ref]),(float)(NumericData[MotorSel][GUI_Id_Ref]))/3.14);
    }
    break;
  }
}

void OnGUI_Currents_Input_ChangeValue(HANDLE_WIN hWin, uint32_t wParam)
{
  NumericDataU8[MotorSel][GUI_Currents_Input] = pGUI_Currents_Input->GetSelectedIndex();
  LCDI_UpdateCurrentRefData();
  LCDI_UpdateCurrentRefLabels();
}

void OnGUI_CtrlMode_ChangeText(HANDLE_WIN hWin, uint32_t wParam)
{
  NumericDataU8[MotorSel][GUI_CtrlMode] = pGUI_CtrlMode->GetSelectedIndex();
  
  if (NumericDataU8[MotorSel][GUI_CtrlMode] == GUI_TORQUE_MODE)
  {
    Page4.SetVisualizable(false);
    (*pUI_SetReg)(g_oUI,MC_PROTOCOL_REG_CONTROL_MODE,STC_TORQUE_MODE);
  }
  else
  {
    Page4.SetVisualizable(true);
    (*pUI_SetReg)(g_oUI,MC_PROTOCOL_REG_CONTROL_MODE,STC_SPEED_MODE);
  }
}

void OnGUI_DAC_Chx_ChangeText(HANDLE_WIN hWin, uint32_t wParam)
{
  if (hWin == pGUI_DAC_Ch1)
  {
    uint8_t Sel = pGUI_DAC_Ch1->GetSelectedIndex();
    NumericDataU8[MotorSel][GUI_DAC_Ch1] = Sel;
    (*pUI_DACChannelConfig)((CUI)g_oDAC, DAC_CH0,
                        GUI_DAC_ChID[LCDI_GetDACConfig(g_oUI)][Sel]);
  }
  else
  {
    uint8_t Sel = pGUI_DAC_Ch2->GetSelectedIndex();
    NumericDataU8[MotorSel][GUI_DAC_Ch2] = Sel;
    (*pUI_DACChannelConfig)((CUI)g_oDAC, DAC_CH1, 
                        GUI_DAC_ChID[LCDI_GetDACConfig(g_oUI)][Sel]);
  } 
}

void OnGUI_IqIdPIDGainsLink(HANDLE_WIN hWin, uint32_t wParam)
{
  uint8_t newVal = (uint8_t)(wParam);
  NumericDataU8[MotorSel][GUI_IqIdPIDGainsLink] = newVal;
  pGUI_IdKP->SetFocusable(!newVal);
  pGUI_IdKI->SetFocusable(!newVal);
  
  if (newVal)
  {
    NumericData[MotorSel][GUI_IdKP] = NumericData[MotorSel][GUI_IqKP];
    NumericData[MotorSel][GUI_IdKI] = NumericData[MotorSel][GUI_IqKI];
    NumericData[MotorSel][GUI_IdKD] = NumericData[MotorSel][GUI_IqKD];
    pGUI_IdKP->SetIntValue(NumericData[MotorSel][GUI_IdKP]);
    pGUI_IdKI->SetIntValue(NumericData[MotorSel][GUI_IdKI]);
    if (pGUI_IdKD)
    {
      pGUI_IdKD->SetIntValue(NumericData[MotorSel][GUI_IdKD]);
    }
  }

  pGUI_IdKP->RefreshAsync();
  pGUI_IdKI->RefreshAsync();
  if (pGUI_IdKD)
  {
    pGUI_IdKD->SetFocusable(!newVal);
    pGUI_IdKD->RefreshAsync();
  }
}

#ifdef LCD_UI_SINGLE
void OnMainFrm_ChangePage(HANDLE_WIN hWin, uint32_t wParam)
{  
  LCDI_ReleaseAllCtrl();
  switch (wParam)
  {
  case 0:
    LCDI_ShowPage1();
    break;
  case 1:
    LCDI_ShowPage2();
    break;
  case 2:
    LCDI_ShowPage4();
    break;
  case 3:
    LCDI_ShowPage5();
    break;
  case 4:
    LCDI_ShowPage6();
    break;
  case 5:
    LCDI_ShowPage7();
    break;
  default:
    break;
  }
}
#endif

#ifdef LCD_UI_DUAL
void OnMainFrm_ChangePage(HANDLE_WIN hWin, uint32_t wParam)
{  
  bool UpdateStatusLabel = true;
  LCDI_ReleaseAllCtrl();
  switch (wParam)
  {
  case 0:
    LCDI_ShowPage1();
    UpdateStatusLabel = false;
    break;
  case 1:
    LCDI_ShowPage2();
    UpdateStatusLabel = false;
    break;
  case 2:
    LCDI_ShowPage3();
    UpdateStatusLabel = false;
    break;
  case 3:
    LCDI_ShowPage4();
    break;
  case 4:
    LCDI_ShowPage5();
    break;
  case 5:
    LCDI_ShowPage6();
    break;
  case 6:
    LCDI_ShowPage7();
    break;
  default:
    break;
  }
  if (UpdateStatusLabel)
  {
    LCDI_SetStatusLabel();
  }
  else
  {
    MainFrm.SetStatusLabel((char*)(&gs_fwVer[FindStr(gs_fwVer)]));
  }
}
#endif

void LCDI_CreateCommon(void)
{
  // Monitor
  pGUI_SpeedMonitor = new CSTMGroup("Monitor",145,90,&MainFrm.m_WorkArea,160,20);
  pLabel6_4 = new CSTMLabel("Measured speed",pGUI_SpeedMonitor,5,15);
  pGUI_SpeedMeasured = new CSTMEditInt32(&NumericData32[MotorSel][GUI_SpeedMeasured],"%6d",6,pGUI_SpeedMonitor,5,30);
  pGUI_StartStop = new CSTMButton("Start/Stop",pGUI_SpeedMonitor,5,65);
  pLabel7_4 = new CSTMLabel("rpm",pGUI_SpeedMonitor,60,30);
  
  EVNT_CTRL_ON_CLICK(*pGUI_StartStop,OnGUI_StartStop_Click );
}

void LCDI_ReleaseAllCtrl(void)
{
  Page1.RemoveAllControls();
  Page2.RemoveAllControls();
  
#ifdef LCD_UI_DUAL
  Page3.RemoveAllControls();
#endif
  
  Page4.RemoveAllControls();
  Page5.RemoveAllControls();
  Page6.RemoveAllControls();
  Page7.RemoveAllControls();
  
  // Configuration and debug page
#ifdef LCD_UI_DUAL
  pGUI_MotorSel = NULL;
#endif
  pGUI_CtrlMode = NULL;
  
  pGUI_DAC_Ch1 = NULL;
  pGUI_DAC_Ch2 = NULL;
  
  pGUI_DC_BUS = NULL;
  pGUI_Temp = NULL;
  
  pGUI_Overcurrent = NULL;
  pGUI_RevupFail = NULL;
  pGUI_SpeedFdbk = NULL;
  pGUI_SW_Error = NULL;
  pGUI_UnderVolt = NULL;
  pGUI_OverVolt = NULL;
  pGUI_OverTemp = NULL;
  pGUI_FaultAck = NULL;

#ifdef LCD_UI_DUAL
  // Dual control panel
  pGUI_SpeedTarget_M1 = NULL;
  pGUI_Iq_Ref_M1 = NULL;
  pGUI_SpeedMeasured_M1 = NULL;
  pGUI_SpeedRampDuration_M1 = NULL;
  pGUI_Id_Ref_M1 = NULL;
  pGUI_SpeedRampExec_M1 = NULL;
  pGUI_SpeedTarget_M2 = NULL;
  pGUI_Iq_Ref_M2 = NULL;
  pGUI_SpeedMeasured_M2 = NULL;
  pGUI_SpeedRampDuration_M2 = NULL;
  pGUI_Id_Ref_M2 = NULL;
  pGUI_SpeedRampExec_M2 = NULL;
  pGUI_StartStop_M1 = NULL;
  pGUI_FaultAck_M1 = NULL;
  pGUI_StartStop_M2 = NULL;
  pGUI_FaultAck_M2 = NULL;
  pGUI_StartBoth = NULL;
  pGUI_ExecBothRamp = NULL;
#endif
  
  // Speed controller
  pGUI_SpeedTarget = NULL;
  pGUI_SpeedRampDuration = NULL;
  pGUI_SpeedRampExec = NULL;
  // Monitor
  pGUI_SpeedKP = NULL;
  pGUI_SpeedKI = NULL;
  pGUI_SpeedKD = NULL;
  pGUI_FW_BUSTarget = NULL;
  pGUI_FW_BUSMeasured = NULL;
  pGUI_FW_KP = NULL;
  pGUI_FW_KI = NULL;
  
  // Current controllers
  pLabel2_5 = NULL;
  pGUI_Iq_Ref = NULL;
  pGUI_Iq_Meas = NULL;
  pLabel4_5 = NULL;
  pGUI_Id_Ref = NULL;
  pGUI_Id_Meas = NULL;
  pGUI_IqKP = NULL;
  pGUI_IqKI = NULL;
  pLabel10_5 = NULL;
  pGUI_IqKD = NULL;
  pGUI_IdKP = NULL;
  pGUI_IdKI = NULL;
  pLabel13_5 = NULL;
  pGUI_IdKD = NULL;
  pGUI_IqIdPIDGainsLink = NULL;
  pGUI_Currents_Input = NULL;
  
  // Sensorless tuning
  pGUI_STO_C1 = NULL;
  pGUI_STO_C2 = NULL;
  pGUI_STO_PLL_KP = NULL;
  pGUI_STO_PLL_KI = NULL;
  pGUI_RUC_Duration = NULL;
  pGUI_RUC_FinalSpeed = NULL;
  pGUI_RUC_FinalToruqe = NULL;
  pGUI_RUC_Stage = NULL;
  
  // Encoder tuning
  pGUI_EncoderAlign = NULL;
  
  // Monitor
  pGUI_SpeedMonitor = NULL;
  pLabel6_4 = NULL;
  pGUI_SpeedMeasured = NULL;
  pGUI_StartStop = NULL;
  pLabel7_4 = NULL;
}

void LCDI_ShowPage1(void)
{  
  // Help page
  CSTMLabel* pLabel1_1 = new CSTMLabel("Help Page", &Page1, 5, 3);
  CSTMLabel* pLabel2_1 = new CSTMLabel("Use the joystick to work with LCD GUI", &Page1, 5, 30);
  CSTMLabel* pLabel3_1 = new CSTMLabel("-UP/DOWN to move between controls", &Page1, 5, 60);
  CSTMLabel* pLabel4_1 = new CSTMLabel("-LEFT/RIGTH to move between pages", &Page1, 5, 75);
  CSTMLabel* pLabel5_1 = new CSTMLabel("-SEL to interact with the control", &Page1, 5, 90);
  CSTMLabel* pLabel6_1 = new CSTMLabel("Copyright STMicroelectronics", &Page1, 5, 180);
  CSTMLabel* pLabel7_1 = new CSTMLabel((char*)s_LCDfwVer, &Page1, 5, 115);
  
  Page1.AddControl(pLabel1_1);
  Page1.AddControl(pLabel2_1);
  Page1.AddControl(pLabel3_1);
  Page1.AddControl(pLabel4_1);
  Page1.AddControl(pLabel5_1);
  Page1.AddControl(pLabel6_1);
  Page1.AddControl(pLabel7_1);
  
#if !defined USE_STM3210E_EVAL
  CSTMBitmap* pBmp1_1  = new CSTMBitmap(LogoImage.Buffer, 72, 44, &Page1, 247, 150);
  Page1.AddControl(pBmp1_1);
#endif
}

void LCDI_ShowPage2(void)
{
  // Disabling help page
  Page1.SetVisualizable(false);
  
  // Configuration and debug page
  CSTMLabel* pLabel1_2 = new CSTMLabel("Configuration and debug", &Page2, 0, 0);
#ifdef LCD_UI_DUAL
  CSTMLabel* pLabel2_2 = new CSTMLabel("Motor", &Page2, 10, 20);
  pGUI_MotorSel = new CSTMCombo(GUI_MotorSelTxt, &Page2, 10, 33);
  CSTMLabel* pLabel3_2 = new CSTMLabel("Ctrl mode", &Page2, 100, 20);
  pGUI_CtrlMode = new CSTMCombo(GUI_CtrlModeTxt, &Page2, 100, 33);
#else
  CSTMLabel* pLabel3_2 = new CSTMLabel("Ctrl mode", &Page2, 10, 20);
  pGUI_CtrlMode = new CSTMCombo(GUI_CtrlModeTxt, &Page2, 10, 33);
#endif
  
  CSTMGroup* pGUI_PB_Status = new CSTMGroup("Power board status", 155, 60, &Page2, 10, 53);
  CSTMLabel* pLabel6_2 = new CSTMLabel("DC Bus volt", pGUI_PB_Status, 15, 17);
  CSTMLabel* pLabel7_2 = new CSTMLabel("Heatsink T.", pGUI_PB_Status, 15, 37);
  pGUI_DC_BUS = new CSTMEditInt(&NumericData[MotorSel][GUI_DC_BUS],"%3d",3,pGUI_PB_Status,
                         110, 15);
  pGUI_Temp = new CSTMEditInt(&NumericData[MotorSel][GUI_Temp],"%3d",3,pGUI_PB_Status, 
                       110, 35);
  
  CSTMGroup* pGUI_Faults = new CSTMGroup("Faults", 100, 170, &Page2, 205, 20);
  pGUI_Overcurrent = new CSTMLabel("Overcurrent", pGUI_Faults, 5, 15);
  pGUI_RevupFail = new CSTMLabel("Revup fail", pGUI_Faults, 5, 33);
  pGUI_SpeedFdbk = new CSTMLabel("Speed fdbk", pGUI_Faults, 5, 51);
  pGUI_SW_Error = new CSTMLabel("SW error", pGUI_Faults, 5, 69);
  pGUI_UnderVolt = new CSTMLabel("Under volt", pGUI_Faults, 5, 87);
  pGUI_OverVolt = new CSTMLabel("Over volt", pGUI_Faults, 5, 105);
  pGUI_OverTemp = new CSTMLabel("Over temp", pGUI_Faults, 5, 123);
  pGUI_FaultAck = new CSTMButton("Fault ack", pGUI_Faults, 10, 141);
  EVNT_CTRL_ON_CLICK(*pGUI_FaultAck,OnGUI_FaultAck_Click);
  
  pGUI_FaultAck->SetTextColor(LightGrey);
  pGUI_FaultAck->SetFocusable(false);
  
  /* Configuration and debug */
  Page2.AddControl(pGUI_FaultAck); // Control 0
  Page2.AddControl(pLabel1_2);
  Page2.AddControl(pLabel3_2);
#ifdef LCD_UI_DUAL
  Page2.AddControl(pLabel2_2);
  Page2.AddControl(pGUI_MotorSel); // Control 4
  pGUI_MotorSel->SetSelectedIndex(MotorSel);
  EVNT_EDIT_ON_CHANGETEXT(*pGUI_MotorSel,OnGUI_MotorSel_ChangeValue);
#endif
  Page2.AddControl(pGUI_CtrlMode);
  pGUI_CtrlMode->SetSelectedIndex(NumericDataU8[MotorSel][GUI_CtrlMode]);
  
  if ((*pUI_GetSelectedMCConfig)(g_oUI) & UI_CFGOPT_DAC)
  {
    CSTMGroup* pGUI_DAC_Settings = new CSTMGroup("DAC Settings", 190, 60, &Page2, 10, 115);
    CSTMLabel* pLabel4_2 = new CSTMLabel("Ch1", pGUI_DAC_Settings, 5, 17);
    CSTMLabel* pLabel5_2 = new CSTMLabel("Ch2", pGUI_DAC_Settings, 5, 37);
    
    pGUI_DAC_Ch1 = new CSTMCombo(GUI_DAC_ChTxt[LCDI_GetDACConfig(g_oUI)], pGUI_DAC_Settings, 33, 15);
    pGUI_DAC_Ch2 = new CSTMCombo(GUI_DAC_ChTxt[LCDI_GetDACConfig(g_oUI)], pGUI_DAC_Settings, 33, 35);
    Page2.AddControl(pGUI_DAC_Settings);
    Page2.AddControl(pLabel4_2);
    Page2.AddControl(pLabel5_2);
    Page2.AddControl(pGUI_DAC_Ch1);
    Page2.AddControl(pGUI_DAC_Ch2);
    pGUI_DAC_Ch1->SetSelectedIndex(NumericDataU8[MotorSel][GUI_DAC_Ch1]);
    pGUI_DAC_Ch2->SetSelectedIndex(NumericDataU8[MotorSel][GUI_DAC_Ch2]);
    
    EVNT_EDIT_ON_CHANGETEXT(*pGUI_DAC_Ch1, OnGUI_DAC_Chx_ChangeText);
    EVNT_EDIT_ON_CHANGETEXT(*pGUI_DAC_Ch2, OnGUI_DAC_Chx_ChangeText);
  }

  Page2.AddControl(pGUI_PB_Status);
  Page2.AddControl(pLabel6_2);
  Page2.AddControl(pLabel7_2);
  Page2.AddControl(pGUI_DC_BUS);
  Page2.AddControl(pGUI_Temp);
  pGUI_DC_BUS->SetFocusable(false);
  pGUI_Temp->SetFocusable(false);
  
  uint32_t hUICfg = (*pUI_GetSelectedMCConfig)(g_oUI);
  if ((MAIN_SCFG_VALUE(hUICfg) == UI_SCODE_ENC) || (AUX_SCFG_VALUE(hUICfg) == UI_SCODE_ENC))
  {
    pGUI_EncoderAlign = new CSTMButton("Encoder alignment",&Page2,10,178);
    Page2.AddControl(pGUI_EncoderAlign);
    
    EVNT_CTRL_ON_CLICK(*pGUI_EncoderAlign,OnGUI_EncoderAlign_Click );
  }
  
  Page2.AddControl(pGUI_Faults);
  Page2.AddControl(pGUI_Overcurrent);
  Page2.AddControl(pGUI_RevupFail);
  Page2.AddControl(pGUI_SpeedFdbk);
  Page2.AddControl(pGUI_SW_Error);
  Page2.AddControl(pGUI_UnderVolt);
  Page2.AddControl(pGUI_OverVolt);
  Page2.AddControl(pGUI_OverTemp);
  pGUI_Overcurrent->SetTextColor(GUI_Fault_Color_Code[NumericDataU8[MotorSel][GUI_Overcurrent]]);
  pGUI_RevupFail->SetTextColor(GUI_Fault_Color_Code[NumericDataU8[MotorSel][GUI_RevupFail]]);
  pGUI_SpeedFdbk->SetTextColor(GUI_Fault_Color_Code[NumericDataU8[MotorSel][GUI_SpeedFdbk]]);
  pGUI_SW_Error->SetTextColor(GUI_Fault_Color_Code[NumericDataU8[MotorSel][GUI_SW_Error]]);
  pGUI_UnderVolt->SetTextColor(GUI_Fault_Color_Code[NumericDataU8[MotorSel][GUI_UnderVolt]]);
  pGUI_OverVolt->SetTextColor(GUI_Fault_Color_Code[NumericDataU8[MotorSel][GUI_OverVolt]]);
  pGUI_OverTemp->SetTextColor(GUI_Fault_Color_Code[NumericDataU8[MotorSel][GUI_OverTemp]]);
    
  EVNT_EDIT_ON_CHANGETEXT(*pGUI_CtrlMode, OnGUI_CtrlMode_ChangeText);
  
  Page2.SetActiveNextControl();
}

#ifdef LCD_UI_DUAL
void LCDI_ShowPage3(void)
{
  // Dual control panel
  CSTMLabel* pLabel1_3 = new CSTMLabel("Dual control panel",&Page3, 0, 0);
  CSTMGroup* pGUI_SetPoint_M1 = new CSTMGroup("Motor 1",145,90,&Page3,10,20);
  if (NumericDataU8[M1][GUI_CtrlMode] == GUI_SPEED_MODE)
  {
    CSTMLabel* pLabel2_3 = new CSTMLabel("Target Measured",pGUI_SetPoint_M1,5,15);
    pGUI_SpeedTarget_M1 = new CSTMEditInt32(&NumericData32[M1][GUI_SpeedTarget],"%6d",6,pGUI_SetPoint_M1,5,30);

    uint8_t bMotorSelTMP = (*pUI_GetReg)(g_oUI,MC_PROTOCOL_REG_TARGET_MOTOR);
    (*pUI_SetReg)(g_oUI,MC_PROTOCOL_REG_TARGET_MOTOR,M1);
    pGUI_SpeedTarget_M1->SetBounds((*pUI_GetReg)(g_oUI,MC_PROTOCOL_REG_MIN_APP_SPEED),
                                (*pUI_GetReg)(g_oUI,MC_PROTOCOL_REG_MAX_APP_SPEED));
    (*pUI_SetReg)(g_oUI,MC_PROTOCOL_REG_TARGET_MOTOR, bMotorSelTMP);
    
    pGUI_SpeedMeasured_M1 = new CSTMEditInt32(&NumericData32[M1][GUI_SpeedMeasured],"%6d",6,pGUI_SetPoint_M1,60,30);
    CSTMLabel* pLabel3_3 = new CSTMLabel("rpm",pGUI_SetPoint_M1,117,30);
    CSTMLabel* pLabel4_3 = new CSTMLabel("Ramp duration ms",pGUI_SetPoint_M1,5,50);
    pGUI_SpeedRampDuration_M1 = new CSTMEditInt(&NumericData[M1][GUI_SpeedRampDuration],"%6d",6,pGUI_SetPoint_M1,5,65);
    pGUI_SpeedRampDuration_M1->SetBounds(0,S16_MAX);
    pGUI_SpeedRampExec_M1 = new CSTMButton("Exec",pGUI_SetPoint_M1,60,65);
    
    Page3.AddControl(pLabel2_3);
    Page3.AddControl(pGUI_SpeedTarget_M1);
    Page3.AddControl(pGUI_SpeedMeasured_M1);
    Page3.AddControl(pLabel3_3);
    Page3.AddControl(pLabel4_3);
    Page3.AddControl(pGUI_SpeedRampDuration_M1);
    Page3.AddControl(pGUI_SpeedRampExec_M1);
    pGUI_SpeedMeasured_M1->SetFocusable(false);
    EVNT_CTRL_ON_CLICK(*pGUI_SpeedRampExec_M1,OnGUI_SpeedRampExec_M1_Click );
  }
  else
  {
    CSTMLabel* pLabel2_3 = new CSTMLabel("Iq ref./Speed",pGUI_SetPoint_M1,5,15);
    pGUI_Iq_Ref_M1 = new CSTMEditInt(&NumericData[M1][GUI_Iq_Ref],"%6d",6,pGUI_SetPoint_M1,5,30);
    EVNT_EDIT_INT_ON_CHANGEVALUE(*pGUI_Iq_Ref_M1, OnGUI_Iq_Ref_ChangeValue_M1);
    pGUI_SpeedMeasured_M1 = new CSTMEditInt32(&NumericData32[M1][GUI_SpeedMeasured],"%6d",6,pGUI_SetPoint_M1,60,30);
    CSTMLabel* pLabel3_3 = new CSTMLabel("rpm",pGUI_SetPoint_M1,117,30);
    CSTMLabel* pLabel4_3 = new CSTMLabel("Id ref.",pGUI_SetPoint_M1,5,50);
    pGUI_Id_Ref_M1 = new CSTMEditInt(&NumericData[M1][GUI_Id_Ref],"%6d",6,pGUI_SetPoint_M1,5,65);
    EVNT_EDIT_INT_ON_CHANGEVALUE(*pGUI_Id_Ref_M1, OnGUI_Id_Ref_ChangeValue_M1);

    Page3.AddControl(pLabel2_3);
    Page3.AddControl(pGUI_Iq_Ref_M1);
    Page3.AddControl(pGUI_SpeedMeasured_M1);
    Page3.AddControl(pLabel3_3);
    Page3.AddControl(pLabel4_3);
    Page3.AddControl(pGUI_Id_Ref_M1);
    pGUI_SpeedMeasured_M1->SetFocusable(false);
  }
  
  pGUI_StartStop_M1 = new CSTMButton("Start/Stop",&Page3,40,120);
  pGUI_FaultAck_M1 = new CSTMButton("Fault ack", &Page3, 40,140);
  EVNT_CTRL_ON_CLICK(*pGUI_FaultAck_M1,OnGUI_FaultAck_M1_Click);  
  pGUI_FaultAck_M1->SetTextColor(LightGrey);
  pGUI_FaultAck_M1->SetFocusable(false);
  Page3.AddControl(pGUI_StartStop_M1);
  Page3.AddControl(pGUI_FaultAck_M1);
  
  CSTMGroup* pGUI_SetPoint_M2 = new CSTMGroup("Motor 2",145,90,&Page3,160,20);
  if (NumericDataU8[M2][GUI_CtrlMode] == GUI_SPEED_MODE)
  {
    CSTMLabel* pLabel5_3 = new CSTMLabel("Target Measured",pGUI_SetPoint_M2,5,15);
    pGUI_SpeedTarget_M2 = new CSTMEditInt32(&NumericData32[M2][GUI_SpeedTarget],"%6d",6,pGUI_SetPoint_M2,5,30);
    
    uint8_t bMotorSelTMP = (*pUI_GetReg)(g_oUI,MC_PROTOCOL_REG_TARGET_MOTOR);
    (*pUI_SetReg)(g_oUI,MC_PROTOCOL_REG_TARGET_MOTOR,M2);
    pGUI_SpeedTarget_M2->SetBounds((*pUI_GetReg)(g_oUI,MC_PROTOCOL_REG_MIN_APP_SPEED),
                                (*pUI_GetReg)(g_oUI,MC_PROTOCOL_REG_MAX_APP_SPEED));
    (*pUI_SetReg)(g_oUI,MC_PROTOCOL_REG_TARGET_MOTOR, bMotorSelTMP);
    
    pGUI_SpeedMeasured_M2 = new CSTMEditInt32(&NumericData32[M2][GUI_SpeedMeasured],"%6d",6,pGUI_SetPoint_M2,60,30);
    CSTMLabel* pLabel6_3 = new CSTMLabel("rpm",pGUI_SetPoint_M2,117,30);
    CSTMLabel* pLabel7_3 = new CSTMLabel("Ramp duration ms",pGUI_SetPoint_M2,5,50);
    pGUI_SpeedRampDuration_M2 = new CSTMEditInt(&NumericData[M2][GUI_SpeedRampDuration],"%6d",6,pGUI_SetPoint_M2,5,65);
    pGUI_SpeedRampDuration_M2->SetBounds(0,S16_MAX);
    pGUI_SpeedRampExec_M2 = new CSTMButton("Exec",pGUI_SetPoint_M2,60,65);
    
    Page3.AddControl(pLabel5_3);
    Page3.AddControl(pGUI_SpeedTarget_M2);
    Page3.AddControl(pGUI_SpeedMeasured_M2);
    Page3.AddControl(pLabel6_3);
    Page3.AddControl(pLabel7_3);
    Page3.AddControl(pGUI_SpeedRampDuration_M2);
    Page3.AddControl(pGUI_SpeedRampExec_M2);
    pGUI_SpeedMeasured_M2->SetFocusable(false);
    EVNT_CTRL_ON_CLICK(*pGUI_SpeedRampExec_M2,OnGUI_SpeedRampExec_M2_Click );
  }
  else
  {
    CSTMLabel* pLabel5_3 = new CSTMLabel("Iq ref./Speed",pGUI_SetPoint_M2,5,15);
    pGUI_Iq_Ref_M2 = new CSTMEditInt(&NumericData[M2][GUI_Iq_Ref],"%6d",6,pGUI_SetPoint_M2,5,30);
    EVNT_EDIT_INT_ON_CHANGEVALUE(*pGUI_Iq_Ref_M2, OnGUI_Iq_Ref_ChangeValue_M2);
    pGUI_SpeedMeasured_M2 = new CSTMEditInt32(&NumericData32[M2][GUI_SpeedMeasured],"%6d",6,pGUI_SetPoint_M2,60,30);
    CSTMLabel* pLabel6_3 = new CSTMLabel("rpm",pGUI_SetPoint_M2,117,30);
    CSTMLabel* pLabel7_3 = new CSTMLabel("Id ref.",pGUI_SetPoint_M2,5,50);
    pGUI_Id_Ref_M2 = new CSTMEditInt(&NumericData[M2][GUI_Id_Ref],"%6d",6,pGUI_SetPoint_M2,5,65);
    EVNT_EDIT_INT_ON_CHANGEVALUE(*pGUI_Id_Ref_M2, OnGUI_Id_Ref_ChangeValue_M2);
    
    Page3.AddControl(pLabel5_3);
    Page3.AddControl(pGUI_Iq_Ref_M2);
    Page3.AddControl(pGUI_SpeedMeasured_M2);
    Page3.AddControl(pLabel6_3);
    Page3.AddControl(pLabel7_3);
    Page3.AddControl(pGUI_Id_Ref_M2);
    pGUI_SpeedMeasured_M2->SetFocusable(false);
  }

  pGUI_StartStop_M2 = new CSTMButton("Start/Stop",&Page3,190,120);
  pGUI_FaultAck_M2 = new CSTMButton("Fault ack", &Page3, 190,140);
  EVNT_CTRL_ON_CLICK(*pGUI_FaultAck_M2,OnGUI_FaultAck_M2_Click);  
  pGUI_FaultAck_M2->SetTextColor(LightGrey);
  pGUI_FaultAck_M2->SetFocusable(false);
  
  pGUI_StartBoth = new CSTMButton("Start/Stop both motors",&Page3,68,160);
    
  Page3.AddControl(pLabel1_3);
  Page3.AddControl(pGUI_SetPoint_M1);
  Page3.AddControl(pGUI_SetPoint_M2);
  Page3.AddControl(pGUI_StartStop_M2);
  Page3.AddControl(pGUI_FaultAck_M2);
  Page3.AddControl(pGUI_StartBoth);
  
  if ((NumericDataU8[M1][GUI_CtrlMode] == GUI_SPEED_MODE) &&
      (NumericDataU8[M2][GUI_CtrlMode] == GUI_SPEED_MODE))
  {
    pGUI_ExecBothRamp = new CSTMButton("Exec simultaneous Ramps",&Page3,64,180);
    Page3.AddControl(pGUI_ExecBothRamp);
    EVNT_CTRL_ON_CLICK(*pGUI_ExecBothRamp,OnGUI_ExecBothRamp_Click );
  }
  
  EVNT_CTRL_ON_CLICK(*pGUI_StartBoth,OnGUI_StartBoth_Click );
  EVNT_CTRL_ON_CLICK(*pGUI_StartStop_M1,OnGUI_StartStop_M1_Click );
  EVNT_CTRL_ON_CLICK(*pGUI_StartStop_M2,OnGUI_StartStop_M2_Click );
  
  Page3.SetActiveNextControl();
}
#endif

void LCDI_ShowPage4(void)
{
  // Speed controller
  CSTMLabel* pLabel1_4 = new CSTMLabel("Speed controller", &Page4, 0, 0);
  CSTMGroup* pGUI_SetPoint = new CSTMGroup("Set point",145,90,&Page4,10,20);
  CSTMLabel* pLabel3_4 = new CSTMLabel("rpm",pGUI_SetPoint,60,30);
  CSTMLabel* pLabel5_4 = new CSTMLabel("ms",pGUI_SetPoint,60,65);
  CSTMLabel* pLabel2_4 = new CSTMLabel("Target speed",pGUI_SetPoint,5,15);
  pGUI_SpeedTarget = new CSTMEditInt32(&NumericData32[MotorSel][GUI_SpeedTarget],"%6d",6,pGUI_SetPoint,5,30);
  pGUI_SpeedTarget->SetBounds((*pUI_GetReg)(g_oUI,MC_PROTOCOL_REG_MIN_APP_SPEED),
                              (*pUI_GetReg)(g_oUI,MC_PROTOCOL_REG_MAX_APP_SPEED));
  CSTMLabel* pLabel4_4 = new CSTMLabel("Ramp duration",pGUI_SetPoint,5,50);
  pGUI_SpeedRampDuration = new CSTMEditInt(&NumericData[MotorSel][GUI_SpeedRampDuration],"%6d",6,pGUI_SetPoint,5,65);
  pGUI_SpeedRampDuration->SetBounds(0,S16_MAX);
  pGUI_SpeedRampExec = new CSTMButton("Exec",pGUI_SetPoint,90,65);
  
  EVNT_CTRL_ON_CLICK(*pGUI_SpeedRampExec,OnGUI_SpeedRampExec_Click );

  LCDI_CreateCommon();
  
  CSTMGroup* pGUI_SpeedPIDGains = new CSTMGroup("PID Gains", 104, 75, &Page4, 10, 115);
  CSTMLabel* pLabel8_4 = new CSTMLabel("KP", pGUI_SpeedPIDGains, 10, 20);
  CSTMLabel* pLabel9_4 = new CSTMLabel("KI", pGUI_SpeedPIDGains, 10, 35);
  pGUI_SpeedKP = new CSTMEditInt(&NumericData[MotorSel][GUI_SpeedKP],"%6d", 6,pGUI_SpeedPIDGains, 40, 20);
  pGUI_SpeedKI = new CSTMEditInt(&NumericData[MotorSel][GUI_SpeedKI],"%6d", 6,pGUI_SpeedPIDGains, 40, 35);
  
  Page4.AddControl(pLabel1_4);
  Page4.AddControl(pLabel3_4);
  Page4.AddControl(pLabel5_4);
  Page4.AddControl(pGUI_SetPoint);
  Page4.AddControl(pLabel2_4);
  Page4.AddControl(pGUI_SpeedTarget);
  Page4.AddControl(pLabel4_4);
  Page4.AddControl(pGUI_SpeedRampDuration);
  Page4.AddControl(pGUI_SpeedRampExec);

  // Monitor
  Page4.AddControl(pGUI_SpeedMonitor);
  Page4.AddControl(pLabel6_4);
  Page4.AddControl(pGUI_SpeedMeasured);
  Page4.AddControl(pLabel7_4);  
  pGUI_SpeedMeasured->SetFocusable(false);  
  Page4.AddControl(pGUI_StartStop);
  
  Page4.AddControl(pGUI_SpeedPIDGains);
  Page4.AddControl(pLabel8_4);  
  Page4.AddControl(pLabel9_4);   
  Page4.AddControl(pGUI_SpeedKP);
  Page4.AddControl(pGUI_SpeedKI);
  if ((*pUI_GetSelectedMCConfig)(g_oUI) & UI_CFGOPT_SPEED_KD)
  {
    CSTMLabel* pLabel10_4 = new CSTMLabel("KD", pGUI_SpeedPIDGains, 10, 50);
    pGUI_SpeedKD = new CSTMEditInt(&NumericData[MotorSel][GUI_SpeedKD],"%6d", 6,pGUI_SpeedPIDGains, 40, 50);
    Page4.AddControl(pLabel10_4); 
    Page4.AddControl(pGUI_SpeedKD);
    pGUI_SpeedKD->SetBounds(0,S16_MAX);
    EVNT_EDIT_INT_ON_CHANGEVALUE(*pGUI_SpeedKP, OnIntText_ChangeValue);
  }
  pGUI_SpeedKP->SetBounds(0,S16_MAX);
  pGUI_SpeedKI->SetBounds(0,S16_MAX);
  
  if ((*pUI_GetSelectedMCConfig)(g_oUI) & UI_CFGOPT_FW)
  {
    CSTMGroup* pGUI_FluxWk = new CSTMGroup("Flux wl. tuning", 180, 75, &Page4, 125, 115);
    CSTMLabel* pLabel11_4 = new CSTMLabel("BUS\x80", pGUI_FluxWk, 10, 14);
    CSTMLabel* pLabel12_4 = new CSTMLabel("BUS\x80", pGUI_FluxWk, 80, 14);
    pGUI_FW_BUSTarget = new CSTMEditInt(&NumericData[MotorSel][GUI_FW_BUSTarget],"%4d",4,pGUI_FluxWk,10,25);
    pGUI_FW_BUSMeasured = new CSTMEditInt(&NumericData[MotorSel][GUI_FW_BUSMeasured],"%4d",4,pGUI_FluxWk,80,25);
    CSTMLabel* pLabel13_4 = new CSTMLabel("KP", pGUI_FluxWk, 10, 44);
    CSTMLabel* pLabel14_4 = new CSTMLabel("KI", pGUI_FluxWk, 80, 44);
    pGUI_FW_KP = new CSTMEditInt(&NumericData[MotorSel][GUI_FW_KP],"%6d",6,pGUI_FluxWk,10,55);
    pGUI_FW_KI = new CSTMEditInt(&NumericData[MotorSel][GUI_FW_KI],"%6d",6,pGUI_FluxWk,80,55);
    
    Page4.AddControl(pGUI_FluxWk);
    Page4.AddControl(pLabel11_4);  
    Page4.AddControl(pLabel12_4);  
    Page4.AddControl(pGUI_FW_BUSTarget);
    Page4.AddControl(pGUI_FW_BUSMeasured);
    pGUI_FW_BUSMeasured->SetFocusable(false);  
    Page4.AddControl(pLabel13_4);  
    Page4.AddControl(pLabel14_4);  
    Page4.AddControl(pGUI_FW_KP);
    Page4.AddControl(pGUI_FW_KI);
    
    pGUI_FW_BUSTarget->SetBounds(0,1000);
    pGUI_FW_KP->SetBounds(0,S16_MAX);
    pGUI_FW_KI->SetBounds(0,S16_MAX);
    
    EVNT_EDIT_INT_ON_CHANGEVALUE(*pGUI_FW_BUSTarget, OnIntText_ChangeValue);
    EVNT_EDIT_INT_ON_CHANGEVALUE(*pGUI_FW_KP, OnIntText_ChangeValue);
    EVNT_EDIT_INT_ON_CHANGEVALUE(*pGUI_FW_KI, OnIntText_ChangeValue);
  }
  
  EVNT_EDIT_INT_ON_CHANGEVALUE(*pGUI_SpeedKP, OnIntText_ChangeValue);
  EVNT_EDIT_INT_ON_CHANGEVALUE(*pGUI_SpeedKI, OnIntText_ChangeValue);

  Page4.SetActiveNextControl();
}

void LCDI_ShowPage5(void)
{
  // Current controllers
  CSTMLabel* pLabel1_5 = new CSTMLabel("Current controllers", &Page5, 0, 0);
  CSTMLabel* pLabel14_5 = new CSTMLabel("Input",&Page5,230,135);
  CSTMGroup* pGUI_SetPoints_Current = new CSTMGroup("Set points",145,90,&Page5,10,20);
  pLabel2_5 = new CSTMLabel("Iq ref.",pGUI_SetPoints_Current,5,15);
  pGUI_Iq_Ref = new CSTMEditInt(&NumericData[MotorSel][GUI_Iq_Ref],"%6d",6,pGUI_SetPoints_Current,5,30);
  CSTMLabel* pLabel3_5 = new CSTMLabel("Iq",pGUI_SetPoints_Current,80,15);
  pGUI_Iq_Meas = new CSTMEditInt(&NumericData[MotorSel][GUI_Iq_Meas],"%6d",6,pGUI_SetPoints_Current,80,30);
  pLabel4_5 = new CSTMLabel("Id ref.",pGUI_SetPoints_Current,5,50);
  pGUI_Id_Ref = new CSTMEditInt(&NumericData[MotorSel][GUI_Id_Ref],"%6d",6,pGUI_SetPoints_Current,5,65);
  CSTMLabel* pLabel5_5 = new CSTMLabel("Id",pGUI_SetPoints_Current,80,50);
  pGUI_Id_Meas = new CSTMEditInt(&NumericData[MotorSel][GUI_Id_Meas],"%6d",6,pGUI_SetPoints_Current,80,65);
  CSTMGroup* pGUI_IqPIDGains = new CSTMGroup("Iq PID Gains",104, 75, &Page5,10, 115);
  CSTMLabel* pLabel8_5 = new CSTMLabel("KP",pGUI_IqPIDGains,10, 20);
  pGUI_IqKP = new CSTMEditInt(&NumericData[MotorSel][GUI_IqKP],"%6d",6,pGUI_IqPIDGains,40, 20);
  CSTMLabel* pLabel9_5 = new CSTMLabel("KI",pGUI_IqPIDGains,10, 35);
  pGUI_IqKI = new CSTMEditInt(&NumericData[MotorSel][GUI_IqKI],"%6d",6,pGUI_IqPIDGains,40, 35);
  CSTMGroup* pGUI_IdPIDGains = new CSTMGroup("Id PID Gains",104, 75, &Page5,120, 115);
  CSTMLabel* pLabel11_5 = new CSTMLabel("KP",pGUI_IdPIDGains,10, 20);
  pGUI_IdKP = new CSTMEditInt(&NumericData[MotorSel][GUI_IdKP],"%6d",6,pGUI_IdPIDGains,40, 20);
  CSTMLabel* pLabel12_5 = new CSTMLabel("KI",pGUI_IdPIDGains,10, 35);
  pGUI_IdKI = new CSTMEditInt(&NumericData[MotorSel][GUI_IdKI],"%6d",6,pGUI_IdPIDGains,40, 35);
  pGUI_IqIdPIDGainsLink = new CSTMCheckBox("Link",&Page5,230,115);
  pGUI_Currents_Input = new CSTMCombo(GUI_Currents_InputTxt,&Page5, 230,150);
  
  LCDI_CreateCommon();  
  
  Page5.AddControl(pLabel1_5);
  Page5.AddControl(pLabel14_5);
  Page5.AddControl(pGUI_SetPoints_Current);
  Page5.AddControl(pLabel2_5);
  Page5.AddControl(pGUI_Iq_Ref);
  Page5.AddControl(pLabel3_5);
  Page5.AddControl(pGUI_Iq_Meas);
  pGUI_Iq_Meas->SetFocusable(false);  
  Page5.AddControl(pLabel4_5);
  Page5.AddControl(pGUI_Id_Ref);
  Page5.AddControl(pLabel5_5);
  Page5.AddControl(pGUI_Id_Meas);
  pGUI_Id_Meas->SetFocusable(false);  

  // Monitor
  Page5.AddControl(pGUI_SpeedMonitor);
  Page5.AddControl(pLabel6_4);
  Page5.AddControl(pGUI_SpeedMeasured);
  Page5.AddControl(pLabel7_4);  
  pGUI_SpeedMeasured->SetFocusable(false);  
  Page5.AddControl(pGUI_StartStop);
  
  uint8_t newVal = NumericDataU8[MotorSel][GUI_IqIdPIDGainsLink];

  Page5.AddControl(pGUI_IqPIDGains);
  Page5.AddControl(pLabel8_5);
  Page5.AddControl(pGUI_IqKP);
  Page5.AddControl(pLabel9_5);
  Page5.AddControl(pGUI_IqKI);
  EVNT_EDIT_INT_ON_CHANGEVALUE(*pGUI_IqKP, OnGUI_IqKP_ChangeValue);
  EVNT_EDIT_INT_ON_CHANGEVALUE(*pGUI_IqKI, OnGUI_IqKI_ChangeValue);
  if ((*pUI_GetSelectedMCConfig)(g_oUI) & UI_CFGOPT_Iq_KD)
  {
    pLabel10_5 = new CSTMLabel("KD",pGUI_IqPIDGains,10, 50);
    pGUI_IqKD = new CSTMEditInt(&NumericData[MotorSel][GUI_IqKD],"%6d",6,pGUI_IqPIDGains,40, 50);
    Page5.AddControl(pLabel10_5);
    Page5.AddControl(pGUI_IqKD);
    pGUI_IqKD->SetBounds(0,S16_MAX);
    EVNT_EDIT_INT_ON_CHANGEVALUE(*pGUI_IqKD, OnGUI_IqKD_ChangeValue);
  }
  pGUI_IqKP->SetBounds(0,S16_MAX);
  pGUI_IqKI->SetBounds(0,S16_MAX);
  
  Page5.AddControl(pGUI_IdPIDGains);
  Page5.AddControl(pLabel11_5);
  Page5.AddControl(pGUI_IdKP);
  Page5.AddControl(pLabel12_5);
  Page5.AddControl(pGUI_IdKI);
  if ((*pUI_GetSelectedMCConfig)(g_oUI) & UI_CFGOPT_Id_KD)
  {
    pLabel13_5 = new CSTMLabel("KD",pGUI_IdPIDGains,10, 50);
    pGUI_IdKD = new CSTMEditInt(&NumericData[MotorSel][GUI_IdKD],"%6d",6,pGUI_IdPIDGains,40, 50);
    Page5.AddControl(pLabel13_5);
    Page5.AddControl(pGUI_IdKD);
    pGUI_IdKD->SetBounds(0,S16_MAX);
    pGUI_IdKD->SetFocusable(!newVal);
    EVNT_EDIT_INT_ON_CHANGEVALUE(*pGUI_IdKD, OnIntText_ChangeValue);
  }
  pGUI_IdKP->SetBounds(0,S16_MAX);
  pGUI_IdKI->SetBounds(0,S16_MAX);
  
  Page5.AddControl(pGUI_IqIdPIDGainsLink);
  Page5.AddControl(pGUI_Currents_Input);
  pGUI_Currents_Input->SetSelectedIndex(NumericDataU8[MotorSel][GUI_Currents_Input]);
  LCDI_UpdateCurrentRefLabels();
  pGUI_IqIdPIDGainsLink->SetChecked(newVal);
  pGUI_IdKP->SetFocusable(!newVal);
  pGUI_IdKI->SetFocusable(!newVal);
  
  EVNT_EDIT_ON_CHANGETEXT(*pGUI_Currents_Input,OnGUI_Currents_Input_ChangeValue);
  EVNT_CTRL_ON_CLICK(*pGUI_IqIdPIDGainsLink,OnGUI_IqIdPIDGainsLink);
  
  EVNT_EDIT_INT_ON_CHANGEVALUE(*pGUI_Iq_Ref, OnGUI_Iq_Ref_ChangeValue);
  EVNT_EDIT_INT_ON_CHANGEVALUE(*pGUI_Id_Ref, OnGUI_Id_Ref_ChangeValue);
  EVNT_EDIT_INT_ON_CHANGEVALUE(*pGUI_IdKP, OnIntText_ChangeValue);
  EVNT_EDIT_INT_ON_CHANGEVALUE(*pGUI_IdKI, OnIntText_ChangeValue);
  
  if (NumericDataU8[MotorSel][GUI_CtrlMode] == GUI_SPEED_MODE)
  {
    pGUI_Iq_Ref->SetFocusable(false);
    if (!((*pUI_GetSelectedMCConfig)(g_oUI) & UI_CFGOPT_SETIDINSPDMODE))
    {
      pGUI_Id_Ref->SetFocusable(false);
    }
  }
  
  Page5.SetActiveNextControl();
}

void LCDI_ShowPage6(void)  // PLL
{
  CSTMLabel* pLabel1_6;
  uint32_t hUICfg = (*pUI_GetSelectedMCConfig)(g_oUI);
  // Sensorless tuning
  if (MAIN_SCFG_VALUE(hUICfg) == UI_SCODE_STO_PLL)
  {
    pLabel1_6 = new CSTMLabel("Sensorless tuning STO & PLL",&Page6, 0, 0);
  }
  if (AUX_SCFG_VALUE(hUICfg) == UI_SCODE_STO_PLL)
  {
    pLabel1_6 = new CSTMLabel("Sensorless tuning STO & PLL (Aux)",&Page6, 0, 0);
  }
  CSTMGroup* pGUI_STO_PLL;
  if (hUICfg & UI_CFGOPT_PLLTUNING)
  {
    pGUI_STO_PLL = new CSTMGroup("STO & PLL",145,90,&Page6,10,20);
  }
  else
  {
    pGUI_STO_PLL = new CSTMGroup("STO",145,90,&Page6,10,20);
  }
  CSTMLabel* pLabel2_6 = new CSTMLabel("G1",pGUI_STO_PLL,5,15);
  pGUI_STO_C1 = new CSTMEditInt(&NumericData[MotorSel][GUI_STO_C1],"%6d",6,pGUI_STO_PLL,5,30);
  CSTMLabel* pLabel3_6 = new CSTMLabel("G2",pGUI_STO_PLL,80,15);
  pGUI_STO_C2 = new CSTMEditInt(&NumericData[MotorSel][GUI_STO_C2],"%6d",6,pGUI_STO_PLL,80,30);
  
  LCDI_CreateCommon();
  
  Page6.AddControl(pLabel1_6);
  Page6.AddControl(pGUI_STO_PLL);
  Page6.AddControl(pLabel2_6);
  Page6.AddControl(pGUI_STO_C1);
  Page6.AddControl(pLabel3_6);
  Page6.AddControl(pGUI_STO_C2);
  
  if (hUICfg & UI_CFGOPT_PLLTUNING)
  {
    CSTMLabel* pLabel4_6 = new CSTMLabel("PLL KP",pGUI_STO_PLL,5,50);
    pGUI_STO_PLL_KP = new CSTMEditInt(&NumericData[MotorSel][GUI_STO_PLL_KP],"%6d",6,pGUI_STO_PLL,5,65);
    pGUI_STO_PLL_KP->SetBounds(0,S16_MAX);
    CSTMLabel* pLabel5_6 = new CSTMLabel("PLL KI",pGUI_STO_PLL,80,50);
    pGUI_STO_PLL_KI = new CSTMEditInt(&NumericData[MotorSel][GUI_STO_PLL_KI],"%6d",6,pGUI_STO_PLL,80,65);
    pGUI_STO_PLL_KI->SetBounds(0,S16_MAX);
    Page6.AddControl(pLabel4_6);
    Page6.AddControl(pGUI_STO_PLL_KP);
    Page6.AddControl(pLabel5_6);
    Page6.AddControl(pGUI_STO_PLL_KI);
    EVNT_EDIT_INT_ON_CHANGEVALUE(*pGUI_STO_PLL_KP, OnIntText_ChangeValue);
    EVNT_EDIT_INT_ON_CHANGEVALUE(*pGUI_STO_PLL_KI, OnIntText_ChangeValue);
  }
  
  // Monitor
  Page6.AddControl(pGUI_SpeedMonitor);
  Page6.AddControl(pLabel6_4);
  Page6.AddControl(pGUI_SpeedMeasured);
  Page6.AddControl(pLabel7_4);  
  pGUI_SpeedMeasured->SetFocusable(false);  
  Page6.AddControl(pGUI_StartStop);

    if (MAIN_SCFG_VALUE(hUICfg) == UI_SCODE_STO_PLL)
  {
    CSTMGroup* pGUI_RevupTuning = new CSTMGroup("Rev up tuning",295,75,&Page6,10,115);
    CSTMLabel* pLabel8_6 = new CSTMLabel("Duration",pGUI_RevupTuning,10,20);
    pGUI_RUC_Duration = new CSTMEditInt(&NumericData[MotorSel][GUI_RUC_Duration],"%6d",6,pGUI_RevupTuning,80,20);
    pGUI_RUC_Duration->SetBounds(0,S16_MAX);
    CSTMLabel* pLabel10_6 = new CSTMLabel("End spd",pGUI_RevupTuning,10,35);
    pGUI_RUC_FinalSpeed = new CSTMEditInt(&NumericData[MotorSel][GUI_RUC_FinalSpeed],"%6d",6,pGUI_RevupTuning,80,35);
    CSTMLabel* pLabel12_6 = new CSTMLabel("End Iq",pGUI_RevupTuning,10,50);
    pGUI_RUC_FinalToruqe = new CSTMEditInt(&NumericData[MotorSel][GUI_RUC_FinalToruqe],"%6d",6,pGUI_RevupTuning,80,50);
    CSTMLabel* pLabel13_6 = new CSTMLabel("Stage",pGUI_RevupTuning,180,20);
    pGUI_RUC_Stage = new CSTMEditInt(&NumericData[MotorSel][GUI_RUC_Stage],"%3d",3,pGUI_RevupTuning,230,20);
    pGUI_RUC_Stage->SetBounds(0,(*pUI_GetReg)(g_oUI,MC_PROTOCOL_REG_RUC_STAGE_NBR) - 1);
    CSTMLabel* pLabel9_6 = new CSTMLabel("ms",pGUI_RevupTuning,140,20);
    CSTMLabel* pLabel11_6 = new CSTMLabel("rpm",pGUI_RevupTuning,140,35);
    LCDI_GetSelectedRUCData(g_oUI, MotorSel, NumericData[MotorSel][GUI_RUC_Stage]);
    EVNT_EDIT_INT_ON_CHANGEVALUE(*pGUI_RUC_Stage, OnGUI_RUC_Stage_ChangeValue);
    EVNT_EDIT_INT_ON_CHANGEVALUE(*pGUI_RUC_Duration, OnGUI_RUC_Duration_ChangeValue);
    EVNT_EDIT_INT_ON_CHANGEVALUE(*pGUI_RUC_FinalSpeed, OnGUI_RUC_FinalSpeed_ChangeValue);
    EVNT_EDIT_INT_ON_CHANGEVALUE(*pGUI_RUC_FinalToruqe, OnGUI_RUC_FinalToruqe_ChangeValue);
    Page6.AddControl(pLabel9_6);
    Page6.AddControl(pLabel11_6);
    Page6.AddControl(pGUI_RevupTuning);
    Page6.AddControl(pLabel8_6);
    Page6.AddControl(pGUI_RUC_Duration);
    Page6.AddControl(pLabel10_6);
    Page6.AddControl(pGUI_RUC_FinalSpeed);
    Page6.AddControl(pLabel12_6);
    Page6.AddControl(pGUI_RUC_FinalToruqe);
    Page6.AddControl(pLabel13_6);
    Page6.AddControl(pGUI_RUC_Stage);
  }
  
  EVNT_EDIT_INT_ON_CHANGEVALUE(*pGUI_STO_C1, OnIntText_ChangeValue);
  EVNT_EDIT_INT_ON_CHANGEVALUE(*pGUI_STO_C2, OnIntText_ChangeValue);
  
  Page6.SetActiveNextControl();
}

void LCDI_ShowPage7(void)  // CORDIC
{
  CSTMLabel* pLabel1_6;
  uint32_t hUICfg = (*pUI_GetSelectedMCConfig)(g_oUI);
  // Sensorless tuning
  if (MAIN_SCFG_VALUE(hUICfg) == UI_SCODE_STO_CR)
  {
    pLabel1_6 = new CSTMLabel("Sensorless tuning STO & CORDIC",&Page7, 0, 0);
  }
  if (AUX_SCFG_VALUE(hUICfg) == UI_SCODE_STO_CR)
  {
    pLabel1_6 = new CSTMLabel("Sensorless tuning STO & CORDIC (Aux)",&Page7, 0, 0);
  }
  CSTMGroup* pGUI_STO_CR;
  pGUI_STO_CR = new CSTMGroup("STO",145,90,&Page7,10,20);
  CSTMLabel* pLabel2_6 = new CSTMLabel("G1",pGUI_STO_CR,5,15);
  pGUI_STO_C1 = new CSTMEditInt(&NumericData[MotorSel][GUI_STO_CR_C1],"%6d",6,pGUI_STO_CR,5,30);
  CSTMLabel* pLabel3_6 = new CSTMLabel("G2",pGUI_STO_CR,80,15);
  pGUI_STO_C2 = new CSTMEditInt(&NumericData[MotorSel][GUI_STO_CR_C2],"%6d",6,pGUI_STO_CR,80,30);
  
  LCDI_CreateCommon();
  
  Page7.AddControl(pLabel1_6);
  Page7.AddControl(pGUI_STO_CR);
  Page7.AddControl(pLabel2_6);
  Page7.AddControl(pGUI_STO_C1);
  Page7.AddControl(pLabel3_6);
  Page7.AddControl(pGUI_STO_C2);
    
  // Monitor
  Page7.AddControl(pGUI_SpeedMonitor);
  Page7.AddControl(pLabel6_4);
  Page7.AddControl(pGUI_SpeedMeasured);
  Page7.AddControl(pLabel7_4);  
  pGUI_SpeedMeasured->SetFocusable(false);  
  Page7.AddControl(pGUI_StartStop);

  if (MAIN_SCFG_VALUE(hUICfg) == UI_SCODE_STO_CR)
  {
    CSTMGroup* pGUI_RevupTuning = new CSTMGroup("Rev up tuning",295,75,&Page7,10,115);
    CSTMLabel* pLabel8_6 = new CSTMLabel("Duration",pGUI_RevupTuning,10,20);
    pGUI_RUC_Duration = new CSTMEditInt(&NumericData[MotorSel][GUI_RUC_Duration],"%6d",6,pGUI_RevupTuning,80,20);
    pGUI_RUC_Duration->SetBounds(0,S16_MAX);
    CSTMLabel* pLabel10_6 = new CSTMLabel("End spd",pGUI_RevupTuning,10,35);
    pGUI_RUC_FinalSpeed = new CSTMEditInt(&NumericData[MotorSel][GUI_RUC_FinalSpeed],"%6d",6,pGUI_RevupTuning,80,35);
    CSTMLabel* pLabel12_6 = new CSTMLabel("End Iq",pGUI_RevupTuning,10,50);
    pGUI_RUC_FinalToruqe = new CSTMEditInt(&NumericData[MotorSel][GUI_RUC_FinalToruqe],"%6d",6,pGUI_RevupTuning,80,50);
    CSTMLabel* pLabel13_6 = new CSTMLabel("Stage",pGUI_RevupTuning,180,20);
    pGUI_RUC_Stage = new CSTMEditInt(&NumericData[MotorSel][GUI_RUC_Stage],"%3d",3,pGUI_RevupTuning,230,20);
    pGUI_RUC_Stage->SetBounds(0,(*pUI_GetReg)(g_oUI,MC_PROTOCOL_REG_RUC_STAGE_NBR) - 1);
    CSTMLabel* pLabel9_6 = new CSTMLabel("ms",pGUI_RevupTuning,140,20);
    CSTMLabel* pLabel11_6 = new CSTMLabel("rpm",pGUI_RevupTuning,140,35);
    LCDI_GetSelectedRUCData(g_oUI, MotorSel, NumericData[MotorSel][GUI_RUC_Stage]);
    EVNT_EDIT_INT_ON_CHANGEVALUE(*pGUI_RUC_Stage, OnGUI_RUC_Stage_ChangeValue);
    EVNT_EDIT_INT_ON_CHANGEVALUE(*pGUI_RUC_Duration, OnGUI_RUC_Duration_ChangeValue);
    EVNT_EDIT_INT_ON_CHANGEVALUE(*pGUI_RUC_FinalSpeed, OnGUI_RUC_FinalSpeed_ChangeValue);
    EVNT_EDIT_INT_ON_CHANGEVALUE(*pGUI_RUC_FinalToruqe, OnGUI_RUC_FinalToruqe_ChangeValue);
    Page7.AddControl(pLabel9_6);
    Page7.AddControl(pLabel11_6);
    Page7.AddControl(pGUI_RevupTuning);
    Page7.AddControl(pLabel8_6);
    Page7.AddControl(pGUI_RUC_Duration);
    Page7.AddControl(pLabel10_6);
    Page7.AddControl(pGUI_RUC_FinalSpeed);
    Page7.AddControl(pLabel12_6);
    Page7.AddControl(pGUI_RUC_FinalToruqe);
    Page7.AddControl(pLabel13_6);
    Page7.AddControl(pGUI_RUC_Stage);
  }
  
  EVNT_EDIT_INT_ON_CHANGEVALUE(*pGUI_STO_C1, OnIntText_ChangeValue);
  EVNT_EDIT_INT_ON_CHANGEVALUE(*pGUI_STO_C2, OnIntText_ChangeValue);
  
  Page7.SetActiveNextControl();
}

void OnGUI_FaultAck_Click(HANDLE_WIN hWin, uint32_t wParam)
{
  (*pUI_ExecCmd)(g_oUI,MC_PROTOCOL_CMD_FAULT_ACK);
}

void OnGUI_FaultAck_M1_Click(HANDLE_WIN hWin, uint32_t wParam)
{
  uint8_t bMotorSelTMP = (*pUI_GetReg)(g_oUI,MC_PROTOCOL_REG_TARGET_MOTOR);
  (*pUI_SetReg)(g_oUI,MC_PROTOCOL_REG_TARGET_MOTOR,M1);
  (*pUI_ExecCmd)(g_oUI,MC_PROTOCOL_CMD_FAULT_ACK);
  (*pUI_SetReg)(g_oUI,MC_PROTOCOL_REG_TARGET_MOTOR, bMotorSelTMP);
}

void OnGUI_FaultAck_M2_Click(HANDLE_WIN hWin, uint32_t wParam)
{
  uint8_t bMotorSelTMP = (*pUI_GetReg)(g_oUI,MC_PROTOCOL_REG_TARGET_MOTOR);
  (*pUI_SetReg)(g_oUI,MC_PROTOCOL_REG_TARGET_MOTOR,M2);
  (*pUI_ExecCmd)(g_oUI,MC_PROTOCOL_CMD_FAULT_ACK);
  (*pUI_SetReg)(g_oUI,MC_PROTOCOL_REG_TARGET_MOTOR, bMotorSelTMP);
}

void OnGUI_SpeedRampExec_Click(HANDLE_WIN hWin, uint32_t wParam)
{
  (*pUI_ExecSpeedRamp)(g_oUI,NumericData32[MotorSel][GUI_SpeedTarget],NumericData[MotorSel][GUI_SpeedRampDuration]);
}

void OnGUI_EncoderAlign_Click(HANDLE_WIN hWin, uint32_t wParam)
{
  (*pUI_ExecCmd)(g_oUI,MC_PROTOCOL_CMD_ENCODER_ALIGN);
}

void OnGUI_StartStop_Click(HANDLE_WIN hWin, uint32_t wParam)
{
  // Command based on actual set is performed before each motor start
  if (NumericDataU8[MotorSel][GUI_CtrlMode] == GUI_SPEED_MODE)
  {
    (*pUI_ExecSpeedRamp)(g_oUI,NumericData32[MotorSel][GUI_SpeedTarget],NumericData[MotorSel][GUI_SpeedRampDuration]);
  }
  else
  {
    switch (NumericDataU8[MotorSel][GUI_Currents_Input])
    {
    case 0:
      (*pUI_SetCurrentReferences)(g_oUI,NumericData[MotorSel][GUI_Iq_Ref],NumericData[MotorSel][GUI_Id_Ref]);
      break;
    case 1:
      (*pUI_SetCurrentReferences)(g_oUI,(int16_t)(NumericData[MotorSel][GUI_I_Ref]*sin((NumericData[MotorSel][GUI_Eps_Ref]*3.14)/180)),
                                        (int16_t)(NumericData[MotorSel][GUI_I_Ref]*cos((NumericData[MotorSel][GUI_Eps_Ref]*3.14)/180)));
      break;
    }
  }
  
  (*pUI_ExecCmd)(g_oUI,MC_PROTOCOL_CMD_START_STOP);
}

#ifdef LCD_UI_DUAL
void OnGUI_SpeedRampExec_M1_Click(HANDLE_WIN hWin, uint32_t wParam)
{
  uint8_t bMotorSelTMP = (*pUI_GetReg)(g_oUI,MC_PROTOCOL_REG_TARGET_MOTOR);
  (*pUI_SetReg)(g_oUI,MC_PROTOCOL_REG_TARGET_MOTOR,M1);
  (*pUI_ExecSpeedRamp)(g_oUI,NumericData32[M1][GUI_SpeedTarget],NumericData[M1][GUI_SpeedRampDuration]);
  (*pUI_SetReg)(g_oUI,MC_PROTOCOL_REG_TARGET_MOTOR, bMotorSelTMP);
}

void OnGUI_SpeedRampExec_M2_Click(HANDLE_WIN hWin, uint32_t wParam)
{
  uint8_t bMotorSelTMP = (*pUI_GetReg)(g_oUI,MC_PROTOCOL_REG_TARGET_MOTOR);
  (*pUI_SetReg)(g_oUI,MC_PROTOCOL_REG_TARGET_MOTOR,M2);
  (*pUI_ExecSpeedRamp)(g_oUI,NumericData32[M2][GUI_SpeedTarget],NumericData[M2][GUI_SpeedRampDuration]);
  (*pUI_SetReg)(g_oUI,MC_PROTOCOL_REG_TARGET_MOTOR, bMotorSelTMP);
}

void OnGUI_StartStop_M1_Click(HANDLE_WIN hWin, uint32_t wParam)
{
  uint8_t bMotorSelTMP = (*pUI_GetReg)(g_oUI,MC_PROTOCOL_REG_TARGET_MOTOR);
  (*pUI_SetReg)(g_oUI,MC_PROTOCOL_REG_TARGET_MOTOR,M1);
  
  // Command based on actual set is performed before each motor start
  if (NumericDataU8[M1][GUI_CtrlMode] == GUI_SPEED_MODE)
  {
    (*pUI_ExecSpeedRamp)(g_oUI,NumericData32[M1][GUI_SpeedTarget],NumericData[M1][GUI_SpeedRampDuration]);
  }
  else
  {
    switch (NumericDataU8[M1][GUI_Currents_Input])
    {
    case 0:
      (*pUI_SetCurrentReferences)(g_oUI,NumericData[M1][GUI_Iq_Ref],NumericData[M1][GUI_Id_Ref]);
      break;
    case 1:
      (*pUI_SetCurrentReferences)(g_oUI,(int16_t)(NumericData[M1][GUI_I_Ref]*sin((NumericData[M1][GUI_Eps_Ref]*3.14)/180)),
                                        (int16_t)(NumericData[M1][GUI_I_Ref]*cos((NumericData[M1][GUI_Eps_Ref]*3.14)/180)));
      break;
    }
  }
  
  (*pUI_ExecCmd)(g_oUI,MC_PROTOCOL_CMD_START_STOP);
  (*pUI_SetReg)(g_oUI,MC_PROTOCOL_REG_TARGET_MOTOR, bMotorSelTMP);
}

void OnGUI_StartStop_M2_Click(HANDLE_WIN hWin, uint32_t wParam)
{
  uint8_t bMotorSelTMP = (*pUI_GetReg)(g_oUI,MC_PROTOCOL_REG_TARGET_MOTOR);
  (*pUI_SetReg)(g_oUI,MC_PROTOCOL_REG_TARGET_MOTOR,M2);
  
  // Command based on actual set is performed before each motor start
  if (NumericDataU8[M2][GUI_CtrlMode] == GUI_SPEED_MODE)
  {
    (*pUI_ExecSpeedRamp)(g_oUI,NumericData32[M2][GUI_SpeedTarget],NumericData[M2][GUI_SpeedRampDuration]);
  }
  else
  {
    switch (NumericDataU8[M2][GUI_Currents_Input])
    {
    case 0:
      (*pUI_SetCurrentReferences)(g_oUI,NumericData[M2][GUI_Iq_Ref],NumericData[M2][GUI_Id_Ref]);
      break;
    case 1:
      (*pUI_SetCurrentReferences)(g_oUI,(int16_t)(NumericData[M2][GUI_I_Ref]*sin((NumericData[M2][GUI_Eps_Ref]*3.14)/180)),
                                        (int16_t)(NumericData[M2][GUI_I_Ref]*cos((NumericData[M2][GUI_Eps_Ref]*3.14)/180)));
      break;
    }
  }
  
  (*pUI_ExecCmd)(g_oUI,MC_PROTOCOL_CMD_START_STOP);
  (*pUI_SetReg)(g_oUI,MC_PROTOCOL_REG_TARGET_MOTOR, bMotorSelTMP);
}

void OnGUI_StartBoth_Click(HANDLE_WIN hWin, uint32_t wParam)
{
  uint8_t bMotorSelTMP = (*pUI_GetReg)(g_oUI,MC_PROTOCOL_REG_TARGET_MOTOR);
  (*pUI_SetReg)(g_oUI,MC_PROTOCOL_REG_TARGET_MOTOR,M1);
  (*pUI_ExecCmd)(g_oUI,MC_PROTOCOL_CMD_START_STOP);
  (*pUI_SetReg)(g_oUI,MC_PROTOCOL_REG_TARGET_MOTOR,M2);
  (*pUI_ExecCmd)(g_oUI,MC_PROTOCOL_CMD_START_STOP);
  (*pUI_SetReg)(g_oUI,MC_PROTOCOL_REG_TARGET_MOTOR, bMotorSelTMP);
}

void OnGUI_ExecBothRamp_Click(HANDLE_WIN hWin, uint32_t wParam)
{
  uint8_t bMotorSelTMP = (*pUI_GetReg)(g_oUI,MC_PROTOCOL_REG_TARGET_MOTOR);
  (*pUI_SetReg)(g_oUI,MC_PROTOCOL_REG_TARGET_MOTOR,M1);
  (*pUI_ExecSpeedRamp)(g_oUI,NumericData32[M1][GUI_SpeedTarget],NumericData[M1][GUI_SpeedRampDuration]);
  (*pUI_SetReg)(g_oUI,MC_PROTOCOL_REG_TARGET_MOTOR,M2);
  (*pUI_ExecSpeedRamp)(g_oUI,NumericData32[M2][GUI_SpeedTarget],NumericData[M2][GUI_SpeedRampDuration]);
  (*pUI_SetReg)(g_oUI,MC_PROTOCOL_REG_TARGET_MOTOR, bMotorSelTMP);
}
#endif
/******************* (C) COPYRIGHT 2011 STMicroelectronics *****END OF FILE****/
