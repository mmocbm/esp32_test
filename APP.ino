const int ledPin = 2; // Assuming the built-in LED is connected to GPIO 2

void setupApp() {
  pinMode(ledPin, OUTPUT); // Initialize the LED pin
  digitalWrite(ledPin, LOW); // Ensure the LED is off initially
}

void loopApp() {
  // Blink the LED
  digitalWrite(ledPin, HIGH); // Turn the LED on
  delay(500);                 // Wait for 500 milliseconds
  digitalWrite(ledPin, LOW);  // Turn the LED off
  delay(500);                 // Wait for 500 milliseconds
}