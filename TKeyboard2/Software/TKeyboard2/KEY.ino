/*
   AT24c04一次只可以写入16个字节
   \n ENTER
   \c Ctrl
   \s Shift
   \a Alt
*/
void readKEYFromEEPROM(String & KEY, int place, bool addr)
{
  if (addr)
    Wire.beginTransmission(EEPROM_I2C_ADDRESS);
  else
    Wire.beginTransmission(0x51);
  Wire.write(place);
  Wire.endTransmission();
  delay(5);
  Wire.requestFrom(EEPROM_I2C_ADDRESS, 16);
  delay(10);
  if (Wire.available()) {
    KEY = "";
    for (int i = 0; i < 16; i++)
    {
      byte data = Wire.read();
      if (data != 255)
        KEY += (char)data;
    }
  }
}

// 从EEPROM中读取键值
void readFromEEPROM()
{
  readKEYFromEEPROM(KEY0, 0, true);
  readKEYFromEEPROM(KEY1, 16, true);
  readKEYFromEEPROM(KEY2, 32, true);
  readKEYFromEEPROM(KEY3, 48, true);
  readKEYFromEEPROM(KEY4, 64, true);
  readKEYFromEEPROM(KEY5, 80, true);
  readKEYFromEEPROM(KEY6, 96, true);
  readKEYFromEEPROM(KEY7, 112, true);
  readKEYFromEEPROM(KEY8, 128, true);
  readKEYFromEEPROM(KEY9, 144, true);
  readKEYFromEEPROM(KEY10, 160, true);
  readKEYFromEEPROM(KEY11, 176, true);
  readKEYFromEEPROM(KEY12, 192, true);
  readKEYFromEEPROM(KEY13, 208, true);
  readKEYFromEEPROM(KEY14, 224, true);
  readKEYFromEEPROM(KEY15, 240, true);

  readKEYFromEEPROM(KEY16, 0, false);
  readKEYFromEEPROM(KEY17, 16, false);
  readKEYFromEEPROM(KEY18, 32, false);
  readKEYFromEEPROM(KEY19, 48, false);
  readKEYFromEEPROM(KEY20, 64, false);
  readKEYFromEEPROM(KEY21, 80, false);
  readKEYFromEEPROM(KEY22, 96, false);
  readKEYFromEEPROM(KEY23, 112, false);
  readKEYFromEEPROM(KEY24, 128, false);
  readKEYFromEEPROM(EC11_1_LEFT, 144, false);
  readKEYFromEEPROM(EC11_1_RIGHT, 160, false);
  readKEYFromEEPROM(EC11_1_CLK, 176, false);
  readKEYFromEEPROM(EC11_2_LEFT, 192, false);
  readKEYFromEEPROM(EC11_2_RIGHT, 208, false);
  readKEYFromEEPROM(EC11_2_CLK, 224, false);
}


void setKEYEEPROM(String &KEY, int place, bool addr)
{
  if (addr) {
    Wire.beginTransmission(EEPROM_I2C_ADDRESS);
  }
  else {
    Wire.beginTransmission(0x51);
  }
  Wire.write(place);
  for (int i = 0; i < KEY.length(); i++) {
    Wire.write(KEY[i]);
  }
  for (int i = KEY.length(); i < 16; i++) {
    Wire.write(255);
  }
  Wire.endTransmission();
}

