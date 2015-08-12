/**
  @page PI parameters and main/aux sensor type

  @verbatim
  ******************** (C) COPYRIGHT 2012 STMicroelectronics *******************
  * @file    PI Regulation and Sensor type/readme.txt 
  * @author  Motor Control Team - System Lab 
  * @version 4.0.0
  * @date    28-May-2014 10:45
  * @brief   How to change the PI parameters and FOC sensors on the fly
  ******************************************************************************
  *
  * Licensed under ST Liberty SW License Agreement V2, (the "License");
  * You may not use this file except in compliance with the License.
  * You may obtain a copy of the License at:
  *
  *        http://www.st.com/software_license_agreement_liberty_v2
  *
  * Unless required by applicable law or agreed to in writing, software 
  * distributed under the License is distributed on an "AS IS" BASIS, 
  * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
  * See the License for the specific language governing permissions and
  * limitations under the License.
  *
  ******************************************************************************
  @endverbatim

@par Example Description 

This example describes how to use the API of Motor Control library to change 
the PI parameters (KP/KI) and control sensor type (Sensorless/Hall/Encoder..) on 
the fly.

The motor starts with the main sensor configured as sensorless (observer + PLL) 
and a speed ramp defined by two variables speed_first_valueRPM and speed_firstramp_duration 
editable by the user respectively 3000 RPM and 2000 msec by default. The KP and KI values 
for Speed Loop PI regulator are set by the default values of workbench file.
After a fixed time (COUNT_MAX) the sensor type is changed in Hall sensor on the 
fly with new values of KP/KI parameters and new speed ramp is generated (speed_second_valueRPM
= 400 RPM and speed_secondramp_duration= 2000msec). When the counter value reaches the 
time  STOP_DURATION, the state machine restarts with the main sensor and default values for 
Speed loop PI Regulator.

MC-Lib API used:

- PI_GetDefaultKP()
- PI_GetDefaultKI()
- PI_SetKP
- PI_SetKI
- FOC_SetSpeedSensor()
- MCI_ExecSpeedRamp()
- MCI_StartMotor()
- MCI_StopMotor()

@par Directory contents 

  - PI Regulation and Sensor type/PI_Sensor_onFLY_F1.c     Example configuration file

@par Hardware and Software environment 

  - This example runs on STM32F1xx Devices.
  
  - This example has been tested with STM3210E-EVAL and MB459 with Shinano motor and 
    it can be easily tailored to any other development board.

  - STM3210E-EVAL Set-up

@par How to use it ? 

In order to make the program work, you must do the following:

 - Use the ST Motor Control Workbench application to configure this
   STM32 PMSM FOC library v4.0 opening the WB file created for STM3210E-EVAL 
 - From IAR application open the workspace file named as "STM32F10x_Example"
 - Select the right example from drop box menu
 - Press F8 to batch-build the entire workspace (select a proper project configuration, 
   according to the uC part in use);
 - Read the messages window and download the firmware;
 - Run the example

 * <h3><center>&copy; COPYRIGHT STMicroelectronics</center></h3>
 */
