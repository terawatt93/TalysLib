#include <sstream>
#include <iostream>
#include <TObject.h>
#include <TRandom.h>
#include <TH1F.h>
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
#include "libxlsxwriter/include/xlsxwriter.h"
/*#include <Minuit2/FunctionMinimum.h>
#include <Minuit2/MnMinimize.h>
#include <Minuit2/MnMigrad.h>
#include <Minuit2/MnUserParameterState.h>
#include <Minuit2/FCNGradientBase.h>*/


#pragma once
using namespace std;

#define OLD_VERSION 1

#define kAngularDistribution 1
#define kExcitationCS 2
#define kTotalInelasticCS 3

#define kVarEnergy 1
#define kVarDeformation 2
#define kVarOptVv 3 //Talts manual p. 44
#define kVarOptWv 4
#define kVarOptRv 5
#define kVarOptAv 6
#define kVarOptWd 7
#define kVarOptRd 8
#define kVarOptAd 9
#define kVarOptVso 10
#define kVarOptWso 11
#define kVarOptRso 12
#define kVarOptAso 13
#define kVarOptRc 14

#define kVarOptv1 15
#define kVarOptv2 16
#define kVarOptv3 17
#define kVarOptv4 18
#define kVarOptw1 19
#define kVarOptw2 20
#define kVarOptd1 21
#define kVarOptd2 22
#define kVarOptd3 23
#define kVarOptvso1 24
#define kVarOptvso2 25
#define kVarOptwso1 26
#define kVarOptwso2 27
#define kUseDefaultOMP 4
#define kUseLevelJP -2
//Функции, объявленные после класса, описываются в одном файле с этим классом!
class Level;
class Nucleus;
class Deformation;
class TalysCalculation;
class OpticalModelParameters;
class Radionuclide;

class TalysLibManager//потом перенсти в отдельный файл!
{
	public:
	static TalysLibManager& Instance();
	bool EnableWarning=true;
	void SetEnableWarning(bool flag);
	bool IsEnableWarning();
	bool GenerateAllGraphs=true;
	int MaxNumberOfThreads=16;
	void Purge();
	private:
	TalysLibManager() { }  // конструктор недоступен
	~TalysLibManager() { } // и деструктор
	// необходимо также запретить копирование
	TalysLibManager(TalysLibManager const&); // реализация не нужна
	TalysLibManager& operator= (TalysLibManager const&);  // и тут
	ClassDef(TalysLibManager, 2);
};

class AdditionalInformationContainer
{
	public:
	map<string,double> AdditionalInformationMap;
	double& operator() (string Key);
	ClassDef(AdditionalInformationContainer, 1);
};

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



class OMPStorageData:public TObject
{
	public:
	OMPStorageData():TObject() {  }
	double Vv=0, Wv=0, Rv=0, Av=0;
	double Wd=0, Rd=0, Ad=0;
	double Vso=0, Wso=0, Rso=0, Aso=0;
	double Rc=0;
	double v1=0, v2=0, v3=0, v4=0; 
	double w1=0, w2=0; 
	double d1=0, d2=0, d3=0; 
	double vso1=0, vso2=0; 
	double wso1=0, wso2=0; 
	double A=0, N=0, Z=0, ProjectileEnergy=0, Ef=0, Vc=0;
	bool ReadFlag=false;
	bool Evaled=false;
	bool SaveEnergyDependence=false;
	int Type=1;
	string Projectile,HRPotentialType;
	ClassDef(OMPStorageData, 1);
};
class OMPStorage:public OMPStorageData
{
	public:
	OMPStorage() {  }; //конструктор по-умолчанию
	OMPStorage(OMPStorageData d);//конструктор из родительского класса OMPStorageData
	OMPStorageData ToOMPStorageData();//объект класса OMPStorageData, задаваемый конструктором по-умолчанию
	Nucleus *Nuclide;
	void EvalKoning();
	void EvalPotential();
	void Read(string &Buffer);
	virtual void Draw(string option="");
	void GenerateOMPGraph();
	TString GetTString();
	TString GetInHumanReadable();
	TGraph GrVv,GrWv,GrVso,GrWso;
	void SetNucleus(Nucleus *_Nuclide);
	void SetProjectile(string _Projectile);
	void SetProjectileEnergy(double Energy);
	void SetVv(double value);
	void SetWv(double value);
	void SetRv(double value);
	void SetAv(double value);
	void SetWd(double value);
	void SetRd(double value);
	void SetAd(double value);
	void SetVso(double value);
	void SetWso(double value);
	void SetRso(double value);
	void SetAso(double value);
	void SetRc(double value);
	void Setv1(double value);
	void Setv2(double value);
	void Setv3(double value);
	void Setv4(double value);
	void Setw1(double value);
	void Setw2(double value);
	void Setd1(double value);
	void Setd2(double value);
	void Setd3(double value);
	void Setvso1(double value);
	void Setvso2(double value);
	void Setwso1(double value);
	void Setwso2(double value);
	double GetVv();
	double GetWv();
	double GetWd();
	double GetVso();
	double GetWso();
	double GetRv();
	double GetAv();
	double GetRd();
	double GetAd();
	double GetRso();
	double GetAso();
	double GetRc();
	double Getv1();
	double Getv2();
	double Getv3();
	double Getv4();
	double Getw1();
	double Getw2();
	double Getd1();
	double Getd2();
	double Getd3();
	double Getvso1();
	double Getvso2();
	double Getwso1();
	double Getwso2();
	ClassDef(OMPStorage, 1);
	private:
	using TObject::Draw;
	using TObject::Read;
};

