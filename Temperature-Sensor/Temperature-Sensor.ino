#define BLYNK_TEMPLATE_ID "TMPL31sV3lueW"
#define BLYNK_TEMPLATE_NAME "sfsaga"
#define BLYNK_AUTH_TOKEN "sMXjbckUrzfiCiZeNh9wSLyAFzQqeicA"

#define BLYNK_PRINT Serial
#define VPIN_BUTTON_1    V1
#define VPIN_BUTTON_2    V2
#define VPIN_BUTTON_3    V3
#include<Wire.h>
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include <DHT.h>
#include <LiquidCrystal_I2C.h>
#define DHTPIN D4 //Define sensor pin(pin 12)
#define DHTTYPE DHT11 //What sensor use

DHT dht(DHTPIN, DHTTYPE);//Create sensor object
LiquidCrystal_I2C lcd(0x27,16,2); //Create lcd object using this pins 8,9,4,6,7

boolean a=LOW,b=HIGH;
float h=0,t=0;
const int ledPin = D6; //LED pins for temperature control 
const int ledPin2 = D8;
long previousMillis = 0;
long interval = 2000; //Read sensor each 2 seconds
char auth[] = "sMXjbckUrzfiCiZeNh9wSLyAFzQqeicA"; //Auth code sent via Email
char ssid[] = "surya";
char pass[] = "87654321";
BlynkTimer timer;
void setup() {
 Serial.begin(9600);   // opens serial port, sets data rate to 9600 bps
  lcd.begin(16,2);      // set up the LCD's number of columns and rows


  Blynk.begin(auth, ssid, pass);
  // You can also specify server:
  //Blynk.begin(auth, ssid, pass, "blynk-cloud.com", 80);
  //Blynk.begin(auth, ssid, pass, IPAddress(192,168,1,100), 8080);
lcd.init();                      // initialize the lcd 
  lcd.backlight();
  Serial.begin(9600);
pinMode(ledPin, OUTPUT);//Change to output my pins
pinMode(ledPin2, OUTPUT);
dht.begin();//Start DHT22 sensor
digitalWrite(ledPin2,LOW);//Turn off LED
digitalWrite(ledPin,LOW);//Turn off LED
lcd.print("Tempera:");// print in lcd this word 
lcd.setCursor(0,1);//Change cursor position
lcd.print("Humedad:");// print in lcd this word 
}

void loop()
{
  unsigned long currentMillis = millis();//time elapsed
  if(currentMillis - previousMillis > interval) //Comparison between the elapsed time and the time in which the action is to be executed
  {
    previousMillis = currentMillis; //"Last time is now"

     h = dht.readHumidity();//humidity value
     t = dht.readTemperature();//temperature value centigrades if you want farenheit change to
     //t = dht.readTemperature(true);
  Blynk.virtualWrite(V1,(int) h);
  Blynk.virtualWrite(V2,(int)t);
    lcd.setCursor(0, 0);
  lcd.print("Temp  : ");
  lcd.print(t);
  lcd.print((char)223);// for Degree(°) 
  lcd.print("C   ");
  lcd.setCursor(0, 1);
  lcd.print("Humid : ");
  lcd.print(h);
  lcd.print("%");
    
    if(t>=40 && a==LOW)//if temperature above of 25 degrees
    {
      digitalWrite(ledPin2,HIGH);//Active air conditioner
 a=HIGH;
      Blynk.virtualWrite(VPIN_BUTTON_3, "PUMP ON");
         delay(10000);
     delay(10000);
      delay(10000);
    }
    else //if temperature is under 23 degrees
    {
      
      digitalWrite(ledPin2,LOW);//Turn off air conditioner
      a=LOW;
      Blynk.virtualWrite(VPIN_BUTTON_3, "PUMP OFF");
    }
      
   
    
  }
  {
  
  Blynk.run();
  timer.run();
 
}
}