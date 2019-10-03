#include<SoftwareSerial.h>
String datoA = "COCA";
String datoB = "PERRO";
String datoS;
String arre;

int push12 = 12;

void setup() {
  // put your setup code here, to run once:
  pinMode(push12, INPUT);
  Serial.begin(115200);
  Serial.println("Comunicacion serial inicializada");
  Serial.println(81);//imprimir en decimal en pc
  Serial.println(81,DEC);//imprime en formato decimal al puerto serial
  Serial.println(81,OCT);//formato octal
  Serial.println(81,BIN);//formato binario
  Serial.write(81);//envia el valor como byte, 81 en ascii es igual a 81
  Serial.println();
  datoS = datoA + datoB;
}

void loop() {
  // put your main code here, to run repeatedly:
  
  if(Serial.available()>0){
      char dato=Serial.read();
      Serial.print(dato);
      arre += dato;
    }
  if(datoS == "COCAPERRO"){
      Serial.println("Si se puede sumar cadenas");
      datoS = "x";
    }

  if(arre == "_gato"){
      Serial.print("si se puede acumular caracter  por caracter, arre es = gato :)");
      arre = "_";
    }
  /*
  if((digitalRead(push12)) == 1){
      Serial.print(arre);
    }*/
  
   

  
  
}
