#include "oled.h"

U8G2_SH1106_128X64_NONAME_F_HW_I2C u8g2(U8G2_R0);

void initScreen() {
  u8g2.begin();

  u8g2.clearBuffer();
  u8g2.setFont(u8g2_font_ncenB08_tr);
  u8g2.drawStr(0, 24, "Time:");
  u8g2.sendBuffer();
}

void drawMainScreen() {
  u8g2.begin();
  u8g2.clearBuffer();

  u8g2.setFont(u8g2_font_ncenB08_tr);
  u8g2.setCursor(0, 14);
  u8g2.print("12:34:56");

  u8g2.setCursor(0, 32);
  u8g2.print("21/04/2025");

  u8g2.setCursor(0, 50);
  u8g2.print("Temp: 23C");

  u8g2.sendBuffer();
}
