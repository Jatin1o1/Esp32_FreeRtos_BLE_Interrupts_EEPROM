#pragma once
#include <Preferences.h>

// put your database  functionality here

Preferences preferences;

uint8_t DP_delay ;
unsigned int param_1 ;
unsigned int param_2 ;
unsigned int param_3;
unsigned int param_4;
unsigned int param_5;
unsigned int param_6;
unsigned int param_8 ;
unsigned int param_9;


float param_7;
float param_10;

void Read_saved_values(){

// one database can store at max two values, if more than one values, use multiple databases

  preferences.begin("DB1", false); param_1 = preferences.getUInt("param_1",5);preferences.end();    
  preferences.begin("DB1", false); param_2 = preferences.getUInt("param_2", 5);preferences.end();
  preferences.begin("DB2", false); param_3 = preferences.getUInt("param_3", 30);preferences.end();
  preferences.begin("DB2", false); param_4 = preferences.getUInt("param_4", 120);preferences.end();  
  preferences.begin("DB3", false); param_5 = preferences.getUInt("param_5", 1);  preferences.end();
  preferences.begin("DB3", false); param_6 = preferences.getUInt("param_6", 1);preferences.end();
  preferences.begin("DB4", false); param_7 = preferences.getFloat("param_7", 1);preferences.end();  
  preferences.begin("DB4", false); param_8 = preferences.getUInt("param_8", 0);preferences.end();
   
  preferences.begin("DB5", false); param_9 = preferences.getUInt("param_9", 0);preferences.end();
  preferences.begin("DB5", false); param_10 = preferences.getFloat("param_10", 10);preferences.end();

  Serial.print("param_1  : "); Serial.println(param_1);
  Serial.print("param_2  : "); Serial.println(param_2);
  Serial.print("param_3  : "); Serial.println(param_3);
  Serial.print("param_4  : "); Serial.println(param_4);
  Serial.print("param_5  : "); Serial.println(param_5);
  Serial.print("param_6  : "); Serial.println(param_6);
  Serial.print("param_7  : "); Serial.println(param_7);
  Serial.print("param_8  : "); Serial.println(param_8);
  Serial.print("param_9  : "); Serial.println(param_9);
  Serial.print("param_10 : "); Serial.println(param_10);

}
