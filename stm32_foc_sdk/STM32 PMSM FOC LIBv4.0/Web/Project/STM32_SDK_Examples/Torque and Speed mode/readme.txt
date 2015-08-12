/**
  @page Torque and Speed mode

  @verbatim
  ******************** (C) COPYRIGHT 2012 STMicroelectronics *******************
  * @file    Torque and Speed mode/readme.txt 
  * @author  Motor Control Team - System Lab 
  * @version 4.0.0
  * @date    28-May-2014 10:45
  * @brief   How to generate a PWM signal according with the electrical motor speed
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

This example describes how to use the API in order to change the FOC control mode 
between Speed and Torque mode.
The motor starts in torque mode with a ramp defined by a torque (torque_value) and 
a torque ramp duration (torque_duration). When the mechanical speed goes above the
threshold (speed_threshold) the motor moves in Speed Control with a its ramp defined
by speed_target and speed_duration.
 
MC-Lib API used:

- MCI_ExecTorqueRamp()
- MCI_StartMotor()
- SPD_GetAvrgMecSpeed01Hz()
- MCI_ExecSpeedRamp()

@par Directory contents 

  - Torque and Speed mode/TqSpeedMode_F1     Example configuration file

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
