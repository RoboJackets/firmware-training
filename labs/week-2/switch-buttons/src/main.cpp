/**
 * For the switch buttons lab, there are 2 input buttons on the RoboJackets
 * training board.  The first button is attached to pin 2 and will yield a
 * digital value of 1 when it is pressed (otherwise it will be a 0).  The
 * second button is attached to pin 3 and will yield a digital value of
 * 0 when pressed (otherwise it will be a 1).
 * 
 * The goal of this lab is to have LED 1 (pin 11) on the board represent
 * the state of button 1 and LED 2 (pin 10) represent the state of button
 * 2.
 * 
 * In this lab, the first LED should be controlled via the main loop.  This
 * will mean polling the state of the first switch and updating the LED
 * accordingly.  The second LED should be controlled via interrupts.  Via
 * interrupts, you should be able to determine when the LED is pressed
 * and when it is released.
 * 
 * Please, do not attach the interrupt to the LOW and HIGH states of the LED.
 * This will override your loop and make for very hard to debug code.  Instead,
 * think about what rising and falling edge will be in this situation and how
 * you can use these states to make the LED represent the state of the button. 
 * 
 * Author: Nathaniel Wert <n8.wert.b@gmail.com>
 */

#include <Arduino.h>

void setup() {

}

void loop() {
  
}
