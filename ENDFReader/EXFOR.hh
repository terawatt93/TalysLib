#pragma once
#include <TH1F.h>
#include <TGraph.h>
#include <TF1.h>
#include <TFile.h>
#include <TObject.h>
#include <string>
#include <list>
#include <TClass.h> 
#include <TSystem.h>   
#include <TROOT.h>
class EXFORTable;
class EXFORManager:public TObject
{
	public:
	string PathToDatabase;
	EXFORManager() : TObject() {	}
	vector<EXFORTable> GetEXFORAngularDistributions(string Projectile, int Z, int A,string OutgoingParticle,int LevelNum);
	vector<EXFORTable> GetEXFORCrossSections(string Projectile, int Z, int A,string OutgoingParticle,int LevelNum);
	ClassDef(EXFORManager, 1);
};

class EXFORTable:public TObject//базовый класс для чтения файлов exfortables (https://www-nds.iaea.org/talys/tutorials/exfortables.pdf)
{
	public:
	int Z=0, A=0,MF=0, MT=0,Year=0;
	std::string Reaction, Author, Projectile, Quantity,X4ID;
	double ProjectileEnergy=0, ExcitationEnergy=0, ExcitationEnergy_EXFOR=0, Emin=0, Emax=0;
	vector<vector<double> > Table;//структура аналогична ENDFBasicTable
	string HeadX,HeadY;
	bool Read(string filename);
	TGraphErrors Graph;
	TGraphErrors* GetTGraph();
	int GetCodeID();
	vector<double> GetX();
	vector<double> GetY();
	vector<double> GetXErr();
	vector<double> GetYErr();
};
