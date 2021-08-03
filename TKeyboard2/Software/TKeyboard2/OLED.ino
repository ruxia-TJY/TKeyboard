/*
   OLED
*/

// 绘制音量动画，isup:是否为增加
void drawVOL(bool isup)
{
//  display.clearDisplay();
//  if (isup)
//    display.drawBitmap(0, 0, VOL_0, 128, 64, 1);
//  else
//    display.drawBitmap(0, 0, VOL_2, 128, 64, 1);
//  display.display();
//  delay(100);
//  display.clearDisplay();
//  display.drawBitmap(0, 0, VOL_1, 128, 64, 1);
//  display.display();
//  delay(50);
  display.clearDisplay();
  if (isup)
    display.drawBitmap(0, 0, VOL_2, 128, 64, 1);
  else
    display.drawBitmap(0, 0, VOL_0, 128, 64, 1);
  display.display();
//  delay(100);
}

void drawBrightness(bool isup)
{
 display.clearDisplay();
  if (isup)
    display.drawBitmap(0, 0, BRIGHTNESS_0, 128, 64, 1);
  else
    display.drawBitmap(0, 0, BRIGHTNESS_1, 128, 64, 1);
  display.display();
  delay(100);
  
  display.clearDisplay();
  if (isup)
    display.drawBitmap(0, 0, BRIGHTNESS_1, 128, 64, 1);
  else
    display.drawBitmap(0, 0, BRIGHTNESS_0, 128, 64, 1);
  display.display();
  delay(100);
}
