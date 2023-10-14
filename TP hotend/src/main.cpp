#include <Arduino.h>
#include <thermistor.h> //importamos la libreria necesaria para la lectura de la temperatura (mediante el termistor)

//CODIFICACION TERMISTOR
//definicion de los pines usados
#define PIN_Termistor 15 //pin del mega 2500 conectado al T2 de la ramps 1.4
#define Termistor 0 // modelo del termistor dentro de esta libreria, el termistor es una 100k ntc 3950

//definicion de los datos del termistor para la libreria
thermistor term(PIN_Termistor,Termistor);

//------------------------------------
//CODIFICACION HEATER
#define PIN_hotend 10 // output del hotend
float setpoint = 89; //definimos el setpoint en 89*C

void setup() {
  Serial.begin(9600); 
}

//definimos el valor del controlador proporcional
float K =27; //los valores usados en las distintas experiencias fueron: 2, 15 y 27

void loop() {
  //lectura de temperatura con libreria 
  double temp=term.analog2temp();
  float error = setpoint -temp; //calculo del error
  
  float u = K*error; //definimos la acción de control/variable manipulada

  //restricción de la señal de salida del microcontrolador (acotada entre 0 y 255)
  if (u > 255){
    u=255;
  }
  if (u<0){
    u=0;
  }

  delay(2000); //establecemos cada cuanto repetir el loop.
  analogWrite(PIN_hotend, u); //se le envia al hotend la señal u 
  
  //especificaciones del grafico para ver la rta temporal de la temperatura en arduino
  Serial.print(0);
  Serial.print("\t");
  Serial.print(120);
  Serial.print("\t");
  Serial.println(temp); 
  
}



