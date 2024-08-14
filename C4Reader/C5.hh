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
	multimap<double, C5Row*> GroupByOneColumn(int col_num);
	multimap< pair<double, double>, C5Row* > GroupByTwoColumns(int col_num1, int col_num2);
	multimap<double, C5Row*> GroupEnergyDistribution();
	multimap< pair<double, double>, C5Row* > GroupAngularDistribution();
	set<double> ED_keys;
	set<pair<double, double>> AD_keys;
	set<double> Keys1;
	set<pair<double, double>> Keys2;
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
	SubentData* fSubent;
	ClassDef(EnergyDistribution,1);
};

class AngularDistribution: public TGraphErrors
{
	public:
	EntryData* fEntry;
	SubentData* fSubent;
	double En;
	ClassDef(AngularDistribution,1);
};

class C5Manager: public TObject
{
	public:
	
	string db_name = "/home/diamonddog/Programs/x4sqlite1.db";
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
	template<typename MapType, typename KeyType>
	void GetC5AngularDistribution(MapType table, KeyType key, int col_num);

	ClassDef(C5Manager,1);

};

