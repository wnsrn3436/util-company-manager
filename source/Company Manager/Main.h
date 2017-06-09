#pragma once

#include "Menu.h"
#include "Company.h"

#define COMPANY_FILE "CompanyDB.txt"
#define COMMAND_STRBUF 256

void CallBackMenu(Menu *);
void CallBackA(Menu *, Company *);
void CallBackB(Menu *, Company *);
void CallBackC(Menu *, Company *);
void CallBackD(Menu *, Company *);
void CallBackE(Menu *, Company *);
void CallBackF(Menu *, Company *);
void GetEmpID(char *);
void GetEmpName(char *);
char GetEmpGender();
void GetEmpState(Employee *);
char GetEmpDepartment();
int GetEmpPosition();
char GetEmpSalaryRank();
int GetEmpWorkedHour();
int GetEmpPayPerHour();