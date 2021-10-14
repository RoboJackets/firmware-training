// Firmware Training Week 2
// User Code


#define D1_PIN 11
#define D2_PIN 10
#define D3_PIN 9
#define D4_PIN 6
#define D5_PIN 5

#define SW1_PIN 2
#define SW2_PIN 3

// Stores the LED pins
int pinArray[5] = {D5_PIN, D4_PIN, D3_PIN, D2_PIN, D1_PIN};

// Stores the state machine state and sets initial state
volatile int8_t state = 0;

void setup()
{
  Serial.begin(9600);
    
  // Set mode of all of the LED pins
  pinMode(D1_PIN, OUTPUT);
  pinMode(D2_PIN, OUTPUT);
  pinMode(D3_PIN, OUTPUT);
  pinMode(D4_PIN, OUTPUT);
  pinMode(D5_PIN, OUTPUT);
  
  digitalWrite(D1_PIN, LOW);
  digitalWrite(D2_PIN, LOW);
  digitalWrite(D3_PIN, LOW);
  digitalWrite(D4_PIN, LOW);
  digitalWrite(D5_PIN, LOW);

  // USER CODE - IMPLEMENT FOR LAB
  
  // SET UP INPUTS
  // Here set up the button inputs
  
  // ATTACH INTERRUPTS
  // Here attach the interrupt service routines to physical pins
}

void loop()
{
  // DISPLAY STATE
  // Here use the state variable and display the results using the LEDs
  // Make sure to use a for loop here, updating every LED

  // Print the current state to the serial monitor
  Serial.print("State ");
  Serial.println(state);
  
  // A delay of 100ms so we do not sample or print too fast
  delay(100);
}

// INTERRUPT 1
// Here write the ISR linked to the SW1 button
void ISR_SW1()
{
}

// INTERRUPT 2
// Here write the ISR linked to the SW2 button
void ISR_SW2()
{
}
