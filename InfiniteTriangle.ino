#include <SoftwareSerial.h>
#include <Adafruit_NeoPixel.h>
#define PIN 7
#define NUMPIXELS 12


SoftwareSerial bt(3,2);
Adafruit_NeoPixel pixels(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);
uint8_t Rc=0,Gc=0,Bc=0;


void setup() {
  Serial.begin(9600);
  bt.begin(9600);
  pixels.begin();
  pixels.setPixelColor(0, pixels.Color(Rc, Gc, Bc));
  pixels.show();
  pixels.clear(); // Set all pixel colors to 'off'
}

void loop() {
  if(bt.available()){
    String rcvData = "";
    rcvData = bt.readString();
    //Serial.write(bt.read());
    Serial.println(rcvData);
    if(rcvData[0] == '0')
    { // Color Mode
      String red = rcvData.substring(rcvData.indexOf('r')+1, rcvData.indexOf('g'));
      String gre = rcvData.substring(rcvData.indexOf('g')+1, rcvData.indexOf('b'));
      String blu = rcvData.substring(rcvData.indexOf('b')+1, rcvData.indexOf('!'));

      int tRed = red.toInt();
      int tGre = gre.toInt();
      int tBlu = blu.toInt();
      
      //Serial.println(tRed);
      //Serial.println(tGre);
      //Serial.println(tBlu);  

      ColorChange(0,tRed,tGre,tBlu);

    }
    else if (rcvData[0] == '1') 
    { // random Color
      //Serial.println("mode 1");   
      int tRed = random(0,256);
      int tGre = random(0,256);
      int tBlu = random(0,256);
      
      //Serial.println(tRed);
      //Serial.println(tGre);
      //Serial.println(tBlu);  

      ColorChange(0,tRed,tGre,tBlu);

    }
    else
    { // Off
      int tRed = 0;
      int tGre = 0;
      int tBlu = 0;
      
      //Serial.println(tRed);
      //Serial.println(tGre);
      //Serial.println(tBlu);  

      ColorChange(0,tRed,tGre,tBlu);
      pixels.clear(); // Set all pixel colors to 'off'
    }
    
  }
}


void ColorChange(unsigned int N, uint8_t Rt, uint8_t Gt, uint8_t Bt)
{
  int dR = Rt - Rc;
  int dG = Gt - Gc;
  int dB = Bt - Bc;
  int showSpeed = 3;

  if (dR > 0)
  {
    for (int i=0 ; i <= dR ; i++)
    {
      for (int n=0 ; n<NUMPIXELS ; n++)
        pixels.setPixelColor(n, pixels.Color(Rc + i, Gc, Bc));
      pixels.show(); delay(showSpeed);  
    }
  }
  else 
  {
    for (int i=0 ; i <= (-1)*dR ; i++)
    {
      for (int n=0 ; n<NUMPIXELS ; n++)
        pixels.setPixelColor(n, pixels.Color(Rc - i, Gc, Bc));
      pixels.show(); delay(showSpeed);
    }
  }

  if (dG > 0)
  {
    for (int i=0 ; i <= dG ; i++)
    {
      for (int n=0 ; n<NUMPIXELS ; n++)
        pixels.setPixelColor(n,pixels.Color(Rt, Gc + i, Bc));
      pixels.show(); delay(showSpeed);
    }
  }
  else 
  {
    for (int i=0 ; i <= (-1)*dG ; i++)
    {
      for (int n=0 ; n<NUMPIXELS ; n++)
        pixels.setPixelColor(n, pixels.Color(Rt, Gc - i, Bc));
      pixels.show(); delay(showSpeed);
    }
  }

  if (dB > 0)
  {
    for (int i=0 ; i <= dB ; i++)
    {
      for (int n=0 ; n<NUMPIXELS ; n++)
        pixels.setPixelColor(n, pixels.Color(Rt, Gt, Bc + i));
      pixels.show(); delay(showSpeed);
    }
  }
  else 
  {
    for (int i=0 ; i <= (-1)*dB ; i++)
    {
      for (int n=0 ; n<NUMPIXELS ; n++)
        pixels.setPixelColor(n,pixels.Color(Rt, Gt, Bc - i));
      pixels.show(); delay(showSpeed);
    }
  }

  Rc = Rt;
  Gc = Gt;
  Bc = Bt;  
}
