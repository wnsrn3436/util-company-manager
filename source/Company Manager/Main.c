#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <limits.h>
#include "Main.h"
#include "Menu.h"
#include "Company.h"
#include "Employee.h"
#include "TypeTag.h"
#include "InputExt.h"

int main()
{
	system("mode con: lines=30 cols=81");

	Menu *menu = NewMenu("");
	CallBackMenu(menu);

	Company *company = NewCompany();
	company->LoadAllEmployee(company, COMPANY_FILE);

	char command[COMMAND_STRBUF];
	while (true)
	{
		printf("메뉴 명령어 : ");
		gets_s(command, COMMAND_STRBUF);
		void(*callback)(Menu *, Company *) = menu->Command(menu, command);
		if (callback != NULL)
		{
			system("cls");
			callback(menu, company);
		}
		else
			printf("> 잘못된 명령어입니다. ");
	}

	company->Dispose(company);
	menu->Dispose(menu);
	return 0;
}

void CallBackMenu(Menu *menu)
{
	menu->ClearCommand(menu);
	menu->SetText(menu, "--------------------------------------------------------------------------------\n                             직원관리 프로그램 v1.0                             \n--------------------------------------------------------------------------------\n\na : 직원정보 조회\nb : 부서별 직원명단 출력\nc : 직원정보 급여 순 출력\nd : 신입직원 등록\ne : 신분변동 처리\nf : 프로그램 종료\n\n--------------------------------------------------------------------------------\n                                 by. wnsrn3436                                  \n--------------------------------------------------------------------------------\n");
	menu->AddCommand(menu, "a", CallBackA);
	menu->AddCommand(menu, "b", CallBackB);
	menu->AddCommand(menu, "c", CallBackC);
	menu->AddCommand(menu, "d", CallBackD);
	menu->AddCommand(menu, "e", CallBackE);
	menu->AddCommand(menu, "f", CallBackF);
	puts(menu->GetText(menu));
}

void CallBackA(Menu *menu, Company *company)
{
	menu->ClearCommand(menu);
	menu->SetText(menu, "--------------------------------------------------------------------------------\n                                  직원정보 조회                                 \n--------------------------------------------------------------------------------\n\nback : 메인메뉴\n\n--------------------------------------------------------------------------------\n");
	menu->AddCommand(menu, "back", CallBackMenu);
	puts(menu->GetText(menu));

	char search[COMMAND_STRBUF];
	GetEmpID(search);

	int searchIndex = company->IndexOf(company, search);
	if (searchIndex != -1)
	{
		Employee *emp = (Employee *)(company->Worker->Get(company->Worker, searchIndex));
		emp->Print(emp);
		printf("\n--------------------------------------------------------------------------------\n\n");
	}
	else
		printf("> 등록되지 않은 사원입니다.\n");
}

void CallBackB(Menu *menu, Company *company)
{
	menu->ClearCommand(menu);
	menu->SetText(menu, "--------------------------------------------------------------------------------\n                               부서별 직원명단 출력                             \n--------------------------------------------------------------------------------\n\nback : 메인메뉴\n\n--------------------------------------------------------------------------------\n");
	menu->AddCommand(menu, "back", CallBackMenu);
	puts(menu->GetText(menu));

	enum EmployeeDepartment search = GetEmpDepartment();

	for (int i = 0; i < company->Count; i++)
	{
		Employee *emp = (Employee *)(company->Worker->Get(company->Worker, i));
		if (emp->ID[0] == ID_FULL_TIME && emp->Job.FullTime.Department == search)
			emp->Print(emp);
	}

	printf("\n--------------------------------------------------------------------------------\n\n");
}

