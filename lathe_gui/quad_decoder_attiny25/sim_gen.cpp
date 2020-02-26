#include <AVR_simulator.h>
void executeFromAddress(AVR_simulator_t * ctx, uint32_t sp)
{
	switch(sp)
	{
case 0x0:
	if(AVR_ldi(ctx, 0x0, /* K */0x18, /* d */0xf) || ctx->breakpointActivated) break;	// ldi {K=00011000, d=1111} HEX:0xe1f8
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
	if(AVR_ldi(ctx, 0x8, /* K */0x1, /* d */0xf) || ctx->breakpointActivated) break;	// ldi {K=00000001, d=1111} HEX:0xe0f1
case 0x9:
	if(AVR_ldi(ctx, 0x9, /* K */0x4a, /* d */0x8) || ctx->breakpointActivated) break;	// ldi {K=01001010, d=1000} HEX:0xe48a
case 0xa:
	if(AVR_ldi(ctx, 0xa, /* K */0x0, /* d */0x1) || ctx->breakpointActivated) break;	// ldi {K=00000000, d=0001} HEX:0xe010
case 0xb:
	if(AVR_ldi(ctx, 0xb, /* K */0x5, /* d */0x0) || ctx->breakpointActivated) break;	// ldi {K=00000101, d=0000} HEX:0xe005
case 0xc:
	if(AVR_in(ctx, 0xc, /* A */0x16, /* d */0xa) || ctx->breakpointActivated) break;	// in {A=010110, d=01010} HEX:0xb2a6
case 0xd:
	if(AVR_and(ctx, 0xd, /* d */0xa, /* r */0x10) || ctx->breakpointActivated) break;	// and {d=01010, r=10000} HEX:0x22a0
case 0xe:
	if(AVR_in(ctx, 0xe, /* A */0x16, /* d */0xb) || ctx->breakpointActivated) break;	// in {A=010110, d=01011} HEX:0xb2b6
case 0xf:
	if(AVR_in(ctx, 0xf, /* A */0x16, /* d */0xc) || ctx->breakpointActivated) break;	// in {A=010110, d=01100} HEX:0xb2c6
case 0x10:
	if(AVR_in(ctx, 0x10, /* A */0x16, /* d */0x1e) || ctx->breakpointActivated) break;	// in {A=010110, d=11110} HEX:0xb3e6
case 0x11:
	if(AVR_and(ctx, 0x11, /* d */0xb, /* r */0x10) || ctx->breakpointActivated) break;	// and {d=01011, r=10000} HEX:0x22b0
case 0x12:
	if(AVR_and(ctx, 0x12, /* d */0xc, /* r */0x10) || ctx->breakpointActivated) break;	// and {d=01100, r=10000} HEX:0x22c0
case 0x13:
	if(AVR_and(ctx, 0x13, /* d */0x1e, /* r */0x10) || ctx->breakpointActivated) break;	// and {d=11110, r=10000} HEX:0x23e0
case 0x14:
	if(AVR_add(ctx, 0x14, /* d */0xb, /* r */0xb) || ctx->breakpointActivated) break;	// add {d=01011, r=01011} HEX:0xcbb
case 0x15:
	if(AVR_or(ctx, 0x15, /* d */0xb, /* r */0xa) || ctx->breakpointActivated) break;	// or {d=01011, r=01010} HEX:0x28ba
case 0x16:
	if(AVR_mov(ctx, 0x16, /* d */0xa, /* r */0x1e) || ctx->breakpointActivated) break;	// mov {d=01010, r=11110} HEX:0x2eae
case 0x17:
	if(AVR_swap(ctx, 0x17, /* d */0xb) || ctx->breakpointActivated) break;	// swap {d=01011} HEX:0x94b2
case 0x18:
	if(AVR_add(ctx, 0x18, /* d */0xc, /* r */0xc) || ctx->breakpointActivated) break;	// add {d=01100, r=01100} HEX:0xccc
case 0x19:
	if(AVR_or(ctx, 0x19, /* d */0x1e, /* r */0xc) || ctx->breakpointActivated) break;	// or {d=11110, r=01100} HEX:0x29ec
case 0x1a:
	if(AVR_or(ctx, 0x1a, /* d */0x1e, /* r */0xb) || ctx->breakpointActivated) break;	// or {d=11110, r=01011} HEX:0x29eb
case 0x1b:
	if(AVR_ldi(ctx, 0x1b, /* K */0x1, /* d */0xf) || ctx->breakpointActivated) break;	// ldi {K=00000001, d=1111} HEX:0xe0f1
case 0x1c:
	if(AVR_in(ctx, 0x1c, /* A */0x16, /* d */0xb) || ctx->breakpointActivated) break;	// in {A=010110, d=01011} HEX:0xb2b6
case 0x1d:
	if(AVR_ijmp(ctx, 0x1d) || ctx->breakpointActivated) break;	// ijmp {} HEX:0x9409
case 0x1e:
	if(AVR_mov(ctx, 0x1e, /* d */0x1e, /* r */0x18) || ctx->breakpointActivated) break;	// mov {d=11110, r=11000} HEX:0x2fe8
case 0x1f:
	if(AVR_in(ctx, 0x1f, /* A */0x16, /* d */0xc) || ctx->breakpointActivated) break;	// in {A=010110, d=01100} HEX:0xb2c6
case 0x20:
	if(AVR_ldi(ctx, 0x20, /* K */0x0, /* d */0xf) || ctx->breakpointActivated) break;	// ldi {K=00000000, d=1111} HEX:0xe0f0
case 0x21:
	if(AVR_ijmp(ctx, 0x21) || ctx->breakpointActivated) break;	// ijmp {} HEX:0x9409
case 0x22:
	if(AVR_nop(ctx, 0x22) || ctx->breakpointActivated) break;	// nop {} HEX:0x0
case 0x23:
	if(AVR_nop(ctx, 0x23) || ctx->breakpointActivated) break;	// nop {} HEX:0x0
case 0x24:
	if(AVR_nop(ctx, 0x24) || ctx->breakpointActivated) break;	// nop {} HEX:0x0
case 0x25:
	if(AVR_nop(ctx, 0x25) || ctx->breakpointActivated) break;	// nop {} HEX:0x0
case 0x26:
	if(AVR_rjmp(ctx, 0x26, /* k */0xff7) || ctx->breakpointActivated) break;	// rjmp {k=111111110111} HEX:0xcff7
case 0x27:
	if(AVR_ldi(ctx, 0x27, /* K */0x1, /* d */0x1) || ctx->breakpointActivated) break;	// ldi {K=00000001, d=0001} HEX:0xe011
case 0x28:
	if(AVR_nop(ctx, 0x28) || ctx->breakpointActivated) break;	// nop {} HEX:0x0
case 0x29:
	if(AVR_nop(ctx, 0x29) || ctx->breakpointActivated) break;	// nop {} HEX:0x0
case 0x2a:
	if(AVR_nop(ctx, 0x2a) || ctx->breakpointActivated) break;	// nop {} HEX:0x0
case 0x2b:
	if(AVR_rjmp(ctx, 0x2b, /* k */0xff2) || ctx->breakpointActivated) break;	// rjmp {k=111111110010} HEX:0xcff2
case 0x2c:
	if(AVR_subi(ctx, 0x2c, /* K */0xff, /* d */0xa) || ctx->breakpointActivated) break;	// subi {K=11111111, d=1010} HEX:0x5faf
case 0x2d:
	if(AVR_sbci(ctx, 0x2d, /* K */0xff, /* d */0xb) || ctx->breakpointActivated) break;	// sbci {K=11111111, d=1011} HEX:0x4fbf
case 0x2e:
	if(AVR_sbci(ctx, 0x2e, /* K */0xff, /* d */0xc) || ctx->breakpointActivated) break;	// sbci {K=11111111, d=1100} HEX:0x4fcf
case 0x2f:
	if(AVR_sbci(ctx, 0x2f, /* K */0xff, /* d */0xd) || ctx->breakpointActivated) break;	// sbci {K=11111111, d=1101} HEX:0x4fdf
case 0x30:
	if(AVR_rjmp(ctx, 0x30, /* k */0xfed) || ctx->breakpointActivated) break;	// rjmp {k=111111101101} HEX:0xcfed
case 0x31:
	if(AVR_subi(ctx, 0x31, /* K */0xfe, /* d */0xa) || ctx->breakpointActivated) break;	// subi {K=11111110, d=1010} HEX:0x5fae
case 0x32:
	if(AVR_sbci(ctx, 0x32, /* K */0xff, /* d */0xb) || ctx->breakpointActivated) break;	// sbci {K=11111111, d=1011} HEX:0x4fbf
case 0x33:
	if(AVR_sbci(ctx, 0x33, /* K */0xff, /* d */0xc) || ctx->breakpointActivated) break;	// sbci {K=11111111, d=1100} HEX:0x4fcf
case 0x34:
	if(AVR_sbci(ctx, 0x34, /* K */0xff, /* d */0xd) || ctx->breakpointActivated) break;	// sbci {K=11111111, d=1101} HEX:0x4fdf
case 0x35:
	if(AVR_rjmp(ctx, 0x35, /* k */0xfe8) || ctx->breakpointActivated) break;	// rjmp {k=111111101000} HEX:0xcfe8
case 0x36:
	if(AVR_subi(ctx, 0x36, /* K */0xfd, /* d */0xa) || ctx->breakpointActivated) break;	// subi {K=11111101, d=1010} HEX:0x5fad
case 0x37:
	if(AVR_sbci(ctx, 0x37, /* K */0xff, /* d */0xb) || ctx->breakpointActivated) break;	// sbci {K=11111111, d=1011} HEX:0x4fbf
case 0x38:
	if(AVR_sbci(ctx, 0x38, /* K */0xff, /* d */0xc) || ctx->breakpointActivated) break;	// sbci {K=11111111, d=1100} HEX:0x4fcf
case 0x39:
	if(AVR_sbci(ctx, 0x39, /* K */0xff, /* d */0xd) || ctx->breakpointActivated) break;	// sbci {K=11111111, d=1101} HEX:0x4fdf
case 0x3a:
	if(AVR_rjmp(ctx, 0x3a, /* k */0xfe3) || ctx->breakpointActivated) break;	// rjmp {k=111111100011} HEX:0xcfe3
case 0x3b:
	if(AVR_subi(ctx, 0x3b, /* K */0x1, /* d */0xa) || ctx->breakpointActivated) break;	// subi {K=00000001, d=1010} HEX:0x50a1
case 0x3c:
	if(AVR_sbci(ctx, 0x3c, /* K */0x0, /* d */0xb) || ctx->breakpointActivated) break;	// sbci {K=00000000, d=1011} HEX:0x40b0
case 0x3d:
	if(AVR_sbci(ctx, 0x3d, /* K */0x0, /* d */0xc) || ctx->breakpointActivated) break;	// sbci {K=00000000, d=1100} HEX:0x40c0
case 0x3e:
	if(AVR_sbci(ctx, 0x3e, /* K */0x0, /* d */0xd) || ctx->breakpointActivated) break;	// sbci {K=00000000, d=1101} HEX:0x40d0
case 0x3f:
	if(AVR_rjmp(ctx, 0x3f, /* k */0xfde) || ctx->breakpointActivated) break;	// rjmp {k=111111011110} HEX:0xcfde
case 0x40:
	if(AVR_subi(ctx, 0x40, /* K */0x2, /* d */0xa) || ctx->breakpointActivated) break;	// subi {K=00000010, d=1010} HEX:0x50a2
case 0x41:
	if(AVR_sbci(ctx, 0x41, /* K */0x0, /* d */0xb) || ctx->breakpointActivated) break;	// sbci {K=00000000, d=1011} HEX:0x40b0
case 0x42:
	if(AVR_sbci(ctx, 0x42, /* K */0x0, /* d */0xc) || ctx->breakpointActivated) break;	// sbci {K=00000000, d=1100} HEX:0x40c0
case 0x43:
	if(AVR_sbci(ctx, 0x43, /* K */0x0, /* d */0xd) || ctx->breakpointActivated) break;	// sbci {K=00000000, d=1101} HEX:0x40d0
case 0x44:
	if(AVR_rjmp(ctx, 0x44, /* k */0xfd9) || ctx->breakpointActivated) break;	// rjmp {k=111111011001} HEX:0xcfd9
case 0x45:
	if(AVR_subi(ctx, 0x45, /* K */0x3, /* d */0xa) || ctx->breakpointActivated) break;	// subi {K=00000011, d=1010} HEX:0x50a3
case 0x46:
	if(AVR_sbci(ctx, 0x46, /* K */0x0, /* d */0xb) || ctx->breakpointActivated) break;	// sbci {K=00000000, d=1011} HEX:0x40b0
case 0x47:
	if(AVR_sbci(ctx, 0x47, /* K */0x0, /* d */0xc) || ctx->breakpointActivated) break;	// sbci {K=00000000, d=1100} HEX:0x40c0
case 0x48:
	if(AVR_sbci(ctx, 0x48, /* K */0x0, /* d */0xd) || ctx->breakpointActivated) break;	// sbci {K=00000000, d=1101} HEX:0x40d0
case 0x49:
	if(AVR_rjmp(ctx, 0x49, /* k */0xfd4) || ctx->breakpointActivated) break;	// rjmp {k=111111010100} HEX:0xcfd4
case 0x4a:
	if(AVR_sbrs(ctx, 0x4a, /* b */0x1, /* r */0xc) || ctx->breakpointActivated) break;	// sbrs {b=001, r=01100} HEX:0xfec1
case 0x4b:
	if(AVR_ldi(ctx, 0x4b, /* K */0x51, /* d */0x8) || ctx->breakpointActivated) break;	// ldi {K=01010001, d=1000} HEX:0xe581
case 0x4c:
	if(AVR_out(ctx, 0x4c, /* A */0x17, /* r */0x0) || ctx->breakpointActivated) break;	// out {A=010111, r=00000} HEX:0xba07
case 0x4d:
	if(AVR_out(ctx, 0x4d, /* A */0x18, /* r */0x0) || ctx->breakpointActivated) break;	// out {A=011000, r=00000} HEX:0xba08
case 0x4e:
	if(AVR_nop(ctx, 0x4e) || ctx->breakpointActivated) break;	// nop {} HEX:0x0
case 0x4f:
	if(AVR_nop(ctx, 0x4f) || ctx->breakpointActivated) break;	// nop {} HEX:0x0
case 0x50:
	if(AVR_rjmp(ctx, 0x50, /* k */0xfbf) || ctx->breakpointActivated) break;	// rjmp {k=111110111111} HEX:0xcfbf
case 0x51:
	if(AVR_ldi(ctx, 0x51, /* K */0x10, /* d */0xe) || ctx->breakpointActivated) break;	// ldi {K=00010000, d=1110} HEX:0xe1e0
case 0x52:
	if(AVR_out(ctx, 0x52, /* A */0x18, /* r */0x1e) || ctx->breakpointActivated) break;	// out {A=011000, r=11110} HEX:0xbbe8
case 0x53:
	if(AVR_out(ctx, 0x53, /* A */0x17, /* r */0x1) || ctx->breakpointActivated) break;	// out {A=010111, r=00001} HEX:0xba17
case 0x54:
	if(AVR_ldi(ctx, 0x54, /* K */0x58, /* d */0x8) || ctx->breakpointActivated) break;	// ldi {K=01011000, d=1000} HEX:0xe588
case 0x55:
	if(AVR_nop(ctx, 0x55) || ctx->breakpointActivated) break;	// nop {} HEX:0x0
case 0x56:
	if(AVR_nop(ctx, 0x56) || ctx->breakpointActivated) break;	// nop {} HEX:0x0
case 0x57:
	if(AVR_rjmp(ctx, 0x57, /* k */0xfb8) || ctx->breakpointActivated) break;	// rjmp {k=111110111000} HEX:0xcfb8
case 0x58:
	if(AVR_mov(ctx, 0x58, /* d */0x14, /* r */0x1a) || ctx->breakpointActivated) break;	// mov {d=10100, r=11010} HEX:0x2f4a
case 0x59:
	if(AVR_mov(ctx, 0x59, /* d */0x15, /* r */0x1b) || ctx->breakpointActivated) break;	// mov {d=10101, r=11011} HEX:0x2f5b
case 0x5a:
	if(AVR_mov(ctx, 0x5a, /* d */0x16, /* r */0x1c) || ctx->breakpointActivated) break;	// mov {d=10110, r=11100} HEX:0x2f6c
case 0x5b:
	if(AVR_mov(ctx, 0x5b, /* d */0x17, /* r */0x1d) || ctx->breakpointActivated) break;	// mov {d=10111, r=11101} HEX:0x2f7d
case 0x5c:
	if(AVR_ldi(ctx, 0x5c, /* K */0x5f, /* d */0x8) || ctx->breakpointActivated) break;	// ldi {K=01011111, d=1000} HEX:0xe58f
case 0x5d:
	if(AVR_nop(ctx, 0x5d) || ctx->breakpointActivated) break;	// nop {} HEX:0x0
case 0x5e:
	if(AVR_rjmp(ctx, 0x5e, /* k */0xfb1) || ctx->breakpointActivated) break;	// rjmp {k=111110110001} HEX:0xcfb1
case 0x5f:
	if(AVR_mov(ctx, 0x5f, /* d */0x13, /* r */0x14) || ctx->breakpointActivated) break;	// mov {d=10011, r=10100} HEX:0x2f34
case 0x60:
	if(AVR_ldi(ctx, 0x60, /* K */0x8, /* d */0x2) || ctx->breakpointActivated) break;	// ldi {K=00001000, d=0010} HEX:0xe028
case 0x61:
	if(AVR_ldi(ctx, 0x61, /* K */0x66, /* d */0x9) || ctx->breakpointActivated) break;	// ldi {K=01100110, d=1001} HEX:0xe696
case 0x62:
	if(AVR_ldi(ctx, 0x62, /* K */0x89, /* d */0x8) || ctx->breakpointActivated) break;	// ldi {K=10001001, d=1000} HEX:0xe889
case 0x63:
	if(AVR_nop(ctx, 0x63) || ctx->breakpointActivated) break;	// nop {} HEX:0x0
case 0x64:
	if(AVR_nop(ctx, 0x64) || ctx->breakpointActivated) break;	// nop {} HEX:0x0
case 0x65:
	if(AVR_rjmp(ctx, 0x65, /* k */0xfaa) || ctx->breakpointActivated) break;	// rjmp {k=111110101010} HEX:0xcfaa
case 0x66:
	if(AVR_mov(ctx, 0x66, /* d */0x13, /* r */0x15) || ctx->breakpointActivated) break;	// mov {d=10011, r=10101} HEX:0x2f35
case 0x67:
	if(AVR_ldi(ctx, 0x67, /* K */0x8, /* d */0x2) || ctx->breakpointActivated) break;	// ldi {K=00001000, d=0010} HEX:0xe028
case 0x68:
	if(AVR_ldi(ctx, 0x68, /* K */0x6d, /* d */0x9) || ctx->breakpointActivated) break;	// ldi {K=01101101, d=1001} HEX:0xe69d
case 0x69:
	if(AVR_ldi(ctx, 0x69, /* K */0x89, /* d */0x8) || ctx->breakpointActivated) break;	// ldi {K=10001001, d=1000} HEX:0xe889
case 0x6a:
	if(AVR_nop(ctx, 0x6a) || ctx->breakpointActivated) break;	// nop {} HEX:0x0
case 0x6b:
	if(AVR_nop(ctx, 0x6b) || ctx->breakpointActivated) break;	// nop {} HEX:0x0
case 0x6c:
	if(AVR_rjmp(ctx, 0x6c, /* k */0xfa3) || ctx->breakpointActivated) break;	// rjmp {k=111110100011} HEX:0xcfa3
case 0x6d:
	if(AVR_mov(ctx, 0x6d, /* d */0x13, /* r */0x16) || ctx->breakpointActivated) break;	// mov {d=10011, r=10110} HEX:0x2f36
case 0x6e:
	if(AVR_ldi(ctx, 0x6e, /* K */0x8, /* d */0x2) || ctx->breakpointActivated) break;	// ldi {K=00001000, d=0010} HEX:0xe028
case 0x6f:
	if(AVR_ldi(ctx, 0x6f, /* K */0x74, /* d */0x9) || ctx->breakpointActivated) break;	// ldi {K=01110100, d=1001} HEX:0xe794
case 0x70:
	if(AVR_ldi(ctx, 0x70, /* K */0x89, /* d */0x8) || ctx->breakpointActivated) break;	// ldi {K=10001001, d=1000} HEX:0xe889
case 0x71:
	if(AVR_nop(ctx, 0x71) || ctx->breakpointActivated) break;	// nop {} HEX:0x0
case 0x72:
	if(AVR_nop(ctx, 0x72) || ctx->breakpointActivated) break;	// nop {} HEX:0x0
case 0x73:
	if(AVR_rjmp(ctx, 0x73, /* k */0xf9c) || ctx->breakpointActivated) break;	// rjmp {k=111110011100} HEX:0xcf9c
case 0x74:
	if(AVR_mov(ctx, 0x74, /* d */0x13, /* r */0x17) || ctx->breakpointActivated) break;	// mov {d=10011, r=10111} HEX:0x2f37
case 0x75:
	if(AVR_ldi(ctx, 0x75, /* K */0x8, /* d */0x2) || ctx->breakpointActivated) break;	// ldi {K=00001000, d=0010} HEX:0xe028
case 0x76:
	if(AVR_ldi(ctx, 0x76, /* K */0x7b, /* d */0x9) || ctx->breakpointActivated) break;	// ldi {K=01111011, d=1001} HEX:0xe79b
case 0x77:
	if(AVR_ldi(ctx, 0x77, /* K */0x89, /* d */0x8) || ctx->breakpointActivated) break;	// ldi {K=10001001, d=1000} HEX:0xe889
case 0x78:
	if(AVR_nop(ctx, 0x78) || ctx->breakpointActivated) break;	// nop {} HEX:0x0
case 0x79:
	if(AVR_nop(ctx, 0x79) || ctx->breakpointActivated) break;	// nop {} HEX:0x0
case 0x7a:
	if(AVR_rjmp(ctx, 0x7a, /* k */0xf95) || ctx->breakpointActivated) break;	// rjmp {k=111110010101} HEX:0xcf95
case 0x7b:
	if(AVR_mov(ctx, 0x7b, /* d */0x13, /* r */0x11) || ctx->breakpointActivated) break;	// mov {d=10011, r=10001} HEX:0x2f31
case 0x7c:
	if(AVR_ldi(ctx, 0x7c, /* K */0x0, /* d */0x1) || ctx->breakpointActivated) break;	// ldi {K=00000000, d=0001} HEX:0xe010
case 0x7d:
	if(AVR_ldi(ctx, 0x7d, /* K */0x8, /* d */0x2) || ctx->breakpointActivated) break;	// ldi {K=00001000, d=0010} HEX:0xe028
case 0x7e:
	if(AVR_ldi(ctx, 0x7e, /* K */0x82, /* d */0x9) || ctx->breakpointActivated) break;	// ldi {K=10000010, d=1001} HEX:0xe892
case 0x7f:
	if(AVR_ldi(ctx, 0x7f, /* K */0x89, /* d */0x8) || ctx->breakpointActivated) break;	// ldi {K=10001001, d=1000} HEX:0xe889
case 0x80:
	if(AVR_nop(ctx, 0x80) || ctx->breakpointActivated) break;	// nop {} HEX:0x0
case 0x81:
	if(AVR_rjmp(ctx, 0x81, /* k */0xf8e) || ctx->breakpointActivated) break;	// rjmp {k=111110001110} HEX:0xcf8e
case 0x82:
	if(AVR_out(ctx, 0x82, /* A */0x18, /* r */0x0) || ctx->breakpointActivated) break;	// out {A=011000, r=00000} HEX:0xba08
case 0x83:
	if(AVR_out(ctx, 0x83, /* A */0x17, /* r */0x0) || ctx->breakpointActivated) break;	// out {A=010111, r=00000} HEX:0xba07
case 0x84:
	if(AVR_ldi(ctx, 0x84, /* K */0x4a, /* d */0x8) || ctx->breakpointActivated) break;	// ldi {K=01001010, d=1000} HEX:0xe48a
case 0x85:
	if(AVR_sbrs(ctx, 0x85, /* b */0x1, /* r */0xc) || ctx->breakpointActivated) break;	// sbrs {b=001, r=01100} HEX:0xfec1
case 0x86:
	if(AVR_ldi(ctx, 0x86, /* K */0x82, /* d */0x8) || ctx->breakpointActivated) break;	// ldi {K=10000010, d=1000} HEX:0xe882
case 0x87:
	if(AVR_nop(ctx, 0x87) || ctx->breakpointActivated) break;	// nop {} HEX:0x0
case 0x88:
	if(AVR_rjmp(ctx, 0x88, /* k */0xf87) || ctx->breakpointActivated) break;	// rjmp {k=111110000111} HEX:0xcf87
case 0x89:
	if(AVR_ldi(ctx, 0x89, /* K */0x10, /* d */0xe) || ctx->breakpointActivated) break;	// ldi {K=00010000, d=1110} HEX:0xe1e0
case 0x8a:
	if(AVR_sbrc(ctx, 0x8a, /* b */0x0, /* r */0x13) || ctx->breakpointActivated) break;	// sbrc {b=000, r=10011} HEX:0xfd30
case 0x8b:
	if(AVR_ldi(ctx, 0x8b, /* K */0x18, /* d */0xe) || ctx->breakpointActivated) break;	// ldi {K=00011000, d=1110} HEX:0xe1e8
case 0x8c:
	if(AVR_out(ctx, 0x8c, /* A */0x18, /* r */0x1e) || ctx->breakpointActivated) break;	// out {A=011000, r=11110} HEX:0xbbe8
case 0x8d:
	if(AVR_ldi(ctx, 0x8d, /* K */0x90, /* d */0x8) || ctx->breakpointActivated) break;	// ldi {K=10010000, d=1000} HEX:0xe980
case 0x8e:
	if(AVR_lsr(ctx, 0x8e, /* d */0x13) || ctx->breakpointActivated) break;	// lsr {d=10011} HEX:0x9536
case 0x8f:
	if(AVR_rjmp(ctx, 0x8f, /* k */0xf80) || ctx->breakpointActivated) break;	// rjmp {k=111110000000} HEX:0xcf80
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
	if(AVR_ldi(ctx, 0x95, /* K */0x9e, /* d */0x8) || ctx->breakpointActivated) break;	// ldi {K=10011110, d=1000} HEX:0xe98e
case 0x96:
	if(AVR_rjmp(ctx, 0x96, /* k */0xf79) || ctx->breakpointActivated) break;	// rjmp {k=111101111001} HEX:0xcf79
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
	if(AVR_ldi(ctx, 0x9c, /* K */0x89, /* d */0x8) || ctx->breakpointActivated) break;	// ldi {K=10001001, d=1000} HEX:0xe889
case 0x9d:
	if(AVR_rjmp(ctx, 0x9d, /* k */0xf72) || ctx->breakpointActivated) break;	// rjmp {k=111101110010} HEX:0xcf72
case 0x9e:
	if(AVR_cbi(ctx, 0x9e, /* A */0x18, /* b */0x4) || ctx->breakpointActivated) break;	// cbi {A=11000, b=100} HEX:0x98c4
case 0x9f:
	if(AVR_dec(ctx, 0x9f, /* d */0x12) || ctx->breakpointActivated) break;	// dec {d=10010} HEX:0x952a
case 0xa0:
	if(AVR_brne(ctx, 0xa0, /* k */0x3) || ctx->breakpointActivated) break;	// brne {k=0000011} HEX:0xf419
case 0xa1:
	if(AVR_ldi(ctx, 0xa1, /* K */0xa6, /* d */0x8) || ctx->breakpointActivated) break;	// ldi {K=10100110, d=1000} HEX:0xea86
case 0xa2:
	if(AVR_ldi(ctx, 0xa2, /* K */0x10, /* d */0x2) || ctx->breakpointActivated) break;	// ldi {K=00010000, d=0010} HEX:0xe120
case 0xa3:
	if(AVR_rjmp(ctx, 0xa3, /* k */0xf6c) || ctx->breakpointActivated) break;	// rjmp {k=111101101100} HEX:0xcf6c
case 0xa4:
	if(AVR_ldi(ctx, 0xa4, /* K */0x97, /* d */0x8) || ctx->breakpointActivated) break;	// ldi {K=10010111, d=1000} HEX:0xe987
case 0xa5:
	if(AVR_rjmp(ctx, 0xa5, /* k */0xf6a) || ctx->breakpointActivated) break;	// rjmp {k=111101101010} HEX:0xcf6a
case 0xa6:
	if(AVR_dec(ctx, 0xa6, /* d */0x12) || ctx->breakpointActivated) break;	// dec {d=10010} HEX:0x952a
case 0xa7:
	if(AVR_brne(ctx, 0xa7, /* k */0x5) || ctx->breakpointActivated) break;	// brne {k=0000101} HEX:0xf429
case 0xa8:
	if(AVR_mov(ctx, 0xa8, /* d */0x18, /* r */0x19) || ctx->breakpointActivated) break;	// mov {d=11000, r=11001} HEX:0x2f89
case 0xa9:
	if(AVR_nop(ctx, 0xa9) || ctx->breakpointActivated) break;	// nop {} HEX:0x0
case 0xaa:
	if(AVR_nop(ctx, 0xaa) || ctx->breakpointActivated) break;	// nop {} HEX:0x0
case 0xab:
	if(AVR_nop(ctx, 0xab) || ctx->breakpointActivated) break;	// nop {} HEX:0x0
case 0xac:
	if(AVR_rjmp(ctx, 0xac, /* k */0xf63) || ctx->breakpointActivated) break;	// rjmp {k=111101100011} HEX:0xcf63
case 0xad:
	if(AVR_nop(ctx, 0xad) || ctx->breakpointActivated) break;	// nop {} HEX:0x0
case 0xae:
	if(AVR_nop(ctx, 0xae) || ctx->breakpointActivated) break;	// nop {} HEX:0x0
case 0xaf:
	if(AVR_nop(ctx, 0xaf) || ctx->breakpointActivated) break;	// nop {} HEX:0x0
case 0xb0:
	if(AVR_rjmp(ctx, 0xb0, /* k */0xf5f) || ctx->breakpointActivated) break;	// rjmp {k=111101011111} HEX:0xcf5f
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
case 0x100:
	if(AVR_rjmp(ctx, 0x100, /* k */0xf21) || ctx->breakpointActivated) break;	// rjmp {k=111100100001} HEX:0xcf21
case 0x101:
	if(AVR_rjmp(ctx, 0x101, /* k */0xf39) || ctx->breakpointActivated) break;	// rjmp {k=111100111001} HEX:0xcf39
case 0x102:
	if(AVR_rjmp(ctx, 0x102, /* k */0xf1f) || ctx->breakpointActivated) break;	// rjmp {k=111100011111} HEX:0xcf1f
case 0x103:
	if(AVR_rjmp(ctx, 0x103, /* k */0xf37) || ctx->breakpointActivated) break;	// rjmp {k=111100110111} HEX:0xcf37
case 0x104:
	if(AVR_rjmp(ctx, 0x104, /* k */0xf27) || ctx->breakpointActivated) break;	// rjmp {k=111100100111} HEX:0xcf27
case 0x105:
	if(AVR_rjmp(ctx, 0x105, /* k */0xf21) || ctx->breakpointActivated) break;	// rjmp {k=111100100001} HEX:0xcf21
case 0x106:
	if(AVR_rjmp(ctx, 0x106, /* k */0xf20) || ctx->breakpointActivated) break;	// rjmp {k=111100100000} HEX:0xcf20
case 0x107:
	if(AVR_rjmp(ctx, 0x107, /* k */0xf38) || ctx->breakpointActivated) break;	// rjmp {k=111100111000} HEX:0xcf38
case 0x108:
	if(AVR_rjmp(ctx, 0x108, /* k */0xf19) || ctx->breakpointActivated) break;	// rjmp {k=111100011001} HEX:0xcf19
case 0x109:
	if(AVR_rjmp(ctx, 0x109, /* k */0xf1d) || ctx->breakpointActivated) break;	// rjmp {k=111100011101} HEX:0xcf1d
case 0x10a:
	if(AVR_rjmp(ctx, 0x10a, /* k */0xf1c) || ctx->breakpointActivated) break;	// rjmp {k=111100011100} HEX:0xcf1c
case 0x10b:
	if(AVR_rjmp(ctx, 0x10b, /* k */0xf1b) || ctx->breakpointActivated) break;	// rjmp {k=111100011011} HEX:0xcf1b
case 0x10c:
	if(AVR_rjmp(ctx, 0x10c, /* k */0xf1f) || ctx->breakpointActivated) break;	// rjmp {k=111100011111} HEX:0xcf1f
case 0x10d:
	if(AVR_rjmp(ctx, 0x10d, /* k */0xf23) || ctx->breakpointActivated) break;	// rjmp {k=111100100011} HEX:0xcf23
case 0x10e:
	if(AVR_rjmp(ctx, 0x10e, /* k */0xf18) || ctx->breakpointActivated) break;	// rjmp {k=111100011000} HEX:0xcf18
case 0x10f:
	if(AVR_rjmp(ctx, 0x10f, /* k */0xf17) || ctx->breakpointActivated) break;	// rjmp {k=111100010111} HEX:0xcf17
case 0x110:
	if(AVR_rjmp(ctx, 0x110, /* k */0xf1b) || ctx->breakpointActivated) break;	// rjmp {k=111100011011} HEX:0xcf1b
case 0x111:
	if(AVR_rjmp(ctx, 0x111, /* k */0xf10) || ctx->breakpointActivated) break;	// rjmp {k=111100010000} HEX:0xcf10
case 0x112:
	if(AVR_rjmp(ctx, 0x112, /* k */0xf19) || ctx->breakpointActivated) break;	// rjmp {k=111100011001} HEX:0xcf19
case 0x113:
	if(AVR_rjmp(ctx, 0x113, /* k */0xf0e) || ctx->breakpointActivated) break;	// rjmp {k=111100001110} HEX:0xcf0e
case 0x114:
	if(AVR_rjmp(ctx, 0x114, /* k */0xf1c) || ctx->breakpointActivated) break;	// rjmp {k=111100011100} HEX:0xcf1c
case 0x115:
	if(AVR_rjmp(ctx, 0x115, /* k */0xf11) || ctx->breakpointActivated) break;	// rjmp {k=111100010001} HEX:0xcf11
case 0x116:
	if(AVR_rjmp(ctx, 0x116, /* k */0xf10) || ctx->breakpointActivated) break;	// rjmp {k=111100010000} HEX:0xcf10
case 0x117:
	if(AVR_rjmp(ctx, 0x117, /* k */0xf23) || ctx->breakpointActivated) break;	// rjmp {k=111100100011} HEX:0xcf23
case 0x118:
	if(AVR_rjmp(ctx, 0x118, /* k */0xf13) || ctx->breakpointActivated) break;	// rjmp {k=111100010011} HEX:0xcf13
case 0x119:
	if(AVR_rjmp(ctx, 0x119, /* k */0xf0d) || ctx->breakpointActivated) break;	// rjmp {k=111100001101} HEX:0xcf0d
case 0x11a:
	if(AVR_rjmp(ctx, 0x11a, /* k */0xf0c) || ctx->breakpointActivated) break;	// rjmp {k=111100001100} HEX:0xcf0c
case 0x11b:
	if(AVR_rjmp(ctx, 0x11b, /* k */0xf0b) || ctx->breakpointActivated) break;	// rjmp {k=111100001011} HEX:0xcf0b
case 0x11c:
	if(AVR_rjmp(ctx, 0x11c, /* k */0xf14) || ctx->breakpointActivated) break;	// rjmp {k=111100010100} HEX:0xcf14
case 0x11d:
	if(AVR_rjmp(ctx, 0x11d, /* k */0xf18) || ctx->breakpointActivated) break;	// rjmp {k=111100011000} HEX:0xcf18
case 0x11e:
	if(AVR_rjmp(ctx, 0x11e, /* k */0xf08) || ctx->breakpointActivated) break;	// rjmp {k=111100001000} HEX:0xcf08
case 0x11f:
	if(AVR_rjmp(ctx, 0x11f, /* k */0xf07) || ctx->breakpointActivated) break;	// rjmp {k=111100000111} HEX:0xcf07
case 0x120:
	if(AVR_rjmp(ctx, 0x120, /* k */0xf01) || ctx->breakpointActivated) break;	// rjmp {k=111100000001} HEX:0xcf01
case 0x121:
	if(AVR_rjmp(ctx, 0x121, /* k */0xf19) || ctx->breakpointActivated) break;	// rjmp {k=111100011001} HEX:0xcf19
case 0x122:
	if(AVR_rjmp(ctx, 0x122, /* k */0xeff) || ctx->breakpointActivated) break;	// rjmp {k=111011111111} HEX:0xceff
case 0x123:
	if(AVR_rjmp(ctx, 0x123, /* k */0xf17) || ctx->breakpointActivated) break;	// rjmp {k=111100010111} HEX:0xcf17
case 0x124:
	if(AVR_rjmp(ctx, 0x124, /* k */0xf07) || ctx->breakpointActivated) break;	// rjmp {k=111100000111} HEX:0xcf07
case 0x125:
	if(AVR_rjmp(ctx, 0x125, /* k */0xf01) || ctx->breakpointActivated) break;	// rjmp {k=111100000001} HEX:0xcf01
case 0x126:
	if(AVR_rjmp(ctx, 0x126, /* k */0xf00) || ctx->breakpointActivated) break;	// rjmp {k=111100000000} HEX:0xcf00
case 0x127:
	if(AVR_rjmp(ctx, 0x127, /* k */0xf18) || ctx->breakpointActivated) break;	// rjmp {k=111100011000} HEX:0xcf18
case 0x128:
	if(AVR_rjmp(ctx, 0x128, /* k */0xefe) || ctx->breakpointActivated) break;	// rjmp {k=111011111110} HEX:0xcefe
case 0x129:
	if(AVR_rjmp(ctx, 0x129, /* k */0xefd) || ctx->breakpointActivated) break;	// rjmp {k=111011111101} HEX:0xcefd
case 0x12a:
	if(AVR_rjmp(ctx, 0x12a, /* k */0xefc) || ctx->breakpointActivated) break;	// rjmp {k=111011111100} HEX:0xcefc
case 0x12b:
	if(AVR_rjmp(ctx, 0x12b, /* k */0xf0f) || ctx->breakpointActivated) break;	// rjmp {k=111100001111} HEX:0xcf0f
case 0x12c:
	if(AVR_rjmp(ctx, 0x12c, /* k */0xefa) || ctx->breakpointActivated) break;	// rjmp {k=111011111010} HEX:0xcefa
case 0x12d:
	if(AVR_rjmp(ctx, 0x12d, /* k */0xef9) || ctx->breakpointActivated) break;	// rjmp {k=111011111001} HEX:0xcef9
case 0x12e:
	if(AVR_rjmp(ctx, 0x12e, /* k */0xf16) || ctx->breakpointActivated) break;	// rjmp {k=111100010110} HEX:0xcf16
case 0x12f:
	if(AVR_rjmp(ctx, 0x12f, /* k */0xf10) || ctx->breakpointActivated) break;	// rjmp {k=111100010000} HEX:0xcf10
case 0x130:
	if(AVR_rjmp(ctx, 0x130, /* k */0xefb) || ctx->breakpointActivated) break;	// rjmp {k=111011111011} HEX:0xcefb
case 0x131:
	if(AVR_rjmp(ctx, 0x131, /* k */0xef0) || ctx->breakpointActivated) break;	// rjmp {k=111011110000} HEX:0xcef0
case 0x132:
	if(AVR_rjmp(ctx, 0x132, /* k */0xef9) || ctx->breakpointActivated) break;	// rjmp {k=111011111001} HEX:0xcef9
case 0x133:
	if(AVR_rjmp(ctx, 0x133, /* k */0xeee) || ctx->breakpointActivated) break;	// rjmp {k=111011101110} HEX:0xceee
case 0x134:
	if(AVR_rjmp(ctx, 0x134, /* k */0xefc) || ctx->breakpointActivated) break;	// rjmp {k=111011111100} HEX:0xcefc
case 0x135:
	if(AVR_rjmp(ctx, 0x135, /* k */0xef1) || ctx->breakpointActivated) break;	// rjmp {k=111011110001} HEX:0xcef1
case 0x136:
	if(AVR_rjmp(ctx, 0x136, /* k */0xef0) || ctx->breakpointActivated) break;	// rjmp {k=111011110000} HEX:0xcef0
case 0x137:
	if(AVR_rjmp(ctx, 0x137, /* k */0xf03) || ctx->breakpointActivated) break;	// rjmp {k=111100000011} HEX:0xcf03
case 0x138:
	if(AVR_rjmp(ctx, 0x138, /* k */0xeee) || ctx->breakpointActivated) break;	// rjmp {k=111011101110} HEX:0xceee
case 0x139:
	if(AVR_rjmp(ctx, 0x139, /* k */0xeed) || ctx->breakpointActivated) break;	// rjmp {k=111011101101} HEX:0xceed
case 0x13a:
	if(AVR_rjmp(ctx, 0x13a, /* k */0xeec) || ctx->breakpointActivated) break;	// rjmp {k=111011101100} HEX:0xceec
case 0x13b:
	if(AVR_rjmp(ctx, 0x13b, /* k */0xee6) || ctx->breakpointActivated) break;	// rjmp {k=111011100110} HEX:0xcee6
case 0x13c:
	if(AVR_rjmp(ctx, 0x13c, /* k */0xeea) || ctx->breakpointActivated) break;	// rjmp {k=111011101010} HEX:0xceea
case 0x13d:
	if(AVR_rjmp(ctx, 0x13d, /* k */0xee9) || ctx->breakpointActivated) break;	// rjmp {k=111011101001} HEX:0xcee9
case 0x13e:
	if(AVR_rjmp(ctx, 0x13e, /* k */0xf01) || ctx->breakpointActivated) break;	// rjmp {k=111100000001} HEX:0xcf01
case 0x13f:
	if(AVR_rjmp(ctx, 0x13f, /* k */0xefb) || ctx->breakpointActivated) break;	// rjmp {k=111011111011} HEX:0xcefb
case 0x140:
	if(AVR_rjmp(ctx, 0x140, /* k */0xefa) || ctx->breakpointActivated) break;	// rjmp {k=111011111010} HEX:0xcefa
case 0x141:
	if(AVR_rjmp(ctx, 0x141, /* k */0xefe) || ctx->breakpointActivated) break;	// rjmp {k=111011111110} HEX:0xcefe
case 0x142:
	if(AVR_rjmp(ctx, 0x142, /* k */0xef8) || ctx->breakpointActivated) break;	// rjmp {k=111011111000} HEX:0xcef8
case 0x143:
	if(AVR_rjmp(ctx, 0x143, /* k */0xefc) || ctx->breakpointActivated) break;	// rjmp {k=111011111100} HEX:0xcefc
case 0x144:
	if(AVR_rjmp(ctx, 0x144, /* k */0xedd) || ctx->breakpointActivated) break;	// rjmp {k=111011011101} HEX:0xcedd
case 0x145:
	if(AVR_rjmp(ctx, 0x145, /* k */0xee1) || ctx->breakpointActivated) break;	// rjmp {k=111011100001} HEX:0xcee1
case 0x146:
	if(AVR_rjmp(ctx, 0x146, /* k */0xee0) || ctx->breakpointActivated) break;	// rjmp {k=111011100000} HEX:0xcee0
case 0x147:
	if(AVR_rjmp(ctx, 0x147, /* k */0xefd) || ctx->breakpointActivated) break;	// rjmp {k=111011111101} HEX:0xcefd
case 0x148:
	if(AVR_rjmp(ctx, 0x148, /* k */0xef2) || ctx->breakpointActivated) break;	// rjmp {k=111011110010} HEX:0xcef2
case 0x149:
	if(AVR_rjmp(ctx, 0x149, /* k */0xedd) || ctx->breakpointActivated) break;	// rjmp {k=111011011101} HEX:0xcedd
case 0x14a:
	if(AVR_rjmp(ctx, 0x14a, /* k */0xedc) || ctx->breakpointActivated) break;	// rjmp {k=111011011100} HEX:0xcedc
case 0x14b:
	if(AVR_rjmp(ctx, 0x14b, /* k */0xedb) || ctx->breakpointActivated) break;	// rjmp {k=111011011011} HEX:0xcedb
case 0x14c:
	if(AVR_rjmp(ctx, 0x14c, /* k */0xed5) || ctx->breakpointActivated) break;	// rjmp {k=111011010101} HEX:0xced5
case 0x14d:
	if(AVR_rjmp(ctx, 0x14d, /* k */0xede) || ctx->breakpointActivated) break;	// rjmp {k=111011011110} HEX:0xcede
case 0x14e:
	if(AVR_rjmp(ctx, 0x14e, /* k */0xed8) || ctx->breakpointActivated) break;	// rjmp {k=111011011000} HEX:0xced8
case 0x14f:
	if(AVR_rjmp(ctx, 0x14f, /* k */0xed7) || ctx->breakpointActivated) break;	// rjmp {k=111011010111} HEX:0xced7
case 0x150:
	if(AVR_rjmp(ctx, 0x150, /* k */0xed6) || ctx->breakpointActivated) break;	// rjmp {k=111011010110} HEX:0xced6
case 0x151:
	if(AVR_rjmp(ctx, 0x151, /* k */0xed5) || ctx->breakpointActivated) break;	// rjmp {k=111011010101} HEX:0xced5
case 0x152:
	if(AVR_rjmp(ctx, 0x152, /* k */0xed4) || ctx->breakpointActivated) break;	// rjmp {k=111011010100} HEX:0xced4
case 0x153:
	if(AVR_rjmp(ctx, 0x153, /* k */0xed3) || ctx->breakpointActivated) break;	// rjmp {k=111011010011} HEX:0xced3
case 0x154:
	if(AVR_rjmp(ctx, 0x154, /* k */0xed2) || ctx->breakpointActivated) break;	// rjmp {k=111011010010} HEX:0xced2
case 0x155:
	if(AVR_rjmp(ctx, 0x155, /* k */0xed1) || ctx->breakpointActivated) break;	// rjmp {k=111011010001} HEX:0xced1
case 0x156:
	if(AVR_rjmp(ctx, 0x156, /* k */0xed0) || ctx->breakpointActivated) break;	// rjmp {k=111011010000} HEX:0xced0
case 0x157:
	if(AVR_rjmp(ctx, 0x157, /* k */0xecf) || ctx->breakpointActivated) break;	// rjmp {k=111011001111} HEX:0xcecf
case 0x158:
	if(AVR_rjmp(ctx, 0x158, /* k */0xece) || ctx->breakpointActivated) break;	// rjmp {k=111011001110} HEX:0xcece
case 0x159:
	if(AVR_rjmp(ctx, 0x159, /* k */0xecd) || ctx->breakpointActivated) break;	// rjmp {k=111011001101} HEX:0xcecd
case 0x15a:
	if(AVR_rjmp(ctx, 0x15a, /* k */0xecc) || ctx->breakpointActivated) break;	// rjmp {k=111011001100} HEX:0xcecc
case 0x15b:
	if(AVR_rjmp(ctx, 0x15b, /* k */0xecb) || ctx->breakpointActivated) break;	// rjmp {k=111011001011} HEX:0xcecb
case 0x15c:
	if(AVR_rjmp(ctx, 0x15c, /* k */0xeca) || ctx->breakpointActivated) break;	// rjmp {k=111011001010} HEX:0xceca
case 0x15d:
	if(AVR_rjmp(ctx, 0x15d, /* k */0xec9) || ctx->breakpointActivated) break;	// rjmp {k=111011001001} HEX:0xcec9
case 0x15e:
	if(AVR_rjmp(ctx, 0x15e, /* k */0xec8) || ctx->breakpointActivated) break;	// rjmp {k=111011001000} HEX:0xcec8
case 0x15f:
	if(AVR_rjmp(ctx, 0x15f, /* k */0xec7) || ctx->breakpointActivated) break;	// rjmp {k=111011000111} HEX:0xcec7
case 0x160:
	if(AVR_rjmp(ctx, 0x160, /* k */0xec6) || ctx->breakpointActivated) break;	// rjmp {k=111011000110} HEX:0xcec6
case 0x161:
	if(AVR_rjmp(ctx, 0x161, /* k */0xec5) || ctx->breakpointActivated) break;	// rjmp {k=111011000101} HEX:0xcec5
case 0x162:
	if(AVR_rjmp(ctx, 0x162, /* k */0xec4) || ctx->breakpointActivated) break;	// rjmp {k=111011000100} HEX:0xcec4
case 0x163:
	if(AVR_rjmp(ctx, 0x163, /* k */0xec3) || ctx->breakpointActivated) break;	// rjmp {k=111011000011} HEX:0xcec3
case 0x164:
	if(AVR_rjmp(ctx, 0x164, /* k */0xec2) || ctx->breakpointActivated) break;	// rjmp {k=111011000010} HEX:0xcec2
case 0x165:
	if(AVR_rjmp(ctx, 0x165, /* k */0xec1) || ctx->breakpointActivated) break;	// rjmp {k=111011000001} HEX:0xcec1
case 0x166:
	if(AVR_rjmp(ctx, 0x166, /* k */0xec0) || ctx->breakpointActivated) break;	// rjmp {k=111011000000} HEX:0xcec0
case 0x167:
	if(AVR_rjmp(ctx, 0x167, /* k */0xebf) || ctx->breakpointActivated) break;	// rjmp {k=111010111111} HEX:0xcebf
case 0x168:
	if(AVR_rjmp(ctx, 0x168, /* k */0xebe) || ctx->breakpointActivated) break;	// rjmp {k=111010111110} HEX:0xcebe
case 0x169:
	if(AVR_rjmp(ctx, 0x169, /* k */0xebd) || ctx->breakpointActivated) break;	// rjmp {k=111010111101} HEX:0xcebd
case 0x16a:
	if(AVR_rjmp(ctx, 0x16a, /* k */0xebc) || ctx->breakpointActivated) break;	// rjmp {k=111010111100} HEX:0xcebc
case 0x16b:
	if(AVR_rjmp(ctx, 0x16b, /* k */0xebb) || ctx->breakpointActivated) break;	// rjmp {k=111010111011} HEX:0xcebb
case 0x16c:
	if(AVR_rjmp(ctx, 0x16c, /* k */0xeba) || ctx->breakpointActivated) break;	// rjmp {k=111010111010} HEX:0xceba
case 0x16d:
	if(AVR_rjmp(ctx, 0x16d, /* k */0xeb9) || ctx->breakpointActivated) break;	// rjmp {k=111010111001} HEX:0xceb9
case 0x16e:
	if(AVR_rjmp(ctx, 0x16e, /* k */0xeb8) || ctx->breakpointActivated) break;	// rjmp {k=111010111000} HEX:0xceb8
case 0x16f:
	if(AVR_rjmp(ctx, 0x16f, /* k */0xeb7) || ctx->breakpointActivated) break;	// rjmp {k=111010110111} HEX:0xceb7
case 0x170:
	if(AVR_rjmp(ctx, 0x170, /* k */0xec0) || ctx->breakpointActivated) break;	// rjmp {k=111011000000} HEX:0xcec0
case 0x171:
	if(AVR_rjmp(ctx, 0x171, /* k */0xeba) || ctx->breakpointActivated) break;	// rjmp {k=111010111010} HEX:0xceba
case 0x172:
	if(AVR_rjmp(ctx, 0x172, /* k */0xebe) || ctx->breakpointActivated) break;	// rjmp {k=111010111110} HEX:0xcebe
case 0x173:
	if(AVR_rjmp(ctx, 0x173, /* k */0xeb8) || ctx->breakpointActivated) break;	// rjmp {k=111010111000} HEX:0xceb8
case 0x174:
	if(AVR_rjmp(ctx, 0x174, /* k */0xec1) || ctx->breakpointActivated) break;	// rjmp {k=111011000001} HEX:0xcec1
case 0x175:
	if(AVR_rjmp(ctx, 0x175, /* k */0xeb1) || ctx->breakpointActivated) break;	// rjmp {k=111010110001} HEX:0xceb1
case 0x176:
	if(AVR_rjmp(ctx, 0x176, /* k */0xeb0) || ctx->breakpointActivated) break;	// rjmp {k=111010110000} HEX:0xceb0
case 0x177:
	if(AVR_rjmp(ctx, 0x177, /* k */0xeaa) || ctx->breakpointActivated) break;	// rjmp {k=111010101010} HEX:0xceaa
case 0x178:
	if(AVR_rjmp(ctx, 0x178, /* k */0xeae) || ctx->breakpointActivated) break;	// rjmp {k=111010101110} HEX:0xceae
case 0x179:
	if(AVR_rjmp(ctx, 0x179, /* k */0xead) || ctx->breakpointActivated) break;	// rjmp {k=111010101101} HEX:0xcead
case 0x17a:
	if(AVR_rjmp(ctx, 0x17a, /* k */0xeac) || ctx->breakpointActivated) break;	// rjmp {k=111010101100} HEX:0xceac
case 0x17b:
	if(AVR_rjmp(ctx, 0x17b, /* k */0xeb0) || ctx->breakpointActivated) break;	// rjmp {k=111010110000} HEX:0xceb0
case 0x17c:
	if(AVR_rjmp(ctx, 0x17c, /* k */0xeaa) || ctx->breakpointActivated) break;	// rjmp {k=111010101010} HEX:0xceaa
case 0x17d:
	if(AVR_rjmp(ctx, 0x17d, /* k */0xea9) || ctx->breakpointActivated) break;	// rjmp {k=111010101001} HEX:0xcea9
case 0x17e:
	if(AVR_rjmp(ctx, 0x17e, /* k */0xebc) || ctx->breakpointActivated) break;	// rjmp {k=111010111100} HEX:0xcebc
case 0x17f:
	if(AVR_rjmp(ctx, 0x17f, /* k */0xea2) || ctx->breakpointActivated) break;	// rjmp {k=111010100010} HEX:0xcea2
case 0x180:
	if(AVR_rjmp(ctx, 0x180, /* k */0xea1) || ctx->breakpointActivated) break;	// rjmp {k=111010100001} HEX:0xcea1
case 0x181:
	if(AVR_rjmp(ctx, 0x181, /* k */0xeb9) || ctx->breakpointActivated) break;	// rjmp {k=111010111001} HEX:0xceb9
case 0x182:
	if(AVR_rjmp(ctx, 0x182, /* k */0xea4) || ctx->breakpointActivated) break;	// rjmp {k=111010100100} HEX:0xcea4
case 0x183:
	if(AVR_rjmp(ctx, 0x183, /* k */0xea3) || ctx->breakpointActivated) break;	// rjmp {k=111010100011} HEX:0xcea3
case 0x184:
	if(AVR_rjmp(ctx, 0x184, /* k */0xea7) || ctx->breakpointActivated) break;	// rjmp {k=111010100111} HEX:0xcea7
case 0x185:
	if(AVR_rjmp(ctx, 0x185, /* k */0xea1) || ctx->breakpointActivated) break;	// rjmp {k=111010100001} HEX:0xcea1
case 0x186:
	if(AVR_rjmp(ctx, 0x186, /* k */0xea0) || ctx->breakpointActivated) break;	// rjmp {k=111010100000} HEX:0xcea0
case 0x187:
	if(AVR_rjmp(ctx, 0x187, /* k */0xe9f) || ctx->breakpointActivated) break;	// rjmp {k=111010011111} HEX:0xce9f
case 0x188:
	if(AVR_rjmp(ctx, 0x188, /* k */0xe99) || ctx->breakpointActivated) break;	// rjmp {k=111010011001} HEX:0xce99
case 0x189:
	if(AVR_rjmp(ctx, 0x189, /* k */0xe9d) || ctx->breakpointActivated) break;	// rjmp {k=111010011101} HEX:0xce9d
case 0x18a:
	if(AVR_rjmp(ctx, 0x18a, /* k */0xe9c) || ctx->breakpointActivated) break;	// rjmp {k=111010011100} HEX:0xce9c
case 0x18b:
	if(AVR_rjmp(ctx, 0x18b, /* k */0xeaa) || ctx->breakpointActivated) break;	// rjmp {k=111010101010} HEX:0xceaa
case 0x18c:
	if(AVR_rjmp(ctx, 0x18c, /* k */0xe9f) || ctx->breakpointActivated) break;	// rjmp {k=111010011111} HEX:0xce9f
case 0x18d:
	if(AVR_rjmp(ctx, 0x18d, /* k */0xea3) || ctx->breakpointActivated) break;	// rjmp {k=111010100011} HEX:0xcea3
case 0x18e:
	if(AVR_rjmp(ctx, 0x18e, /* k */0xe9d) || ctx->breakpointActivated) break;	// rjmp {k=111010011101} HEX:0xce9d
case 0x18f:
	if(AVR_rjmp(ctx, 0x18f, /* k */0xea1) || ctx->breakpointActivated) break;	// rjmp {k=111010100001} HEX:0xcea1
case 0x190:
	if(AVR_rjmp(ctx, 0x190, /* k */0xe96) || ctx->breakpointActivated) break;	// rjmp {k=111010010110} HEX:0xce96
case 0x191:
	if(AVR_rjmp(ctx, 0x191, /* k */0xe95) || ctx->breakpointActivated) break;	// rjmp {k=111010010101} HEX:0xce95
case 0x192:
	if(AVR_rjmp(ctx, 0x192, /* k */0xe94) || ctx->breakpointActivated) break;	// rjmp {k=111010010100} HEX:0xce94
case 0x193:
	if(AVR_rjmp(ctx, 0x193, /* k */0xe93) || ctx->breakpointActivated) break;	// rjmp {k=111010010011} HEX:0xce93
case 0x194:
	if(AVR_rjmp(ctx, 0x194, /* k */0xe92) || ctx->breakpointActivated) break;	// rjmp {k=111010010010} HEX:0xce92
case 0x195:
	if(AVR_rjmp(ctx, 0x195, /* k */0xe91) || ctx->breakpointActivated) break;	// rjmp {k=111010010001} HEX:0xce91
case 0x196:
	if(AVR_rjmp(ctx, 0x196, /* k */0xe90) || ctx->breakpointActivated) break;	// rjmp {k=111010010000} HEX:0xce90
case 0x197:
	if(AVR_rjmp(ctx, 0x197, /* k */0xe8f) || ctx->breakpointActivated) break;	// rjmp {k=111010001111} HEX:0xce8f
case 0x198:
	if(AVR_rjmp(ctx, 0x198, /* k */0xe8e) || ctx->breakpointActivated) break;	// rjmp {k=111010001110} HEX:0xce8e
case 0x199:
	if(AVR_rjmp(ctx, 0x199, /* k */0xe8d) || ctx->breakpointActivated) break;	// rjmp {k=111010001101} HEX:0xce8d
case 0x19a:
	if(AVR_rjmp(ctx, 0x19a, /* k */0xe8c) || ctx->breakpointActivated) break;	// rjmp {k=111010001100} HEX:0xce8c
case 0x19b:
	if(AVR_rjmp(ctx, 0x19b, /* k */0xe8b) || ctx->breakpointActivated) break;	// rjmp {k=111010001011} HEX:0xce8b
case 0x19c:
	if(AVR_rjmp(ctx, 0x19c, /* k */0xe8a) || ctx->breakpointActivated) break;	// rjmp {k=111010001010} HEX:0xce8a
case 0x19d:
	if(AVR_rjmp(ctx, 0x19d, /* k */0xe89) || ctx->breakpointActivated) break;	// rjmp {k=111010001001} HEX:0xce89
case 0x19e:
	if(AVR_rjmp(ctx, 0x19e, /* k */0xe88) || ctx->breakpointActivated) break;	// rjmp {k=111010001000} HEX:0xce88
case 0x19f:
	if(AVR_rjmp(ctx, 0x19f, /* k */0xe87) || ctx->breakpointActivated) break;	// rjmp {k=111010000111} HEX:0xce87
case 0x1a0:
	if(AVR_rjmp(ctx, 0x1a0, /* k */0xe86) || ctx->breakpointActivated) break;	// rjmp {k=111010000110} HEX:0xce86
case 0x1a1:
	if(AVR_rjmp(ctx, 0x1a1, /* k */0xe85) || ctx->breakpointActivated) break;	// rjmp {k=111010000101} HEX:0xce85
case 0x1a2:
	if(AVR_rjmp(ctx, 0x1a2, /* k */0xe84) || ctx->breakpointActivated) break;	// rjmp {k=111010000100} HEX:0xce84
case 0x1a3:
	if(AVR_rjmp(ctx, 0x1a3, /* k */0xe83) || ctx->breakpointActivated) break;	// rjmp {k=111010000011} HEX:0xce83
case 0x1a4:
	if(AVR_rjmp(ctx, 0x1a4, /* k */0xe82) || ctx->breakpointActivated) break;	// rjmp {k=111010000010} HEX:0xce82
case 0x1a5:
	if(AVR_rjmp(ctx, 0x1a5, /* k */0xe81) || ctx->breakpointActivated) break;	// rjmp {k=111010000001} HEX:0xce81
case 0x1a6:
	if(AVR_rjmp(ctx, 0x1a6, /* k */0xe80) || ctx->breakpointActivated) break;	// rjmp {k=111010000000} HEX:0xce80
case 0x1a7:
	if(AVR_rjmp(ctx, 0x1a7, /* k */0xe7f) || ctx->breakpointActivated) break;	// rjmp {k=111001111111} HEX:0xce7f
case 0x1a8:
	if(AVR_rjmp(ctx, 0x1a8, /* k */0xe7e) || ctx->breakpointActivated) break;	// rjmp {k=111001111110} HEX:0xce7e
case 0x1a9:
	if(AVR_rjmp(ctx, 0x1a9, /* k */0xe7d) || ctx->breakpointActivated) break;	// rjmp {k=111001111101} HEX:0xce7d
case 0x1aa:
	if(AVR_rjmp(ctx, 0x1aa, /* k */0xe7c) || ctx->breakpointActivated) break;	// rjmp {k=111001111100} HEX:0xce7c
case 0x1ab:
	if(AVR_rjmp(ctx, 0x1ab, /* k */0xe7b) || ctx->breakpointActivated) break;	// rjmp {k=111001111011} HEX:0xce7b
case 0x1ac:
	if(AVR_rjmp(ctx, 0x1ac, /* k */0xe7a) || ctx->breakpointActivated) break;	// rjmp {k=111001111010} HEX:0xce7a
case 0x1ad:
	if(AVR_rjmp(ctx, 0x1ad, /* k */0xe79) || ctx->breakpointActivated) break;	// rjmp {k=111001111001} HEX:0xce79
case 0x1ae:
	if(AVR_rjmp(ctx, 0x1ae, /* k */0xe78) || ctx->breakpointActivated) break;	// rjmp {k=111001111000} HEX:0xce78
case 0x1af:
	if(AVR_rjmp(ctx, 0x1af, /* k */0xe77) || ctx->breakpointActivated) break;	// rjmp {k=111001110111} HEX:0xce77
case 0x1b0:
	if(AVR_rjmp(ctx, 0x1b0, /* k */0xe76) || ctx->breakpointActivated) break;	// rjmp {k=111001110110} HEX:0xce76
case 0x1b1:
	if(AVR_rjmp(ctx, 0x1b1, /* k */0xe75) || ctx->breakpointActivated) break;	// rjmp {k=111001110101} HEX:0xce75
case 0x1b2:
	if(AVR_rjmp(ctx, 0x1b2, /* k */0xe79) || ctx->breakpointActivated) break;	// rjmp {k=111001111001} HEX:0xce79
case 0x1b3:
	if(AVR_rjmp(ctx, 0x1b3, /* k */0xe6e) || ctx->breakpointActivated) break;	// rjmp {k=111001101110} HEX:0xce6e
case 0x1b4:
	if(AVR_rjmp(ctx, 0x1b4, /* k */0xe72) || ctx->breakpointActivated) break;	// rjmp {k=111001110010} HEX:0xce72
case 0x1b5:
	if(AVR_rjmp(ctx, 0x1b5, /* k */0xe71) || ctx->breakpointActivated) break;	// rjmp {k=111001110001} HEX:0xce71
case 0x1b6:
	if(AVR_rjmp(ctx, 0x1b6, /* k */0xe70) || ctx->breakpointActivated) break;	// rjmp {k=111001110000} HEX:0xce70
case 0x1b7:
	if(AVR_rjmp(ctx, 0x1b7, /* k */0xe83) || ctx->breakpointActivated) break;	// rjmp {k=111010000011} HEX:0xce83
case 0x1b8:
	if(AVR_rjmp(ctx, 0x1b8, /* k */0xe8c) || ctx->breakpointActivated) break;	// rjmp {k=111010001100} HEX:0xce8c
case 0x1b9:
	if(AVR_rjmp(ctx, 0x1b9, /* k */0xe6d) || ctx->breakpointActivated) break;	// rjmp {k=111001101101} HEX:0xce6d
case 0x1ba:
	if(AVR_rjmp(ctx, 0x1ba, /* k */0xe6c) || ctx->breakpointActivated) break;	// rjmp {k=111001101100} HEX:0xce6c
case 0x1bb:
	if(AVR_rjmp(ctx, 0x1bb, /* k */0xe66) || ctx->breakpointActivated) break;	// rjmp {k=111001100110} HEX:0xce66
case 0x1bc:
	if(AVR_rjmp(ctx, 0x1bc, /* k */0xe83) || ctx->breakpointActivated) break;	// rjmp {k=111010000011} HEX:0xce83
case 0x1bd:
	if(AVR_rjmp(ctx, 0x1bd, /* k */0xe7d) || ctx->breakpointActivated) break;	// rjmp {k=111001111101} HEX:0xce7d
case 0x1be:
	if(AVR_rjmp(ctx, 0x1be, /* k */0xe81) || ctx->breakpointActivated) break;	// rjmp {k=111010000001} HEX:0xce81
case 0x1bf:
	if(AVR_rjmp(ctx, 0x1bf, /* k */0xe7b) || ctx->breakpointActivated) break;	// rjmp {k=111001111011} HEX:0xce7b
case 0x1c0:
	if(AVR_rjmp(ctx, 0x1c0, /* k */0xe7a) || ctx->breakpointActivated) break;	// rjmp {k=111001111010} HEX:0xce7a
case 0x1c1:
	if(AVR_rjmp(ctx, 0x1c1, /* k */0xe7e) || ctx->breakpointActivated) break;	// rjmp {k=111001111110} HEX:0xce7e
case 0x1c2:
	if(AVR_rjmp(ctx, 0x1c2, /* k */0xe64) || ctx->breakpointActivated) break;	// rjmp {k=111001100100} HEX:0xce64
case 0x1c3:
	if(AVR_rjmp(ctx, 0x1c3, /* k */0xe63) || ctx->breakpointActivated) break;	// rjmp {k=111001100011} HEX:0xce63
case 0x1c4:
	if(AVR_rjmp(ctx, 0x1c4, /* k */0xe5d) || ctx->breakpointActivated) break;	// rjmp {k=111001011101} HEX:0xce5d
case 0x1c5:
	if(AVR_rjmp(ctx, 0x1c5, /* k */0xe61) || ctx->breakpointActivated) break;	// rjmp {k=111001100001} HEX:0xce61
case 0x1c6:
	if(AVR_rjmp(ctx, 0x1c6, /* k */0xe60) || ctx->breakpointActivated) break;	// rjmp {k=111001100000} HEX:0xce60
case 0x1c7:
	if(AVR_rjmp(ctx, 0x1c7, /* k */0xe5f) || ctx->breakpointActivated) break;	// rjmp {k=111001011111} HEX:0xce5f
case 0x1c8:
	if(AVR_rjmp(ctx, 0x1c8, /* k */0xe72) || ctx->breakpointActivated) break;	// rjmp {k=111001110010} HEX:0xce72
case 0x1c9:
	if(AVR_rjmp(ctx, 0x1c9, /* k */0xe5d) || ctx->breakpointActivated) break;	// rjmp {k=111001011101} HEX:0xce5d
case 0x1ca:
	if(AVR_rjmp(ctx, 0x1ca, /* k */0xe5c) || ctx->breakpointActivated) break;	// rjmp {k=111001011100} HEX:0xce5c
case 0x1cb:
	if(AVR_rjmp(ctx, 0x1cb, /* k */0xe65) || ctx->breakpointActivated) break;	// rjmp {k=111001100101} HEX:0xce65
case 0x1cc:
	if(AVR_rjmp(ctx, 0x1cc, /* k */0xe55) || ctx->breakpointActivated) break;	// rjmp {k=111001010101} HEX:0xce55
case 0x1cd:
	if(AVR_rjmp(ctx, 0x1cd, /* k */0xe5e) || ctx->breakpointActivated) break;	// rjmp {k=111001011110} HEX:0xce5e
case 0x1ce:
	if(AVR_rjmp(ctx, 0x1ce, /* k */0xe53) || ctx->breakpointActivated) break;	// rjmp {k=111001010011} HEX:0xce53
case 0x1cf:
	if(AVR_rjmp(ctx, 0x1cf, /* k */0xe5c) || ctx->breakpointActivated) break;	// rjmp {k=111001011100} HEX:0xce5c
case 0x1d0:
	if(AVR_rjmp(ctx, 0x1d0, /* k */0xe6f) || ctx->breakpointActivated) break;	// rjmp {k=111001101111} HEX:0xce6f
case 0x1d1:
	if(AVR_rjmp(ctx, 0x1d1, /* k */0xe73) || ctx->breakpointActivated) break;	// rjmp {k=111001110011} HEX:0xce73
case 0x1d2:
	if(AVR_rjmp(ctx, 0x1d2, /* k */0xe54) || ctx->breakpointActivated) break;	// rjmp {k=111001010100} HEX:0xce54
case 0x1d3:
	if(AVR_rjmp(ctx, 0x1d3, /* k */0xe53) || ctx->breakpointActivated) break;	// rjmp {k=111001010011} HEX:0xce53
case 0x1d4:
	if(AVR_rjmp(ctx, 0x1d4, /* k */0xe66) || ctx->breakpointActivated) break;	// rjmp {k=111001100110} HEX:0xce66
case 0x1d5:
	if(AVR_rjmp(ctx, 0x1d5, /* k */0xe51) || ctx->breakpointActivated) break;	// rjmp {k=111001010001} HEX:0xce51
case 0x1d6:
	if(AVR_rjmp(ctx, 0x1d6, /* k */0xe50) || ctx->breakpointActivated) break;	// rjmp {k=111001010000} HEX:0xce50
case 0x1d7:
	if(AVR_rjmp(ctx, 0x1d7, /* k */0xe4f) || ctx->breakpointActivated) break;	// rjmp {k=111001001111} HEX:0xce4f
case 0x1d8:
	if(AVR_rjmp(ctx, 0x1d8, /* k */0xe67) || ctx->breakpointActivated) break;	// rjmp {k=111001100111} HEX:0xce67
case 0x1d9:
	if(AVR_rjmp(ctx, 0x1d9, /* k */0xe4d) || ctx->breakpointActivated) break;	// rjmp {k=111001001101} HEX:0xce4d
case 0x1da:
	if(AVR_rjmp(ctx, 0x1da, /* k */0xe4c) || ctx->breakpointActivated) break;	// rjmp {k=111001001100} HEX:0xce4c
case 0x1db:
	if(AVR_rjmp(ctx, 0x1db, /* k */0xe50) || ctx->breakpointActivated) break;	// rjmp {k=111001010000} HEX:0xce50
case 0x1dc:
	if(AVR_rjmp(ctx, 0x1dc, /* k */0xe5e) || ctx->breakpointActivated) break;	// rjmp {k=111001011110} HEX:0xce5e
case 0x1dd:
	if(AVR_rjmp(ctx, 0x1dd, /* k */0xe44) || ctx->breakpointActivated) break;	// rjmp {k=111001000100} HEX:0xce44
case 0x1de:
	if(AVR_rjmp(ctx, 0x1de, /* k */0xe5c) || ctx->breakpointActivated) break;	// rjmp {k=111001011100} HEX:0xce5c
case 0x1df:
	if(AVR_rjmp(ctx, 0x1df, /* k */0xe42) || ctx->breakpointActivated) break;	// rjmp {k=111001000010} HEX:0xce42
case 0x1e0:
	if(AVR_rjmp(ctx, 0x1e0, /* k */0xe46) || ctx->breakpointActivated) break;	// rjmp {k=111001000110} HEX:0xce46
case 0x1e1:
	if(AVR_rjmp(ctx, 0x1e1, /* k */0xe45) || ctx->breakpointActivated) break;	// rjmp {k=111001000101} HEX:0xce45
case 0x1e2:
	if(AVR_rjmp(ctx, 0x1e2, /* k */0xe53) || ctx->breakpointActivated) break;	// rjmp {k=111001010011} HEX:0xce53
case 0x1e3:
	if(AVR_rjmp(ctx, 0x1e3, /* k */0xe4d) || ctx->breakpointActivated) break;	// rjmp {k=111001001101} HEX:0xce4d
case 0x1e4:
	if(AVR_rjmp(ctx, 0x1e4, /* k */0xe42) || ctx->breakpointActivated) break;	// rjmp {k=111001000010} HEX:0xce42
case 0x1e5:
	if(AVR_rjmp(ctx, 0x1e5, /* k */0xe41) || ctx->breakpointActivated) break;	// rjmp {k=111001000001} HEX:0xce41
case 0x1e6:
	if(AVR_rjmp(ctx, 0x1e6, /* k */0xe40) || ctx->breakpointActivated) break;	// rjmp {k=111001000000} HEX:0xce40
case 0x1e7:
	if(AVR_rjmp(ctx, 0x1e7, /* k */0xe44) || ctx->breakpointActivated) break;	// rjmp {k=111001000100} HEX:0xce44
case 0x1e8:
	if(AVR_rjmp(ctx, 0x1e8, /* k */0xe52) || ctx->breakpointActivated) break;	// rjmp {k=111001010010} HEX:0xce52
case 0x1e9:
	if(AVR_rjmp(ctx, 0x1e9, /* k */0xe3d) || ctx->breakpointActivated) break;	// rjmp {k=111000111101} HEX:0xce3d
case 0x1ea:
	if(AVR_rjmp(ctx, 0x1ea, /* k */0xe3c) || ctx->breakpointActivated) break;	// rjmp {k=111000111100} HEX:0xce3c
case 0x1eb:
	if(AVR_rjmp(ctx, 0x1eb, /* k */0xe45) || ctx->breakpointActivated) break;	// rjmp {k=111001000101} HEX:0xce45
case 0x1ec:
	if(AVR_rjmp(ctx, 0x1ec, /* k */0xe35) || ctx->breakpointActivated) break;	// rjmp {k=111000110101} HEX:0xce35
case 0x1ed:
	if(AVR_rjmp(ctx, 0x1ed, /* k */0xe3e) || ctx->breakpointActivated) break;	// rjmp {k=111000111110} HEX:0xce3e
case 0x1ee:
	if(AVR_rjmp(ctx, 0x1ee, /* k */0xe33) || ctx->breakpointActivated) break;	// rjmp {k=111000110011} HEX:0xce33
case 0x1ef:
	if(AVR_rjmp(ctx, 0x1ef, /* k */0xe3c) || ctx->breakpointActivated) break;	// rjmp {k=111000111100} HEX:0xce3c
case 0x1f0:
	if(AVR_rjmp(ctx, 0x1f0, /* k */0xe36) || ctx->breakpointActivated) break;	// rjmp {k=111000110110} HEX:0xce36
case 0x1f1:
	if(AVR_rjmp(ctx, 0x1f1, /* k */0xe35) || ctx->breakpointActivated) break;	// rjmp {k=111000110101} HEX:0xce35
case 0x1f2:
	if(AVR_rjmp(ctx, 0x1f2, /* k */0xe3e) || ctx->breakpointActivated) break;	// rjmp {k=111000111110} HEX:0xce3e
case 0x1f3:
	if(AVR_rjmp(ctx, 0x1f3, /* k */0xe38) || ctx->breakpointActivated) break;	// rjmp {k=111000111000} HEX:0xce38
case 0x1f4:
	if(AVR_rjmp(ctx, 0x1f4, /* k */0xe32) || ctx->breakpointActivated) break;	// rjmp {k=111000110010} HEX:0xce32
case 0x1f5:
	if(AVR_rjmp(ctx, 0x1f5, /* k */0xe31) || ctx->breakpointActivated) break;	// rjmp {k=111000110001} HEX:0xce31
case 0x1f6:
	if(AVR_rjmp(ctx, 0x1f6, /* k */0xe30) || ctx->breakpointActivated) break;	// rjmp {k=111000110000} HEX:0xce30
case 0x1f7:
	if(AVR_rjmp(ctx, 0x1f7, /* k */0xe2a) || ctx->breakpointActivated) break;	// rjmp {k=111000101010} HEX:0xce2a
case 0x1f8:
	if(AVR_rjmp(ctx, 0x1f8, /* k */0xe47) || ctx->breakpointActivated) break;	// rjmp {k=111001000111} HEX:0xce47
case 0x1f9:
	if(AVR_rjmp(ctx, 0x1f9, /* k */0xe2d) || ctx->breakpointActivated) break;	// rjmp {k=111000101101} HEX:0xce2d
case 0x1fa:
	if(AVR_rjmp(ctx, 0x1fa, /* k */0xe2c) || ctx->breakpointActivated) break;	// rjmp {k=111000101100} HEX:0xce2c
case 0x1fb:
	if(AVR_rjmp(ctx, 0x1fb, /* k */0xe30) || ctx->breakpointActivated) break;	// rjmp {k=111000110000} HEX:0xce30
case 0x1fc:
	if(AVR_rjmp(ctx, 0x1fc, /* k */0xe3e) || ctx->breakpointActivated) break;	// rjmp {k=111000111110} HEX:0xce3e
case 0x1fd:
	if(AVR_rjmp(ctx, 0x1fd, /* k */0xe24) || ctx->breakpointActivated) break;	// rjmp {k=111000100100} HEX:0xce24
case 0x1fe:
	if(AVR_rjmp(ctx, 0x1fe, /* k */0xe3c) || ctx->breakpointActivated) break;	// rjmp {k=111000111100} HEX:0xce3c
case 0x1ff:
	if(AVR_rjmp(ctx, 0x1ff, /* k */0xe22) || ctx->breakpointActivated) break;	// rjmp {k=111000100010} HEX:0xce22
		default:
			AVR_error_nosp(ctx, sp);
			break;
	}
}
