#pragma once

/*
  Author of this Code : Jatin Goyal
  @github : https://github.com/Jatin1o1
  @linkedIn : https://www.linkedin.com/in/jatin1o1/

  Description : BiolerPlate code  Esp32 + FreeRtos + BLE + Interrupts + DataBase

  License : Use Freely, and Say Thanks to me !!
*/


// put your Configuration here.

#define DEBUG false


#define Output_1 15
#define Output_2 18
#define Output_3 19 

#define Input_1 39
#define Input_2 36
#define Input_3 35    // interrupt Pin to restart device
#define Input_4 21   // interrupt Pin to Handle Task 

bool Input_1_state = false;
bool Input_2_state = false;
bool Input_3_state = false;
bool Input_4_state = false;

#define Freq 240  // Define Frequency as 80MHz/ 160MHZ / 240MHZ

#define seconds() (millis()/1000)  // convert and return millis to seconds
#define minutes() (millis()/60000) // convert and return millis to minutes
