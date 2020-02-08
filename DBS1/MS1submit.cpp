/*

DBS milestone 1 +milestone 2


Jianwen Yang 153169180
Anna Chervonnaya 121433197
DO HUU DUY 157235185
Luciana Gonzaga Altermann 129855185









*/
#define _CRT_SECURE_NO_WARNINGS
#include <iomanip>
#include <iostream>
#include <cstring>
#include <mysql.h>
#include <sstream>
using namespace std;


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


int main() {
	MYSQL* conn;
	conn = mysql_init(0);
	conn = mysql_real_connect(conn, "mymysql.senecacollege.ca", "db_jyang219", "8:(sBhvId8", "db_jyang219", 3306, nullptr, 0);
	if (conn) {

		cout << "*********************HR Menu*********************" << endl << endl;


		int option = 6;
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

//To form the full name using strcat
char* EmployeeList::fullName(const char* str1, const char* str2) {
	char tempN[100];
	strcpy(tempN, str1);
	strcat(tempN, " ");
	strcat(tempN, str2);
	return tempN;
}

//Display menu, and get result from user
int EmployeeList::menu() {



	cout << "1) Find Employee" << endl;
	cout << "2) Employees Report" << endl;
	cout << "3) Add Employee" << endl;
	cout << "4) Update Employee" << endl;
	cout << "5) Remove Employee" << endl;
	cout << "0) Exit" << endl;
	bool  ok = false;
	int option;
	while (!ok) {
		cin >> option;
		if (cin.fail() || cin.get() != '\n') {
			cin.clear();
			cin.ignore(1000, '\n');
			cout << "Invalid input, Enter again: ";
		}
		else {
			if (option > 5 || option < 0) {
				cout << "Invalid input, Enter again: ";
			}
			else {
				ok = true;
			}

		}
	}

	return option;

}

//Display employees, mode1: 1person mode, mode2: list mode
void EmployeeList::display(int ty) {
	if (ty == 1) {
		cout << "employeeNumber = " << tempEmployee.employeeNumber << endl;
		cout << "lastName = " << tempEmployee.lastName << endl;
		cout << "firstName = " << tempEmployee.firstName << endl;
		cout << "email = " << tempEmployee.email << endl;
		cout << "phone = " << tempEmployee.phone << endl;
		cout << "extension = " << tempEmployee.extension << endl;
		cout << "reportsTo = " << tempEmployee.reportTo << endl;
		cout << "jobTitle = " << tempEmployee.jobTitle << endl;
		cout << "city = " << tempEmployee.city << endl;
	}
	else if (ty == 2) {
		char temName[100];
		strcpy(temName, fullName(tempEmployee.firstName, tempEmployee.lastName));
		cout << setw(10) << left << tempEmployee.employeeNumber;
		cout << setw(27) << left << temName;
		cout << setw(36) << left << tempEmployee.email;
		cout << setw(20) << left << tempEmployee.phone;
		cout << setw(10) << left << tempEmployee.extension;
		cout << setw(30) << left << tempEmployee.reportTo << endl;

	}


}

//find employee function
void EmployeeList::findEmployee(MYSQL* conn) {
	//create the query to get the employee
	string query = "SELECT * FROM employees JOIN offices USING(officeCode) WHERE employeeNumber=";
	cout << "Please input employee ID(4 digits): ";
	int fID;
	//make integer from user input into string
	cin >> fID;
	stringstream str;
	str << fID;
	string num = str.str();
	query = query + num + ';';
	//create pointer to the query
	const char* q = query.c_str();
	//excute the query and check if it works
	int exequery = mysql_query(conn, q);
	if (!exequery) {
		// create the res object to  store the whole data from database
		MYSQL_RES* res;
		res = mysql_store_result(conn);
		//create a row object to make the result into a row 
		MYSQL_ROW row = mysql_fetch_row(res);
		//if the row is NULL, it means no this employee
		if (row == NULL) {
			cout << "EMPLOYEE "<<fID<<" DOES NOT EXIST!" << endl;
		}
		else {
			//save all data into the temp structure
			tempEmployee.employeeNumber = fID;
			strcpy(tempEmployee.lastName, row[2]);
			strcpy(tempEmployee.firstName, row[3]);
			strcpy(tempEmployee.email, row[5]);
			strcpy(tempEmployee.phone, row[9]);
			strcpy(tempEmployee.extension, row[4]);
			strcpy(tempEmployee.jobTitle, row[7]);
			strcpy(tempEmployee.city, row[8]);
			char repoID[6];


			//get the 'report to' name
			if (row[6] == NULL) {
				strcpy(tempEmployee.reportTo, "She is the president!");
			}
			else {

				strcpy(repoID, row[6]);
				string query2 = "SELECT * FROM employees WHERE employeeNumber=";
				query2 = query2 + repoID + ';';
				const char* q2 = query2.c_str();
				int exequery = mysql_query(conn, q2);
				MYSQL_RES* repoRes;
				repoRes = mysql_store_result(conn);
				MYSQL_ROW row2 = mysql_fetch_row(repoRes);
				strcpy(tempEmployee.reportTo, fullName(row2[2], row2[1]));

			}
			display(1);
		}
	}

}



void EmployeeList::displayAll(MYSQL* conn) {
	cout << "Emp ID    Emp Name                   Email                               Phone               ext       Manager" << endl;
	cout << "-------------------------------------------------------------------------------------------------------" << endl << endl;
	string query = "SELECT * FROM employees JOIN offices using(officeCode);";
	const char* q = query.c_str();
	int exequery = mysql_query(conn, q);
	int totalEmp = 0;
	if (!exequery) {
		MYSQL_RES* res;
		res = mysql_store_result(conn);
		MYSQL_ROW row;
		while (row = mysql_fetch_row(res)) {

			tempEmployee.employeeNumber = atoi(row[1]);
			strcpy(tempEmployee.lastName, row[2]);
			strcpy(tempEmployee.firstName, row[3]);
			strcpy(tempEmployee.email, row[5]);
			strcpy(tempEmployee.phone, row[9]);
			strcpy(tempEmployee.extension, row[4]);
			strcpy(tempEmployee.jobTitle, row[7]);
			strcpy(tempEmployee.city, row[8]);
			char repoID[6];


			//get the 'report to' name
			if (row[6] == NULL) {
				strcpy(tempEmployee.reportTo, "She is the president!");
			}
			else {

				strcpy(repoID, row[6]);
				string query2 = "SELECT * FROM employees WHERE employeeNumber=";
				query2 = query2 + repoID + ';';
				const char* q2 = query2.c_str();
				int exequery = mysql_query(conn, q2);
				MYSQL_RES* repoRes;
				repoRes = mysql_store_result(conn);
				MYSQL_ROW row2 = mysql_fetch_row(repoRes);
				strcpy(tempEmployee.reportTo, fullName(row2[2], row2[1]));
			}

			display(2);

			totalEmp++;
		}
		if (totalEmp == 0) {
			cout << "There is no employee's infomation to be displayed!" << endl;
		}
		else {
			cout << "-------------------------------------------------------------------------------------------------------" << endl;
			cout << "Total Employees: " << totalEmp << endl;

		}
	}
}
void EmployeeList::insertEmployee(MYSQL* conn) {
	
	int newID;
	cout << "Employee Number: ";
	bool ok=false;
	while (!ok) {
	 cin >> newID;
	 if (cin.fail()) {
		 cout << "invalid employee number, input again: ";
		 cin.clear();
		 cin.ignore(1000, '\n');
	 }
	 else {

		 if (newID < 1000 || newID>9999) {
			 cout << "invalid employee number, input again: ";
		 }
		 else {
			 ok = true;
		 }
	 }
	}
	
	stringstream str;
	str << newID;
	string eID = str.str();
	

	string query1 = "SELECT * FROM employees WHERE employeeNumber=" + eID+";";
	const char* q1 = query1.c_str();
	int exequery1 = mysql_query(conn, q1);
	if (!exequery1) {

		MYSQL_RES* res;
		res = mysql_store_result(conn);
		MYSQL_ROW row = mysql_fetch_row(res);

		if (row == NULL) {
			cout << "Last Name: ";
			cin >> tempEmployee.lastName;
			cout << "First Name: ";
			cin >> tempEmployee.firstName;
			cout << "Email: ";
			cin >> tempEmployee.email;
			cout << "Extension: ";
			cin >> tempEmployee.extension;
			cout << "Job Title: ";
			cin >> tempEmployee.jobTitle;
			cout << "City: ";
			cin >> tempEmployee.city;

			string query2 = "INSERT INTO employees VALUES (" + eID + ", '" + tempEmployee.firstName + "', '" + tempEmployee.lastName + "', '" + tempEmployee.extension + "', '" + tempEmployee.email + "', 1, 1002, '" + tempEmployee.jobTitle + "');";
			const char* q2 = query2.c_str();
			int exequery2 = mysql_query(conn, q2);
			if (!exequery2) {
				cout << "INSERTED" << endl;
			}
		}
		else {
			cout << "An employee with the same employee number exists." << endl;
		}
	}
}
void EmployeeList::updateEmployee(MYSQL* conn) {
	string eID;
	cout << "Employee Number: ";
	cin >> eID;

	string query1 = "SELECT * FROM employees WHERE employeeNumber=" + eID+";";
	const char* q1 = query1.c_str();
	int exequery1 = mysql_query(conn, q1);
	if (!exequery1) {
		MYSQL_RES* res;
		res = mysql_store_result(conn);
		MYSQL_ROW row = mysql_fetch_row(res);

		if (row == NULL) {
			cout << "No this ID!" << endl;
		}
		else {
			cout << "Old extenshion: " << row[3] << endl;
			cout << "New Extension: ";
			cin >> tempEmployee.extension;
			string str2 = "UPDATE employees SET extension= '";
			string query2 = str2 + tempEmployee.extension + "' WHERE employeeNumber=" + eID + ";";
			const char* q2 = query2.c_str();
			int exequery2 = mysql_query(conn, q2);
			if (!exequery2) {
				cout << "UPDATED" << endl;
			}
		}

	}
}
void EmployeeList::deleteEmployee(MYSQL* conn) {
	string eID;
	cout << "Employee Number: ";
	cin >> eID;

	string query1 = "SELECT * FROM employees WHERE employeeNumber=" + eID+";";
	const char* q1 = query1.c_str();
	int exequery1 = mysql_query(conn, q1);
	if (!exequery1) {
		MYSQL_RES* res;
		res = mysql_store_result(conn);
		MYSQL_ROW row = mysql_fetch_row(res);

		if (row == NULL) {
			cout << "No this ID!" << endl;
		}
		else {
			string query2 = "DELETE FROM employees WHERE employeeNumber=" + eID+';';
			const char* q2 = query2.c_str();
			int exequery2 = mysql_query(conn, q2);
			if (!exequery2) {
				cout << "DELETED" << endl;
			}
		}

	}
}