#include "oled.h"

U8G2_SH1106_128X64_NONAME_F_HW_I2C u8g2(U8G2_R0);

MENU_ITEM selectedItem;

void initScreen() {
  selectedItem = BLANK;

  u8g2.begin();

  u8g2.clearBuffer();
  u8g2.setFont(u8g2_font_ncenB08_tr);
  u8g2.drawStr(0, 24, "Hi there!");
  u8g2.sendBuffer();
}

void clearScreen() {
  u8g2.clearBuffer();
}

void applyScreenBuffer() {
  u8g2.sendBuffer();
}

void drawMainScreen() {
  char timeStr[9];
  snprintf(timeStr, sizeof(timeStr), "%02d:%02d:%02d", hour, minute, second);
  u8g2.setFont(u8g2_font_ncenB12_tr);
  uint8_t timeStrWidth = u8g2.getStrWidth(timeStr);
  uint8_t timeStrX = (128 - timeStrWidth) / 2;
  uint8_t timeStrY = (64 + u8g2.getAscent()) / 2;
  u8g2.drawStr(timeStrX, timeStrY, timeStr);

  char dateStr[11];
  u8g2.setFont(u8g2_font_ncenB08_tr);
  snprintf(dateStr, sizeof(dateStr), "%02d/%02d/%04d", date, month, year);
  uint8_t dateStrWidth = u8g2.getStrWidth(dateStr);
  uint8_t dateStrX = (128 - dateStrWidth) / 2;
  uint8_t dateStrY = 64 - u8g2.getAscent();
  u8g2.drawStr(dateStrX, dateStrY, dateStr);
}

void drawAlarmScreen() {

}

void updateSelection(uint8_t direction) {
  u8g2.clearBuffer();
  drawMainScreen();

  if(direction > 0) {
    selectedItem = static_cast<MENU_ITEM>(selectedItem + 1);
  }
  else {
    selectedItem = static_cast<MENU_ITEM>(selectedItem - 1);
  }
}
