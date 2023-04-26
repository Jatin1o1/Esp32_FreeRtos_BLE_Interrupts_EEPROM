#pragma once

#include "config.h"
#include "database.h"

#include <BLEDevice.h>
#include <BLEServer.h>
#include <BLEUtils.h>
#include <BLE2902.h>

BLEServer *pServer = NULL;
BLECharacteristic * pTxCharacteristic;
BLEAdvertising *pAdvertising = BLEDevice::getAdvertising();

bool deviceConnected = false;
bool oldDeviceConnected = false;
uint8_t txValue = 0;
short int  default_sends= 0;

#define SERVICE_UUID           "6E400001-B5A3-F393-E0A9-E50E24DCCA9E" // UART service UUID
#define CHARACTERISTIC_UUID_RX "6E400002-B5A3-F393-E0A9-E50E24DCCA9E"
#define CHARACTERISTIC_UUID_TX "6E400003-B5A3-F393-E0A9-E50E24DCCA9E"

class MyServerCallbacks: public BLEServerCallbacks {
    void onConnect(BLEServer* pServer) {
        deviceConnected = true;
        Serial.print("  App connected");
        default_sends = 0;
    };
    void onDisconnect(BLEServer* pServer) {
      deviceConnected = false;
      Serial.println("  App Disconnected");
      }
};

void check_data(String recv)   // ex: // "A_:10" is input
{
    String param = recv.substring(0, 3);
    param = recv.substring(0, 3);
    int value = 0;
    //"Lets say we are Updating parameter if got data from Bluetooth"
    if (param == "A_")   
    {                                     
        value = recv.substring(4).toInt(); 
        
        param_1=value;
        preferences.begin("DB1", false);
        preferences.putUInt("param_1", value);
        preferences.end();
    }  
    if (param == "B_")
    {                                      
        value = recv.substring(4).toInt(); 
        param_2=value;
        preferences.begin("DB1", false);
        preferences.putUInt("param_2", value);
        preferences.end();
    }
    if (param == "C_")
    {                                      
        value = recv.substring(4).toInt(); 
        param_3=value;
        
        preferences.begin("DB2", false);
        preferences.putUInt("param_3", value);
        preferences.end();
    
    }
    if (param == "D_")
    {                                      
        value = recv.substring(4).toInt(); 
        param_4=value;
        preferences.begin("DB2", false);
        preferences.putUInt("param_4", value);
        preferences.end();
    }
    if (param == "E_")
    {                                     
        value = recv.substring(4).toInt(); // Serial.println(Jat);
        if (value == 1){
            param_5=value;
            preferences.begin("DB3", false);
            preferences.putUInt("param_5", value);
            preferences.end();
        }
    }
    if (param == "F_")
    { 
        value = recv.substring(4).toInt();
        param_6=value;
        preferences.begin("DB3", false);
        preferences.putUInt("param_6", value);
        preferences.end();

    }
    {
        // Serial.print("received extra info from bluetooth  ");
        // Serial.println(recv);
    }
}

class MyCallbacks: public BLECharacteristicCallbacks {
    void onWrite(BLECharacteristic *pCharacteristic) {
      std::string rxValue = pCharacteristic->getValue();

      if (rxValue.length() > 0) {
        Serial.println("*********");
        Serial.print("Received Value: ");           Serial.println(rxValue.c_str());

        check_data(rxValue.c_str()); // callback sends data to dataFilter function
      }
    }
};

void initialize_BLE()
{
    BLEDevice::init("ESP32_BLE");
    
    // Create the BLE Server
    pServer = BLEDevice::createServer();
    pServer->setCallbacks(new MyServerCallbacks());

    // Create the BLE Service
    BLEService *pService = pServer->createService(SERVICE_UUID);

    // Create a BLE Characteristic
    pTxCharacteristic = pService->createCharacteristic(CHARACTERISTIC_UUID_TX,BLECharacteristic::PROPERTY_NOTIFY);

    pTxCharacteristic->addDescriptor(new BLE2902());
    BLECharacteristic * pRxCharacteristic = pService->createCharacteristic(CHARACTERISTIC_UUID_RX,BLECharacteristic::PROPERTY_WRITE);

    pRxCharacteristic->setCallbacks(new MyCallbacks());

    // Start the service
    pService->start();
    pAdvertising->addServiceUUID(SERVICE_UUID);
    pAdvertising->setScanResponse(false);
    //pAdvertising->setMinPreferred(0x06);  // functions that help with iPhone connections issue
    pAdvertising->setMinPreferred(0x0);  // set value to 0x00 to not advertise this parameter

    //pAdvertising->setMinPreferred(0x12);
    
    // Start advertising
    BLEDevice::startAdvertising();
    Serial.println("Waiting for ESP32_BLE app");
}

void  BLE_connection_check(){
    // disconnecting
    if (!deviceConnected && oldDeviceConnected) {
        delay(500); // give the bluetooth stack the chance to get things readys
        BLEDevice::startAdvertising();
        Serial.println("start advertising");
           
        default_sends=0;
        oldDeviceConnected = deviceConnected;
    }
    // connecting
    if (deviceConnected && !oldDeviceConnected) {
		// do stuff here on connecting
        oldDeviceConnected = deviceConnected;
    }
}

/*
  Author of this Code : Jatin Goyal
  @github : https://github.com/Jatin1o1
  @linkedIn : https://www.linkedin.com/in/jatin1o1/

  Description : BiolerPlate code  Esp32 + FreeRtos + BLE + Interrupts + DataBase

  License : Use Freely, and Say Thanks to me !!

*/
