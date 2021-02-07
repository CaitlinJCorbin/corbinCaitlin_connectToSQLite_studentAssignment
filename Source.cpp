//////////////////////////////////////////////
//	Caitlin J. Corbin						//
//	Last Updated - December 13, 2020		//
//	CSCI 210 M05 Programming Assignment 1	//
//	"Connect to a SQLite Database"			//
//////////////////////////////////////////////

#include <iostream>
#include "sqlite3.h"

// Used this as a reference : https://www.tutorialspoint.com/sqlite/sqlite_c_cpp.htm

static int callback(void* data, int argc, char** argv, char** azColName){
	int i;
	fprintf(stderr, "%s: ", (const char*)data);

	for (i = 0; i < argc; i++) {
		printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
	}

	printf("\n");
	return 0;
}

int main(int argc, char* argv[]) {
	sqlite3* db;
	char* zErrMsg = 0;
	int rc;
	const char* sql;
	const char* data = "Callback function called";

	rc = sqlite3_open("factdb.db", &db);

	if (rc) {
		fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
		return (0);
	}
	else {
		fprintf(stderr, "Opened database successfully\n");
	}

	sql = "SELECT * FROM BOOK";

	rc = sqlite3_exec(db, sql, callback, (void*)data, &zErrMsg);

	if (rc != SQLITE_OK) {
		fprintf(stderr, "SQL error: %s\n", zErrMsg);
		sqlite3_free(zErrMsg);
	}
	else {
		fprintf(stdout, "Operation done successfully\n");
	}

	sqlite3_close(db);
	return 0;
};