// Global
unsigned long debounceDelay = 50;

// Reprint button
const int reprintButtonPin = 2;
int reprintButtonState;
int lastReprintButtonState = LOW;
unsigned long lastReprintButtonDebounceTime = 0;

// Capture button
const int captureButtonPin = 3;
int captureButtonState;
int lastCaptureButtonState = LOW;
unsigned long lastCaptureButtonDebounceTime = 0;

// Capture LED
const int captureLedPin = 4;
int captureLedState = HIGH;
unsigned long lastCaptureLedDebounceTime = 0;

void setup() {
  Serial.begin(9600);
  pinMode(reprintButtonPin, INPUT);
  pinMode(captureButtonPin, INPUT);
  pinMode(captureLedPin, OUTPUT);
}

void loop() {
  digitalWrite(captureLedPin, captureLedState);
  lastCaptureLedDebounceTime++;
  delay(1);
  if (lastCaptureLedDebounceTime > 1000) {
    lastCaptureLedDebounceTime = 0;
    if (captureLedState == HIGH) {
      captureLedState = LOW;
    } else {
      captureLedState = HIGH;
    }
  }

  // Capture button debounce
  int captureButtonReading = digitalRead(captureButtonPin);
  if (captureButtonReading != lastCaptureButtonState) {
    lastCaptureButtonDebounceTime = millis();
  }

  if ((millis() - lastCaptureButtonDebounceTime) > debounceDelay) {
    if (captureButtonReading != captureButtonState) {
      captureButtonState = captureButtonReading;
      if (captureButtonState == HIGH) {

        // Turns on the indicator light
        digitalWrite(captureLedPin, HIGH);

        // Turns on and off rapidly until we send down the capture signal
        int delayTime = 5000;
        int internalDelayTime = 500;
        int internalBlinkCount = 0;
        while (delayTime > 0) {
          internalBlinkCount++;
          delay(internalDelayTime);
          digitalWrite(captureLedPin, LOW);
          delayTime -= (50 * internalBlinkCount) ;
          internalDelayTime -= (5 * internalBlinkCount) ;
          delay(internalDelayTime);
          digitalWrite(captureLedPin, HIGH);
          delayTime -= (50 * internalBlinkCount) ;
        }

        // Turns on the LED signal for foolishness?
        digitalWrite(captureLedPin, HIGH);

        // Signals the main program the camera should capture something
        Serial.println("capture");

        // Wait for the main program to signal to proceed
        while (Serial.available()) {
          Serial.read();
        }
        while (!Serial.available());

        // Reset our blink
        captureLedState = LOW;
        digitalWrite(captureLedPin, captureLedState);
        lastCaptureLedDebounceTime = 0;
      }
    }
  }

  lastCaptureButtonState = captureButtonReading;

  // Reprint debounce
  int reprintButtonReading = digitalRead(reprintButtonPin);
  if (reprintButtonReading != lastReprintButtonState) {
    lastReprintButtonDebounceTime = millis();
  }

  if ((millis() - lastReprintButtonDebounceTime) > debounceDelay) {
    if (reprintButtonReading != reprintButtonState) {
      reprintButtonState = reprintButtonReading;
      if (reprintButtonState == HIGH) {

        // Turns off the LED signal
        digitalWrite(captureLedPin, LOW);

        Serial.println("reprint");

        // Wait for the main program to signal to proceed
        while (Serial.available()) {
          Serial.read();
        }
        while (!Serial.available());

        // Reset our blink
        captureLedState = HIGH;
        digitalWrite(captureLedPin, captureLedState);
        lastCaptureLedDebounceTime = 0;
      }
    }
  }

  lastReprintButtonState = reprintButtonReading;
}
