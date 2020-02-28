#include <AVR_simulator.h>
void executeFromAddress(AVR_simulator_t * ctx, uint32_t sp)
{
	switch(sp)
	{
case 0x0:
	if(AVR_ldi(ctx, 0x0, /* K */0x2, /* d */0xf) || ctx->breakpointActivated) break;	// ldi {K=00000010, d=1111} HEX:0xe0f2
case 0x1:
	if(AVR_mov(ctx, 0x1, /* d */0x1, /* r */0x1f) || ctx->breakpointActivated) break;	// mov {d=00001, r=11111} HEX:0x2e1f
case 0x2:
	if(AVR_ldi(ctx, 0x2, /* K */0x0, /* d */0xf) || ctx->breakpointActivated) break;	// ldi {K=00000000, d=1111} HEX:0xe0f0
case 0x3:
	if(AVR_mov(ctx, 0x3, /* d */0x0, /* r */0x1f) || ctx->breakpointActivated) break;	// mov {d=00000, r=11111} HEX:0x2e0f
case 0x4:
	if(AVR_mov(ctx, 0x4, /* d */0x1a, /* r */0x1f) || ctx->breakpointActivated) break;	// mov {d=11010, r=11111} HEX:0x2faf
case 0x5:
	if(AVR_mov(ctx, 0x5, /* d */0x1b, /* r */0x1f) || ctx->breakpointActivated) break;	// mov {d=11011, r=11111} HEX:0x2fbf
case 0x6:
	if(AVR_mov(ctx, 0x6, /* d */0x1c, /* r */0x1f) || ctx->breakpointActivated) break;	// mov {d=11100, r=11111} HEX:0x2fcf
case 0x7:
	if(AVR_mov(ctx, 0x7, /* d */0x1d, /* r */0x1f) || ctx->breakpointActivated) break;	// mov {d=11101, r=11111} HEX:0x2fdf
case 0x8:
	if(AVR_mov(ctx, 0x8, /* d */0x2, /* r */0x1f) || ctx->breakpointActivated) break;	// mov {d=00010, r=11111} HEX:0x2e2f
case 0x9:
	if(AVR_mov(ctx, 0x9, /* d */0x3, /* r */0x1f) || ctx->breakpointActivated) break;	// mov {d=00011, r=11111} HEX:0x2e3f
case 0xa:
	if(AVR_mov(ctx, 0xa, /* d */0x4, /* r */0x1f) || ctx->breakpointActivated) break;	// mov {d=00100, r=11111} HEX:0x2e4f
case 0xb:
	if(AVR_mov(ctx, 0xb, /* d */0x5, /* r */0x1f) || ctx->breakpointActivated) break;	// mov {d=00101, r=11111} HEX:0x2e5f
case 0xc:
	if(AVR_ldi(ctx, 0xc, /* K */0x1, /* d */0xf) || ctx->breakpointActivated) break;	// ldi {K=00000001, d=1111} HEX:0xe0f1
case 0xd:
	if(AVR_ldi(ctx, 0xd, /* K */0x60, /* d */0x8) || ctx->breakpointActivated) break;	// ldi {K=01100000, d=1000} HEX:0xe680
case 0xe:
	if(AVR_ldi(ctx, 0xe, /* K */0x0, /* d */0x1) || ctx->breakpointActivated) break;	// ldi {K=00000000, d=0001} HEX:0xe010
case 0xf:
	if(AVR_ldi(ctx, 0xf, /* K */0x5, /* d */0x0) || ctx->breakpointActivated) break;	// ldi {K=00000101, d=0000} HEX:0xe005
case 0x10:
	if(AVR_in(ctx, 0x10, /* A */0x16, /* d */0xa) || ctx->breakpointActivated) break;	// in {A=010110, d=01010} HEX:0xb2a6
case 0x11:
	if(AVR_and(ctx, 0x11, /* d */0xa, /* r */0x10) || ctx->breakpointActivated) break;	// and {d=01010, r=10000} HEX:0x22a0
case 0x12:
	if(AVR_in(ctx, 0x12, /* A */0x16, /* d */0xb) || ctx->breakpointActivated) break;	// in {A=010110, d=01011} HEX:0xb2b6
case 0x13:
	if(AVR_in(ctx, 0x13, /* A */0x16, /* d */0xc) || ctx->breakpointActivated) break;	// in {A=010110, d=01100} HEX:0xb2c6
case 0x14:
	if(AVR_ldi(ctx, 0x14, /* K */0x2, /* d */0xf) || ctx->breakpointActivated) break;	// ldi {K=00000010, d=1111} HEX:0xe0f2
case 0x15:
	if(AVR_in(ctx, 0x15, /* A */0x16, /* d */0x1e) || ctx->breakpointActivated) break;	// in {A=010110, d=11110} HEX:0xb3e6
case 0x16:
	if(AVR_and(ctx, 0x16, /* d */0xb, /* r */0x10) || ctx->breakpointActivated) break;	// and {d=01011, r=10000} HEX:0x22b0
case 0x17:
	if(AVR_and(ctx, 0x17, /* d */0xc, /* r */0x10) || ctx->breakpointActivated) break;	// and {d=01100, r=10000} HEX:0x22c0
case 0x18:
	if(AVR_and(ctx, 0x18, /* d */0x1e, /* r */0x10) || ctx->breakpointActivated) break;	// and {d=11110, r=10000} HEX:0x23e0
case 0x19:
	if(AVR_add(ctx, 0x19, /* d */0xb, /* r */0xb) || ctx->breakpointActivated) break;	// add {d=01011, r=01011} HEX:0xcbb
case 0x1a:
	if(AVR_or(ctx, 0x1a, /* d */0xb, /* r */0xa) || ctx->breakpointActivated) break;	// or {d=01011, r=01010} HEX:0x28ba
case 0x1b:
	if(AVR_mov(ctx, 0x1b, /* d */0xa, /* r */0x1e) || ctx->breakpointActivated) break;	// mov {d=01010, r=11110} HEX:0x2eae
case 0x1c:
	if(AVR_swap(ctx, 0x1c, /* d */0xb) || ctx->breakpointActivated) break;	// swap {d=01011} HEX:0x94b2
case 0x1d:
	if(AVR_add(ctx, 0x1d, /* d */0xc, /* r */0xc) || ctx->breakpointActivated) break;	// add {d=01100, r=01100} HEX:0xccc
case 0x1e:
	if(AVR_or(ctx, 0x1e, /* d */0x1e, /* r */0xc) || ctx->breakpointActivated) break;	// or {d=11110, r=01100} HEX:0x29ec
case 0x1f:
	if(AVR_or(ctx, 0x1f, /* d */0x1e, /* r */0xb) || ctx->breakpointActivated) break;	// or {d=11110, r=01011} HEX:0x29eb
case 0x20:
	if(AVR_ldi(ctx, 0x20, /* K */0x2, /* d */0x6) || ctx->breakpointActivated) break;	// ldi {K=00000010, d=0110} HEX:0xe062
case 0x21:
	if(AVR_in(ctx, 0x21, /* A */0x16, /* d */0xb) || ctx->breakpointActivated) break;	// in {A=010110, d=01011} HEX:0xb2b6
case 0x22:
	if(AVR_out(ctx, 0x22, /* A */0x18, /* r */0x1) || ctx->breakpointActivated) break;	// out {A=011000, r=00001} HEX:0xba18
case 0x23:
	if(AVR_lpm(ctx, 0x23, /* d */0x14, /* i */0x0) || ctx->breakpointActivated) break;	// lpm {d=10100, i=0} HEX:0x9144
case 0x24:
	if(AVR_sbrc(ctx, 0x24, /* b */0x3, /* r */0xb) || ctx->breakpointActivated) break;	// sbrc {b=011, r=01011} HEX:0xfcb3
case 0x25:
	if(AVR_rjmp(ctx, 0x25, /* k */0x7) || ctx->breakpointActivated) break;	// rjmp {k=000000000111} HEX:0xc007
case 0x26:
	if(AVR_movw(ctx, 0x26, /* d */0x1, /* r */0xd) || ctx->breakpointActivated) break;	// movw {d=0001, r=1101} HEX:0x11d
case 0x27:
	if(AVR_movw(ctx, 0x27, /* d */0x2, /* r */0xe) || ctx->breakpointActivated) break;	// movw {d=0010, r=1110} HEX:0x12e
case 0x28:
	if(AVR_sbr(ctx, 0x28, /* K */0x2, /* d */0x1) || ctx->breakpointActivated) break;	// sbr {K=00000010, d=0001} HEX:0x6012
case 0x29:
	if(AVR_ldi(ctx, 0x29, /* K */0x0, /* d */0xf) || ctx->breakpointActivated) break;	// ldi {K=00000000, d=1111} HEX:0xe0f0
case 0x2a:
	if(AVR_mov(ctx, 0x2a, /* d */0x1e, /* r */0x18) || ctx->breakpointActivated) break;	// mov {d=11110, r=11000} HEX:0x2fe8
case 0x2b:
	if(AVR_in(ctx, 0x2b, /* A */0x16, /* d */0xc) || ctx->breakpointActivated) break;	// in {A=010110, d=01100} HEX:0xb2c6
case 0x2c:
	if(AVR_ijmp(ctx, 0x2c) || ctx->breakpointActivated) break;	// ijmp {} HEX:0x9409
case 0x2d:
	if(AVR_rjmp(ctx, 0x2d, /* k */0xffb) || ctx->breakpointActivated) break;	// rjmp {k=111111111011} HEX:0xcffb
case 0x2e:
	if(AVR_ldi(ctx, 0x2e, /* K */0x2, /* d */0xf) || ctx->breakpointActivated) break;	// ldi {K=00000010, d=1111} HEX:0xe0f2
case 0x2f:
	if(AVR_in(ctx, 0x2f, /* A */0x16, /* d */0x1e) || ctx->breakpointActivated) break;	// in {A=010110, d=11110} HEX:0xb3e6
case 0x30:
	if(AVR_and(ctx, 0x30, /* d */0xb, /* r */0x10) || ctx->breakpointActivated) break;	// and {d=01011, r=10000} HEX:0x22b0
case 0x31:
	if(AVR_and(ctx, 0x31, /* d */0xc, /* r */0x10) || ctx->breakpointActivated) break;	// and {d=01100, r=10000} HEX:0x22c0
case 0x32:
	if(AVR_and(ctx, 0x32, /* d */0x1e, /* r */0x10) || ctx->breakpointActivated) break;	// and {d=11110, r=10000} HEX:0x23e0
case 0x33:
	if(AVR_add(ctx, 0x33, /* d */0xb, /* r */0xb) || ctx->breakpointActivated) break;	// add {d=01011, r=01011} HEX:0xcbb
case 0x34:
	if(AVR_or(ctx, 0x34, /* d */0xb, /* r */0xa) || ctx->breakpointActivated) break;	// or {d=01011, r=01010} HEX:0x28ba
case 0x35:
	if(AVR_mov(ctx, 0x35, /* d */0xa, /* r */0x1e) || ctx->breakpointActivated) break;	// mov {d=01010, r=11110} HEX:0x2eae
case 0x36:
	if(AVR_swap(ctx, 0x36, /* d */0xb) || ctx->breakpointActivated) break;	// swap {d=01011} HEX:0x94b2
case 0x37:
	if(AVR_add(ctx, 0x37, /* d */0xc, /* r */0xc) || ctx->breakpointActivated) break;	// add {d=01100, r=01100} HEX:0xccc
case 0x38:
	if(AVR_or(ctx, 0x38, /* d */0x1e, /* r */0xc) || ctx->breakpointActivated) break;	// or {d=11110, r=01100} HEX:0x29ec
case 0x39:
	if(AVR_or(ctx, 0x39, /* d */0x1e, /* r */0xb) || ctx->breakpointActivated) break;	// or {d=11110, r=01011} HEX:0x29eb
case 0x3a:
	if(AVR_nop(ctx, 0x3a) || ctx->breakpointActivated) break;	// nop {} HEX:0x0
case 0x3b:
	if(AVR_in(ctx, 0x3b, /* A */0x16, /* d */0xb) || ctx->breakpointActivated) break;	// in {A=010110, d=01011} HEX:0xb2b6
case 0x3c:
	if(AVR_lpm(ctx, 0x3c, /* d */0x15, /* i */0x0) || ctx->breakpointActivated) break;	// lpm {d=10101, i=0} HEX:0x9154
case 0x3d:
	if(AVR_cpi(ctx, 0x3d, /* K */0x4, /* d */0x4) || ctx->breakpointActivated) break;	// cpi {K=00000100, d=0100} HEX:0x3044
case 0x3e:
	if(AVR_breq(ctx, 0x3e, /* k */0x11) || ctx->breakpointActivated) break;	// breq {k=0010001} HEX:0xf089
case 0x3f:
	if(AVR_cpi(ctx, 0x3f, /* K */0x4, /* d */0x5) || ctx->breakpointActivated) break;	// cpi {K=00000100, d=0101} HEX:0x3054
case 0x40:
	if(AVR_breq(ctx, 0x40, /* k */0x11) || ctx->breakpointActivated) break;	// breq {k=0010001} HEX:0xf089
case 0x41:
	if(AVR_add(ctx, 0x41, /* d */0x14, /* r */0x15) || ctx->breakpointActivated) break;	// add {d=10100, r=10101} HEX:0xf45
case 0x42:
	if(AVR_ldi(ctx, 0x42, /* K */0xff, /* d */0x5) || ctx->breakpointActivated) break;	// ldi {K=11111111, d=0101} HEX:0xef5f
case 0x43:
	if(AVR_sbrs(ctx, 0x43, /* b */0x7, /* r */0x14) || ctx->breakpointActivated) break;	// sbrs {b=111, r=10100} HEX:0xff47
case 0x44:
	if(AVR_ldi(ctx, 0x44, /* K */0x0, /* d */0x5) || ctx->breakpointActivated) break;	// ldi {K=00000000, d=0101} HEX:0xe050
case 0x45:
	if(AVR_in(ctx, 0x45, /* A */0x16, /* d */0xc) || ctx->breakpointActivated) break;	// in {A=010110, d=01100} HEX:0xb2c6
case 0x46:
	if(AVR_out(ctx, 0x46, /* A */0x18, /* r */0x16) || ctx->breakpointActivated) break;	// out {A=011000, r=10110} HEX:0xbb68
case 0x47:
	if(AVR_add(ctx, 0x47, /* d */0x1a, /* r */0x14) || ctx->breakpointActivated) break;	// add {d=11010, r=10100} HEX:0xfa4
case 0x48:
	if(AVR_adc(ctx, 0x48, /* d */0x1b, /* r */0x15) || ctx->breakpointActivated) break;	// adc {d=11011, r=10101} HEX:0x1fb5
case 0x49:
	if(AVR_adc(ctx, 0x49, /* d */0x1c, /* r */0x15) || ctx->breakpointActivated) break;	// adc {d=11100, r=10101} HEX:0x1fc5
case 0x4a:
	if(AVR_adc(ctx, 0x4a, /* d */0x1d, /* r */0x15) || ctx->breakpointActivated) break;	// adc {d=11101, r=10101} HEX:0x1fd5
case 0x4b:
	if(AVR_nop(ctx, 0x4b) || ctx->breakpointActivated) break;	// nop {} HEX:0x0
case 0x4c:
	if(AVR_nop(ctx, 0x4c) || ctx->breakpointActivated) break;	// nop {} HEX:0x0
case 0x4d:
	if(AVR_nop(ctx, 0x4d) || ctx->breakpointActivated) break;	// nop {} HEX:0x0
case 0x4e:
	if(AVR_nop(ctx, 0x4e) || ctx->breakpointActivated) break;	// nop {} HEX:0x0
case 0x4f:
	if(AVR_rjmp(ctx, 0x4f, /* k */0xfc5) || ctx->breakpointActivated) break;	// rjmp {k=111111000101} HEX:0xcfc5
case 0x50:
	if(AVR_nop(ctx, 0x50) || ctx->breakpointActivated) break;	// nop {} HEX:0x0
case 0x51:
	if(AVR_nop(ctx, 0x51) || ctx->breakpointActivated) break;	// nop {} HEX:0x0
case 0x52:
	if(AVR_nop(ctx, 0x52) || ctx->breakpointActivated) break;	// nop {} HEX:0x0
case 0x53:
	if(AVR_nop(ctx, 0x53) || ctx->breakpointActivated) break;	// nop {} HEX:0x0
case 0x54:
	if(AVR_nop(ctx, 0x54) || ctx->breakpointActivated) break;	// nop {} HEX:0x0
case 0x55:
	if(AVR_in(ctx, 0x55, /* A */0x16, /* d */0xc) || ctx->breakpointActivated) break;	// in {A=010110, d=01100} HEX:0xb2c6
case 0x56:
	if(AVR_out(ctx, 0x56, /* A */0x18, /* r */0x16) || ctx->breakpointActivated) break;	// out {A=011000, r=10110} HEX:0xbb68
case 0x57:
	if(AVR_sbr(ctx, 0x57, /* K */0x1, /* d */0x1) || ctx->breakpointActivated) break;	// sbr {K=00000001, d=0001} HEX:0x6011
case 0x58:
	if(AVR_nop(ctx, 0x58) || ctx->breakpointActivated) break;	// nop {} HEX:0x0
case 0x59:
	if(AVR_nop(ctx, 0x59) || ctx->breakpointActivated) break;	// nop {} HEX:0x0
case 0x5a:
	if(AVR_nop(ctx, 0x5a) || ctx->breakpointActivated) break;	// nop {} HEX:0x0
case 0x5b:
	if(AVR_nop(ctx, 0x5b) || ctx->breakpointActivated) break;	// nop {} HEX:0x0
case 0x5c:
	if(AVR_nop(ctx, 0x5c) || ctx->breakpointActivated) break;	// nop {} HEX:0x0
case 0x5d:
	if(AVR_nop(ctx, 0x5d) || ctx->breakpointActivated) break;	// nop {} HEX:0x0
case 0x5e:
	if(AVR_nop(ctx, 0x5e) || ctx->breakpointActivated) break;	// nop {} HEX:0x0
case 0x5f:
	if(AVR_rjmp(ctx, 0x5f, /* k */0xfb5) || ctx->breakpointActivated) break;	// rjmp {k=111110110101} HEX:0xcfb5
case 0x60:
	if(AVR_sbrs(ctx, 0x60, /* b */0x1, /* r */0xc) || ctx->breakpointActivated) break;	// sbrs {b=001, r=01100} HEX:0xfec1
case 0x61:
	if(AVR_ldi(ctx, 0x61, /* K */0x67, /* d */0x8) || ctx->breakpointActivated) break;	// ldi {K=01100111, d=1000} HEX:0xe687
case 0x62:
	if(AVR_nop(ctx, 0x62) || ctx->breakpointActivated) break;	// nop {} HEX:0x0
case 0x63:
	if(AVR_nop(ctx, 0x63) || ctx->breakpointActivated) break;	// nop {} HEX:0x0
case 0x64:
	if(AVR_nop(ctx, 0x64) || ctx->breakpointActivated) break;	// nop {} HEX:0x0
case 0x65:
	if(AVR_nop(ctx, 0x65) || ctx->breakpointActivated) break;	// nop {} HEX:0x0
case 0x66:
	if(AVR_rjmp(ctx, 0x66, /* k */0xfc7) || ctx->breakpointActivated) break;	// rjmp {k=111111000111} HEX:0xcfc7
case 0x67:
	if(AVR_sbrc(ctx, 0x67, /* b */0x1, /* r */0xc) || ctx->breakpointActivated) break;	// sbrc {b=001, r=01100} HEX:0xfcc1
case 0x68:
	if(AVR_ldi(ctx, 0x68, /* K */0x6e, /* d */0x8) || ctx->breakpointActivated) break;	// ldi {K=01101110, d=1000} HEX:0xe68e
case 0x69:
	if(AVR_nop(ctx, 0x69) || ctx->breakpointActivated) break;	// nop {} HEX:0x0
case 0x6a:
	if(AVR_nop(ctx, 0x6a) || ctx->breakpointActivated) break;	// nop {} HEX:0x0
case 0x6b:
	if(AVR_nop(ctx, 0x6b) || ctx->breakpointActivated) break;	// nop {} HEX:0x0
case 0x6c:
	if(AVR_nop(ctx, 0x6c) || ctx->breakpointActivated) break;	// nop {} HEX:0x0
case 0x6d:
	if(AVR_rjmp(ctx, 0x6d, /* k */0xfc0) || ctx->breakpointActivated) break;	// rjmp {k=111111000000} HEX:0xcfc0
case 0x6e:
	if(AVR_movw(ctx, 0x6e, /* d */0x3, /* r */0xd) || ctx->breakpointActivated) break;	// movw {d=0011, r=1101} HEX:0x13d
case 0x6f:
	if(AVR_movw(ctx, 0x6f, /* d */0x4, /* r */0xe) || ctx->breakpointActivated) break;	// movw {d=0100, r=1110} HEX:0x14e
case 0x70:
	if(AVR_ldi(ctx, 0x70, /* K */0x75, /* d */0x8) || ctx->breakpointActivated) break;	// ldi {K=01110101, d=1000} HEX:0xe785
case 0x71:
	if(AVR_out(ctx, 0x71, /* A */0x18, /* r */0x1) || ctx->breakpointActivated) break;	// out {A=011000, r=00001} HEX:0xba18
case 0x72:
	if(AVR_out(ctx, 0x72, /* A */0x17, /* r */0x1) || ctx->breakpointActivated) break;	// out {A=010111, r=00001} HEX:0xba17
case 0x73:
	if(AVR_nop(ctx, 0x73) || ctx->breakpointActivated) break;	// nop {} HEX:0x0
case 0x74:
	if(AVR_rjmp(ctx, 0x74, /* k */0xfb9) || ctx->breakpointActivated) break;	// rjmp {k=111110111001} HEX:0xcfb9
case 0x75:
	if(AVR_mov(ctx, 0x75, /* d */0x13, /* r */0x6) || ctx->breakpointActivated) break;	// mov {d=10011, r=00110} HEX:0x2d36
case 0x76:
	if(AVR_ldi(ctx, 0x76, /* K */0x7c, /* d */0x9) || ctx->breakpointActivated) break;	// ldi {K=01111100, d=1001} HEX:0xe79c
case 0x77:
	if(AVR_ldi(ctx, 0x77, /* K */0xbb, /* d */0x8) || ctx->breakpointActivated) break;	// ldi {K=10111011, d=1000} HEX:0xeb8b
case 0x78:
	if(AVR_nop(ctx, 0x78) || ctx->breakpointActivated) break;	// nop {} HEX:0x0
case 0x79:
	if(AVR_nop(ctx, 0x79) || ctx->breakpointActivated) break;	// nop {} HEX:0x0
case 0x7a:
	if(AVR_nop(ctx, 0x7a) || ctx->breakpointActivated) break;	// nop {} HEX:0x0
case 0x7b:
	if(AVR_rjmp(ctx, 0x7b, /* k */0xfb2) || ctx->breakpointActivated) break;	// rjmp {k=111110110010} HEX:0xcfb2
case 0x7c:
	if(AVR_mov(ctx, 0x7c, /* d */0x13, /* r */0x7) || ctx->breakpointActivated) break;	// mov {d=10011, r=00111} HEX:0x2d37
case 0x7d:
	if(AVR_ldi(ctx, 0x7d, /* K */0x83, /* d */0x9) || ctx->breakpointActivated) break;	// ldi {K=10000011, d=1001} HEX:0xe893
case 0x7e:
	if(AVR_ldi(ctx, 0x7e, /* K */0xbb, /* d */0x8) || ctx->breakpointActivated) break;	// ldi {K=10111011, d=1000} HEX:0xeb8b
case 0x7f:
	if(AVR_nop(ctx, 0x7f) || ctx->breakpointActivated) break;	// nop {} HEX:0x0
case 0x80:
	if(AVR_nop(ctx, 0x80) || ctx->breakpointActivated) break;	// nop {} HEX:0x0
case 0x81:
	if(AVR_nop(ctx, 0x81) || ctx->breakpointActivated) break;	// nop {} HEX:0x0
case 0x82:
	if(AVR_rjmp(ctx, 0x82, /* k */0xfab) || ctx->breakpointActivated) break;	// rjmp {k=111110101011} HEX:0xcfab
case 0x83:
	if(AVR_mov(ctx, 0x83, /* d */0x13, /* r */0x8) || ctx->breakpointActivated) break;	// mov {d=10011, r=01000} HEX:0x2d38
case 0x84:
	if(AVR_ldi(ctx, 0x84, /* K */0x8a, /* d */0x9) || ctx->breakpointActivated) break;	// ldi {K=10001010, d=1001} HEX:0xe89a
case 0x85:
	if(AVR_ldi(ctx, 0x85, /* K */0xbb, /* d */0x8) || ctx->breakpointActivated) break;	// ldi {K=10111011, d=1000} HEX:0xeb8b
case 0x86:
	if(AVR_nop(ctx, 0x86) || ctx->breakpointActivated) break;	// nop {} HEX:0x0
case 0x87:
	if(AVR_nop(ctx, 0x87) || ctx->breakpointActivated) break;	// nop {} HEX:0x0
case 0x88:
	if(AVR_nop(ctx, 0x88) || ctx->breakpointActivated) break;	// nop {} HEX:0x0
case 0x89:
	if(AVR_rjmp(ctx, 0x89, /* k */0xfa4) || ctx->breakpointActivated) break;	// rjmp {k=111110100100} HEX:0xcfa4
case 0x8a:
	if(AVR_mov(ctx, 0x8a, /* d */0x13, /* r */0x9) || ctx->breakpointActivated) break;	// mov {d=10011, r=01001} HEX:0x2d39
case 0x8b:
	if(AVR_ldi(ctx, 0x8b, /* K */0x91, /* d */0x9) || ctx->breakpointActivated) break;	// ldi {K=10010001, d=1001} HEX:0xe991
case 0x8c:
	if(AVR_ldi(ctx, 0x8c, /* K */0xbb, /* d */0x8) || ctx->breakpointActivated) break;	// ldi {K=10111011, d=1000} HEX:0xeb8b
case 0x8d:
	if(AVR_nop(ctx, 0x8d) || ctx->breakpointActivated) break;	// nop {} HEX:0x0
case 0x8e:
	if(AVR_nop(ctx, 0x8e) || ctx->breakpointActivated) break;	// nop {} HEX:0x0
case 0x8f:
	if(AVR_nop(ctx, 0x8f) || ctx->breakpointActivated) break;	// nop {} HEX:0x0
case 0x90:
	if(AVR_rjmp(ctx, 0x90, /* k */0xf9d) || ctx->breakpointActivated) break;	// rjmp {k=111110011101} HEX:0xcf9d
case 0x91:
	if(AVR_mov(ctx, 0x91, /* d */0x13, /* r */0x11) || ctx->breakpointActivated) break;	// mov {d=10011, r=10001} HEX:0x2f31
case 0x92:
	if(AVR_ldi(ctx, 0x92, /* K */0x0, /* d */0x1) || ctx->breakpointActivated) break;	// ldi {K=00000000, d=0001} HEX:0xe010
case 0x93:
	if(AVR_ldi(ctx, 0x93, /* K */0x98, /* d */0x9) || ctx->breakpointActivated) break;	// ldi {K=10011000, d=1001} HEX:0xe998
case 0x94:
	if(AVR_ldi(ctx, 0x94, /* K */0xbb, /* d */0x8) || ctx->breakpointActivated) break;	// ldi {K=10111011, d=1000} HEX:0xeb8b
case 0x95:
	if(AVR_movw(ctx, 0x95, /* d */0x3, /* r */0x1) || ctx->breakpointActivated) break;	// movw {d=0011, r=0001} HEX:0x131
case 0x96:
	if(AVR_movw(ctx, 0x96, /* d */0x4, /* r */0x2) || ctx->breakpointActivated) break;	// movw {d=0100, r=0010} HEX:0x142
case 0x97:
	if(AVR_rjmp(ctx, 0x97, /* k */0xf96) || ctx->breakpointActivated) break;	// rjmp {k=111110010110} HEX:0xcf96
case 0x98:
	if(AVR_mov(ctx, 0x98, /* d */0x13, /* r */0x6) || ctx->breakpointActivated) break;	// mov {d=10011, r=00110} HEX:0x2d36
case 0x99:
	if(AVR_ldi(ctx, 0x99, /* K */0x9f, /* d */0x9) || ctx->breakpointActivated) break;	// ldi {K=10011111, d=1001} HEX:0xe99f
case 0x9a:
	if(AVR_ldi(ctx, 0x9a, /* K */0xbb, /* d */0x8) || ctx->breakpointActivated) break;	// ldi {K=10111011, d=1000} HEX:0xeb8b
case 0x9b:
	if(AVR_nop(ctx, 0x9b) || ctx->breakpointActivated) break;	// nop {} HEX:0x0
case 0x9c:
	if(AVR_nop(ctx, 0x9c) || ctx->breakpointActivated) break;	// nop {} HEX:0x0
case 0x9d:
	if(AVR_nop(ctx, 0x9d) || ctx->breakpointActivated) break;	// nop {} HEX:0x0
case 0x9e:
	if(AVR_rjmp(ctx, 0x9e, /* k */0xf8f) || ctx->breakpointActivated) break;	// rjmp {k=111110001111} HEX:0xcf8f
case 0x9f:
	if(AVR_mov(ctx, 0x9f, /* d */0x13, /* r */0x7) || ctx->breakpointActivated) break;	// mov {d=10011, r=00111} HEX:0x2d37
case 0xa0:
	if(AVR_ldi(ctx, 0xa0, /* K */0xa6, /* d */0x9) || ctx->breakpointActivated) break;	// ldi {K=10100110, d=1001} HEX:0xea96
case 0xa1:
	if(AVR_ldi(ctx, 0xa1, /* K */0xbb, /* d */0x8) || ctx->breakpointActivated) break;	// ldi {K=10111011, d=1000} HEX:0xeb8b
case 0xa2:
	if(AVR_nop(ctx, 0xa2) || ctx->breakpointActivated) break;	// nop {} HEX:0x0
case 0xa3:
	if(AVR_nop(ctx, 0xa3) || ctx->breakpointActivated) break;	// nop {} HEX:0x0
case 0xa4:
	if(AVR_nop(ctx, 0xa4) || ctx->breakpointActivated) break;	// nop {} HEX:0x0
case 0xa5:
	if(AVR_rjmp(ctx, 0xa5, /* k */0xf88) || ctx->breakpointActivated) break;	// rjmp {k=111110001000} HEX:0xcf88
case 0xa6:
	if(AVR_mov(ctx, 0xa6, /* d */0x13, /* r */0x8) || ctx->breakpointActivated) break;	// mov {d=10011, r=01000} HEX:0x2d38
case 0xa7:
	if(AVR_ldi(ctx, 0xa7, /* K */0xad, /* d */0x9) || ctx->breakpointActivated) break;	// ldi {K=10101101, d=1001} HEX:0xea9d
case 0xa8:
	if(AVR_ldi(ctx, 0xa8, /* K */0xbb, /* d */0x8) || ctx->breakpointActivated) break;	// ldi {K=10111011, d=1000} HEX:0xeb8b
case 0xa9:
	if(AVR_nop(ctx, 0xa9) || ctx->breakpointActivated) break;	// nop {} HEX:0x0
case 0xaa:
	if(AVR_nop(ctx, 0xaa) || ctx->breakpointActivated) break;	// nop {} HEX:0x0
case 0xab:
	if(AVR_nop(ctx, 0xab) || ctx->breakpointActivated) break;	// nop {} HEX:0x0
case 0xac:
	if(AVR_rjmp(ctx, 0xac, /* k */0xf81) || ctx->breakpointActivated) break;	// rjmp {k=111110000001} HEX:0xcf81
case 0xad:
	if(AVR_mov(ctx, 0xad, /* d */0x13, /* r */0x9) || ctx->breakpointActivated) break;	// mov {d=10011, r=01001} HEX:0x2d39
case 0xae:
	if(AVR_ldi(ctx, 0xae, /* K */0xb4, /* d */0x9) || ctx->breakpointActivated) break;	// ldi {K=10110100, d=1001} HEX:0xeb94
case 0xaf:
	if(AVR_ldi(ctx, 0xaf, /* K */0xbb, /* d */0x8) || ctx->breakpointActivated) break;	// ldi {K=10111011, d=1000} HEX:0xeb8b
case 0xb0:
	if(AVR_nop(ctx, 0xb0) || ctx->breakpointActivated) break;	// nop {} HEX:0x0
case 0xb1:
	if(AVR_nop(ctx, 0xb1) || ctx->breakpointActivated) break;	// nop {} HEX:0x0
case 0xb2:
	if(AVR_nop(ctx, 0xb2) || ctx->breakpointActivated) break;	// nop {} HEX:0x0
case 0xb3:
	if(AVR_rjmp(ctx, 0xb3, /* k */0xf7a) || ctx->breakpointActivated) break;	// rjmp {k=111101111010} HEX:0xcf7a
case 0xb4:
	if(AVR_out(ctx, 0xb4, /* A */0x17, /* r */0x0) || ctx->breakpointActivated) break;	// out {A=010111, r=00000} HEX:0xba07
case 0xb5:
	if(AVR_out(ctx, 0xb5, /* A */0x18, /* r */0x0) || ctx->breakpointActivated) break;	// out {A=011000, r=00000} HEX:0xba08
case 0xb6:
	if(AVR_ldi(ctx, 0xb6, /* K */0x60, /* d */0x8) || ctx->breakpointActivated) break;	// ldi {K=01100000, d=1000} HEX:0xe680
case 0xb7:
	if(AVR_nop(ctx, 0xb7) || ctx->breakpointActivated) break;	// nop {} HEX:0x0
case 0xb8:
	if(AVR_nop(ctx, 0xb8) || ctx->breakpointActivated) break;	// nop {} HEX:0x0
case 0xb9:
	if(AVR_nop(ctx, 0xb9) || ctx->breakpointActivated) break;	// nop {} HEX:0x0
case 0xba:
	if(AVR_rjmp(ctx, 0xba, /* k */0xf73) || ctx->breakpointActivated) break;	// rjmp {k=111101110011} HEX:0xcf73
case 0xbb:
	if(AVR_out(ctx, 0xbb, /* A */0x18, /* r */0x0) || ctx->breakpointActivated) break;	// out {A=011000, r=00000} HEX:0xba08
case 0xbc:
	if(AVR_ldi(ctx, 0xbc, /* K */0x0, /* d */0x6) || ctx->breakpointActivated) break;	// ldi {K=00000000, d=0110} HEX:0xe060
case 0xbd:
	if(AVR_sbrs(ctx, 0xbd, /* b */0x0, /* r */0x13) || ctx->breakpointActivated) break;	// sbrs {b=000, r=10011} HEX:0xff30
case 0xbe:
	if(AVR_ldi(ctx, 0xbe, /* K */0x2, /* d */0x6) || ctx->breakpointActivated) break;	// ldi {K=00000010, d=0110} HEX:0xe062
case 0xbf:
	if(AVR_ldi(ctx, 0xbf, /* K */0xc2, /* d */0x8) || ctx->breakpointActivated) break;	// ldi {K=11000010, d=1000} HEX:0xec82
case 0xc0:
	if(AVR_nop(ctx, 0xc0) || ctx->breakpointActivated) break;	// nop {} HEX:0x0
case 0xc1:
	if(AVR_rjmp(ctx, 0xc1, /* k */0xf6c) || ctx->breakpointActivated) break;	// rjmp {k=111101101100} HEX:0xcf6c
case 0xc2:
	if(AVR_out(ctx, 0xc2, /* A */0x18, /* r */0x0) || ctx->breakpointActivated) break;	// out {A=011000, r=00000} HEX:0xba08
case 0xc3:
	if(AVR_ldi(ctx, 0xc3, /* K */0x0, /* d */0x6) || ctx->breakpointActivated) break;	// ldi {K=00000000, d=0110} HEX:0xe060
case 0xc4:
	if(AVR_sbrs(ctx, 0xc4, /* b */0x1, /* r */0x13) || ctx->breakpointActivated) break;	// sbrs {b=001, r=10011} HEX:0xff31
case 0xc5:
	if(AVR_ldi(ctx, 0xc5, /* K */0x2, /* d */0x6) || ctx->breakpointActivated) break;	// ldi {K=00000010, d=0110} HEX:0xe062
case 0xc6:
	if(AVR_ldi(ctx, 0xc6, /* K */0xc9, /* d */0x8) || ctx->breakpointActivated) break;	// ldi {K=11001001, d=1000} HEX:0xec89
case 0xc7:
	if(AVR_nop(ctx, 0xc7) || ctx->breakpointActivated) break;	// nop {} HEX:0x0
case 0xc8:
	if(AVR_rjmp(ctx, 0xc8, /* k */0xf65) || ctx->breakpointActivated) break;	// rjmp {k=111101100101} HEX:0xcf65
case 0xc9:
	if(AVR_out(ctx, 0xc9, /* A */0x18, /* r */0x0) || ctx->breakpointActivated) break;	// out {A=011000, r=00000} HEX:0xba08
case 0xca:
	if(AVR_ldi(ctx, 0xca, /* K */0x0, /* d */0x6) || ctx->breakpointActivated) break;	// ldi {K=00000000, d=0110} HEX:0xe060
case 0xcb:
	if(AVR_sbrs(ctx, 0xcb, /* b */0x2, /* r */0x13) || ctx->breakpointActivated) break;	// sbrs {b=010, r=10011} HEX:0xff32
case 0xcc:
	if(AVR_ldi(ctx, 0xcc, /* K */0x2, /* d */0x6) || ctx->breakpointActivated) break;	// ldi {K=00000010, d=0110} HEX:0xe062
case 0xcd:
	if(AVR_ldi(ctx, 0xcd, /* K */0xd0, /* d */0x8) || ctx->breakpointActivated) break;	// ldi {K=11010000, d=1000} HEX:0xed80
case 0xce:
	if(AVR_nop(ctx, 0xce) || ctx->breakpointActivated) break;	// nop {} HEX:0x0
case 0xcf:
	if(AVR_rjmp(ctx, 0xcf, /* k */0xf5e) || ctx->breakpointActivated) break;	// rjmp {k=111101011110} HEX:0xcf5e
case 0xd0:
	if(AVR_out(ctx, 0xd0, /* A */0x18, /* r */0x0) || ctx->breakpointActivated) break;	// out {A=011000, r=00000} HEX:0xba08
case 0xd1:
	if(AVR_ldi(ctx, 0xd1, /* K */0x0, /* d */0x6) || ctx->breakpointActivated) break;	// ldi {K=00000000, d=0110} HEX:0xe060
case 0xd2:
	if(AVR_sbrs(ctx, 0xd2, /* b */0x3, /* r */0x13) || ctx->breakpointActivated) break;	// sbrs {b=011, r=10011} HEX:0xff33
case 0xd3:
	if(AVR_ldi(ctx, 0xd3, /* K */0x2, /* d */0x6) || ctx->breakpointActivated) break;	// ldi {K=00000010, d=0110} HEX:0xe062
case 0xd4:
	if(AVR_ldi(ctx, 0xd4, /* K */0xd7, /* d */0x8) || ctx->breakpointActivated) break;	// ldi {K=11010111, d=1000} HEX:0xed87
case 0xd5:
	if(AVR_nop(ctx, 0xd5) || ctx->breakpointActivated) break;	// nop {} HEX:0x0
case 0xd6:
	if(AVR_rjmp(ctx, 0xd6, /* k */0xf57) || ctx->breakpointActivated) break;	// rjmp {k=111101010111} HEX:0xcf57
case 0xd7:
	if(AVR_out(ctx, 0xd7, /* A */0x18, /* r */0x0) || ctx->breakpointActivated) break;	// out {A=011000, r=00000} HEX:0xba08
case 0xd8:
	if(AVR_ldi(ctx, 0xd8, /* K */0x0, /* d */0x6) || ctx->breakpointActivated) break;	// ldi {K=00000000, d=0110} HEX:0xe060
case 0xd9:
	if(AVR_sbrs(ctx, 0xd9, /* b */0x4, /* r */0x13) || ctx->breakpointActivated) break;	// sbrs {b=100, r=10011} HEX:0xff34
case 0xda:
	if(AVR_ldi(ctx, 0xda, /* K */0x2, /* d */0x6) || ctx->breakpointActivated) break;	// ldi {K=00000010, d=0110} HEX:0xe062
case 0xdb:
	if(AVR_ldi(ctx, 0xdb, /* K */0xde, /* d */0x8) || ctx->breakpointActivated) break;	// ldi {K=11011110, d=1000} HEX:0xed8e
case 0xdc:
	if(AVR_nop(ctx, 0xdc) || ctx->breakpointActivated) break;	// nop {} HEX:0x0
case 0xdd:
	if(AVR_rjmp(ctx, 0xdd, /* k */0xf50) || ctx->breakpointActivated) break;	// rjmp {k=111101010000} HEX:0xcf50
case 0xde:
	if(AVR_out(ctx, 0xde, /* A */0x18, /* r */0x0) || ctx->breakpointActivated) break;	// out {A=011000, r=00000} HEX:0xba08
case 0xdf:
	if(AVR_ldi(ctx, 0xdf, /* K */0x0, /* d */0x6) || ctx->breakpointActivated) break;	// ldi {K=00000000, d=0110} HEX:0xe060
case 0xe0:
	if(AVR_sbrs(ctx, 0xe0, /* b */0x5, /* r */0x13) || ctx->breakpointActivated) break;	// sbrs {b=101, r=10011} HEX:0xff35
case 0xe1:
	if(AVR_ldi(ctx, 0xe1, /* K */0x2, /* d */0x6) || ctx->breakpointActivated) break;	// ldi {K=00000010, d=0110} HEX:0xe062
case 0xe2:
	if(AVR_ldi(ctx, 0xe2, /* K */0xe5, /* d */0x8) || ctx->breakpointActivated) break;	// ldi {K=11100101, d=1000} HEX:0xee85
case 0xe3:
	if(AVR_nop(ctx, 0xe3) || ctx->breakpointActivated) break;	// nop {} HEX:0x0
case 0xe4:
	if(AVR_rjmp(ctx, 0xe4, /* k */0xf49) || ctx->breakpointActivated) break;	// rjmp {k=111101001001} HEX:0xcf49
case 0xe5:
	if(AVR_out(ctx, 0xe5, /* A */0x18, /* r */0x0) || ctx->breakpointActivated) break;	// out {A=011000, r=00000} HEX:0xba08
case 0xe6:
	if(AVR_ldi(ctx, 0xe6, /* K */0x0, /* d */0x6) || ctx->breakpointActivated) break;	// ldi {K=00000000, d=0110} HEX:0xe060
case 0xe7:
	if(AVR_sbrs(ctx, 0xe7, /* b */0x6, /* r */0x13) || ctx->breakpointActivated) break;	// sbrs {b=110, r=10011} HEX:0xff36
case 0xe8:
	if(AVR_ldi(ctx, 0xe8, /* K */0x2, /* d */0x6) || ctx->breakpointActivated) break;	// ldi {K=00000010, d=0110} HEX:0xe062
case 0xe9:
	if(AVR_ldi(ctx, 0xe9, /* K */0xec, /* d */0x8) || ctx->breakpointActivated) break;	// ldi {K=11101100, d=1000} HEX:0xee8c
case 0xea:
	if(AVR_nop(ctx, 0xea) || ctx->breakpointActivated) break;	// nop {} HEX:0x0
case 0xeb:
	if(AVR_rjmp(ctx, 0xeb, /* k */0xf42) || ctx->breakpointActivated) break;	// rjmp {k=111101000010} HEX:0xcf42
case 0xec:
	if(AVR_out(ctx, 0xec, /* A */0x18, /* r */0x0) || ctx->breakpointActivated) break;	// out {A=011000, r=00000} HEX:0xba08
case 0xed:
	if(AVR_ldi(ctx, 0xed, /* K */0x0, /* d */0x6) || ctx->breakpointActivated) break;	// ldi {K=00000000, d=0110} HEX:0xe060
case 0xee:
	if(AVR_sbrs(ctx, 0xee, /* b */0x7, /* r */0x13) || ctx->breakpointActivated) break;	// sbrs {b=111, r=10011} HEX:0xff37
case 0xef:
	if(AVR_ldi(ctx, 0xef, /* K */0x2, /* d */0x6) || ctx->breakpointActivated) break;	// ldi {K=00000010, d=0110} HEX:0xe062
case 0xf0:
	if(AVR_mov(ctx, 0xf0, /* d */0x18, /* r */0x19) || ctx->breakpointActivated) break;	// mov {d=11000, r=11001} HEX:0x2f89
case 0xf1:
	if(AVR_nop(ctx, 0xf1) || ctx->breakpointActivated) break;	// nop {} HEX:0x0
case 0xf2:
	if(AVR_rjmp(ctx, 0xf2, /* k */0xf3b) || ctx->breakpointActivated) break;	// rjmp {k=111100111011} HEX:0xcf3b
		default:
			AVR_error_nosp(ctx, sp);
			break;
	}
}