class OpticalModelParametersData:public TObject
{
	public:
	OpticalModelParametersData():TObject() {  }
	OMPStorageData PotentialData, PotentialDispData, PotentialKoningData;
	int nOMP;
	bool NormalisationMode=true;
	bool Read=false;
	bool JLM_flag=false;
	bool goriely=false;
	bool hilaire=false;
	bool Koning=false;
	bool Dispersive=false;
	string Projectile;
	vector<string> ContentOfFile;
	int A,Z,N;
	ClassDef(OpticalModelParametersData, 1);
};

class OpticalModelParameters:public OpticalModelParametersData//:public TObject
{
	private:
	
	public:
	OpticalModelParameters();//конструктор по-умолчанию
	OpticalModelParameters(OpticalModelParametersData d);//конструктор из родительского класса OpticalModelParametersData
	OpticalModelParametersData ToOpticalModelParametersData();//функция по переводу объекта класса OpticalModelParameters в OpticalModelParametersData
	OMPStorage *DefaultOMP=0;
	OMPStorage Potential, PotentialDisp, PotentialKoning;
	
	void ReadPotentials(string Line);
	void SaveEnergyDependence(bool State);
	unsigned int PointToPasteChangedOMP=0;
	Nucleus *Nuclide;
	
	void SetDefaultOMP(int option);
	void SetVv(double value);
	void SetWv(double value);
	void SetRv(double value);
	void SetAv(double value);
	void SetWd(double value);
	void SetRd(double value);
	void SetAd(double value);
	void SetVso(double value);
	void SetWso(double value);
	void SetRso(double value);
	void SetAso(double value);
	void SetRc(double value);
	void Setv1(double value);
	void Setv2(double value);
	void Setv3(double value);
	void Setv4(double value);
	void Setw1(double value);
	void Setw2(double value);
	void Setd1(double value);
	void Setd2(double value);
	void Setd3(double value);
	void Setvso1(double value);
	void Setvso2(double value);
	void Setwso1(double value);
	void Setwso2(double value);
	bool ReadOMP(string _Projectile="n");
	void SaveOMP(string filename,int UseKoning=0);//UseKoning=0-не использовать потенциал Кенинга; 1-использовать Кенинга, если нет локальной ОМ; 2-использовать только Кенинга
	//void RestoreOMP();
	double GetVv();
	double GetWv();
	double GetWd();
	double GetVso();
	double GetWso();
	double GetRv();
	double GetAv();
	double GetRd();
	double GetAd();
	double GetRso();
	double GetAso();
	double GetRc();	
	double Getv1();
	double Getv2();
	double Getv3();
	double Getv4();
	double Getw1();
	double Getw2();
	double Getd1();
	double Getd2();
	double Getd3();
	double Getvso1();
	double Getvso2();
	double Getwso1();
	double Getwso2();
	void AssignPointers(Nucleus *N=0);
	ClassDef(OpticalModelParameters, 1);
};

class SpinParity:public TObject
{
	public:
	float J;
	int Parity;
	SpinParity(float J_in, int Parity_in);
	//SpinParity();
	SpinParity(float J_in=0);
	SpinParity(string str);
	string GetLine();
	TString GetTLatex();
	string GetStringAsGammaMultipolarity();
	static vector<SpinParity> QSum(SpinParity &JP1,SpinParity &JP2);
	static vector<SpinParity> QSum(SpinParity &JPi,SpinParity &JPf,SpinParity &RadJP);
	ClassDef(SpinParity, 1);
};

