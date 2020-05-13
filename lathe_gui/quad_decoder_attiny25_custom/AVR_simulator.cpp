#include <AVR_simulator.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdio.h>


#define lo(X) ((uint8_t)(X&0xFF))
#define hi(X) ((uint8_t)((X>>8)&0xFF))

#define AVR_checkpc() if(ctx->PC!=pc) {printf("PC ERROR! ctx->PC:0x%x pc:0x%x\n", ctx->PC, pc); ASSERT_FAIL();} else {} checkBreakpoint(ctx, pc);

extern void executeFromAddress(AVR_simulator_t * ctx, uint32_t sp);
static uint32_t getSP(AVR_simulator_t * ctx);
static void setSP(AVR_simulator_t * ctx, uint32_t sp);
static uint8_t pop(AVR_simulator_t * ctx);
static uint8_t getMem(AVR_simulator_t * ctx, uint32_t addr);

static void beforeStart(AVR_simulator_t * ctx);
static void checkBreakpoint(AVR_simulator_t * ctx, uint32_t pc);
static void debugUseCycle(AVR_simulator_t * ctx, uint32_t cycle);

static uint8_t ASSERT_FAIL()
{
	printf("FAIL\n");
	exit(1);
}
static void unimpl(){/* TODO fail */}

bool AVR_error_nosp(AVR_simulator_t * ctx, uint32_t pc)
{
	printf("ERROR NOSP: 0x%x\n", pc);
	ASSERT_FAIL();
	return false;
}
static bool is16PC(AVR_simulator_t * ctx)
{
	return true;
}
static bool is22PC(AVR_simulator_t * ctx)
{
	return false;
}
static bool isXMEGA(AVR_simulator_t * ctx)
{
	return false;
}
static bool isXMEGAOrAVR8L(AVR_simulator_t * ctx)
{
	return false;
}
static bool is2WordCommand(AVR_simulator_t * ctx, uint32_t pc)
{
	return false;	// TODO
}
static void useCycle(AVR_simulator_t * ctx, uint32_t cycle)
{
	ctx->cycle+=cycle;
	debugUseCycle(ctx, cycle);
}
static uint32_t popPC(AVR_simulator_t * ctx)
{
	uint8_t high=pop(ctx);
	uint8_t low=pop(ctx);
	return (((uint32_t)high)<<8)|low;
}
static uint8_t getIO(AVR_simulator_t * ctx, uint8_t A)
{
	if(A>=N_IO) ASSERT_FAIL();
	return ctx->ADDRESS[ADDR_IO+A];
}
static void setIO(AVR_simulator_t * ctx, uint8_t A, uint8_t v)
{
	if(A>=N_IO) ASSERT_FAIL();
	ctx->ADDRESS[ADDR_IO+A]=v;
}
static uint32_t getSP(AVR_simulator_t * ctx)
{
	return getIO(ctx, SP_IO_ADDR);
}
static void setSP(AVR_simulator_t * ctx, uint32_t sp)
{
	setIO(ctx, SP_IO_ADDR, sp);
}
static void globalEnableInterrupt(AVR_simulator_t * ctx, bool enable)
{
	uint8_t prev=getIO(ctx, SREG_IO_ADDR);
	if(enable)
	{
		prev|=SREG_I;
	}else
	{
		prev&=~SREG_I;
	}
	setIO(ctx, SREG_IO_ADDR, prev);
}
static void setReg(AVR_simulator_t * ctx, uint8_t d, uint8_t val)
{
	if(d>=N_REG) ASSERT_FAIL();
	ctx->ADDRESS[d+ADDR_REG]=val;
}
static uint8_t getReg(AVR_simulator_t * ctx, uint8_t d)
{
	if(d>=N_REG) ASSERT_FAIL();
	return ctx->ADDRESS[d+ADDR_REG];
}
static uint8_t getMem(AVR_simulator_t * ctx, uint32_t addr)
{
	if(addr>=N_SRAM) ASSERT_FAIL();
	return ctx->ADDRESS[addr+ADDR_SRAM];
}
static void setMem(AVR_simulator_t * ctx, uint32_t addr, uint8_t val)
{
	if(addr>=N_SRAM) ASSERT_FAIL();
	ctx->ADDRESS[addr+ADDR_SRAM]=val;
}
static bool skipCommand(AVR_simulator_t * ctx, uint32_t pc, bool skip)
{
	// printf("SKIP COMMAND: %x %d\n", pc, skip);
	if(skip)
	{
		if(is2WordCommand(ctx,pc+1))
		{
			useCycle(ctx,isXMEGA(ctx)?4:3);
			ctx->PC=pc+3;
			return true;
		}else
		{
			useCycle(ctx,isXMEGA(ctx)?3:2);
			ctx->PC=pc+2;
			// printf("SKIP COMMAND SKIP one to: %x\n", ctx->PC);
			return true;
		}
	}else
	{
		useCycle(ctx,isXMEGA(ctx)?2:1);
		ctx->PC++;
		return false;
	}
}
static void updateSREG(AVR_simulator_t * ctx, uint8_t changeBitsMask, uint8_t newBits)
{
	uint8_t prev=getIO(ctx, SREG_IO_ADDR);
	prev&=~changeBitsMask;
	prev|=newBits&changeBitsMask;
	setIO(ctx, SREG_IO_ADDR, prev);
}
static void setSREG_SVNZ(AVR_simulator_t * ctx, bool s,bool v,bool n,bool z)
{
	updateSREG(ctx, 
		0b00011110,
		(s?SREG_S:0)|
		(v?SREG_V:0)|
		(n?SREG_N:0)|
		(z?SREG_Z:0)
		);
}
static void setSREG_HSVNZC(AVR_simulator_t * ctx, bool h, bool s,bool v,bool n,bool z, bool c)
{
	updateSREG(ctx, 
		0b00111111,
		(s?SREG_H:0)|
		(s?SREG_S:0)|
		(v?SREG_V:0)|
		(n?SREG_N:0)|
		(z?SREG_Z:0)|
		(c?SREG_C:0)
		);
}
static uint8_t getSREG(AVR_simulator_t * ctx)
{
	return getIO(ctx, SREG_IO_ADDR);
}
static bool isBitMask(uint8_t val, uint8_t bitMask)
{
	return (val&bitMask)!=0;
}
static bool notBitMask(uint8_t val, uint8_t bitMask)
{
	return (val&bitMask)==0;
}
static bool notBitIndex(uint8_t val, uint8_t bitIndex)
{
	return (val&(1<<bitIndex))==0;
}
static bool isBitIndex(uint8_t val, uint8_t bitIndex)
{
	return (val&(1<<bitIndex))!=0;
}

