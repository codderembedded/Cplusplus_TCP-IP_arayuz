#include <iostream>
#include <stdio.h>
#include "SQLDatabase.h"
#include <string>

using namespace std;

namespace SQLDatabase
{
	int SQLDatabase::createDB(const char* s)
	{
		sqlite3* DB;
		int exit = 0;
		exit = sqlite3_open(s, &DB);
		sqlite3_close(DB);
		return 0;
	}

	int SQLDatabase::createTable(const char* s)
	{
		sqlite3* DB;
		
		string sql = "CREATE TABLE IF NOT EXISTS CLIENTS("
			"ID INTEGER PRIMARY KEY AUTOINCREMENT, "
			"Number					TEXT NOT NULL, "
			"HostName				TEXT NOT NULL, "
			"Service				TEXT NOT NULL, "
			"IpAddress				TEXT NOT NULL, "
			"OSName					TEXT NOT NULL, "
			"SystemManufacturer		TEXT NOT NULL, "
			"TotalPysicalMemory		TEXT NOT NULL, "
			"BiosVersion			TEXT NOT NULL, "
			"Ethernet				TEXT NOT NULL, "			
			"Wifi					TEXT NOT NULL );";

		try
		{
			int exit = 0;
			exit = sqlite3_open(s, &DB);

			char* messageError;
			exit = sqlite3_exec(DB, sql.c_str(), NULL, 0, &messageError);

			if (exit != SQLITE_OK) {
				cerr << "Error Create Table" << endl;
				sqlite3_free(messageError);
			}
			else
				cout << "Table created successfully" << endl;
			sqlite3_close(DB);
		}
		catch (const exception & e)
		{
			cerr << e.what();
		}

		return 0;
	}

	int SQLDatabase::insertData(const char* s,int index, string host, string service, string IpAddress, string OsName,
		string SystemMnaufacturer, string TotalPysicalMemory, string BiosVersion, string Ethernet, string Wifi)
	{
		sqlite3* DB;
		char* messaggeError;
		
		int exit = sqlite3_open(s, &DB);
		string Sindex = to_string(index);
		string sql("INSERT INTO CLIENTS (Number, HostName, Service, IpAddress, OSName, SystemManufacturer, TotalPysicalMemory, BiosVersion, Ethernet, Wifi) VALUES( '" + Sindex + "', '" + host + "', '" + service + "', '" + IpAddress + "', '" + OsName + "','" + SystemMnaufacturer + "','" + TotalPysicalMemory + "','" + BiosVersion + "','" + Ethernet + "','" + Wifi + "' );");

		exit = sqlite3_exec(DB, sql.c_str(), NULL, 0, &messaggeError);
		if (exit != SQLITE_OK) {
			cerr << "Error Insert" << endl;
			sqlite3_free(messaggeError);
		}
		else
			cout << "Records created Successfully!" << endl;

		return 0;
	}

	int SQLDatabase::updateData(const char* s, int SetNumber, int WhereNumber)
	{
		sqlite3* DB;
		char* messaggeError;

		int exit = sqlite3_open(s, &DB);
		string sql1 = "UPDATE CLIENTS SET Number = ";
		string Ssetnumber = to_string(SetNumber);
		string sql2 = " WHERE Number = ";
		string Swherenumber = to_string(WhereNumber);
		string sql = sql1 + Ssetnumber + sql2 + Swherenumber;
		//string sql("UPDATE CLIENTS SET Number = 1 WHERE Number = 2");

		exit = sqlite3_exec(DB, sql.c_str(), NULL, 0, &messaggeError);
		if (exit != SQLITE_OK) {
			cerr << "Error Insert" << endl;
			sqlite3_free(messaggeError);
		}
		else
			cout << "Records created Successfully!" << endl;

		return 0;
	}

	// retrieve contents of database used by selectData()
	/* argc: holds the number of results, azColName: holds each column returned in array, argv: holds each value in array */
	int callback(void* NotUsed, int argc, char** argv, char** azColName)
	{
		for (int i = 0; i < argc; i++) {
			// column name and value
			cout << azColName[i] << ": " << argv[i] << endl;
		}

		cout << endl;
		return 0;
	}

	int SQLDatabase::deleteData(const char* s, int id)
	{
		sqlite3* DB;
	
		int exit = sqlite3_open(s, &DB);
		string sqlstring = "DELETE FROM CLIENTS WHERE Number = ";
		string idstring = to_string(id);
		string sql = sqlstring + idstring;
		sqlite3_exec(DB, sql.c_str(), callback, NULL, NULL);
		cout << sql << endl;
		cout << "Database is deleted" << endl;
		return 0;
	}

	int SQLDatabase::deleteAllData(const char* s)
	{
		sqlite3* DB;

		int exit = sqlite3_open(s, &DB);
		string sql = "DELETE FROM CLIENTS";
		sqlite3_exec(DB, sql.c_str(), callback, NULL, NULL);
		cout << "All database is deleted" << endl;
		return 0;
	}

	int SQLDatabase::selectData(const char* s)
	{
		sqlite3* DB;

		int exit = sqlite3_open(s, &DB);

		string sql = "SELECT * FROM CLIENTS;";

		/* An open database, SQL to be evaluated, Callback function, 1st argument to callback, Error msg written here*/
		sqlite3_exec(DB, sql.c_str(), callback, NULL, NULL);

		return 0;
	}

	

}