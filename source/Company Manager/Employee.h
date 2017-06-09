#pragma once

#include "TypeTag.h"
#include "StringExt.h"

#define EMPLOYEE_STRBUF 256

enum EmployeeID
{
	ID_FULL_TIME = 'R',
	ID_PART_TIME = 'A'
};

enum EmployeeGender
{
	GENDER_MAN = 'M',
	GENDER_WOMAN = 'F'
};

enum EmployeeDepartment
{
	ACCOUNTING = 'A', //경리부
	DIVISION, //사업부
	MARKETING, //마케팅부
	PLANNING, //기획실
	RELATION, //홍보부
};
#define EMP_DEPT_START ACCOUNTING
#define EMP_DEPT_END RELATION
#define EMP_DEPT_LEN 5
const char *EmployeeDepartment[];

enum EmployeePosition
{
	DIRECTOR, //대표이사
	GENERAL, //부장
	DEPUTY_GENERAL, //차장
	MANAGER, //과장
	ASSISTANT, //대리
	STAFF //사원
};
#define EMP_POS_START DIRECTOR
#define EMP_POS_END STAFF
#define EMP_POS_LEN 6
const char *EmployeePosition[];

enum EmployeeSalaryRank
{
	A_RANK = 'A',
	B_RANK,
	C_RANK,
	D_RANK,
	E_RANK,
	F_RANK
};
#define EMP_RANK_START A_RANK
#define EMP_RANK_END F_RANK
#define EMP_RANK_LEN 6
const char *EmployeeSalaryRank[];

union EmployeeRemarks
{
	char State[EMPLOYEE_STRBUF];
	int Vacation;
};

typedef struct _Employee
{
	char ID[EMPLOYEE_STRBUF];
	char Name[EMPLOYEE_STRBUF];
	enum EmployeeGender Gender;
	enum TypeTag RemarksTag;
	union EmployeeRemarks Remarks;
	union
	{
		struct
		{
			enum EmployeeDepartment Department;
			enum EmployeePosition Position;
			enum EmployeeSalaryRank SalaryRank;
		} FullTime;
		struct
		{
			int WorkedHour;
			int PayPerHour;
		} PartTime;
	} Job;
	void(*Print)(struct _Employee *);
} Employee;

Employee NewEmployee();

void _EmployeePrint(Employee *);