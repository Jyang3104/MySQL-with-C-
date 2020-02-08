/*
#ifndef DBS_EMP_H
#define DBS_EMP_H
#include <iostream>
#include <mysql.h>
namespace dbs
{
	struct Employee {
		int employeeNumber;
		char lastName[50];
		char firstName[50];
		char email[100];
		char phone[50];
		char extension[10];
		char reportTo[100];
		char jobTitle[50];
		char city[50];
	};

	class EmployeeList {
		struct Employee tempEmployee;
		
		
	public:
	
		int menu();
		void findEmployee(MYSQL* conn);
		void display(int ty);
		void displayAll(MYSQL* conn);
		void insertEmployee(MYSQL* conn);
		void updateEmployee(MYSQL* conn);
		void deleteEmployee(MYSQL* conn);
		char* fullName(const char*, const char*);
		



	};
	

}
#endif

*/