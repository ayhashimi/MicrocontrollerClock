
#include <TinyWireM.h>
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
#include <DS1307RTC.h>
#include <RTClib.h>

RTC_DS3231 rtc;
LiquidCrystal_I2C lcd(0x27, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE);  // Set the LCD I2C address
//int tempPin = 0;
//int ledPin = 11;
//int brightness = 0;
//int fade = 100;
//boolean b = true;
//oolean f = false;
//boolean r = false;

void setup()  
{
  lcd.begin(20,4); 

  //Serial.begin(9600);

  //pinMode(ledPin, OUTPUT);

  rtc.begin();

  rtc.adjust(DateTime(F(__DATE__),F(__TIME__)));
  
  createCustomCharacters();
 
  printFrame();
}

byte verticalLine[8] = {
  B00100,
  B00100,
  B00100,
  B00100,
  B00100,
  B00100,
  B00100,
  B00100
};  

byte char2[8] = {
  B00000,
  B00000,
  B00000,
  B11100,
  B00100,
  B00100,
  B00100,
  B00100
};

byte char1[8] = {
  B00000,
  B00000,
  B00000,
  B00111,
  B00100,
  B00100,
  B00100,
  B00100
};

byte char3[8] = {
  B00100,
  B00100,
  B00100,
  B00111,
  B00000,
  B00000,
  B00000,
  B00000
};

byte char4[8] = {
  B00100,
  B00100,
  B00100,
  B11100,
  B00000,
  B00000,
  B00000,
  B00000
};

void createCustomCharacters()
{
  lcd.createChar(0, verticalLine);
  lcd.createChar(1, char1);
  lcd.createChar(2, char2);
  lcd.createChar(3, char3);
  lcd.createChar(4, char4);
}

void printFrame()
{
  lcd.setCursor(1,0);
  lcd.print("------------------");
  lcd.setCursor(1,3);
  lcd.print("------------------");
  lcd.setCursor(0,1);
  lcd.write(byte(0));
  lcd.setCursor(0,2);
  lcd.write(byte(0));
  lcd.setCursor(19,1);
  lcd.write(byte(0));
  lcd.setCursor(19,2);
  lcd.write(byte(0));
  lcd.setCursor(0,0);
  lcd.write(byte(1));
  lcd.setCursor(19,0);
  lcd.write(byte(2));
  lcd.setCursor(0,3);
  lcd.write(byte(3));
  lcd.setCursor(19,3);
  lcd.write(byte(4));
}

void loop() 
{
  //int tempReading = analogRead(tempPin);
  // This is OK
  //double tempK = log(10000.0 * ((1024.0 / tempReading - 1)));
  //tempK = 1 / (0.001129148 + (0.000234125 + (0.0000000876741 * tempK * tempK )) * tempK );       //  Temp Kelvin
  //float tempC = tempK - 273.15;            // Convert Kelvin to Celcius
  //float tempF = (tempC * 9.0)/ 5.0 + 32.0; // Convert Celcius to Fahrenheit
  /*  replaced
    float tempVolts = tempReading * 5.0 / 1024.0;
    float tempC = (tempVolts - 0.5) * 10.0;
    float tempF = tempC * 9.0 / 5.0 + 32.0;
  */

  //lcd.setCursor(1,11);
  //lcd.print("Temp:    F");
  //lcd.setCursor(11,2);
  //lcd.print(tempC);



   tmElements_t tm;
  
  /*if (b)
  {
      brightness = brightness + 10;
      if (brightness == 100)
      {
        analogWrite(ledPin, brightness);
          brightness = 0;
          b = false;
          f = true;
      }
      else
      {
        analogWrite(ledPin, brightness);
      }
  }

  if (f)
  {
      fade = fade - 10;

      if (fade == 0)
      {
          brightness = 10;
          fade = 100;
          f = false;
          b = true;
      }
      else
      {
        analogWrite(ledPin, fade);
      }
  }*/



  if (RTC.read(tm)) {
    printDate(5,1,tm);
    printTime(6,2,tm);  
   
  } else {
    if (RTC.chipPresent()) {
      //The DS1307 is stopped. Please run the SetTime
    } else {
      //DS1307 read error! Please check the circuitry
    }
    delay(9000);
  }

  delay(1000);
}

void printTime(int character,int line, tmElements_t tm)
{
  String seconds,minutes;
  lcd.setCursor(character,line);

  if (tm.Hour == 0)
  {
    lcd.print(12);
  }
  else if (tm.Hour > 12)
  {
    tm.Hour = tm.Hour - 12;
    if (tm.Hour < 10)
    {
      lcd.print(0);
    }
    lcd.print(tm.Hour);
  }
  else
  {
    if (tm.Hour < 10)
    {
      lcd.print(0);
    }
    lcd.print(tm.Hour);
  }

  lcd.print(":");
  
  if(tm.Minute<10)
  {
    minutes = "0"+String(tm.Minute);
    lcd.print(minutes);
  }else
  {
    lcd.print(tm.Minute);
  }
  lcd.print(":");
  if(tm.Second<10)
  {
    seconds = "0"+String(tm.Second);
    lcd.print(seconds);
  }else
  {
    lcd.print(tm.Second);
  }
}

void printDate(int character,int line, tmElements_t tm)
{
  lcd.setCursor(character,line);
  lcd.print(tm.Month);
  lcd.print("/");
  lcd.print(tm.Day);
  lcd.print("/");
  lcd.print(tmYearToCalendar(tm.Year));
}

