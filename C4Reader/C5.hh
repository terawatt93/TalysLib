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
	unordered_map<string, double> Row; // вектор хранит значение полей 
	json cdat;
	SubentData* fSubent; // указатель на сабент которому принадлежит строка
	ClassDef(C5Row,1);
};

class SubentData: public TObject // класс хранящий информацию о Subent EXFOR
{
	public:
	string SubentID, Quant; // строка номер сабента, тип измеренной велечины
	int zTarg, aTarg, zProd, aProd;
	array<string, 9> SF; // вектор который хранит SF1-8
	vector<string> col_names_EXFOR; 
	vector<string> col_names_expansion;
	size_t it=0;
	vector<C5Row*> DataTable; // таблица из строк с5_dat
	EntryData* fEntry; // указатель на ентри которому принадлежит сабент
	ClassDef(SubentData,1);
};

class EntryData: public TObject // класс хранящий информацию о Entry EXFOR
{
	public:
	string EntryID, Year, Title, DOI, Reference; // номер ентри, первый автор, год публикации, название, DOI, реф пока не знаю в каком виде добавить, детекторы
	vector<pair<string, string>> Detector; // Информация о детекторах. Val1 -- код детектора. Val2 -- текст описание.
	vector<pair<string, string>> Method; // Информация об используемом методе. Val1 -- набор кодов. Val2 -- текст описание.
	vector<string> Authors; // полный список авторов
	vector<SubentData*> fSubentVec; // указатель на сабенты которые принадлежат данному ентри
	void GetAuthors(json &authors); // json в string
	void GetTitle(json &title); // json в string
	void GetDetector(json &detectors); // json в string
	void GetMethod(json &method);
	ClassDef(EntryData,1);
};

class EnergyDistribution: public TObject
{
	public:
	vector<double> Y,X,ErrorY,ErrorX;
	bool InRange(double emin, double emax);
	SubentData* fSubent;
	ClassDef(EnergyDistribution,1);
};

class AngularDistribution: public TObject
{
	public:
	vector<double> Y,X,ErrorY,ErrorX;
	double ProjectileEnergy;
	SubentData* fSubent;
	ClassDef(AngularDistribution,1);
};

class C5Manager: public TObject
{
	public:
	
	string db_name = "../../../../../ZFSRAID/EXFOR_library/x4sqlite1.db";
	sqlite3 *db = 0;
	int connection = 0;
	
	list<C5Row> Rows;
	list<SubentData> Subents;
	list<EntryData> Entries;
		
	//list<EnergyDistribution> ED_vec;
	//list<AngularDistribution> AD_vec;
	
	void SearchSubents(const string& Target);
	void ExtractSubentData(const string& SubentID, const string& Quant, const array<string,9>& SF, int zTarg, int aTarg, int zProd, int aProd);
	
	EnergyDistribution GetC5EnergyDistribution(SubentData& subent);
	AngularDistribution GetC5AngularDistribution(SubentData& subent);
	AngularDistribution GetC5ElasticAngularDistribution(SubentData& subent);
	
	ClassDef(C5Manager,1);

};
