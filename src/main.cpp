/*

TITRE          : Amplificateur LED avec Transistor
AUTEUR         : Franck Nkeubou Awougang
DATE           : 26/02/2022
DESCRIPTION    : programme permetttant de controler l'intensité d'une LED en utilisant un Rotation
				 sensor pour contrôler l'intenseité de la LED en utilisant le transistor.
VERSION        : 0.0.1

*/

#include <Arduino.h>
#include "Timer.h"

const int LED_PIN = 3;
const int PIN_ROTATION_SENSOR = A1;

Timer Time;
short int Delay = 2000;
short int LedValue = 0;
short int LastLedValue = 0;
short int MaxValueBroche = 1023;
float TensionValue = 0;
float TensionMaximale = 3.3;

void setup() {
	// put your setup code here, to run once:
	Serial.begin(9600);
	pinMode(LED_PIN, OUTPUT); //On configure notre Arduino.
	pinMode(PIN_ROTATION_SENSOR, INPUT); //On configure notre Arduino.
	// pinMode(Button, INPUT);//On configure l'entrée du signal du bouton à la broche correspondante.
	Time.startTimer(Delay);
}

void loop() {
	short int Value = analogRead(PIN_ROTATION_SENSOR); // capture de la valeur du capteur.
	LedValue = map(Value, 0, 1023, 0, 255); // mapping de la valeur pour une sortie analogue.
	// Faisons la conversion pour obtenir la tension correspondante.
	TensionValue = (Value * TensionMaximale) / MaxValueBroche;
	if (LedValue - LastLedValue >= 3 || LedValue - LastLedValue <= -3){
		LastLedValue = LedValue;
		analogWrite(LED_PIN, LedValue);
		Serial.println((String) "LED Value = " + Value + "\nTension = " + TensionValue + " V\n");
	}
	delay(1);
}