std::istream& operator >> (std::istream &istr,SpinParity &JP);
std::ostream& operator << (std::ostream &ostr,SpinParity &JP);
bool operator == (const SpinParity &JP1, const SpinParity &JP2);
float abs(SpinParity JP);

class GammaTransitionData:public TObject
{
	public:
	GammaTransitionData():TObject(){ }
	//float Energy=0,EnergyErr=0,Intensity=0,CrossSection=0,E_in=0,Tolerancy=0,Rel_Cs=0,TalysCrossSection=0, TalysE_i=0,TalysE_f=0;
	//расширение для разных энергий
	float Energy=0,EnergyErr=0,Intensity=0,CrossSection=0,E_in=0,Tolerancy=0,Rel_Cs=0,TalysCrossSection=0, TalysE_i=0,TalysE_f=0;
	vector<float> TalysCrossSections;
	vector<float> X_Values;
	SpinParity TalysJP_i,TalysJP_f;
	vector<SpinParity> TalysMultipolarity;
	string Multipolarity,nuclide,reaction, Origin;
	AdditionalInformationContainer AI;
	double& AdditionalInformation(string Key); 
	ClassDef(GammaTransitionData, 2);
};

class GammaTransition:public GammaTransitionData
{
	public:
	//float Energy,EnergyErr,Intensity,CrossSection,E_in,Tolerancy,Rel_Cs,TalysCrossSection, TalysE_i,TalysE_f, TalysJP_i,TalysJP_f,TalysMultipolarity;
	TGraph CSGraph;
	bool IsCSGraphGenerated=false;
	int InitLevelNumber, FinalLevelNumber;
	Level* fLevel;
	Level* fFinalLevel;
	GammaTransition()
	{
		Energy=0; EnergyErr=0; Intensity=0; CrossSection=0; E_in=0; Tolerancy=0; Rel_Cs=0; TalysCrossSection=0;
		fLevel=0; fFinalLevel=0; InitLevelNumber=0; FinalLevelNumber=0;
	}
	GammaTransition(double Energy,string nuclide)
	{
		this->Energy=Energy;
		this->nuclide=nuclide;
	}
	void SetTGraphNameAndTitle(string ValName);
	void AddPoint(double x_value,double y_value);
	void AddPoint(double x_value,GammaTransition *g);
	void AddPoint(GammaTransition *g);
	GammaTransition(GammaTransitionData d);
	bool ReadTransition(string line,string ReadNuclName, float E_in);
	string GetLine(string option="");//possible option:brief
	bool CheckEnergy(float E,float Tolerancy,float intensity=0);
	const char *GetName()  const;
	void FindFinalLevel(double Tolerancy=2);
	void SetInformationExtractedFromTalys(float TalysE_f, float TalysE_i, SpinParity JP_f, SpinParity JP_i);
	void ErasePointers();
	void EvalMultipolarity();
	SpinParity GetMostProbableMultipolarity();
	string GetStringOfMostProbableMultipolarities();
	double GetEnergy();
	double GetIntensity();
	double GetRelativeIntensity();
	void GenerateGraphs();
	TGraph *GetCSGraph();
	ClassDef(GammaTransition, 1);
};

class LevelData:public TObject
{
	public:
	LevelData():TObject() { }
	string Nuclide, HalfLife,HalfLifeErr,JP,Origin;
	vector<SpinParity> JP_values;
	vector<GammaTransitionData> GammasData;
	int Mark;//величина, определяющая достоверность уровня: размер вектора с JP, если JP.size=0, то Mark=99,если есть неопределенность (скобки), то размер ветора*2
	float Energy, EnergyErr, TalysCS, TalysCSCompound, TalysCSDirect, OutgoingParticleEnergy; SpinParity TalysJP;
	vector<float> ADTot,ADDirect, ADCompound, Angle, AngleLab, Branching;
	vector<unsigned int> NumbersOfFinalLevels;
	vector<float> CSValues, CSCompoundValues, CSDirectValues;
	vector<float> X_Values;
	vector<vector<float > > ADTotValues,ADDirectValues, ADCompoundValues, AngleLabValues;
	AdditionalInformationContainer AI;
	double& AdditionalInformation(string Key); 
	ClassDef(LevelData, 2);
};

