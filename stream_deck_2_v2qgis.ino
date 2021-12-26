/*
  Base Project / @author 'Stream Cheap' Mini Macro Keyboard / David Madison
  @link partsnotincluded.com/electronics/diy-stream-deck-mini-macro-keyboard

  Added oled screen and support leds for retro illuminate by Nicolas ELIE / Twitter @nico_themaire
  https://github.com/themaire/StreamDeck
*/

// OLED screen
#include "screen.h"

// Buttons PWM LEDs
#include "pwm_leds.h"

// Keyboard definition
#include "Keyboard.h"
#include "keyboard_btn.h"

void failsafe() {
  for (;;) {} // Just going to hang out here for awhile :D
}

void setup() {
  //------ Startup SCREEN
  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { // Address 0x3C for 128x32
    Serial.println(F("SSD1306 allocation failed"));
    for (;;); // Don't proceed, loop forever
  }

  // Show initial display buffer contents on the screen --
  // the library initializes this with an Adafruit splash screen.
  // Clear the buffer
  display.clearDisplay();
  display.display();

  //------ Startup buttons
  // Safety check. Ground pin #1 (RX) to cancel keyboard inputs.
  pinMode(1, INPUT_PULLUP);
  if (!digitalRead(1)) {
    failsafe();
  }
  // Set pinmode for all button in the array
  for (int i = 0; i < NumButtons; i++) {
    pinMode(buttons[i].pin, INPUT_PULLUP);
  }

  //------ Buttons PWM LEDs
  tlc.begin();
  if (oe >= 0) {
    pinMode(oe, OUTPUT);
    digitalWrite(oe, LOW);
  }
  colorWipe(0, 0, 100, 440);
  //rainbowCycle(10);

  for (int i = 0; i < NumButtons; i++) {
    tlc.setLED(i, 4095, 2000, 0);
    delay(500);
    tlc.write();
  }

  colorWipe(300, 0, 100, 240);
}

void loop() {
  for (int i = 0; i < NumButtons; i++) {
    buttons[i].update();
  }

  delay(100);
}