static int32_t toSigned(uint32_t k, uint8_t nBits)
{
	if((k & (1<<(nBits-1)))!=0)
	{
		// negative
		return (int32_t)k|(0xffffffff<<nBits);
	}else
	{
		return (int32_t)k;
	}
}
static void push(AVR_simulator_t * ctx, uint8_t v)
{
	uint32_t addr=getSP(ctx);
	setMem(ctx, addr, v);
	setSP(ctx, addr-1);
}
static uint8_t pop(AVR_simulator_t * ctx)
{
	uint32_t addr=getSP(ctx);
	uint8_t v=getMem(ctx, addr+1);
	setSP(ctx, addr+1);
	return v;
}

/// Debugger callbacks are included so it is possible to inline them
#include <AVR_debugger.cpp>

static void compare(AVR_simulator_t * ctx, uint8_t a, uint8_t b, uint8_t carry, bool prevz)
{
	uint8_t R=a-b-carry;
	bool sregc=
		(notBitIndex(a,7)&&isBitIndex(b,7)) ||
		(isBitIndex(b,7)&&isBitIndex(R,7)) ||
		(isBitIndex(R,7)&&notBitIndex(a,7));
	bool sregz=(R==0)?prevz:0;
	bool sregn=(R&0b10000000)!=0;
	bool sregh=
		(notBitIndex(a,3)&&isBitIndex(b,3)) ||
		((isBitIndex(b,3))&&isBitIndex(R,3)) ||
		((!isBitIndex(a,3))&&isBitIndex(R,3));
	bool sregv=(isBitIndex(a,7)&&notBitIndex(b,7)&&notBitIndex(R,7))||
		(notBitIndex(a,7)&&isBitIndex(b,7)&&isBitIndex(R,7));
	bool sregs=sregn!=sregv;
	uint8_t regNew=
		(sregh?SREG_H:0)|
		(sregs?SREG_S:0)|
		(sregv?SREG_V:0)|
		(sregn?SREG_N:0)|
		(sregz?SREG_Z:0)|
		(sregc?SREG_C:0);
	updateSREG(ctx, SREG_H|SREG_S|SREG_V|SREG_N|SREG_Z|SREG_C,
		regNew);
}

