#include <stdio.h>
#include <ctype.h>
#include <errno.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include "log.h"
#include "adjacent.h"


struct cords
{
  int x;
  int y;
};

static const char qwerty_table[QWERTY_ROWS][QWERTY_COLS] = {
  { 'q', 'w', 'e', 'r', 't', 'y', 'u', 'i', 'o', 'p' },
  { 'a', 's', 'd', 'f', 'g', 'h', 'j', 'k', 'l', ' ' },
  { 'z', 'x', 'c', 'v', 'b', 'n', 'm', ' ', ' ', ' ' }
};

char keyboard[QWERTY_ROWS][QWERTY_COLS] = {
{0  ,0  ,0  ,0  ,0  ,0  ,0  ,0  ,0  ,0  ,0  ,0  ,0  ,0  ,0  ,0  ,0  ,0  ,0  ,0  ,0  ,0 },
{0  ,'q','q','w','w','e','e','r','r','t','t','y','y','u','u','i','i','o','o','p','p',0 },
{0  ,0  ,'a','a','s','s','d','d','f','f','g','g','h','h','j','j','k','k','l','l',0  ,0 },
{0  ,0  ,0  ,'z','z','x','x','c','c','v','v','b','b','n','n','m','m',0  ,0  ,0  ,0  ,0 },
{0  ,0  ,0  ,0  ,0  ,0  ,0  ,0  ,0  ,0  ,0  ,0  ,0  ,0  ,0  ,0  ,0  ,0  ,0  ,0  ,0  ,0 }
};

int map[NUMBER_LETTERS] = {0};

