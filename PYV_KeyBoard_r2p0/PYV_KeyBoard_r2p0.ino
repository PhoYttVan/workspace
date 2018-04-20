#include "Keyboard.h"
#include <avr/pgmspace.h>

#define CapsLock    Drive_595(0x20);
#define NumLock     Drive_595(0x40);
#define ScorllLock  Drive_595(0x80);

#define RCLK  11
#define SRCLK 12
#define SER   13
#define LCTRL   (0x80)//=0xE0-0x60  KEY_LEFT_CTRL
#define LSHIFT  (0x81)//=0xE1-0x60  KEY_LEFT_SHIFT
#define LALT    (0x82)//=0xE2-0x60  KEY_LEFT_ALT
#define LGUI    (0x83)//=0xE3-0x60  KEY_LEFT_GUI
#define RCTRL   (0x84)//=0xE4-0x60  KEY_RIGHT_CTRL
#define RSHIFT  (0x85)//=0xE5-0x60  KEY_RIGHT_SHIFT
#define RALT    (0x86)//=0xE6-0x60  KEY_RIGHT_ALT
#define RGUI    (0x87)//=0xE7-0x60  KEY_RIGHT_GUI

#define RETURN  (0x88)//=0x28+0x60  KEY_RETURN
#define ESC     (0x89)//=0x29+0x60  KEY_ESC
#define BK      (0x8A)//=0x2A+0x60  KEY_BACKSPACE
#define TAB     (0x8B)//=0x2B+0x60  KEY_TAB

#define NUM     (0x8F)//=0x53+0x3C  PAD_NUMLOCK
#define DIV     (0x90)//=0x54+0x3C  PAD_DIV
#define MUL     (0x91)//=0x55+0x3C  PAD_MUL
#define SUB     (0x92)//=0x56+0x3C  PAD_SUB
#define ADD     (0x93)//=0x57+0x3C  PAD_ADD
#define ENTER   (0x94)//=0x58+0x3C  PAD_ENTER
#define PAD_1   (0x95)//=0x59+0x3C  PAD_1
#define PAD_2   (0x96)//=0x5A+0x3C  PAD_2
#define PAD_3   (0x97)//=0x5B+0x3C  PAD_3
#define PAD_4   (0x98)//=0x5C+0x3C  PAD_4
#define PAD_5   (0x99)//=0x5D+0x3C  PAD_5
#define PAD_6   (0x9A)//=0x5E+0x3C  PAD_6
#define PAD_7   (0x9B)//=0x5F+0x3C  PAD_7
#define PAD_8   (0x9C)//=0x60+0x3C  PAD_8
#define PAD_9   (0x9D)//=0x61+0x3C  PAD_9
#define PAD_0   (0x9E)//=0x62+0x3C  PAD_0
#define PAD_D   (0x9F)//=0x63+0x3C  PAD_DOT

#define CAPS    (0x01)//=0x39-0x38  KEY_CAPS_LOCK
#define F1      (0x02)//=0x3A-0x38  KEY_F1
#define F2      (0x03)//=0x3B-0x38  KEY_F2
#define F3      (0x04)//=0x3C-0x38  KEY_F3
#define F4      (0x05)//=0x3D-0x38  KEY_F4
#define F5      (0x06)//=0x3E-0x38  KEY_F5
#define F6      (0x07)//=0x3F-0x38  KEY_F6
#define F7      (0x08)//=0x40-0x38  KEY_F7
#define F8      (0x09)//=0x41-0x38  KEY_F8
#define F9      (0x0A)//=0x42-0x38  KEY_F9
#define F10     (0x0B)//=0x43-0x38  KEY_F10
#define F11     (0x0C)//=0x44-0x38  KEY_F11
#define F12     (0x0D)//=0x45-0x38  KEY_F12
#define PS      (0x0E)//=0x46-0x38  KEY_PrintScreen
#define SCROLL  (0x0F)//=0x47-0x38  KEY_ScrollLock
#define PAUSE   (0x00)//=0x48-0x38  KEY_Pause
#define INSERT  (0x11)//=0x49-0x38  KEY_INSER
#define HOME    (0x12)//=0x4A-0x38  KEY_HOME
#define PGUP    (0x13)//=0x4B-0x38  KEY_PAGE_UP
#define DELETE  (0x14)//=0x4C-0x38  KEY_DELETE
#define END     (0x15)//=0x4D-0x38  KEY_END
#define PGDN    (0x16)//=0x4E-0x38  KEY_PAGE_DOWN
#define RIGHT   (0x17)//=0x4F-0x38  KEY_RIGHT_ARROW
#define LEFT    (0x18)//=0x50-0x38  KEY_LEFT_ARROW
#define DOWN    (0x19)//=0x51-0x38  KEY_DOWN_ARROW
#define UP      (0x1A)//=0x52-0x38  KEY_UP_ARROW

