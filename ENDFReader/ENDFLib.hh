#include <TH1F.h>
#include <TGraph.h>
#include <TGraph2D.h>
#include <TF1.h>
#include <TFile.h>
#include <TCanvas.h>
#include <TLegend.h>
#include <TObject.h>
#include <thread>  
#include <zip.h>
#include <string>
#include <list>
#include <TClass.h> 
#include <TSystem.h>   
#include <map>  
#include <TROOT.h>
#include <TMath.h>

#pragma once

using namespace std;

class ENDFFile;
class ENDFTable;
class MTEntry
{
	public:
	MTEntry() {  }
	MTEntry(string inp);
	int MT=0;
	string Reaction;
	string EntryDescription;
	void GetFromString(string inp);
};

class ENDFDictonary
{
	public:
	bool WasRead=false;
	map<int,MTEntry> MTDictonary;
	map<int,string> MFDictonary;
	void ReadMTDictonary();
	MTEntry *GetEntryByMT(int MT);
	string GetMFDescription(int MF);
	string GetMTDescription(int MT);
	static ENDFDictonary* Instance() 
	{
		static ENDFDictonary inst;
		return &inst;
	}
	private:
	ENDFDictonary() { if(!WasRead){ReadMTDictonary(); WasRead=true;} }
	public:
};


class ENDFDescription
{
	public:
	string Content;
	void AddFromString(string inp);
	ENDFFile *fFile;//!
};

class ENDFContentEntry
{
	public:
	MTEntry Entry_MT;
	int NRows,FileNumber;
	bool GetFromString(string inp);
};

class ENDFContent
{
	public:
	vector<ENDFContentEntry> Entries;
	TString GetEntriesInTLatexFormat();
	void GetFromString(string inp);
};

class ENDFBasicTable:public TObject
{
	public:
	vector<vector<double> > Table;
	int GetNRows();
	double& at(unsigned int Column, unsigned int Row);//метод, изменяющий размерность таблицы и возвращающий ссылку на ячейку
	double* Get(unsigned int Column, unsigned int Row);//метод, не меняющий размера таблицы и возвращающий указатель на нее
	void GetFromStringBase(string inp);
	vector<double> GetColumn(unsigned int Column);
	vector<double> GetRow(unsigned int Row);
	void GetSizes(unsigned int &NColumns,unsigned int &NRows);
	vector<double> GetSequence(unsigned int Column,unsigned int Row,unsigned int Length,unsigned int *NextColumn=0,unsigned int *NextRow=0);//функция нужна для считывания ряда коэффициентов Лежандра
	void GetSequence2(vector<double> &x,vector<double> &y,unsigned int Column,unsigned int Row,unsigned int Length,unsigned int *NextColumn=0,unsigned int *NextRow=0);//функция нужна для считывания таблично заданных угловых распределений
	ClassDef(ENDFBasicTable, 1);
};

class ENDFAngularDistribution:public TObject//класс, извлекающий из ENSDFTable информацию об угловом распределении
{
	public:
	int Type=0;//показывает тип параметризации распределения, 1-многочлены Лежандра, 2-таблица
	double Energy=0;//энергия налетающей частицы
	double SecondaryEnergy=0;//энергия вылетающей частицы (по состоянию на 25.01.22 актуально для гамма-квантов)
	vector<double> LegendreCoefficients;//здесь хранятся коэффициенты Лежандров при данной энергии;
	//TF1 AdistFunction;//из-за "очень удобной" организации работы с gsl приходится жертвовать производительностью 
	vector<double> XValues;
	vector<double> YValues;
	TGraph ADistGraph;
	TGraph* GetAngularDistribution(string _Type="Deg",int NPoints=180);//типы угловых распределений: Deg-в градусах, Cos-в косинусах
	//void GetSizes(unsigned int &NColumns,unsigned int &NRows);
	ENDFTable *fTable=0;//!
	ClassDef(ENDFAngularDistribution, 1);
};

class ENDFTable:public ENDFBasicTable
{
	public:
	int ID;//определяет ИД таблицы, т.е. MF*1000+MT
	ENDFBasicTable Header;
	bool IsHeaderFinished=false;
	int MF=0;//соответствует типу файла и определяет методику считывания и обработки (см. табл. Table 4 на стр. 12 в https://www.oecd-nea.org/dbdata/data/manual-endf/endf102.pdf)
	int MT=0;
	int Type=1;//Type 1 соответствует TAB1 (файлы типа #\sigma(E)), Type 2 соответствует TAB2 
	void GetFromString(string inp,int *_MF=0,int *_MT=0);
	vector<double> GetX();
	vector<double> GetY();
	vector<double> GetZ();
	TGraph TableGraph;
	TGraph* GetTGraph();
	void GenerateAngularDistributions4();//генерировать угловые распределения в соотв. с файлом 4
	void GenerateAngularDistributions14();//генерировать угловые распределения в соотв. с файлом 14
	vector<ENDFAngularDistribution> ADist4;//угловое распределение, соответствующее MF=4(для нейтронов)
	vector<ENDFAngularDistribution> ADist14;//угловое распределение, соответствующее MF=14(для гамма)
	string GetRawTable();
	ENDFFile *fFile=0;//!
	ClassDef(ENDFTable, 1);
	//ENDFAngularDistribution *GetAngularDistribution(double Energy);
};

class ENDFFile:public TObject
{
	public:
	string Filename;
	string Projectile;
	bool IsLoaded=false;
	ENDFDescription Description;
	ENDFContent Content;
	ENDFTable* GetENDFTable(int MF,int MT);//получить указатель на таблицу или создать новую
	ENDFTable* FindENDFTable(int MF,int MT);//получить указатель на таблицу
	map<int,ENDFTable> ENDFTables;
	void Read(string filename);
	void Read(string _Projectile,string Nuclide);
	vector<ENDFAngularDistribution*> GetGammaAngularDistributions(double GammaEnergy,double Thr=1);//найти угловые распределения для гамма
	vector<ENDFAngularDistribution*> GetNeutronAngularDistributions(int LevelNum);
	vector<ENDFAngularDistribution*> GetAngularDistributions(string OutgoingParticle,int LevelNum);
	TGraph2D GetTGraph2DGammaAngularDistributions(double GammaEnergy,double Thr=1,string _Type="Deg",int NPoints=180);
	TGraph2D GetTGraph2DNeutronAngularDistributions(int LevelNum,string _Type="Deg",int NPoints=180);
	TGraph GetGammaAngularDistribution(double GammaEnergy,double NeutronEnergy,double Thr=1,string _Type="Deg",int NPoints=180);
	TGraph GetNeutronAngularDistribution(int LevelNum,double NeutronEnergy,string _Type="Deg",int NPoints=180);
	TGraph GetNeutronCrossSections(int LevelNum);
	
	TGraph2D GetTGraph2DAngularDistributions(string OutgoingParticle,int LevelNum,string _Type="Deg",int NPoints=180);
	TGraph GetAngularDistribution(string OutgoingParticle,int LevelNum,double NeutronEnergy,string _Type="Deg",int NPoints=180);
	TGraph GetCrossSections(string OutgoingParticle,int LevelNum);
	
	bool WasRead=false;
	private:
	ENDFTable* LastENDFTable=0;
	public:
	~ENDFFile();
	ClassDef(ENDFFile, 1);
};
int GetAdditionIndex(string Projectile,string OutgoingParticle,int LevelNum);
