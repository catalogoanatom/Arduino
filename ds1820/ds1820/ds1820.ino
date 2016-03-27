// Program odczytuje temperaturę kilku czujników

#include <OneWire.h>
#include <DS18B20.h>
#include <LiquidCrystal.h>
#include <EEPROM.h>

const int relay1Pin =  3;
const int relay2Pin =  11;

int t1p=29;
int t2p=29;
// Numer pinu do którego podłaczasz czujnik
#define ONEWIRE_PIN 2

// Ilość czujników
#define SENSORS_NUM 2
#define TRASH_POSITION 11
// Adresy czujników
const byte address[SENSORS_NUM][8] PROGMEM = {
  0x28, 0xFF, 0x65, 0x90, 0x72, 0x15, 0x3, 0x3B,
  0x28, 0xFF, 0xCB, 0xB7, 0x72, 0x15, 0x3, 0x5C
};

OneWire onewire(ONEWIRE_PIN);
DS18B20 sensors(&onewire);
LiquidCrystal lcd(8, 9, 4, 5, 6, 7);

void setup() {
  
  t1p=EEPROM.read(0);
  t2p=EEPROM.read(1);

  lcd.begin(16, 2);
  pinMode(relay1Pin, OUTPUT);
  pinMode(relay2Pin, OUTPUT);
  digitalWrite(relay1Pin, HIGH);
  digitalWrite(relay2Pin, HIGH);
  while(!Serial);
  Serial.begin(9600);


  sensors.begin();
  sensors.request();
}

void save_tp(int t1, int t2)
{
  EEPROM.write(0, t1);
  EEPROM.write(1, t2);
}



void print_treshholds(int t1, int t2)
{

  lcd.setCursor(TRASH_POSITION, 0);
  lcd.print(t1);
  lcd.setCursor(TRASH_POSITION, 1);
  lcd.print(t2);
}

#define btnRIGHT  0
#define btnUP     1
#define btnDOWN   2
#define btnLEFT   3
#define btnSELECT 4
#define btnNONE   5

int read_LCD_buttons()
{
  int adc_key_in    = 0;


  adc_key_in = analogRead(0);      // read the value from the sensor 
  delay(5); //switch debounce delay. Increase this delay if incorrect switch selections are returned.
  int k = (analogRead(0) - adc_key_in); //gives the button a slight range to allow for a little contact resistance noise
  if (5 < abs(k)) return btnNONE;  // double checks the keypress. If the two readings are not equal +/-k value after debounce delay, it tries again.
  // my buttons when read are centered at these valies: 0, 144, 329, 504, 741
  // we add approx 50 to those values and check to see if we are close
  if (adc_key_in > 1000) return btnNONE; // We make this the 1st option for speed reasons since it will be the most likely result
  if (adc_key_in < 50)   {
    save_tp(t1p,t2p); 
    return btnRIGHT;
  }  
  if (adc_key_in < 195)  {
    t2p++;
    return btnUP;
  } 
  if (adc_key_in < 380)  {
    t2p--;
    return btnDOWN;
  } 
  if (adc_key_in < 555)  {
    t1p++; 
    return btnLEFT;
  } 
  if (adc_key_in < 790)  {
    t1p--; 
    return btnSELECT;
  }   
  return btnNONE;  // when all others fail, return this...
}




void loop() {
  if (sensors.available())
  {
    for (byte i=0; i<SENSORS_NUM; i++)
    {
      float temperature = sensors.readTemperature(FA(address[i]));

      if (i==1)
      {
        lcd.setCursor(0, 0);
        lcd.print("T1: ");
        if (  temperature > t1p)  
        {
          digitalWrite(relay1Pin, HIGH);

        }
        else
          digitalWrite(relay1Pin, LOW);


      }
      else
      {
        lcd.setCursor(0, 1);
        lcd.print("T2: ");

        if (  temperature > t2p)  
        {
          digitalWrite(relay2Pin, HIGH);

        }
        else
          digitalWrite(relay2Pin, LOW);


      }
      lcd.print(temperature);


      Serial.print(F("#"));
      Serial.print(i);
      Serial.print(F(": "));
      Serial.print(temperature);
      Serial.println(F(" 'C"));
    }

    sensors.request();
    read_LCD_buttons();
    print_treshholds(t1p,  t2p);
    //    save_tp(t1p, t2p);


  }

  // tu umieść resztę twojego programu
  // Będzie działał bez blokowania
}



