

const int led11 = 11;
String megaDato;

void setup() {
    Serial.begin(115200);
    delay(50);
    pinMode(led11, OUTPUT);
  } 

void loop() {
    if(Serial.available()){
        String data = Serial.readStringUntil('\n');
        megaDato = data;
        Serial.print(data);
      }

    if(megaDato=='A'){digitalWrite(led11, HIGH);}
    else if (megaDato=='B') digitalWrite(led11, LOW);
      
  }
