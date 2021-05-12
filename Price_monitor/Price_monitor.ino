// Change these these pins numbers to the pins connected to your encoder.
#define ENCDT 18
#define ENCCLK 19
#define ENCBTN 12

#define BUZZER 5

//Number of items on the menu
#define MENUITEMS 5

//Dispaly settings
#define DISPLAY_WIDTH 128
#define DISPLAY_HEIGHT 64
#define ICON_WIDTH 32
#define ICON_HEIGHT 32
#define ICON_GAP 13

#include <Arduino.h>
#include <U8g2lib.h>
#include <OneButton.h>

#ifdef U8X8_HAVE_HW_SPI
#include <SPI.h>
#endif
#ifdef U8X8_HAVE_HW_I2C
#include <Wire.h>

#endif
////////////////////////////////////D0,D1, D2, D3,D4,D5,D6,D7, EN,RS/DI,CS1, CS2 /////////////////////////////////////////////////
//U8G2_KS0108_128X64_F u8g2(U8G2_R0, 8, 9, 10, 11, 4, 5, 6, 7, 18, 17, 14, 15, /*cs2=*/ U8X8_PIN_NONE, /* reset=*/  U8X8_PIN_NONE);   // Set
//////////////// RST = 5V, R/W = GND /////////////////

U8G2_SH1106_128X64_NONAME_F_HW_I2C u8g2(U8G2_R0, /* reset=*/ U8X8_PIN_NONE);
OneButton encoderButton(ENCBTN, true);

void drawIcon(const uint8_t* iconName,u8g2_uint_t  x,u8g2_uint_t  y,uint16_t  glyph);
void bootPage();
void powerStatus();
void printerInfo();
void pastPrint();
void Timerclock();
void menuPage();

float calculatePWR(float voltage,float current);
float calculatePWRP(float power);
float calculatePrintingCost(float manPowerCost,float powerCost,float materialCost);
float currencyConversion(float value, float exchangeRate);

ICACHE_RAM_ATTR void updateEncoder();
ICACHE_RAM_ATTR void checkTicks();

uint8_t counter = 5; //Start drawing from the last (cyclic)
uint8_t currentMenuPostion = 0;
uint8_t currentStateCLK;
uint8_t lastStateCLK;

volatile unsigned long lastEncodeUpdate = 0;
volatile bool updateScreen = true;
volatile bool inSideMenu = false;
volatile bool editable = false;

bool relayTurnOn = false;

String menuListNames[] = {"Power Status","Printer info","Past Print","Clock","Start Monitor"};
String filamentType[] = {"PLA","ABS","PETG","CPE","HIPS","Nylon","PC","PLA","PVA","TPU"};
int filamentInfoData[] = {0,0,0}; //type, cost of filament roll , weight of 1-print

struct menu_entry_type
{
    const uint8_t *smallIcon;
    const uint8_t *largeIcon;
    uint16_t icon;
    String name;
};

struct menu_entry_type menu_entry_list[] =
{
  { u8g2_font_open_iconic_embedded_2x_t,u8g2_font_open_iconic_embedded_4x_t,67, menuListNames[0]},
  { u8g2_font_open_iconic_thing_2x_t,u8g2_font_open_iconic_thing_4x_t,66, menuListNames[1]},
  { u8g2_font_open_iconic_app_2x_t,u8g2_font_open_iconic_app_4x_t,64, menuListNames[2]},
  { u8g2_font_open_iconic_app_2x_t,u8g2_font_open_iconic_app_4x_t,69, menuListNames[3]},
  { u8g2_font_open_iconic_play_2x_t,u8g2_font_open_iconic_play_4x_t,69, menuListNames[4]},
//  { NULL, 0, NULL } 
};

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  u8g2.begin();  
  drawFrame(printerInfo);
  delay(5000);
  pinMode(ENCDT,INPUT_PULLUP);
  pinMode(ENCCLK,INPUT_PULLUP);
  pinMode(ENCBTN,INPUT_PULLUP);
  
  // Read the initial state of CLK
  lastStateCLK = digitalRead(ENCCLK);
  
  // Call updateEncoder() when any high/low changed seen
  attachInterrupt(ENCDT, updateEncoder, CHANGE);
  attachInterrupt(ENCCLK, updateEncoder, CHANGE);
  attachInterrupt(ENCBTN, checkTicks, CHANGE);

  encoderButton.attachClick(buttonForward);
  encoderButton.setPressTicks(1000); // that is the time when LongPressStart is called
  encoderButton.attachLongPressStart(buttonBackward);
  
}

void loop() {
   encoderButton.tick();
   
  //Updating the dispaly
  if(updateScreen)
  {
    u8g2.firstPage();  
    do {
      
      if(!editable && !inSideMenu)
        currentMenuPostion = 0;//((counter+1)%MENUITEMS + 1);

      switch(currentMenuPostion){
          case 0:
            menuPage();
            break;
          case 1:
            powerStatus();
            break;
          case 2:
            printerInfo();
            break;
          case 3:
           pastPrint();
            break;
          case 4:
          Timerclock();
            break;
          default:
            Serial.println(F("Default Screen"));
        }
      updateScreen = false;
      }while ( u8g2.nextPage() );
  } 
}
