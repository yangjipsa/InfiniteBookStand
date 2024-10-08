#include <Adafruit_NeoPixel.h>
#define PIN 7
#define NUMPIXELS 12


Adafruit_NeoPixel pixels(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);
unsigned char Rc=0,Gc=0,Bc=0;


void setup() {
  pixels.begin();
  pixels.setPixelColor(0, pixels.Color(0, 0, 0));
  pixels.show();
  pixels.clear(); // Set all pixel colors to 'off'
}

void loop() 
{
  unsigned char tRed = random(0, 256);
  unsigned char tGre = random(0, 256);
  unsigned char tBlu = random(0, 256);

  ColorChange(0,tRed,tGre,tBlu);
  
  delay(5000);
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
