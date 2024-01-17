#include <SoftwareSerial.h>

long            _delayTX            = 2000;
unsigned long   _previousTXMillis   = 0;

const byte _txPin = 27;
const byte _rxPin = 28;

SoftwareSerial mySerial (_rxPin, _txPin);

const byte tailleMessageMax = 50;
char message[tailleMessageMax + 1]; // +1 car on doit avoir un caractère de fin de chaîne en C, le '\0'

const char marqueurDeFin = '#';

void setup() {
  pinMode(_rxPin, INPUT);
  pinMode(_txPin, OUTPUT);

  Serial1.begin( 115200 );
  mySerial.begin(115200);
}

boolean ecouter()
{
  static byte indexMessage = 0; // static pour se souvenir de cette variable entre 2 appels consécutifs. initialisée qu'une seule fois.
  boolean messageEnCours = true;

  while (mySerial.available() && messageEnCours) {
    int c = mySerial.read();
    if (c != -1) {
      Serial.print(F("Octet lu: 0x")); Serial.print(c, HEX); // ici c est un entier, on affiche le code ASCII en Hexadécimal
      Serial.print(F("\t[")); Serial.print((char) c); Serial.println(F("]"));
      switch (c) {
        case marqueurDeFin:
          Serial.println(F("Fin de chaine"));
          message[indexMessage] = '\0'; // on termine la c-string
          indexMessage = 0; // on se remet au début pour la prochaine fois
          messageEnCours = false;
          break;
        default:
          if (indexMessage <= tailleMessageMax - 1) message[indexMessage++] = (char) c; // on stocke le caractère et on passe à la case suivante
          else Serial.println(F("j'ignore!"));
          break;
      }
    }
  }
  return messageEnCours;
}

void loop() {
  if (! ecouter()) {
    // on a reçu le marqueur de fin
    Serial.print(F("Phrase: [")); Serial.print(message); Serial.println(F("]"));
  } 
  // while (mySerial.available() > 0) {
  //   Serial.println("Received");
	// 	Serial.println(mySerial.readStringUntil('\n'));
	// }


  unsigned long currentMillis = millis();
  if (currentMillis - _previousTXMillis >= _delayTX) {
    _previousTXMillis = currentMillis;
    
    Serial1.println("Send data");
    //mySerial.println(45);
    mySerial.print('a');
    mySerial.print(45);
    mySerial.print('a');
    mySerial.print('#');
  }
}
