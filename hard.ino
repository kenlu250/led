#include <SoftwareSerial.h>
SoftwareSerial BluetoothSerial(3,4); // RX, TX(3接BT Tx,4接BT Rx)
#include <Adafruit_NeoPixel.h>
#define PIN            6
#define NUMPIXELS      16
byte red,green,blue;
int i;
char code;
byte value=0; //brightness
Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);
void setup()
{
  Serial.begin(9600);
  BluetoothSerial.begin(9600);
  pixels.begin(); 
  pixels.setBrightness(value);  
}
void loop() 
{
  if(BluetoothSerial.available())
  {
    delay(50);
    code=BluetoothSerial.read(); 
    Serial.print("code=");
    Serial.println(code);
    if(code=='0')
    {
        pixels.setBrightness(0);    //min brightness  
        display(0,0,0);             //off light                     
    }
    else if(code=='1')
    {
        pixels.setBrightness(255);  //max brightness
        display(255,255,255);       //on light        
    }
    else if(code=='r')
    {
      red=BluetoothSerial.read();
      Serial.print("red=");
      Serial.println(red);       
    }
    else if(code=='g')
    {
      green=BluetoothSerial.read();
      Serial.print("green=");
      Serial.println(green);         
    }
    else if(code=='b')
    {
      blue=BluetoothSerial.read();
      Serial.print("blue=");
      Serial.println(blue);         
    }    
    else if(code=='s')
    {
      value=BluetoothSerial.read();
      Serial.print("value=");
      Serial.println(value);     
      if(value<=20)
        pixels.setBrightness(0);  
      else
        pixels.setBrightness(value);          
    }
    display(red,green,blue);
  }
}   
void display(byte R, byte G, byte B)
{ 
  for(i=0;i<NUMPIXELS;i++)
  {
     pixels.setPixelColor(i,R,G,B); // num,red,green,blue
     pixels.show(); // This sends the updated pixel color to the hardware.
  }
}    
