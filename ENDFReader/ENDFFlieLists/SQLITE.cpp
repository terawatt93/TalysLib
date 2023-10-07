#include <vector>
#include <string>
#include <iostream>
#include "sqlite3.h"
using namespace std;




using Record = std::vector<std::string>;
using Records = std::vector<Record>;

int select_callback(void *p_data, int num_fields, char **p_fields, char **p_col_names)
{
	Records* records = static_cast<Records*>(p_data);
	try 
	{
		records->emplace_back(p_fields, p_fields + num_fields);
	}
	catch (...) 
	{
		// abort select on failure, don't let exception propogate thru sqlite3 call-stack
		return 1;
	}
	return 0;
}

Records select_stmt(sqlite3* db,const char* stmt)
{
	Records records;  
	char *errmsg;
	int ret = sqlite3_exec(db, stmt, select_callback, &records, &errmsg);
	if (ret != SQLITE_OK) {
		std::cerr << "Error in select statement " << stmt << "[" << errmsg << "]\n";
	}
	else {
		std::cerr << records.size() << " records returned.\n";
	}

	return records;
}

void sql_stmt(sqlite3* db,const char* stmt)
{
	char *errmsg;
	int ret = sqlite3_exec(db, stmt, 0, 0, &errmsg);
	if (ret != SQLITE_OK) 
	{
		std::cerr << "Error in select statement " << stmt << "[" << errmsg << "]\n";
	}
}

void SQLITE()
{
	sqlite3* db;
	if (sqlite3_open("ENDFBASE.db", &db) != SQLITE_OK) 
	{
		std::cerr << "Could not open database.\n";
		return ;
	}

	Records records = select_stmt(db,"SELECT * from ENDF_B_VIII_0 WHERE Projectile == \"n\" AND Z==1");
	sqlite3_close(db);

	for(unsigned int i=0;i<records.size();i++)
	{
		for(unsigned int j=0;j<records[i].size();j++)
		{
			cout<<records[i][j]<<" ";
		}
		cout<<"\n";
	}
	for (auto& record : records) 
	{
		// do something with your records
	}

	return ;
}
