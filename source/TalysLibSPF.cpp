#pragma once
#include "../TalysLib.hh"

double TalysLibSPF::_GetNuclearMass(string nucleus)
{
	return GetNuclearMass(nucleus);
}
double TalysLibSPF::_GetAbundance(string nucleus)
{
	return GetAbundance(nucleus);
}

double TalysLibSPF::_GetAbundance(string nucleus,string EnrichedIsotope,double abun)
{
	double Abun1=0;
	int SelectedA=_GetA(EnrichedIsotope);
	int UsedA=_GetA(nucleus);
	double UsedAbun=0;
	vector<int> A_values;
	vector<double> Abundances;
	string Element=GetNucleusName(nucleus);
	GetAbundance(Element,A_values,Abundances);
	for(unsigned int i=0;i<A_values.size();i++)
	{
		if(A_values[i]==SelectedA)
		{
			continue;
		}
		if(A_values[i]==UsedA)
		{
			UsedAbun=Abundances[i];
		}
		Abun1+=Abundances[i];
	}
	double k_norm=(1-abun)/Abun1;
	return k_norm*UsedAbun;
}

double TalysLibSPF::_GetNuclearMass(int Z, int A)
{
	return GetNuclearMass( Z,  A);
}
double TalysLibSPF::_GetSeparationEnergy(string nucleus, string particle)
{
	return GetSeparationEnergy(nucleus,particle);
}
double TalysLibSPF::_GetSeparationEnergy(int nucleus_Z, int nucleus_A, int particle_Z, int particle_A)
{
	return GetSeparationEnergy( nucleus_Z,  nucleus_A,  particle_Z,  particle_A);
}

double TalysLibSPF::_RecoilEnergyFromGammaEmission(double Egamma, string nuclide)
{
	return RecoilEnergyFromGammaEmission( Egamma,  nuclide);
}
int TalysLibSPF::_Nproc()
{
	return Nproc();
}
float TalysLibSPF::_EvalKineticEnergy(float ma,float mA,float mb,float mB,float Ta,float angle,float Q)//reference: http://nuclphys.sinp.msu.ru/reactions/cinem.htm
{
	return EvalKineticEnergy( ma, mA, mb, mB, Ta, angle, Q);
}
float TalysLibSPF::_EvalKineticEnergy(string a,string A,string b,string B,float Ta,float angle)//reference: http://nuclphys.sinp.msu.ru/reactions/cinem.htm
{
	return EvalKineticEnergy( a, A, b, B, Ta, angle);
}
float TalysLibSPF::_EvalKineticEnergy(string a,string A,string b,string B,float Ta,float angle,double Q)//reference: http://nuclphys.sinp.msu.ru/reactions/cinem.htm
{
	return EvalKineticEnergy( a, A, b, B, Ta, angle, Q);
}
double TalysLibSPF::_RelKineticEnergy(float ma,float mA,float mb,float mB,float Ta,float angle)//релятивистская формула для кинетической энергии. Для расчета энергий неупруго рассеянных нейтронов нужно добавить Q к mB при вызове
{
	return RelKineticEnergy( ma, mA, mb, mB, Ta, angle);
}
int TalysLibSPF::_GetZ(string nucleus)
{
	int z,a;
	GetAZ(nucleus,z,a);
	return z;
}
int TalysLibSPF::_GetA(string nucleus)
{
	int z,a;
	GetAZ(nucleus,z,a);
	return a;
}
string TalysLibSPF::_GetElementName(int Z)
{
	return GetNucleusName(Z);
}
vector<string> TalysLibSPF::_GetElementNames(int Z)
{
	return GetElementNames(Z);
}
vector<string> TalysLibSPF::_GetElementNames(string NuclName)
{
	return GetElementNames(NuclName);
}