class LevelDeformationData:public TObject
{
	public:
	LevelDeformationData(): TObject() { }
	char TypeOfLevel,TypeOfDeformation;
	int NumberOfBand, NumberOfLevel, LOfBand=-1, NumberOfPhonons=-1, MagneticNumber=-1;
	vector<float> Beta;
	ClassDef(LevelDeformationData, 1);
};
class LevelDeformation:public LevelDeformationData
{
	public:
	LevelDeformation(char Type='B') {TypeOfDeformation='B';}
	void GetFromString(string input);
	void TurnToBeta(int A);
	TString GenerateStringForDefFile();
	Level* fLevel=0;
	Deformation *fDeformation=0;
	LevelDeformation(LevelDeformationData d);
	LevelDeformationData ToLevelDeformationData();
	ClassDef(LevelDeformation, 1);
};
class DeformationData:public TObject
{
	public:
	DeformationData(): TObject() { }
	int A,Z,NLevels;
	char TypeOfCollectivity='S',TypeOfDeformation='B';
	vector<LevelDeformationData> LevelDeformationsData;
	vector<string> ContentOfFile;
	ClassDef(DeformationData, 1);
};
class Deformation:public DeformationData
{
	public:
	Deformation() {  };
	vector<LevelDeformation> LevelDeformations;
	Deformation(DeformationData d);
	unsigned int PointToPastChangedDeformation=0;
	void SetZA(int _Z,int _A);
	void SetTypeOfCollectivity( char _Type='S');
	void ReadDeformation();
	void WriteDeformation(string filename);
	void SetDeformation(Level *l,char LevT, int BandN=-1, int BandL=-1, int MagN=-1,int NPhon=-1, vector<float> *Def=0);
	void SetDefaultDeformationType(char _Type='D');
	//void RestoreDeformation();
	void Sort();
	DeformationData ToDeformationData();
	void AssignPointers();
	ClassDef(Deformation, 1);
};

class Level:public LevelData
{
	public:
	vector<Level*> SimilarLevels;
	LevelDeformation *deformation=0;
	Level()
	{
		Mark=99;
		deformation=0;
	}
	Level(LevelData ld);
	bool IsGraphGenerated=false;
	bool PlottedADist=false;
	bool PlottedADist2D=false;
	TGraph AdistTotalTalys, AdistCompoundTalys, AdistDirectTalys;//угловые распределения
	TGraph2D AdistTotalTalys2D, AdistCompoundTalys2D, AdistDirectTalys2D;//угловые распределения
	TGraph CSGraph, CSCompoundGraph, CSDirectGraph;
	int Number;
	
	list<TGraph> GeneratedGraphsList;
	
	//float Energy, EnergyErr,TalysCS,TalysJP;
	vector<GammaTransition> Gammas;
	bool ReadLevel(string line,string ReadNuclName);
	void ReadTransition(string line);
	void AddLineFromTalys(double E, double CS);
	void AddLineFromTalys(double E, double CS, double E_i, double E_f, SpinParity JP_i, SpinParity JP_f, unsigned int InitLevelNumber, unsigned int FinalLevelNumber);
	void Reset();
	//void Print();
	const char *GetName()  const;
	bool CheckEnergy(float E,float Tolerancy,float intensity);
	vector<GammaTransition*> GetTransition(float E,float Tolerancy,float intensity);
	Nucleus* fNucleus;
	//методы для задания параметров уровня
	void SetEnergy(float Energy); void SetEnergyErr(float EnergyErr); void SetTalysCS(float TalysCS); void SetTalysSpinParity(SpinParity TalysJP);
	void SetOrigin(string Origin); void AddJPValue(SpinParity JPValue); void AddSimilarLevel(Level* SimilarLevel); 
	void SetDeformation(char LevT, int BandN=-1, int BandL=-1,  int MagN=-1, int NPhon=-1,vector<float> *Def=0);//генерирует объект deformation и добавляет его в ядерную деформацию.
	//порядок и назначение аргументов соответствуют .def файлу (ECIS_report.pdf, стр.3)
	//методы для получения параметров уровня
	float GetEnergy(); float GetEnergyErr(); float GetTalysCS(); SpinParity GetTalysSpinParity();
	string GetOrigin(); vector<SpinParity>& GetJPValues(); vector<Level*>& GetSimilarLevels();
	void AssignPointers();
	void ErasePointers();
	TGraph* GetAngularDistribution(string type="Total",string option="");//если график уже построен, выдается сохраненный, если нет, или option=="new", строится заново
	TGraph2D* GetAngularDistribution2D(string type="Total",string option="");
	TGraph* GetAngularDistributionAtEnergy(float Energy,string type="Total",string option="");
	TMultiGraph* GetTMultiGraphForAngularDistributions(string graphics="all");
	TGraph *GetCSGraph(string type="Total");
	LevelData ToLevelData();
	void SetTGraphNameAndTitle(string ValName);
	void AddPoint(double x_value,Level *level);
	void AddPoint(Level *level);
	void GenerateGraphs();
	ClassDef(Level, 2);
};

