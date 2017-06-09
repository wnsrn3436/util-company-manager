#include <stdio.h>
#include <malloc.h>
#include <string.h>
#include "Company.h"
#include "Employee.h"
#include "TypeTag.h"
#include "List.h"

#pragma warning(disable:4996)

Company *NewCompany()
{
	Company *company = (Company *)malloc(sizeof(Company));
	company->Worker = NewList(sizeof(Employee));
	company->Count = 0;
	company->LoadAllEmployee = _CompanyLoadAllEmployee;
	company->SaveEmployee = _CompanySaveEmployee;
	company->SaveAllEmployee = _CompanySaveAllEmployee;
	company->AddEmployee = _CompanyAddEmployee;
	company->IndexOf = _CompanyIndexOf;
	company->Dispose = _CompanyDispose;
	return company;
}

bool _CompanyLoadAllEmployee(Company *company, char *fileName)
{
	FILE *file = fopen(fileName, "r");
	if (file != NULL)
	{
		while (!feof(file))
		{
			Employee emp = NewEmployee();
			fscanf(file, "%s %s %d %d ", emp.ID, emp.Name, &(emp.Gender), &(emp.RemarksTag));

			if (emp.RemarksTag == HAS_INT)
				fscanf(file, "%d ", &(emp.Remarks.Vacation));
			else if (emp.RemarksTag == HAS_STRING)
				fscanf(file, "%s ", emp.Remarks.State);

			if (emp.ID[0] == ID_FULL_TIME)
				fscanf(file, "%d %d %d\n", &(emp.Job.FullTime.Department), &(emp.Job.FullTime.Position), &(emp.Job.FullTime.SalaryRank));
			else if (emp.ID[0] == ID_PART_TIME)
				fscanf(file, "%d %d\n", &(emp.Job.PartTime.WorkedHour), &(emp.Job.PartTime.PayPerHour));

			company->AddEmployee(company, &emp);
		}
		fclose(file);
		return true;
	}
	else
		return false;
}

bool _CompanySaveEmployee(Employee *emp, char *fileName)
{
	FILE *file = fopen(fileName, "a");
	if (file != NULL)
	{
		fprintf(file, "%s %s %d %d ", emp->ID, emp->Name, emp->Gender, emp->RemarksTag);

		if (emp->RemarksTag == HAS_INT)
			fprintf(file, "%d ", emp->Remarks.Vacation);
		else if (emp->RemarksTag == HAS_STRING)
			fprintf(file, "%s ", emp->Remarks.State);

		if (emp->ID[0] == ID_FULL_TIME)
			fprintf(file, "%d %d %d\n", emp->Job.FullTime.Department, emp->Job.FullTime.Position, emp->Job.FullTime.SalaryRank);
		else if (emp->ID[0] == ID_PART_TIME)
			fprintf(file, "%d %d\n", emp->Job.PartTime.WorkedHour, emp->Job.PartTime.PayPerHour);

		fclose(file);
		return true;
	}
	else
		return false;
}

bool _CompanySaveAllEmployee(Company *company, char *fileName)
{
	FILE *file;
	if ((file = fopen(fileName, "w")) == NULL)
		return false;
	fclose(file);

	for (int i = 0; i < company->Count; i++)
	{
		Employee *emp = (Employee *)company->Worker->Get(company->Worker, i);
		_CompanySaveEmployee(emp, fileName);
	}

	return true;
}

void _CompanyAddEmployee(Company *company, Employee *emp)
{
	company->Worker->Add(company->Worker, emp);
	++(company->Count);
}

int _CompanyIndexOf(Company *company, char *empID)
{
	for (int i = 0; i < company->Count; i++)
	{
		Employee *emp = (Employee *)(company->Worker->Get(company->Worker, i));
		if (strcmp(empID, emp->ID) == 0)
			return i;
	}
	return -1;
}

void _CompanyDispose(Company *company)
{
	company->Worker->Dispose(company->Worker);
	free(company);
}