#include <MFRC522.h>
#include <SPI.h>

#define SAD 10
#define RST 5
#define VERDE 7 // led de color verde
#define ROJO 8  // led de color rojo 
#define BUZZER 9 
#define RELE 4

MFRC522 nfc(SAD, RST);

char val;

void setup() {
  pinMode(VERDE, OUTPUT);  // para el led verde de correcto
  pinMode(ROJO, OUTPUT);  // para el led rojo de incorrecto 
  pinMode(RELE, OUTPUT);
  pinMode(BUZZER, OUTPUT);  //para el buzzer 
  beep(50, 130);
  beep(50, 130);
  beep(50, 130);
  delay(100);
  SPI.begin();
  Serial.begin(9600);
  nfc.begin();
  }

void beep(int tiempo, int tono)
{
  tone(BUZZER, tono);
  delay(tiempo);                
  noTone(BUZZER);           
}

void loop() {
  byte status;
  byte data[MAX_LEN];
  byte serial[5];   
  int i, j, pos;

  status = nfc.requestTag(MF1_REQIDL, data);

  if (status == MI_OK) {
    status = nfc.antiCollision(data);
    memcpy(serial, data, 5);   
  	 Serial.print("a");
    for (i = 0; i < 5; i++) {
      Serial.write(serial[i]);
    }
    
   nfc.selectTag(serial);  //muestra una sola vez el numero 
   nfc.haltTag();
  }

  if(Serial.available()){
    val = Serial.read();
    Serial.println(val);     
    
    if(val== 'v'){ 
     digitalWrite(VERDE,HIGH);
      beep(250, 300);
     digitalWrite(VERDE,LOW);
    }
    else if(val == 'o') {
      digitalWrite(RELE, HIGH);
      digitalWrite(VERDE,HIGH);
      beep(250, 500);
      delay(1000);
      digitalWrite(VERDE,LOW);
      digitalWrite(RELE,LOW);
     
    }
    else{
     digitalWrite(ROJO,HIGH);
       beep(250, 20);
     digitalWrite(ROJO,LOW); 
    }
  } 
  delay(1000);
}
