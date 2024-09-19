#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>
#define CHECK_ZERO(a) (((a) == 0) ? 0 : 1)
#define LETTER_SHIFT(a) (1 << (a))
#define START_LETTER 'a'
/* a b c d e f g h i j k  l  m  n  o  p  q  r  s  t  u  v  w  x  y  z
   0 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20 21 22 23 24 25
*/
char keyboard[5][22] = {
{0  ,0  ,0  ,0  ,0  ,0  ,0  ,0  ,0  ,0  ,0  ,0  ,0  ,0  ,0  ,0  ,0  ,0  ,0  ,0  ,0  ,0 },
{0  ,'q','q','w','w','e','e','r','r','t','t','y','y','u','u','i','i','o','o','p','p',0 },
{0  ,0  ,'a','a','s','s','d','d','f','f','g','g','h','h','j','j','k','k','l','l',0  ,0 },
{0  ,0  ,0  ,'z','z','x','x','c','c','v','v','b','b','n','n','m','m',0  ,0  ,0  ,0  ,0 },
{0  ,0  ,0  ,0  ,0  ,0  ,0  ,0  ,0  ,0  ,0  ,0  ,0  ,0  ,0  ,0  ,0  ,0  ,0  ,0  ,0  ,0 }
};
int ls[26] = {0};
int map[26] = {0};
int m2[26] = {0};

int initialize_maps2(void) {
	//char value = 'a';
	for (int i = 0; i < 26; i++){
		for(int j = 23;j < 83 ; j++){
			int x = j/22;
			int y = j%22;
			if ((START_LETTER + i) == keyboard[x][y]){
				//printf("%d %d %d\n",i,x,y);
				/*x,y;x,y-1;x,y+2;x-1,y;x-1,y+1;x+1,y;x+1,y+1*/
				m2[i] = CHECK_ZERO(keyboard[x][y]) * LETTER_SHIFT(keyboard[x][y]-START_LETTER) +
					CHECK_ZERO(keyboard[x][y-1]) * LETTER_SHIFT(keyboard[x][y-1]-START_LETTER) +
					CHECK_ZERO(keyboard[x][y+2]) * LETTER_SHIFT(keyboard[x][y+2]-START_LETTER) +
					CHECK_ZERO(keyboard[x-1][y]) * LETTER_SHIFT(keyboard[x-1][y]-START_LETTER) +
					CHECK_ZERO(keyboard[x-1][y+1]) * LETTER_SHIFT(keyboard[x-1][y+1]-START_LETTER) +
					CHECK_ZERO(keyboard[x+1][y]) * LETTER_SHIFT(keyboard[x+1][y]-START_LETTER) +
					CHECK_ZERO(keyboard[x+1][y+1]) * LETTER_SHIFT(keyboard[x+1][y+1]-START_LETTER);
				break;
			}
		}
	}
	return 0;
}


int initialize_maps (void){

for (int i  = 0; i < 26 ; i++)
  ls[i] = LETTER_SHIFT(i);

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

return 0;

}
/*char tolower(char sym){
	char ans;
	if (sym >= 'A' && sym <= 'Z')
		ans = sym - 'A' + 'a';
	else if (sym>= 'a' && sym <= 'z')
		ans = sym;
	return ans;
}*/

int main(void)
{
    int cnt = 0;
    FILE * fp;
    char * line = NULL;
    size_t len = 0;
    ssize_t read;
	initialize_maps();
	initialize_maps2();
    fp = fopen("text.txt", "r");
    if (fp == NULL)
        exit(EXIT_FAILURE);

    while ((read = getline(&line, &len, fp)) != -1) {
    	int i = 0;
    	bool break_flag = true;
	//printf("0.line = %s, len = %ld\n",line, len);
	if (strlen(line) == 2) {
		printf("1.line = %s\n",line);
		cnt++;
		continue;
	}
	
	for (; i < (strlen(line) - 2) ; i++ ){
		char cur = (char) tolower((char)line[i]);
		char next = (char) tolower((char)line[i+1]);
			printf("cur = %c, next = %c, %d %d %d\n",cur,next,(int)cur - START_LETTER,m2[cur - START_LETTER],LETTER_SHIFT(next));
		if (cur == next) 
			continue;
		if ((m2[cur - START_LETTER] & LETTER_SHIFT(next - START_LETTER) ) == 0){
			break_flag = false;
			break;
		}
	}
	printf("2.break_flag %d, %s,i %d\n",break_flag, line,i);
	
	if( break_flag == true && i == (strlen(line) - 2)){
	printf("3.line = %s\n",line);
		cnt++;
		}
		else {
			printf("4.line = %s\n",line);
		}
	
    }

    fclose(fp);
    if (line)
        free(line);
        
     for (int i = 0;i < 26;i++){
     	printf("map[%d] = %d, m2[%d] = %d\n",i,map[i],i,m2[i]);
     }
     printf("cnt = %d\n",cnt);
     
    exit(EXIT_SUCCESS);
}
