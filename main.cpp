#include <sqlite3.h>
#include <iostream>
#include <string>
#include <sstream>

void createTable(sqlite3* db, const std::string& tableName);
void openDatabase(sqlite3*& db, const char* DBName);
void insertDataIntoTable(sqlite3* db, const std::string& tableName, std::string sqlQuery);
void selectAllDataFromTable(sqlite3*& db, std::string tableName);
void deleteDataFromTable(sqlite3*& db, std::string sqlQuery);

// Callback function to handle the data returned from the query
static int callback(void* NotUsed, int argc, char** argv, char** azColName) {
    for (int i = 0; i < argc; i++) {
        std::cout << azColName[i] << ": " << (argv[i] ? argv[i] : "NULL") << std::endl;
    }
    std::cout << std::endl;
    return 0;
}

int main(int argc, char const* argv[]) {

    std::cout << argc << std::endl;

    // Print each argument
    for (int i = 0; i < argc; ++i) {
        std::cout << "Argument " << i << ": " << argv[i] << std::endl;
    }

    sqlite3* db;
    const char* DBName = "products.db";

    std::string tableName = "PRODUCT";

    // openDatabase(db, DBName);
    openDatabase(db, argv[1]);

    // createTable(db, tableName);
    createTable(db, argv[2]);

    std::stringstream sqlStream;
    std::string sqlQuery;

    sqlStream << "INSERT INTO " << argv[2] << " (NAME, AGE, ADDRESS, SALARY) "
        << "VALUES ('Paul', 32, 'California', 20000.00 );";

    // sqlStream << "INSERT INTO " << tableName << " (NAME, AGE, ADDRESS, SALARY) "
    //     << "VALUES ('Paul', 32, 'California', 20000.00 );";

    sqlQuery = sqlStream.str();

    insertDataIntoTable(db, DBName, sqlQuery);

    // sqlStream << "DELETE FROM " << tableName << " WHERE ID = 24;";

    // sqlQuery = sqlStream.str();

    // deleteDataFromTable(db, sqlQuery);

    // sqlStream << "SELECT * FROM " << tableName << " ;";

    // sqlQuery = sqlStream.str();

    selectAllDataFromTable(db, argv[2]);

    sqlite3_close(db);
    return 0;
}

void deleteDataFromTable(sqlite3*& db, std::string sqlQuery) {
    std::cout << "deleting data from table..." << std::endl;

    char* errmsg = 0;
    int exit = sqlite3_exec(db, sqlQuery.c_str(), callback, 0, &errmsg);
    if (exit != SQLITE_OK) {
        std::cerr << "Error deleting data from table: " << sqlite3_errmsg(db) << std::endl;
    } else {
        std::cout << "Delted data from table successfully!" << std::endl;
    }
}

void selectAllDataFromTable(sqlite3*& db, std::string tableName) {
    std::cout << "selecting data from table..." << std::endl;

    char* errmsg = 0;

    std::stringstream sqlStream;
    std::string sqlQuery;

    sqlStream << "SELECT * FROM " << tableName << " ;";

    sqlQuery = sqlStream.str();

    int exit = sqlite3_exec(db, sqlQuery.c_str(), callback, 0, &errmsg);
    if (exit != SQLITE_OK) {
        std::cerr << "Error selecting data from table: " << sqlite3_errmsg(db) << std::endl;
    } else {
        std::cout << "Selected data from table successfully!" << std::endl;
    }
}

void insertDataIntoTable(sqlite3* db, const std::string& tableName, std::string sqlQuery) {
    std::cout << "Inserting data into table: " << tableName << " ..." << std::endl;

    char* errmsg = 0;
    int exit = sqlite3_exec(db, sqlQuery.c_str(), 0, 0, &errmsg);
    if (exit != SQLITE_OK) {
        std::cerr << "Error inserting data into table: " << errmsg << std::endl;
        sqlite3_free(errmsg);
    } else {
        std::cout << "Data inserted into table successfully!" << std::endl;
    }
}

void createTable(sqlite3* db, const std::string& tableName) {
    std::cout << "Creating table: " << tableName << " ..." << std::endl;
    std::stringstream sqlQuery;
    sqlQuery << "CREATE TABLE IF NOT EXISTS " << tableName << " ("
        << "ID INTEGER PRIMARY KEY AUTOINCREMENT, "
        << "NAME TEXT NOT NULL, "
        << "AGE INT NOT NULL, "
        << "ADDRESS CHAR(50), "
        << "SALARY REAL );";

    char* errmsg = 0;
    int exit = sqlite3_exec(db, sqlQuery.str().c_str(), 0, 0, &errmsg);
    if (exit != SQLITE_OK) {
        std::cerr << "Error creating table: " << errmsg << std::endl;
        sqlite3_free(errmsg);
    } else {
        std::cout << "Table created successfully!" << std::endl;
    }
}

void openDatabase(sqlite3*& db, const char* DBName) {
    std::cout << "Opening database..." << std::endl;
    int exit = sqlite3_open(DBName, &db);
    if (exit != SQLITE_OK) {
        std::cerr << "Error opening database: " << sqlite3_errmsg(db) << std::endl;
    } else {
        std::cout << "Opened database successfully!" << std::endl;
    }
}
