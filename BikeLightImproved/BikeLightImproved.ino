const int ButtonPin = 2;
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
    Serial.begin(9600);
}

void Sweep(){
    int i;
    Serial.print("Sweep\n");
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
  Serial.print("Colors\n");
  for (i = 0; i < 3; ++i){
      digitalWrite(13 - 2*i, HIGH);
       digitalWrite(13 - 6 - 2*i, HIGH);
       delay(freq);
       digitalWrite(13-2*i, LOW);
       digitalWrite(13-6 -2*i, LOW);
  }
}


void loop(){
    Serial.print(i);
    switch (i){
      case 0: Sweep(); break;
      case 1: SOS(); break;
      case 2: Colors(); break;
      case 3: break;
    }
    Serial.print("\n");
    if ( digitalRead(ButtonPin) == HIGH){
        Serial.print("Button Read!\n");
        i++;
        Serial.print(i);
        if (i > 3) i = 0;
        delay(1000);
    }
    
}