class NucleusData:public TObject
{
	public:
	NucleusData(): TObject() {  }
	string Name,Reaction,Projectile,addition;
	int A,Z;
	vector<LevelData> LevelsData;
	vector<NucleusData> ProductsData;
	bool TalysCalculated;
	vector<float> EnergyGrid;//сетка энергий, используемая для расчетов
	double Abundance,ProjectileEnergy=14.1,ProjectileEnergyCM,Mass,ProjectileMass,OutgoingParticleMass;
	//сечения и дифсечения
	vector<float> Angle, AngleLab, ElTot, ElCompound, ElDirect;//дифсечения
	vector<vector<float> > ElTotValues, ElCompoundValues, ElDirectValues, AngleLabValues;
	float TOTGamProd=0, TOTNProd=0, TOTPProd=0, TOTDProd=0, TOTAProd=0,TOTTauProd=0;
	float TotElastic=0, CompoundElastic=0, DirectElastic=0, TotInelastic=0, CompoundInelastic=0, DirectInelastic=0, TotTalys=0;//сечения, для продуктов неупругие соответствуют сечению их образования
	
	vector<float> TOTGamProdValues, TOTNProdValues, TOTPProdValues, TOTDProdValues, TOTAProdValues,TOTTauProdValues;
	vector<float> TotElasticValues, CompoundElasticValues, DirectElasticValues, TotInelasticValues, CompoundInelasticValues, DirectInelasticValues, TotTalysValues;
	
	float BNECS_g, BNECS_n, BNECS_p, BNECS_d, BNECS_t, BNECS_tau, BNECS_a, TEISTot,TEISCont,TEISDiscr;
	
	vector<float> BNECS_g_Values, BNECS_n_Values, BNECS_p_Values, BNECS_d_Values, BNECS_t_Values, BNECS_tau_Values, BNECS_a_Values, TEISTot_Values,TEISCont_Values,TEISDiscr_Values;
	
	bool TalysGroundStateExsists=false, FastFlag=true, FastCalculated=false;
	int OMPoptionN=1, OMPoptionP=1;
	int WriteOMPOrUseKoningP=-1;
	int WriteOMPOrUseKoningN=-1;
	int ThreadNumber=0;
	bool WriteDeformation=false;
	//int TestVar=0;
	AdditionalInformationContainer AI;
	double& AdditionalInformation(string Key); 
	const char *GetName()  const;
	
	OpticalModelParametersData OMPNData;
	OpticalModelParametersData OMPPData;
	DeformationData DefData;
	
	ClassDef(NucleusData, 2);
};

class Nucleus:public NucleusData
{
	public:
	bool PlottedADist=false;
	bool PlottedADist2D=false;
	bool kAlwaysNewGraphs=false;
	bool ConvertToLab=false;
	int MainNucleusFlag=0;
	unsigned int EnergyGridIndex=0;
	
	vector<Level> Levels;
	vector<Level*> LevelsFromTalys;
	vector<Level*> LevelsFromENSDF;
	vector<string> TalysOptions;
	
	list<TGraph> GeneratedGraphsList;
	
	float MinEnergy=0,MaxEnergy=0;
	
