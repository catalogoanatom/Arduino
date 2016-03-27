/*
  LiquidCrystal Library - Hello World
 
 Demonstrates the use a 16x2 LCD display.  The LiquidCrystal
 library works with all LCD displays that are compatible with the 
 Hitachi HD44780 driver. There are many of them out there, and you
 can usually tell them by the 16-pin interface.
 
 This sketch prints "Hello World!" to the LCD
 and shows the time.
 
  The circuit:
 * LCD RS pin to digital pin 12
 * LCD Enable pin to digital pin 11
 * LCD D4 pin to digital pin 5
 * LCD D5 pin to digital pin 4
 * LCD D6 pin to digital pin 3
 * LCD D7 pin to digital pin 2
 * LCD R/W pin to ground
 * 10K resistor:
 * ends to +5V and ground
 * wiper to LCD VO pin (pin 3)
 
 Library originally added 18 Apr 2008
 by David A. Mellis
 library modified 5 Jul 2009
 by Limor Fried (http://www.ladyada.net)
 example added 9 Jul 2009
 by Tom Igoe
 modified 22 Nov 2010
 by Tom Igoe
 
 This example code is in the public domain.

 http://www.arduino.cc/en/Tutorial/LiquidCrystal
 */

// include the library code:
#include <LiquidCrystal.h>

// initialize the library with the numbers of the interface pins
LiquidCrystal lcd(8, 9, 4, 5, 6, 7);
String inputString = "";
boolean stringComplete = false; 


void setup() {
  inputString.reserve(200);
  // set up the LCD's number of columns and rows: 
  lcd.begin(16, 2);
  // Print a message to the LCD.
  lcd.print("Hello, World!");
  lcd.setCursor(8, 1);
  Serial.begin(9600); 
}

void loop() {
  // set the cursor to column 0, line 1
  // (note: line 1 is the second row, since counting begins with 0):
 //  lcd.clear();
 // lcd.setCursor(0, 1);
  // print the number of seconds since reset:
 //lcd.print(millis()/1000);
 //  lcd.print("    ");
 //   lcd.setCursor(0, 1);
  // lcd.print(analogRead(A0));
  //delay (1000);
//Serial.print(analogRead(A0));
int x;
x= analogRead(A0);


if (x !=1023)
  {
  Serial.print(x);
  Serial.print("\n");

lcd.setCursor(0, 1); 
  switch (x)
  {
    case 100: 
      lcd.print("UP    "); break;
    case 255: 
      lcd.print("DW    "); break;
    
    case 0: 
      lcd.print("RG    "); break;
    case 408: 
      lcd.print("LF    "); break;
    case 639:
      lcd.print("SELECT"); break;
  
  }
  }
  
//delay(100);


 serialEvent(); //call the function
  // print the string when a newline arrives:
   if (stringComplete) {
    lcd.clear();
    lcd.print(inputString);
    // clear the string:
    inputString = "";
    stringComplete = false;
 
}
  }


void serialEvent() {
  while (Serial.available()) {
    // get the new byte:
    char inChar = (char)Serial.read();
    // add it to the inputString:
    inputString += inChar;
    // if the incoming character is a newline, set a flag
    // so the main loop can do something about it:
    if (inChar == '\n') {
      stringComplete = true;
    }    
  }
}