#define ______  (0xFF)
#define LFN     (0xF1)
#define LSPACE  (0xF0)
#define RFN     (0xF0)
#define RSPACE  (0xF0)

#define ROW0 A5
#define ROW1 A4
#define ROW2 A3
#define ROW3 A2
#define ROW4 A1
#define ROW5 A0

#define COL3  0xFF0F // ColList[0]
#define COL4  0xFF17 // ColList[1]
#define COL5  0xFF1B // ColList[2]
#define COL6  0xFF1D // ColList[3]
//#define COL7  0xFF1E
#define COL8  0x7F1F // ColList[4]
#define COL9  0xBF1F // ColList[5]
#define COL10 0xDF1F // ColList[6]
#define COL11 0xEF1F // ColList[7]
#define COL12 0xF71F // ColList[8]
#define COL13 0xFB1F // ColList[9]
#define COL14 0xFD1F // ColList[10]
//#define COL15 0xFE1F

#define MaxRow    6
#define MaxCol    11
#define MaxLayer  2

//#define COMB2_01  

const PROGMEM char Comb2[][2]   = {
  {LCTRL,'c'},
  {LCTRL,'v'},
};

const PROGMEM char Comb3[][3]   = {
  {LCTRL,LSHIFT,'c'},
  {LCTRL,LSHIFT,'v'},
  {LCTRL,'w','r'},
};

const PROGMEM char Comb4[][4]   = {
  {LCTRL,LSHIFT,LALT,'c'},
  {LCTRL,LSHIFT,LALT,'v'},
  {LCTRL,'w'   ,LCTRL,'r'},
};

const PROGMEM char Comb5[][5]   = {
  {LCTRL,LSHIFT,LALT,LGUI,'c'},
  {LCTRL,LSHIFT,LALT,LGUI,'v'},
};
// const PROGMEM char Comb2[2][4] = {"LCTRL+c", "LCTRL+v"};
//const PROGMEM char Comb3[2][7] = {"LCTRL+LSHIFT+v", "LCTRL+LALT+v"};
//unsigned char CombList[2][] = {Copy, PasteI};

const PROGMEM unsigned int ColList[MaxCol] = {COL3, COL4, COL5, COL6, COL8, COL9, COL10, COL11, COL12, COL13, COL14};
const PROGMEM unsigned int RowList[MaxRow] = {ROW0, ROW1, ROW2, ROW3, ROW4, ROW5}; // int -> char
//unsigned int RowList[MaxRow] = {A5,A4,A3,A2,A1,A0}; // int -> char

unsigned char Layer = 1;

struct {
  unsigned char PrevState :1;
}KeyboardInfo[MaxRow][MaxCol];

#define IS_CMD 0x8000
#define IS_STR 0x4000
#define COMB2  0x8200
#define COMB3  0x8300
#define COMB4  0x8400
#define COMB5  0x8500
#define LAYER0 0x0000
#define LAYER1 0x0100
#define LAYER2 0x0200

#define CMDR1C0 "TEST"

