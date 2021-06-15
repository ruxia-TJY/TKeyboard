/*
   TKeyboard
   小键盘项目
*/

#include <HID-Project.h>
#include <Keypad.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define OLED_RESET     4

#define CLK 7
#define DT 9
#define SW 8

#define ModeLED 5
#define BtnLED 6

#define OLED_SCREEN_WIDTH 128
#define OLED_SCREEN_HEIGHT 64

// 旋钮模式
bool IsModeVOL = true;
// 按键模式
bool IsBtnMusic = true;


int currentStateCLK;
int lastStateCLK;
unsigned long lastButtonPress = 0;

const byte MatKeyboard_ROWS = 3;
const byte MatKeyboard_COLS = 4;

char keys[MatKeyboard_ROWS][MatKeyboard_COLS] = {
  {'1', '2', '3', '4'},
  {'5', '6', '7', '8'},
  {'9', 'a', 'b', 'c'}
};

byte MatKeyboard_rowPin[MatKeyboard_ROWS] = {20, 19, 18};
byte MatKeyboard_colPin[MatKeyboard_COLS] = {10, 16, 14, 15};

Keypad keypad = Keypad(makeKeymap(keys), MatKeyboard_rowPin, MatKeyboard_colPin, MatKeyboard_ROWS, MatKeyboard_COLS);

Adafruit_SSD1306 display(OLED_SCREEN_WIDTH, OLED_SCREEN_HEIGHT, &Wire, OLED_RESET);

void setup() {
  
  pinMode(CLK, INPUT);
  pinMode(DT, INPUT);
  pinMode(SW, INPUT_PULLUP);

  pinMode(ModeLED, OUTPUT);
  pinMode(BtnLED, OUTPUT);

  Serial.begin(9600);
  Consumer.begin();
  System.begin();

  digitalWrite(ModeLED, HIGH);
  digitalWrite(BtnLED, HIGH);

  lastStateCLK = digitalRead(CLK);

  
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);  
  
  initDraw();
  display.display();
}

void initDraw()
{
  display.clearDisplay();//清屏
  display.setTextColor(WHITE);//开像素点发光
  
  display.setTextSize(2); //设置字体大小  
  display.setCursor(13, 5);//设置显示位置
  display.println("TKeyboard");

  display.setTextSize(2);//设置字体大小  
  display.setCursor(25, 40);//设置显示位置
  display.println("-ruxia-");
}
void loop() {
  currentStateCLK = digitalRead(CLK);

  if (currentStateCLK != lastStateCLK && currentStateCLK == 1) {
    if (digitalRead(DT) != currentStateCLK) {
      // 旋钮右旋
      if (IsModeVOL) {
        Consumer.write(MEDIA_VOL_UP);
      }
      else {
        Consumer.write(CONSUMER_BRIGHTNESS_UP);
      }
    } else {
      // 旋钮左旋
      if (IsModeVOL) {
        Consumer.write(MEDIA_VOL_DOWN);
      }
      else {
        Consumer.write(CONSUMER_BRIGHTNESS_DOWN);
      }
    }
  }

  lastStateCLK = currentStateCLK;

  // 旋钮按下
  int btnState = digitalRead(SW);
  
  if (btnState == LOW) {
    //if 50ms have passed since last LOW pulse, it means that the
    //button has been pressed, released and pressed again
    if (millis() - lastButtonPress > 50) {
      Serial.println("Button pressed!");
      Consumer.write(MEDIA_VOL_MUTE);
    }

    // Remember last button press event
    lastButtonPress = millis();
  }
  // 矩阵按键
  char key = keypad.getKey();
  if (key != NO_KEY) {
    Serial.println(key);
    switch (key) {
      Serial.println(key);
      case '1':
        System.write(SYSTEM_SLEEP);
        break;
      case '2':
        System.write(SYSTEM_WAKE_UP);
        break;
      case '3':
        Consumer.write(MEDIA_REWIND);
        break;
      case '4':
        if (IsModeVOL) {
          IsModeVOL = false;
          digitalWrite(ModeLED, LOW);
        }
        else {
          IsModeVOL = true;
          digitalWrite(ModeLED, HIGH);
        }
        break;
      case '5':        
        if (IsBtnMusic) {
          Consumer.write(MEDIA_PREV);
          
        }
        else {
          Consumer.write(CONSUMER_BROWSER_BACK);
        }
        break;
      case '6':
        if (IsBtnMusic) {
          Consumer.write(MEDIA_PLAY_PAUSE);
        }
        else {
          Consumer.write(CONSUMER_BROWSER_REFRESH);
        }
        break;
      case '7':
        if (IsBtnMusic) {
          Consumer.write(MEDIA_STOP);
        }
        else {
          Consumer.write(CONSUMER_BROWSER_HOME);
        }
        break;
      case '8':
        if (IsBtnMusic) {
          Consumer.write(MEDIA_NEXT);
        }
        else {
          Consumer.write(CONSUMER_BROWSER_FORWARD);
        }
        break;
      case '9':
        Consumer.write(CONSUMER_CALCULATOR);
        break;
      case 'a':
        Consumer.write(CONSUMER_EXPLORER);
        break;
      case 'b':
        Consumer.write(MEDIA_FAST_FORWARD);
        break;
      case 'c':
        if (IsBtnMusic) {
          IsBtnMusic = false;
          digitalWrite(BtnLED, LOW);
        }
        else {
          IsBtnMusic = true;
          digitalWrite(BtnLED, HIGH);
        }
        break;
    }
  }

  delay(1)
  ;
}