void CallBackC(Menu *menu, Company *company)
{
	menu->ClearCommand(menu);
	menu->SetText(menu, "--------------------------------------------------------------------------------\n                               직원정보 급여 순 출력                            \n--------------------------------------------------------------------------------\n\nback : 메인메뉴\n\n--------------------------------------------------------------------------------\n");
	menu->AddCommand(menu, "back", CallBackMenu);
	puts(menu->GetText(menu));

	for (int i = 0; i < company->Count - 1; i++)
	{
		for (int j = i + 1; j < company->Count; j++)
		{
			bool isCompared = false;
			Employee emp = *(Employee *)(company->Worker->Get(company->Worker, i));
			Employee emp2 = *(Employee *)(company->Worker->Get(company->Worker, j));
			if (emp.ID[0] == ID_FULL_TIME && emp2.ID[0] == ID_FULL_TIME)
			{
				if (emp.Job.FullTime.Position > emp2.Job.FullTime.Position)
					isCompared = true;
				else if (emp.Job.FullTime.Position == emp2.Job.FullTime.Position)
					isCompared = emp.Job.FullTime.SalaryRank > emp2.Job.FullTime.SalaryRank;
			}
			else if (emp.ID[0] == ID_PART_TIME && emp2.ID[0] == ID_PART_TIME)
				isCompared = emp.Job.PartTime.PayPerHour < emp2.Job.PartTime.PayPerHour;

			if (isCompared)
			{
				company->Worker->Replace(company->Worker, i, &emp2);
				company->Worker->Replace(company->Worker, j, &emp);
			}
		}
	}

	printf("[ 정직원 ]\n");
	for (int i = 0; i < company->Count; i++)
	{
		Employee *emp = (Employee *)(company->Worker->Get(company->Worker, i));
		if (emp->ID[0] == ID_FULL_TIME)
			emp->Print(emp);
	}

	printf("\n[ 아르바이트 ]\n");
	for (int i = 0; i < company->Count; i++)
	{
		Employee *emp = (Employee *)(company->Worker->Get(company->Worker, i));
		if (emp->ID[0] == ID_PART_TIME)
			emp->Print(emp);
	}

	printf("\n--------------------------------------------------------------------------------\n\n");
}

void CallBackD(Menu *menu, Company *company)
{
	menu->ClearCommand(menu);
	menu->SetText(menu, "--------------------------------------------------------------------------------\n                                   신입직원 등록                                \n--------------------------------------------------------------------------------\n\nback : 메인메뉴\n\n--------------------------------------------------------------------------------\n");
	menu->AddCommand(menu, "back", CallBackMenu);
	puts(menu->GetText(menu));

	Employee emp = NewEmployee();

	while (true)
	{
		GetEmpID(emp.ID);
		if (company->IndexOf(company, emp.ID) == -1)
			break;
		else
			printf("> 이미 등록된 사원입니다. 다시 입력해주세요 : ");
	}
	GetEmpName(emp.Name);
	emp.Gender = GetEmpGender();
	GetEmpState(&emp);

	if (emp.ID[0] == ID_FULL_TIME)
	{
		emp.Job.FullTime.Department = GetEmpDepartment();
		emp.Job.FullTime.Position = GetEmpPosition();
		emp.Job.FullTime.SalaryRank = GetEmpSalaryRank();
		if (emp.RemarksTag == HAS_INT) emp.Remarks.Vacation = 10 - emp.Job.FullTime.Position;
	}
	else if (emp.ID[0] == ID_PART_TIME)
	{
		emp.Job.PartTime.WorkedHour = GetEmpWorkedHour();
		emp.Job.PartTime.PayPerHour = GetEmpPayPerHour();
		if (emp.RemarksTag == HAS_INT) emp.Remarks.Vacation = 1;
	}

	company->AddEmployee(company, &emp);
	company->SaveEmployee(&emp, COMPANY_FILE);

	printf("신입직원 등록완료.\n");
	printf("--------------------------------------------------------------------------------\n\n");
}

void CallBackE(Menu *menu, Company *company)
{
	menu->ClearCommand(menu);
	menu->SetText(menu, "--------------------------------------------------------------------------------\n                                   신분변동 처리                                \n--------------------------------------------------------------------------------\n\nback : 메인메뉴\n\n--------------------------------------------------------------------------------\n");
	menu->AddCommand(menu, "back", CallBackMenu);
	puts(menu->GetText(menu));

	char search[COMMAND_STRBUF];
	GetEmpID(search);

	int searchIndex = company->IndexOf(company, search);
	if (searchIndex != -1)
	{
		Employee emp = *(Employee *)(company->Worker->Get(company->Worker, searchIndex));

		GetEmpState(&emp);
		emp.Job.FullTime.Department = GetEmpDepartment();
		emp.Job.FullTime.Position = GetEmpPosition();
		emp.Job.FullTime.SalaryRank = GetEmpSalaryRank();
		if (emp.RemarksTag == HAS_INT) emp.Remarks.Vacation = 10 - emp.Job.FullTime.Position;

		company->Worker->Replace(company->Worker, searchIndex, &emp);
		company->SaveAllEmployee(company, COMPANY_FILE);

		printf("신분변동 완료.\n");
		printf("--------------------------------------------------------------------------------\n\n");
	}
	else
		printf("> 등록되지 않은 사원입니다.\n");
}

