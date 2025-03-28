#include <unordered_map>
#include <map>
#include <string>
#include <memory>
#include <any>
#include <stdexcept>
#include <iostream>
#include "../Parser.cpp"

class YANDFMapObject
{
	public:
	map<string,YANDFMapObject> Content;
	int C_I=0;
	double C_F=0;
	string C_S;
	bool ClassVariables=false;
	string BackKey="";
	string Dimension="";
	vector<vector<double> > DataContent;
	vector<string> DataDimensions;
	vector<string> DataHeaders;
	int NColumns=0, NRows=0,NRowsRead=0;
	YANDFMapObject& operator=(const int I);
	YANDFMapObject& operator=(const double I);
	YANDFMapObject& operator=(const string I);
	YANDFMapObject& operator[](string key);
	YANDFMapObject& operator[](int key);
	YANDFMapObject* at(string key);
	YANDFMapObject* at(int key);
	vector<double> GetColumn(string key);
	double GetCell(string key,int Index);
	void get(int &I);
	void get(double &I);
	void get(string &I);
	void set(int I);
	void set(double I);
	void set(string I);
	void get(string k,int &I);
	void get(string k,double &I);
	void get(string k,string &I);
	void get(string k,YANDFMapObject &I);
	void ParseYANDF(string inp);
	void ReadYANDF(string fname);
};
