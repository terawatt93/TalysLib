#pragma once
#include "libxlsxwriter/include/xlsxwriter.h"
#include <sstream>
#include <iostream>
#include <TObject.h>

class TXlsxwriter:public TObject
{
	public:
	TXlsxwriter():TObject() {gSystem->Load((string(getenv("TALYSLIBDIR"))+"/libxlsxwriter/lib/libxlsxwriter.so").c_str()) ;}
	bool Opened=false;
	lxw_workbook  *workbook;
	vector<lxw_worksheet*> worksheets;
	vector<lxw_format*> formats;
	lxw_format* CurrentFormat=0;
	vector<string> FormatNames;
	lxw_worksheet* CurrentWorksheet;
	unsigned int CurrentWorksheetNumber;
	vector<string> worksheetNames;
	string Filename;
	vector<int> CeilX,CeilY,XBorder;
	void AddFormat(string FormatName, string Format, string IsNum="");
	void SetInitCeil(uint32_t x,uint32_t y);
	void SelectFormat(string FormatName="");
	void Open(string _Filename);
	void GoToWorksheet(string Name);
	void SetXBorder(int x);
	void Close();
	void WriteCeil(uint32_t x,uint32_t y,double value);
	void WriteCeil(uint32_t x,uint32_t y,int value);
	void WriteCeil(uint32_t x,uint32_t y,long unsigned int value);
	void WriteCeil(uint32_t x,uint32_t y,string value);
	~TXlsxwriter();
	void WriteTString(TString ts);
	ClassDef(TXlsxwriter, 1);
};

TXlsxwriter &operator << (TXlsxwriter &tx, double value);
TXlsxwriter &operator << (TXlsxwriter &tx, float value);
TXlsxwriter &operator << (TXlsxwriter &tx, int value);
TXlsxwriter &operator << (TXlsxwriter &tx, unsigned int value);
TXlsxwriter &operator << (TXlsxwriter &tx, char value);
TXlsxwriter &operator << (TXlsxwriter &tx, string value);
