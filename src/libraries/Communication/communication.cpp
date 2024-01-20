#include "communication.h"

// SoftwareSerial mySerial (rxPin, txPin);

Communication::Communication(int rxPin, int txPin) : _serial(rxPin, txPin) {
	_rxPin = rxPin;
	_txPin  = txPin;
}

void Communication::setup() {
    _tailleMessageMax = 50;
    _message[_tailleMessageMax + 1]; // +1 car on doit avoir un caractère de fin de chaîne en C, le '\0'
    // _marqueurDeFin = '#';

    Serial.println(F("Communication::Setup()"));
    pinMode(_rxPin, INPUT);
    pinMode(_txPin, OUTPUT);
    _serial.begin(115200);
}

bool Communication::listen() {
    static byte indexMessage = 0; // static pour se souvenir de cette variable entre 2 appels consécutifs. initialisée qu'une seule fois.
    boolean messageEnCours = true;

    while (_serial.available() && messageEnCours) {
        int c = _serial.read();
        if (c != -1) {
            // Serial.print(F("Octet lu: 0x")); Serial.print(c, HEX); // ici c est un entier, on affiche le code ASCII en Hexadécimal
            // Serial.print(F("\t[")); Serial.print((char) c); Serial.println(F("]"));
            switch (c) {
            case '#':
                // Serial.println(F("Fin de chaine"));
                _message[indexMessage] = '\0'; // on termine la c-string
                indexMessage = 0; // on se remet au début pour la prochaine fois
                messageEnCours = false;
                break;
            default:
                if (indexMessage <= _tailleMessageMax - 1) _message[indexMessage++] = (char) c; // on stocke le caractère et on passe à la case suivante
                // else Serial.println(F("j'ignore!"));
                break;
            }
        }
    }
    return !messageEnCours;
}

char * Communication::getMessage() {
    return _message;
} 

void Communication::sendMessage(const char * message) {
    // Serial.println(_message);
    const char *p;
    p = message;
    while (*p) {
        // Serial.print(*p);
        _serial.print(*p);
        p++;
    }
    
    _serial.print(_marqueurDeFin);
    // Serial.println();
    // Serial.println(F("done"));
} 

void Communication::sendData(const uint8_t * dataType, int8_t data)
{
    //uint8_t* Order = (uint8_t*) &myOrder;
    _serial.write(dataType, sizeof(uint8_t));
    // _serial.write(data);
    // _serial.write(_marqueurDeFin);
}