unsigned int KeyboardTable[MaxLayer][MaxRow][MaxCol] = {
  {
    ______, ______, ______, ______, ESC   , ______, F1    , F2    , F3    , F4    , F5    ,
    NUM   , DIV   , MUL   , SUB   , '~'   , '1'   , '2'   , '3'   , '4'   , '5'   , '6'   ,
    PAD_1 , PAD_2 , PAD_3 , ______, TAB   , 'q'   , 'w'   , 'e'   , 'r'   , 't'   , ______,
    PAD_4 , PAD_5 , PAD_6 , ADD   , CAPS  , 'a'   , 's'   , 'd'   , 'f'   , 'g'   , ______,
    PAD_7 , PAD_8 , PAD_9 , ______, LSHIFT, 'z'   , 'x'   , 'c'   , 'v'   , 'b'   , ______,
    PAD_0 , ______, PAD_D , ENTER , LCTRL , LGUI  , LALT  , LFN   , LSPACE, ______, ______,
  },{
    ______, ______, ______, ______, ESC   , ______, F1    , F2    , F3    , F4    , F5    ,
    IS_CMD&LAYER1&NUM   , DIV   , MUL   , SUB   , '~'   , '1'   , '2'   , '3'   , '4'   , '5'   , '6'   ,
    LAYER1+NUM , PAD_2 , PAD_3 , ______, TAB   , 'q'   , 'w'   , 'e'   , 'r'   , 't'   , ______,
    NUM, PAD_5 , PAD_6 , ADD   , CAPS  , 'a'   , 's'   , 'd'   , 'f'   , 'g'   , ______,
    PAD_7 , PAD_8 , PAD_9 , ______, LSHIFT, 'z'   , 'x'   , 'c'   , 'v'   , 'b'   , ______,
    PAD_0 , ______, PAD_D , ENTER , LCTRL , LGUI  , LALT  , LFN   , LSPACE, ______, ______,
  }
};

void setup () {
  Serial.begin(9600);
  pinMode(RCLK,OUTPUT);
  pinMode(SRCLK,OUTPUT);
  pinMode(SER,OUTPUT); 
  for (unsigned char i = 0; i < MaxRow; i++) {
    for (unsigned char j = 0; j < MaxCol; j++) {
      KeyboardInfo[i][j].PrevState = 0;
//      KeyboardInfo[i][j].Layer     = LayerTable[i][j];
    }
  }
  // int *array;
  // array = (int*)malloc(10*sizeof(int));
  // for (unsigned int i=0; i<10; i++){
      // *array++ = i+1;
       // Serial.print(*array,DEC);
  // }
  // free(array);
  Serial.print(Comb2[1]);
  // Serial.print(ddd[1]);
}

void loop() {
    for (unsigned char i = 0; i < MaxCol; i++) {
      ScanCol(i);
    }
}

void ScanCol(unsigned char Col) {
    Drive_595(ColList[Col]);
    for (unsigned char i = 0; i < MaxRow; i++) {
        ScanRow(i,Col);
    }
}

void ScanRow(unsigned char Row,unsigned char Col) {
    char key       = KeyboardTable[Layer][Row][Col];
    bool PrevBottonState = KeyboardInfo[Row][Col].PrevState;
    bool CurrBottonState = (analogRead(RowList[Row]) < 512) ? 1 : 0;
    if ((CurrBottonState != PrevBottonState ) && CurrBottonState == 1) {
        Serial.print(" Row=");
        Serial.print(Row,DEC);
        Serial.print(" Col=");
        Serial.print(Col,DEC);
        KeyPress(Row,Col);
    } else if ((CurrBottonState != PrevBottonState ) && CurrBottonState == 0) {
        Serial.print(" Row=");
        Serial.print(Row,DEC);
        Serial.print(" Col=");
        Serial.print(Col,DEC);
        KeyRelease(Row,Col);
    }
    KeyboardInfo[Row][Col].PrevState = CurrBottonState;
    Keyboard.releaseAll();
}

void Drive_595(int data) {
  union var{ 
    int i;
    char c[2];
  }ColDriver;

  ColDriver.i = data;

  digitalWrite(RCLK,LOW); //将ST_CP口上面加低电平让芯片准备好接收数据
  shiftOut(SER,SRCLK,MSBFIRST,ColDriver.c[1]);
  shiftOut(SER,SRCLK,MSBFIRST,ColDriver.c[0]);
  digitalWrite(RCLK,HIGH); //将ST_CP这个针脚恢复到高电平
}

void KeyPress (unsigned char Row, unsigned char Col){
  int key       = KeyboardTable[Layer][Row][Col];
  if (key == LFN) {
    Layer =  1 - Layer; // temp
  }
  Serial.print(" Layer =");
  Serial.print(Layer,HEX);
  Serial.print(" KeyValue =");
  Serial.print(key,HEX);
  Serial.print(" Pressed\n");
  Keyboard.press(key);
}

void KeyRelease (unsigned char Row,unsigned char Col){
  char key       = KeyboardTable[Layer][Row][Col];
  Serial.print(" KeyValue =");
  Serial.print(key,HEX);
  Serial.print(" Released\n");
  Keyboard.release(key);
}
