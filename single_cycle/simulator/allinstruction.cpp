#include <iostream>
#include "allinstruction.h"
#include <string>
#include <string.h>
#include <stdio.h>
using namespace std;

unsigned int getrd(unsigned int inst[])
{
	unsigned int retrd = 0, b = 16;
	for(int i=0; i<5; i++){
		retrd += b*inst[16+i];
		b /= 2;
	}
	return retrd;
}
unsigned int getrs(unsigned int inst[])
{
	unsigned int retrs = 0, b = 16;
	for(int i=0; i<5; i++){
		retrs += b*inst[6+i];
		b /= 2;
	}
	return retrs;
}
unsigned int getrt(unsigned int inst[])
{
	unsigned int retrt = 0, b = 16;
	for(int i=0; i<5; i++){
		retrt += b*inst[11+i];
		b /= 2;
	}
	return retrt;
}
unsigned int getshamt(unsigned int inst[])
{
	unsigned int retshamt = 0, b = 16;
	for(int i=0; i<5; i++){
		retshamt += b*inst[21+i];
		b /= 2;
	}
	return retshamt;
}
unsigned int getfunct(unsigned int inst[])
{
	unsigned int retfunct = 0, b = 32;
	for(int i=0; i<6; i++){
		retfunct += b*inst[26+i];
		b /= 2;
	}
	return retfunct;
}
unsigned int getimu(unsigned int inst[])
{
	unsigned int retimu = 0, b = 32768;
	for(int i=0; i<16; i++){
		retimu += b*inst[16+i];
		b /= 2;
	}
	return retimu;
}
int getim(unsigned int inst[])
{
	int ret, b1, b2;
	b1 = instruct[reg[34]+2];
	b2 = (unsigned char)instruct[reg[34]+3];
	b1 = b1 << 8;
	ret = (b1 | b2);
	/*int ret, b = 32768;
	for(int i=0; i<16; i++){
		if(i == 0) ret -= b*inst[16+i];
		else ret += b*inst[16+i];
		b /= 2;
	}*/
	return ret;
}
unsigned int getaddr(unsigned int inst[])
{
	int retaddr = 0, b = 33554432;
	for(int i=0; i<26; i++){
		retaddr += b*inst[6+i];
		b /= 2;
	}
	return retaddr;
}

