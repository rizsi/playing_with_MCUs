#include <AVR_simulator.h>
void executeFromAddress(AVR_simulator_t * ctx, uint32_t sp)
{
	switch(sp)
	{
case 0x0:
	if(AVR_ldi(ctx, 0x0, /* K */0x0, /* d */0xf) || ctx->breakpointActivated) break;	// ldi {K=00000000, d=1111} HEX:0xe0f0
case 0x1:
	if(AVR_mov(ctx, 0x1, /* d */0x0, /* r */0x1f) || ctx->breakpointActivated) break;	// mov {d=00000, r=11111} HEX:0x2e0f
case 0x2:
	if(AVR_mov(ctx, 0x2, /* d */0x1a, /* r */0x1f) || ctx->breakpointActivated) break;	// mov {d=11010, r=11111} HEX:0x2faf
case 0x3:
	if(AVR_mov(ctx, 0x3, /* d */0x1b, /* r */0x1f) || ctx->breakpointActivated) break;	// mov {d=11011, r=11111} HEX:0x2fbf
case 0x4:
	if(AVR_mov(ctx, 0x4, /* d */0x1c, /* r */0x1f) || ctx->breakpointActivated) break;	// mov {d=11100, r=11111} HEX:0x2fcf
case 0x5:
	if(AVR_mov(ctx, 0x5, /* d */0x1d, /* r */0x1f) || ctx->breakpointActivated) break;	// mov {d=11101, r=11111} HEX:0x2fdf
case 0x6:
	if(AVR_ldi(ctx, 0x6, /* K */0x1, /* d */0xf) || ctx->breakpointActivated) break;	// ldi {K=00000001, d=1111} HEX:0xe0f1
case 0x7:
	if(AVR_ldi(ctx, 0x7, /* K */0x5a, /* d */0x8) || ctx->breakpointActivated) break;	// ldi {K=01011010, d=1000} HEX:0xe58a
case 0x8:
	if(AVR_ldi(ctx, 0x8, /* K */0x0, /* d */0x1) || ctx->breakpointActivated) break;	// ldi {K=00000000, d=0001} HEX:0xe010
case 0x9:
	if(AVR_ldi(ctx, 0x9, /* K */0x5, /* d */0x0) || ctx->breakpointActivated) break;	// ldi {K=00000101, d=0000} HEX:0xe005
case 0xa:
	if(AVR_in(ctx, 0xa, /* A */0x16, /* d */0xa) || ctx->breakpointActivated) break;	// in {A=010110, d=01010} HEX:0xb2a6
case 0xb:
	if(AVR_and(ctx, 0xb, /* d */0xa, /* r */0x10) || ctx->breakpointActivated) break;	// and {d=01010, r=10000} HEX:0x22a0
case 0xc:
	if(AVR_in(ctx, 0xc, /* A */0x16, /* d */0xb) || ctx->breakpointActivated) break;	// in {A=010110, d=01011} HEX:0xb2b6
case 0xd:
	if(AVR_in(ctx, 0xd, /* A */0x16, /* d */0xc) || ctx->breakpointActivated) break;	// in {A=010110, d=01100} HEX:0xb2c6
case 0xe:
	if(AVR_ldi(ctx, 0xe, /* K */0x2, /* d */0xf) || ctx->breakpointActivated) break;	// ldi {K=00000010, d=1111} HEX:0xe0f2
case 0xf:
	if(AVR_in(ctx, 0xf, /* A */0x16, /* d */0x1e) || ctx->breakpointActivated) break;	// in {A=010110, d=11110} HEX:0xb3e6
case 0x10:
	if(AVR_and(ctx, 0x10, /* d */0xb, /* r */0x10) || ctx->breakpointActivated) break;	// and {d=01011, r=10000} HEX:0x22b0
case 0x11:
	if(AVR_and(ctx, 0x11, /* d */0xc, /* r */0x10) || ctx->breakpointActivated) break;	// and {d=01100, r=10000} HEX:0x22c0
case 0x12:
	if(AVR_and(ctx, 0x12, /* d */0x1e, /* r */0x10) || ctx->breakpointActivated) break;	// and {d=11110, r=10000} HEX:0x23e0
case 0x13:
	if(AVR_add(ctx, 0x13, /* d */0xb, /* r */0xb) || ctx->breakpointActivated) break;	// add {d=01011, r=01011} HEX:0xcbb
case 0x14:
	if(AVR_or(ctx, 0x14, /* d */0xb, /* r */0xa) || ctx->breakpointActivated) break;	// or {d=01011, r=01010} HEX:0x28ba
case 0x15:
	if(AVR_mov(ctx, 0x15, /* d */0xa, /* r */0x1e) || ctx->breakpointActivated) break;	// mov {d=01010, r=11110} HEX:0x2eae
case 0x16:
	if(AVR_swap(ctx, 0x16, /* d */0xb) || ctx->breakpointActivated) break;	// swap {d=01011} HEX:0x94b2
case 0x17:
	if(AVR_add(ctx, 0x17, /* d */0xc, /* r */0xc) || ctx->breakpointActivated) break;	// add {d=01100, r=01100} HEX:0xccc
case 0x18:
	if(AVR_or(ctx, 0x18, /* d */0x1e, /* r */0xc) || ctx->breakpointActivated) break;	// or {d=11110, r=01100} HEX:0x29ec
case 0x19:
	if(AVR_or(ctx, 0x19, /* d */0x1e, /* r */0xb) || ctx->breakpointActivated) break;	// or {d=11110, r=01011} HEX:0x29eb
case 0x1a:
	if(AVR_nop(ctx, 0x1a) || ctx->breakpointActivated) break;	// nop {} HEX:0x0
case 0x1b:
	if(AVR_in(ctx, 0x1b, /* A */0x16, /* d */0xb) || ctx->breakpointActivated) break;	// in {A=010110, d=01011} HEX:0xb2b6
case 0x1c:
	if(AVR_lpm(ctx, 0x1c, /* d */0x14, /* i */0x0) || ctx->breakpointActivated) break;	// lpm {d=10100, i=0} HEX:0x9144
case 0x1d:
	if(AVR_sbrc(ctx, 0x1d, /* b */0x3, /* r */0xb) || ctx->breakpointActivated) break;	// sbrc {b=011, r=01011} HEX:0xfcb3
case 0x1e:
	if(AVR_rjmp(ctx, 0x1e, /* k */0x8) || ctx->breakpointActivated) break;	// rjmp {k=000000001000} HEX:0xc008
case 0x1f:
	if(AVR_movw(ctx, 0x1f, /* d */0x1, /* r */0xd) || ctx->breakpointActivated) break;	// movw {d=0001, r=1101} HEX:0x11d
case 0x20:
	if(AVR_movw(ctx, 0x20, /* d */0x2, /* r */0xe) || ctx->breakpointActivated) break;	// movw {d=0010, r=1110} HEX:0x12e
case 0x21:
	if(AVR_sbr(ctx, 0x21, /* K */0x2, /* d */0x1) || ctx->breakpointActivated) break;	// sbr {K=00000010, d=0001} HEX:0x6012
case 0x22:
	if(AVR_ldi(ctx, 0x22, /* K */0x0, /* d */0xf) || ctx->breakpointActivated) break;	// ldi {K=00000000, d=1111} HEX:0xe0f0
case 0x23:
	if(AVR_mov(ctx, 0x23, /* d */0x1e, /* r */0x18) || ctx->breakpointActivated) break;	// mov {d=11110, r=11000} HEX:0x2fe8
case 0x24:
	if(AVR_nop(ctx, 0x24) || ctx->breakpointActivated) break;	// nop {} HEX:0x0
case 0x25:
	if(AVR_in(ctx, 0x25, /* A */0x16, /* d */0xc) || ctx->breakpointActivated) break;	// in {A=010110, d=01100} HEX:0xb2c6
case 0x26:
	if(AVR_ijmp(ctx, 0x26) || ctx->breakpointActivated) break;	// ijmp {} HEX:0x9409
case 0x27:
	if(AVR_rjmp(ctx, 0x27, /* k */0xffa) || ctx->breakpointActivated) break;	// rjmp {k=111111111010} HEX:0xcffa
case 0x28:
	if(AVR_ldi(ctx, 0x28, /* K */0x2, /* d */0xf) || ctx->breakpointActivated) break;	// ldi {K=00000010, d=1111} HEX:0xe0f2
case 0x29:
	if(AVR_in(ctx, 0x29, /* A */0x16, /* d */0x1e) || ctx->breakpointActivated) break;	// in {A=010110, d=11110} HEX:0xb3e6
case 0x2a:
	if(AVR_and(ctx, 0x2a, /* d */0xb, /* r */0x10) || ctx->breakpointActivated) break;	// and {d=01011, r=10000} HEX:0x22b0
case 0x2b:
	if(AVR_and(ctx, 0x2b, /* d */0xc, /* r */0x10) || ctx->breakpointActivated) break;	// and {d=01100, r=10000} HEX:0x22c0
case 0x2c:
	if(AVR_and(ctx, 0x2c, /* d */0x1e, /* r */0x10) || ctx->breakpointActivated) break;	// and {d=11110, r=10000} HEX:0x23e0
case 0x2d:
	if(AVR_add(ctx, 0x2d, /* d */0xb, /* r */0xb) || ctx->breakpointActivated) break;	// add {d=01011, r=01011} HEX:0xcbb
case 0x2e:
	if(AVR_or(ctx, 0x2e, /* d */0xb, /* r */0xa) || ctx->breakpointActivated) break;	// or {d=01011, r=01010} HEX:0x28ba
case 0x2f:
	if(AVR_mov(ctx, 0x2f, /* d */0xa, /* r */0x1e) || ctx->breakpointActivated) break;	// mov {d=01010, r=11110} HEX:0x2eae
case 0x30:
	if(AVR_swap(ctx, 0x30, /* d */0xb) || ctx->breakpointActivated) break;	// swap {d=01011} HEX:0x94b2
case 0x31:
	if(AVR_add(ctx, 0x31, /* d */0xc, /* r */0xc) || ctx->breakpointActivated) break;	// add {d=01100, r=01100} HEX:0xccc
case 0x32:
	if(AVR_or(ctx, 0x32, /* d */0x1e, /* r */0xc) || ctx->breakpointActivated) break;	// or {d=11110, r=01100} HEX:0x29ec
case 0x33:
	if(AVR_or(ctx, 0x33, /* d */0x1e, /* r */0xb) || ctx->breakpointActivated) break;	// or {d=11110, r=01011} HEX:0x29eb
case 0x34:
	if(AVR_nop(ctx, 0x34) || ctx->breakpointActivated) break;	// nop {} HEX:0x0
case 0x35:
	if(AVR_in(ctx, 0x35, /* A */0x16, /* d */0xb) || ctx->breakpointActivated) break;	// in {A=010110, d=01011} HEX:0xb2b6
case 0x36:
	if(AVR_lpm(ctx, 0x36, /* d */0x15, /* i */0x0) || ctx->breakpointActivated) break;	// lpm {d=10101, i=0} HEX:0x9154
case 0x37:
	if(AVR_cpi(ctx, 0x37, /* K */0x4, /* d */0x4) || ctx->breakpointActivated) break;	// cpi {K=00000100, d=0100} HEX:0x3044
case 0x38:
	if(AVR_breq(ctx, 0x38, /* k */0x11) || ctx->breakpointActivated) break;	// breq {k=0010001} HEX:0xf089
case 0x39:
	if(AVR_cpi(ctx, 0x39, /* K */0x4, /* d */0x5) || ctx->breakpointActivated) break;	// cpi {K=00000100, d=0101} HEX:0x3054
case 0x3a:
	if(AVR_breq(ctx, 0x3a, /* k */0x11) || ctx->breakpointActivated) break;	// breq {k=0010001} HEX:0xf089
case 0x3b:
	if(AVR_add(ctx, 0x3b, /* d */0x14, /* r */0x15) || ctx->breakpointActivated) break;	// add {d=10100, r=10101} HEX:0xf45
case 0x3c:
	if(AVR_ldi(ctx, 0x3c, /* K */0xff, /* d */0x5) || ctx->breakpointActivated) break;	// ldi {K=11111111, d=0101} HEX:0xef5f
case 0x3d:
	if(AVR_sbrs(ctx, 0x3d, /* b */0x7, /* r */0x14) || ctx->breakpointActivated) break;	// sbrs {b=111, r=10100} HEX:0xff47
case 0x3e:
	if(AVR_ldi(ctx, 0x3e, /* K */0x0, /* d */0x5) || ctx->breakpointActivated) break;	// ldi {K=00000000, d=0101} HEX:0xe050
case 0x3f:
	if(AVR_in(ctx, 0x3f, /* A */0x16, /* d */0xc) || ctx->breakpointActivated) break;	// in {A=010110, d=01100} HEX:0xb2c6
case 0x40:
	if(AVR_add(ctx, 0x40, /* d */0x1a, /* r */0x14) || ctx->breakpointActivated) break;	// add {d=11010, r=10100} HEX:0xfa4
case 0x41:
	if(AVR_adc(ctx, 0x41, /* d */0x1b, /* r */0x15) || ctx->breakpointActivated) break;	// adc {d=11011, r=10101} HEX:0x1fb5
case 0x42:
	if(AVR_adc(ctx, 0x42, /* d */0x1c, /* r */0x15) || ctx->breakpointActivated) break;	// adc {d=11100, r=10101} HEX:0x1fc5
case 0x43:
	if(AVR_adc(ctx, 0x43, /* d */0x1d, /* r */0x15) || ctx->breakpointActivated) break;	// adc {d=11101, r=10101} HEX:0x1fd5
case 0x44:
	if(AVR_nop(ctx, 0x44) || ctx->breakpointActivated) break;	// nop {} HEX:0x0
case 0x45:
	if(AVR_nop(ctx, 0x45) || ctx->breakpointActivated) break;	// nop {} HEX:0x0
case 0x46:
	if(AVR_nop(ctx, 0x46) || ctx->breakpointActivated) break;	// nop {} HEX:0x0
case 0x47:
	if(AVR_nop(ctx, 0x47) || ctx->breakpointActivated) break;	// nop {} HEX:0x0
case 0x48:
	if(AVR_nop(ctx, 0x48) || ctx->breakpointActivated) break;	// nop {} HEX:0x0
case 0x49:
	if(AVR_rjmp(ctx, 0x49, /* k */0xfc5) || ctx->breakpointActivated) break;	// rjmp {k=111111000101} HEX:0xcfc5
case 0x4a:
	if(AVR_nop(ctx, 0x4a) || ctx->breakpointActivated) break;	// nop {} HEX:0x0
case 0x4b:
	if(AVR_nop(ctx, 0x4b) || ctx->breakpointActivated) break;	// nop {} HEX:0x0
case 0x4c:
	if(AVR_nop(ctx, 0x4c) || ctx->breakpointActivated) break;	// nop {} HEX:0x0
case 0x4d:
	if(AVR_nop(ctx, 0x4d) || ctx->breakpointActivated) break;	// nop {} HEX:0x0
case 0x4e:
	if(AVR_nop(ctx, 0x4e) || ctx->breakpointActivated) break;	// nop {} HEX:0x0
case 0x4f:
	if(AVR_in(ctx, 0x4f, /* A */0x16, /* d */0xc) || ctx->breakpointActivated) break;	// in {A=010110, d=01100} HEX:0xb2c6
case 0x50:
	if(AVR_sbr(ctx, 0x50, /* K */0x1, /* d */0x1) || ctx->breakpointActivated) break;	// sbr {K=00000001, d=0001} HEX:0x6011
case 0x51:
	if(AVR_nop(ctx, 0x51) || ctx->breakpointActivated) break;	// nop {} HEX:0x0
case 0x52:
	if(AVR_nop(ctx, 0x52) || ctx->breakpointActivated) break;	// nop {} HEX:0x0
case 0x53:
	if(AVR_nop(ctx, 0x53) || ctx->breakpointActivated) break;	// nop {} HEX:0x0
case 0x54:
	if(AVR_nop(ctx, 0x54) || ctx->breakpointActivated) break;	// nop {} HEX:0x0
case 0x55:
	if(AVR_nop(ctx, 0x55) || ctx->breakpointActivated) break;	// nop {} HEX:0x0
case 0x56:
	if(AVR_nop(ctx, 0x56) || ctx->breakpointActivated) break;	// nop {} HEX:0x0
case 0x57:
	if(AVR_nop(ctx, 0x57) || ctx->breakpointActivated) break;	// nop {} HEX:0x0
case 0x58:
	if(AVR_nop(ctx, 0x58) || ctx->breakpointActivated) break;	// nop {} HEX:0x0
case 0x59:
	if(AVR_rjmp(ctx, 0x59, /* k */0xfb5) || ctx->breakpointActivated) break;	// rjmp {k=111110110101} HEX:0xcfb5
case 0x5a:
	if(AVR_sbrs(ctx, 0x5a, /* b */0x1, /* r */0xc) || ctx->breakpointActivated) break;	// sbrs {b=001, r=01100} HEX:0xfec1
case 0x5b:
	if(AVR_ldi(ctx, 0x5b, /* K */0x61, /* d */0x8) || ctx->breakpointActivated) break;	// ldi {K=01100001, d=1000} HEX:0xe681
case 0x5c:
	if(AVR_nop(ctx, 0x5c) || ctx->breakpointActivated) break;	// nop {} HEX:0x0
case 0x5d:
	if(AVR_nop(ctx, 0x5d) || ctx->breakpointActivated) break;	// nop {} HEX:0x0
case 0x5e:
	if(AVR_nop(ctx, 0x5e) || ctx->breakpointActivated) break;	// nop {} HEX:0x0
case 0x5f:
	if(AVR_nop(ctx, 0x5f) || ctx->breakpointActivated) break;	// nop {} HEX:0x0
case 0x60:
	if(AVR_rjmp(ctx, 0x60, /* k */0xfc7) || ctx->breakpointActivated) break;	// rjmp {k=111111000111} HEX:0xcfc7
case 0x61:
	if(AVR_sbrc(ctx, 0x61, /* b */0x1, /* r */0xc) || ctx->breakpointActivated) break;	// sbrc {b=001, r=01100} HEX:0xfcc1
case 0x62:
	if(AVR_ldi(ctx, 0x62, /* K */0x68, /* d */0x8) || ctx->breakpointActivated) break;	// ldi {K=01101000, d=1000} HEX:0xe688
case 0x63:
	if(AVR_nop(ctx, 0x63) || ctx->breakpointActivated) break;	// nop {} HEX:0x0
case 0x64:
	if(AVR_nop(ctx, 0x64) || ctx->breakpointActivated) break;	// nop {} HEX:0x0
case 0x65:
	if(AVR_nop(ctx, 0x65) || ctx->breakpointActivated) break;	// nop {} HEX:0x0
case 0x66:
	if(AVR_nop(ctx, 0x66) || ctx->breakpointActivated) break;	// nop {} HEX:0x0
case 0x67:
	if(AVR_rjmp(ctx, 0x67, /* k */0xfc0) || ctx->breakpointActivated) break;	// rjmp {k=111111000000} HEX:0xcfc0
case 0x68:
	if(AVR_movw(ctx, 0x68, /* d */0x3, /* r */0xd) || ctx->breakpointActivated) break;	// movw {d=0011, r=1101} HEX:0x13d
case 0x69:
	if(AVR_movw(ctx, 0x69, /* d */0x4, /* r */0xe) || ctx->breakpointActivated) break;	// movw {d=0100, r=1110} HEX:0x14e
case 0x6a:
	if(AVR_ldi(ctx, 0x6a, /* K */0x6f, /* d */0x8) || ctx->breakpointActivated) break;	// ldi {K=01101111, d=1000} HEX:0xe68f
case 0x6b:
	if(AVR_nop(ctx, 0x6b) || ctx->breakpointActivated) break;	// nop {} HEX:0x0
case 0x6c:
	if(AVR_nop(ctx, 0x6c) || ctx->breakpointActivated) break;	// nop {} HEX:0x0
case 0x6d:
	if(AVR_nop(ctx, 0x6d) || ctx->breakpointActivated) break;	// nop {} HEX:0x0
case 0x6e:
	if(AVR_rjmp(ctx, 0x6e, /* k */0xfb9) || ctx->breakpointActivated) break;	// rjmp {k=111110111001} HEX:0xcfb9
case 0x6f:
	if(AVR_ldi(ctx, 0x6f, /* K */0x80, /* d */0x3) || ctx->breakpointActivated) break;	// ldi {K=10000000, d=0011} HEX:0xe830
case 0x70:
	if(AVR_ldi(ctx, 0x70, /* K */0x76, /* d */0x9) || ctx->breakpointActivated) break;	// ldi {K=01110110, d=1001} HEX:0xe796
case 0x71:
	if(AVR_ldi(ctx, 0x71, /* K */0xca, /* d */0x8) || ctx->breakpointActivated) break;	// ldi {K=11001010, d=1000} HEX:0xec8a
case 0x72:
	if(AVR_nop(ctx, 0x72) || ctx->breakpointActivated) break;	// nop {} HEX:0x0
case 0x73:
	if(AVR_nop(ctx, 0x73) || ctx->breakpointActivated) break;	// nop {} HEX:0x0
case 0x74:
	if(AVR_nop(ctx, 0x74) || ctx->breakpointActivated) break;	// nop {} HEX:0x0
case 0x75:
	if(AVR_rjmp(ctx, 0x75, /* k */0xfb2) || ctx->breakpointActivated) break;	// rjmp {k=111110110010} HEX:0xcfb2
case 0x76:
	if(AVR_ldi(ctx, 0x76, /* K */0x7d, /* d */0x8) || ctx->breakpointActivated) break;	// ldi {K=01111101, d=1000} HEX:0xe78d
case 0x77:
	if(AVR_nop(ctx, 0x77) || ctx->breakpointActivated) break;	// nop {} HEX:0x0
case 0x78:
	if(AVR_nop(ctx, 0x78) || ctx->breakpointActivated) break;	// nop {} HEX:0x0
case 0x79:
	if(AVR_nop(ctx, 0x79) || ctx->breakpointActivated) break;	// nop {} HEX:0x0
case 0x7a:
	if(AVR_nop(ctx, 0x7a) || ctx->breakpointActivated) break;	// nop {} HEX:0x0
case 0x7b:
	if(AVR_nop(ctx, 0x7b) || ctx->breakpointActivated) break;	// nop {} HEX:0x0
case 0x7c:
	if(AVR_rjmp(ctx, 0x7c, /* k */0xfab) || ctx->breakpointActivated) break;	// rjmp {k=111110101011} HEX:0xcfab
case 0x7d:
	if(AVR_ldi(ctx, 0x7d, /* K */0x84, /* d */0x8) || ctx->breakpointActivated) break;	// ldi {K=10000100, d=1000} HEX:0xe884
case 0x7e:
	if(AVR_nop(ctx, 0x7e) || ctx->breakpointActivated) break;	// nop {} HEX:0x0
case 0x7f:
	if(AVR_nop(ctx, 0x7f) || ctx->breakpointActivated) break;	// nop {} HEX:0x0
case 0x80:
	if(AVR_nop(ctx, 0x80) || ctx->breakpointActivated) break;	// nop {} HEX:0x0
case 0x81:
	if(AVR_nop(ctx, 0x81) || ctx->breakpointActivated) break;	// nop {} HEX:0x0
case 0x82:
	if(AVR_nop(ctx, 0x82) || ctx->breakpointActivated) break;	// nop {} HEX:0x0
case 0x83:
	if(AVR_rjmp(ctx, 0x83, /* k */0xfa4) || ctx->breakpointActivated) break;	// rjmp {k=111110100100} HEX:0xcfa4
case 0x84:
	if(AVR_mov(ctx, 0x84, /* d */0x13, /* r */0x6) || ctx->breakpointActivated) break;	// mov {d=10011, r=00110} HEX:0x2d36
case 0x85:
	if(AVR_ldi(ctx, 0x85, /* K */0x8b, /* d */0x9) || ctx->breakpointActivated) break;	// ldi {K=10001011, d=1001} HEX:0xe89b
case 0x86:
	if(AVR_ldi(ctx, 0x86, /* K */0xca, /* d */0x8) || ctx->breakpointActivated) break;	// ldi {K=11001010, d=1000} HEX:0xec8a
case 0x87:
	if(AVR_nop(ctx, 0x87) || ctx->breakpointActivated) break;	// nop {} HEX:0x0
case 0x88:
	if(AVR_nop(ctx, 0x88) || ctx->breakpointActivated) break;	// nop {} HEX:0x0
case 0x89:
	if(AVR_nop(ctx, 0x89) || ctx->breakpointActivated) break;	// nop {} HEX:0x0
case 0x8a:
	if(AVR_rjmp(ctx, 0x8a, /* k */0xf9d) || ctx->breakpointActivated) break;	// rjmp {k=111110011101} HEX:0xcf9d
case 0x8b:
	if(AVR_mov(ctx, 0x8b, /* d */0x13, /* r */0x7) || ctx->breakpointActivated) break;	// mov {d=10011, r=00111} HEX:0x2d37
case 0x8c:
	if(AVR_ldi(ctx, 0x8c, /* K */0x92, /* d */0x9) || ctx->breakpointActivated) break;	// ldi {K=10010010, d=1001} HEX:0xe992
case 0x8d:
	if(AVR_ldi(ctx, 0x8d, /* K */0xca, /* d */0x8) || ctx->breakpointActivated) break;	// ldi {K=11001010, d=1000} HEX:0xec8a
case 0x8e:
	if(AVR_nop(ctx, 0x8e) || ctx->breakpointActivated) break;	// nop {} HEX:0x0
case 0x8f:
	if(AVR_nop(ctx, 0x8f) || ctx->breakpointActivated) break;	// nop {} HEX:0x0
case 0x90:
	if(AVR_nop(ctx, 0x90) || ctx->breakpointActivated) break;	// nop {} HEX:0x0
case 0x91:
	if(AVR_rjmp(ctx, 0x91, /* k */0xf96) || ctx->breakpointActivated) break;	// rjmp {k=111110010110} HEX:0xcf96
case 0x92:
	if(AVR_mov(ctx, 0x92, /* d */0x13, /* r */0x8) || ctx->breakpointActivated) break;	// mov {d=10011, r=01000} HEX:0x2d38
case 0x93:
	if(AVR_ldi(ctx, 0x93, /* K */0x99, /* d */0x9) || ctx->breakpointActivated) break;	// ldi {K=10011001, d=1001} HEX:0xe999
case 0x94:
	if(AVR_ldi(ctx, 0x94, /* K */0xca, /* d */0x8) || ctx->breakpointActivated) break;	// ldi {K=11001010, d=1000} HEX:0xec8a
case 0x95:
	if(AVR_nop(ctx, 0x95) || ctx->breakpointActivated) break;	// nop {} HEX:0x0
case 0x96:
	if(AVR_nop(ctx, 0x96) || ctx->breakpointActivated) break;	// nop {} HEX:0x0
case 0x97:
	if(AVR_nop(ctx, 0x97) || ctx->breakpointActivated) break;	// nop {} HEX:0x0
case 0x98:
	if(AVR_rjmp(ctx, 0x98, /* k */0xf8f) || ctx->breakpointActivated) break;	// rjmp {k=111110001111} HEX:0xcf8f
case 0x99:
	if(AVR_mov(ctx, 0x99, /* d */0x13, /* r */0x9) || ctx->breakpointActivated) break;	// mov {d=10011, r=01001} HEX:0x2d39
case 0x9a:
	if(AVR_ldi(ctx, 0x9a, /* K */0xa0, /* d */0x9) || ctx->breakpointActivated) break;	// ldi {K=10100000, d=1001} HEX:0xea90
case 0x9b:
	if(AVR_ldi(ctx, 0x9b, /* K */0xca, /* d */0x8) || ctx->breakpointActivated) break;	// ldi {K=11001010, d=1000} HEX:0xec8a
case 0x9c:
	if(AVR_nop(ctx, 0x9c) || ctx->breakpointActivated) break;	// nop {} HEX:0x0
case 0x9d:
	if(AVR_nop(ctx, 0x9d) || ctx->breakpointActivated) break;	// nop {} HEX:0x0
case 0x9e:
	if(AVR_nop(ctx, 0x9e) || ctx->breakpointActivated) break;	// nop {} HEX:0x0
case 0x9f:
	if(AVR_rjmp(ctx, 0x9f, /* k */0xf88) || ctx->breakpointActivated) break;	// rjmp {k=111110001000} HEX:0xcf88
case 0xa0:
	if(AVR_mov(ctx, 0xa0, /* d */0x13, /* r */0x11) || ctx->breakpointActivated) break;	// mov {d=10011, r=10001} HEX:0x2f31
case 0xa1:
	if(AVR_ldi(ctx, 0xa1, /* K */0x0, /* d */0x1) || ctx->breakpointActivated) break;	// ldi {K=00000000, d=0001} HEX:0xe010
case 0xa2:
	if(AVR_ldi(ctx, 0xa2, /* K */0xa7, /* d */0x9) || ctx->breakpointActivated) break;	// ldi {K=10100111, d=1001} HEX:0xea97
case 0xa3:
	if(AVR_ldi(ctx, 0xa3, /* K */0xca, /* d */0x8) || ctx->breakpointActivated) break;	// ldi {K=11001010, d=1000} HEX:0xec8a
case 0xa4:
	if(AVR_nop(ctx, 0xa4) || ctx->breakpointActivated) break;	// nop {} HEX:0x0
case 0xa5:
	if(AVR_nop(ctx, 0xa5) || ctx->breakpointActivated) break;	// nop {} HEX:0x0
case 0xa6:
	if(AVR_rjmp(ctx, 0xa6, /* k */0xf81) || ctx->breakpointActivated) break;	// rjmp {k=111110000001} HEX:0xcf81
case 0xa7:
	if(AVR_movw(ctx, 0xa7, /* d */0x3, /* r */0x1) || ctx->breakpointActivated) break;	// movw {d=0011, r=0001} HEX:0x131
case 0xa8:
	if(AVR_movw(ctx, 0xa8, /* d */0x4, /* r */0x2) || ctx->breakpointActivated) break;	// movw {d=0100, r=0010} HEX:0x142
case 0xa9:
	if(AVR_mov(ctx, 0xa9, /* d */0x13, /* r */0x6) || ctx->breakpointActivated) break;	// mov {d=10011, r=00110} HEX:0x2d36
case 0xaa:
	if(AVR_ldi(ctx, 0xaa, /* K */0xae, /* d */0x9) || ctx->breakpointActivated) break;	// ldi {K=10101110, d=1001} HEX:0xea9e
case 0xab:
	if(AVR_ldi(ctx, 0xab, /* K */0xca, /* d */0x8) || ctx->breakpointActivated) break;	// ldi {K=11001010, d=1000} HEX:0xec8a
case 0xac:
	if(AVR_nop(ctx, 0xac) || ctx->breakpointActivated) break;	// nop {} HEX:0x0
case 0xad:
	if(AVR_rjmp(ctx, 0xad, /* k */0xf7a) || ctx->breakpointActivated) break;	// rjmp {k=111101111010} HEX:0xcf7a
case 0xae:
	if(AVR_mov(ctx, 0xae, /* d */0x13, /* r */0x7) || ctx->breakpointActivated) break;	// mov {d=10011, r=00111} HEX:0x2d37
case 0xaf:
	if(AVR_ldi(ctx, 0xaf, /* K */0xb5, /* d */0x9) || ctx->breakpointActivated) break;	// ldi {K=10110101, d=1001} HEX:0xeb95
case 0xb0:
	if(AVR_ldi(ctx, 0xb0, /* K */0xca, /* d */0x8) || ctx->breakpointActivated) break;	// ldi {K=11001010, d=1000} HEX:0xec8a
case 0xb1:
	if(AVR_nop(ctx, 0xb1) || ctx->breakpointActivated) break;	// nop {} HEX:0x0
case 0xb2:
	if(AVR_nop(ctx, 0xb2) || ctx->breakpointActivated) break;	// nop {} HEX:0x0
case 0xb3:
	if(AVR_nop(ctx, 0xb3) || ctx->breakpointActivated) break;	// nop {} HEX:0x0
case 0xb4:
	if(AVR_rjmp(ctx, 0xb4, /* k */0xf73) || ctx->breakpointActivated) break;	// rjmp {k=111101110011} HEX:0xcf73
case 0xb5:
	if(AVR_mov(ctx, 0xb5, /* d */0x13, /* r */0x8) || ctx->breakpointActivated) break;	// mov {d=10011, r=01000} HEX:0x2d38
case 0xb6:
	if(AVR_ldi(ctx, 0xb6, /* K */0xbc, /* d */0x9) || ctx->breakpointActivated) break;	// ldi {K=10111100, d=1001} HEX:0xeb9c
case 0xb7:
	if(AVR_ldi(ctx, 0xb7, /* K */0xca, /* d */0x8) || ctx->breakpointActivated) break;	// ldi {K=11001010, d=1000} HEX:0xec8a
case 0xb8:
	if(AVR_nop(ctx, 0xb8) || ctx->breakpointActivated) break;	// nop {} HEX:0x0
case 0xb9:
	if(AVR_nop(ctx, 0xb9) || ctx->breakpointActivated) break;	// nop {} HEX:0x0
case 0xba:
	if(AVR_nop(ctx, 0xba) || ctx->breakpointActivated) break;	// nop {} HEX:0x0
case 0xbb:
	if(AVR_rjmp(ctx, 0xbb, /* k */0xf6c) || ctx->breakpointActivated) break;	// rjmp {k=111101101100} HEX:0xcf6c
case 0xbc:
	if(AVR_mov(ctx, 0xbc, /* d */0x13, /* r */0x9) || ctx->breakpointActivated) break;	// mov {d=10011, r=01001} HEX:0x2d39
case 0xbd:
	if(AVR_ldi(ctx, 0xbd, /* K */0xc3, /* d */0x9) || ctx->breakpointActivated) break;	// ldi {K=11000011, d=1001} HEX:0xec93
case 0xbe:
	if(AVR_ldi(ctx, 0xbe, /* K */0xca, /* d */0x8) || ctx->breakpointActivated) break;	// ldi {K=11001010, d=1000} HEX:0xec8a
case 0xbf:
	if(AVR_nop(ctx, 0xbf) || ctx->breakpointActivated) break;	// nop {} HEX:0x0
case 0xc0:
	if(AVR_nop(ctx, 0xc0) || ctx->breakpointActivated) break;	// nop {} HEX:0x0
case 0xc1:
	if(AVR_nop(ctx, 0xc1) || ctx->breakpointActivated) break;	// nop {} HEX:0x0
case 0xc2:
	if(AVR_rjmp(ctx, 0xc2, /* k */0xf65) || ctx->breakpointActivated) break;	// rjmp {k=111101100101} HEX:0xcf65
case 0xc3:
	if(AVR_out(ctx, 0xc3, /* A */0x18, /* r */0x0) || ctx->breakpointActivated) break;	// out {A=011000, r=00000} HEX:0xba08
case 0xc4:
	if(AVR_out(ctx, 0xc4, /* A */0x17, /* r */0x0) || ctx->breakpointActivated) break;	// out {A=010111, r=00000} HEX:0xba07
case 0xc5:
	if(AVR_ldi(ctx, 0xc5, /* K */0x5a, /* d */0x8) || ctx->breakpointActivated) break;	// ldi {K=01011010, d=1000} HEX:0xe58a
case 0xc6:
	if(AVR_nop(ctx, 0xc6) || ctx->breakpointActivated) break;	// nop {} HEX:0x0
case 0xc7:
	if(AVR_nop(ctx, 0xc7) || ctx->breakpointActivated) break;	// nop {} HEX:0x0
case 0xc8:
	if(AVR_nop(ctx, 0xc8) || ctx->breakpointActivated) break;	// nop {} HEX:0x0
case 0xc9:
	if(AVR_rjmp(ctx, 0xc9, /* k */0xf5e) || ctx->breakpointActivated) break;	// rjmp {k=111101011110} HEX:0xcf5e
case 0xca:
	if(AVR_ldi(ctx, 0xca, /* K */0x9, /* d */0x2) || ctx->breakpointActivated) break;	// ldi {K=00001001, d=0010} HEX:0xe029
case 0xcb:
	if(AVR_ldi(ctx, 0xcb, /* K */0x0, /* d */0x6) || ctx->breakpointActivated) break;	// ldi {K=00000000, d=0110} HEX:0xe060
case 0xcc:
	if(AVR_ldi(ctx, 0xcc, /* K */0xd8, /* d */0x8) || ctx->breakpointActivated) break;	// ldi {K=11011000, d=1000} HEX:0xed88
case 0xcd:
	if(AVR_ldi(ctx, 0xcd, /* K */0x2, /* d */0xe) || ctx->breakpointActivated) break;	// ldi {K=00000010, d=1110} HEX:0xe0e2
case 0xce:
	if(AVR_out(ctx, 0xce, /* A */0x18, /* r */0x1e) || ctx->breakpointActivated) break;	// out {A=011000, r=11110} HEX:0xbbe8
case 0xcf:
	if(AVR_out(ctx, 0xcf, /* A */0x17, /* r */0x1e) || ctx->breakpointActivated) break;	// out {A=010111, r=11110} HEX:0xbbe7
case 0xd0:
	if(AVR_rjmp(ctx, 0xd0, /* k */0xf57) || ctx->breakpointActivated) break;	// rjmp {k=111101010111} HEX:0xcf57
case 0xd1:
	if(AVR_ldi(ctx, 0xd1, /* K */0x2, /* d */0x6) || ctx->breakpointActivated) break;	// ldi {K=00000010, d=0110} HEX:0xe062
case 0xd2:
	if(AVR_sbrc(ctx, 0xd2, /* b */0x0, /* r */0x13) || ctx->breakpointActivated) break;	// sbrc {b=000, r=10011} HEX:0xfd30
case 0xd3:
	if(AVR_ldi(ctx, 0xd3, /* K */0x0, /* d */0x6) || ctx->breakpointActivated) break;	// ldi {K=00000000, d=0110} HEX:0xe060
case 0xd4:
	if(AVR_lsr(ctx, 0xd4, /* d */0x13) || ctx->breakpointActivated) break;	// lsr {d=10011} HEX:0x9536
case 0xd5:
	if(AVR_ldi(ctx, 0xd5, /* K */0xd8, /* d */0x8) || ctx->breakpointActivated) break;	// ldi {K=11011000, d=1000} HEX:0xed88
case 0xd6:
	if(AVR_nop(ctx, 0xd6) || ctx->breakpointActivated) break;	// nop {} HEX:0x0
case 0xd7:
	if(AVR_rjmp(ctx, 0xd7, /* k */0xf50) || ctx->breakpointActivated) break;	// rjmp {k=111101010000} HEX:0xcf50
case 0xd8:
	if(AVR_out(ctx, 0xd8, /* A */0x18, /* r */0x16) || ctx->breakpointActivated) break;	// out {A=011000, r=10110} HEX:0xbb68
case 0xd9:
	if(AVR_nop(ctx, 0xd9) || ctx->breakpointActivated) break;	// nop {} HEX:0x0
case 0xda:
	if(AVR_dec(ctx, 0xda, /* d */0x12) || ctx->breakpointActivated) break;	// dec {d=10010} HEX:0x952a
case 0xdb:
	if(AVR_brne(ctx, 0xdb, /* k */0x3) || ctx->breakpointActivated) break;	// brne {k=0000011} HEX:0xf419
case 0xdc:
	if(AVR_ldi(ctx, 0xdc, /* K */0xe1, /* d */0x8) || ctx->breakpointActivated) break;	// ldi {K=11100001, d=1000} HEX:0xee81
case 0xdd:
	if(AVR_nop(ctx, 0xdd) || ctx->breakpointActivated) break;	// nop {} HEX:0x0
case 0xde:
	if(AVR_rjmp(ctx, 0xde, /* k */0xf49) || ctx->breakpointActivated) break;	// rjmp {k=111101001001} HEX:0xcf49
case 0xdf:
	if(AVR_ldi(ctx, 0xdf, /* K */0xd1, /* d */0x8) || ctx->breakpointActivated) break;	// ldi {K=11010001, d=1000} HEX:0xed81
case 0xe0:
	if(AVR_rjmp(ctx, 0xe0, /* k */0xf47) || ctx->breakpointActivated) break;	// rjmp {k=111101000111} HEX:0xcf47
case 0xe1:
	if(AVR_ldi(ctx, 0xe1, /* K */0xe8, /* d */0x8) || ctx->breakpointActivated) break;	// ldi {K=11101000, d=1000} HEX:0xee88
case 0xe2:
	if(AVR_ldi(ctx, 0xe2, /* K */0x2, /* d */0x6) || ctx->breakpointActivated) break;	// ldi {K=00000010, d=0110} HEX:0xe062
case 0xe3:
	if(AVR_nop(ctx, 0xe3) || ctx->breakpointActivated) break;	// nop {} HEX:0x0
case 0xe4:
	if(AVR_nop(ctx, 0xe4) || ctx->breakpointActivated) break;	// nop {} HEX:0x0
case 0xe5:
	if(AVR_nop(ctx, 0xe5) || ctx->breakpointActivated) break;	// nop {} HEX:0x0
case 0xe6:
	if(AVR_nop(ctx, 0xe6) || ctx->breakpointActivated) break;	// nop {} HEX:0x0
case 0xe7:
	if(AVR_rjmp(ctx, 0xe7, /* k */0xf40) || ctx->breakpointActivated) break;	// rjmp {k=111101000000} HEX:0xcf40
case 0xe8:
	if(AVR_out(ctx, 0xe8, /* A */0x18, /* r */0x16) || ctx->breakpointActivated) break;	// out {A=011000, r=10110} HEX:0xbb68
case 0xe9:
	if(AVR_mov(ctx, 0xe9, /* d */0x18, /* r */0x19) || ctx->breakpointActivated) break;	// mov {d=11000, r=11001} HEX:0x2f89
case 0xea:
	if(AVR_nop(ctx, 0xea) || ctx->breakpointActivated) break;	// nop {} HEX:0x0
case 0xeb:
	if(AVR_nop(ctx, 0xeb) || ctx->breakpointActivated) break;	// nop {} HEX:0x0
case 0xec:
	if(AVR_nop(ctx, 0xec) || ctx->breakpointActivated) break;	// nop {} HEX:0x0
case 0xed:
	if(AVR_nop(ctx, 0xed) || ctx->breakpointActivated) break;	// nop {} HEX:0x0
case 0xee:
	if(AVR_rjmp(ctx, 0xee, /* k */0xf39) || ctx->breakpointActivated) break;	// rjmp {k=111100111001} HEX:0xcf39
		default:
			AVR_error_nosp(ctx, sp);
			break;
	}
}
