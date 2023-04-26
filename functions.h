#pragma once
#include "config.h"  // contains pin definition 
#include "blue.h"


void initialize_peripherals(){
  pinMode(Input_1, INPUT); // initializing the Inputs
  pinMode(Input_2, INPUT);   
  pinMode(Input_3, INPUT);   
  pinMode(Input_4, INPUT);  
  
  pinMode(Output_1, OUTPUT);   // initializing the Outputs
  pinMode(Output_2, OUTPUT);
  pinMode(Output_3, OUTPUT);
  digitalWrite(Output_1,LOW);
  digitalWrite(Output_2,LOW);
  digitalWrite(Output_3,LOW);

  
  Serial.println(" \n\t Peripherals Initialised sucessfully");
}


void function_1(){
  digitalWrite(Output_2, HIGH);  
  digitalWrite(Output_3, LOW);
  delay(40);        
  digitalWrite(Output_2, LOW);
  digitalWrite(Output_3, LOW); 
  Serial.println("\n\t function_1 executed");
}
void function_2(){
  digitalWrite(Output_2, LOW);  
  digitalWrite(Output_3, HIGH);
  delay(40);        
  digitalWrite(Output_2, LOW);
  digitalWrite(Output_3, LOW);
  Serial.println("\n\t function_2 executed");
}

/*
  Author of this Code : Jatin Goyal
  @github : https://github.com/Jatin1o1
  @linkedIn : https://www.linkedin.com/in/jatin1o1/

  Description : BiolerPlate code  Esp32 + FreeRtos + BLE + Interrupts + DataBase

  License : Use Freely, and Say Thanks to me !!
*/