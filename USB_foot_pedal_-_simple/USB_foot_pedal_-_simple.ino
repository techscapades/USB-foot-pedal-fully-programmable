/*
 * ezButton library created by ArduinoGetStarted: https://github.com/ArduinoGetStarted/button
 * Where to find Keyboard modifiers: https://www.arduino.cc/reference/en/language/functions/usb/keyboard/keyboardmodifiers/
 * Where to find Mouse modifiers: https://www.arduino.cc/reference/en/language/functions/usb/mouse/
*/

#include <ezButton.h>
#include <Mouse.h>
#include <Keyboard.h>

ezButton button_1(4); // Switch pin connected to pin 4 and Ground

const int SHORT_PRESS_TIME = 800; // 800 milliseconds
const int LONG_PRESS_TIME  = 800; // 800 milliseconds
unsigned long pressedTime  = 0;
unsigned long releasedTime = 0;
bool isPressing = false;
bool isLongDetected = false;

void setup() {
  Serial.begin(115200);
  button_1.setDebounceTime(50); // set debounce time to 50 milliseconds
  Mouse.begin();
  Keyboard.begin();
  Serial.println("====================================");

}

void loop() {


  button_1.loop(); // MUST call the loop() function first

  if (button_1.isPressed()) {
    pressedTime = millis();
    isPressing = true;
    isLongDetected = false;
  }

  if (button_1.isReleased()) {
    isPressing = false;
    releasedTime = millis();

    long pressDuration = releasedTime - pressedTime;

    if ( pressDuration < SHORT_PRESS_TIME ) {
      Serial.println("A short press is detected");
      //start of code that will run when short press is detected
      Keyboard.write(KEY_RIGHT_ARROW);
      Mouse.move(20, 0, 0);
      //Keyboard.press(KEY_LEFT_ALT);
      //Keyboard.press(KEY_F4);
      //Keyboard.releaseAll();
      //end of code that will run when short press is detected
    }

  }

  if (isPressing == true && isLongDetected == false) {
    long pressDuration = millis() - pressedTime;

    if ( pressDuration > LONG_PRESS_TIME ) {
      isLongDetected = true;
      Serial.println("A long press is detected");
      //start of code that will run when long press is detected
      Mouse.move(0, 0, 2);
      //Mouse.click(MOUSE_RIGHT);
      Keyboard.print("I'm a long press");
      //end of code that will run when long press is detected
    }
  }



}
