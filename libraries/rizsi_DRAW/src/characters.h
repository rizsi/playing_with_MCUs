#define N_CHARS 95
#define CHAR_WIDTH 8
#define CHAR_HEIGHT 12
#define CHAR_MIN_Y 1
#define CHAR_MAX_Y 13
const PROGMEM uint8_t char_lengths [95]=
{
1,
1,
1,
1,
1,
1,
1,
1,
1,
1,
1,
1,
1,
1,
1,
1,
1,
1,
1,
1,
1,
1,
1,
1,
1,
1,
1,
1,
1,
1,
1,
1,
1,
1,
1,
1,
1,
1,
1,
1,
1,
1,
1,
1,
1,
1,
1,
1,
1,
1,
1,
1,
1,
1,
1,
1,
1,
1,
1,
1,
1,
1,
1,
1,
1,
1,
1,
1,
1,
1,
1,
1,
1,
1,
1,
2,
2,
2,
2,
2,
2,
2,
2,
2,
2,
2,
2,
2,
2,
2,
2,
2,
2,
2,
2,
};
#define CHAR_LENGTH 2
const PROGMEM uint8_t values [190]=
{
/*   0 */ 0B00100000,0B00000000,/* \x20\x00*/
/* ! 1 */ 0B00100001,0B00000000,/* \x21\x00*/
/* % 2 */ 0B00100101,0B00000000,/* \x25\x00*/
/* ( 3 */ 0B00101000,0B00000000,/* \x28\x00*/
/* ) 4 */ 0B00101001,0B00000000,/* \x29\x00*/
/* * 5 */ 0B00101010,0B00000000,/* \x2a\x00*/
/* + 6 */ 0B00101011,0B00000000,/* \x2b\x00*/
/* , 7 */ 0B00101100,0B00000000,/* \x2c\x00*/
/* - 8 */ 0B00101101,0B00000000,/* \x2d\x00*/
/* . 9 */ 0B00101110,0B00000000,/* \x2e\x00*/
/* / 10 */ 0B00101111,0B00000000,/* \x2f\x00*/
/* 0 11 */ 0B00110000,0B00000000,/* \x30\x00*/
/* 1 12 */ 0B00110001,0B00000000,/* \x31\x00*/
/* 2 13 */ 0B00110010,0B00000000,/* \x32\x00*/
/* 3 14 */ 0B00110011,0B00000000,/* \x33\x00*/
/* 4 15 */ 0B00110100,0B00000000,/* \x34\x00*/
/* 5 16 */ 0B00110101,0B00000000,/* \x35\x00*/
/* 6 17 */ 0B00110110,0B00000000,/* \x36\x00*/
/* 7 18 */ 0B00110111,0B00000000,/* \x37\x00*/
/* 8 19 */ 0B00111000,0B00000000,/* \x38\x00*/
/* 9 20 */ 0B00111001,0B00000000,/* \x39\x00*/
/* : 21 */ 0B00111010,0B00000000,/* \x3a\x00*/
/* = 22 */ 0B00111101,0B00000000,/* \x3d\x00*/
/* A 23 */ 0B01000001,0B00000000,/* \x41\x00*/
/* B 24 */ 0B01000010,0B00000000,/* \x42\x00*/
/* C 25 */ 0B01000011,0B00000000,/* \x43\x00*/
/* D 26 */ 0B01000100,0B00000000,/* \x44\x00*/
/* E 27 */ 0B01000101,0B00000000,/* \x45\x00*/
/* F 28 */ 0B01000110,0B00000000,/* \x46\x00*/
/* G 29 */ 0B01000111,0B00000000,/* \x47\x00*/
/* H 30 */ 0B01001000,0B00000000,/* \x48\x00*/
/* I 31 */ 0B01001001,0B00000000,/* \x49\x00*/
/* J 32 */ 0B01001010,0B00000000,/* \x4a\x00*/
/* K 33 */ 0B01001011,0B00000000,/* \x4b\x00*/
/* L 34 */ 0B01001100,0B00000000,/* \x4c\x00*/
/* M 35 */ 0B01001101,0B00000000,/* \x4d\x00*/
/* N 36 */ 0B01001110,0B00000000,/* \x4e\x00*/
/* O 37 */ 0B01001111,0B00000000,/* \x4f\x00*/
/* P 38 */ 0B01010000,0B00000000,/* \x50\x00*/
/* Q 39 */ 0B01010001,0B00000000,/* \x51\x00*/
/* R 40 */ 0B01010010,0B00000000,/* \x52\x00*/
/* S 41 */ 0B01010011,0B00000000,/* \x53\x00*/
/* T 42 */ 0B01010100,0B00000000,/* \x54\x00*/
/* U 43 */ 0B01010101,0B00000000,/* \x55\x00*/
/* V 44 */ 0B01010110,0B00000000,/* \x56\x00*/
/* W 45 */ 0B01010111,0B00000000,/* \x57\x00*/
/* X 46 */ 0B01011000,0B00000000,/* \x58\x00*/
/* Y 47 */ 0B01011001,0B00000000,/* \x59\x00*/
/* Z 48 */ 0B01011010,0B00000000,/* \x5a\x00*/
/* a 49 */ 0B01100001,0B00000000,/* \x61\x00*/
/* b 50 */ 0B01100010,0B00000000,/* \x62\x00*/
/* c 51 */ 0B01100011,0B00000000,/* \x63\x00*/
/* d 52 */ 0B01100100,0B00000000,/* \x64\x00*/
/* e 53 */ 0B01100101,0B00000000,/* \x65\x00*/
/* f 54 */ 0B01100110,0B00000000,/* \x66\x00*/
/* g 55 */ 0B01100111,0B00000000,/* \x67\x00*/
/* h 56 */ 0B01101000,0B00000000,/* \x68\x00*/
/* i 57 */ 0B01101001,0B00000000,/* \x69\x00*/
/* j 58 */ 0B01101010,0B00000000,/* \x6a\x00*/
/* k 59 */ 0B01101011,0B00000000,/* \x6b\x00*/
/* l 60 */ 0B01101100,0B00000000,/* \x6c\x00*/
/* m 61 */ 0B01101101,0B00000000,/* \x6d\x00*/
/* n 62 */ 0B01101110,0B00000000,/* \x6e\x00*/
/* o 63 */ 0B01101111,0B00000000,/* \x6f\x00*/
/* p 64 */ 0B01110000,0B00000000,/* \x70\x00*/
/* q 65 */ 0B01110001,0B00000000,/* \x71\x00*/
/* r 66 */ 0B01110010,0B00000000,/* \x72\x00*/
/* s 67 */ 0B01110011,0B00000000,/* \x73\x00*/
/* t 68 */ 0B01110100,0B00000000,/* \x74\x00*/
/* u 69 */ 0B01110101,0B00000000,/* \x75\x00*/
/* v 70 */ 0B01110110,0B00000000,/* \x76\x00*/
/* w 71 */ 0B01110111,0B00000000,/* \x77\x00*/
/* x 72 */ 0B01111000,0B00000000,/* \x78\x00*/
/* y 73 */ 0B01111001,0B00000000,/* \x79\x00*/
/* z 74 */ 0B01111010,0B00000000,/* \x7a\x00*/
/* § 75 */ 0B11000010,0B10100111,/* \xc2\xa7*/
/* ° 76 */ 0B11000010,0B10110000,/* \xc2\xb0*/
/* Á 77 */ 0B11000011,0B10000001,/* \xc3\x81*/
/* É 78 */ 0B11000011,0B10001001,/* \xc3\x89*/
/* Í 79 */ 0B11000011,0B10001101,/* \xc3\x8d*/
/* Ó 80 */ 0B11000011,0B10010011,/* \xc3\x93*/
/* Ö 81 */ 0B11000011,0B10010110,/* \xc3\x96*/
/* Ú 82 */ 0B11000011,0B10011010,/* \xc3\x9a*/
/* Ü 83 */ 0B11000011,0B10011100,/* \xc3\x9c*/
/* á 84 */ 0B11000011,0B10100001,/* \xc3\xa1*/
/* é 85 */ 0B11000011,0B10101001,/* \xc3\xa9*/
/* í 86 */ 0B11000011,0B10101101,/* \xc3\xad*/
/* ó 87 */ 0B11000011,0B10110011,/* \xc3\xb3*/
/* ö 88 */ 0B11000011,0B10110110,/* \xc3\xb6*/
/* ú 89 */ 0B11000011,0B10111010,/* \xc3\xba*/
/* ü 90 */ 0B11000011,0B10111100,/* \xc3\xbc*/
/* Ő 91 */ 0B11000101,0B10010000,/* \xc5\x90*/
/* ő 92 */ 0B11000101,0B10010001,/* \xc5\x91*/
/* Ű 93 */ 0B11000101,0B10110000,/* \xc5\xb0*/
/* ű 94 */ 0B11000101,0B10110001,/* \xc5\xb1*/
};
const PROGMEM uint8_t pixels [1520]=
{
/*   */ /*col0*/ 0B00000000, 0B00000000, /*col1*/ 0B00000000, 0B00000000, /*col2*/ 0B00000000, 0B00000000, /*col3*/ 0B00000000, 0B00000000, /*col4*/ 0B00000000, 0B00000000, /*col5*/ 0B00000000, 0B00000000, /*col6*/ 0B00000000, 0B00000000, /*col7*/ 0B00000000, 0B00000000, 
/* ! */ /*col0*/ 0B00000000, 0B00000000, /*col1*/ 0B00000000, 0B00000000, /*col2*/ 0B00000000, 0B00000000, /*col3*/ 0B00001011, 0B11110000, /*col4*/ 0B00000000, 0B00000000, /*col5*/ 0B00000000, 0B00000000, /*col6*/ 0B00000000, 0B00000000, /*col7*/ 0B00000000, 0B00000000, 
/* % */ /*col0*/ 0B00000010, 0B01110000, /*col1*/ 0B00000010, 0B01010000, /*col2*/ 0B00000001, 0B01110000, /*col3*/ 0B00001110, 0B10000000, /*col4*/ 0B00001010, 0B10000000, /*col5*/ 0B00001110, 0B01000000, /*col6*/ 0B00000000, 0B00000000, /*col7*/ 0B00000000, 0B00000000, 
/* ( */ /*col0*/ 0B00000000, 0B00000000, /*col1*/ 0B00000000, 0B00000000, /*col2*/ 0B00001111, 0B11110000, /*col3*/ 0B00010000, 0B00001000, /*col4*/ 0B00000000, 0B00000000, /*col5*/ 0B00000000, 0B00000000, /*col6*/ 0B00000000, 0B00000000, /*col7*/ 0B00000000, 0B00000000, 
/* ) */ /*col0*/ 0B00000000, 0B00000000, /*col1*/ 0B00000000, 0B00000000, /*col2*/ 0B00011000, 0B00011000, /*col3*/ 0B00000111, 0B11100000, /*col4*/ 0B00000000, 0B00000000, /*col5*/ 0B00000000, 0B00000000, /*col6*/ 0B00000000, 0B00000000, /*col7*/ 0B00000000, 0B00000000, 
/* * */ /*col0*/ 0B00000000, 0B00000000, /*col1*/ 0B00000001, 0B00100000, /*col2*/ 0B00000000, 0B11000000, /*col3*/ 0B00000011, 0B11110000, /*col4*/ 0B00000000, 0B11000000, /*col5*/ 0B00000001, 0B00100000, /*col6*/ 0B00000000, 0B00000000, /*col7*/ 0B00000000, 0B00000000, 
/* + */ /*col0*/ 0B00000000, 0B00000000, /*col1*/ 0B00000001, 0B00000000, /*col2*/ 0B00000001, 0B00000000, /*col3*/ 0B00000111, 0B11000000, /*col4*/ 0B00000001, 0B00000000, /*col5*/ 0B00000001, 0B00000000, /*col6*/ 0B00000000, 0B00000000, /*col7*/ 0B00000000, 0B00000000, 
/* , */ /*col0*/ 0B00000000, 0B00000000, /*col1*/ 0B00000000, 0B00000000, /*col2*/ 0B00010000, 0B00000000, /*col3*/ 0B00001100, 0B00000000, /*col4*/ 0B00000000, 0B00000000, /*col5*/ 0B00000000, 0B00000000, /*col6*/ 0B00000000, 0B00000000, /*col7*/ 0B00000000, 0B00000000, 
/* - */ /*col0*/ 0B00000000, 0B00000000, /*col1*/ 0B00000000, 0B00000000, /*col2*/ 0B00000001, 0B00000000, /*col3*/ 0B00000001, 0B00000000, /*col4*/ 0B00000001, 0B00000000, /*col5*/ 0B00000000, 0B00000000, /*col6*/ 0B00000000, 0B00000000, /*col7*/ 0B00000000, 0B00000000, 
/* . */ /*col0*/ 0B00000000, 0B00000000, /*col1*/ 0B00000000, 0B00000000, /*col2*/ 0B00000000, 0B00000000, /*col3*/ 0B00001100, 0B00000000, /*col4*/ 0B00000000, 0B00000000, /*col5*/ 0B00000000, 0B00000000, /*col6*/ 0B00000000, 0B00000000, /*col7*/ 0B00000000, 0B00000000, 
/* / */ /*col0*/ 0B00000000, 0B00000000, /*col1*/ 0B00010000, 0B00000000, /*col2*/ 0B00001100, 0B00000000, /*col3*/ 0B00000011, 0B10000000, /*col4*/ 0B00000000, 0B01100000, /*col5*/ 0B00000000, 0B00010000, /*col6*/ 0B00000000, 0B00000000, /*col7*/ 0B00000000, 0B00000000, 
/* 0 */ /*col0*/ 0B00000000, 0B00000000, /*col1*/ 0B00000111, 0B11100000, /*col2*/ 0B00001100, 0B00110000, /*col3*/ 0B00001000, 0B00010000, /*col4*/ 0B00001000, 0B10010000, /*col5*/ 0B00001100, 0B00110000, /*col6*/ 0B00000111, 0B11100000, /*col7*/ 0B00000000, 0B00000000, 
/* 1 */ /*col0*/ 0B00000000, 0B00000000, /*col1*/ 0B00001000, 0B00010000, /*col2*/ 0B00001000, 0B00010000, /*col3*/ 0B00001111, 0B11110000, /*col4*/ 0B00001000, 0B00000000, /*col5*/ 0B00001000, 0B00000000, /*col6*/ 0B00000000, 0B00000000, /*col7*/ 0B00000000, 0B00000000, 
/* 2 */ /*col0*/ 0B00000000, 0B00000000, /*col1*/ 0B00001000, 0B00100000, /*col2*/ 0B00001100, 0B00010000, /*col3*/ 0B00001010, 0B00010000, /*col4*/ 0B00001011, 0B00010000, /*col5*/ 0B00001001, 0B10010000, /*col6*/ 0B00001000, 0B11100000, /*col7*/ 0B00000000, 0B00000000, 
/* 3 */ /*col0*/ 0B00000000, 0B00000000, /*col1*/ 0B00000100, 0B00100000, /*col2*/ 0B00001000, 0B10010000, /*col3*/ 0B00001000, 0B10010000, /*col4*/ 0B00001000, 0B10010000, /*col5*/ 0B00001001, 0B10010000, /*col6*/ 0B00000111, 0B01100000, /*col7*/ 0B00000000, 0B00000000, 
/* 4 */ /*col0*/ 0B00000000, 0B00000000, /*col1*/ 0B00000011, 0B00000000, /*col2*/ 0B00000011, 0B10000000, /*col3*/ 0B00000010, 0B01000000, /*col4*/ 0B00000010, 0B00110000, /*col5*/ 0B00001111, 0B11110000, /*col6*/ 0B00000010, 0B00000000, /*col7*/ 0B00000000, 0B00000000, 
/* 5 */ /*col0*/ 0B00000000, 0B00000000, /*col1*/ 0B00001000, 0B11110000, /*col2*/ 0B00001000, 0B10010000, /*col3*/ 0B00001000, 0B10010000, /*col4*/ 0B00001000, 0B10010000, /*col5*/ 0B00001001, 0B10010000, /*col6*/ 0B00000111, 0B00000000, /*col7*/ 0B00000000, 0B00000000, 
/* 6 */ /*col0*/ 0B00000000, 0B00000000, /*col1*/ 0B00000111, 0B11000000, /*col2*/ 0B00001001, 0B00100000, /*col3*/ 0B00001000, 0B10010000, /*col4*/ 0B00001000, 0B10010000, /*col5*/ 0B00001000, 0B10010000, /*col6*/ 0B00000111, 0B00010000, /*col7*/ 0B00000000, 0B00000000, 
/* 7 */ /*col0*/ 0B00000000, 0B00000000, /*col1*/ 0B00000000, 0B00010000, /*col2*/ 0B00001000, 0B00010000, /*col3*/ 0B00000110, 0B00010000, /*col4*/ 0B00000001, 0B10010000, /*col5*/ 0B00000000, 0B01110000, /*col6*/ 0B00000000, 0B00010000, /*col7*/ 0B00000000, 0B00000000, 
/* 8 */ /*col0*/ 0B00000000, 0B00000000, /*col1*/ 0B00000111, 0B01100000, /*col2*/ 0B00001000, 0B10010000, /*col3*/ 0B00001000, 0B10010000, /*col4*/ 0B00001000, 0B10010000, /*col5*/ 0B00001000, 0B10010000, /*col6*/ 0B00000111, 0B01100000, /*col7*/ 0B00000000, 0B00000000, 
/* 9 */ /*col0*/ 0B00000000, 0B00000000, /*col1*/ 0B00001000, 0B11100000, /*col2*/ 0B00001001, 0B00010000, /*col3*/ 0B00001001, 0B00010000, /*col4*/ 0B00001001, 0B00010000, /*col5*/ 0B00000101, 0B00010000, /*col6*/ 0B00000011, 0B11100000, /*col7*/ 0B00000000, 0B00000000, 
/* : */ /*col0*/ 0B00000000, 0B00000000, /*col1*/ 0B00000000, 0B00000000, /*col2*/ 0B00000000, 0B00000000, /*col3*/ 0B00001100, 0B11000000, /*col4*/ 0B00000000, 0B00000000, /*col5*/ 0B00000000, 0B00000000, /*col6*/ 0B00000000, 0B00000000, /*col7*/ 0B00000000, 0B00000000, 
/* = */ /*col0*/ 0B00000010, 0B10000000, /*col1*/ 0B00000010, 0B10000000, /*col2*/ 0B00000010, 0B10000000, /*col3*/ 0B00000010, 0B10000000, /*col4*/ 0B00000010, 0B10000000, /*col5*/ 0B00000010, 0B10000000, /*col6*/ 0B00000000, 0B00000000, /*col7*/ 0B00000000, 0B00000000, 
/* A */ /*col0*/ 0B00000000, 0B00000000, /*col1*/ 0B00001100, 0B00000000, /*col2*/ 0B00000011, 0B10000000, /*col3*/ 0B00000010, 0B01110000, /*col4*/ 0B00000010, 0B01110000, /*col5*/ 0B00000011, 0B10000000, /*col6*/ 0B00001100, 0B00000000, /*col7*/ 0B00000000, 0B00000000, 
/* B */ /*col0*/ 0B00000000, 0B00000000, /*col1*/ 0B00001111, 0B11110000, /*col2*/ 0B00001000, 0B10010000, /*col3*/ 0B00001000, 0B10010000, /*col4*/ 0B00001000, 0B10010000, /*col5*/ 0B00001000, 0B10010000, /*col6*/ 0B00000111, 0B01100000, /*col7*/ 0B00000000, 0B00000000, 
/* C */ /*col0*/ 0B00000000, 0B00000000, /*col1*/ 0B00000011, 0B11000000, /*col2*/ 0B00000100, 0B00100000, /*col3*/ 0B00001000, 0B00010000, /*col4*/ 0B00001000, 0B00010000, /*col5*/ 0B00001000, 0B00010000, /*col6*/ 0B00000100, 0B00100000, /*col7*/ 0B00000000, 0B00000000, 
/* D */ /*col0*/ 0B00000000, 0B00000000, /*col1*/ 0B00001111, 0B11110000, /*col2*/ 0B00001000, 0B00010000, /*col3*/ 0B00001000, 0B00010000, /*col4*/ 0B00001000, 0B00010000, /*col5*/ 0B00000100, 0B00100000, /*col6*/ 0B00000011, 0B11000000, /*col7*/ 0B00000000, 0B00000000, 
/* E */ /*col0*/ 0B00000000, 0B00000000, /*col1*/ 0B00001111, 0B11110000, /*col2*/ 0B00001000, 0B10010000, /*col3*/ 0B00001000, 0B10010000, /*col4*/ 0B00001000, 0B10010000, /*col5*/ 0B00001000, 0B10010000, /*col6*/ 0B00001000, 0B10010000, /*col7*/ 0B00000000, 0B00000000, 
/* F */ /*col0*/ 0B00000000, 0B00000000, /*col1*/ 0B00001111, 0B11110000, /*col2*/ 0B00000000, 0B10010000, /*col3*/ 0B00000000, 0B10010000, /*col4*/ 0B00000000, 0B10010000, /*col5*/ 0B00000000, 0B10010000, /*col6*/ 0B00000000, 0B10010000, /*col7*/ 0B00000000, 0B00000000, 
/* G */ /*col0*/ 0B00000000, 0B00000000, /*col1*/ 0B00000011, 0B11000000, /*col2*/ 0B00000100, 0B00100000, /*col3*/ 0B00001000, 0B00010000, /*col4*/ 0B00001000, 0B00010000, /*col5*/ 0B00001001, 0B00010000, /*col6*/ 0B00000111, 0B00100000, /*col7*/ 0B00000000, 0B00000000, 
/* H */ /*col0*/ 0B00000000, 0B00000000, /*col1*/ 0B00001111, 0B11110000, /*col2*/ 0B00000000, 0B10000000, /*col3*/ 0B00000000, 0B10000000, /*col4*/ 0B00000000, 0B10000000, /*col5*/ 0B00000000, 0B10000000, /*col6*/ 0B00001111, 0B11110000, /*col7*/ 0B00000000, 0B00000000, 
/* I */ /*col0*/ 0B00000000, 0B00000000, /*col1*/ 0B00001000, 0B00010000, /*col2*/ 0B00001000, 0B00010000, /*col3*/ 0B00001111, 0B11110000, /*col4*/ 0B00001000, 0B00010000, /*col5*/ 0B00001000, 0B00010000, /*col6*/ 0B00000000, 0B00000000, /*col7*/ 0B00000000, 0B00000000, 
/* J */ /*col0*/ 0B00000000, 0B00000000, /*col1*/ 0B00000100, 0B00000000, /*col2*/ 0B00001000, 0B00000000, /*col3*/ 0B00001000, 0B00010000, /*col4*/ 0B00001000, 0B00010000, /*col5*/ 0B00000111, 0B11110000, /*col6*/ 0B00000000, 0B00000000, /*col7*/ 0B00000000, 0B00000000, 
/* K */ /*col0*/ 0B00000000, 0B00000000, /*col1*/ 0B00001111, 0B11110000, /*col2*/ 0B00000000, 0B10000000, /*col3*/ 0B00000001, 0B01000000, /*col4*/ 0B00000010, 0B00100000, /*col5*/ 0B00000100, 0B00010000, /*col6*/ 0B00001000, 0B00000000, /*col7*/ 0B00000000, 0B00000000, 
/* L */ /*col0*/ 0B00000000, 0B00000000, /*col1*/ 0B00001111, 0B11110000, /*col2*/ 0B00001000, 0B00000000, /*col3*/ 0B00001000, 0B00000000, /*col4*/ 0B00001000, 0B00000000, /*col5*/ 0B00001000, 0B00000000, /*col6*/ 0B00001000, 0B00000000, /*col7*/ 0B00000000, 0B00000000, 
/* M */ /*col0*/ 0B00000000, 0B00000000, /*col1*/ 0B00001111, 0B11110000, /*col2*/ 0B00000000, 0B01100000, /*col3*/ 0B00000001, 0B10000000, /*col4*/ 0B00000001, 0B10000000, /*col5*/ 0B00000000, 0B01100000, /*col6*/ 0B00001111, 0B11110000, /*col7*/ 0B00000000, 0B00000000, 
/* N */ /*col0*/ 0B00000000, 0B00000000, /*col1*/ 0B00001111, 0B11110000, /*col2*/ 0B00000000, 0B00100000, /*col3*/ 0B00000000, 0B11000000, /*col4*/ 0B00000011, 0B00000000, /*col5*/ 0B00000100, 0B00000000, /*col6*/ 0B00001111, 0B11110000, /*col7*/ 0B00000000, 0B00000000, 
/* O */ /*col0*/ 0B00000000, 0B00000000, /*col1*/ 0B00000111, 0B11100000, /*col2*/ 0B00001100, 0B00110000, /*col3*/ 0B00001000, 0B00010000, /*col4*/ 0B00001000, 0B00010000, /*col5*/ 0B00001100, 0B00110000, /*col6*/ 0B00000111, 0B11100000, /*col7*/ 0B00000000, 0B00000000, 
/* P */ /*col0*/ 0B00000000, 0B00000000, /*col1*/ 0B00001111, 0B11110000, /*col2*/ 0B00000001, 0B00010000, /*col3*/ 0B00000001, 0B00010000, /*col4*/ 0B00000001, 0B00010000, /*col5*/ 0B00000001, 0B00010000, /*col6*/ 0B00000000, 0B11100000, /*col7*/ 0B00000000, 0B00000000, 
/* Q */ /*col0*/ 0B00000000, 0B00000000, /*col1*/ 0B00000111, 0B11100000, /*col2*/ 0B00001100, 0B00110000, /*col3*/ 0B00001000, 0B00010000, /*col4*/ 0B00001000, 0B00010000, /*col5*/ 0B00011100, 0B00110000, /*col6*/ 0B00010111, 0B11100000, /*col7*/ 0B00000000, 0B00000000, 
/* R */ /*col0*/ 0B00000000, 0B00000000, /*col1*/ 0B00001111, 0B11110000, /*col2*/ 0B00000001, 0B00010000, /*col3*/ 0B00000001, 0B00010000, /*col4*/ 0B00000001, 0B00010000, /*col5*/ 0B00000011, 0B00010000, /*col6*/ 0B00000100, 0B11100000, /*col7*/ 0B00001000, 0B00000000, 
/* S */ /*col0*/ 0B00000000, 0B00000000, /*col1*/ 0B00000100, 0B11100000, /*col2*/ 0B00001000, 0B10010000, /*col3*/ 0B00001000, 0B10010000, /*col4*/ 0B00001000, 0B10010000, /*col5*/ 0B00001001, 0B00010000, /*col6*/ 0B00000111, 0B00100000, /*col7*/ 0B00000000, 0B00000000, 
/* T */ /*col0*/ 0B00000000, 0B00010000, /*col1*/ 0B00000000, 0B00010000, /*col2*/ 0B00000000, 0B00010000, /*col3*/ 0B00001111, 0B11110000, /*col4*/ 0B00000000, 0B00010000, /*col5*/ 0B00000000, 0B00010000, /*col6*/ 0B00000000, 0B00010000, /*col7*/ 0B00000000, 0B00000000, 
/* U */ /*col0*/ 0B00000000, 0B00000000, /*col1*/ 0B00000111, 0B11110000, /*col2*/ 0B00001000, 0B00000000, /*col3*/ 0B00001000, 0B00000000, /*col4*/ 0B00001000, 0B00000000, /*col5*/ 0B00001000, 0B00000000, /*col6*/ 0B00000111, 0B11110000, /*col7*/ 0B00000000, 0B00000000, 
/* V */ /*col0*/ 0B00000000, 0B00000000, /*col1*/ 0B00000000, 0B00110000, /*col2*/ 0B00000001, 0B11000000, /*col3*/ 0B00001110, 0B00000000, /*col4*/ 0B00001110, 0B00000000, /*col5*/ 0B00000001, 0B11000000, /*col6*/ 0B00000000, 0B00110000, /*col7*/ 0B00000000, 0B00000000, 
/* W */ /*col0*/ 0B00000000, 0B11110000, /*col1*/ 0B00001111, 0B00000000, /*col2*/ 0B00000011, 0B10000000, /*col3*/ 0B00000000, 0B01100000, /*col4*/ 0B00000011, 0B10000000, /*col5*/ 0B00001111, 0B00000000, /*col6*/ 0B00000000, 0B11110000, /*col7*/ 0B00000000, 0B00000000, 
/* X */ /*col0*/ 0B00000000, 0B00000000, /*col1*/ 0B00001000, 0B00010000, /*col2*/ 0B00000110, 0B01100000, /*col3*/ 0B00000001, 0B10000000, /*col4*/ 0B00000001, 0B10000000, /*col5*/ 0B00000110, 0B01100000, /*col6*/ 0B00001000, 0B00010000, /*col7*/ 0B00000000, 0B00000000, 
/* Y */ /*col0*/ 0B00000000, 0B00010000, /*col1*/ 0B00000000, 0B00110000, /*col2*/ 0B00000000, 0B11000000, /*col3*/ 0B00001111, 0B10000000, /*col4*/ 0B00000000, 0B11000000, /*col5*/ 0B00000000, 0B00110000, /*col6*/ 0B00000000, 0B00010000, /*col7*/ 0B00000000, 0B00000000, 
/* Z */ /*col0*/ 0B00000000, 0B00000000, /*col1*/ 0B00001000, 0B00010000, /*col2*/ 0B00001110, 0B00010000, /*col3*/ 0B00001011, 0B00010000, /*col4*/ 0B00001000, 0B10010000, /*col5*/ 0B00001000, 0B01110000, /*col6*/ 0B00001000, 0B00010000, /*col7*/ 0B00000000, 0B00000000, 
/* a */ /*col0*/ 0B00000000, 0B00000000, /*col1*/ 0B00000110, 0B01000000, /*col2*/ 0B00001001, 0B01000000, /*col3*/ 0B00001001, 0B01000000, /*col4*/ 0B00001001, 0B01000000, /*col5*/ 0B00001111, 0B10000000, /*col6*/ 0B00000000, 0B00000000, /*col7*/ 0B00000000, 0B00000000, 
/* b */ /*col0*/ 0B00000000, 0B00000000, /*col1*/ 0B00001111, 0B11111000, /*col2*/ 0B00001000, 0B01000000, /*col3*/ 0B00001000, 0B01000000, /*col4*/ 0B00001000, 0B01000000, /*col5*/ 0B00000111, 0B10000000, /*col6*/ 0B00000000, 0B00000000, /*col7*/ 0B00000000, 0B00000000, 
/* c */ /*col0*/ 0B00000000, 0B00000000, /*col1*/ 0B00000111, 0B10000000, /*col2*/ 0B00001100, 0B11000000, /*col3*/ 0B00001000, 0B01000000, /*col4*/ 0B00001000, 0B01000000, /*col5*/ 0B00001000, 0B01000000, /*col6*/ 0B00000000, 0B00000000, /*col7*/ 0B00000000, 0B00000000, 
/* d */ /*col0*/ 0B00000000, 0B00000000, /*col1*/ 0B00000111, 0B10000000, /*col2*/ 0B00001000, 0B01000000, /*col3*/ 0B00001000, 0B01000000, /*col4*/ 0B00001000, 0B01000000, /*col5*/ 0B00001111, 0B11111000, /*col6*/ 0B00000000, 0B00000000, /*col7*/ 0B00000000, 0B00000000, 
/* e */ /*col0*/ 0B00000000, 0B00000000, /*col1*/ 0B00000111, 0B10000000, /*col2*/ 0B00001001, 0B01000000, /*col3*/ 0B00001001, 0B01000000, /*col4*/ 0B00001001, 0B01000000, /*col5*/ 0B00001001, 0B10000000, /*col6*/ 0B00000000, 0B00000000, /*col7*/ 0B00000000, 0B00000000, 
/* f */ /*col0*/ 0B00000000, 0B00000000, /*col1*/ 0B00000000, 0B01000000, /*col2*/ 0B00000000, 0B01000000, /*col3*/ 0B00001111, 0B11110000, /*col4*/ 0B00000000, 0B01001000, /*col5*/ 0B00000000, 0B01001000, /*col6*/ 0B00000000, 0B00000000, /*col7*/ 0B00000000, 0B00000000, 
/* g */ /*col0*/ 0B00000000, 0B00000000, /*col1*/ 0B00000111, 0B10000000, /*col2*/ 0B00101000, 0B01000000, /*col3*/ 0B00101000, 0B01000000, /*col4*/ 0B00101000, 0B01000000, /*col5*/ 0B00011111, 0B11000000, /*col6*/ 0B00000000, 0B00000000, /*col7*/ 0B00000000, 0B00000000, 
/* h */ /*col0*/ 0B00000000, 0B00000000, /*col1*/ 0B00001111, 0B11111000, /*col2*/ 0B00000000, 0B10000000, /*col3*/ 0B00000000, 0B01000000, /*col4*/ 0B00000000, 0B01000000, /*col5*/ 0B00001111, 0B10000000, /*col6*/ 0B00000000, 0B00000000, /*col7*/ 0B00000000, 0B00000000, 
/* i */ /*col0*/ 0B00000000, 0B00000000, /*col1*/ 0B00001000, 0B01000000, /*col2*/ 0B00001000, 0B01000000, /*col3*/ 0B00001111, 0B11001000, /*col4*/ 0B00001000, 0B00000000, /*col5*/ 0B00001000, 0B00000000, /*col6*/ 0B00000000, 0B00000000, /*col7*/ 0B00000000, 0B00000000, 
/* j */ /*col0*/ 0B00000000, 0B00000000, /*col1*/ 0B00100000, 0B01000000, /*col2*/ 0B00100000, 0B01000000, /*col3*/ 0B00011111, 0B11001000, /*col4*/ 0B00000000, 0B00000000, /*col5*/ 0B00000000, 0B00000000, /*col6*/ 0B00000000, 0B00000000, /*col7*/ 0B00000000, 0B00000000, 
/* k */ /*col0*/ 0B00000000, 0B00000000, /*col1*/ 0B00001111, 0B11111000, /*col2*/ 0B00000001, 0B00000000, /*col3*/ 0B00000010, 0B10000000, /*col4*/ 0B00000100, 0B01000000, /*col5*/ 0B00001000, 0B00000000, /*col6*/ 0B00000000, 0B00000000, /*col7*/ 0B00000000, 0B00000000, 
/* l */ /*col0*/ 0B00000000, 0B00001000, /*col1*/ 0B00000000, 0B00001000, /*col2*/ 0B00000111, 0B11111000, /*col3*/ 0B00001000, 0B00000000, /*col4*/ 0B00001000, 0B00000000, /*col5*/ 0B00000000, 0B00000000, /*col6*/ 0B00000000, 0B00000000, /*col7*/ 0B00000000, 0B00000000, 
/* m */ /*col0*/ 0B00000000, 0B00000000, /*col1*/ 0B00001111, 0B11000000, /*col2*/ 0B00000000, 0B01000000, /*col3*/ 0B00001111, 0B11000000, /*col4*/ 0B00000000, 0B01000000, /*col5*/ 0B00001111, 0B11000000, /*col6*/ 0B00000000, 0B00000000, /*col7*/ 0B00000000, 0B00000000, 
/* n */ /*col0*/ 0B00000000, 0B00000000, /*col1*/ 0B00001111, 0B11000000, /*col2*/ 0B00000000, 0B10000000, /*col3*/ 0B00000000, 0B01000000, /*col4*/ 0B00000000, 0B01000000, /*col5*/ 0B00001111, 0B10000000, /*col6*/ 0B00000000, 0B00000000, /*col7*/ 0B00000000, 0B00000000, 
/* o */ /*col0*/ 0B00000000, 0B00000000, /*col1*/ 0B00000111, 0B10000000, /*col2*/ 0B00001000, 0B01000000, /*col3*/ 0B00001000, 0B01000000, /*col4*/ 0B00001000, 0B01000000, /*col5*/ 0B00000111, 0B10000000, /*col6*/ 0B00000000, 0B00000000, /*col7*/ 0B00000000, 0B00000000, 
/* p */ /*col0*/ 0B00000000, 0B00000000, /*col1*/ 0B00111111, 0B11000000, /*col2*/ 0B00001000, 0B01000000, /*col3*/ 0B00001000, 0B01000000, /*col4*/ 0B00001000, 0B01000000, /*col5*/ 0B00000111, 0B10000000, /*col6*/ 0B00000000, 0B00000000, /*col7*/ 0B00000000, 0B00000000, 
/* q */ /*col0*/ 0B00000000, 0B00000000, /*col1*/ 0B00000111, 0B10000000, /*col2*/ 0B00001000, 0B01000000, /*col3*/ 0B00001000, 0B01000000, /*col4*/ 0B00001000, 0B01000000, /*col5*/ 0B00111111, 0B11000000, /*col6*/ 0B00000000, 0B00000000, /*col7*/ 0B00000000, 0B00000000, 
/* r */ /*col0*/ 0B00000000, 0B00000000, /*col1*/ 0B00000000, 0B00000000, /*col2*/ 0B00001111, 0B11000000, /*col3*/ 0B00000000, 0B01000000, /*col4*/ 0B00000000, 0B01000000, /*col5*/ 0B00000000, 0B11000000, /*col6*/ 0B00000000, 0B00000000, /*col7*/ 0B00000000, 0B00000000, 
/* s */ /*col0*/ 0B00000000, 0B00000000, /*col1*/ 0B00001001, 0B10000000, /*col2*/ 0B00001001, 0B01000000, /*col3*/ 0B00001001, 0B01000000, /*col4*/ 0B00001010, 0B01000000, /*col5*/ 0B00000110, 0B01000000, /*col6*/ 0B00000000, 0B00000000, /*col7*/ 0B00000000, 0B00000000, 
/* t */ /*col0*/ 0B00000000, 0B01000000, /*col1*/ 0B00000000, 0B01000000, /*col2*/ 0B00001111, 0B11110000, /*col3*/ 0B00001000, 0B01000000, /*col4*/ 0B00001000, 0B01000000, /*col5*/ 0B00000000, 0B00000000, /*col6*/ 0B00000000, 0B00000000, /*col7*/ 0B00000000, 0B00000000, 
/* u */ /*col0*/ 0B00000000, 0B00000000, /*col1*/ 0B00000111, 0B11000000, /*col2*/ 0B00001000, 0B00000000, /*col3*/ 0B00001000, 0B00000000, /*col4*/ 0B00001000, 0B00000000, /*col5*/ 0B00001111, 0B11000000, /*col6*/ 0B00000000, 0B00000000, /*col7*/ 0B00000000, 0B00000000, 
/* v */ /*col0*/ 0B00000000, 0B00000000, /*col1*/ 0B00000000, 0B11000000, /*col2*/ 0B00000111, 0B00000000, /*col3*/ 0B00001000, 0B00000000, /*col4*/ 0B00000111, 0B00000000, /*col5*/ 0B00000000, 0B11000000, /*col6*/ 0B00000000, 0B00000000, /*col7*/ 0B00000000, 0B00000000, 
/* w */ /*col0*/ 0B00000000, 0B11000000, /*col1*/ 0B00000011, 0B00000000, /*col2*/ 0B00001100, 0B00000000, /*col3*/ 0B00000011, 0B00000000, /*col4*/ 0B00001100, 0B00000000, /*col5*/ 0B00000011, 0B00000000, /*col6*/ 0B00000000, 0B11000000, /*col7*/ 0B00000000, 0B00000000, 
/* x */ /*col0*/ 0B00000000, 0B00000000, /*col1*/ 0B00001000, 0B01000000, /*col2*/ 0B00001100, 0B11000000, /*col3*/ 0B00000011, 0B00000000, /*col4*/ 0B00001100, 0B11000000, /*col5*/ 0B00001000, 0B01000000, /*col6*/ 0B00000000, 0B00000000, /*col7*/ 0B00000000, 0B00000000, 
/* y */ /*col0*/ 0B00000000, 0B00000000, /*col1*/ 0B00100000, 0B11000000, /*col2*/ 0B00110111, 0B00000000, /*col3*/ 0B00001100, 0B00000000, /*col4*/ 0B00000011, 0B10000000, /*col5*/ 0B00000000, 0B01000000, /*col6*/ 0B00000000, 0B00000000, /*col7*/ 0B00000000, 0B00000000, 
/* z */ /*col0*/ 0B00000000, 0B00000000, /*col1*/ 0B00001000, 0B01000000, /*col2*/ 0B00001110, 0B01000000, /*col3*/ 0B00001011, 0B01000000, /*col4*/ 0B00001001, 0B11000000, /*col5*/ 0B00001000, 0B01000000, /*col6*/ 0B00000000, 0B00000000, /*col7*/ 0B00000000, 0B00000000, 
/* § */ /*col0*/ 0B00000000, 0B00000000, /*col1*/ 0B00010001, 0B10100000, /*col2*/ 0B00010010, 0B01010000, /*col3*/ 0B00010010, 0B11010000, /*col4*/ 0B00010100, 0B10010000, /*col5*/ 0B00001011, 0B00010000, /*col6*/ 0B00000000, 0B00000000, /*col7*/ 0B00000000, 0B00000000, 
/* ° */ /*col0*/ 0B00000000, 0B00000000, /*col1*/ 0B00000000, 0B00000000, /*col2*/ 0B00000000, 0B01110000, /*col3*/ 0B00000000, 0B01010000, /*col4*/ 0B00000000, 0B01110000, /*col5*/ 0B00000000, 0B00000000, /*col6*/ 0B00000000, 0B00000000, /*col7*/ 0B00000000, 0B00000000, 
/* Á */ /*col0*/ 0B00000000, 0B00000000, /*col1*/ 0B00001100, 0B00000000, /*col2*/ 0B00000011, 0B10000000, /*col3*/ 0B00000010, 0B01110000, /*col4*/ 0B00000010, 0B01110100, /*col5*/ 0B00000011, 0B10000010, /*col6*/ 0B00001100, 0B00000000, /*col7*/ 0B00000000, 0B00000000, 
/* É */ /*col0*/ 0B00000000, 0B00000000, /*col1*/ 0B00001111, 0B11110000, /*col2*/ 0B00001000, 0B10010000, /*col3*/ 0B00001000, 0B10010000, /*col4*/ 0B00001000, 0B10010100, /*col5*/ 0B00001000, 0B10010010, /*col6*/ 0B00001000, 0B10010000, /*col7*/ 0B00000000, 0B00000000, 
/* Í */ /*col0*/ 0B00000000, 0B00000000, /*col1*/ 0B00001000, 0B00010000, /*col2*/ 0B00001000, 0B00010000, /*col3*/ 0B00001111, 0B11110000, /*col4*/ 0B00001000, 0B00010100, /*col5*/ 0B00001000, 0B00010010, /*col6*/ 0B00000000, 0B00000000, /*col7*/ 0B00000000, 0B00000000, 
/* Ó */ /*col0*/ 0B00000000, 0B00000000, /*col1*/ 0B00000111, 0B11100000, /*col2*/ 0B00001100, 0B00110000, /*col3*/ 0B00001000, 0B00010000, /*col4*/ 0B00001000, 0B00010100, /*col5*/ 0B00001100, 0B00110010, /*col6*/ 0B00000111, 0B11100000, /*col7*/ 0B00000000, 0B00000000, 
/* Ö */ /*col0*/ 0B00000000, 0B00000000, /*col1*/ 0B00000111, 0B11100000, /*col2*/ 0B00001100, 0B00110100, /*col3*/ 0B00001000, 0B00010000, /*col4*/ 0B00001000, 0B00010000, /*col5*/ 0B00001100, 0B00110100, /*col6*/ 0B00000111, 0B11100000, /*col7*/ 0B00000000, 0B00000000, 
/* Ú */ /*col0*/ 0B00000000, 0B00000000, /*col1*/ 0B00000111, 0B11110000, /*col2*/ 0B00001000, 0B00000000, /*col3*/ 0B00001000, 0B00000000, /*col4*/ 0B00001000, 0B00000100, /*col5*/ 0B00001000, 0B00000010, /*col6*/ 0B00000111, 0B11110000, /*col7*/ 0B00000000, 0B00000000, 
/* Ü */ /*col0*/ 0B00000000, 0B00000000, /*col1*/ 0B00000111, 0B11110000, /*col2*/ 0B00001000, 0B00000100, /*col3*/ 0B00001000, 0B00000000, /*col4*/ 0B00001000, 0B00000000, /*col5*/ 0B00001000, 0B00000100, /*col6*/ 0B00000111, 0B11110000, /*col7*/ 0B00000000, 0B00000000, 
/* á */ /*col0*/ 0B00000000, 0B00000000, /*col1*/ 0B00000110, 0B01000000, /*col2*/ 0B00001001, 0B01000000, /*col3*/ 0B00001001, 0B01010000, /*col4*/ 0B00001001, 0B01001000, /*col5*/ 0B00001111, 0B10000000, /*col6*/ 0B00000000, 0B00000000, /*col7*/ 0B00000000, 0B00000000, 
/* é */ /*col0*/ 0B00000000, 0B00000000, /*col1*/ 0B00000111, 0B10000000, /*col2*/ 0B00001001, 0B01000000, /*col3*/ 0B00001001, 0B01010000, /*col4*/ 0B00001001, 0B01001000, /*col5*/ 0B00001001, 0B10000000, /*col6*/ 0B00000000, 0B00000000, /*col7*/ 0B00000000, 0B00000000, 
/* í */ /*col0*/ 0B00000000, 0B00000000, /*col1*/ 0B00001000, 0B01000000, /*col2*/ 0B00001000, 0B01000000, /*col3*/ 0B00001111, 0B11010000, /*col4*/ 0B00001000, 0B00001000, /*col5*/ 0B00001000, 0B00000000, /*col6*/ 0B00000000, 0B00000000, /*col7*/ 0B00000000, 0B00000000, 
/* ó */ /*col0*/ 0B00000000, 0B00000000, /*col1*/ 0B00000111, 0B10000000, /*col2*/ 0B00001000, 0B01000000, /*col3*/ 0B00001000, 0B01010000, /*col4*/ 0B00001000, 0B01001000, /*col5*/ 0B00000111, 0B10000000, /*col6*/ 0B00000000, 0B00000000, /*col7*/ 0B00000000, 0B00000000, 
/* ö */ /*col0*/ 0B00000000, 0B00000000, /*col1*/ 0B00000111, 0B10000000, /*col2*/ 0B00001000, 0B01010000, /*col3*/ 0B00001000, 0B01000000, /*col4*/ 0B00001000, 0B01010000, /*col5*/ 0B00000111, 0B10000000, /*col6*/ 0B00000000, 0B00000000, /*col7*/ 0B00000000, 0B00000000, 
/* ú */ /*col0*/ 0B00000000, 0B00000000, /*col1*/ 0B00000111, 0B11000000, /*col2*/ 0B00001000, 0B00000000, /*col3*/ 0B00001000, 0B00010000, /*col4*/ 0B00001000, 0B00001000, /*col5*/ 0B00001111, 0B11000000, /*col6*/ 0B00000000, 0B00000000, /*col7*/ 0B00000000, 0B00000000, 
/* ü */ /*col0*/ 0B00000000, 0B00000000, /*col1*/ 0B00000111, 0B11000000, /*col2*/ 0B00001000, 0B00010000, /*col3*/ 0B00001000, 0B00000000, /*col4*/ 0B00001000, 0B00010000, /*col5*/ 0B00001111, 0B11000000, /*col6*/ 0B00000000, 0B00000000, /*col7*/ 0B00000000, 0B00000000, 
/* Ő */ /*col0*/ 0B00000000, 0B00000000, /*col1*/ 0B00000111, 0B11100000, /*col2*/ 0B00001100, 0B00110100, /*col3*/ 0B00001000, 0B00010000, /*col4*/ 0B00001000, 0B00010100, /*col5*/ 0B00001100, 0B00110000, /*col6*/ 0B00000111, 0B11100000, /*col7*/ 0B00000000, 0B00000000, 
/* ő */ /*col0*/ 0B00000000, 0B00000000, /*col1*/ 0B00000111, 0B10000000, /*col2*/ 0B00001000, 0B01010000, /*col3*/ 0B00001000, 0B01001000, /*col4*/ 0B00001000, 0B01010000, /*col5*/ 0B00000111, 0B10001000, /*col6*/ 0B00000000, 0B00000000, /*col7*/ 0B00000000, 0B00000000, 
/* Ű */ /*col0*/ 0B00000000, 0B00000000, /*col1*/ 0B00000111, 0B11110000, /*col2*/ 0B00001000, 0B00000100, /*col3*/ 0B00001000, 0B00000000, /*col4*/ 0B00001000, 0B00000100, /*col5*/ 0B00001000, 0B00000000, /*col6*/ 0B00000111, 0B11110000, /*col7*/ 0B00000000, 0B00000000, 
/* ű */ /*col0*/ 0B00000000, 0B00000000, /*col1*/ 0B00000111, 0B11000000, /*col2*/ 0B00001000, 0B00010000, /*col3*/ 0B00001000, 0B00001000, /*col4*/ 0B00001000, 0B00010000, /*col5*/ 0B00001111, 0B11001000, /*col6*/ 0B00000000, 0B00000000, /*col7*/ 0B00000000, 0B00000000, 
};
