#include <SoftwareSerial.h>
SoftwareSerial quectel(8,9);

char numero_cell[]="4661016976";
int pulsador = 12;
int led = 11;
int valor;

void setup() {
  // put your setup code here, to run once:
  pinMode(pulsador, INPUT);
  pinMode(led, OUTPUT);
  Serial.begin(115200);
  quectel.begin(115200);
  Serial.print("Comunicaion con quectel");
}

void loop() {
  // put your main code here, to run repeatedly:
  while(1){
    valor = digitalRead(pulsador);
    if (valor == LOW ){
        while(valor == LOW){;}
        quectel.println("AT+CMGF=1");
        delay(2000);
        quectel.println("AT+CMGS=");
        quectel.println((char)34);
        quectel.println(numero_cell);
        quectel.println((char)34);
        delay(200);
        quectel.print("Lets do it!!");
        quectel.print((char)26);
        Serial.print("Lets do it!!\n");

        for(int i=0; i<=20; i++){
            digitalWrite(led,HIGH);
            delay(80);
            digitalWrite(led,LOW);
            delay(80);
          }
      }
  }

}
