#include <stdio.h>
#include <string.h>
//#include " ~/work/c/MeasureMemory/define.h"
#include "./define.h"

#define IS_COMB (0x80)
#define IS_STR (0x40)
//#define COMB2  (0x82)
//#define COMB3  (0x83)
//#define COMB4  (0x84)
//#define COMB5  (0x85)
//#define LAYER0 (0x00)
//#define LAYER1 (0x01)
//#define LAYER2 (0x02)

#define MASK_LCTRL   (0x80)
#define MASK_LSHIFT  (0x40)
#define MASK_LALT    (0x20)
#define MASK_LGUI    (0x10)
#define MASK_RCTRL   (0x08)
#define MASK_RSHIFT  (0x04)
#define MASK_RALT    (0x02)
#define MASK_RGUI    (0x01)
#define MASK_NONE    (0x00)

#define COMB001 (0x81)
#define COMB002 (0x82)
#define COMB003 (0x83)
#define COMB004 (0x84)
#define COMB005 (0x85)

//#define MODIFY_MASK  (0x)
#define COMB_MASK (0x7F)

const char Comb[][2] = {
    {MASK_LCTRL,                                'c'},
    {MASK_NONE,                                 'c'},
    {MASK_LCTRL,                                'v'},
    {MASK_LCTRL+MASK_LSHIFT,                    'c'},
    {MASK_LCTRL+MASK_LSHIFT,                    'v'},
    {MASK_LCTRL+MASK_LSHIFT+MASK_LALT,          'c'},
    {MASK_LCTRL+MASK_LSHIFT+MASK_LALT,          'v'},
    {MASK_LCTRL+MASK_LSHIFT+MASK_LALT+MASK_LGUI,'c'},
    {MASK_LCTRL+MASK_LSHIFT+MASK_LALT+MASK_LGUI,'v'},
};

unsigned char KeyboardTable[MaxLayer][MaxRow][MaxCol] = {
  {
    ______, ______, ______, ______, ESC   , ______, F1    , F2    , F3    , F4    , F5    ,
    NUM   , DIV   , MUL   , SUB   , '~'   , '1'   , '2'   , '3'   , '4'   , '5'   , '6'   ,
    PAD_1 , PAD_2 , PAD_3 , ______, TAB   , 'q'   , 'w'   , 'e'   , 'r'   , 't'   , ______,
    PAD_4 , PAD_5 , PAD_6 , ADD   , CAPS  , 'a'   , 's'   , 'd'   , 'f'   , 'g'   , ______,
    PAD_7 , PAD_8 , PAD_9 , ______, LSHIFT, 'z'   , 'x'   , 'c'   , 'v'   , 'b'   , ______,
    PAD_0 , ______, PAD_D , ENTER , LCTRL , LGUI  , LALT  , LFN   , LSPACE, ______, ______,
  },{
    ______, ______, ______, ______, ESC   , ______, F1    , F2    , F3    , F4    , F5    ,
    COMB001 , DIV   , MUL   , SUB   , '~'   , '1'   , '2'   , '3'   , '4'   , '5'   , '6'   ,
    COMB002 , PAD_2 , PAD_3 , ______, TAB   , 'q'   , 'w'   , 'e'   , 'r'   , 't'   , ______,
    COMB003, PAD_5 , PAD_6 , ADD   , CAPS  , 'a'   , 's'   , 'd'   , 'f'   , 'g'   , ______,
    COMB004, PAD_8 , PAD_9 , ______, LSHIFT, 'z'   , 'x'   , 'c'   , 'v'   , 'b'   , ______,
    COMB005, ______, PAD_D , ENTER , LCTRL , LGUI  , LALT  , LFN   , LSPACE, ______, ______,
  }
};

const char mask_list[8] = { MASK_LCTRL ,MASK_LSHIFT ,MASK_LALT ,MASK_LGUI ,MASK_RCTRL ,MASK_RSHIFT ,MASK_RALT ,MASK_RGUI};
const char* str_list[8] = { "LCTRL" ,"LSHIFT" ,"LALT" ,"LGUI" ,"RCTRL" ,"RSHIFT" ,"RALT" ,"RGUI"};

void get_modify_key ( char modify_key ) {
    char* s;//待返回的字符串，需要申请动态内存空间
    printf("press ");
    for (int i = 0; i < 8 ; i++ ) {
        if (modify_key & mask_list[i])
        {
            printf( "%s + ", str_list[i]);
        }
    }
}

void main () {
    int row, col,layer;
    layer = 0;
    row = 4;
    col = 5;
//    printf("please input row < %d\t:", MaxRow);
//    scanf("%d",&row);
//    printf("please input col < %d\t:", MaxCol);
//    scanf("%d",&col);
    printf("row = %d, col = %d\n", row, col);
    int KeyValue = KeyboardTable[layer][row][col];
    printf("KeyValue = %x \n",KeyValue);
    if (layer != 0 ) {
        if (KeyValue & IS_COMB) {
            char comb_index = (KeyValue & COMB_MASK);
            printf("comb_index = %x \n",comb_index );
            char modify_key = Comb[comb_index][0];
            char print__key = Comb[comb_index][1];
            printf("comb = %x %x\n",modify_key, print__key);
            get_modify_key(modify_key);
            printf("%c \n" ,print__key );
        }
    } else {
        printf("%c \n" ,KeyValue);
    }
}
