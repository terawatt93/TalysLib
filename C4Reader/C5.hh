#pragma once
#include <sstream>
#include <iostream>
#include <fstream>
#include <TObject.h>
#include <TRandom.h>
#include <TH1F.h>
#include <TH2F.h>
#include <TF1.h>
#include <TFile.h>
#include <TGraph.h>
#include <TGraph2D.h>
#include <TMultiGraph.h>
#include <TCanvas.h>
#include <TLegend.h>
#include <TObject.h>
#include <TPaveText.h>
#include <TLatex.h>
#include <TGraphErrors.h>
#include <thread>  
#include <TVectorD.h> 
#include <TSystem.h>   
#include <map>  
#include <TROOT.h>  
#include <TVirtualFitter.h>
#include <sqlite3.h>
#include "../TXlsxwriter.hh"
#include <nlohmann/json.hpp>
#include <set>

using nlohmann::json;
using namespace std;

class C5Row;
class SubentData;
class EntryData;
class EnergyDistribution;
class AngularDistribution;

class C5Row: public TObject // класс хранящий информацию о строке x4pro_c5dat
{
	public:
	vector<double> Row; // вектор хранит значение полей 
	json cdat;
	SubentData* fSubent; // указатель на сабент которому принадлежит строка
	ClassDef(C5Row,1);
};

class SubentData: public TObject // класс хранящий информацию о Subent EXFOR
{
	public:
	string SubentID, Quant; // строка номер сабента, тип измеренной велечины
	vector<string> SF; // вектор который хранит SF1-8
	vector<string> col_names;
	int zTarg, aTarg, zProd, aProd; 
	vector<C5Row*> DataTable; // таблица из строк с5_dat
	multimap<double, C5Row*> GroupByData(int col_num);
	set<double> Keys;
	//void GetC5EnergyDistribution(multimap<double, C5Row*> table, double key);
	EntryData* fEntry; // указатель на ентри которому принадлежит сабент
	ClassDef(SubentData,1);
};

class EntryData: public TObject // класс хранящий информацию о Entry EXFOR
{
	public:
	string EntryID, FirstAuthor, Year, Title, DOI, Reference, Detector; // номер ентри, первый автор, год публикации, название, DOI, реф пока не знаю в каком виде добавить, детекторы
	vector<string> Authors; // полный список авторов
	vector<SubentData*> fSubentVec; // указатель на сабенты которые принадлежат данному ентри
	void GetAuthors(json &authors); // json в string
	void GetTitle(json &title); // json в string
	void GetDetector(json &detectors); // json в string
	ClassDef(EntryData,1);
};

class EnergyDistribution: public TGraphErrors
{
	public:
	EntryData* fEntry;
};

class AngularDistribution: public TGraphErrors
{
	public:
	EntryData* fEntry;
};

class C5Manager: public TObject
{
	public:
	
	string db_name = "/home/diamonddog/Programs/TalysLib/x4sqlite1.db";
	sqlite3 *db = 0;
	int connection = 0;
	string TargetNucl;
	
	list<C5Row> Rows;
	list<SubentData> Subents;
	list<EntryData> Entries;
		
	list<EnergyDistribution> ED_vec;
	list<AngularDistribution> AD_vec;
	
	void ExtractData(string SubentID, string Quant, vector<string> SF, int zTarg, int aTarg, int zProd, int aProd);
	void SearchSubent(string Target);
	
	void GetC5EnergyDistribution(multimap<double, C5Row*> table, double key);
	void GetC5AngularDistribution(multimap<double, C5Row*> table, double key);

	ClassDef(C5Manager,1);

};
