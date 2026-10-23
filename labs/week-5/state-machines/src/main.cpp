/**
 * For this lab we're going to create a small state machine.  Unfortunately, there
 * are only two buttons on our board so this state machine is going to be pretty simple
 * and small.
 * 
 * In this lab, we're going to be creating a combination lock (actually a permutation lock
 * but... you know).  First, you are going to come up with a 5 press keycode using the buttons
 * on the board.  This can be something like 1, 1, 1, 1, 1 or 1, 2, 1, 2, 2 but feel free to
 * choose whatever combination speaks to you.  Whenever the wrong button is pressed, you should
 * fall back to the locked state.
 * 
 * We are going to consider each of the presses a different state, so we will have the following
 * states:
 *  Locked
 *  First Code
 *  Second Code
 *  Third Code
 *  Fourth Code
 *  Unlocked
 * 
 * With this lab, you should progress through the states and set leds D1 and D2 to high when
 * the correct input is entered.
 * 
 * I've created a few helpers to get you started, but feel free to ignore them, delete them,
 * or do whatever you want with them.
 * 
 * Author: Nathaniel Wert <n8.wert.b@gmail.com>
 */

#include <Arduino.h>


#define BTN0 2
#define BTN1 3

enum class LockStates : uint8_t {
    Locked = 0,
    FirstCode,
    SecondCode,
    ThirdCode,
    FourthCode,
    Unlocked
};

void btn_ISR();

uint8_t LEDS[5] = {5, 6, 9, 10, 11};

uint8_t combo[5] = {1, 2, 2, 1, 1};

LockStates state = LockStates::Locked;

uint32_t last_press = 0;
uint8_t last_btns = 0;
volatile uint8_t btns = 0;

void setup() {
    Serial.begin(9600);
    Serial.println("Hello World!");

    attachInterrupt(digitalPinToInterrupt(BTN0), btn_ISR, CHANGE);
    attachInterrupt(digitalPinToInterrupt(BTN1), btn_ISR, CHANGE);

    for (auto led : LEDS) {
        pinMode(led, OUTPUT);
    }
}

void loop() {
    Serial.print("Button States: ");
    Serial.println(btns);

    for (auto led : LEDS) {
        digitalWrite(led, LOW);
    }

    switch (state) {
        case LockStates::Locked:
            if (btns == combo[0]) {
                state = LockStates::FirstCode;
            } else if (btns != 0) {
                state = LockStates::Locked;
            }
        break;
        case LockStates::FirstCode:
            if (btns == combo[1]) {
                state = LockStates::SecondCode;
            } else if (btns != 0) {
                state = LockStates::Locked;
            }

            digitalWrite(LEDS[0], HIGH);
        break;
        case LockStates::SecondCode:
            if (btns == combo[2]) {
                state = LockStates::ThirdCode;
            } else if (btns != 0) {
                state = LockStates::Locked;
            }

            digitalWrite(LEDS[1], HIGH);
        break;
        case LockStates::ThirdCode:
            if (btns == combo[3]) {
                state = LockStates::FourthCode;
            } else if (btns != 0) {
                state = LockStates::Locked;
            }

            digitalWrite(LEDS[2], HIGH);
        break;
        case LockStates::FourthCode:
            if (btns == combo[4]) {
                state = LockStates::Unlocked;
            } else if (btns != 0) {
                state = LockStates::Locked;
            }

            digitalWrite(LEDS[3], HIGH);
        break;
        case LockStates::Unlocked:
            if (btns != 0) {
                state = LockStates::Locked;
            }
            for (auto led : LEDS) {
                digitalWrite(led, HIGH);
            }
        break;
        default:
        break;
    }

    btns = 0;
}



void btn_ISR() {
    if (last_press < millis() - 200) {
        btns = (digitalRead(BTN0) & 0b1) | (!digitalRead(BTN1) & 0b1) << 1;
        if (last_btns != btns) {
            last_press = millis();
        }
    }
}