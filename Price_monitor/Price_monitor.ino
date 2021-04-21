#include <Arduino.h>
#include <U8g2lib.h>
#include <Encoder.h>

#ifdef U8X8_HAVE_HW_SPI
#include <SPI.h>
#endif
#ifdef U8X8_HAVE_HW_I2C
#include <Wire.h>
#endif

// Change these two numbers to the pins connected to your encoder.
//   Best Performance: both pins have interrupt capability
Encoder encoder(2,3);

//////////////////////////////////D0,D1, D2, D3,D4,D5,D6,D7, EN,RS/DI,CS1, CS2 /////////////////////////////////////////////////
U8G2_KS0108_128X64_F u8g2(U8G2_R0, 8, 9, 10, 11, 4, 5, 6, 7, 18, 17, 14, 15, /*cs2=*/ U8X8_PIN_NONE, /* reset=*/  U8X8_PIN_NONE);   // Set
////////////// RST = 5V, R/W = GND /////////////////

void drawIcon(const uint8_t* iconName,u8g2_uint_t  x,u8g2_uint_t  y,uint16_t  glyph);
void readEncoder();

long oldPosition  = -999;

volatile uint8_t menuSelection = 2;
uint8_t selection = 1;
bool updateScreen = true;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  u8g2.begin();  
  u8g2.firstPage(); 
  do{
    bootPage();    
  }while(u8g2.nextPage());
}

void loop() {
  // put your main code here, to run repeatedly:
  readEncoder();

  //Updating the dispaly
  if(updateScreen)
  {
    u8g2.firstPage();  
    do {
      int ch = (menuSelection);
      switch(ch){
          case 0:
            menuPage();
            break;
          case 1:
            PowerStatus();
            break;
          case 2:
            lastFailedPrint();
            break;
          case 3:
            printerStats();
            break;
          case 4:
            screenSaver();
            break;
          case 5:
            settings();
            break;
          default:
            Serial.println(F("Default Screen"));
        }
      updateScreen = false;
      }while ( u8g2.nextPage() );
  }

  
}