static bool is_latin_letter(const char ch)
{
  return (ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z');
}

static int get_kb_cords(const char ch, struct cords *kb_cords)
{
  int i;
  int j;
  char lower_ch;

  if (!is_latin_letter(ch)) {
    return EINVAL;
  }

  lower_ch = tolower(ch);

  for (i = 0; i < QWERTY_ROWS; i++) {
    for (j = 0; j < QWERTY_COLS; j++) {
      if (qwerty_table[i][j] == lower_ch) {
        kb_cords->x = j;
        kb_cords->y = i;
        return 0;
      }
    }
  }

  return ERANGE;
}

static unsigned char is_adjacent_qwerty_buttons(struct cords kb1, struct cords kb2)
{
  if (abs(kb1.y - kb2.y) > 1) {
    return 0;
  }

  if (kb1.y == kb2.y) {
    return abs(kb1.x - kb2.x) == 1;
  }

  if (abs(kb1.x - kb2.x) < 2) {
    return (kb1.x == kb2.x) || 
           (kb1.x > kb2.x && kb1.y < kb2.y) ||
           (kb1.x < kb2.x && kb1.y > kb2.y);
  }

  return 0;
}

unsigned char is_adjacent_chars(const char ch1, const char ch2)
{
  struct cords kb1_cords;
  struct cords kb2_cords;
  int result;

  result = get_kb_cords(ch1, &kb1_cords);
  if (result != 0) {
    print_err("illegal char: %c (%s)", ch1, strerror(result));
    return 0;
  }

  result = get_kb_cords(ch2, &kb2_cords);
  if (result != 0) {
    print_err("illegal char: %c (%s)", ch2, strerror(result));
    return 0;
  }

  return is_adjacent_qwerty_buttons(kb1_cords, kb2_cords);
}

unsigned char is_word_correct(const char *word)
{
  const char *p;

  
  if (word[1] == '\000') {
    return 1;
  }

  for (p = word; *(p + 1) != '\000'; p++) {
    if (*p == *(p + 1)) {
      continue;
    }

    if (!is_adjacent_chars(*p, *(p + 1))) {
      return 0;
    }
  }

  return 1;
}

int initialize_maps(void) {

  for (int i = 0; i < NUMBER_LETTERS; i++){ //cycle at every english letter
    for(int j = 0;j < QWERTY_ROWS*QWERTY_COLS - 1 ; j++){ // cycle at
      int x = j/QWERTY_COLS;
      int y = j%QWERTY_COLS;
      if ((LETTER1 + i) == keyboard[x][y]){

        /*x,y;x,y-1;x,y+2;x-1,y;x-1,y+1;x+1,y;x+1,y+1 exact button + adjacent buttons*/
        map[i] = CHECK_ZERO(keyboard[x][y]) * LETTER_SHIFT(keyboard[x][y]-LETTER1) +
        CHECK_ZERO(keyboard[x][y-1]) * LETTER_SHIFT(keyboard[x][y-1]-LETTER1) +
        CHECK_ZERO(keyboard[x][y+2]) * LETTER_SHIFT(keyboard[x][y+2]-LETTER1) +
        CHECK_ZERO(keyboard[x-1][y]) * LETTER_SHIFT(keyboard[x-1][y]-LETTER1) +
        CHECK_ZERO(keyboard[x-1][y+1]) * LETTER_SHIFT(keyboard[x-1][y+1]-LETTER1) +
        CHECK_ZERO(keyboard[x+1][y]) * LETTER_SHIFT(keyboard[x+1][y]-LETTER1) +
        CHECK_ZERO(keyboard[x+1][y+1]) * LETTER_SHIFT(keyboard[x+1][y+1]-LETTER1);
        break;
      }
    }
  }
  return 0;
}
/* 
map[0] = ls[0]   | ls[16] | ls[18] | ls[22] | ls[25]; //Aqswz
map[1] = ls[1]   | ls[6]  | ls[7]  | ls[13] | ls[21]; //Bghnv
map[2] = ls[2]   | ls[3]  | ls[5]  | ls[21] | ls[23]; //Cdfvx
map[3] = ls[2]   | ls[3]  | ls[4]  | ls[5]  | ls[17] | ls[18]  | ls[23]; //cDefrsx
map[4] = ls[3]   | ls[4]  | ls[17] | ls[18] | ls[22]; //dErsw
map[5] = ls[2]   | ls[3]  | ls[5]  | ls[6]  | ls[17] | ls[19]  | ls[21]; //cdFgrtv
map[6] = ls[1]   | ls[5]  | ls[6]  | ls[7]  | ls[19] | ls[21]  | ls[24]; //bfGhtvy
map[7] = ls[1]   | ls[6]  | ls[7]  | ls[9]  | ls[13] | ls[20]  | ls[24]; //bgHjnuy
map[8] = ls[8]   | ls[9]  | ls[10] | ls[14] | ls[20]; //Ijkou
map[9] = ls[7]   | ls[8]  | ls[9]  | ls[10] | ls[12] | ls[13]  | ls[20]; //hiJkmnu
map[10] = ls[8]  | ls[9]  | ls[10] | ls[11] | ls[12] | ls[14]; //ijKlmo
map[11] = ls[10] | ls[11] | ls[14] | ls[15]; //kLop
map[12] = ls[9]  | ls[10] | ls[12] | ls[13]; //jkMn
map[13] = ls[1]  | ls[7]  | ls[9]  | ls[12] | ls[13]; //bhjmN
map[14] = ls[8]  | ls[10] | ls[11] | ls[14] | ls[15]; //iklOp
map[15] = ls[11] | ls[14] | ls[15]; //loP
map[16] = ls[0]  | ls[16] | ls[22]; //aQw
map[17] = ls[3]  | ls[4]  | ls[5]  | ls[17] | ls[19]; //defRt
map[18] = ls[0]  | ls[3]  | ls[4]  | ls[18] | ls[22] | ls[18] | ls[22]; //adeSwxz
map[19] = ls[5]  | ls[16] | ls[18] | ls[22] | ls[25]; //fgrTy
map[20] = ls[7]  | ls[8]  | ls[9]  | ls[20] | ls[24]; //hijUy
map[21] = ls[1]  | ls[2]  | ls[5]  | ls[6]  | ls[21]; //bcfgV
map[22] = ls[0]  | ls[4]  | ls[16] | ls[18] | ls[22]; //aeqSW
map[23] = ls[2]  | ls[3]  | ls[18] | ls[23] | ls[25]; //cdsXz
map[24] = ls[6]  | ls[7]  | ls[19] | ls[20] | ls[24]; //ghtuY
map[25] = ls[0]  | ls[18] | ls[23] | ls[25]; //asxZ
*/