	string PathToCalculationDir;
	string OutgoingParticle;
	OpticalModelParameters OMPN;
	OpticalModelParameters OMPP;
	Deformation Def;
	void SetThreadNumber(int _ThreadNumber=0);
	TGraph ElacticTotTalys, ElasticDirectTalys,ElasticCompoundTalys;//угловые распределения
	TGraph2D ElacticTotTalys2D, ElasticDirectTalys2D,ElasticCompoundTalys2D;//угловые распределения
	TGraph InelasticTotTalysV, InelasticDirectTalysV,InelasticCompoundTalysV, ElasticTotTalysV, ElasticDirectTalysV,ElasticCompoundTalysV, TotTalysV;//сечения
	TGraph BNECS_gamma, BNECS_neutron, BNECS_proton, BNECS_deuteron, BNECS_triton, BNECS_3He, BNECS_alpha, TEISGraphTot, TEISGraphCont, TEISGraphDiscr;
	void ReadElastic();
	TGraph* GetElasticAngularDistribution(string type="Total",string option="");//если график упругого уже построен, выдается сохраненный, если нет, или option=="new", строится заново
	TGraph* GetElasticAngularDistributionAtEnergy(float Energy, string type="Total",string option="");
	TGraph2D* GetElasticAngularDistribution2D(string type="Total",string option="");
	void SetOMPOption(string Particle="n",int _OMPoption=1);
	void MergeLevels(float tolerancy);
	void MergeEnergyGridData(vector<Nucleus*> NucleiInEnergyGrid);//функция выполняет копирование данных из вектора NucleiInEnergyGrid для построения энергетической сетки
	void SortingLevels();
	void GenerateEnergyGrig(float min, float step, float max);
	Nucleus* FindProductsByReaction(string reaction);
	Nucleus* FindProductByName(string _Name);
	Nucleus* fMotherNucleus;
	TalysCalculation* fTalysCalculation=0;
	Nucleus()
	{
		TalysCalculated=false;
		fMotherNucleus=0;
	}
	void GetFromNucleusData(NucleusData ND);
	Nucleus(string Name,string Reaction="");
	Nucleus(NucleusData ND);
	//const char *GetName()  const;
	void ReadENSDFFile(string filename="",string Nuclide="");
	void ReadLevelsFromTalysDatabase(string type="final");
	void SetProjectileEnergy(double E);
	//void Print();
	vector<Level*> GetLevelsWithCorrespondingTransitions(float Energy, float tolerancy=1,float intensity=0);
	Level* FindLevelFromTalys(float Energy,SpinParity JP);
	Level* FindBestLevelByEJP(float Energy,SpinParity JP,float tolerancy=1);
	Level* FindLevelByEnergy(float Energy,float tolerancy=1);
	Level* FindLevelByNumber(int number);
	GammaTransition* GetBestTransition(float Energy,float tolerancy=1);
	vector<GammaTransition*> GetGammaTransition(float Energy, float tolerancy=1,float intensity=0);
	vector<GammaTransition*> GetGammaTransitions(string option="Talys",int BetterThan=100,float tolerancy=1,float intensity=0);
	/*опции:
	 * "Talys"-вывести только те линии, для которых есть результат в Talys
	 * "ENSDF"-вывести только те линии, для которых есть результат в ENSDF
	 * "All"-вывести все линии
	 * "not Talys"-все, кроме Talys
	 * "not ENSDF"-все, кроме ENSDF
	 * 
	 * аргумент BetterThan-вывести линии с уровней, mark которых меньше этого значения
	 */
	vector<Nucleus> Products;
	void GenerateProducts(string _Projectile="n");
	void ExecuteCalculationInTalys(string _Projectile="n");
	void ReadTalysCalculationResult();
	void AssignSimilarLevels(float Tolerancy=1.5);
	void DrawLevelScheme(double MinTalysCS=0);
	void AssignPointers();
	void ErasePointers();
	void AssignDeformationsToLevels();
	void SetLevelDeformation(int LevelNumber,char LevT, int BandN=-1, int BandL=-1, int MagN=-1, int NPhon=-1,  vector<float> *DefVec=0);
	void SetLevelDeformation(double LevelEnergy,char LevT, int BandN=-1, int BandL=-1, int MagN=-1, int NPhon=-1, vector<float> *DefVec=0);
	string PrintLevels();
	string PrintReactions();
	string ReactionToTalysNotation(char DataSelection=kExcitationCS);
	TString ReactionInTLatexFormat(string option="full");
	TString NucleusNameInTLatexFormat(string option="short");
	float GetMass();
	NucleusData ToNucleusData();
	void GenerateGammaSpectrum(TH1F *Spectrum, TF1* ResolutionFunction, int NEntries=100000);
	void SetTGraphNameAndTitle(string ValName);
	void AddPoint(double x_value, Nucleus* Nucl);
	void AddPoint(Nucleus* Nucl);
	void GenerateGraphs();
	void SaveToRootFile(TFile *f,string Addition="");
	void ReadFromRootFile(TFile *f,string Name="");
	void ReadFromRootFile(string FileName="",string Name="");
	void SaveToXLSX(string filename);
	static void Recompile()
	{
		system((" cd "+string(getenv("TALYSLIBDIR"))+"; make clean; make").c_str());
	}
	Nucleus& Copy();
	~Nucleus();
	ClassDef(Nucleus, 1);
	private:
	using TObject::GetName;
	using TObject::Copy;
	
};

class Radionuclide:public Nucleus
{
	public:
	void ReadGRDatabase();
	bool IsRead=false;
	Radionuclide(string _Name):Nucleus(_Name) { ReadGRDatabase(); }
	Radionuclide():Nucleus() {  }
	double BranchRatio=0;
	double DecayConstant=0;
	double GetHalfLife();
	
	vector<Radionuclide> Products;
	void AssignPointers();
	vector<GammaTransition*> GetGammaTransitions(double E_thr=0,double Int_thr=0);
	Radionuclide* FindProductByName(string _Name);
	Radionuclide* fMotherNucleus=0;
	ClassDef(Radionuclide, 1);
};

