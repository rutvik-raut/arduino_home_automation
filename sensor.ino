#include <LiquidCrystal.h>      //Include Header Library for LCD
LiquidCrystal lcd(7,6,5,4,3,2);   //Define Data Pins of LCD
int tempPin = A1;           // Output Pin Of Temperature Sensor
int fan = 11;       // Fan Connection Pin
int led = 8;        // Led Connection Pin

float temp;
float tempMin = 30;   
float tempMax = 60;   

int fanSpeed;
int fanLCD;


int LDR = A5;       // LDR input at A5 pin.
int LIGHT = 10;     // Bulb Connection Pin
int LDRReading = 0; // To Store Input Value from LDR


void setup() 
{
  pinMode(fan, OUTPUT);
  pinMode(led, OUTPUT);
  pinMode(tempPin, INPUT);
  lcd.begin(16,2);  
  
  pinMode(LIGHT, OUTPUT); 
  pinMode(LDR,INPUT);
  
  Serial.begin(9600);
}

void loop() 
{  
  temp = readTemp();   // Accept Temperature Values from Function
  Serial.print("\n Temperature in Celsius = ");
  Serial.print(temp);
   
     if(temp < tempMin)
   {   
       fanSpeed = 0;      // fan is not spinning
       analogWrite(fan,fanSpeed); 
       fanLCD=0;
       digitalWrite(fan,LOW);       
   }
    
   if((temp >= tempMin) && (temp <= tempMax)) // if temperature is higher than minimum temp
   {  
       fanSpeed = temp;
       //fanSpeed=1.5*fanSpeed;//map(temp, tempMin, tempMax, 0, 100); // the actual speed of fan//map(temp, tempMin, tempMax, 32, 255);
       fanLCD = map(temp, tempMin, tempMax, 0, 100);  // speed of fan to display on LCD100
       analogWrite(fan, fanSpeed);  // spin the fan at the fanSpeed speed

       //digitalWrite(fan,HIGH);
   } 
   
   if(temp > tempMax) // if temp is higher than tempMax
     {        
     digitalWrite(led, HIGH);  // turn on led 
     } 
   else               // else turn of led
     {                    
     digitalWrite(led, LOW); 
     }
   
   lcd.print("Temp : ");
   lcd.print(temp);      // display the temperature
   lcd.print(" C ");
   lcd.setCursor(0,1);   // move cursor to next line
   lcd.print("FanS :");
   lcd.print(fanSpeed);    // display the fan speed
   lcd.print("%");
   lcd.print(" Ldr:");
   lcd.print(LDRReading);
   delay(200);
   lcd.clear();   




LDRReading = analogRead(LDR);
   //Serial.println(LDRReading);
  if(LDRReading<=20)
  {
     digitalWrite(LIGHT,LOW);
  }
  else
  {
    digitalWrite(LIGHT,HIGH);
  }


}

float readTemp() {  // get the temperature and convert it to celsius
  temp = analogRead(tempPin);

  float milivlt = (temp/1024.0)*5000;   // accepted value from LM35 is in volts convert to mili volt
  float celsius = milivlt/10;           // convert mili volt value to Celsius

  return celsius;
  //return temp * 0.48828125;
}

