#include <AVR_simulator.h>
void executeFromAddress(AVR_simulator_t * ctx, uint32_t sp)
{
	switch(sp)
	{
case 0x0:
	if(AVR_ldi(ctx, 0x0, /* K */0x18, /* d */0xf) || ctx->breakpointActivated) break;	// ldi {K=00011000, d=1111} HEX:0xe1f8
case 0x1:
	if(AVR_mov(ctx, 0x1, /* d */0xd, /* r */0x1f) || ctx->breakpointActivated) break;	// mov {d=01101, r=11111} HEX:0x2edf
case 0x2:
	if(AVR_ldi(ctx, 0x2, /* K */0x2, /* d */0xf) || ctx->breakpointActivated) break;	// ldi {K=00000010, d=1111} HEX:0xe0f2
case 0x3:
	if(AVR_mov(ctx, 0x3, /* d */0xe, /* r */0x1f) || ctx->breakpointActivated) break;	// mov {d=01110, r=11111} HEX:0x2eef
case 0x4:
	if(AVR_ldi(ctx, 0x4, /* K */0x1a, /* d */0xf) || ctx->breakpointActivated) break;	// ldi {K=00011010, d=1111} HEX:0xe1fa
case 0x5:
	if(AVR_mov(ctx, 0x5, /* d */0x1, /* r */0x1f) || ctx->breakpointActivated) break;	// mov {d=00001, r=11111} HEX:0x2e1f
case 0x6:
	if(AVR_ldi(ctx, 0x6, /* K */0x0, /* d */0xf) || ctx->breakpointActivated) break;	// ldi {K=00000000, d=1111} HEX:0xe0f0
case 0x7:
	if(AVR_mov(ctx, 0x7, /* d */0x0, /* r */0x1f) || ctx->breakpointActivated) break;	// mov {d=00000, r=11111} HEX:0x2e0f
case 0x8:
	if(AVR_mov(ctx, 0x8, /* d */0x1a, /* r */0x1f) || ctx->breakpointActivated) break;	// mov {d=11010, r=11111} HEX:0x2faf
case 0x9:
	if(AVR_mov(ctx, 0x9, /* d */0x1b, /* r */0x1f) || ctx->breakpointActivated) break;	// mov {d=11011, r=11111} HEX:0x2fbf
case 0xa:
	if(AVR_mov(ctx, 0xa, /* d */0x1c, /* r */0x1f) || ctx->breakpointActivated) break;	// mov {d=11100, r=11111} HEX:0x2fcf
case 0xb:
	if(AVR_mov(ctx, 0xb, /* d */0x1d, /* r */0x1f) || ctx->breakpointActivated) break;	// mov {d=11101, r=11111} HEX:0x2fdf
case 0xc:
	if(AVR_mov(ctx, 0xc, /* d */0x2, /* r */0x1f) || ctx->breakpointActivated) break;	// mov {d=00010, r=11111} HEX:0x2e2f
case 0xd:
	if(AVR_mov(ctx, 0xd, /* d */0x3, /* r */0x1f) || ctx->breakpointActivated) break;	// mov {d=00011, r=11111} HEX:0x2e3f
case 0xe:
	if(AVR_mov(ctx, 0xe, /* d */0x4, /* r */0x1f) || ctx->breakpointActivated) break;	// mov {d=00100, r=11111} HEX:0x2e4f
case 0xf:
	if(AVR_mov(ctx, 0xf, /* d */0x5, /* r */0x1f) || ctx->breakpointActivated) break;	// mov {d=00101, r=11111} HEX:0x2e5f
case 0x10:
	if(AVR_ldi(ctx, 0x10, /* K */0x0, /* d */0x8) || ctx->breakpointActivated) break;	// ldi {K=00000000, d=1000} HEX:0xe080
case 0x11:
	if(AVR_ldi(ctx, 0x11, /* K */0x0, /* d */0x1) || ctx->breakpointActivated) break;	// ldi {K=00000000, d=0001} HEX:0xe010
case 0x12:
	if(AVR_ldi(ctx, 0x12, /* K */0x5, /* d */0x0) || ctx->breakpointActivated) break;	// ldi {K=00000101, d=0000} HEX:0xe005
case 0x13:
	if(AVR_in(ctx, 0x13, /* A */0x16, /* d */0xa) || ctx->breakpointActivated) break;	// in {A=010110, d=01010} HEX:0xb2a6
case 0x14:
	if(AVR_and(ctx, 0x14, /* d */0xa, /* r */0x10) || ctx->breakpointActivated) break;	// and {d=01010, r=10000} HEX:0x22a0
case 0x15:
	if(AVR_in(ctx, 0x15, /* A */0x16, /* d */0xb) || ctx->breakpointActivated) break;	// in {A=010110, d=01011} HEX:0xb2b6
case 0x16:
	if(AVR_in(ctx, 0x16, /* A */0x16, /* d */0xc) || ctx->breakpointActivated) break;	// in {A=010110, d=01100} HEX:0xb2c6
case 0x17:
	if(AVR_ldi(ctx, 0x17, /* K */0x2, /* d */0xf) || ctx->breakpointActivated) break;	// ldi {K=00000010, d=1111} HEX:0xe0f2
case 0x18:
	if(AVR_out(ctx, 0x18, /* A */0x18, /* r */0x1) || ctx->breakpointActivated) break;	// out {A=011000, r=00001} HEX:0xba18
case 0x19:
	if(AVR_in(ctx, 0x19, /* A */0x16, /* d */0x1e) || ctx->breakpointActivated) break;	// in {A=010110, d=11110} HEX:0xb3e6
case 0x1a:
	if(AVR_out(ctx, 0x1a, /* A */0x18, /* r */0x1) || ctx->breakpointActivated) break;	// out {A=011000, r=00001} HEX:0xba18
case 0x1b:
	if(AVR_and(ctx, 0x1b, /* d */0xb, /* r */0x10) || ctx->breakpointActivated) break;	// and {d=01011, r=10000} HEX:0x22b0
case 0x1c:
	if(AVR_and(ctx, 0x1c, /* d */0xc, /* r */0x10) || ctx->breakpointActivated) break;	// and {d=01100, r=10000} HEX:0x22c0
case 0x1d:
	if(AVR_and(ctx, 0x1d, /* d */0x1e, /* r */0x10) || ctx->breakpointActivated) break;	// and {d=11110, r=10000} HEX:0x23e0
case 0x1e:
	if(AVR_add(ctx, 0x1e, /* d */0xb, /* r */0xb) || ctx->breakpointActivated) break;	// add {d=01011, r=01011} HEX:0xcbb
case 0x1f:
	if(AVR_or(ctx, 0x1f, /* d */0xb, /* r */0xa) || ctx->breakpointActivated) break;	// or {d=01011, r=01010} HEX:0x28ba
case 0x20:
	if(AVR_mov(ctx, 0x20, /* d */0xa, /* r */0x1e) || ctx->breakpointActivated) break;	// mov {d=01010, r=11110} HEX:0x2eae
case 0x21:
	if(AVR_swap(ctx, 0x21, /* d */0xb) || ctx->breakpointActivated) break;	// swap {d=01011} HEX:0x94b2
case 0x22:
	if(AVR_add(ctx, 0x22, /* d */0xc, /* r */0xc) || ctx->breakpointActivated) break;	// add {d=01100, r=01100} HEX:0xccc
case 0x23:
	if(AVR_or(ctx, 0x23, /* d */0x1e, /* r */0xb) || ctx->breakpointActivated) break;	// or {d=11110, r=01011} HEX:0x29eb
case 0x24:
	if(AVR_ldi(ctx, 0x24, /* K */0x1a, /* d */0x6) || ctx->breakpointActivated) break;	// ldi {K=00011010, d=0110} HEX:0xe16a
case 0x25:
	if(AVR_in(ctx, 0x25, /* A */0x16, /* d */0xb) || ctx->breakpointActivated) break;	// in {A=010110, d=01011} HEX:0xb2b6
case 0x26:
	if(AVR_or(ctx, 0x26, /* d */0x1e, /* r */0xc) || ctx->breakpointActivated) break;	// or {d=11110, r=01100} HEX:0x29ec
case 0x27:
	if(AVR_lpm(ctx, 0x27, /* d */0x14, /* i */0x0) || ctx->breakpointActivated) break;	// lpm {d=10100, i=0} HEX:0x9144
case 0x28:
	if(AVR_sbrs(ctx, 0x28, /* b */0x3, /* r */0xb) || ctx->breakpointActivated) break;	// sbrs {b=011, r=01011} HEX:0xfeb3
case 0x29:
	if(AVR_rjmp(ctx, 0x29, /* k */0x7) || ctx->breakpointActivated) break;	// rjmp {k=000000000111} HEX:0xc007
case 0x2a:
	if(AVR_movw(ctx, 0x2a, /* d */0x1, /* r */0xd) || ctx->breakpointActivated) break;	// movw {d=0001, r=1101} HEX:0x11d
case 0x2b:
	if(AVR_movw(ctx, 0x2b, /* d */0x2, /* r */0xe) || ctx->breakpointActivated) break;	// movw {d=0010, r=1110} HEX:0x12e
case 0x2c:
	if(AVR_sbr(ctx, 0x2c, /* K */0x2, /* d */0x1) || ctx->breakpointActivated) break;	// sbr {K=00000010, d=0001} HEX:0x6012
case 0x2d:
	if(AVR_nop(ctx, 0x2d) || ctx->breakpointActivated) break;	// nop {} HEX:0x0
case 0x2e:
	if(AVR_mov(ctx, 0x2e, /* d */0x1e, /* r */0x18) || ctx->breakpointActivated) break;	// mov {d=11110, r=11000} HEX:0x2fe8
case 0x2f:
	if(AVR_in(ctx, 0x2f, /* A */0x16, /* d */0xc) || ctx->breakpointActivated) break;	// in {A=010110, d=01100} HEX:0xb2c6
case 0x30:
	if(AVR_ijmp(ctx, 0x30) || ctx->breakpointActivated) break;	// ijmp {} HEX:0x9409
case 0x31:
	if(AVR_rjmp(ctx, 0x31, /* k */0xffb) || ctx->breakpointActivated) break;	// rjmp {k=111111111011} HEX:0xcffb
case 0x32:
	if(AVR_nop(ctx, 0x32) || ctx->breakpointActivated) break;	// nop {} HEX:0x0
case 0x33:
	if(AVR_nop(ctx, 0x33) || ctx->breakpointActivated) break;	// nop {} HEX:0x0
case 0x34:
	if(AVR_nop(ctx, 0x34) || ctx->breakpointActivated) break;	// nop {} HEX:0x0
case 0x35:
	if(AVR_in(ctx, 0x35, /* A */0x16, /* d */0x1e) || ctx->breakpointActivated) break;	// in {A=010110, d=11110} HEX:0xb3e6
case 0x36:
	if(AVR_and(ctx, 0x36, /* d */0xb, /* r */0x10) || ctx->breakpointActivated) break;	// and {d=01011, r=10000} HEX:0x22b0
case 0x37:
	if(AVR_and(ctx, 0x37, /* d */0xc, /* r */0x10) || ctx->breakpointActivated) break;	// and {d=01100, r=10000} HEX:0x22c0
case 0x38:
	if(AVR_and(ctx, 0x38, /* d */0x1e, /* r */0x10) || ctx->breakpointActivated) break;	// and {d=11110, r=10000} HEX:0x23e0
case 0x39:
	if(AVR_add(ctx, 0x39, /* d */0xb, /* r */0xb) || ctx->breakpointActivated) break;	// add {d=01011, r=01011} HEX:0xcbb
case 0x3a:
	if(AVR_or(ctx, 0x3a, /* d */0xb, /* r */0xa) || ctx->breakpointActivated) break;	// or {d=01011, r=01010} HEX:0x28ba
case 0x3b:
	if(AVR_mov(ctx, 0x3b, /* d */0xa, /* r */0x1e) || ctx->breakpointActivated) break;	// mov {d=01010, r=11110} HEX:0x2eae
case 0x3c:
	if(AVR_swap(ctx, 0x3c, /* d */0xb) || ctx->breakpointActivated) break;	// swap {d=01011} HEX:0x94b2
case 0x3d:
	if(AVR_add(ctx, 0x3d, /* d */0xc, /* r */0xc) || ctx->breakpointActivated) break;	// add {d=01100, r=01100} HEX:0xccc
case 0x3e:
	if(AVR_or(ctx, 0x3e, /* d */0x1e, /* r */0xc) || ctx->breakpointActivated) break;	// or {d=11110, r=01100} HEX:0x29ec
case 0x3f:
	if(AVR_or(ctx, 0x3f, /* d */0x1e, /* r */0xb) || ctx->breakpointActivated) break;	// or {d=11110, r=01011} HEX:0x29eb
case 0x40:
	if(AVR_out(ctx, 0x40, /* A */0x18, /* r */0x16) || ctx->breakpointActivated) break;	// out {A=011000, r=10110} HEX:0xbb68
case 0x41:
	if(AVR_in(ctx, 0x41, /* A */0x16, /* d */0xb) || ctx->breakpointActivated) break;	// in {A=010110, d=01011} HEX:0xb2b6
case 0x42:
	if(AVR_lpm(ctx, 0x42, /* d */0x15, /* i */0x0) || ctx->breakpointActivated) break;	// lpm {d=10101, i=0} HEX:0x9154
case 0x43:
	if(AVR_cpi(ctx, 0x43, /* K */0x4, /* d */0x4) || ctx->breakpointActivated) break;	// cpi {K=00000100, d=0100} HEX:0x3044
case 0x44:
	if(AVR_breq(ctx, 0x44, /* k */0x11) || ctx->breakpointActivated) break;	// breq {k=0010001} HEX:0xf089
case 0x45:
	if(AVR_cpi(ctx, 0x45, /* K */0x4, /* d */0x5) || ctx->breakpointActivated) break;	// cpi {K=00000100, d=0101} HEX:0x3054
case 0x46:
	if(AVR_breq(ctx, 0x46, /* k */0x11) || ctx->breakpointActivated) break;	// breq {k=0010001} HEX:0xf089
case 0x47:
	if(AVR_add(ctx, 0x47, /* d */0x14, /* r */0x15) || ctx->breakpointActivated) break;	// add {d=10100, r=10101} HEX:0xf45
case 0x48:
	if(AVR_ldi(ctx, 0x48, /* K */0xff, /* d */0x5) || ctx->breakpointActivated) break;	// ldi {K=11111111, d=0101} HEX:0xef5f
case 0x49:
	if(AVR_sbrs(ctx, 0x49, /* b */0x7, /* r */0x14) || ctx->breakpointActivated) break;	// sbrs {b=111, r=10100} HEX:0xff47
case 0x4a:
	if(AVR_ldi(ctx, 0x4a, /* K */0x0, /* d */0x5) || ctx->breakpointActivated) break;	// ldi {K=00000000, d=0101} HEX:0xe050
case 0x4b:
	if(AVR_in(ctx, 0x4b, /* A */0x16, /* d */0xc) || ctx->breakpointActivated) break;	// in {A=010110, d=01100} HEX:0xb2c6
case 0x4c:
	if(AVR_nop(ctx, 0x4c) || ctx->breakpointActivated) break;	// nop {} HEX:0x0
case 0x4d:
	if(AVR_add(ctx, 0x4d, /* d */0x1a, /* r */0x14) || ctx->breakpointActivated) break;	// add {d=11010, r=10100} HEX:0xfa4
case 0x4e:
	if(AVR_adc(ctx, 0x4e, /* d */0x1b, /* r */0x15) || ctx->breakpointActivated) break;	// adc {d=11011, r=10101} HEX:0x1fb5
case 0x4f:
	if(AVR_adc(ctx, 0x4f, /* d */0x1c, /* r */0x15) || ctx->breakpointActivated) break;	// adc {d=11100, r=10101} HEX:0x1fc5
case 0x50:
	if(AVR_adc(ctx, 0x50, /* d */0x1d, /* r */0x15) || ctx->breakpointActivated) break;	// adc {d=11101, r=10101} HEX:0x1fd5
case 0x51:
	if(AVR_nop(ctx, 0x51) || ctx->breakpointActivated) break;	// nop {} HEX:0x0
case 0x52:
	if(AVR_nop(ctx, 0x52) || ctx->breakpointActivated) break;	// nop {} HEX:0x0
case 0x53:
	if(AVR_nop(ctx, 0x53) || ctx->breakpointActivated) break;	// nop {} HEX:0x0
case 0x54:
	if(AVR_nop(ctx, 0x54) || ctx->breakpointActivated) break;	// nop {} HEX:0x0
case 0x55:
	if(AVR_rjmp(ctx, 0x55, /* k */0xfc3) || ctx->breakpointActivated) break;	// rjmp {k=111111000011} HEX:0xcfc3
case 0x56:
	if(AVR_nop(ctx, 0x56) || ctx->breakpointActivated) break;	// nop {} HEX:0x0
case 0x57:
	if(AVR_nop(ctx, 0x57) || ctx->breakpointActivated) break;	// nop {} HEX:0x0
case 0x58:
	if(AVR_nop(ctx, 0x58) || ctx->breakpointActivated) break;	// nop {} HEX:0x0
case 0x59:
	if(AVR_nop(ctx, 0x59) || ctx->breakpointActivated) break;	// nop {} HEX:0x0
case 0x5a:
	if(AVR_nop(ctx, 0x5a) || ctx->breakpointActivated) break;	// nop {} HEX:0x0
case 0x5b:
	if(AVR_in(ctx, 0x5b, /* A */0x16, /* d */0xc) || ctx->breakpointActivated) break;	// in {A=010110, d=01100} HEX:0xb2c6
case 0x5c:
	if(AVR_nop(ctx, 0x5c) || ctx->breakpointActivated) break;	// nop {} HEX:0x0
case 0x5d:
	if(AVR_sbr(ctx, 0x5d, /* K */0x1, /* d */0x1) || ctx->breakpointActivated) break;	// sbr {K=00000001, d=0001} HEX:0x6011
case 0x5e:
	if(AVR_nop(ctx, 0x5e) || ctx->breakpointActivated) break;	// nop {} HEX:0x0
case 0x5f:
	if(AVR_nop(ctx, 0x5f) || ctx->breakpointActivated) break;	// nop {} HEX:0x0
case 0x60:
	if(AVR_nop(ctx, 0x60) || ctx->breakpointActivated) break;	// nop {} HEX:0x0
case 0x61:
	if(AVR_nop(ctx, 0x61) || ctx->breakpointActivated) break;	// nop {} HEX:0x0
case 0x62:
	if(AVR_nop(ctx, 0x62) || ctx->breakpointActivated) break;	// nop {} HEX:0x0
case 0x63:
	if(AVR_nop(ctx, 0x63) || ctx->breakpointActivated) break;	// nop {} HEX:0x0
case 0x64:
	if(AVR_nop(ctx, 0x64) || ctx->breakpointActivated) break;	// nop {} HEX:0x0
case 0x65:
	if(AVR_rjmp(ctx, 0x65, /* k */0xfb3) || ctx->breakpointActivated) break;	// rjmp {k=111110110011} HEX:0xcfb3
case 0x66:
	if(AVR_nop(ctx, 0x66) || ctx->breakpointActivated) break;	// nop {} HEX:0x0
case 0x67:
	if(AVR_nop(ctx, 0x67) || ctx->breakpointActivated) break;	// nop {} HEX:0x0
case 0x68:
	if(AVR_nop(ctx, 0x68) || ctx->breakpointActivated) break;	// nop {} HEX:0x0
case 0x69:
	if(AVR_nop(ctx, 0x69) || ctx->breakpointActivated) break;	// nop {} HEX:0x0
case 0x6a:
	if(AVR_nop(ctx, 0x6a) || ctx->breakpointActivated) break;	// nop {} HEX:0x0
case 0x6b:
	if(AVR_nop(ctx, 0x6b) || ctx->breakpointActivated) break;	// nop {} HEX:0x0
case 0x6c:
	if(AVR_nop(ctx, 0x6c) || ctx->breakpointActivated) break;	// nop {} HEX:0x0
case 0x6d:
	if(AVR_nop(ctx, 0x6d) || ctx->breakpointActivated) break;	// nop {} HEX:0x0
case 0x6e:
	if(AVR_nop(ctx, 0x6e) || ctx->breakpointActivated) break;	// nop {} HEX:0x0
case 0x6f:
	if(AVR_nop(ctx, 0x6f) || ctx->breakpointActivated) break;	// nop {} HEX:0x0
case 0x70:
	if(AVR_nop(ctx, 0x70) || ctx->breakpointActivated) break;	// nop {} HEX:0x0
case 0x71:
	if(AVR_nop(ctx, 0x71) || ctx->breakpointActivated) break;	// nop {} HEX:0x0
case 0x72:
	if(AVR_nop(ctx, 0x72) || ctx->breakpointActivated) break;	// nop {} HEX:0x0
case 0x73:
	if(AVR_nop(ctx, 0x73) || ctx->breakpointActivated) break;	// nop {} HEX:0x0
case 0x74:
	if(AVR_nop(ctx, 0x74) || ctx->breakpointActivated) break;	// nop {} HEX:0x0
case 0x75:
	if(AVR_nop(ctx, 0x75) || ctx->breakpointActivated) break;	// nop {} HEX:0x0
case 0x76:
	if(AVR_nop(ctx, 0x76) || ctx->breakpointActivated) break;	// nop {} HEX:0x0
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
	if(AVR_nop(ctx, 0x7c) || ctx->breakpointActivated) break;	// nop {} HEX:0x0
case 0x7d:
	if(AVR_nop(ctx, 0x7d) || ctx->breakpointActivated) break;	// nop {} HEX:0x0
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
	if(AVR_nop(ctx, 0x83) || ctx->breakpointActivated) break;	// nop {} HEX:0x0
case 0x84:
	if(AVR_nop(ctx, 0x84) || ctx->breakpointActivated) break;	// nop {} HEX:0x0
case 0x85:
	if(AVR_nop(ctx, 0x85) || ctx->breakpointActivated) break;	// nop {} HEX:0x0
case 0x86:
	if(AVR_nop(ctx, 0x86) || ctx->breakpointActivated) break;	// nop {} HEX:0x0
case 0x87:
	if(AVR_nop(ctx, 0x87) || ctx->breakpointActivated) break;	// nop {} HEX:0x0
case 0x88:
	if(AVR_nop(ctx, 0x88) || ctx->breakpointActivated) break;	// nop {} HEX:0x0
case 0x89:
	if(AVR_nop(ctx, 0x89) || ctx->breakpointActivated) break;	// nop {} HEX:0x0
case 0x8a:
	if(AVR_nop(ctx, 0x8a) || ctx->breakpointActivated) break;	// nop {} HEX:0x0
case 0x8b:
	if(AVR_nop(ctx, 0x8b) || ctx->breakpointActivated) break;	// nop {} HEX:0x0
case 0x8c:
	if(AVR_nop(ctx, 0x8c) || ctx->breakpointActivated) break;	// nop {} HEX:0x0
case 0x8d:
	if(AVR_nop(ctx, 0x8d) || ctx->breakpointActivated) break;	// nop {} HEX:0x0
case 0x8e:
	if(AVR_nop(ctx, 0x8e) || ctx->breakpointActivated) break;	// nop {} HEX:0x0
case 0x8f:
	if(AVR_nop(ctx, 0x8f) || ctx->breakpointActivated) break;	// nop {} HEX:0x0
case 0x90:
	if(AVR_nop(ctx, 0x90) || ctx->breakpointActivated) break;	// nop {} HEX:0x0
case 0x91:
	if(AVR_nop(ctx, 0x91) || ctx->breakpointActivated) break;	// nop {} HEX:0x0
case 0x92:
	if(AVR_nop(ctx, 0x92) || ctx->breakpointActivated) break;	// nop {} HEX:0x0
case 0x93:
	if(AVR_nop(ctx, 0x93) || ctx->breakpointActivated) break;	// nop {} HEX:0x0
case 0x94:
	if(AVR_nop(ctx, 0x94) || ctx->breakpointActivated) break;	// nop {} HEX:0x0
case 0x95:
	if(AVR_nop(ctx, 0x95) || ctx->breakpointActivated) break;	// nop {} HEX:0x0
case 0x96:
	if(AVR_nop(ctx, 0x96) || ctx->breakpointActivated) break;	// nop {} HEX:0x0
case 0x97:
	if(AVR_nop(ctx, 0x97) || ctx->breakpointActivated) break;	// nop {} HEX:0x0
case 0x98:
	if(AVR_nop(ctx, 0x98) || ctx->breakpointActivated) break;	// nop {} HEX:0x0
case 0x99:
	if(AVR_nop(ctx, 0x99) || ctx->breakpointActivated) break;	// nop {} HEX:0x0
case 0x9a:
	if(AVR_nop(ctx, 0x9a) || ctx->breakpointActivated) break;	// nop {} HEX:0x0
case 0x9b:
	if(AVR_nop(ctx, 0x9b) || ctx->breakpointActivated) break;	// nop {} HEX:0x0
case 0x9c:
	if(AVR_nop(ctx, 0x9c) || ctx->breakpointActivated) break;	// nop {} HEX:0x0
case 0x9d:
	if(AVR_nop(ctx, 0x9d) || ctx->breakpointActivated) break;	// nop {} HEX:0x0
case 0x9e:
	if(AVR_nop(ctx, 0x9e) || ctx->breakpointActivated) break;	// nop {} HEX:0x0
case 0x9f:
	if(AVR_nop(ctx, 0x9f) || ctx->breakpointActivated) break;	// nop {} HEX:0x0
case 0xa0:
	if(AVR_nop(ctx, 0xa0) || ctx->breakpointActivated) break;	// nop {} HEX:0x0
case 0xa1:
	if(AVR_nop(ctx, 0xa1) || ctx->breakpointActivated) break;	// nop {} HEX:0x0
case 0xa2:
	if(AVR_nop(ctx, 0xa2) || ctx->breakpointActivated) break;	// nop {} HEX:0x0
case 0xa3:
	if(AVR_nop(ctx, 0xa3) || ctx->breakpointActivated) break;	// nop {} HEX:0x0
case 0xa4:
	if(AVR_nop(ctx, 0xa4) || ctx->breakpointActivated) break;	// nop {} HEX:0x0
case 0xa5:
	if(AVR_nop(ctx, 0xa5) || ctx->breakpointActivated) break;	// nop {} HEX:0x0
case 0xa6:
	if(AVR_nop(ctx, 0xa6) || ctx->breakpointActivated) break;	// nop {} HEX:0x0
case 0xa7:
	if(AVR_nop(ctx, 0xa7) || ctx->breakpointActivated) break;	// nop {} HEX:0x0
case 0xa8:
	if(AVR_nop(ctx, 0xa8) || ctx->breakpointActivated) break;	// nop {} HEX:0x0
case 0xa9:
	if(AVR_nop(ctx, 0xa9) || ctx->breakpointActivated) break;	// nop {} HEX:0x0
case 0xaa:
	if(AVR_nop(ctx, 0xaa) || ctx->breakpointActivated) break;	// nop {} HEX:0x0
case 0xab:
	if(AVR_nop(ctx, 0xab) || ctx->breakpointActivated) break;	// nop {} HEX:0x0
case 0xac:
	if(AVR_nop(ctx, 0xac) || ctx->breakpointActivated) break;	// nop {} HEX:0x0
case 0xad:
	if(AVR_nop(ctx, 0xad) || ctx->breakpointActivated) break;	// nop {} HEX:0x0
case 0xae:
	if(AVR_nop(ctx, 0xae) || ctx->breakpointActivated) break;	// nop {} HEX:0x0
case 0xaf:
	if(AVR_nop(ctx, 0xaf) || ctx->breakpointActivated) break;	// nop {} HEX:0x0
case 0xb0:
	if(AVR_nop(ctx, 0xb0) || ctx->breakpointActivated) break;	// nop {} HEX:0x0
case 0xb1:
	if(AVR_nop(ctx, 0xb1) || ctx->breakpointActivated) break;	// nop {} HEX:0x0
case 0xb2:
	if(AVR_nop(ctx, 0xb2) || ctx->breakpointActivated) break;	// nop {} HEX:0x0
case 0xb3:
	if(AVR_nop(ctx, 0xb3) || ctx->breakpointActivated) break;	// nop {} HEX:0x0
case 0xb4:
	if(AVR_nop(ctx, 0xb4) || ctx->breakpointActivated) break;	// nop {} HEX:0x0
case 0xb5:
	if(AVR_nop(ctx, 0xb5) || ctx->breakpointActivated) break;	// nop {} HEX:0x0
case 0xb6:
	if(AVR_nop(ctx, 0xb6) || ctx->breakpointActivated) break;	// nop {} HEX:0x0
case 0xb7:
	if(AVR_nop(ctx, 0xb7) || ctx->breakpointActivated) break;	// nop {} HEX:0x0
case 0xb8:
	if(AVR_nop(ctx, 0xb8) || ctx->breakpointActivated) break;	// nop {} HEX:0x0
case 0xb9:
	if(AVR_nop(ctx, 0xb9) || ctx->breakpointActivated) break;	// nop {} HEX:0x0
case 0xba:
	if(AVR_nop(ctx, 0xba) || ctx->breakpointActivated) break;	// nop {} HEX:0x0
case 0xbb:
	if(AVR_nop(ctx, 0xbb) || ctx->breakpointActivated) break;	// nop {} HEX:0x0
case 0xbc:
	if(AVR_nop(ctx, 0xbc) || ctx->breakpointActivated) break;	// nop {} HEX:0x0
case 0xbd:
	if(AVR_nop(ctx, 0xbd) || ctx->breakpointActivated) break;	// nop {} HEX:0x0
case 0xbe:
	if(AVR_nop(ctx, 0xbe) || ctx->breakpointActivated) break;	// nop {} HEX:0x0
case 0xbf:
	if(AVR_nop(ctx, 0xbf) || ctx->breakpointActivated) break;	// nop {} HEX:0x0
case 0xc0:
	if(AVR_nop(ctx, 0xc0) || ctx->breakpointActivated) break;	// nop {} HEX:0x0
case 0xc1:
	if(AVR_nop(ctx, 0xc1) || ctx->breakpointActivated) break;	// nop {} HEX:0x0
case 0xc2:
	if(AVR_nop(ctx, 0xc2) || ctx->breakpointActivated) break;	// nop {} HEX:0x0
case 0xc3:
	if(AVR_nop(ctx, 0xc3) || ctx->breakpointActivated) break;	// nop {} HEX:0x0
case 0xc4:
	if(AVR_nop(ctx, 0xc4) || ctx->breakpointActivated) break;	// nop {} HEX:0x0
case 0xc5:
	if(AVR_nop(ctx, 0xc5) || ctx->breakpointActivated) break;	// nop {} HEX:0x0
case 0xc6:
	if(AVR_nop(ctx, 0xc6) || ctx->breakpointActivated) break;	// nop {} HEX:0x0
case 0xc7:
	if(AVR_nop(ctx, 0xc7) || ctx->breakpointActivated) break;	// nop {} HEX:0x0
case 0xc8:
	if(AVR_nop(ctx, 0xc8) || ctx->breakpointActivated) break;	// nop {} HEX:0x0
case 0xc9:
	if(AVR_nop(ctx, 0xc9) || ctx->breakpointActivated) break;	// nop {} HEX:0x0
case 0xca:
	if(AVR_nop(ctx, 0xca) || ctx->breakpointActivated) break;	// nop {} HEX:0x0
case 0xcb:
	if(AVR_nop(ctx, 0xcb) || ctx->breakpointActivated) break;	// nop {} HEX:0x0
case 0xcc:
	if(AVR_nop(ctx, 0xcc) || ctx->breakpointActivated) break;	// nop {} HEX:0x0
case 0xcd:
	if(AVR_nop(ctx, 0xcd) || ctx->breakpointActivated) break;	// nop {} HEX:0x0
case 0xce:
	if(AVR_nop(ctx, 0xce) || ctx->breakpointActivated) break;	// nop {} HEX:0x0
case 0xcf:
	if(AVR_nop(ctx, 0xcf) || ctx->breakpointActivated) break;	// nop {} HEX:0x0
case 0xd0:
	if(AVR_nop(ctx, 0xd0) || ctx->breakpointActivated) break;	// nop {} HEX:0x0
case 0xd1:
	if(AVR_nop(ctx, 0xd1) || ctx->breakpointActivated) break;	// nop {} HEX:0x0
case 0xd2:
	if(AVR_nop(ctx, 0xd2) || ctx->breakpointActivated) break;	// nop {} HEX:0x0
case 0xd3:
	if(AVR_nop(ctx, 0xd3) || ctx->breakpointActivated) break;	// nop {} HEX:0x0
case 0xd4:
	if(AVR_nop(ctx, 0xd4) || ctx->breakpointActivated) break;	// nop {} HEX:0x0
case 0xd5:
	if(AVR_nop(ctx, 0xd5) || ctx->breakpointActivated) break;	// nop {} HEX:0x0
case 0xd6:
	if(AVR_nop(ctx, 0xd6) || ctx->breakpointActivated) break;	// nop {} HEX:0x0
case 0xd7:
	if(AVR_nop(ctx, 0xd7) || ctx->breakpointActivated) break;	// nop {} HEX:0x0
case 0xd8:
	if(AVR_nop(ctx, 0xd8) || ctx->breakpointActivated) break;	// nop {} HEX:0x0
case 0xd9:
	if(AVR_nop(ctx, 0xd9) || ctx->breakpointActivated) break;	// nop {} HEX:0x0
case 0xda:
	if(AVR_nop(ctx, 0xda) || ctx->breakpointActivated) break;	// nop {} HEX:0x0
case 0xdb:
	if(AVR_nop(ctx, 0xdb) || ctx->breakpointActivated) break;	// nop {} HEX:0x0
case 0xdc:
	if(AVR_nop(ctx, 0xdc) || ctx->breakpointActivated) break;	// nop {} HEX:0x0
case 0xdd:
	if(AVR_nop(ctx, 0xdd) || ctx->breakpointActivated) break;	// nop {} HEX:0x0
case 0xde:
	if(AVR_nop(ctx, 0xde) || ctx->breakpointActivated) break;	// nop {} HEX:0x0
case 0xdf:
	if(AVR_nop(ctx, 0xdf) || ctx->breakpointActivated) break;	// nop {} HEX:0x0
case 0xe0:
	if(AVR_nop(ctx, 0xe0) || ctx->breakpointActivated) break;	// nop {} HEX:0x0
case 0xe1:
	if(AVR_nop(ctx, 0xe1) || ctx->breakpointActivated) break;	// nop {} HEX:0x0
case 0xe2:
	if(AVR_nop(ctx, 0xe2) || ctx->breakpointActivated) break;	// nop {} HEX:0x0
case 0xe3:
	if(AVR_nop(ctx, 0xe3) || ctx->breakpointActivated) break;	// nop {} HEX:0x0
case 0xe4:
	if(AVR_nop(ctx, 0xe4) || ctx->breakpointActivated) break;	// nop {} HEX:0x0
case 0xe5:
	if(AVR_nop(ctx, 0xe5) || ctx->breakpointActivated) break;	// nop {} HEX:0x0
case 0xe6:
	if(AVR_nop(ctx, 0xe6) || ctx->breakpointActivated) break;	// nop {} HEX:0x0
case 0xe7:
	if(AVR_nop(ctx, 0xe7) || ctx->breakpointActivated) break;	// nop {} HEX:0x0
case 0xe8:
	if(AVR_nop(ctx, 0xe8) || ctx->breakpointActivated) break;	// nop {} HEX:0x0
case 0xe9:
	if(AVR_nop(ctx, 0xe9) || ctx->breakpointActivated) break;	// nop {} HEX:0x0
case 0xea:
	if(AVR_nop(ctx, 0xea) || ctx->breakpointActivated) break;	// nop {} HEX:0x0
case 0xeb:
	if(AVR_nop(ctx, 0xeb) || ctx->breakpointActivated) break;	// nop {} HEX:0x0
case 0xec:
	if(AVR_nop(ctx, 0xec) || ctx->breakpointActivated) break;	// nop {} HEX:0x0
case 0xed:
	if(AVR_nop(ctx, 0xed) || ctx->breakpointActivated) break;	// nop {} HEX:0x0
case 0xee:
	if(AVR_nop(ctx, 0xee) || ctx->breakpointActivated) break;	// nop {} HEX:0x0
case 0xef:
	if(AVR_nop(ctx, 0xef) || ctx->breakpointActivated) break;	// nop {} HEX:0x0
case 0xf0:
	if(AVR_nop(ctx, 0xf0) || ctx->breakpointActivated) break;	// nop {} HEX:0x0
case 0xf1:
	if(AVR_nop(ctx, 0xf1) || ctx->breakpointActivated) break;	// nop {} HEX:0x0
case 0xf2:
	if(AVR_nop(ctx, 0xf2) || ctx->breakpointActivated) break;	// nop {} HEX:0x0
case 0xf3:
	if(AVR_nop(ctx, 0xf3) || ctx->breakpointActivated) break;	// nop {} HEX:0x0
case 0xf4:
	if(AVR_nop(ctx, 0xf4) || ctx->breakpointActivated) break;	// nop {} HEX:0x0
case 0xf5:
	if(AVR_nop(ctx, 0xf5) || ctx->breakpointActivated) break;	// nop {} HEX:0x0
case 0xf6:
	if(AVR_nop(ctx, 0xf6) || ctx->breakpointActivated) break;	// nop {} HEX:0x0
case 0xf7:
	if(AVR_nop(ctx, 0xf7) || ctx->breakpointActivated) break;	// nop {} HEX:0x0
case 0xf8:
	if(AVR_nop(ctx, 0xf8) || ctx->breakpointActivated) break;	// nop {} HEX:0x0
case 0xf9:
	if(AVR_nop(ctx, 0xf9) || ctx->breakpointActivated) break;	// nop {} HEX:0x0
case 0xfa:
	if(AVR_nop(ctx, 0xfa) || ctx->breakpointActivated) break;	// nop {} HEX:0x0
case 0xfb:
	if(AVR_nop(ctx, 0xfb) || ctx->breakpointActivated) break;	// nop {} HEX:0x0
case 0xfc:
	if(AVR_nop(ctx, 0xfc) || ctx->breakpointActivated) break;	// nop {} HEX:0x0
case 0xfd:
	if(AVR_nop(ctx, 0xfd) || ctx->breakpointActivated) break;	// nop {} HEX:0x0
case 0xfe:
	if(AVR_nop(ctx, 0xfe) || ctx->breakpointActivated) break;	// nop {} HEX:0x0
case 0xff:
	if(AVR_nop(ctx, 0xff) || ctx->breakpointActivated) break;	// nop {} HEX:0x0
case 0x200:
	if(AVR_sbrs(ctx, 0x200, /* b */0x1, /* r */0xc) || ctx->breakpointActivated) break;	// sbrs {b=001, r=01100} HEX:0xfec1
case 0x201:
	if(AVR_ldi(ctx, 0x201, /* K */0x5, /* d */0x8) || ctx->breakpointActivated) break;	// ldi {K=00000101, d=1000} HEX:0xe085
case 0x202:
	if(AVR_nop(ctx, 0x202) || ctx->breakpointActivated) break;	// nop {} HEX:0x0
case 0x203:
	if(AVR_nop(ctx, 0x203) || ctx->breakpointActivated) break;	// nop {} HEX:0x0
case 0x204:
	if(AVR_rjmp(ctx, 0x204, /* k */0xe2d) || ctx->breakpointActivated) break;	// rjmp {k=111000101101} HEX:0xce2d
case 0x205:
	if(AVR_sbrc(ctx, 0x205, /* b */0x1, /* r */0xc) || ctx->breakpointActivated) break;	// sbrc {b=001, r=01100} HEX:0xfcc1
case 0x206:
	if(AVR_ldi(ctx, 0x206, /* K */0xa, /* d */0x8) || ctx->breakpointActivated) break;	// ldi {K=00001010, d=1000} HEX:0xe08a
case 0x207:
	if(AVR_nop(ctx, 0x207) || ctx->breakpointActivated) break;	// nop {} HEX:0x0
case 0x208:
	if(AVR_nop(ctx, 0x208) || ctx->breakpointActivated) break;	// nop {} HEX:0x0
case 0x209:
	if(AVR_rjmp(ctx, 0x209, /* k */0xe28) || ctx->breakpointActivated) break;	// rjmp {k=111000101000} HEX:0xce28
case 0x20a:
	if(AVR_movw(ctx, 0x20a, /* d */0x3, /* r */0xd) || ctx->breakpointActivated) break;	// movw {d=0011, r=1101} HEX:0x13d
case 0x20b:
	if(AVR_movw(ctx, 0x20b, /* d */0x4, /* r */0xe) || ctx->breakpointActivated) break;	// movw {d=0100, r=1110} HEX:0x14e
case 0x20c:
	if(AVR_ldi(ctx, 0x20c, /* K */0xf, /* d */0x8) || ctx->breakpointActivated) break;	// ldi {K=00001111, d=1000} HEX:0xe08f
case 0x20d:
	if(AVR_out(ctx, 0x20d, /* A */0x17, /* r */0xe) || ctx->breakpointActivated) break;	// out {A=010111, r=01110} HEX:0xbae7
case 0x20e:
	if(AVR_rjmp(ctx, 0x20e, /* k */0xe23) || ctx->breakpointActivated) break;	// rjmp {k=111000100011} HEX:0xce23
case 0x20f:
	if(AVR_mov(ctx, 0x20f, /* d */0x13, /* r */0x6) || ctx->breakpointActivated) break;	// mov {d=10011, r=00110} HEX:0x2d36
case 0x210:
	if(AVR_ldi(ctx, 0x210, /* K */0x14, /* d */0x9) || ctx->breakpointActivated) break;	// ldi {K=00010100, d=1001} HEX:0xe194
case 0x211:
	if(AVR_ldi(ctx, 0x211, /* K */0x46, /* d */0x8) || ctx->breakpointActivated) break;	// ldi {K=01000110, d=1000} HEX:0xe486
case 0x212:
	if(AVR_nop(ctx, 0x212) || ctx->breakpointActivated) break;	// nop {} HEX:0x0
case 0x213:
	if(AVR_rjmp(ctx, 0x213, /* k */0xe1e) || ctx->breakpointActivated) break;	// rjmp {k=111000011110} HEX:0xce1e
case 0x214:
	if(AVR_mov(ctx, 0x214, /* d */0x13, /* r */0x7) || ctx->breakpointActivated) break;	// mov {d=10011, r=00111} HEX:0x2d37
case 0x215:
	if(AVR_ldi(ctx, 0x215, /* K */0x19, /* d */0x9) || ctx->breakpointActivated) break;	// ldi {K=00011001, d=1001} HEX:0xe199
case 0x216:
	if(AVR_ldi(ctx, 0x216, /* K */0x46, /* d */0x8) || ctx->breakpointActivated) break;	// ldi {K=01000110, d=1000} HEX:0xe486
case 0x217:
	if(AVR_nop(ctx, 0x217) || ctx->breakpointActivated) break;	// nop {} HEX:0x0
case 0x218:
	if(AVR_rjmp(ctx, 0x218, /* k */0xe19) || ctx->breakpointActivated) break;	// rjmp {k=111000011001} HEX:0xce19
case 0x219:
	if(AVR_mov(ctx, 0x219, /* d */0x13, /* r */0x8) || ctx->breakpointActivated) break;	// mov {d=10011, r=01000} HEX:0x2d38
case 0x21a:
	if(AVR_ldi(ctx, 0x21a, /* K */0x1e, /* d */0x9) || ctx->breakpointActivated) break;	// ldi {K=00011110, d=1001} HEX:0xe19e
case 0x21b:
	if(AVR_ldi(ctx, 0x21b, /* K */0x46, /* d */0x8) || ctx->breakpointActivated) break;	// ldi {K=01000110, d=1000} HEX:0xe486
case 0x21c:
	if(AVR_nop(ctx, 0x21c) || ctx->breakpointActivated) break;	// nop {} HEX:0x0
case 0x21d:
	if(AVR_rjmp(ctx, 0x21d, /* k */0xe14) || ctx->breakpointActivated) break;	// rjmp {k=111000010100} HEX:0xce14
case 0x21e:
	if(AVR_mov(ctx, 0x21e, /* d */0x13, /* r */0x9) || ctx->breakpointActivated) break;	// mov {d=10011, r=01001} HEX:0x2d39
case 0x21f:
	if(AVR_ldi(ctx, 0x21f, /* K */0x23, /* d */0x9) || ctx->breakpointActivated) break;	// ldi {K=00100011, d=1001} HEX:0xe293
case 0x220:
	if(AVR_ldi(ctx, 0x220, /* K */0x46, /* d */0x8) || ctx->breakpointActivated) break;	// ldi {K=01000110, d=1000} HEX:0xe486
case 0x221:
	if(AVR_nop(ctx, 0x221) || ctx->breakpointActivated) break;	// nop {} HEX:0x0
case 0x222:
	if(AVR_rjmp(ctx, 0x222, /* k */0xe0f) || ctx->breakpointActivated) break;	// rjmp {k=111000001111} HEX:0xce0f
case 0x223:
	if(AVR_mov(ctx, 0x223, /* d */0x13, /* r */0x11) || ctx->breakpointActivated) break;	// mov {d=10011, r=10001} HEX:0x2f31
case 0x224:
	if(AVR_ldi(ctx, 0x224, /* K */0x0, /* d */0x1) || ctx->breakpointActivated) break;	// ldi {K=00000000, d=0001} HEX:0xe010
case 0x225:
	if(AVR_ldi(ctx, 0x225, /* K */0x28, /* d */0x9) || ctx->breakpointActivated) break;	// ldi {K=00101000, d=1001} HEX:0xe298
case 0x226:
	if(AVR_ldi(ctx, 0x226, /* K */0x46, /* d */0x8) || ctx->breakpointActivated) break;	// ldi {K=01000110, d=1000} HEX:0xe486
case 0x227:
	if(AVR_rjmp(ctx, 0x227, /* k */0xe0a) || ctx->breakpointActivated) break;	// rjmp {k=111000001010} HEX:0xce0a
case 0x228:
	if(AVR_movw(ctx, 0x228, /* d */0x3, /* r */0x1) || ctx->breakpointActivated) break;	// movw {d=0011, r=0001} HEX:0x131
case 0x229:
	if(AVR_movw(ctx, 0x229, /* d */0x4, /* r */0x2) || ctx->breakpointActivated) break;	// movw {d=0100, r=0010} HEX:0x142
case 0x22a:
	if(AVR_ldi(ctx, 0x22a, /* K */0x2d, /* d */0x8) || ctx->breakpointActivated) break;	// ldi {K=00101101, d=1000} HEX:0xe28d
case 0x22b:
	if(AVR_nop(ctx, 0x22b) || ctx->breakpointActivated) break;	// nop {} HEX:0x0
case 0x22c:
	if(AVR_rjmp(ctx, 0x22c, /* k */0xe05) || ctx->breakpointActivated) break;	// rjmp {k=111000000101} HEX:0xce05
case 0x22d:
	if(AVR_mov(ctx, 0x22d, /* d */0x13, /* r */0x6) || ctx->breakpointActivated) break;	// mov {d=10011, r=00110} HEX:0x2d36
case 0x22e:
	if(AVR_ldi(ctx, 0x22e, /* K */0x32, /* d */0x9) || ctx->breakpointActivated) break;	// ldi {K=00110010, d=1001} HEX:0xe392
case 0x22f:
	if(AVR_ldi(ctx, 0x22f, /* K */0x46, /* d */0x8) || ctx->breakpointActivated) break;	// ldi {K=01000110, d=1000} HEX:0xe486
case 0x230:
	if(AVR_nop(ctx, 0x230) || ctx->breakpointActivated) break;	// nop {} HEX:0x0
case 0x231:
	if(AVR_rjmp(ctx, 0x231, /* k */0xe00) || ctx->breakpointActivated) break;	// rjmp {k=111000000000} HEX:0xce00
case 0x232:
	if(AVR_mov(ctx, 0x232, /* d */0x13, /* r */0x7) || ctx->breakpointActivated) break;	// mov {d=10011, r=00111} HEX:0x2d37
case 0x233:
	if(AVR_ldi(ctx, 0x233, /* K */0x37, /* d */0x9) || ctx->breakpointActivated) break;	// ldi {K=00110111, d=1001} HEX:0xe397
case 0x234:
	if(AVR_ldi(ctx, 0x234, /* K */0x46, /* d */0x8) || ctx->breakpointActivated) break;	// ldi {K=01000110, d=1000} HEX:0xe486
case 0x235:
	if(AVR_nop(ctx, 0x235) || ctx->breakpointActivated) break;	// nop {} HEX:0x0
case 0x236:
	if(AVR_rjmp(ctx, 0x236, /* k */0xdfb) || ctx->breakpointActivated) break;	// rjmp {k=110111111011} HEX:0xcdfb
case 0x237:
	if(AVR_mov(ctx, 0x237, /* d */0x13, /* r */0x8) || ctx->breakpointActivated) break;	// mov {d=10011, r=01000} HEX:0x2d38
case 0x238:
	if(AVR_ldi(ctx, 0x238, /* K */0x3c, /* d */0x9) || ctx->breakpointActivated) break;	// ldi {K=00111100, d=1001} HEX:0xe39c
case 0x239:
	if(AVR_ldi(ctx, 0x239, /* K */0x46, /* d */0x8) || ctx->breakpointActivated) break;	// ldi {K=01000110, d=1000} HEX:0xe486
case 0x23a:
	if(AVR_nop(ctx, 0x23a) || ctx->breakpointActivated) break;	// nop {} HEX:0x0
case 0x23b:
	if(AVR_rjmp(ctx, 0x23b, /* k */0xdf6) || ctx->breakpointActivated) break;	// rjmp {k=110111110110} HEX:0xcdf6
case 0x23c:
	if(AVR_mov(ctx, 0x23c, /* d */0x13, /* r */0x9) || ctx->breakpointActivated) break;	// mov {d=10011, r=01001} HEX:0x2d39
case 0x23d:
	if(AVR_ldi(ctx, 0x23d, /* K */0x41, /* d */0x9) || ctx->breakpointActivated) break;	// ldi {K=01000001, d=1001} HEX:0xe491
case 0x23e:
	if(AVR_ldi(ctx, 0x23e, /* K */0x46, /* d */0x8) || ctx->breakpointActivated) break;	// ldi {K=01000110, d=1000} HEX:0xe486
case 0x23f:
	if(AVR_nop(ctx, 0x23f) || ctx->breakpointActivated) break;	// nop {} HEX:0x0
case 0x240:
	if(AVR_rjmp(ctx, 0x240, /* k */0xdf1) || ctx->breakpointActivated) break;	// rjmp {k=110111110001} HEX:0xcdf1
case 0x241:
	if(AVR_out(ctx, 0x241, /* A */0x17, /* r */0x0) || ctx->breakpointActivated) break;	// out {A=010111, r=00000} HEX:0xba07
case 0x242:
	if(AVR_ldi(ctx, 0x242, /* K */0x0, /* d */0x8) || ctx->breakpointActivated) break;	// ldi {K=00000000, d=1000} HEX:0xe080
case 0x243:
	if(AVR_nop(ctx, 0x243) || ctx->breakpointActivated) break;	// nop {} HEX:0x0
case 0x244:
	if(AVR_nop(ctx, 0x244) || ctx->breakpointActivated) break;	// nop {} HEX:0x0
case 0x245:
	if(AVR_rjmp(ctx, 0x245, /* k */0xdec) || ctx->breakpointActivated) break;	// rjmp {k=110111101100} HEX:0xcdec
case 0x246:
	if(AVR_out(ctx, 0x246, /* A */0x18, /* r */0xd) || ctx->breakpointActivated) break;	// out {A=011000, r=01101} HEX:0xbad8
case 0x247:
	if(AVR_sbrc(ctx, 0x247, /* b */0x0, /* r */0x13) || ctx->breakpointActivated) break;	// sbrc {b=000, r=10011} HEX:0xfd30
case 0x248:
	if(AVR_ldi(ctx, 0x248, /* K */0x18, /* d */0x6) || ctx->breakpointActivated) break;	// ldi {K=00011000, d=0110} HEX:0xe168
case 0x249:
	if(AVR_ldi(ctx, 0x249, /* K */0x4b, /* d */0x8) || ctx->breakpointActivated) break;	// ldi {K=01001011, d=1000} HEX:0xe48b
case 0x24a:
	if(AVR_rjmp(ctx, 0x24a, /* k */0xde7) || ctx->breakpointActivated) break;	// rjmp {k=110111100111} HEX:0xcde7
case 0x24b:
	if(AVR_out(ctx, 0x24b, /* A */0x18, /* r */0xd) || ctx->breakpointActivated) break;	// out {A=011000, r=01101} HEX:0xbad8
case 0x24c:
	if(AVR_sbrc(ctx, 0x24c, /* b */0x1, /* r */0x13) || ctx->breakpointActivated) break;	// sbrc {b=001, r=10011} HEX:0xfd31
case 0x24d:
	if(AVR_ldi(ctx, 0x24d, /* K */0x18, /* d */0x6) || ctx->breakpointActivated) break;	// ldi {K=00011000, d=0110} HEX:0xe168
case 0x24e:
	if(AVR_ldi(ctx, 0x24e, /* K */0x50, /* d */0x8) || ctx->breakpointActivated) break;	// ldi {K=01010000, d=1000} HEX:0xe580
case 0x24f:
	if(AVR_rjmp(ctx, 0x24f, /* k */0xde2) || ctx->breakpointActivated) break;	// rjmp {k=110111100010} HEX:0xcde2
case 0x250:
	if(AVR_out(ctx, 0x250, /* A */0x18, /* r */0xd) || ctx->breakpointActivated) break;	// out {A=011000, r=01101} HEX:0xbad8
case 0x251:
	if(AVR_sbrc(ctx, 0x251, /* b */0x2, /* r */0x13) || ctx->breakpointActivated) break;	// sbrc {b=010, r=10011} HEX:0xfd32
case 0x252:
	if(AVR_ldi(ctx, 0x252, /* K */0x18, /* d */0x6) || ctx->breakpointActivated) break;	// ldi {K=00011000, d=0110} HEX:0xe168
case 0x253:
	if(AVR_ldi(ctx, 0x253, /* K */0x55, /* d */0x8) || ctx->breakpointActivated) break;	// ldi {K=01010101, d=1000} HEX:0xe585
case 0x254:
	if(AVR_rjmp(ctx, 0x254, /* k */0xddd) || ctx->breakpointActivated) break;	// rjmp {k=110111011101} HEX:0xcddd
case 0x255:
	if(AVR_out(ctx, 0x255, /* A */0x18, /* r */0xd) || ctx->breakpointActivated) break;	// out {A=011000, r=01101} HEX:0xbad8
case 0x256:
	if(AVR_sbrc(ctx, 0x256, /* b */0x3, /* r */0x13) || ctx->breakpointActivated) break;	// sbrc {b=011, r=10011} HEX:0xfd33
case 0x257:
	if(AVR_ldi(ctx, 0x257, /* K */0x18, /* d */0x6) || ctx->breakpointActivated) break;	// ldi {K=00011000, d=0110} HEX:0xe168
case 0x258:
	if(AVR_ldi(ctx, 0x258, /* K */0x5a, /* d */0x8) || ctx->breakpointActivated) break;	// ldi {K=01011010, d=1000} HEX:0xe58a
case 0x259:
	if(AVR_rjmp(ctx, 0x259, /* k */0xdd8) || ctx->breakpointActivated) break;	// rjmp {k=110111011000} HEX:0xcdd8
case 0x25a:
	if(AVR_out(ctx, 0x25a, /* A */0x18, /* r */0xd) || ctx->breakpointActivated) break;	// out {A=011000, r=01101} HEX:0xbad8
case 0x25b:
	if(AVR_sbrc(ctx, 0x25b, /* b */0x4, /* r */0x13) || ctx->breakpointActivated) break;	// sbrc {b=100, r=10011} HEX:0xfd34
case 0x25c:
	if(AVR_ldi(ctx, 0x25c, /* K */0x18, /* d */0x6) || ctx->breakpointActivated) break;	// ldi {K=00011000, d=0110} HEX:0xe168
case 0x25d:
	if(AVR_ldi(ctx, 0x25d, /* K */0x5f, /* d */0x8) || ctx->breakpointActivated) break;	// ldi {K=01011111, d=1000} HEX:0xe58f
case 0x25e:
	if(AVR_rjmp(ctx, 0x25e, /* k */0xdd3) || ctx->breakpointActivated) break;	// rjmp {k=110111010011} HEX:0xcdd3
case 0x25f:
	if(AVR_out(ctx, 0x25f, /* A */0x18, /* r */0xd) || ctx->breakpointActivated) break;	// out {A=011000, r=01101} HEX:0xbad8
case 0x260:
	if(AVR_sbrc(ctx, 0x260, /* b */0x5, /* r */0x13) || ctx->breakpointActivated) break;	// sbrc {b=101, r=10011} HEX:0xfd35
case 0x261:
	if(AVR_ldi(ctx, 0x261, /* K */0x18, /* d */0x6) || ctx->breakpointActivated) break;	// ldi {K=00011000, d=0110} HEX:0xe168
case 0x262:
	if(AVR_ldi(ctx, 0x262, /* K */0x64, /* d */0x8) || ctx->breakpointActivated) break;	// ldi {K=01100100, d=1000} HEX:0xe684
case 0x263:
	if(AVR_rjmp(ctx, 0x263, /* k */0xdce) || ctx->breakpointActivated) break;	// rjmp {k=110111001110} HEX:0xcdce
case 0x264:
	if(AVR_out(ctx, 0x264, /* A */0x18, /* r */0xd) || ctx->breakpointActivated) break;	// out {A=011000, r=01101} HEX:0xbad8
case 0x265:
	if(AVR_sbrc(ctx, 0x265, /* b */0x6, /* r */0x13) || ctx->breakpointActivated) break;	// sbrc {b=110, r=10011} HEX:0xfd36
case 0x266:
	if(AVR_ldi(ctx, 0x266, /* K */0x18, /* d */0x6) || ctx->breakpointActivated) break;	// ldi {K=00011000, d=0110} HEX:0xe168
case 0x267:
	if(AVR_ldi(ctx, 0x267, /* K */0x69, /* d */0x8) || ctx->breakpointActivated) break;	// ldi {K=01101001, d=1000} HEX:0xe689
case 0x268:
	if(AVR_rjmp(ctx, 0x268, /* k */0xdc9) || ctx->breakpointActivated) break;	// rjmp {k=110111001001} HEX:0xcdc9
case 0x269:
	if(AVR_out(ctx, 0x269, /* A */0x18, /* r */0xd) || ctx->breakpointActivated) break;	// out {A=011000, r=01101} HEX:0xbad8
case 0x26a:
	if(AVR_sbrc(ctx, 0x26a, /* b */0x7, /* r */0x13) || ctx->breakpointActivated) break;	// sbrc {b=111, r=10011} HEX:0xfd37
case 0x26b:
	if(AVR_ldi(ctx, 0x26b, /* K */0x18, /* d */0x6) || ctx->breakpointActivated) break;	// ldi {K=00011000, d=0110} HEX:0xe168
case 0x26c:
	if(AVR_mov(ctx, 0x26c, /* d */0x18, /* r */0x19) || ctx->breakpointActivated) break;	// mov {d=11000, r=11001} HEX:0x2f89
case 0x26d:
	if(AVR_rjmp(ctx, 0x26d, /* k */0xdc4) || ctx->breakpointActivated) break;	// rjmp {k=110111000100} HEX:0xcdc4
		default:
			AVR_error_nosp(ctx, sp);
			break;
	}
}
