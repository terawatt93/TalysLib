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

using namespace std;

class C4String:public TObject
{
	public:
	int Prj, Targ, M, MF, MT, Sub;
	double Energy, dEnergy, Data, dData, Cos_LO, dCos_LO, ELV_HL, dELV_HL;
	string I78, PXC, Reference;
	void GetFromString(string str);
	double *GetField(string colname);
	ClassDef(C4String,1);
};

class C4DataSet:public TObject
{
	public:
	string DataSet, Reaction;
	int Date=0, MF=0, MT=0, Proj=0, Targ=0, ZTarg=0, ATarg=0;
	vector<C4String> Table;
	void Read(ifstream &ifs, string _DataSet="");
	int GetZTarg();
	int GetATarg();
	vector<double> GetVectorOfValues(string colname,string RefColName="",double RefValue=0,double Difference=0);//возвращает вектор значений, соответствующих значениям в колонке RefColName, отличающимся от RefValue не более, чем на Difference
	vector<double> GetVectorOfPossibleValues(string colname);//возвращает вектор значений, которые принимает соответствующая колонка
	ClassDef(C4DataSet,1);
};


class C4Entry:public TObject
{
	public:
	C4DataSet DataSet;//не было обнаружено множественных Dataset в entry
	string Entry, Author1, RefCode, Reference, Title, DOI;
	vector<string> Authors;
	int Year;
	void Read(ifstream &ifs);
	const char *GetName()  const;
	ClassDef(C4Entry,1);
};
class C4AngularDistribution:public TGraphErrors
{
	public:
	C4Entry *fEntry;//!
	double ProjectileEnergy,LevelEnergy;
	//TGraphErrors Graph;
	void CopyData();
	string DataSet, Reaction, ID;//ID-соответствует номеру записи в DataSet
	int Date=0, MF=0, MT=0, Proj=0, Targ=0, ZTarg=0, ATarg=0;
	string Entry, Author1, RefCode, Reference, Title, DOI;
	vector<string> Authors;
	//void Draw(string Option="");
	int Year;
	ClassDef(C4AngularDistribution,1);
};
class C4EnergyDistribution:public TGraphErrors
{
	public:
	C4Entry *fEntry;//!
	double LevelEnergy;
	//TGraphErrors Graph;
	void CopyData();
	string DataSet, Reaction, ID;
	int Date=0, MF=0, MT=0, Proj=0, Targ=0, ZTarg=0, ATarg=0;
	string Entry, Author1, RefCode, Reference, Title, DOI;
	vector<string> Authors;
	//void Draw(string Option="");
	int Year;
	ClassDef(C4EnergyDistribution,1);
};
vector<C4AngularDistribution> ExtractAngularDistributions(C4Entry *Entry);
vector<C4EnergyDistribution> ExtractEnergyDistributions(C4Entry *Entry);

class C4Container:public TObject//хранит c4 в упорядоченном виде: по MF
{
	public:
	vector<int> MF_values;
	vector<vector<C4Entry> > Data;
	void AddData(C4Entry *Entry);
	vector<C4Entry> *GetData(int MF);
	vector<C4AngularDistribution> GetAngularDistributions();
	vector<C4EnergyDistribution>  GetEnergyDistributions();
	void GenerateBaseSummaryAndSaveToXLSX(string Filename,string Template="MF MT PrjE LevE Author Year Reference");
	void GenerateBaseSummaryAndSaveToXLSX(TXlsxwriter &xl,string Template="MF MT PrjE LevE Author Year Reference");
	ClassDef(C4Container,2);
};//

C4Container RequestC4DataSubentVector(sqlite3 *db, TFile *BaseROOT,string reaction,string projectile,int Z, int A,string Option="");//запрашивает все данные C4, определяя MT из reaction и все возможные MF. Если reaction=="", запрашивается упругое рассеяние
