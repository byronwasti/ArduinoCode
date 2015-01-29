const int ButtonPin = 2;
const int analogInPin = A0;
int sensorValue = 0; // Value read-out of potentiometer
int STATE; // Which mode the program is in
int freq = 100; // Frequency of each mode

unsigned long previousMillis = 0;
unsigned long currentMillis;

int LEDstate = LOW; 

// Setting up 6 pins for output
// and 1 for input (the button)
void setup(){
    pinMode(13, OUTPUT);
    pinMode(11, OUTPUT);
    pinMode(9, OUTPUT);
    pinMode(7, OUTPUT);
    pinMode(5, OUTPUT);
    pinMode(3, OUTPUT);
    pinMode(ButtonPin, INPUT);
}


// Blips all of the LEDs on and off at
// the frequency specified by the potentiometer
void AllOn(){
  int j;
   
   // Turns off/on the LED.
   if(currentMillis - previousMillis >= freq){
        previousMillis = currentMillis;

        if (LEDstate == LOW) {
            LEDstate = HIGH;
        }
        else LEDstate = LOW;
    }
    
    // Writes all of the LEDs
    for( j = 3; j < 15; j+=2){
       digitalWrite( j, LEDstate); 
    }
  
}
  
// Setting up the S timing structure
// for the SOS mode functionality.
int S ( void ){
    static int i;

    if (currentMillis - previousMillis > freq){
        previousMillis = currentMillis;
        i++;

        // If i is a multiple of 2 it will
        // go high. 
        if ( i % 2) LEDstate = HIGH;
        else LEDstate = LOW;

        if ( i > 5){
            i = 0;
            return 1; // Returns a switch
                      // to next letter
        }
    }
    return 0; // Remain on same letter
}

// Setting up the O timing structure
// for the SOS mode functionality.
int O ( void ){
    static int i;

    if( currentMillis - previousMillis > freq){
        previousMillis = currentMillis;
        i++;

        // If i is a multiple of 4 it will
        // go low, giving "long" blips.
        if ( i % 4 == 0 ) LEDstate = LOW;
        else LEDstate = HIGH;

        if ( i > 11){
            i = 0;
            return 1; // Returns a switch
                      // to next letter
        }
    }
    return 0; // Remain on same letter
}

void SOS(){
    static int j, k = 0;

    // j specifies which letter is being used.
    switch(j) {
        case 0: k = S(); break;
        case 1: k = O(); break;
        case 2: k = S(); break;
    }

    // Sets up the structure to switch letters
    // if one of the letter functions returns
    // a switch state for k
    if (k == 1){
        k = 0;
        j++;
        if (j > 2) {
            j = 0;
            return;
        }
    }

    // Writes the current state to all of the LEDs
    int i;
    for (i = 3; i < 14; i+=2){
        digitalWrite(i, LEDstate);
    }
}


// 3 - 2 - 1 code,
// labeled here differently.
// Goes all on, middle 4 on,
// then middle 2 on,
// then all off.
void OUT_IN(){
  static int i;
  
  if( currentMillis - previousMillis >= freq){
    previousMillis = currentMillis;
    if( LEDstate == LOW){
        LEDstate = HIGH;
        i++;
        
        if(i > 3) i = 0;
    }
    else LEDstate = LOW;
  }
  
  // state of i determines LEDs being written
  switch(i){
      case 0: digitalWrite(13,LEDstate); digitalWrite(3,LEDstate);
      case 1: digitalWrite(11,LEDstate); digitalWrite(5,LEDstate);
      case 2: digitalWrite(9,LEDstate); digitalWrite(7,LEDstate);
  }
}

// Lights up the individual
// colors and sweeps through them.
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
  
  // Writes the colors (which are paired)
  digitalWrite(13 - 2*i, LEDstate);
  digitalWrite(13 - 6 - 2*i, LEDstate);
}


// Sweeps through all of the LEDs
// one by one. 
void Sweep(){
  static int i;
   
   if(currentMillis - previousMillis >= freq){
        previousMillis = currentMillis;
        if (LEDstate == LOW) {
            LEDstate = HIGH;
            i++;
            if (i > 5) i = 0;
        }
        else LEDstate = LOW;
    }

  // Writes the specified LED.
  digitalWrite( 13 - 2*i, LEDstate); 
}

// The main function
void loop(){
    
  // Sets currentMillis to the time read-out
  // of the arduino
  currentMillis = millis();
  
  // Reads potentiometer value and maps it
  // to the freq value
  sensorValue = analogRead(analogInPin);
  freq = map(sensorValue, 0, 1023, 10, 1000);
 
 
   // Chooses the state, or mode to go to.
    switch (STATE){
      case 0: Sweep(); break;
      case 1: Colors(); break;
      case 2: AllOn(); break;
      case 3: OUT_IN(); break;
      case 4: SOS(); break;
      default: break;
    }     

    // If button is read, iterate state up by 1.
    if ( digitalRead(ButtonPin) == HIGH){
        STATE++;
        if (STATE > 5) STATE = 0;
        delay(1000); // eliminate button bounce.
    }
}
