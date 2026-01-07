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
//#include "../TXlsxwriter.hh"
#include <nlohmann/json.hpp>
#include <set>

using nlohmann::json;
using namespace std;

class SubentData;
class EntryData;
class EnergyDistribution;
class AngularDistribution;


class SubentData: public TObject // класс хранящий информацию о Subent EXFOR
{
	public:
	string SubentID, Quant; // строка номер сабента, тип измеренной велечины
	int zTarg, aTarg, zProd, aProd;
	int MT, MF;
	string SF1, SF2, SF3, SF4, SF5, SF6, SF7, SF8, SF9;
	string x2_hdr;
	string Reacode;
	string Data_basic_units;
	unordered_map<string, string> c5_expansion;
	vector<string> col_keys;
	struct DataRow
	{
		unordered_map<string, double> Row;
		json cdat;
	};
	vector<DataRow> DataTable;
	EntryData* fEntry; // указатель на ентри которому принадлежит сабент
	ClassDef(SubentData,1);
};

class EntryData: public TObject // класс хранящий информацию о Entry EXFOR
{
	public:
	string EntryID; // номер ентри, первый автор, год публикации, название, DOI, реф пока не знаю в каком виде добавить, детекторы
	string Title;
	vector<string> Year;
	vector<string> DOI;
	vector<string> Reference;
	vector<pair<string, string>> Detector; // Информация о детекторах. Val1 -- код детектора. Val2 -- текст описание.
	vector<pair<string, string>> Method; // Информация об используемом методе. Val1 -- набор кодов. Val2 -- текст описание.
	vector<string> Authors; // полный список авторов
	vector<SubentData*> fSubentVec; // указатель на сабенты которые принадлежат данному ентри
	void GetAuthors(json &authors); // json в string
	void GetTitle(json &title); // json в string
	void GetDetector(json &detectors); // json в string
	void GetMethod(json &method);
	void GetReference(json &reference);
	ClassDef(EntryData,1);
};

class EnergyDistribution: public TObject
{
	public:
	vector<vector<double>> data_points; // [0]: ProjectileEnergy, [1]: Data, [2]: [0]Err, [3]: [1]Err
	TGraphErrors graph;
	SubentData* fSubent;
	GammaTransition* Transition;
	ClassDef(EnergyDistribution,1);
};

class AngularDistribution: public TObject
{
	public:
	vector<vector<double>> data_points; // [0]: ProjectileEnergy, [1]: Ang, [2]: Data, [3] AngErr, [4] DataErr
	TGraphErrors graph;
	SubentData* fSubent;
	GammaTransition* Transition;
	Level* fLevel;
	ClassDef(AngularDistribution,1);
};

class C5Manager: public TObject
{
	public:
	
	string db_name = "/home/diamonddog/Programs/x4sqlite1.db";
	sqlite3 *db = 0;
	int connection = 0;
	
	Nucleus* fMotherNucleus;
	
	list<SubentData> Subents;
	list<EntryData> Entries;
	
	void SearchSubents();
	void ExtractSubentData();
	
	void AssignC5ToLevel(double tolerancy_gamma);
	
	ClassDef(C5Manager,1);

};