double ConvertAngleToLab(double angle, double ma, double Ta, double mA, double mb, double mB, double Tb);

class TalysFitter
{
	public:
	TF1 FitFunction;
	bool Calculated=false;
	bool ParTrackingFlag=false;
	bool ParChanged=false;
	bool GeneratedTF1=false;
	double x_val;
	TalysFitter(string NuclName);
	Nucleus Nuclide;
	void EnableParTracking();
	void DisableParTracking();
	void TrackParChanges();
	void (*ParAssignmentFunction)(TalysFitter *PointetToTF);
	double (*GetEvaluationResult)(double x_value,TalysFitter *PointetToTF);
	double Eval(double *x, double *p);
	vector<double> PreviousParameters;
	vector<double> Parameters;
	vector<string> ParNames;
	vector<double> Offsets;
	TGraphErrors GraphForMultiFit;
	void AddToGraphForMultiFit(TGraphErrors *gr, double Mv);
	void GenerateGraphForMultiFit(vector<TObject*> &PointersToGraphs,vector<double> &_Offsets);
	void FitMulti();
	TPaveText GenerateTPaveTextForFitResult(double x1=0.7,double y1=0.6,double x2=0.95,double y2=0.95,string Option="br NDC");
	TF1* GenerateTF1(string name, double x_min,double x_max);
};

class TalysFitterMT
{
	public:
	bool Calculated=false;
	bool GeneratedTF1=false;
	TalysFitterMT(string NuclName, unsigned int ThreadNumber=0);
	unsigned int InitThreadNumber=0;
	Nucleus Nuclide;
	Nucleus InitNuclide;
	Nucleus BestNuclide;
	double lambda=1;
	TGraph Chi2Values;
	TGraph FitValues;
	TGraph InitValues;
	vector<TGraph> ParValuesGraphs;
	void FillFitValues();
	void (*ParAssignmentFunctionForPar)(TalysFitterMT *PointetToTF,Nucleus *PointerToNucleus, double ParValue, int Index);
	double (*GetEvaluationResultForNucl)(TalysFitterMT *PointetToTF,double x_value,Nucleus *PointerToNucleus);
	void SaveToRootFile(TFile *f);
	TVirtualFitter *Fitter;
	void InitTVirtualFitter(string type);
	void Minimize(int NCalls=1000, double tolerance=0.01);
	void DrawFitProgress();
	double BestChi2=1e250;
	void GetCurrentGraphNumberAndOffset(double x, int &GraphIterator, double &Offset);
	void SetParameter(unsigned int n, double value, string name, double epsilon, double low, double high);
	void SetParameter(unsigned int n, double value, string name, double epsilon, double range);
	void (*ParAssignmentFunction)(TalysFitterMT *PointetToTF,Nucleus *Nucl, vector<double> Parameters);
	double (*GetEvaluationResult)(double x_value,TalysFitterMT *PointetToTF,Nucleus *Nucl);
	void FCN(int &npar, double *gin, double &f, double *par, int flag);
	vector<double> InitParameters;
	vector<double> Parameters;
	vector<double> LowLimits;
	vector<double> HighLimits;
	vector<double> EpsilonValues;
	vector<double> EvalGrad();
	vector<string> ParNames;
	vector<double> Offsets;
	TGraphErrors GraphForMultiFit;
	void AddToGraphForMultiFit(TGraphErrors *gr, double Mv);
	void GenerateGraphForMultiFit(vector<TObject*> &PointersToGraphs,vector<double> &_Offsets);
	TPaveText GenerateTPaveTextForFitResult(double x1=0.7,double y1=0.6,double x2=0.95,double y2=0.95,string Option="bl NDC");
};
double EvalChi2(TalysFitterMT *TFM,Nucleus* Nucl);

class TalysCalculation:public TObject
{
	public:
	vector<Nucleus> Results;
	//void EvalInThread(unsigned int index);
	bool EnableMultiThreading=false;
	Nucleus* FinalResult;//здесь хранится расчет с максимальным значением параметра, в нем будут графики для неупругих сечений
	string Target, Proj;
	vector<string> TalysOptions;
	string Variable="Energy";
	TGraph Elastic, Inelastic;
	vector<double> VarValues;
	bool GeneratedGraphs=false;
	
