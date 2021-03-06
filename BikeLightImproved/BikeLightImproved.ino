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

/*
int S ( void ){
    static int i;

    if (currentMillis - previousMillis > freq){
        previousMillis = currentMillis;
        i++;
        if ( i % 2) LEDstate = HIGH;
        else LEDstate = LOW;
        
        if ( i > 5){
            i = 0;
            return 1;
        }
    }
    return 0;
}

int O ( void ){
    static int i;

    if( currentMillis - previousMillis > freq){
        previousMillis = currentMillis;
        i++;
        if ( i % 4 == 0 ) LEDstate = LOW;
        else LEDstate = HIGH;
        if ( i > 11){
            i = 0;
            return 1;
        }
    }
    return 0;
}

void SOS(){
    static int j, k = 0;
    switch(j) {
        case 0: k = S(); break;
        case 1: k = O(); break;
        case 2: k = S(); break;
    }
    if (k == 1){
        k = 0;
        j++;
        if (j > 2) {
            j = 0;
            return;
        }
    }
}


void IN_OUTS(int direc){
  int i;
  int a, b, c;
  if (direc == 0){
         a = 0;
         b = 1;
         c = 2;
    }
    else {
        a = 2;
        b = 1;
        c = 0;
    }
  
  if( currentMillis - previousMillis >= freq){
    previousMillis = currentMillis;
    if( LEDstate == LOW){
        LEDstate = HIGH;
        i++;
        if(i > 2) i = 0;
    }
    else LEDstate = LOW;
  }
  const int x =a, y = b, z = c;
  switch( i ){
    case 0:
        digitalWrite(13, LEDstate);
        digitalWrite(3, LEDstate);
    case 1:
        digitalWrite(11, LEDstate);
        digitalWrite(5, LEDstate);
    case 2:
        digitalWrite(9, LEDstate);
        digitalWrite(7, LEDstate);
  }
  
}
*/

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
      //case 2: IN_OUTS(0); break;
      //case 3: IN_OUTS(1); break;
//      case 4: SOS(); break;
      default: break;
    }     

    if ( digitalRead(ButtonPin) == HIGH){
        STATE++;
        if (STATE > 5) STATE = 0;
        delay(1000);
    }
}

