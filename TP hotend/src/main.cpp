#include <Arduino.h>
#include <thermistor.h>

//CODIFICACION TERMISTOR
#define PIN_Termistor 15 //pin del mega 2500 conectado al T2 de la ramps 1.4
#define Termistor 0 // modelo del termistor dentro de esta libreria, el termistor es una 100k ntc 3950

//definicion de los datos del termistor para la libreria
thermistor term(PIN_Termistor,Termistor);

//------------------------------------
//CODIFICACION HEATER
#define PIN_hotend 10 // output del hotend
float setpoint = 89;

//------------------------------------
//COMUNICACION POR PUERTO SERIE
//------------------------------------
//PWM (Pulse Width Modulation - Modulación de Ancho de Pulso)

void setup() {
  Serial.begin(9600);
}
float K =27;
void loop() {
  //lectura de temperatura con libreria 
  double temp=term.analog2temp();
  float error = setpoint -temp; 
  
  float u = K*error;
  if (u > 255){
    u=255;
  }
  if (u<0){
    u=0;
  }
  delay(2000);
  analogWrite(PIN_hotend, u); 
  
  Serial.print(0);
  Serial.print("\t");
  Serial.print(120);
  Serial.print("\t");
  Serial.println(temp);
  
}

