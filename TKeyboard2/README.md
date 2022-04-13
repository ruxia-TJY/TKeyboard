# TKeyboard2（开发中）

## 描述

按下按键，从EEPROM相应地址读取操作字符串。对于媒体音量增加等使用转义字符串。例如提升音量存储为\m。

对于具体转义字符串请查看表。

原本制作了OLED动画，但是会导致旋转旋钮出现问题，所以注释掉。

8个LED显示灯通过74LS595控制，其中三个LED用于系统CAPS，NUMS，ScrollLock.剩余5个灯暂时未想好功能。

### 修改键值

目前写死在程序里面，可以通过程序里面的setKeyForEEPROM()函数修改每个键值的功能，并调用一次该函数即可写入EEPROM。后续写一个软件，用以修改。

## 教程

### 预览图

![](./Preview/TKeyboard2.jpg)
### 组装

元件焊接位置见bom文件夹下文件



外壳有两种方案，一是像TKeyboard版本一样，由两块PCB板4枚M3螺丝组装。

二是3D打印（设计中），本人设计很烂，建议可以自行设计



## 元件

|   元件   |  封装    | 数量 |
| :----: | :----: | :----: |
| Leonardo Pro Micro | Mini接口 | 1 |
| 旋转编码器EC11 |  | 2 |
| 0.96寸OLED |  | 1 |
| 按键 |  | 25 |
| BC6301 | SOP-14 | 1 |
| AT24C04 | SOP-8 | 1 |
| 74LS595 | SOP-16 | 1 |
| LED | 0805 | 8 |
| 排母 | 1x12 | 2 |
| 排母 | 1x4 | 1 |
| 1N4148WS | SOD-323 | 25 |





## 开源协议

```
BSD 3-Clause License

Copyright (c) 2021, ruxia-TJY
All rights reserved.

Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions are met:

* Redistributions of source code must retain the above copyright notice, this
  list of conditions and the following disclaimer.

* Redistributions in binary form must reproduce the above copyright notice,
  this list of conditions and the following disclaimer in the documentation
  and/or other materials provided with the distribution.

* Neither the name of the copyright holder nor the names of its
  contributors may be used to endorse or promote products derived from
  this software without specific prior written permission.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
```