static void avr_sub(AVR_simulator_t * ctx, uint8_t d, uint8_t value, uint8_t carry, bool prevz)
{
	uint8_t Rd=getReg(ctx, d);
	uint16_t diff=((uint16_t)Rd)-value-carry;
	uint8_t R=(uint8_t)diff;

	bool h=(notBitIndex(Rd,3)&&isBitIndex(value, 3))||
		(isBitIndex(value,3)&&isBitIndex(R, 3))||
		(isBitIndex(R,3)&&isBitIndex(Rd, 3));
	bool v=(isBitIndex(Rd,7)&&notBitIndex(value,7)&&notBitIndex(R,7))||
		(notBitIndex(Rd,7)&&isBitIndex(value,7)&&isBitIndex(R,7));
	bool n=isBitIndex(R,7);
	bool s=n!=v;
	bool z=(R==0)?prevz:0;
	bool c=((int16_t)diff)<0;
	setSREG_HSVNZC(ctx, h, s, v, n, z, c);
//	printf("AVR_SUB: r%d PREV:%d SUB:%d NEW:%d\n", d, Rd, value, R);
	setReg(ctx, d, R);
	ctx->PC++;
	useCycle(ctx, 1);
}


// ***************** Implementations of commands *****************
bool AVR_rjmp(AVR_simulator_t * ctx, uint32_t pc, uint32_t k)
{
	AVR_checkpc();
	int32_t rel=toSigned(k, 12);
	useCycle(ctx, 2);
	ctx->PC+=1+rel;
	return true;
}
bool AVR_rcall(AVR_simulator_t * ctx, uint32_t pc, uint32_t k)
{
	AVR_checkpc();
	int32_t rel=toSigned(k, 12);
	if(!is16PC(ctx))
	{
		ASSERT_FAIL();
	}else
	{
		pc++;
		push(ctx, lo(pc));
		push(ctx, hi(pc));
		ctx->PC=pc+rel;
		useCycle(ctx, 3);	// TODO cycles in XMEGA are different
	}
	return true;
}
bool AVR_reti(AVR_simulator_t * ctx, uint32_t pc)
{
	AVR_checkpc();
	uint32_t retpc=popPC(ctx);
	printf("RETi 0x%x\n", retpc);
	ctx->PC=retpc;
	globalEnableInterrupt(ctx, true);
	useCycle(ctx, is16PC(ctx)?4:(is22PC(ctx)?5:ASSERT_FAIL()));
	return true;
}
bool AVR_ret(AVR_simulator_t * ctx, uint32_t pc)
{
	AVR_checkpc();
	uint32_t retpc=popPC(ctx);
	printf("RET 0x%x\n", retpc);
	ctx->PC=retpc;
	useCycle(ctx, is16PC(ctx)?4:(is22PC(ctx)?5:ASSERT_FAIL()));
	return true;
}
bool AVR_in(AVR_simulator_t * ctx, uint32_t pc, uint8_t A, uint8_t d)
{
	AVR_checkpc();
	uint8_t val=getIO(ctx, A);
	setReg(ctx,d, val);
	useCycle(ctx,1);
	ctx->PC++;
	return false;
}
bool AVR_mov(AVR_simulator_t * ctx, uint32_t pc, uint8_t d, uint8_t r)
{
	AVR_checkpc();
	uint8_t val=getReg(ctx, r);
	setReg(ctx, d, val);
	useCycle(ctx,1);
	ctx->PC++;
	return false;
}
bool AVR_movw(AVR_simulator_t * ctx, uint32_t pc, uint8_t d, uint8_t r)
{
	AVR_checkpc();
	d*=2;
	r*=2;
	uint8_t val=getReg(ctx, r);
	setReg(ctx, d, val);
	val=getReg(ctx, r+1);
	setReg(ctx, d+1, val);
	useCycle(ctx,1);
	ctx->PC++;
	return false;
}
bool AVR_add_carry(AVR_simulator_t * ctx, uint32_t pc, uint8_t d, uint8_t r, uint8_t carry)
{
	AVR_checkpc();
	uint8_t a=getReg(ctx,d);
	uint8_t b=getReg(ctx,r);
	uint16_t c=(((uint16_t) a) + ((uint16_t)b) + carry);
	uint8_t R=(uint8_t)c;
	bool sregh=(isBitIndex(a,3)&&isBitIndex(b,3))||
		(isBitIndex(b,3)&&notBitIndex(R,3))||
		(isBitIndex(a,3)&&notBitIndex(R,3));
	bool sregv=(isBitIndex(a,7)&&isBitIndex(b,7)&&notBitIndex(R, 7))||
		(notBitIndex(a,7)&&notBitIndex(b,7)&&isBitIndex(R, 7));
	bool sregn=((int8_t)R)<0;
	uint8_t sreg=
		(sregh?SREG_H:0)|
		((sregn != sregv)?SREG_S:0)|
		(sregv?SREG_V:0)|
		(sregn?SREG_N:0)|
		((R==0)?SREG_Z:0)|
		(c>255?SREG_C:0);
	setReg(ctx,d, R);
	updateSREG(ctx, SREG_H|SREG_S|SREG_V|SREG_N|SREG_Z|SREG_C, sreg);
	useCycle(ctx,1);
	ctx->PC++;
	return false;
}
bool AVR_add(AVR_simulator_t * ctx, uint32_t pc, uint8_t d, uint8_t r)
{
	return AVR_add_carry(ctx, pc, d, r, 0);
}
bool AVR_adc(AVR_simulator_t * ctx, uint32_t pc, uint8_t d, uint8_t r)
{
	return AVR_add_carry(ctx, pc, d, r, getSREG(ctx)&SREG_C);
}