	double ProjectileEnergy;
	void ReadParametersFromFile(string filename);
	void ExecuteCalculation();
	void ExecuteCalculation(void (*VarChangeFunction)(Nucleus *Nuclide,double value));
	void ExecuteCalculation(void (*VarChangeFunction)(Nucleus *Nuclide,vector<double> &value),vector<vector<double> > &VariableValues);
	void SetTarget(string _Target);
	void SetProjectile(string _Proj);
	void SetVarValues(double min,double max,double step);
	void GenerateGraphs();
	TGraph *GetLevelExcitationCrossSection(double LevelEnergy,string NucleusName="",string Option="Total");
	TGraph *GetGammaTransitionCrossSction(double GammaEnergy,string NucleusName="");
	TMultiGraph* GetAngularDistributionsForLevel(double LevelEnergy,string NucleusName="",string type="Total",string option="",TLegend *leg=0);//выдает TMultiGraph с угловыми распределениями, соответствующими значениям VarValues
	TMultiGraph* GetElasticAngularDistributions(string type="Total",string option="",TLegend *leg=0);//выдает TMultiGraph с угловыми распределениями, соответствующими значениям VarValues
	
	
	ClassDef(TalysCalculation, 1);
};

GammaTransition* GetBestTransitionFromVector(float Energy, float Tolerancy,vector<Nucleus> &Nuclei);
void ReadNucleiFromRootFile(vector<Nucleus> &Nuclei,TFile *f);
int CheckGammaTransitionIntegrality(GammaTransition* gt);

class TLMaterial:public TObject
{
	public:
	bool EnableMultiThreading=true;
	int NThreads=7;
	bool GeneratedLineList=false;
	vector<GammaTransition*> Gammas;
	vector<GammaTransition> Bkg;
	string MaterialFormula;
	double Density;
	double MolarMass=0;
	double GetMolarMass();
	bool Calculated=false;
	vector<Nucleus*> Nuclides;
	vector<int> Quantities;
	TLMaterial():TObject(){ };
	TLMaterial(string _MaterialFormula);
	void SetDensity(double _Density);
	double GetDensity();
	void AddElement(string Element, int Q);
	void AddBackground(string PathToBackground);
	void SaveToXLSX(string filename);
	void PrintGammas(double CrossSectionThreshold=0,bool UseAbundancy=true);
	vector<GammaTransition*> GetGammaTransitions(double CrossSectionThreshold=0,bool UseAbundancy=true);
	vector<GammaTransition*> GetGammaTransitionsE(double EnergyThreshold=0,double CrossSectionThreshold=0,bool UseAbundancy=true);
	~TLMaterial()
	{
		for(unsigned int i=0;i<Nuclides.size();i++)
		{
			delete Nuclides[i];
		}
	}
	ClassDef(TLMaterial, 1);
};

class SampleInformation:public TObject //класс, хранящий информацию об образце и фоне
{
	private:
	double SizeX, SizeY, SizeZ, PositionX, PositionY, PositionZ, Density;
	vector<NucleusData> Nuclei;
	vector<NucleusData> NucleiInMedia;
	string Substance;
	vector<string> Elements;
	vector<string> ElementsInMedia;
	vector<int> Quantities;
	void GenerateNucleiListFromSubstance();
	string Name; 
	string SampleType;
	public:
	SampleInformation():TObject(){ }
	SampleInformation(string substance, double Density, double SizeX=6, double SizeY=6, double SizeZ=14, double PositionX=0, double PositionY=0, double PositionZ=0);
	void SetListOfNucleiInMedia(string List);
	void SetListOfNuclei(string List);
	void SetListOfNuclei(vector<Nucleus> &Nuclei);
	void SetListOfNucleiInMedia(vector<Nucleus> &Nuclei);
	void SetSubstance(string Substance);
	void SetPosition(double PositionX=0, double PositionY=0, double PositionZ=0);
	void SetSizes(double SizeX=6, double SizeY=6, double SizeZ=14);
	void SetDensity(double Density);
	void SetSampleType(string Type);
	vector<NucleusData> GetListOfNuclei();
	vector<NucleusData> GetListOfNucleiInMedia();
	string GetSubstance();
	vector<string> GetElements();
	vector<string> GetElementsInMedia();
	vector<int> GetQuantities();
	void SaveToRootFile(TFile *f);
	void ReadFromRootFile(TFile *f,string Name="");
	void ReadFromRootFile(string FileName="",string Name="");
	void ReadFromTXTFile(string filename);
	void SetName(string Name);
	const char* GetName();
	double GetConcentration(string Nucl="");
	double GetDensity(); 
	string GetSampleType();
	void GetSizes(double &SizeX, double &SizeY, double &SizeZ);
	void GetPosition(double &PositionX, double &PositionY, double &PositionZ);
	ClassDef(SampleInformation, 1);
	private:
	using TObject::GetName;
};


