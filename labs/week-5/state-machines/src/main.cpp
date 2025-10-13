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

void setup() {

}

void loop() {

}