bool AVR_lsr(AVR_simulator_t * ctx, uint32_t pc, uint8_t d)
{
	AVR_checkpc();
	uint8_t a=getReg(ctx,d);
	uint8_t res=a>>1;
	setReg(ctx,d, res);
	unimpl();	// TODO SREG
//	updateSREG(ctx, SREG_H|SREG_S|SREG_V|SREG_N|SREG_Z|SREG_C, sreg);
	useCycle(ctx,1);
	ctx->PC++;
	return false;
}
bool AVR_eor(AVR_simulator_t * ctx, uint32_t pc, uint8_t d, uint8_t r)
{
	AVR_checkpc();
	uint8_t a=getReg(ctx,d);
	uint8_t b=getReg(ctx,r);
	uint8_t res=a^b;
	bool sregn=((int8_t)res)<0;
	uint8_t sreg=
		(sregn?SREG_S:0)|
		0 | // V
		(sregn?SREG_N:0)|
		(res==0? SREG_Z:0);
	setReg(ctx,d, res);
	updateSREG(ctx, SREG_H|SREG_S|SREG_V|SREG_N|SREG_Z|SREG_C, sreg);
	useCycle(ctx,1);
	ctx->PC++;
	return false;
}
static uint8_t avr_and(AVR_simulator_t * ctx, uint8_t a, uint8_t b)
{
	uint8_t res=a&b;
	bool sregn=((int8_t)res)<0;
	uint8_t sreg=
		(sregn?SREG_S:0)|
		0 | // V
		(sregn?SREG_N:0)|
		(res==0? SREG_Z:0);
	updateSREG(ctx, SREG_H|SREG_S|SREG_V|SREG_N|SREG_Z|SREG_C, sreg);
	return res;
}
bool AVR_and(AVR_simulator_t * ctx, uint32_t pc, uint8_t d, uint8_t r)
{
	AVR_checkpc();
	uint8_t a=getReg(ctx,d);
	uint8_t b=getReg(ctx,r);
	uint8_t res=avr_and(ctx, a, b);
	setReg(ctx, d, res);
	useCycle(ctx,1);
	ctx->PC++;
	return false;
}
bool AVR_andi(AVR_simulator_t * ctx, uint32_t pc, uint8_t K, uint8_t d)
{
	AVR_checkpc();
	uint8_t a=getReg(ctx,d+16);
	uint8_t res=avr_and(ctx, a, K);
	setReg(ctx, d+16, res);
	useCycle(ctx,1);
	ctx->PC++;
	return false;
}
static void value_or(AVR_simulator_t * ctx, uint8_t d, uint8_t b)
{
	uint8_t a=getReg(ctx,d);
	uint8_t res=a|b;
	bool sregn=((int8_t)res)<0;
	uint8_t sreg=
		(sregn?SREG_S:0)|
		0 | // V
		(sregn?SREG_N:0)|
		(res==0? SREG_Z:0); // TODO check SREG values!
	setReg(ctx,d, res);
	updateSREG(ctx, SREG_S|SREG_V|SREG_N|SREG_Z, sreg);
	useCycle(ctx,1);
	ctx->PC++;
}
bool AVR_or(AVR_simulator_t * ctx, uint32_t pc, uint8_t d, uint8_t r)
{
	AVR_checkpc();
	uint8_t b=getReg(ctx,r);
	value_or(ctx, d, b);
	return false;
}
bool AVR_sbr(AVR_simulator_t * ctx, uint32_t pc, uint8_t K, uint8_t d)
{
	AVR_checkpc();
	// printf("AVR_SBR: d%d K:%d\n", d+16, K);
	value_or(ctx, d+16, K);
	return false;
}


