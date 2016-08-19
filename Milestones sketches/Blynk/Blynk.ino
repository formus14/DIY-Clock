#include "blynk/blynk.h" 

char auth[] =  "Put your Auth Token Here"; 
void setup() { 
  Serial.begin(9600); 
  Blynk.begin(auth); 
  pinMode(D7, OUTPUT); 
  } 
  
 void loop() { 
  Blynk.run(); 
  }