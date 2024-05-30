//#include "includes_main.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <map>
#include <complex>
 
#include "RConfigure.h"
#include "Math/SpecFuncMathCore.h"
#include "Math/SpecFuncMathMore.h"

typedef complex<double> complexd;
#pragma once
using namespace ROOT::Math;


// calclation of Racah function U(j1,j2,j5,j4;j3,j6)

double Racah(double j1, double j2, double j5, double j4, double j3, double j6);// j1,j2,j4,j5 ; j3,j6

// calculation of clebsh_gordan coefficients C_{j1 m1 j2 m2}^{j3 m3}

double clebsh_gordan(double j1,double m1, double j2,double m2, double j3, double m3);

// calculation of 9j-symbols 
//  ( j1 j2 j3 )
//  ( j4 j5 j6 )
//  ( j7 j8 j9 )

double j9sym(double j1, double j2, double j3, double j4, double j5, double j6, double j7, double j8, double j9);

double g_J(double J, double s=0.5, int Ia =0 );

// make vector of allowed transmission from alpha channel to beta channel (related to spin  and paritty conservation)

vector<tuple<double, int, double, int, double>> lj();
class Dlam;
class ST_Matrix; 

// class with elements after reading fort.60 and fort.70
class ST_Matrix
{	
	public:
	// S_matrix  S_{J} (l_\alpha j_\alpha \to l_\beta j_beta)
	// see formula 17 in file Gamma-02.pdf
	map<tuple<int, int, int, int, double, double>, complexd> S1; // S-matrix indexes [(el/inel, number of block, l_a, l_b, j_a, j_b)] 
	map<tuple<int, int, int, int, double, double>, double> Smod; // module of S-matrix
	map<tuple<TString, int, int, double, double, TString>, double> Trans; // transmission coefficients [("particle",level, l, j, J, "parity")]
	map<tuple<double, TString>, double> Tfull; // sum of all channels for spin of compound nucleus J
	
	friend class Dlam;
	bool WasRead=false;
	int ReadSmatrix(string SMBuf);
	int ReadTransCoef(string TransBuf);
	
	
	void Read(string SMBuf,string TransBuf)
	{
		ReadSmatrix(SMBuf);
		ReadTransCoef(TransBuf);
	}
	int BlockNumber=0;
};

// class of coefficients before angular functuons 
// D^{lam}_{lam1 Q}
class Dlam
{
	int lam = 0, lam1 = 0, Q = 0; // lam - initial neutron, lam1 - scatterd neutron, Q - gamma 
	TF1 phi;
	complexd result = complexd(0,0); // result of calcutalions 
	double beg; 
	int L = 2;
	int Ii = 2, If = 0, Ia = 0;
	int BlockNumber=0;
	double s = 0.5;
	public:
	Dlam();	
	Dlam(int Lam,int Lam1,int QQ);
	
	int addS(ST_Matrix &AD);// function to calculate direct part of reaction
	int addT(ST_Matrix &AD);// function to calculate compound part of reaction
	double pr_result(){return result.real();} 

};
