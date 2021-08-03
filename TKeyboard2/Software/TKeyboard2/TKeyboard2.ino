/*
   TKeyboard2
   一个基于32U4的小键盘项目

   EEPROM：AT24C04
   按键芯片：BC6301
   LED控制：74LS595
*/

#include<HID-Project.h>
#include<SoftwareSerial.h>
#include<bc_key_scan.h>
#include<Wire.h>
#include<Adafruit_GFX.h>
#include<Adafruit_SSD1306.h>
#include "KEY.h"
#include "OLED.h"

// 旋钮
#define CLK1_PIN 14
#define DT1_PIN 15
#define SW1_PIN 18
#define CLK2_PIN 9
#define DT2_PIN 10
#define SW2_PIN 16

// 74LS595芯片
#define LS595_DATA_PIN 21
#define LS595_LATCH_PIN 20
#define LS595_CLOCK_PIN 19

// EEPROM 地址，使用AT24C04芯片，有两个部分
#define EEPROM_I2C_ADDRESS_1 0x50
#define EEPROM_I2C_ADDRESS_2 0x51

// OLED
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET 4
#define OLED_I2C_ADDRESS 0x3c

int currentStateCLK1;
int currentStateCLK2;
int lastStateCLK1;
int lastStateCLK2;
unsigned long lastButton1Press = 0;
unsigned long lastButton2Press = 0;

// LED状态列表，通过此列表设置每个LED的亮暗
int LS595_LED_DATA[8] = {0, 0, 0, 0, 0, 0, 0, 0};
// BC6301芯片
SoftwareSerial swSerial(8, 6);
BcKeyScan Keypad(swSerial);

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

// 每隔一段时间清屏
int freq = 0;

void setup() {
  swSerial.begin(9600);
  BootKeyboard.begin();
  Consumer.begin();
  Keyboard.begin();
  Wire.begin();
  display.begin(SSD1306_SWITCHCAPVCC, OLED_I2C_ADDRESS);

  pinMode(CLK1_PIN, INPUT_PULLUP);
  pinMode(DT1_PIN, INPUT_PULLUP);
  pinMode(SW1_PIN, INPUT_PULLUP);
  pinMode(CLK2_PIN, INPUT_PULLUP);
  pinMode(DT2_PIN, INPUT_PULLUP);
  pinMode(SW2_PIN, INPUT_PULLUP);

  pinMode(LS595_DATA_PIN, OUTPUT);
  pinMode(LS595_LATCH_PIN, OUTPUT);
  pinMode(LS595_CLOCK_PIN, OUTPUT);

  lastStateCLK1 = digitalRead(CLK1_PIN);
  lastStateCLK2 = digitalRead(CLK2_PIN);
  
  // 从EEPROM存储中读取键值
  readFromEEPROM();
}

void loop() {
  // freq计次1000下，清屏
  freq++;
  if (freq == 1000) {
    display.clearDisplay();
    display.display();
    freq = 0;
  }

  // 按键
  Keypad.checkChanges();
  if (Keypad.isKeyChanged()) {
    // 从上->下，从左->右边。按键值依次是
    // 0  6   12  18  24
    // 1  7   13  19  25
    // 2  8   14  20  26
    // 3  9   15  21  27
    // 4  10  16  22  28
    // 这个地方代码多且丑，不知道Arduino有没有更好的方法
    switch (Keypad.getKeyValue()) {
      case 0:
        showKEY(KEY0);
        break;
      case 1:
        showKEY(KEY1);
        break;
      case 2:
        showKEY(KEY2);
        break;
      case 3:
        showKEY(KEY3);
        break;
      case 4:
        showKEY(KEY4);
      case 6:
        showKEY(KEY5);
        break;
      case 7:
        showKEY(KEY6);
        break;
      case 8:
        showKEY(KEY7);
        break;
      case 9:
        showKEY(KEY8);
        break;
      case 10:
        showKEY(KEY9);
        break;
      case 12:
        showKEY(KEY10);
        break;
      case 13:
        showKEY(KEY11);
        break;
      case 14:
        showKEY(KEY12);
        break;
      case 15:
        showKEY(KEY13);
        break;
      case 16:
        showKEY(KEY14);
        break;
      case 18:
        showKEY(KEY15);
        break;
      case 19:
        showKEY(KEY16);
        break;
      case 20:
        showKEY(KEY17);
        break;
      case 21:
        showKEY(KEY18);
        break;
      case 22:
        showKEY(KEY19);
        break;
      case 24:
        showKEY(KEY20);
        break;
      case 25:
        showKEY(KEY21);
        break;
      case 26:
        showKEY(KEY22);
        break;
      case 27:
        showKEY(KEY23);
        break;
      case 28:
        showKEY(KEY24);
        break;
    }
  }

  // 旋转编码器
  currentStateCLK1 = digitalRead(CLK1_PIN);
  currentStateCLK2 = digitalRead(CLK2_PIN);

  if (currentStateCLK1 != lastStateCLK1 && currentStateCLK1 == 1) {
    if (digitalRead(DT1_PIN) != currentStateCLK1) {
      // 旋钮1右旋
      showKEY(EC11_1_RIGHT);
    }
    else {
      // 旋钮1左旋
      showKEY(EC11_1_LEFT);
    }
  }

  lastStateCLK1 = currentStateCLK1;

  int btn1State = digitalRead(SW1_PIN);

  if (btn1State == LOW) {
    if (millis() - lastButton1Press > 50) {
      // 旋钮1按下
      showKEY(EC11_1_CLK);
    }
    lastButton1Press = millis();
  }


  if (currentStateCLK2 != lastStateCLK2 && currentStateCLK2 == 1) {
    if (digitalRead(DT2_PIN) != currentStateCLK2) {
      // 旋钮2右旋
      showKEY(EC11_2_RIGHT);
    }
    else {
      // 旋钮2左旋
      showKEY(EC11_2_LEFT);
    }
  }

  lastStateCLK2 = currentStateCLK2;

  int btn2State = digitalRead(SW2_PIN);

  if (btn2State == LOW) {
    if (millis() - lastButton2Press > 50) {
      // 旋钮2按下
      showKEY(EC11_2_CLK);
    }
    lastButton2Press = millis();
  }


  // 设置Led列表开关
  LS595_LED_DATA[5] = (BootKeyboard.getLeds() & LED_CAPS_LOCK) ? 1 : 0;
  LS595_LED_DATA[4] = (BootKeyboard.getLeds() & LED_NUM_LOCK) ? 1 : 0;
  LS595_LED_DATA[6] = (BootKeyboard.getLeds() & LED_SCROLL_LOCK) ? 1 : 0;
  
  // 根据LS595_LED_DATA列表设置每个LED的开关
  setLeds();
  delay(1);
}


void setLeds()
{
  digitalWrite(LS595_LATCH_PIN, LOW);
  for (int i = 0; i < 8; i++) {
    digitalWrite(LS595_CLOCK_PIN, LOW);
    digitalWrite(LS595_DATA_PIN, LS595_LED_DATA[i]);
    digitalWrite(LS595_CLOCK_PIN, HIGH);
  }
  digitalWrite(LS595_LATCH_PIN, HIGH);
}
