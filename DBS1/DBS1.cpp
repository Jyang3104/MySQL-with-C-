/*
#define _CRT_SECURE_NO_WARNINGS
#include <mysql.h>
#include <iostream>
#include <cstring>
#include <sstream>
using namespace std;




int main(void)
{
	int employeeNumber;
	char lastName[50];
	char firstName[50];
	char email[100];
	char phone[50];
	char extension[10];
	char reportTo[100];
	char jobTitle[50];
	char city[50];


	MYSQL* conn;
	conn = mysql_init(0);
	conn = mysql_real_connect(conn, "mymysql.senecacollege.ca", "db_jyang219", "8:(sBhvId8", "db_jyang219", 3306, nullptr, 0);

	if (conn) {
		cout << "successful" << endl;
	}
	else {
		cout << "fail" << endl;
	}

	string eID;
	cout << "Employee Number: ";
	cin >> eID;

	string query1 = "select * from employees where employeeNumber=" + eID;
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
			cout << "New Extension: ";
			cin >> extension;
			string str2 = "UPDATE employees SET extension= '";
			string query2 = str2 + extension + "' WHERE employeeNumber=" + eID + ";";
			const char* q2 = query2.c_str();
			int exequery2 = mysql_query(conn, q2);
			if (!exequery2) {
				cout << "success!" << endl;
			}
		}
	}

	/*

    string eID;
	cout << "Employee Number: ";
	cin >> eID;

	string query1 = "select * from employees where employeeNumber="+eID;
	const char* q1 = query1.c_str();
	int exequery1 = mysql_query(conn, q1);
	if (!exequery1) {

		MYSQL_RES* res;
		res = mysql_store_result(conn);
		MYSQL_ROW row = mysql_fetch_row(res);

		if (row == NULL) {
			cout << "Last Name: ";
			cin >> lastName;
			cout << "First Name: ";
			cin >> firstName;
			cout << "Email: ";
			cin >> email;
			cout << "Extension: ";
			cin >> extension;
			cout << "Job Title: ";
			cin >> jobTitle;
			cout << "City: ";
			cin >> city;

			string query2 = "INSERT INTO employees VALUES (" + eID + ", '" + firstName + "', '" + lastName + "', '" + extension + "', '" + email + "', 1, 1002, '" + jobTitle + "');";
			const char* q2 = query2.c_str();
			int exequery2 = mysql_query(conn, q2);
			if (!exequery2) {
				cout << "success!" << endl;
			}
		}
		else {
			cout << "An employee with the same employee number exists." << endl;
		}







		/*
		string query = "select * from employees join offices using(officeCode);";
		const char* q = query.c_str();
		int exequery = mysql_query(conn, q);
		int totalEmp=0;
		if (!exequery) {
			MYSQL_RES* res;
			res = mysql_store_result(conn);
			MYSQL_ROW row;
			while (row = mysql_fetch_row(res)) {

				employeeNumber = atoi(row[1]);
				strcpy(lastName, row[2]);
				strcpy(firstName, row[3]);
				strcpy(email, row[5]);
				strcpy(phone, row[9]);
				strcpy(extension, row[4]);
				strcpy(jobTitle, row[7]);
				strcpy(city, row[8]);
				char repoID[6];


				//get the 'report to' name
				if (row[6] == NULL) {
					strcpy(reportTo, "She is the president!");
				}
				else {

					strcpy(repoID, row[6]);
					string query2 = "select * from employees where employeeNumber=";
					query2 = query2 + repoID + ';';
					const char* q2 = query2.c_str();
					int exequery = mysql_query(conn, q2);
					MYSQL_RES* repoRes;
					repoRes = mysql_store_result(conn);
					MYSQL_ROW row2 = mysql_fetch_row(repoRes);
					strcpy(reportTo, row2[1]);
				}

				cout << "employeeNumber: " << employeeNumber << endl;
				cout << "lastName: " << lastName << endl;
				cout << "firstName: " << firstName << endl;
				cout << "email: " << email << endl;
				cout << "phone: " << phone << endl;
				cout << "extension: " << extension << endl;
				cout << "reportsTo: " << reportTo << endl;
				cout << "jobTitle: " << jobTitle << endl;
				cout << "city: " << city << endl;
				cout << "---------------------------------------------" << endl;
				totalEmp++;
			}
			cout << "Total Employees: " << totalEmp << endl;

		}

		string query = "select * from employees join offices using(officeCode) where employeeNumber=";
		cout << "Please input employee ID(4 digits): ";
		int a;
		cin >> a;
		stringstream str;
		str << a;
		string num = str.str();
		query = query +num+';';
			const char* q = query.c_str();
			int exequery = mysql_query(conn, q);
			if (!exequery) {

				MYSQL_RES* res;
				res = mysql_store_result(conn);
				MYSQL_ROW row = mysql_fetch_row(res);

					if (row==NULL) {
						cout << "fail id" << endl;
					}
					else {
						employeeNumber = a;
						strcpy(lastName, row[2]);
						strcpy(firstName, row[3]);
						strcpy(email, row[5]);
						strcpy(phone, row[9]);
						strcpy(extension, row[4]);
						strcpy(jobTitle, row[7]);
						strcpy(city, row[8]);
						char repoID[6];


						//get the 'report to' name
						if (row[6] == NULL) {
							strcpy(reportTo, "Shi is the president!");
						}
						else {

							strcpy(repoID, row[6]);
							string query2 = "select * from employees where employeeNumber=";
							query2 = query2 + repoID + ';';
							const char* q2 = query2.c_str();
							int exequery = mysql_query(conn, q2);
							MYSQL_RES* repoRes;
							repoRes = mysql_store_result(conn);
							MYSQL_ROW row2 = mysql_fetch_row(repoRes);
							strcpy(reportTo, row2[1]);
						}
						}

						cout << "employeeNumber: " << employeeNumber << endl;
						cout << "lastName: " << lastName << endl;
						cout << "firstName: " << firstName << endl;
						cout << "email: " << email << endl;
						cout << "phone: " << phone << endl;
						cout << "extension: " << extension << endl;
						cout << "reportsTo: " << reportTo << endl;
						cout << "jobTitle: " << jobTitle << endl;
						cout << "city: " << city << endl;
						


	}
			
		

		mysql_close(conn);
	return 0;
}
*/

