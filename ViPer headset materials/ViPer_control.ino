#include <Servo.h>

Servo myservo;  // create servo object 

unsigned long startMillis;
const int servoPin = 10;
const int buttonPin = 2;  // button connected to pin 2
int buttonState = 0;      // current state of the button
int lastButtonState = 0;  // previous state of the button
int buttonPushCounter = 0; // counter for the number of button presses
unsigned long lastDebounceTime = 0;  // the last time the output pin was toggled
unsigned long debounceDelay = 50;    // the debounce time; increase if the output flickers
bool returningToZero = true; // flag to handle initial movement to zero position
int lastPos = 0; 

void setup() {
  Serial.begin(115200);         // initialize serial communication at 115200 bits per second
  myservo.attach(servoPin);     // attaches the servo on pin 10 to the servo object
  pinMode(buttonPin, INPUT);    // initialize the button pin as an input
  startMillis = millis();       // record the start time           // start at the neutral position
}

void loop() {

  // read the state of the switch into a local variable
  int reading = digitalRead(buttonPin);

  // check if the button state has changed
  if (reading != lastButtonState) {
    lastDebounceTime = millis(); // reset the debouncing timer
  }

  if ((millis() - lastDebounceTime) > debounceDelay) {
    // if the button state has changed:
    if (reading != buttonState) {
      buttonState = reading;

      // only toggle the counter if the new button state is HIGH
      if (buttonState == HIGH) {
        buttonPushCounter++;
        if (buttonPushCounter > 3) {
          buttonPushCounter = 0; // reset counter after 3 presses
        }
      }
    }
  }

  // save the reading. Next time through the loop, it'll be the lastButtonState:
  lastButtonState = reading;

  unsigned long currentMillis = millis();
  float t = (currentMillis - startMillis) / 1000.0;  // convert milliseconds to seconds
  float pos = 105; // default position

  // Select expression based on the number of button presses
  if (buttonPushCounter == 1) {
    // Low perturbation magnitude
    pos = 100 + 12.5*(0.5*sin(M_PI * 2 * 0.25 * t) + 0.25 * sin(M_PI * 2 * 0.125 * t) + 0.25 * sin(M_PI * 2 * 0.442 * t));
  } else if (buttonPushCounter == 2) {
    // High perturbation magnitude
    pos = 100 + 25*(0.5*sin(M_PI * 2 * 0.25 * t) + 0.25 * sin(M_PI * 2 * 0.125 * t) + 0.25 * sin(M_PI * 2 * 0.442 * t));
  } else if (buttonPushCounter == 3) {
    // Zero perturbation magnitude
    pos = 105; // Neutral
  }
//135
  // Ensure the position is within the valid range 
  pos = constrain(pos, 62, 118);

  // Only update the servo if the position has changed
  if (pos != lastPos) {
    myservo.write(pos);  // update the servo position
    lastPos = pos; // save the current position
  }
  
  myservo.write(pos);  // update the servo position
  
  // Print the position to the Serial Monitor
  Serial.print("Time: ");
  Serial.print(t);
  Serial.print(" s, Position: ");
  Serial.print(pos);
  Serial.print(" Button Presses: ");
  Serial.println(buttonPushCounter);
  
  Serial.println(pos);
  delay(15);  // small delay to smooth out the motion
}

