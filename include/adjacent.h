#define QWERTY_ROWS 5
#define QWERTY_COLS 22

#define NUMBER_LETTERS 26
#define CHECK_ZERO(D) (((D) == 0) ? 0 : 1)
#define LETTER_SHIFT(D) (1 << (D))
#define LETTER1 'a'
/* a b c d e f g h i j k  l  m  n  o  p  q  r  s  t  u  v  w  x  y  z
   0 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20 21 22 23 24 25
*/

int initialize_maps(void);
unsigned char is_word_correct(const char *word);
