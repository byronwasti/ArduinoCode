const int ButtonPin = 2;
const int analogInPin = A0;
int sensorValue = 0;
int STATE;
int freq = 100;

unsigned long previousMillis = 0;
unsigned long currentMillis;

int LEDstate = LOW;

void setup(){
    pinMode(13, OUTPUT);
    pinMode(11, OUTPUT);
    pinMode(9, OUTPUT);
    pinMode(7, OUTPUT);
    pinMode(5, OUTPUT);
    pinMode(3, OUTPUT);
    pinMode(ButtonPin, INPUT);
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


void IN_OUTS(){
  int i;
  
  if( currentMillis - previousMillis >= freq){
    previousMillis = currentMillis;
    if( LEDstate == LOW){
        LEDstate = HIGH;
        i++;
        if(i > 2) i = 0;
    }
    else LEDstate = LOW;
  }
  
  
  
}

void Colors(){
  static int i;
  
  if( currentMillis - previousMillis >= freq){
      previousMillis = currentMillis;
      if (LEDstate == LOW){
        LEDstate = HIGH;
        i++;
        if(i>2) i = 0;
      }
      else LEDstate = LOW;
  }
  
  digitalWrite(13 - 2*i, LEDstate);
  digitalWrite(13 - 6 - 2*i, LEDstate);
}

void Sweep(){
  static int i;
   
   if(currentMillis - previousMillis >= freq){
        previousMillis = currentMillis;
        //digitalWrite(13, HIGH);
        if (LEDstate == LOW) {
            LEDstate = HIGH;
            i++;
            if (i > 5) i = 0;
        }
        else LEDstate = LOW;
    }
  digitalWrite( 13 - 2*i, LEDstate); 
}

void loop(){
  currentMillis = millis();
  
  sensorValue = analogRead(analogInPin);
  freq = map(sensorValue, 0, 1023, 10, 1000);
 
 
    switch (STATE){
      case 0: Sweep(); break;
      case 1: Colors(); break;
      case 2: InOut(); break;
      case 3: OutIn(); break;
      case 4: SOS(); break;
      default: break;
    }     

    if ( digitalRead(ButtonPin) == HIGH){
        STATE++;
        if (STATE > 5) STATE = 0;
        delay(1000);
    }

    
}

