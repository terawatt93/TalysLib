#include <string>
#include <iostream>
#include <sstream>
#include <TString.h>
#include <vector>
#include "../libxlsxwriter/include/xlsxwriter.h"
#include "TSystem.h"
#pragma once

R__LOAD_LIBRARY(../libxlsxwriter/lib/libxlsxwriter.so)

using namespace std;

class TXlsxwriter;
TXlsxwriter &operator << (TXlsxwriter &tx, double value);
TXlsxwriter &operator << (TXlsxwriter &tx, float value);
TXlsxwriter &operator << (TXlsxwriter &tx, int value);
TXlsxwriter &operator << (TXlsxwriter &tx, unsigned int value);
TXlsxwriter &operator << (TXlsxwriter &tx, char value);
TXlsxwriter &operator << (TXlsxwriter &tx, string value);

void TXlsxwriter::AddFormat(string FormatName, string Format, string IsNum)
{
	FormatNames.push_back(FormatName);
	formats.push_back(workbook_add_format(workbook));
	if(IsNum.find("NUM")!=string::npos)
	{
		format_set_num_format(formats[formats.size()-1],Format.c_str());
	}
	if(IsNum.find("bold")!=string::npos)
	{
		format_set_bold(formats[formats.size()-1]);
	}
	if(IsNum.find("italic")!=string::npos)
	{
		format_set_italic(formats[formats.size()-1]);
	}
}
void TXlsxwriter::SetInitCeil(uint32_t x,uint32_t y)
{
	CeilX[CurrentWorksheetNumber]=x;
	CeilY[CurrentWorksheetNumber]=y;
	XBorder[CurrentWorksheetNumber]=x;
}
void TXlsxwriter::SelectFormat(string FormatName)
{
	if(FormatName.size()==0)
	{
		CurrentFormat=0;
		return;
	}
	else
	{
		for(unsigned int i=0;i<formats.size();i++)
		{
			if(FormatNames[i]==FormatName)
			{
				CurrentFormat=formats[i];
				return;
			}
		}
	}
	cout<<"Format with name "<<FormatName<<" not found!\n";
}
void TXlsxwriter::Open(string _Filename)
{
	Filename=_Filename;
	workbook  = workbook_new(Filename.c_str());
}
void TXlsxwriter::GoToWorksheet(string Name)
{
	for(unsigned int i=0;i<worksheetNames.size();i++)
	{
		if(Name==worksheetNames[i])
		{
			CurrentWorksheetNumber=i;
			CurrentWorksheet=worksheets[i];
			return;
		}
	}
	worksheetNames.push_back(Name);
	CurrentWorksheet=workbook_add_worksheet(workbook,Name.c_str());
	worksheets.push_back(CurrentWorksheet);
	CeilX.push_back(0); CeilY.push_back(0);XBorder.push_back(0);
	CurrentWorksheetNumber=worksheets.size()-1;
}
void TXlsxwriter::SetXBorder(int x)
{
	XBorder[CurrentWorksheetNumber]=x;
}
void TXlsxwriter::Close()
{
	workbook_close(workbook);
}
void TXlsxwriter::WriteCeil(uint32_t x,uint32_t y,double value)
{
	worksheet_write_number(CurrentWorksheet, y, x, value, CurrentFormat);
	CeilX[CurrentWorksheetNumber]=x+1;
	CeilY[CurrentWorksheetNumber]=y;
}
void TXlsxwriter::WriteCeil(uint32_t x,uint32_t y,int value)
{
	worksheet_write_number(CurrentWorksheet, y, x, value, CurrentFormat);
	CeilX[CurrentWorksheetNumber]=x+1;
	CeilY[CurrentWorksheetNumber]=y;
}
void TXlsxwriter::WriteCeil(uint32_t x,uint32_t y,long unsigned int value)
{
	worksheet_write_number(CurrentWorksheet, y, x, value, CurrentFormat);
	CeilX[CurrentWorksheetNumber]=x+1;
	CeilY[CurrentWorksheetNumber]=y;
}
void TXlsxwriter::WriteCeil(uint32_t x,uint32_t y,string value)
{
	worksheet_write_string(CurrentWorksheet, y, x, value.c_str(), CurrentFormat);
	CeilX[CurrentWorksheetNumber]=x+1;
	CeilY[CurrentWorksheetNumber]=y;
}
TXlsxwriter::~TXlsxwriter()
{
	Close();
}
void TXlsxwriter::WriteTString(TString ts)
{
	stringstream s(ts.Data());
	string line;
	while(getline(s,line))
	{
		stringstream ss(line);
		while(ss)
		{
			TString tmp;
			ss>>tmp;
			if(tmp.IsDec())
			{
				int value=tmp.Atoi();
				*this<<value;
			}
			else if(tmp.IsFloat())
			{
				double value=tmp.Atof();
				*this<<value;
			}
			else
			{
				string value(tmp.Data());
				*this<<value;
			}
		}
		*this<<"\n";
	}
}

TXlsxwriter &operator << (TXlsxwriter &tx, double value)
{
	tx.WriteCeil(tx.CeilX[tx.CurrentWorksheetNumber],tx.CeilY[tx.CurrentWorksheetNumber],value);
	return tx;
}
TXlsxwriter &operator << (TXlsxwriter &tx, float value)
{
	tx.WriteCeil(tx.CeilX[tx.CurrentWorksheetNumber],tx.CeilY[tx.CurrentWorksheetNumber],value);
	return tx;
}
TXlsxwriter &operator << (TXlsxwriter &tx, int value)
{
	tx.WriteCeil(tx.CeilX[tx.CurrentWorksheetNumber],tx.CeilY[tx.CurrentWorksheetNumber],value);
	return tx;
}
TXlsxwriter &operator << (TXlsxwriter &tx,long unsigned int value)
{
	tx.WriteCeil(tx.CeilX[tx.CurrentWorksheetNumber],tx.CeilY[tx.CurrentWorksheetNumber],value);
	return tx;
}
TXlsxwriter &operator << (TXlsxwriter &tx, char value)
{
	string s;
	s+=value;
	tx.WriteCeil(tx.CeilX[tx.CurrentWorksheetNumber],tx.CeilY[tx.CurrentWorksheetNumber],s);
	return tx;
}
TXlsxwriter &operator << (TXlsxwriter &tx, string value)
{
	if(value=="\n")
	{
		tx.CeilY[tx.CurrentWorksheetNumber]++;
		tx.CeilX[tx.CurrentWorksheetNumber]=tx.XBorder[tx.CurrentWorksheetNumber];
	}
	else
	{
		tx.WriteCeil(tx.CeilX[tx.CurrentWorksheetNumber],tx.CeilY[tx.CurrentWorksheetNumber],value);
	}

	return tx;
}
