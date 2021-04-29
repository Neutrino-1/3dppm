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
  
}


void printerInfo()
{
  
}

void clock()
{
  
}

void pastPrint()
{
  
}

void settings()
{
}

void menuPage()
{    
    detachInterrupt(ENCDT);
    detachInterrupt(ENCCLK); 
    for(int i = 0; i < 3; i++)
    {   
       int menuIconToPrint = (counter+i)%5;
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
