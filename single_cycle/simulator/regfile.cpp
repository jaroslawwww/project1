#include "regfile.h"
using namespace std;

map<int, int> reg;
char data[1024];
char instruct[1024];
int cycle = 0;
bool termi = 0;
int error3 = 0;
int jump = 0;
FILE* file_ptr;


void regset()
{
	reg[0] = 0; //zero
	reg[1] = 0; //at
	reg[2] = 0; //v0
	reg[3] = 0;	//v1
	reg[4] = 0; //a0
	reg[5] = 0; //a1
	reg[6] = 0; //a2
	reg[7] = 0; //a3
	reg[8] = 0; //t0
	reg[9] = 0; //t1
	reg[10] = 0; //t2
	reg[11] = 0; //t3
	reg[12] = 0; //t4
	reg[13] = 0; //t5
	reg[14] = 0; //t6
	reg[15] = 0; //t7
	reg[16] = 0; //s0
	reg[17] = 0; //s1
	reg[18] = 0; //s2
	reg[19] = 0; //s3
	reg[20] = 0; //s4
	reg[21] = 0; //s5
	reg[22] = 0; //s6
	reg[23] = 0; //s7
	reg[24] = 0; //t8
	reg[25] = 0; //t9
	reg[26] = 0; //k0
	reg[27] = 0; //k1
	reg[28] = 0; //gp
	reg[29] = 0; //sp
	reg[30] = 0; //fp
	reg[31] = 0; //ra
	reg[32] = 0; //hi
	reg[33] = 0; //lo
	reg[34] = 0; //pc
}