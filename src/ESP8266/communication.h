#ifndef COMMUNICATION_H
#define COMMUNICATION_H

#include <Arduino.h>
#include <ArduinoJson.h>
#include <SoftwareSerial.h>

class Communication {
    private:
        int _rxPin;
        int _txPin;
        SoftwareSerial _serial;
        byte _tailleMessageMax;
        char _message[51];
        const char _marqueurDeFin = '#';
        
    public:
        Communication(int rxPin, int txPin);
        void setup();
        bool listen();
        char * getMessage();
        void sendMessage(const char * message);
};

#endif
