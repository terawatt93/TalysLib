#pragma once
#include <stdio.h>
#include <vector>
#include <cstring>
#include <sstream>
#include <iostream>
#include <fstream>
#include <cmath>
#include <TString.h>
#include "Constants.cpp"
#include <stdarg.h> 
#include <cstdlib>
#include <dirent.h>
#include <TPad.h>
#include <TGraph.h>
#include <TGraph2D.h>
#include <TCanvas.h>
#include <TFile.h>
#include <TKey.h>

#define AngularMomentumSize 7
using namespace std;
template <typename T> bool InVector(vector<T> &vec,T element)
{
	for(unsigned int i=0;i<vec.size();i++)
	{
		if(element==vec[i])
		{
			return true;
		}
	}
	return false;
}
void CopyFileContentToBuffer(ifstream &t,string &buff);
void CopyFileContentToBuffer(string Filename,string &buff);

//void ChangeParNumeration(string &init, string &result, vector<pair<int,int> > &Combinations);
string ChangeParNumeration(string &init, int MinIndex=0);
bool IsNumber(const std::string& s);
bool IsFloat(const std::string& s);

vector<string> GetListOfObjectNames(TFile *f);
vector<TPad*> GeneratePadsOnCanvas(double x1, double y1, double x2, double y2,int nx, int ny,TCanvas *c=0);

void AddPointToTGraph(TGraph* gr, double x_value, double y_value);

void AddPointToTGraph(TGraph2D* gr, double x_value, double y_value, double z_value);

bool IsDirectoryAlreadyExsisted(string Name);//функция проверяет, существует ли директория с данным именем. Нужна для решения конфликтов, возникающих при одновременном расчете двух ядер с однинаковым именем

std::vector<std::string> SplitString(const std::string &s, char delim, bool MergeDelimeters=true);
std::vector<std::string> FromFortranFormat(string str,string Format);

string GetPotential(ifstream &ifs);
void EscapeNextNLines(ifstream &ifs,unsigned int N);
string GetPathToTalysData();

int sgn(int val);

bool CompareBeginOfString(string s1, string s2);

vector<double> QuantumSum(float A, float B);
vector<double> Multipolarities(float JPf,float JPi);

string GetField(string input, int FieldNumber);
int FindInVector(int element,vector<int> v);


void ParseReaction(string reaction, string &Projectile, string &OutgoingParticle);
string NLJToString(int n, int L, float J);

int StringToNLJ(string s, int &n, int &l, float &JP);

string LToString(int L);

vector<int> StringLToInt(string L_string);

string GetNucleusName(int Z);
string GetNucleusName(string Name);

string GetParticleName(int Z, int A);
double TalysJPToNormalJP(string TalysJP);

void GetAZ(string nucleus, int &Z, int &A);

int GetTalysVersion();

double GetNuclearMass(string nucleus);
void GetAbundance(string nucleus,vector<int> &A_values, vector<double> &Abundances);
double GetAbundance(string nucleus);
double GetAverageMass(string nucleus);

double GetNuclearMass(int Z, int A);
double GetSeparationEnergy(string nucleus, string particle="n");
double GetSeparationEnergy(int nucleus_Z, int nucleus_A, int particle_Z, int particle_A);
void ParceReaction(string reaction, string &type, int &ParticleType);
double DopplerBroading(double E,double MNucl);
double HPGeSigma(double E,string Nucleus);
double RefSigmaForDet(double E, TString Det);

double HPGeSigmaOSGI(double E);
double HPGeSigma(double E,int Z, int A);
double RecoilEnergyFromGammaEmission(double Egamma, string nuclide);
int Nproc();
vector<string> ListFiles(string mask, string PathTo="");
vector<string> FindFile(vector<string> Paths, string Mask);
void GenerateListOfElements(string composition, vector<string> &Elements, vector<int> &Quantity);
double GetMolarMass(string Composition);
vector<double> GetMolarMassFractions(string Composition);
string InvertString(string line);
string GetFileType(string line);
float GetEnergyFromFileName(string line);
string GetPath(string line);
string GetFileName(string line);
float EvalKineticEnergy(float ma,float mA,float mb,float mB,float Ta,float angle,float Q);//reference: http://nuclphys.sinp.msu.ru/reactions/cinem.htm
float EvalKineticEnergy(string a,string A,string b,string B,float Ta,float angle);//reference: http://nuclphys.sinp.msu.ru/reactions/cinem.htm
float EvalKineticEnergy(string a,string A,string b,string B,float Ta,float angle,double Q);//reference: http://nuclphys.sinp.msu.ru/reactions/cinem.htm
double RelKineticEnergy(float ma,float mA,float mb,float mB,float Ta,float angle);//релятивистская формула для кинетической энергии. Для расчета энергий неупруго рассеянных нейтронов нужно добавить Q к mB при вызове

