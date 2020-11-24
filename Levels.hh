#include <sstream>
#include <iostream>
#include <TObject.h>
#include <TRandom.h>
#include <TH1F.h>
#include <TFile.h>
#include <TGraph.h>
#include <TMultiGraph.h>
#pragma once
using namespace std;


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

class Level;
class Nucleus;
class Deformation;
class OpticalModelParameters:public TObject
{
	public:
	double Vv, Wv, Rv, Av, Wd, Rd, Ad, Vso, Wso, Rso, Aso, Rc, v1, v2, v3, v4, w1, w2, d1, d2, d3, vso1, vso2, wso1, wso2, A, N, Z, ProjectileEnergy, Ef, Vc;
	bool NormalisationMode=true;
	bool Read=false;
	bool JLM_flag=false;
	bool goriely=false;
	bool hilaire=false;
	bool Koning=false;
	string Projectile;
	Nucleus *Nuclide;
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
	bool ReadOMP();
	void SaveOMP();//способ записи OMP приведен в omppar.f
	void RestoreOMP();
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
	float Energy,EnergyErr,Intensity,CrossSection,E_in,Tolerancy,Rel_Cs,TalysCrossSection, TalysE_i,TalysE_f;
	SpinParity TalysJP_i,TalysJP_f;
	vector<SpinParity> TalysMultipolarity;
	string Multipolarity,nuclide,reaction, Origin;
	ClassDef(GammaTransitionData, 1);
};

class GammaTransition:public GammaTransitionData
{
	public:
	//float Energy,EnergyErr,Intensity,CrossSection,E_in,Tolerancy,Rel_Cs,TalysCrossSection, TalysE_i,TalysE_f, TalysJP_i,TalysJP_f,TalysMultipolarity;
	TGraph CSGraph;
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
	GammaTransition(GammaTransitionData d);
	bool ReadTransition(string line,string ReadNuclName, float E_in);
	string GetLine(string option="");//possible option:brief
	bool CheckEnergy(float E,float Tolerancy,float intensity=0);
	const char *GetName()  const;
	void FindFinalLevel(double Tolerancy=2);
	void SetInformationExtractedFromTalys(float TalysE_f, float TalysE_i, SpinParity JP_f, SpinParity JP_i);
	void ErasePointers();
	double GetEnergy();
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
	vector<float> ADTot,ADDirect, ADCompound, Angle,Branching;
	vector<unsigned int> NumbersOfFinalLevels;
	ClassDef(LevelData, 1);
};

class LevelDeformation:public TObject
{
	public:
	char TypeOfLevel,TypeOfDeformation;
	LevelDeformation(char Type='B'):TObject() {TypeOfDeformation='B';}
	int NumberOfBand, NumberOfLevel, LOfBand=-1, NumberOfPhonons=-1, MagneticNumber=-1;
	vector<float> Beta;
	void GetFromString(string input);
	void TurnToBeta(int A);
	TString GenerateStringForDefFile();
	Level* fLevel=0;
	Deformation *fDeformation=0;
	ClassDef(LevelDeformation, 1);
};
class Deformation:public TObject
{
	public:
	Deformation():TObject() { }
	int A,Z,NLevels;
	char TypeOfCollectivity,TypeOfDeformation;
	vector<LevelDeformation> LevelDeformations;
	vector<string> ContentOfFile;
	unsigned int PointToPastChangedDeformation=0;
	void SetZA(int _Z,int _A);
	void ReadDeformation();
	void WriteDeformation();
	void RestoreDeformation();
	void Sort();
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
	bool PlottedADist=false;
	TGraph AdistTotalTalys, AdistCompoundTalys, AdistDirectTalys;//угловые распределения
	TGraph CSGraph, CSCompoundGraph, CSDirectGraph;
	int Number;
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
	void SetDeformation(char LevT, int BandN=-1, int BandL=-1, int NPhon=-1, int MagN=-1, vector<float> *Def=0);//генерирует объект deformation и добавляет его в ядерную деформацию.
	//порядок и назначение аргументов соответствуют .def файлу (ECIS_report.pdf, стр.3)
	//методы для получения параметров уровня
	float GetEnergy(); float GetEnergyErr(); float GetTalysCS(); SpinParity GetTalysSpinParity();
	string GetOrigin(); vector<SpinParity>& GetJPValues(); vector<Level*>& GetSimilarLevels();
	void AssignPointers();
	void ErasePointers();
	TGraph* GetAngularDistribution(string type="Total",string option="");//если график уже построен, выдается сохраненный, если нет, или option=="new", строится заново
	TMultiGraph* GetTMultiGraphForAngularDistributions(string graphics="all");
	LevelData ToLevelData();
	void SetTGraphNameAndTitle(string ValName);
	void AddPoint(double x_value,Level *level);
	ClassDef(Level, 1);
};

