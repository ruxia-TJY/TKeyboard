/*
 * TKeyboard2
 * 一个基于32U4的小键盘项目
 * 
 * 开源链接: https://github.com/ruxia-TJY/TKeyboard
 * 元器件:
 *  > EEPROM：AT24C04
 *  > 按键芯片：BC6301
 *  > LED控制：74LS595
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

// 位操作
#define setbit(x,y) x|=(1<<y)
#define clrbit(x,y) x&=~(1<<y)
#define getbit(x,y) ((x & (1 << y)) >> y)

// 特殊功能相应的位置，详见下面的LED定义LEDLS595_LED_DATA
#define LED_NUM_LOCK_BIT 2
#define LED_CAPS_LOCK_BIT 1
#define LED_SCROLL_LOCK_BIT 0

int currentStateCLK1;
int currentStateCLK2;
int lastStateCLK1;
int lastStateCLK2;
unsigned long lastButton1Press = 0;
unsigned long lastButton2Press = 0;

// LED状态列表，通过此列表设置每个LED的亮暗
//int LS595_LED_DATA[8] = {0, 0, 0, 0, 0, 0, 0, 0};
unsigned char LS595_LED_DATA = 0;


// BC6301芯片
SoftwareSerial swSerial(8, 6);
BcKeyScan Keypad(swSerial);

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

// 每隔一段时间清屏
unsigned int freq = 0;

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
    sendKEY(Keypad.getKeyValue());
  }

  // 旋转编码器
  currentStateCLK1 = digitalRead(CLK1_PIN);
  currentStateCLK2 = digitalRead(CLK2_PIN);

  if (currentStateCLK1 != lastStateCLK1 && currentStateCLK1 == 1) {
    if (digitalRead(DT1_PIN) != currentStateCLK1) {
      // 旋钮1右旋
      sendKEY(30);
    }
    else {
      // 旋钮1左旋
      sendKEY(29);
    }
  }

  lastStateCLK1 = currentStateCLK1;

  int btn1State = digitalRead(SW1_PIN);

  if (btn1State == LOW) {
    if (millis() - lastButton1Press > 50) {
      // 旋钮1按下
      sendKEY(31);
    }
    lastButton1Press = millis();
  }


  if (currentStateCLK2 != lastStateCLK2 && currentStateCLK2 == 1) {
    if (digitalRead(DT2_PIN) != currentStateCLK2) {
      // 旋钮2右旋
      sendKEY(33);
    }
    else {
      // 旋钮2左旋
      sendKEY(32);
    }
  }

  lastStateCLK2 = currentStateCLK2;

  int btn2State = digitalRead(SW2_PIN);

  if (btn2State == LOW) {
    if (millis() - lastButton2Press > 50) {
      // 旋钮2按下
      sendKEY(34);
    }
    lastButton2Press = millis();
  }


  // 设置Led列表开关
  if((BootKeyboard.getLeds() & LED_CAPS_LOCK))
    setbit(LS595_LED_DATA,LED_CAPS_LOCK_BIT);
  else
    clrbit(LS595_LED_DATA,LED_CAPS_LOCK_BIT);

  if((BootKeyboard.getLeds() & LED_NUM_LOCK))
    setbit(LS595_LED_DATA,LED_NUM_LOCK_BIT);
  else
    clrbit(LS595_LED_DATA,LED_NUM_LOCK_BIT);

  if((BootKeyboard.getLeds() & LED_SCROLL_LOCK))
    setbit(LS595_LED_DATA,LED_SCROLL_LOCK_BIT);
  else
    clrbit(LS595_LED_DATA,LED_SCROLL_LOCK_BIT);

    
  // 根据LS595_LED_DATA设置每个LED的开关
  setLeds();
  delay(1);
}


// 根据LS595_LED_DATA设置LED。
void setLeds()
{
  digitalWrite(LS595_LATCH_PIN, LOW);
  shiftOut(LS595_DATA_PIN,LS595_CLOCK_PIN,MSBFIRST,LS595_LED_DATA);
  digitalWrite(LS595_LATCH_PIN, HIGH);
}