//--------------------------------------------
void instruction(char buffer[])
{
	unsigned int ins[32] = {0};
	unsigned int temp, a, index=0;
	for(int i=0; i<4; i++){
		temp = buffer[i];
		for(int j=7; j>=0; j--){
			a = temp % 2;
			temp = temp/2;
			ins[index+j] = a;
		}
		index += 8;
	}
	int opcode = 0, b = 32;
	for(int i=0; i<6; i++){
		opcode += b*ins[i];
		b /= 2;
	}
	
	unsigned int funct = getfunct(ins);
	unsigned int rd = getrd(ins), rs = getrs(ins), rt = getrt(ins), shamt = getshamt(ins), imu = getimu(ins), addr = getaddr(ins);

	int im = getim(ins);
	long long int mul;
	unsigned long long int mulu;
	int forlo;
	printf("%d: %d %d %d %d %d %d %d %d %d\n",cycle , opcode, rs, rt, rd, shamt, funct, im, imu, addr);
	switch(opcode){
		case 0:
			switch(funct){
				case 32: //add
					if(rd == 0){
						errordump(1);
						if(reg[rs]>=0 && reg[rt]>=0 && reg[rs]+reg[rt]<0) errordump(2);
						if(reg[rs]<0 && reg[rt]<0 && reg[rs]+reg[rt]>=0) errordump(2);
						break;
					}
					if(reg[rs]>=0 && reg[rt]>=0 && reg[rs]+reg[rt]<0) errordump(2);
					if(reg[rs]<0 && reg[rt]<0 && reg[rs]+reg[rt]>=0) errordump(2);
					reg[rd] = reg[rs] + reg[rt];
					break;
				case 33: //addu
					if(rd == 0){
						errordump(1);
						break;
					}
					reg[rd] = reg[rs] + reg[rt];
					break;
				case 34: //sub
					if(rd == 0){
						errordump(1);
						if(reg[rs]>=0 && (-reg[rt])>=0 && reg[rs]+(-reg[rt])<0) errordump(2);
						if(reg[rs]<0 && (-reg[rt])<0 && reg[rs]+(-reg[rt])>=0) errordump(2);
						break;
					}
					if(reg[rs]>=0 && (-reg[rt])>=0 && reg[rs]+(-reg[rt])<0) errordump(2);
					if(reg[rs]<0 && (-reg[rt])<0 && reg[rs]+(-reg[rt])>=0) errordump(2);
					reg[rd] = reg[rs]+(-reg[rt]);
					break;
				case 36: //and
					if(rd == 0){
						errordump(1);
						break;
					}
					reg[rd] = (reg[rs] & reg[rt]);
					break;
				case 37: //or
					if(rd == 0){
						errordump(1);
						break;
					}
					reg[rd] = (reg[rs] | reg[rt]);
					break;					
				case 38: //xor
					if(rd == 0){
						errordump(1);
						break;
					}
					reg[rd] = (reg[rs] ^ reg[rt]);
					break;
				case 39: //nor
					if(rd == 0){
						errordump(1);
						break;
					}
					reg[rd] = ~(reg[rs] | reg[rt]);
					break;
				case 40: //nand
					if(rd == 0){
						errordump(1);
						break;
					}
					reg[rd] = ~(reg[rs] & reg[rt]);
					break;
				case 42: //slt
					if(rd == 0){
						errordump(1);
						break;
					}
					reg[rd] = reg[rs] < reg[rt];
					break;
				case 0: //sll
					if(!(rd == 0 && rt ==0 && shamt == 0) && rd == 0){
						errordump(1);
						break;
					}
					reg[rd] = reg[rt] << shamt;
					break;
				case 2: //srl
				{
					if(rd == 0){
						errordump(1);
						break;
					}
					reg[rd] = (unsigned int)reg[rt] >> shamt;
					
					break;
				}
				case 3: //sra
					if(rd == 0){
						errordump(1);
						break;
					}
					reg[rd] = reg[rt] >> shamt;
					break;
				case 8: //jr
					jump = 1;
					reg[34] = reg[rs];
					break;
				case 24: //mult problem
				{
					if(error3 == 1) errordump(3);
					else error3 = 1;
					//mul = reg[rs] * reg[rt];
					if(reg[rs]>=0 && reg[rt]>=0 && mul<0) errordump(2);
					long long int ma = reg[rs], mb = reg[rt];
					mul = ma * mb;
					forlo = mul;
					reg[32] = mul>>32;
					reg[33] = forlo;
					printf("%lld %x %x %x %x\n", mul, reg[32], reg[33], reg[rs], reg[rt]);
					break;
				}
				case 25: //multu
				{
					if(error3 == 1) errordump(3);
					else error3 = 1;
					unsigned long long int a = (unsigned int)reg[rs], b = (unsigned int)reg[rt];
					mulu = a * b;
					forlo = mulu;
					reg[32] = mulu >> 32;
					reg[33] = forlo;
					break;
				}
				case 16: //mfhi
					if(error3 == 1) error3 = 0;
					if(rd == 0){
						errordump(1);
						break;
					}
					reg[rd] = reg[32];
					break;
				case 18: //mflo
					if(error3 == 1) error3 = 0;
					if(rd == 0){
						errordump(1);
						break;
					}
					reg[rd] = reg[33];
					break;
			}
			break;
		case 8: //addi
			if(rt == 0){
				errordump(1);
				if(reg[rs]>=0 && im >=0 && reg[rs]+im<0) errordump(2);
				if(reg[rs]<0 && im<0 && reg[rs]+im>=0) errordump(2);
				break;
			}
			if(reg[rs]>=0 && im>=0 && reg[rs]+im<0) errordump(2);
			if(reg[rs]<0 && im<0 && reg[rs]+im>=0) errordump(2);
			reg[rt] = reg[rs] + im;
			break;
		case 9: //addiu
			if(rt == 0){
				errordump(1);
				break;
			}
			reg[rt] = reg[rs] + im;
			break;
		case 35: //lw
		{
			if(rt == 0){
				errordump(1);
				if(reg[rs]>=0 && reg[rs]+im<0 && im>=0) errordump(2);
				if(reg[rs]<0 && im<0 && reg[rs]+im>=0) errordump(2);
				if(reg[rs]+im > 1020 || reg[rs]+im <0){
					errordump(4);
					termi = 1;
				} 
				if((reg[rs]+im)%4 != 0) {
					errordump(5);
					termi = 1;
				}
				break;
			}
			if(reg[rs]>=0 && reg[rs]+im<0 && im>=0) errordump(2);
			if(reg[rs]<0 && im<0 && reg[rs]+im>=0) errordump(2);
			if(reg[rs]+im > 1020 || reg[rs]+im <0){
				errordump(4);
				termi = 1;
			} 
			if((reg[rs]+im)%4 != 0) {
				errordump(5);
				termi = 1;
			}
			if(termi) break;
			int temp1;
			temp1 = (unsigned char)data[reg[rs]+im];
			for(int r=1; r<4; r++){
				temp1 = temp1 << 8;
				temp1 = temp1 | (unsigned char)data[reg[rs]+im+r];
			}
			reg[rt] = temp1;
			
			break;
		}
		case 33: //lh
		{
			if(rt == 0){
				errordump(1);
				if(reg[rs]>=0 && reg[rs]+im<0 && im>=0) errordump(2);
				if(reg[rs]<0 && im<0 && reg[rs]+im>=0) errordump(2);
				if(reg[rs]+im > 1022 || reg[rs]+im <0){
					errordump(4);
					termi = 1;
				} 
				if((reg[rs]+im)%2 != 0){
					errordump(5);
					termi = 1;
				} 
				break;
			}
			if(reg[rs]>=0 && reg[rs]+im<0 && im>=0) errordump(2);
			if(reg[rs]<0 && im<0 && reg[rs]+im>=0) errordump(2);
			if(reg[rs]+im > 1022 || reg[rs]+im <0){
				errordump(4);
				termi = 1;
			} 
			if((reg[rs]+im)%2 != 0){
				errordump(5);
				termi = 1;
			} 
			if(termi) break;
			int temp1;
			temp1 = data[reg[rs]+im]; ///////problem
			for(int r=1; r<2; r++){
				temp1 = temp1 << 8;
				temp1 = temp1 | ((unsigned char)data[reg[rs]+im+r]);
			}
			reg[rt] = temp1;
			break;
		}
		case 37: //lhu
		{
			if(rt == 0){
				errordump(1);
				if(reg[rs]>=0 && reg[rs]+im<0 && im>=0) errordump(2);
				if(reg[rs]<0 && im<0 && reg[rs]+im>=0) errordump(2);
				if(reg[rs]+im > 1022 || reg[rs]+im <0){
					errordump(4);
					termi = 1;
				} 
				if((reg[rs]+im)%2 != 0){
					errordump(5);
					termi = 1;
				}
				break;
			}
			if(reg[rs]>=0 && reg[rs]+im<0 && im>=0) errordump(2);
			if(reg[rs]<0 && im<0 && reg[rs]+im>=0) errordump(2);
			if(reg[rs]+im > 1022 || reg[rs]+im <0){
				errordump(4);
				termi = 1;
			} 
			if((reg[rs]+im)%2 != 0){
				errordump(5);
				termi = 1;
			}
			if(termi) break;
			unsigned int temp1;
			temp1 = (unsigned char)data[reg[rs]+im];
			temp1 = temp1 << 8;
			temp1 = temp1 | (unsigned char)data[reg[rs]+im+1];
			reg[rt] = temp1;
			break;
		}
		case 32: //lb
		{
			if(rt == 0){
				errordump(1);
				if(reg[rs]>=0 && reg[rs]+im<0 && im>=0) errordump(2);
				if(reg[rs]<0 && im<0 && reg[rs]+im>=0) errordump(2);
				if(reg[rs]+im > 1023 || reg[rs]+im <0){
					errordump(4);
					termi = 1;
				} 
				break;
			}
			if(reg[rs]>=0 && reg[rs]+im<0 && im>=0) errordump(2);
			if(reg[rs]<0 && im<0 && reg[rs]+im>=0) errordump(2);
			if(reg[rs]+im > 1023 || reg[rs]+im <0){
				errordump(4);
				termi = 1;
			}
			if(termi) break;
			reg[rt] = data[reg[rs]+im];
			break;
		}
		case 36: //lbu
		{
			if(rt == 0){
				errordump(1);
				if(reg[rs]>=0 && reg[rs]+im<0 && im>0) errordump(2);
				if(reg[rs]<0 && im<0 && reg[rs]+im>=0) errordump(2);
				if(reg[rs]+im > 1023 || reg[rs]+im <0){
					errordump(4);
					termi = 1;
				} 
				break;
			}
			if(reg[rs]>=0 && reg[rs]+im<0 && im>0) errordump(2);
			if(reg[rs]<0 && im<0 && reg[rs]+im>=0) errordump(2);
			if(reg[rs]+im > 1023 || reg[rs]+im <0){
				errordump(4);
				termi = 1;
			}
			if(termi) break;
			unsigned int temp = (unsigned char)data[reg[rs]+im];
			reg[rt] = temp;
			break;
		}
		case 43: //sw
			if(reg[rs]>=0 && reg[rs]+im<0 && im>=0) errordump(2);
			if(reg[rs]<0 && im<0 && reg[rs]+im>=0) errordump(2);
			if(reg[rs]+im > 1020 || reg[rs]+im <0){
				errordump(4);
				termi = 1;
			} 
			if((reg[rs]+im)%4 != 0){
				errordump(5);
				termi = 1;
			} 
			if(termi) break;
			data[reg[rs]+im+3] = reg[rt];
			for(int r=2; r>=0; r--){
				data[reg[rs]+im+r] = reg[rt] >> 8*(3-r);
			}
			break;
		case 41: //sh
			
			if(reg[rs]>=0 && (reg[rs]+im)<0 && im>=0) errordump(2);
			if(reg[rs]<0 && im<0 && reg[rs]+im>=0) errordump(2);
			if(reg[rs]+im > 1022 || reg[rs]+im <0){
				 errordump(4);
				 termi = 1;
			}
			if((reg[rs]+im)%2 != 0){
				errordump(5);
				termi = 1;
			} 
			if(termi) break;
			data[reg[rs]+im+1] = reg[rt];
			data[reg[rs]+im] = reg[rt] >> 8;
			break;
		case 40: //sb
			if(reg[rs]>=0 && (reg[rs]+im)<0 && im>=0) errordump(2);
			if(reg[rs]<0 && im<0 && reg[rs]+im>=0) errordump(2);
			if(reg[rs]+im > 1023 || reg[rs]+im <0){
				errordump(4);	
				termi = 1;
			}  
			if(termi) break;
			data[reg[rs]+im] = reg[rt];
			break;
		case 15: //lui
			if(rt == 0){
				errordump(1);
				break;
			}
			reg[rt] = im << 16;
			break;
		case 12: //andi
			if(rt == 0){
				errordump(1);
				break;
			}
			reg[rt] = (reg[rs] & imu);
			break;
		case 13: //ori
			if(rt == 0){
				errordump(1);
				break;
			}
			reg[rt] = (reg[rs] | imu);
			break;
		case 14: //nori
			if(rt == 0){
				errordump(1);
				break;
			}
			reg[rt] = ~(reg[rs] | imu);
			break;
		case 10: //slti
			if(rt == 0){
				errordump(1);
				break;
			}
			reg[rt] = (reg[rs] < im);
			break;
		case 4: //beq
			if(reg[rs] == reg[rt]) reg[34] = reg[34]+4*im;
			break;
		case 5: //bne
			if(reg[rs] != reg[rt]) reg[34] = reg[34]+4*im;
			break;
		case 7: //bgtz
			if(reg[rs] > 0) reg[34] = reg[34]+4*im;
			break;
		case 2: //j
			reg[34] = (((reg[34]+4) >> 28) << 28) | addr << 2;
			jump = 1;
			break;
		case 3: //jal
			jump = 1;
			reg[31] = reg[34]+4;
			reg[34] = (((reg[34]+4) >> 28) << 28) | addr << 2;
			break;
		case 63: //halt
			termi = 1;
			break;
		default: break;
	}
}
