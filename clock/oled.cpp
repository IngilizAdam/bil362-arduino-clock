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
  // --- TIME ---
  char timeStr[9];
  snprintf(timeStr, sizeof(timeStr), "%02d:%02d:%02d", hour, minute, second);

  u8g2.setFont(u8g2_font_ncenB12_tr);
  uint8_t timeY = 20;
  uint8_t timeX = (128 - u8g2.getStrWidth(timeStr)) / 2;
  u8g2.drawStr(timeX, timeY, timeStr);

  // Draw boxes for selected time item
  int partWidth = u8g2.getStrWidth("00");
  int colonWidth = u8g2.getStrWidth(":");

  int hourX = timeX;
  int minX = hourX + partWidth + colonWidth;
  int secX = minX + partWidth + colonWidth;

  int boxY = timeY - u8g2.getAscent() - 2;
  int boxHeight = u8g2.getAscent() + 4;

  switch (selectedItem) {
    case HOUR:
      u8g2.drawRFrame(hourX - 2, boxY, partWidth + 4, boxHeight, 2);
      break;
    case MINUTE:
      u8g2.drawRFrame(minX - 2, boxY, partWidth + 4, boxHeight, 2);
      break;
    case SECOND:
      u8g2.drawRFrame(secX - 2, boxY, partWidth + 4, boxHeight, 2);
      break;
  }

  // --- DATE ---
  u8g2.setFont(u8g2_font_ncenB08_tr);
  char dateStr[20];
  snprintf(dateStr, sizeof(dateStr), "%02d/%02d/%04d", date, month, year);

  uint8_t dateY = 50;
  uint8_t dateX = (128 - u8g2.getStrWidth(dateStr)) / 2;
  u8g2.drawStr(dateX, dateY, dateStr);

  // Box for selected date part
  partWidth = u8g2.getStrWidth("00");
  colonWidth = u8g2.getStrWidth("/");

  int dayX = dateX;
  int monthX = dayX + partWidth + colonWidth;
  int yearX = monthX + partWidth + colonWidth;

  boxY = dateY - u8g2.getAscent() - 2;
  boxHeight = u8g2.getAscent() + 4;

  switch (selectedItem) {
    case DAY:
      u8g2.drawRFrame(dayX - 2, boxY, partWidth + 4, boxHeight, 2);
      break;
    case MONTH:
      u8g2.drawRFrame(monthX - 2, boxY, partWidth + 4, boxHeight, 2);
      break;
    case YEAR:
      u8g2.drawRFrame(yearX - 2, boxY, u8g2.getStrWidth("0000") + 4, boxHeight, 2);
      break;
  }
}

void drawAlarmScreen() {
  // --- Alarm Time ---
  char timeStr[6];
  snprintf(timeStr, sizeof(timeStr), "%02d:%02d", alarmHour, alarmMinute);

  u8g2.setFont(u8g2_font_ncenB14_tr);
  uint8_t timeX = (128 - u8g2.getStrWidth(timeStr)) / 2;
  uint8_t timeY = 24;
  u8g2.drawStr(timeX, timeY, timeStr);

  // Box around hour
  if (selectedItem == ALARM_HOUR) {
    char hourStr[3];
    snprintf(hourStr, sizeof(hourStr), "%02d", alarmHour);
    uint8_t hourX = timeX;
    uint8_t hourW = u8g2.getStrWidth(hourStr);
    u8g2.drawRFrame(hourX - 2, timeY - 14, hourW + 4, 16, 2);
  }

  // Box around minute
  if (selectedItem == ALARM_MINUTE) {
    char minStr[3];
    snprintf(minStr, sizeof(minStr), "%02d", alarmMinute);
    uint8_t minX = timeX + u8g2.getStrWidth("00:");
    uint8_t minW = u8g2.getStrWidth(minStr);
    u8g2.drawRFrame(minX - 2, timeY - 14, minW + 4, 16, 2);
  }

  // --- Tone Options ---
  u8g2.setFont(u8g2_font_6x10_tr);
  char* tone1 = "Tone 1";
  char* tone2 = "Tone 2";
  char* tone3 = "Tone 3";
  uint8_t toneY = 35;
  uint8_t toneX = (128 - u8g2.getStrWidth(tone1)) / 2;
  u8g2.drawStr(toneX, toneY, tone1);
  if(selectedItem == ALARM_TONE_1) {
    u8g2.drawRFrame(toneX - 2, toneY - 10, u8g2.getStrWidth(tone1) + 4, 16, 2);
  }
  toneY += 10;
  toneX = (128 - u8g2.getStrWidth(tone2)) / 2;
  u8g2.drawStr(toneX, toneY, tone2);
  if(selectedItem == ALARM_TONE_2) {
    u8g2.drawRFrame(toneX - 2, toneY - 10, u8g2.getStrWidth(tone2) + 4, 16, 2);
  }
  toneY += 10;
  toneX = (128 - u8g2.getStrWidth(tone3)) / 2;
  u8g2.drawStr(toneX, toneY, tone3);
  if(selectedItem == ALARM_TONE_3) {
    u8g2.drawRFrame(toneX - 2, toneY - 10, u8g2.getStrWidth(tone3) + 4, 16, 2);
  }
}

