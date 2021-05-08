/*
Running Lights & Blinkers

Turn on running lights for n seconds after input from sensor

Push button for left and right blinkers.

*/
//Timer
unsigned long curTime;
unsigned long startTime;
unsigned long endTime;
//Running Senor
int const inPin = 2;
int inPinValue = 0;
int const motTime = 700;
int const runPin = 5;
//Blinker
bool blinkStatus;
bool blinkingLeft;
bool blinkingRight;
unsigned long enterTime = 0;
int const bLength = 600;
int const potPin = A0;
int potValue;
int leftPin = 11;
int rightPin = 8;

void setup() {
  pinMode(inPin, INPUT);
  pinMode(runPin, OUTPUT);
  pinMode(leftPin, OUTPUT);
  pinMode(rightPin, OUTPUT);

  digitalWrite(runPin, LOW);
  digitalWrite(leftPin, LOW);
  digitalWrite(rightPin, LOW);
  Serial.begin(9600);
}

void loop() {
  curTime = millis();
  potValue = analogRead(potPin);
  
  // Blinker
  if (blinkStatus == false) {
    Serial.println("ready to blink");
    if (potValue <= 341) {
     // left
     blinkStatus = true;
     blinkingLeft = true;
    } else if (potValue >= 682) {
     // right
     blinkStatus = true;
     blinkingRight = true;
    }
  } else {
    if (blinkingLeft == true) {
      // enter recursive blinking function left
      Serial.println("leftblink");
      if (enterTime <= 0) {
      enterTime = blink(curTime, bLength, leftPin);
      } else if (curTime >= enterTime) {
       enterTime = 0;
      }
    }
    if (blinkingRight == true) {
      // enter recursive blinking function right
      Serial.println("rightblink");
      if (enterTime <= 0) {
      enterTime = blink(curTime, bLength, rightPin);
      } else if (curTime >= enterTime) {
       enterTime = 0;
      }
    }
    
  }

  // Detect Motion
  inPinValue = digitalRead(inPin);
  if (inPinValue > 0) {
    startTime = curTime;
    endTime = startTime + motTime;
    digitalWrite(runPin, HIGH);
  }

  // End Blink
  if (potValue > 341 && potValue < 682) {
    digitalWrite(leftPin, LOW);
    digitalWrite(rightPin, LOW);
    blinkingLeft = false;
    blinkingRight = false;
    blinkStatus = false;
  }
  // End Motion
  if (curTime >= endTime) {
    digitalWrite(runPin, LOW);
    }
  }

// blinker recursive function
unsigned long blink(unsigned long curTime, unsigned long bLength, int bPin) {
  Serial.println("In Blink");
  enterTime = curTime + bLength;
  
  int pStatus = digitalRead(bPin);
  if (pStatus <= 0) {
    digitalWrite(bPin, HIGH);
  } else {
    digitalWrite(bPin, LOW);
  }
  
  return enterTime;
}
