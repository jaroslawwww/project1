#ifndef regfile_H_INCLUDED
#define regfile_H_INCLUDED
#include <map>
#include <iostream>
#include <string>
#include <stdio.h>
using namespace std;

extern map<int, int> reg;
extern char data[1024];
extern char instruct[1024];
extern int cycle;
extern bool termi;
extern int error3;
extern int jump;
extern FILE* file_ptr;

void regset(void);

#endif