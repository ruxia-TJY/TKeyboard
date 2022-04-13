/*
 * 按键/旋钮操作
 * 当按下按键,程序从EEPROM中读取相应操作描述字符串，执行
 */
#ifndef KEY_H
#define KEY_H

// 按键得到的值如下：
// 0  6   12  18  24
// 1  7   13  19  25
// 2  8   14  20  26
// 3  9   15  21  27
// 4  10  16  22  28
// 加上两个EC11的左旋/右旋/点击，映射为29,30,31;32,33,34
// 中间的空如5,设置为255,事实上,在整个程序中不会用到
unsigned int KeyValueMap[] = {0,16,32,48,64,255,80,96,112,128,144,255,160,176,192,208,224,255,240,0,16,32,48,255,64,80,96,112,128,144,160,176,192,208,224};

// 当前的KEY,每按下按键/旋转旋钮,从EEPROM读取赋值到此。
String KEY_SEND;

// 从EEPROM中读取KEY，赋值给KEY_SEND，以便发送
void readKEYFromEEPROM(int place, bool addr);

// 根据描述字符串SEND_KEY执行命令
void showKEY();

// 读取并发送KEY
void sendKEY(int valueOfKeyboard);
#endif
