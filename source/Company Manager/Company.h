#pragma once

#include "Employee.h"
#include "List.h"

typedef struct _Company
{
	List *Worker;
	int Count;
	bool (*LoadAllEmployee)(struct _Company *, char *);
	bool (*SaveEmployee)(Employee *, char *);
	bool(*SaveAllEmployee)(struct _Company *, char *);
	void (*AddEmployee)(struct _Company *, Employee *);
	int (*IndexOf)(struct _Company *, char *);
	void (*Dispose)(struct _Company *);
} Company;

Company *NewCompany();

bool _CompanyLoadAllEmployee(Company *, char *);
bool _CompanySaveEmployee(Employee *, char *);
bool _CompanySaveAllEmployee(Company *, char *);
void _CompanyAddEmployee(Company *, Employee *);
int _CompanyIndexOf(Company *, char *);
void _CompanyDispose(Company *);