class NucleusData:public TObject
{
	public:
	NucleusData(): TObject() {  }
	string Name,Reaction,Projectile;
	int A,Z;
	vector<LevelData> LevelsData;
	vector<NucleusData> ProductsData;
	bool TalysCalculated;
	double Abundance,ProjectileEnergy=14.1;
	//сечения и дифсечения
	vector<float> Angle, ElTot, ElCompound, ElDirect;//дифсечения
	float TOTGamProd=0, TOTNProd=0, TOTPProd=0, TOTDProd=0, TOTAProd=0;
	float TotElastic=0, CompoundElastic=0, DirectElastic=0, TotInelastic=0, CompoundInelastic=0, DirectInelastic=0, TotTalys=0;//сечения, для продуктов неупругие соответствуют сечению их образования
	float BNECS_g, BNECS_n, BNECS_p, BNECS_d, BNECS_t, BNECS_tau, BNECS_a, TEISTot,TEISCont,TEISDiscr;
	const char *GetName()  const;
	ClassDef(NucleusData, 1);
};

class Nucleus:public NucleusData
{
	public:
	bool PlottedADist=false;
	vector<Level> Levels;
	vector<Level*> LevelsFromTalys;
	vector<Level*> LevelsFromENSDF;
	vector<string> TalysOptions;
	Deformation Def;
	TGraph ElacticTotTalys, ElasticDirectTalys,ElasticCompoundTalys;//угловые распределения
	TGraph InelasticTotTalysV, InelasticDirectTalysV,InelasticCompoundTalysV, ElasticTotTalysV, ElasticDirectTalysV,ElasticCompoundTalysV, TotTalysV;//сечения
	TGraph BNECS_gamma, BNECS_neutron, BNECS_proton, BNECS_deuteron, BNECS_triton, BNECS_3He, BNECS_alpha, TEISGraphTot, TEISGraphCont, TEISGraphDiscr;
	void ReadElastic();
	TGraph* GetElasticAngularDistribution(string type="Total",string option="");//если график упругого уже построен, выдается сохраненный, если нет, или option=="new", строится заново
	bool TalysGroundStateExsists=false;
	void MergeLevels(float tolerancy);
	void SortingLevels();
	Nucleus* FindProductsByReaction(string reaction);
	Nucleus* fMotherNucleus;
	Nucleus()
	{
		TalysCalculated=false;
		fMotherNucleus=0;
	}
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
	Level* FindLevelByNumber(int number);
	GammaTransition* GetBestTransition(float Energy,float tolerancy=1);
	void PrintLevelsWithCorrespondingTransitions(float Energy, float tolerancy=1,float intensity=0);
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
	void GenerateProducts(string Projectile="n");
	void ExecuteCalculationInTalys(string Projectile="n");
	void ReadTalysCalculationResult();
	void AssignSimilarLevels(float Tolerancy=1.5);
	void DrawLevelScheme(double MinTalysCS=0);
	void AssignPointers();
	void ErasePointers();
	void AssignDeformationsToLevels();
	string PrintLevels();
	string PrintReactions();
	string ReactionToTalysNotation(char DataSelection=kExcitationCS);
	float GetMass();
	NucleusData ToNucleusData();
	void GenerateGammaSpectrum(TH1F *Spectrum, TF1* ResolutionFunction, int NEntries=100000);
	void SetTGraphNameAndTitle(string ValName);
	void AddPoint(double x_value, Nucleus* Nucl);
	ClassDef(Nucleus, 1);
};

class TalysCalculation:public TObject
{
	public:
	vector<Nucleus> Results;
	Nucleus* FinalResult;//здесь хранится расчет с максимальным значением параметра, в нем будут графики для неупругих сечений
	string Target, Proj;
	vector<string> TalysOptions;
	string Variable="Energy";
	TGraph Elastic, Inelastic;
	vector<double> VarValues;
	double ProjectileEnergy;
	void ReadParametersFromFile(string filename);
	void ExecuteCalculation();
	void SetTarget(string _Target);
	void SetProjectile(string _Proj);
	void SetEnergies(double min,double max,double step);
	void GenerateGraphs();
	TGraph GetLevelExcitationCrossSection(double LevelEnergy,string NucleusName="");
	TGraph GetGammaTransitionCrossSction(double GammaEnergy,string NucleusName="");
	ClassDef(TalysCalculation, 1);
};

GammaTransition* GetBestTransitionFromVector(float Energy, float Tolerancy,vector<Nucleus> &Nuclei);
void ReadNucleiFromRootFile(vector<Nucleus> &Nuclei,TFile *f);
int CheckGammaTransitionIntegrality(GammaTransition* gt);
	

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
};


