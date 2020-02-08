/*
#define _CRT_SECURE_NO_WARNINGS
#include <iomanip>
#include <iostream>
#include <cstring>
#include <mysql.h>
using namespace std;
#include "EmployeeList.h"
using namespace dbs;

int main() {
	MYSQL* conn;
	conn = mysql_init(0);
	conn = mysql_real_connect(conn, "mymysql.senecacollege.ca", "db_jyang219", "8:(sBhvId8", "db_jyang219", 3306, nullptr, 0);
if(conn){

	cout << "*********************HR Menu*********************" << endl << endl;


	int option=6;
	EmployeeList emp;
	while (option != 0) {
		option = emp.menu();
		if (option == 1) {
			emp.findEmployee(conn);	
			cout << endl << endl;
		}
		else if (option == 2) {
			emp.displayAll(conn);
			cout << endl << endl;
		}
		else if (option == 3) {
			emp.insertEmployee(conn);
			cout << endl << endl;
		}
		else if (option == 4) {
			emp.updateEmployee(conn);
			cout << endl << endl;
		}
		else if (option == 5) {
			emp.deleteEmployee(conn);
			cout << endl << endl;
		}
		else {
			cout << "exit" << endl;
		}
	
	
	}

	mysql_close(conn);
	}
	return 0;

}
*/
