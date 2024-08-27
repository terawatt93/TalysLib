#include <stdio.h>
#include <stdlib.h>
#include <sqlite3.h> 
#include <TObject.h>
#include <vector>
#include <utility>
//int sqlite3_column_type( sqlite3_stmt* stmt, int cidx ); - возвращает тип колонки, 1 - SQLITE_INTEGER, 2-SQLITE_FLOAT, 3-SQLITE_TEXT, 4-SQLITE_BLOB, 5-SQLITE_NULL

class SQLiteRW;

class SQLRow:public TObject
{
	public:
	SQLiteRW *fBase=0;
	vector<pair<int,double> > Content_d;//хранятся результаты запроса, тут - float
	vector<pair<int,int> > Content_i;
	vector<pair<int,string> > Content_s;
	vector<pair<int,char> > Content_n;//тут хранится null
	vector<string> Headers;
	string Types;
	string AsString();
	string AsSQLString();
	string AsUpdateString();
	string GetValue(string Key);
	int current_index_in=0;
	int TotalContent=0;
	int current_index_out=0;
	double GetD(int index);
	int GetI(int index);
	string GetS(int index);
	void FromSQL(sqlite3_stmt* stmt);
	ClassDef(SQLRow,1);
};

SQLRow &operator << (SQLRow &tx, double value);
SQLRow &operator << (SQLRow &tx, int value);
SQLRow &operator << (SQLRow &tx, string value);

SQLRow &operator >> (SQLRow &tx, double &value);
SQLRow &operator >> (SQLRow &tx, int &value);
SQLRow &operator >> (SQLRow &tx, string &value);

class SQLiteRW:public TObject
{
	public:
	sqlite3 *db=0;//указатель на БД
	int rc;
	string CurrentTable;
	vector<string> TabHeaders;
	void Open(string Filename);
	void Close();
	int SelectTable(string TabName);
	void CreateTable(string Headers);
	vector<SQLRow> ToInsert;
	vector<SQLRow> Select(string Condition);
	void Insert();
	void Update(string Condition);
	bool getline(SQLRow &line);
	void SetNullHandlingType(string Option="Empty str");//установить тип обработки NULL: "Empty str"-пустая строка (по-умолчанию), "NaNI" - NAN (целое), "NaNF" - NAN (дробное), "0I" - ноль (целый), "0F" - 0 (дробное) 
	int NullHandlingType=0;
	ClassDef(SQLiteRW,1);
};

SQLiteRW &operator << (SQLiteRW &tx, double value);
SQLiteRW &operator << (SQLiteRW &tx, int value);
SQLiteRW &operator << (SQLiteRW &tx, string value);
