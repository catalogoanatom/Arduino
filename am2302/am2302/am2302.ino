#include "DHT.h"
#include <LiquidCrystal.h>
#define DHTPIN 12     
#define DHTTYPE DHT22 //DHT11, DHT21, DHT22

DHT dht(DHTPIN, DHTTYPE);
//const int buttonPin = 12;    // the number of the pushbutton pin





byte gradus[8] = {
  0b00110,
  0b01001,
  0b01001,
  0b00110,
  0b00000,
  0b00000,
  0b00000,
  0b00000
};

byte up[8] = {
  0b00100,
  0b01110,
  0b11111,
  0b00100,
  0b00100,
  0b00100,
  0b00100,
  0b00100
};

byte down[8] = {
  0b00100,
  0b00100,
  0b00100,
  0b00100,
  0b00100,
  0b11111,
  0b01110,
  0b00100
};









const int relay1Pin =  3;
const int relay2Pin =  11;

float h0=0;
float t0=0;

LiquidCrystal lcd(8, 9, 4, 5, 6, 7);

void setup() 
{
  pinMode(relay1Pin, OUTPUT);
  pinMode(relay2Pin, OUTPUT);

  lcd.begin(16, 2);
  lcd.createChar(1, gradus);
  lcd.createChar(2, up);
  lcd.createChar(3, down);
  Serial.begin(9600); 
  Serial.println("DHT22 - Test!");

  dht.begin();
}

void loop() 
{

  //Serial.print(digitalRead(buttonPin));
  delay(5000);
  float h = dht.readHumidity();     //Luftfeuchte auslesen
  float t = dht.readTemperature();  //Temperatur auslesen

  // Prüfen ob eine gültige Zahl zurückgegeben wird. Wenn NaN (not a number) zurückgegeben wird, dann Fehler ausgeben.
  if (isnan(t) || isnan(h)) 
  {
    Serial.println("DHT22 konnte nicht ausgelesen werden");
  } 
  else
  {
    Serial.print("Luftfeuchte: "); 
    Serial.print(h);
    Serial.print(" %\t");
    Serial.print("Temperatur: "); 
    Serial.print(t);
    Serial.println(" C");


    lcd.setCursor(0, 0);
    lcd.print("T: ");
    lcd.print(t);
    lcd.write(1);


    if( t>t0)
      lcd.write(2);    
    else if (t==t0)
      ;
    else
      lcd.write(3);

    t0=t;


    lcd.setCursor(0, 1);
    lcd.print("H: ");
    lcd.print(h);
    lcd.print("%");

    if( h>h0)
      lcd.write(2);    
    else if (h==h0)
        ;
    else
      lcd.write(3);

    h0=h; 





    if (  t > 27.0)  
    {
      digitalWrite(relay1Pin, HIGH);

    }
    else
      digitalWrite(relay1Pin, LOW);





    if (  h > 40.0)  
    {
      digitalWrite(relay2Pin, HIGH);

    }
    else
      digitalWrite(relay2Pin, LOW);



  }
}


