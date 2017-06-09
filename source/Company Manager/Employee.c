#include <stdio.h>
#include "Employee.h"

const char *EmployeeDepartment[] = { "경리부", "사업부", "마케팅부", "기획실", "홍보부" };
const char *EmployeePosition[] = { "대표이사", "부장", "차장", "과장", "대리", "사원" };
const char *EmployeeSalaryRank[] = { "6호봉", "5호봉", "4호봉", "3호봉", "2호봉", "1호봉" };

Employee NewEmployee()
{
	Employee emp;
	emp.Print = _EmployeePrint;
	return emp;
}

void _EmployeePrint(Employee *emp)
{
	printf("%s %s %s ", emp->ID, emp->Name, (emp->Gender == GENDER_MAN ? "남성" : "여성"));

	if (emp->RemarksTag == HAS_INT)
		printf("휴가가능일[%d] ", emp->Remarks.Vacation);
	else if (emp->RemarksTag == HAS_STRING)
		printf("메모[%s] ", emp->Remarks.State);

	if (emp->ID[0] == ID_FULL_TIME)
		printf("%s %s %s\n", EmployeeDepartment[emp->Job.FullTime.Department - EMP_DEPT_START],
			EmployeePosition[emp->Job.FullTime.Position - EMP_POS_START],
			EmployeeSalaryRank[emp->Job.FullTime.SalaryRank - EMP_RANK_START]);
	else if (emp->ID[0] == ID_PART_TIME)
		printf("근무시간[%d시간] 시간당급여[%d원]\n", emp->Job.PartTime.WorkedHour, emp->Job.PartTime.PayPerHour);
}