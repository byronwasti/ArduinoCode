const int ButtonPin = 2;
const int analogInPin = A0;
int sensorValue = 0;
int i;
int freq = 100;

void setup(){
    pinMode(13, OUTPUT);
    pinMode(11, OUTPUT);
    pinMode(9, OUTPUT);
    pinMode(7, OUTPUT);
    pinMode(5, OUTPUT);
    pinMode(3, OUTPUT);
    pinMode(ButtonPin, INPUT);
}

void Sweep(){
    int i;
     for ( i = 0; i < 6; ++i){
        digitalWrite( 13 - 2*i, HIGH);
        delay(freq);
        digitalWrite(13 - 2*i, LOW);
    }
}

void AllOn( int D){
  int i;
  for (i = 3; i < 13; i += 2){
      digitalWrite(i, HIGH);
  }
  delay(D);
  for(i = 3; i < 13; i += 2){
      digitalWrite(i, LOW);
  }
  delay(D);
}
  

void SOS(){
  int i;
  for ( i = 0; i < 3; i++){
      AllOn(100);
  }
  for (i = 0; i < 3; i++){
    AllOn(500);
  }
  for(i = 0; i < 3; i++){
    AllOn(100);
  }   
  delay(1000);
}

void Colors(){
  int i;
  for (i = 0; i < 3; ++i){
      digitalWrite(13 - 2*i, HIGH);
       digitalWrite(13 - 6 - 2*i, HIGH);
       delay(freq);
       digitalWrite(13-2*i, LOW);
       digitalWrite(13-6 -2*i, LOW);
  }
}

void OutIn(){
    int i;
    for (i =0; i < 3; ++i){
        switch(i){
            case 0: 
                digitalWrite(13, HIGH);
                digitalWrite(3, HIGH);
                delay(freq);
                digitalWrite(13, LOW);
                digitalWrite(3,LOW);
            case 1:
                digitalWrite(11, HIGH);
                digitalWrite(5, HIGH);
                delay(freq);
                digitalWrite(11, LOW);
                digitalWrite(5,LOW);
            case 2:
                digitalWrite(9, HIGH);
                digitalWrite(7, HIGH);
                delay(freq);
                digitalWrite(9, LOW);
                digitalWrite(7,LOW);
        }
    }    
    delay(freq);
}

void InOut(){
    int i;
    for (i =0; i < 3; ++i){
        switch(i){
            case 2: 
                digitalWrite(13, HIGH);
                digitalWrite(3, HIGH);
                delay(freq);
                digitalWrite(13, LOW);
                digitalWrite(3,LOW);
            case 1:
                digitalWrite(11, HIGH);
                digitalWrite(5, HIGH);
                delay(freq);
                digitalWrite(11, LOW);
                digitalWrite(5,LOW);
            case 0:
                digitalWrite(9, HIGH);
                digitalWrite(7, HIGH);
                delay(freq);
                digitalWrite(9, LOW);
                digitalWrite(7,LOW);
        }
    }    
    delay(freq);
}

void loop(){
  sensorValue = analogRead(analogInPin);
  freq = map(sensorValue, 0, 1023, 10, 1000);
  
    switch (i){
      case 0: Sweep(); break;
      case 1: OutIn(); break;
      case 2: InOut(); break;
      case 3: Colors(); break;
      case 4: SOS(); break;
      case 5: break;
    }
    if ( digitalRead(ButtonPin) == HIGH){
        i++;
        if (i > 5) i = 0;
        delay(1000);
    }
    
}

