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
 * LCD VSS pin to ground
 * LCD VCC pin to 5V
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
 modified 7 Nov 2016
 by Arturo Guadalupi

 This example code is in the public domain.

 http://www.arduino.cc/en/Tutorial/LiquidCrystalHelloWorld

*/

/*
  Button

  Turns on and off a light emitting diode(LED) connected to digital pin 13,
  when pressing a pushbutton attached to pin 2.

  The circuit:
  - LED attached from pin 13 to ground
  - pushbutton attached to pin 2 from +5V
  - 10K resistor attached to pin 2 from ground

  - Note: on most Arduinos there is already an LED on the board
    attached to pin 13.

  created 2005
  by DojoDave <http://www.0j0.org>
  modified 30 Aug 2011
  by Tom Igoe

  This example code is in the public domain.

  http://www.arduino.cc/en/Tutorial/Button
*/

// constants won't change. They're used here to set pin numbers:
const int buttonPin = 7;     // the number of the pushbutton pin

// variables will change:
int buttonState = 0;         // variable for reading the pushbutton status


// include the library code:
#include <LiquidCrystal.h>

// initialize the library by associating any needed LCD interface pin
// with the arduino pin number it is connected to
const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
const int WIN_LED = 13, LOSE_LED = 9;
#define echoPin 10 // attach pin D2 Arduino to pin Echo of HC-SR04
#define trigPin 8 //attach pin D3 Arduino to pin Trig of HC-SR04
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);
int level = 0;
boolean won = true;
boolean wonAll = false;
long randNumber;
boolean endGame;

// defines variables
long duration; // variable for the duration of sound wave travel

void setup() {
  // set up the LCD's number of columns and rows:
  lcd.begin(16, 2);
  // Print a message to the LCD.
  // initialize the pushbutton pin as an input:
  pinMode(buttonPin, INPUT);
  pinMode(WIN_LED, OUTPUT);
  pinMode(LOSE_LED, OUTPUT);
  randomSeed(analogRead(0));

  pinMode(trigPin, OUTPUT); // Sets the trigPin as an OUTPUT
  pinMode(echoPin, INPUT); // Sets the echoPin as an INPUT
  
 
  

}

//Returns the distance of the closest object to the ultrasonic sensor
int CalcDistance(){

   digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  // Sets the trigPin HIGH (ACTIVE) for 10 microseconds
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  // Reads the echoPin, returns the sound wave travel time in microseconds
  duration = pulseIn(echoPin, HIGH);
  // Calculating the distance
  return duration * 0.017; // Speed of sound wave divided by 2 (go and back)
}

void roundEnded(boolean didWin){
  char const *str = "You WON!";
  int ledToTurnOn = WIN_LED;
  if (!didWin){
    str = "You LOST!";
    ledToTurnOn = LOSE_LED;
  }
  lcd.setCursor(0, 0);
  lcd.clear();
  lcd.print(str);
  digitalWrite(ledToTurnOn, HIGH);   
  endGame = true;
  won = didWin;
  delay(1500);
  
}

void loop() {
  // set the cursor to column 0, line 1
  // (note: line 1 is the second row, since counting begins with 0):
  digitalWrite(WIN_LED, LOW); 
  digitalWrite(LOSE_LED, LOW); 

  delay(1000);
  if (won){
    level++;
  }
  if (level >= 10){
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("You finished");
    lcd.setCursor(0, 1);
    lcd.print("the game!");
    level = 0;
    delay(200000);
  }
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Click when 8! L");
  lcd.print(level);


  delay(3000);
  lcd.setCursor(0, 0);
  lcd.print("                ");

 
  endGame = false;
  won = false;
  while (!endGame){
    digitalWrite(WIN_LED, LOW); 
    digitalWrite(LOSE_LED, LOW); 

    randNumber = random(10);
    lcd.setCursor(0, 1);
    lcd.print(" ");
    lcd.setCursor(0, 1);
    lcd.print(randNumber);
    for (int j = 0 ; j < 40; j ++){
        delay(10-level);
        buttonState = digitalRead(buttonPin);
        int distance = CalcDistance();
        if (buttonState == HIGH || distance < 15){
          //Player clicked or got closer with the hand
          boolean playerWon = randNumber == 8;
          roundEnded(playerWon);

         }
    }

  }
  
}
  
