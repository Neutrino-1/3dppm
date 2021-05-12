void drawFrame(void (*drawableFrame)())
{
  u8g2.firstPage(); 
  do{
     drawableFrame(); 
  }while(u8g2.nextPage());
}

void drawIcon(const uint8_t* iconName,u8g2_uint_t  x,u8g2_uint_t  y,uint16_t  glyph)
{
    u8g2.setFont(iconName);
    u8g2.drawGlyph(x,y,glyph);
}

void bootPage()
{
  drawIcon(u8g2_font_open_iconic_play_4x_t,DISPLAY_WIDTH/2-12,DISPLAY_HEIGHT-22,64); 
  u8g2.setFont(u8g2_font_glasstown_nbp_tf);
  uint8_t x_text_position = (DISPLAY_WIDTH - 13*5)/2;
  u8g2.setCursor(x_text_position,63);
  u8g2.print(F("Price Monitor"));
}

void powerStatus()
{
  //current consumption
  //power consumption
  //price 
}

void printerInfo()
{
  int xoffest = 17;
  //filament type
  //filament cost
  //filament weight

  /*Title*/
   u8g2.setFont(u8g2_font_glasstown_nbp_tf);
   u8g2.setCursor((DISPLAY_WIDTH - 13*5)/2 + 10,17);
   u8g2.print(F("Filament Info"));

   /*Filament type*/
   u8g2.setFont(u8g2_font_micro_tr);
   u8g2.setCursor(25+xoffest,35);
   u8g2.print(F("Type"));

   if (filamentInfoData[0] < 0)
      filamentInfoData[0] = 0;
   else if (filamentInfoData[0] > 9)
      filamentInfoData[0] = 9;
   
   if((counter+1)% 3 == 1 && editable)
    {
        Serial.println(filamentInfoData[0]);
        Serial.println(filamentType[filamentInfoData[0]]);
        u8g2.setFont(u8g2_font_open_iconic_arrow_1x_t);
        if(filamentInfoData[0] > 0)
           u8g2.drawGlyph(55+xoffest,35,77);
        if(filamentInfoData[0] < 9)
        {
           u8g2.drawGlyph((filamentType[filamentInfoData[0]].length()*5)+59+xoffest,35,78);
        }
    }
    
   u8g2.setFont(u8g2_font_micro_tr);
   u8g2.setCursor(63+xoffest,34);
   u8g2.print(filamentType[filamentInfoData[0]]);

   /*Filament Cost*/
   u8g2.setCursor(25+xoffest,48);
   u8g2.print(F("Cost"));
   
   if((counter+1)% 3 == 2 && editable)
    {
    u8g2.setFont(u8g2_font_open_iconic_arrow_1x_t);
    if(filamentInfoData[1] > 0)
    u8g2.drawGlyph(55+xoffest,48,77);
    u8g2.drawGlyph(71+xoffest,48,78);
    }
    
   u8g2.setFont(u8g2_font_micro_tr);
   u8g2.setCursor(63+xoffest,47);
   u8g2.print(filamentInfoData[1]*5);

   /*Model Weight*/
   u8g2.setCursor(25+xoffest,60);
   u8g2.print(F("Weight"));
   
    if((counter+1)% 3 == 0 && editable)
    {
      u8g2.setFont(u8g2_font_open_iconic_arrow_1x_t);
      if(filamentInfoData[2] > 0)
      u8g2.drawGlyph(55+xoffest,60,77);
      u8g2.drawGlyph(71+xoffest,60,78);
    }

   u8g2.setFont(u8g2_font_micro_tr);
   u8g2.setCursor(63+xoffest,59);
   u8g2.print(filamentInfoData[2]*2);
  
}

void Timerclock()
{
   u8g2.setFont(u8g2_font_ncenB18_tn);
   u8g2.setCursor((DISPLAY_WIDTH - 5*12)/2,DISPLAY_HEIGHT/2+12);
   u8g2.print(F("11:55"));

   u8g2.setFont(u8g2_font_micro_tr);
   u8g2.setCursor((DISPLAY_WIDTH - 22*5)/2 + 11,63);
   u8g2.print("Price of the print : $25");
}

void pastPrint()
{
   //selection list with time and cost
}

void menuPage()
{    
    detachInterrupt(ENCDT);
    detachInterrupt(ENCCLK); 
    for(int i = 0; i < 3; i++)
    {   
       currentMenuPostion = (counter+1)%MENUITEMS + 1;
       int menuIconToPrint = (counter+i)%MENUITEMS;
       if(i == 1)
       {
          u8g2.drawRBox((ICON_WIDTH + ICON_GAP)+ 4,DISPLAY_HEIGHT-18-ICON_HEIGHT,ICON_WIDTH+6,ICON_HEIGHT+5,4);
          u8g2.setDrawColor(0); 
          drawIcon(menu_entry_list[menuIconToPrint].largeIcon,(ICON_WIDTH + ICON_GAP)+7,DISPLAY_HEIGHT-15,menu_entry_list[menuIconToPrint].icon);
          u8g2.setDrawColor(1); 
          u8g2.setFont(u8g2_font_micro_tr);
          uint8_t x_text_position = (DISPLAY_WIDTH - menu_entry_list[menuIconToPrint].name.length()*5)/2;
          u8g2.setCursor(x_text_position+9,63);
          u8g2.print(menu_entry_list[menuIconToPrint].name);
          continue;
       }
       drawIcon(menu_entry_list[menuIconToPrint].smallIcon,i*(ICON_WIDTH*1.4)+15,DISPLAY_HEIGHT-23,menu_entry_list[menuIconToPrint].icon);
    }
    Serial.println(counter);
    Serial.println();
    attachInterrupt(ENCDT, updateEncoder, CHANGE);
    attachInterrupt(ENCCLK, updateEncoder, CHANGE);
}
