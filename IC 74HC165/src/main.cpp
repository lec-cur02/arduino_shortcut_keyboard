#include <Arduino.h>
#include <LiquidCrystal.h>

/*LCD in Four bits mode 
RS = 13, RW to GND, E = 12, D4 = 5, D5 = 4, D6 = 3, D7 = 2  */
LiquidCrystal lcd(13, 12, 5, 4, 3, 2);

const int RS = 13; 
const int EN = 12;
const int latchPin = 9;
const int clockPin = 8; 
const int dataPin1 = A1;
const int dataPin2 = A0; 

const char alphabet[14] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 
                         'I', 'J', 'K', 'L', 'M', 'N'};

//cursor position
int posX = 0, posY = 0;

void setup(){
  lcd.begin(20, 4);
  Serial.begin(9600);
  pinMode(dataPin1, INPUT);
  pinMode(dataPin2, INPUT);
  pinMode(latchPin, OUTPUT);
  pinMode(clockPin, OUTPUT);
}

void loop(){
// Load parallel data from shift registers to Q registers
  digitalWrite(latchPin, LOW);
  digitalWrite(latchPin, HIGH);
  for(int i=0; i < 8; i++){
    //set new position of cursor when character printed
    lcd.setCursor(posX, posY);
    int val1 = digitalRead(dataPin1);
    int val2 = digitalRead(dataPin2);
    if(val1 == HIGH){
      lcd.print(alphabet[7-i]);
      posX++;
    }
    if(val2 == HIGH){
      lcd.print(alphabet[15-i]);
      posX++;
    }
    // Move to next line if end of line is reached
    if(posX == 20){
      posX = 0;
      posY++;
    }
    //Shift to next bit
    digitalWrite(clockPin, HIGH);
    digitalWrite(clockPin, LOW);
  }
  delay(1000);
}