#include <iostream>
#include <stdio.h>
#include <string>
#include <string.h>
#include "allinstruction.h"
#include "regfile.h"
#include "errordetect.h"
using namespace std;

int main()
{	
	char buffer[4];
	int i = -1, index = 0, max = 0;
	regset();
	FILE *fp, *result;
	fpos_t pos;
	fp = fopen("dimage.bin", "rb");
	result = fopen("snapshot.rpt", "w");
	file_ptr = fopen("error_dump.rpt", "w");
	if(!fp) return 1;
	
	while(i++<257){
		if(i>1+max) break;
		int temp = 0;
		fread(buffer, sizeof(char), 4, fp);
		if(i == 0){
			temp = (unsigned char)buffer[0];
			for(int y=1; y<4; y++){
				temp = temp << 8;
				temp = (temp | (unsigned char)buffer[y]);
			}
			reg[29] = temp;
		}else if(i == 1){
			max = (unsigned char)buffer[0];
			for(int y=1; y<4; y++){
				max = max<< 8;
				max = (max | (unsigned char)buffer[y]);
			}
		}else if(i > 1){
			data[index++] = buffer[0];
			data[index++] = buffer[1];
			data[index++] = buffer[2];
			data[index++] = buffer[3];
		}
	}
	fclose(fp);
	fp = fopen("iimage.bin", "rb");
	if(!fp) return 1;
	i = -1, index = 0;
	while(i++<257){
		if(i>1+max) break;
		int temp = 0;
		fread(buffer, sizeof(char), 4, fp);
		if(i == 0){
			temp = (unsigned char)buffer[0];
			for(int y=1; y<4; y++){
				temp = temp << 8;
				temp = (temp | (unsigned char)buffer[y]);
			}
			reg[34] = temp;
			index = reg[34];
		}else if(i == 1){
			max = (unsigned char)buffer[0];
			for(int y=1; y<4; y++){
				max = max<< 8;
				max = (max | (unsigned char)buffer[y]);
			}
		}else if(i > 1){
			instruct[index++] = buffer[0];
			instruct[index++] = buffer[1];
			instruct[index++] = buffer[2];
			instruct[index++] = buffer[3];
		}
	}
	fprintf(result, "cycle %d\n", cycle);
	for(int j=0; j<35; j++){
		if(j<10) fprintf(result, "$0%d: 0x%08X\n", j, reg[j]);
		else if(j<32) fprintf(result, "$%d: 0x%08X\n", j, reg[j]);
		else if(j==32) fprintf(result, "$HI: 0x%08X\n", reg[j]);
		else if(j==33) fprintf(result, "$LO: 0x%08X\n", reg[j]);
		else fprintf(result, "PC: 0x%08X\n", reg[j]);
	}
	fprintf(result, "\n\n");
	while(1){
		int diff[35], x;
		for(x=0; x<35; x++) diff[x] = reg[x];
		//if(termi) break;
		cycle++;
		instruction(&instruct[reg[34]]);
		if(termi) break;
		if(jump != 1) reg[34] += 4;
		else jump = 0;
		fprintf(result, "cycle %d\n", cycle);
		for(x=0; x<35; x++){
			if(diff[x] != reg[x]) {
				if(x<10) fprintf(result, "$0%d: 0x%08X\n", x, reg[x]);
				else if(x<32) fprintf(result, "$%d: 0x%08X\n", x, reg[x]);
				else if(x==32) fprintf(result, "$HI: 0x%08X\n", reg[x]);
				else if(x==33) fprintf(result, "$LO: 0x%08X\n", reg[x]);
				else fprintf(result, "PC: 0x%08X\n", reg[x]);
			}
		}
		fprintf(result, "\n\n");
	}
	fclose(result);
	fclose(fp);
	fclose(file_ptr);
	
	return 0;
}
