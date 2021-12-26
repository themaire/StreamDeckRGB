
// Key definitions
//const uint8_t BUTTON_KEY8 = KEY_F20;

    // KEY_LEFT_GUI
    // KEY_LEFT_SHIFT
    // KEY_LEFT_CTRL

const uint8_t BUTTON_TAB = KEY_TAB;
const uint8_t COMMAND = KEY_LEFT_GUI;
const uint8_t CTRL = KEY_LEFT_CTRL;
const uint8_t ALT = KEY_LEFT_ALT;

const uint8_t BUTTON_KEY1 = CTRL;
const uint8_t BUTTON_KEY2 = CTRL;
const uint8_t BUTTON_KEY3 = COMMAND;
const uint8_t BUTTON_KEY4 = "";
const uint8_t BUTTON_KEY5 = ALT;
const uint8_t BUTTON_KEY6 = "";
const uint8_t BUTTON_KEY7 = KEY_F6;
const uint8_t BUTTON_KEY8 = CTRL;

// Btn GPIO definitions
const uint8_t BUTTON_PIN1 = A1;
const uint8_t BUTTON_PIN2 = A0;
const uint8_t BUTTON_PIN3 = 10;
const uint8_t BUTTON_PIN4 = A2;
const uint8_t BUTTON_PIN5 = 7;
const uint8_t BUTTON_PIN6 = 4;
const uint8_t BUTTON_PIN7 = 8;
const uint8_t BUTTON_PIN8 = 9;

const long debounceTime = 130;
unsigned long lastPressed;
uint8_t cptBtn = 0;

// Button helper class for handling press/release and debouncing
class button {
  public:
    const char key;
    const uint8_t pin;
    bool activated = false;
    uint8_t mode = 0;
    bool tabed = false;

    button(uint8_t k, uint8_t p) : key(k), pin(p) {}

    void clearBlank() {
      display.clearDisplay();
      display.display();
    }

    void printText(String myinputstring, int8_t x=0, int8_t y=0, int8_t siZe=2) {
      display.clearDisplay();
    
      display.setTextSize(siZe); // Draw X-scale text
      display.setTextColor(WHITE);
      display.setCursor(x, y);
      display.println(myinputstring);
      display.display(); // Show expected text
    }

