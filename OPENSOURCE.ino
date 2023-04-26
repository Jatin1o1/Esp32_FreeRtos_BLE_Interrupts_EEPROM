
#include "config.h"         // contains pin definition
#include "blue.h"
#include "functions.h"
#include "database.h"
#include "soc/soc.h"
#include "soc/rtc_cntl_reg.h"

//#include <FreeRTOS.h>

TaskHandle_t Checking_func;
TaskHandle_t Runner_func;

//Taskhandle_t Timer_second;

  
void setup()
{
  Serial.begin(115200);
  
  WRITE_PERI_REG(RTC_CNTL_BROWN_OUT_REG, 0); //disable burnout  detector


  setCpuFrequencyMhz(Freq);   // setfrequency
  delay(1000);
   
  Serial.print("CPU Freq = ");   Serial.print(getCpuFrequencyMhz()); Serial.println(" MHz\n\n\n");
  
  
  // initialize code
  initialize_BLE();
  Serial.println("The device started, now you can pair it with bluetooth APP!");
  Read_saved_values();
  initialize_peripherals(); 

  
  xTaskCreatePinnedToCore( Checking_functions, "Checking_func", 2048,  NULL, 1, &Checking_func, 0); // core 0 tasks
  xTaskCreatePinnedToCore( runner, "runner", 4096,  NULL, 1, &Runner_func, 1); //  core 1 tasks

  attachInterrupt(digitalPinToInterrupt(Input_4),INTR_fx, CHANGE);  // attaching Input_4 to Interrupt
  attachInterrupt(digitalPinToInterrupt(Input_3),Restart, HIGH);  // attaching Input_4 to Interrupt


  delay(1000);    digitalWrite(Output_1, HIGH);
  delay(200);     digitalWrite(Output_1, LOW);
  delay(200);     digitalWrite(Output_1, HIGH);
  delay(200);     digitalWrite(Output_1, LOW);

}
//Interrupt Function (ISR)
void INTR_fx() {
  Input_4_state= digitalRead(Input_4);  

  if (!Input_4_state){    // Input High, Suspends task
    vTaskSuspend( Runner_func);   // suspends a tasks
    Serial.println("Runner task is halted");  
  }
  else{  // Input High, run task
    vTaskResume( Runner_func);
    Serial.println("Runing task is Resumed"); 
  }
}
void Restart() {
  noInterrupts ();  // stops the RTC Iterrupts, also Stops the Millis timer when restarting
  ESP.restart();
}

unsigned long previousMillis = 0;
void loop() {
  // you can remove everything from  loop 

  unsigned long currentMillis = millis();
  String Defaults;
  if (currentMillis - previousMillis >= 2000)
  {
    previousMillis = currentMillis; 
    if (deviceConnected){
      
        if ( default_sends < 5){   // send saved paramters value to App for 5 times, when connected

        Serial.print("\t\t\t\t\t DEF Send : ");
        Defaults =  ">*,DEF," +     
                    String(param_1)  + "," +
                    String(param_2)  + "," +
                    String(param_3)  + "," + 
                    String(param_4)  + "," + 
                    String(param_5)  + "," +
                    String(param_6)  + "," +
                    String(param_7)  + "," +
                    String(param_8)  + "," +
                    String(param_9)  + "," +
                    String(param_10) + ", < " ;

        pTxCharacteristic->setValue(Defaults.c_str());             pTxCharacteristic->notify();  
        Serial.println(Defaults);
        default_sends +=1 ;  
        }    

        // data that will be sent regularly
        String Final_msg= ">*, param_1:" + String(param_1)+ "device running , <";

        pTxCharacteristic->setValue(Final_msg.c_str());             pTxCharacteristic->notify(); 
          
    }
  
  }
}

// Tasks  

void runner( void * pvParameters){  
  while (true) {
    
    if (DEBUG) {   Serial.println("\t\t\t  RUNNER TASK called");    
      }

    if (true)  {
      //Serial.println("loop 1 in runner task ");
      Serial.print("Task Running for : ");
      Serial.print(minutes() );
      Serial.print(" Minutes | ");
      Serial.print(seconds());
      Serial.println(" Seconds");
    }

    vTaskDelay(1000 / portTICK_RATE_MS);  // 1 seconds delay
  }
}

void Checking_functions( void * pvParameters){
  while (true) {
    if (DEBUG) {
      Serial.println("\t\t\t CHECK TASK called");
    }

    //Input_1_state = digitalRead(Input_1); 
    //Input_2_state = digitalRead(Input_2); 
    //Input_3_state = digitalRead(Input_3); 
    
    BLE_connection_check();

    vTaskDelay(500 / portTICK_RATE_MS);  // 0.5 seconds delay
    
  }
}
/*
  Author of this Code : Jatin Goyal
  @github : https://github.com/Jatin1o1
  @linkedIn : https://www.linkedin.com/in/jatin1o1/

  Description : BiolerPlate code  Esp32 + FreeRtos + BLE + Interrupts + EEPROM (Flash Memory)

  License : Use Freely, and Say Thanks to me !!
*/