void setEEPROM()
{
  setKEYEEPROM(KEY0, 0, true); delay(10);
  setKEYEEPROM(KEY1, 16, true); delay(10);
  setKEYEEPROM(KEY2, 32, true); delay(10);
  setKEYEEPROM(KEY3, 48, true); delay(10);
  setKEYEEPROM(KEY4, 64, true); delay(10);
  setKEYEEPROM(KEY5, 80, true); delay(10);
  setKEYEEPROM(KEY6, 96, true); delay(10);
  setKEYEEPROM(KEY7, 112, true); delay(10);
  setKEYEEPROM(KEY8, 128, true); delay(10);
  setKEYEEPROM(KEY9, 144, true); delay(10);
  setKEYEEPROM(KEY10, 160, true); delay(10);
  setKEYEEPROM(KEY11, 176, true); delay(10);
  setKEYEEPROM(KEY12, 192, true); delay(10);
  setKEYEEPROM(KEY13, 208, true); delay(10);
  setKEYEEPROM(KEY14, 224, true); delay(10);
  setKEYEEPROM(KEY15, 240, true); delay(10);

  setKEYEEPROM(KEY16, 0, false); delay(10);
  setKEYEEPROM(KEY17, 16, false); delay(10);
  setKEYEEPROM(KEY18, 32, false); delay(10);
  setKEYEEPROM(KEY19, 48, false); delay(10);
  setKEYEEPROM(KEY20, 64, false); delay(10);
  setKEYEEPROM(KEY21, 80, false); delay(10);
  setKEYEEPROM(KEY22, 96, false); delay(10);
  setKEYEEPROM(KEY23, 112, false); delay(10);
  setKEYEEPROM(KEY24, 128, false); delay(10);
  setKEYEEPROM(EC11_1_LEFT, 144, false); delay(10);
  setKEYEEPROM(EC11_1_RIGHT, 160, false); delay(10);
  setKEYEEPROM(EC11_1_CLK, 176, false); delay(10);
  setKEYEEPROM(EC11_2_LEFT, 192, false); delay(10);
  setKEYEEPROM(EC11_2_RIGHT, 208, false); delay(10);
  setKEYEEPROM(EC11_2_CLK, 224, false); delay(10);
}

void showKEY(String& KEY)
{
  Serial.println(KEY);

  bool isEscape = false;    // 是否转义
  bool isCaps = false;      // 是否强制转换大写

  // 循环字符串字符
  for (int i = 0; i < KEY.length(); i++) {
    if (KEY[i] == '\\') {
      isEscape = true;
      continue;
    }

    if (isEscape) {
      switch (KEY[i]) {
        case 'b'://是否强制转换大写
          isCaps = true;
          break;
        case 'n'://Enter
          Keyboard.write(KEY_ENTER);
          break;
        case 'a':// Alt
          Keyboard.write(KEY_RIGHT_ALT);
          break;
        case 'c'://Ctrl
          Keyboard.write(KEY_RIGHT_CTRL);
          break;
        case 'u':// 音量上升
          Consumer.write(MEDIA_VOL_UP);
          //          drawVOL(true);
          break;
        case 'd'://音量下降
          Consumer.write(MEDIA_VOL_DOWN);
          //          drawVOL(false);
          break;
        case 'j'://亮度上升
          Consumer.write(CONSUMER_BRIGHTNESS_UP);
          break;
        case 'k'://亮度下降
          Consumer.write(CONSUMER_BRIGHTNESS_DOWN);
          break;
        case 'm':// 打开/取消静音
          Consumer.write(MEDIA_VOL_MUTE);
          break;
      }
      isEscape = false;
    }
    else {
      // 当开启CAPS时候，可以防止输入法，但是，原本的字符串大写也会变成小写。
      if (isCaps && (LS595_LED_DATA[5] == 0) && (KEY[i] >= 'a' && KEY[i] <= 'z')) {
        Serial.println("未开启大写");
        Keyboard.write(KEY_CAPS_LOCK);
        Keyboard.write(KEY[i]);
        Keyboard.write(KEY_CAPS_LOCK);
      }
      else
        Keyboard.write(KEY[i]);
    }
  }
}

// 对EEPROM设值
//void setKeyForEEPROM()
//{
//  KEY0 = "\\bV";
//  KEY1 = "\\bM";
//  KEY2 = "\\bL";
//  KEY3 = "\\bW";
//  KEY4 = "\\bC";
//  KEY5 = "\\bK";
//  KEY6 = "\\bI";
//  KEY7 = "\\bB";
//  KEY8 = "\\bS";
//  KEY9 = "\\bY";
//  KEY10 = "\\bE";
//  KEY11 = "\\bQ";
//  KEY12 = "\\bO";
//  KEY13 = "\\bP";
//  KEY14 = "\\bT";
//  KEY15 = "\\bA";
//  KEY16 = "\\bH";
//  KEY17 = "\\bR";
//  KEY18 = "\\bZ";
//  KEY19 = "\\bX";
//  KEY20 = "+";
//  KEY21 = "-";
//  KEY22 = "*";
//  KEY23 = "/";
//  KEY24 = "=";
//
//  EC11_1_LEFT = "\\d";
//  EC11_1_RIGHT = "\\u";
//  EC11_1_CLK = "\\m";
//
//  EC11_2_LEFT = "\\k";
//  EC11_2_RIGHT = "\\j";
//  EC11_2_CLK = "";
//  // 写入EEPROM
//  setEEPROM();
//}