    void press(boolean state) {

      if (state == pressed || (millis() - lastPressed  <= debounceTime)) {
        return; // Nothing to see here, folks
      }
      lastPressed = millis();
      
      state ? Keyboard.press(key) : Keyboard.release(key);
      pressed = state;

      if (pin == BUTTON_PIN5 and pressed) {
        if (!tabed) {
          Keyboard.press(BUTTON_TAB);
          delay(50);
          //Keyboard.release(BUTTON_TAB);
          Keyboard.releaseAll();
          tabed = true;
        }
        tabed = false;
        Serial.println("Cmd");
      } else if (pin == BUTTON_PIN1 and pressed) {
          Keyboard.press('c');
          delay(50);
          //Keyboard.release('c');
          //Keyboard.release(BUTTON_KEY1);
          Keyboard.releaseAll();
      } else if (pin == BUTTON_PIN2 and pressed) {
          Keyboard.press('v');
          delay(50);
          //Keyboard.release('v');
          Keyboard.releaseAll();
      } else if (pin == BUTTON_PIN3 and pressed) {
          Keyboard.press('e');
          delay(50);
          //Keyboard.release('e');
          Keyboard.releaseAll();
      } else if (pin == BUTTON_PIN6 and pressed) {
          Keyboard.press('s');
          delay(50);
          //Keyboard.release('s');
          Keyboard.releaseAll();
      } else if (pin == BUTTON_PIN8 and pressed) {
          Keyboard.press(KEY_F6);
          delay(50);
          //Keyboard.release(KEY_F6);
          Keyboard.releaseAll();
      }

      cptBtn += 1;

      if (pressed == 0){

        display.stopscroll();
        colorWipe(0, 0, 0, 0); // Off all instantly

        // display.startscrollright(0x00, 0x0F);
        // display.stopscroll();
        if (pin == BUTTON_PIN1) {
          printText(" CTRL + C",0,10);
          display.display();

          tlc.setLED(7, 0, 4095, 0);
          tlc.write();
        } else if (pin == BUTTON_PIN2) {
          printText(" CTRL + V",0,10);
          display.display();
          tlc.setLED(6, 4095, 0, 0);
          tlc.write();
        } else if (pin == BUTTON_PIN3) {
          printText(" Explora.",0,10);
          display.display();
          //colorWipe(0, 4095, 0, 10);
          tlc.setLED(5, 4095, 4095, 4095);
          tlc.write();
          delay(50);
          tlc.setLED(5, 0, 0, 0);
          tlc.write();
        } else if (pin == BUTTON_PIN4) {
          colorWipe(0, 0, 4095, 10);
          printText("  Outro",0,10);
          display.display();
        } else if (pin == BUTTON_PIN5) {
          if (activated == false) {
            printText("  ALT-Tab ",0,10);
            display.display();

            tlc.setLED(0, 4095, 4095, 4095);
            tlc.write();
            delay(50);
            tlc.setLED(0, 0, 0, 0);
            tlc.write();
          } 
        } else if (pin == BUTTON_PIN6) {
          // CMD + S
          
          printText(" CTRL + S",0,10);
          display.display();
          tlc.setLED(1, 4095, 100, 2000);
          tlc.write();

        } else if (pin == BUTTON_PIN7) {
          // TABLE
          tlc.setLED(2, 409, 40, 40);
          tlc.write();
          printText("Table",30,10);
          display.display();
          
          // RECORDING
          //colorWipe(4095, 0, 4095, 100);
//          if (activated == false) {
//            activated = true;
//            printText("Record",40,10);
//            display.drawBitmap(0, 0, rec, Icon_width, Icon_height, 1);
//            display.display();
//          } else if (activated == true and cptBtn == 2){
//            activated = false;
//            printText("  Stop rec",0,10);
//            display.fillRect(0,9,17,17,WHITE);
//            display.display();
//          }

        } else if (pin == BUTTON_PIN8) {
          // TABLE selected
          tlc.setLED(3, 409, 40, 40);
          tlc.write();
          printText("SEL Table",15,10);
          display.display();
          
          // MUTING
//          if (activated == false) {
//            colorWipe(4095, 4095, 4095, 10);
//            activated = true;
//            printText("Mute",52,10);
//            display.drawBitmap(0, 0, mute, Icon_width, Icon_height, 1);
//            display.startscrollright(0x00, 0x0F);
//            display.display();
//          } else if (activated == true and cptBtn == 2){
//            activated = false;
//            display.stopscroll();
//            printText("On AIR",42,10);
//            display.drawBitmap(0, 0, no_mute, Icon_width, Icon_height, 1);
//            display.display();
//          }

        } else {
          clearBlank();
          // Draw pin n° with the simple screen function
          String charpin;
          charpin = String(pin) + " - " + "\n" + String(activated) + "- cptBtn: " + String(cptBtn);
          printText(charpin);
        }
        
        cptBtn = 0;
      }

    }

    void update() {
      press(!digitalRead(pin));
    }

  private:
    const long debounceTime = 30;
    unsigned long lastPressed;
    boolean pressed = 0;
    uint8_t cptBtn = 0;
};

// Objects creations
// Button objects, organized in array
button buttons[] = {
  {BUTTON_KEY1, BUTTON_PIN1},
  {BUTTON_KEY2, BUTTON_PIN2},
  {BUTTON_KEY3, BUTTON_PIN3},
  {BUTTON_KEY4, BUTTON_PIN4},
  {BUTTON_KEY5, BUTTON_PIN5},
  {BUTTON_KEY6, BUTTON_PIN6},
  {BUTTON_KEY7, BUTTON_PIN7},
  {BUTTON_KEY8, BUTTON_PIN8},
};

const uint8_t NumButtons = sizeof(buttons) / sizeof(button);