bool AVR_sbic(AVR_simulator_t * ctx, uint32_t pc, uint8_t A, uint8_t b)
{
	AVR_checkpc();
	uint8_t val=getIO(ctx, A);
	uint8_t masked=val&(1<<b);
	return skipCommand(ctx, pc, masked==0);
}
bool AVR_sbis(AVR_simulator_t * ctx, uint32_t pc, uint8_t A, uint8_t b)
{
	AVR_checkpc();
	uint8_t val=getIO(ctx, A);
	uint8_t masked=val&(1<<b);
	return skipCommand(ctx, pc, masked!=0);
}

bool AVR_sbrs(AVR_simulator_t * ctx, uint32_t pc, uint8_t b, uint8_t r)
{
	AVR_checkpc();
	uint8_t val=getReg(ctx, r);
	uint8_t masked=val&(1<<b);
	return skipCommand(ctx, pc, masked!=0);
}
bool AVR_sbrc(AVR_simulator_t * ctx, uint32_t pc, uint8_t b, uint8_t r)
{
	AVR_checkpc();
	uint8_t val=getReg(ctx, r);
	uint8_t masked=val&(1<<b);
	return skipCommand(ctx, pc, masked==0);
}
bool AVR_swap(AVR_simulator_t * ctx, uint32_t pc, uint8_t d)
{
	AVR_checkpc();
	uint8_t val=getReg(ctx, d);
	uint8_t R=(val>>4)|(val<<4);
	setReg(ctx, d, R);
	useCycle(ctx,1);
	ctx->PC++;
	return false;
}
bool AVR_out(AVR_simulator_t * ctx, uint32_t pc, uint8_t A, uint8_t r)
{
	AVR_checkpc();
	uint8_t val=getReg(ctx, r);
	setIO(ctx, A, val);
	useCycle(ctx,1);
	ctx->PC++;
	return false;
}
bool AVR_ldi(AVR_simulator_t * ctx, uint32_t pc, uint8_t K, uint8_t d)
{
	AVR_checkpc();
	setReg(ctx, d+16, K);
	useCycle(ctx,1);
	ctx->PC++;
	return false;	
}
bool AVR_sbi(AVR_simulator_t * ctx, uint32_t pc, uint8_t A, uint8_t b)
{
	AVR_checkpc();
	uint8_t prev=getIO(ctx, A);
	uint8_t mask=1<<b;
	setIO(ctx, A, prev|mask);
	useCycle(ctx,isXMEGAOrAVR8L(ctx)?1:2);
	ctx->PC++;
	return false;
}
bool AVR_cbi(AVR_simulator_t * ctx, uint32_t pc, uint8_t A, uint8_t b)
{
	AVR_checkpc();
	uint8_t prev=getIO(ctx, A);
	uint8_t mask=1<<b;
	setIO(ctx, A, prev&~mask);
	useCycle(ctx,isXMEGAOrAVR8L(ctx)?1:2);
	ctx->PC++;
	return false;
}
bool AVR_cli(AVR_simulator_t * ctx, uint32_t pc)
{
	AVR_checkpc();
	globalEnableInterrupt(ctx, false);
	useCycle(ctx,1);
	ctx->PC++;
	return false;
}
bool AVR_sei(AVR_simulator_t * ctx, uint32_t pc)
{
	AVR_checkpc();
	globalEnableInterrupt(ctx, true);
	useCycle(ctx,1);
	ctx->PC++;
	return false;
}
bool AVR_nop(AVR_simulator_t * ctx, uint32_t pc)
{
	AVR_checkpc();
	useCycle(ctx, 1);
	ctx->PC++;
	return false;
}
bool AVR_cp(AVR_simulator_t * ctx, uint32_t pc, uint8_t d, uint8_t r)
{
	AVR_checkpc();
	uint8_t a=getReg(ctx, d);
	uint8_t b=getReg(ctx, r);
	compare(ctx, a,b, 0, true);
	useCycle(ctx, 1);
	ctx->PC++;
	return false;
}
bool AVR_cpc(AVR_simulator_t * ctx, uint32_t pc, uint8_t d, uint8_t r)
{
	AVR_checkpc();
	uint8_t prevSREG=getSREG(ctx);
	uint8_t a=getReg(ctx, d);
	uint8_t b=getReg(ctx, r);
	bool prevz=isBitMask(prevSREG, SREG_Z);
	compare(ctx, a,b, getSREG(ctx)&SREG_C, prevz);
	useCycle(ctx, 1);
	ctx->PC++;
	return false;
}
bool AVR_cpi(AVR_simulator_t * ctx, uint32_t pc, uint8_t K, uint8_t d)
{
	AVR_checkpc();
	uint8_t a=getReg(ctx, d+16);
	compare(ctx, a, K, 0, true);
	useCycle(ctx, 1);
	ctx->PC++;
	return false;
}