void CallBackF(Menu *menu, Company *company)
{
	menu->ClearCommand(menu);
	menu->SetText(menu, "프로그램을 종료합니다.");
	menu->AddCommand(menu, "back", CallBackMenu);
	puts(menu->GetText(menu));

	exit(0);
}

void GetEmpID(char *dest)
{
	printf("TIP.\n");
	printf("사원[R]/아르바이트[A][##]\n\n");
	printf("사원번호 : ");
	while (true)
	{
		GetLimitedString(dest, 3, 3);
		if ((dest[0] == ID_FULL_TIME || dest[0] == ID_PART_TIME) && (atoi(dest + 1) > 0 && atoi(dest + 1) < 100))
			break;
		else
			printf("> 잘못된 사원번호입니다. 다시 입력해주세요 : ");
	}
	printf("--------------------------------------------------------------------------------\n\n");
}

void GetEmpName(char *dest)
{
	printf("이름(최대10글자) : ");
	GetLimitedString(dest, 1, 10);
	printf("--------------------------------------------------------------------------------\n\n");
}

char GetEmpGender()
{
	char gender;
	printf("남성[M]/여성[F] : ");
	while (true)
	{
		gender = GetOnlyChar();
		if (gender == GENDER_MAN || gender == GENDER_WOMAN)
		{
			printf("--------------------------------------------------------------------------------\n\n");
			return gender;
		}
		else
			printf("> 잘못된 성별입니다. 다시 입력해주세요 : ");
	}
}

void GetEmpState(Employee *emp)
{
	printf("직원상태메모[Y]/메모안함[N] : ");
	while (true)
	{
		char state = GetOnlyChar();
		if (state == 'Y')
		{
			printf("직원상태 : ");
			gets_s(emp->Remarks.State, EMPLOYEE_STRBUF);
			emp->RemarksTag = HAS_STRING;
			break;
		}
		else if (state == 'N')
		{
			emp->RemarksTag = HAS_INT;
			break;
		}
		else
			printf("> 잘못된 입력입니다. 다시 입력해주세요 : ");
	}
	printf("--------------------------------------------------------------------------------\n\n");
}

char GetEmpDepartment()
{
	printf("TIP.\n");
	for (int i = 0; i < EMP_DEPT_LEN; i++)
	{
		printf("%s[%c] ", EmployeeDepartment[i], EMP_DEPT_START + i);
	}
	printf("\n\n소속부서 : ");
	char department = GetLimitedChar(EMP_DEPT_START, EMP_DEPT_END);
	printf("--------------------------------------------------------------------------------\n\n");
	return department;
}

int GetEmpPosition()
{
	printf("TIP.\n");
	for (int i = 0; i < EMP_POS_LEN; i++)
	{
		printf("%s[%d] ", EmployeePosition[i], EMP_POS_START + i);
	}
	printf("\n\n직급 : ");
	int position = GetLimitedInteger(EMP_POS_START, EMP_POS_END);
	printf("--------------------------------------------------------------------------------\n\n");
	return position;
}

char GetEmpSalaryRank()
{
	printf("TIP.\n");
	for (int i = 0; i < EMP_RANK_LEN; i++)
	{
		printf("%s[%c] ", EmployeeSalaryRank[i], EMP_RANK_START + i);
	}
	printf("\n\n호봉 : ");
	char salaryRank = GetLimitedChar(EMP_RANK_START, EMP_RANK_END);
	printf("--------------------------------------------------------------------------------\n\n");
	return salaryRank;
}

int GetEmpWorkedHour()
{
	printf("근무시간 : ");
	int workedHour = GetLimitedInteger(0, INT_MAX);
	printf("--------------------------------------------------------------------------------\n\n");
	return workedHour;
}

int GetEmpPayPerHour()
{
	printf("시간당급여 : ");
	int payPerHour = GetLimitedInteger(0, INT_MAX);
	printf("--------------------------------------------------------------------------------\n\n");
	return payPerHour;
}