void drawScreen() {
  if(selectedItem < ALARM) {
    drawMainScreen();
  }
  else {
    drawAlarmScreen();
  }
}

void updateSelection(int direction) {
  if(direction > 0) {
    if (!selectionActive) {
      if(selectedItem < FINAL) {
        selectedItem = static_cast<MENU_ITEM>(selectedItem + 1);
      }
    }
    else {
      if(selectedItem == HOUR) {
        hour++;
        if(hour > 23) {
          hour = 0;
        }
      }
      else if(selectedItem == MINUTE) {
        minute++;
        if(minute > 59) {
          minute = 0;
        }
      }
      else if(selectedItem == SECOND) {
        second++;
        if(second > 59) {
          second = 0;
        }
      }
      else if(selectedItem == DAY) {
        date++;
        if(date > 31) {
          date = 1;
        }
      }
      else if(selectedItem == MONTH) {
        month++;
        if(month > 12) {
          month = 1;
        }
      }
      else if(selectedItem == YEAR) {
        year++;
        if(year > 2099) {
          year = 1900;
        }
      }
      else if(selectedItem == ALARM_HOUR) {
        alarmHour++;
        if(alarmHour > 23) {
          alarmHour = 0;
        }
      }
      else if(selectedItem == ALARM_MINUTE) {
        alarmMinute++;
        if(alarmMinute > 59) {
          alarmMinute = 0;
        }
      }
    }
  }
  else if(direction < 0) {
    if (!selectionActive) {
      if(selectedItem > BLANK) {
        selectedItem = static_cast<MENU_ITEM>(selectedItem - 1);
      }
    }
    else {
      if(selectedItem == HOUR) {
        hour--;
        if(hour < 0) {
          hour = 23;
        }
      }
      else if(selectedItem == MINUTE) {
        minute--;
        if(minute < 0) {
          minute = 59;
        }
      }
      else if(selectedItem == SECOND) {
        second--;
        if(second < 0) {
          second = 59;
        }
      }
      else if(selectedItem == DAY) {
        date--;
        if(date < 1) {
          date = 31;
        }
      }
      else if(selectedItem == MONTH) {
        month--;
        if(month < 1) {
          month = 12;
        }
      }
      else if(selectedItem == YEAR) {
        year--;
        if(year < 1900) {
          year = 2099;
        }
      }
      else if(selectedItem == ALARM_HOUR) {
        alarmHour--;
        if(alarmHour < 0) {
          alarmHour = 23;
        }
      }
      else if(selectedItem == ALARM_MINUTE) {
        alarmMinute--;
        if(alarmMinute < 0) {
          alarmMinute = 59;
        }
      }
    }
  }
}