bool AVR_inc(AVR_simulator_t * ctx, uint32_t pc, uint8_t d)
{
	AVR_checkpc();
	uint8_t val=getReg(ctx, d);
	bool v=val==0x7f;
	val++;
	setReg(ctx, d, val);
	bool n=(val&0b10000000)!=0;
	bool s=v!=n;
	bool z=val==0;
	setSREG_SVNZ(ctx,s,v,n,z);
	useCycle(ctx, 1);
	ctx->PC++;
	return false;
}
bool AVR_dec(AVR_simulator_t * ctx, uint32_t pc, uint8_t d)
{
	AVR_checkpc();
	uint8_t val=getReg(ctx, d);
	bool v=val==0x80;
	val--;
	setReg(ctx, d, val);
	bool n=(val&0b10000000)!=0;
	bool s=v!=n;
	bool z=val==0;
	setSREG_SVNZ(ctx,s,v,n,z);
	useCycle(ctx, 1);
	ctx->PC++;
	return false;
}

static bool branchIf(AVR_simulator_t * ctx, uint32_t k, bool cond)
{
	if(cond)
	{
		uint32_t rel=toSigned(k, 7);
//		printf("Branch IF jump rel: 0x%x\n", rel);
		useCycle(ctx, 2);
		ctx->PC+=1+rel;
		return true;
	}else
	{
//		printf("Branch IF nojump\n");
		useCycle(ctx, 1);
		ctx->PC++;
		return false;
	}
}
bool AVR_breq(AVR_simulator_t * ctx, uint32_t pc, uint32_t k)
{
	AVR_checkpc();
	uint8_t sreg=getSREG(ctx);
	return branchIf(ctx, k, isBitMask(sreg,SREG_Z));
}
bool AVR_brsh(AVR_simulator_t * ctx, uint32_t pc, uint32_t k)
{
	AVR_checkpc();
	uint8_t sreg=getSREG(ctx);
	return branchIf(ctx, k, notBitMask(sreg,SREG_C));
}

