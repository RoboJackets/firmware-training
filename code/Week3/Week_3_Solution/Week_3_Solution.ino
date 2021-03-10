// Firmware Training Week 3
// User Code Example
// Marine Maisonneuve, Logan Schick

#define D1_PIN 11

#define SW1_PIN 2

// Stores the light value
uint8_t light_value = 0;

void setup()
{
  Serial.begin(9600);
  
  // Set mode of the LED pin
  pinMode(D1_PIN, OUTPUT);
  digitalWrite(D1_PIN, LOW);
  
  // Set mode of the button input
  pinMode(SW1_PIN, INPUT);
  
  // USER CODE - IMPLEMENT FOR LAB
  
  // ATTACH INTERRUPTS
  // Here attach the interrupt service routines to physical pins
  attachInterrupt(digitalPinToInterrupt(SW1_PIN), LED_INT, RISING);

  // SET REGISTER VALUES
  // Here set the initial values of TCCR2A, TCCR2B, and OCR2A
  TCCR2A = 0b10000011; //Datasheet section 15.11.1
  TCCR2B = 0b00000111; //Datasheet section 15.11.2
  OCR2A =  0b00000000; //Datasheet section 15.11.4
}

void loop()
{
  // Print the current light value to the serial monitor
  Serial.print("Light value: ");
  Serial.println(light_value);
  
  // A delay of 100ms so we do not sample or print too fast
  delay(100);
}

// INTERRUPT
// Here write the ISR linked to the SW1 button
void LED_INT() {
  light_value += 25;
  
  if (light_value > 255) {
    light_value = 0;
  }
  
  OCR2A = light_value;
}