bool AVR_brne(AVR_simulator_t * ctx, uint32_t pc, uint32_t k)
{
	AVR_checkpc();
	uint8_t sreg=getSREG(ctx);
	return branchIf(ctx, k, notBitMask(sreg,SREG_Z));
}

bool AVR_brge(AVR_simulator_t * ctx, uint32_t pc, uint32_t k)
{
	AVR_checkpc();
	uint8_t sreg=getSREG(ctx);
	return branchIf(ctx, k, isBitMask(sreg,SREG_N)!=isBitMask(sreg,SREG_V));
}

bool AVR_ijmp(AVR_simulator_t * ctx, uint32_t pc)
{
	AVR_checkpc();
	unimpl();
	uint8_t ZL=getReg(ctx, 30);
	uint8_t ZH=getReg(ctx, 31);
	useCycle(ctx, 2);
	ctx->PC=(((uint32_t)ZH)<<8)|ZL;
	return true;
}
bool AVR_sub(AVR_simulator_t * ctx, uint32_t pc, uint8_t d, uint8_t r)
{
	AVR_checkpc();
	avr_sub(ctx, d, getReg(ctx, r), 0, true);
	return false;
}
bool AVR_sbc(AVR_simulator_t * ctx, uint32_t pc, uint8_t d, uint8_t r)
{
	AVR_checkpc();
	uint8_t sreg=getSREG(ctx);
	avr_sub(ctx, d, getReg(ctx, r), sreg&SREG_C, isBitMask(sreg,SREG_C));
	return false;
}
bool AVR_sbci(AVR_simulator_t * ctx, uint32_t pc, uint8_t K, uint8_t d)
{
	AVR_checkpc();
	d+=16;
	uint8_t sreg=getSREG(ctx);
	avr_sub(ctx, d, K, sreg&SREG_C, isBitMask(sreg,SREG_C));
	return false;
}
bool AVR_subi(AVR_simulator_t * ctx, uint32_t pc, uint8_t K, uint8_t d)
{
	AVR_checkpc();
	d+=16;
	avr_sub(ctx, d, K, 0, true);
	return false;
}
bool AVR_lpm(AVR_simulator_t * ctx, uint32_t pc, uint8_t d, uint8_t i)
{
	AVR_checkpc();
	if(i!=0)
	{
		ASSERT_FAIL();
		// TODO not implemented
	}
	uint8_t zl=getReg(ctx, 30);
	uint8_t zh=getReg(ctx, 31);
	uint16_t addr=((uint16_t)zh<<8)+zl;
	uint8_t val=AVR_read_progmem_byte(addr);
	setReg(ctx, d, val);
	useCycle(ctx, 3);
	ctx->PC++;
	return false;
}

