#include "../TalysLib.hh"
#include <sys/stat.h>

#include <bits/stdc++.h>
#include <cstring>
#include <algorithm>
#include <cctype>
#include "../Parser.cpp"
#include <TLine.h>
#include <TText.h>
#include <TList.h>
#include <TKey.h>
#include "SpinParity.cc"
#pragma once
//методы класса OpticalModelParameters
void OMPStorage::SetNucleus(Nucleus *_Nuclide)
{
	Nuclide=_Nuclide;
	A=Nuclide->A;
	Z=Nuclide->Z;
	N=A-Z;
}
void OMPStorage::SetProjectile(string _Projectile)
{
	Projectile=_Projectile;
}
void OMPStorage::SetProjectileEnergy(double Energy)
{
	ProjectileEnergy=Energy;
	if(Projectile=="n")
	{
		Vc=0;
		Ef=-11.2814+0.02646*A;
	}
	else if(Projectile=="p")
	{
		Rc=1.198+0.697*pow(A,-2/3)+12.994*pow(A,-5/3);
		Vc=1.73*Z*A-(1.0/3.0)/Rc;
		Ef=-8.4075 + 0.01378*A;
	}
}
void OpticalModelParameters::SetVv(double value)
{
	if(NormalisationMode)
	{
		//double CurrentVv=v1()
	}
}
TString OMPStorage::GetTString()
{
	TString result;
	result+=TString::Format("%4i%7.2f%8.3f\n",Type,Ef,Rc);
	result+=TString::Format("%8.3f%8.3f%6.1f%10.4f%9.6f%6.1f%7.1f\n",Rv,Av,v1,v2,v3,w1,w2);
	result+=TString::Format("%8.3f%8.3f%6.1f%10.4f%7.2f\n",Rd,Ad,d1,d2,d3);
	result+=TString::Format("%8.3f%8.3f%6.1f%10.4f%6.1f%7.1f\n",Rso,Aso,vso1,vso2,wso1,wso2);
	return result;
}
TString OMPStorage::GetInHumanReadable()
{
	TString result="    V_v    r_v    a_v    Wv    rw    aw    Vd    rvd    avd    Wd    rwd    awd    Vso    rvso    avso    Wso    rwso    awso\n";
	result+=TString::Format("%4.3f %4.3f %4.3f %4.3f %4.3f %4.3f %4.3f %4.3f %4.3f %4.3f %4.3f %4.3f %4.3f %4.3f %4.3f %4.3f %4.3f %4.3f",Vv, Rv, Av, Wv, Rv, Av, 0.0, Rd, Ad, Wd, Rd, Ad, Vso, Rso, Aso, Wso, Rso, Aso);
	return result;
	
}
/*void OpticalModelParameters::SetWv(double value)
void OpticalModelParameters::SetRv(double value)
void OpticalModelParameters::SetAv(double value)
void OpticalModelParameters::SetWd(double value)
void OpticalModelParameters::SetRd(double value)
void OpticalModelParameters::SetAd(double value)
void OpticalModelParameters::SetVso(double value)
void OpticalModelParameters::SetRso(double value)
void OpticalModelParameters::SetAso(double value)
void OpticalModelParameters::SetRc(double value)
void OpticalModelParameters::Setv1(double value)
void OpticalModelParameters::Setv2(double value)
void OpticalModelParameters::Setv3(double value)
void OpticalModelParameters::Setv4(double value)
void OpticalModelParameters::Setw1(double value)
void OpticalModelParameters::Setw2(double value)
void OpticalModelParameters::Setd1(double value)
void OpticalModelParameters::Setd2(double value)
void OpticalModelParameters::Setd3(double value)
void OpticalModelParameters::Setvso1(double value)
void OpticalModelParameters::Setvso2(double value)
void OpticalModelParameters::Setwso1(double value)
void OpticalModelParameters::Setwso2(double value)*/

void OMPStorage::EvalKoning()
{
	if(!Nuclide)
	{
		cout<<"Cannot evaluate Koning parametrisation! Pointer to Nucleus is invalid!\n";
	}
	N=Nuclide->A-Nuclide->Z; Z=Nuclide->Z; A=Nuclide->A;
	double E=ProjectileEnergy;
	if(Projectile=="n")
	{
		v1=59.30-21.0*(N-Z)/A-0.024*A;
		v2=0.007228 - 1.48e-6*A;
		v3=1.994e-5 - 2.0e-8*A;
		v4=7.10e-9;
		w1=12.195 + 0.0167*A;
		w2=73.55 + 0.0795*A;
		d1=16.0 - 16.0*(N - Z)/A;
		d2=0.0180 + 0.003802/(1 + exp((A - 156.)/8.));
		d3=11.5;
		vso1=5.922 + 0.0030*A;
		vso2=0.0040;
		wso1=-3.1;
		wso2=160.;
		Ef=-11.2814 + 0.02646*A;
		Rv=1.3039 - 0.4054*pow(A,-1.0/3);
		Av=0.6778 - 1.487e-4*A;
		Rd=1.3424 - 0.01585*pow(A,1.0/3);
		Ad=0.5446 - 1.656e-4*A;
		Rso=1.1854 - 0.647*pow(A,-1.0/3);
		Aso=0.59;
		Vc=0;
	}
	else if(Projectile=="p")
	{
		v1=59.30 + 21.0*(N - Z)/A - 0.024*A;
		v2=0.007067 + 4.23e-6*A;
		v3=1.729e-5 + 1.136e-8*A;
		v4=7.10e-9;
		w1=14.667 + 0.009629*A;
		w2=73.55 + 0.0795*A;
		d1=16.0 + 16.0*(N - Z)/A;
		d2=0.0180 + 0.003802/(1 + exp((A - 156.)/8.));
		d3=11.5;
		vso1=5.922 + 0.0030*A;
		vso2=0.0040;
		wso1=-3.1;
		wso2=160.;
		Ef=-8.4075 + 0.01378*A;
		Rc=1.198 + 0.697*pow(A,-2.0/3) + 12.994*pow(A,-5.0/3);
		Rv=1.3039 - 0.4054*pow(A,-1.0/3);
		Av=0.6778 - 1.487e-4*A;
		Rd=1.3424 - 0.01585*pow(A,1.0/3);
		Ad=0.5187 + 5.205e-4*A;
		Rso=1.1854 - 0.647*pow(A,-1.0/3);
		Vc=1.73*Z*pow(A,-1.0/3)/Rc;
	}
	EvalPotential();
	/*Vv=v1*(1-v2*(E-Ef)+v3*pow((E-Ef),2)+v4*pow((E-Ef),3));
	Wv=w1*(pow((E-Ef),2)/(pow((E-Ef),2)+pow(w2,2)));
	Wd=d1*pow((E-Ef),2)*exp(-d2*(E-Ef))/(pow((E-Ef),2)+pow(d3,2));
	Vso=vso1*exp(-vso2*(E-Ef));
	Wso=wso1*(pow((E-Ef),2)/(pow((E-Ef),2)+pow(wso2,2)));*/
}

void OMPStorage::EvalPotential()
{
	double E=Nuclide->ProjectileEnergy;
	Vv=v1*(1 - v2*(E - Ef) + v3*pow((E - Ef),2) - v4*pow((E - Ef),3))+Vc*v1*(v2-2*v3*(E-Ef)+3*v4*pow(E-Ef,2));
	Wv=w1*pow((E-Ef),2)/(pow(E-Ef,2)+pow(w2,2));
	Wd=d1*pow(E-Ef,2)/(pow(E-Ef,2)+pow(d3,2))*exp(-d2*(E-Ef));
	Vso=vso1*exp(-vso2*(E-Ef));
	Wso=wso1*pow(E-Ef,2)/(pow(E-Ef,2)+pow(wso2,2));
}
void OMPStorage::Read(string &Buffer)
{
	stringstream s(Buffer);
	s>>Type>>Ef>>Rc;
	s>>Rv>>Av>>v1>>v2>>v3>>w1>>w2;
	s>>Rd>>Ad>>d1>>d2>>d3;
	s>>Rso>>Aso>>vso1>>vso2>>wso1>>wso2;
	ReadFlag=true;
}
OpticalModelParameters::OpticalModelParameters()
{
	Potential.Type=1;
	PotentialDisp.Type=2;
	PotentialKoning.Type=3;
}

string GetPotential(ifstream &ifs)
{
	string result;
	for(unsigned int i=0;i<4;i++)
	{
		string tmp;
		getline(ifs,tmp);
		result+=tmp;
		result+="\n";
	}
	return result;
}

bool OpticalModelParameters::ReadOMP(string _Projectile)
{
	Projectile=_Projectile;
	Potential.SetProjectile(_Projectile);
	PotentialDisp.SetProjectile(_Projectile);
	PotentialKoning.SetProjectile(_Projectile);
	if(!Nuclide)
	{
		cout<<"OpticalModelParameters::ReadOMP() Error! Nucleus does not set!";
		return false;
	}
	else
	{
		Potential.Nuclide=Nuclide;
		PotentialDisp.Nuclide=Nuclide;
		PotentialKoning.Nuclide=Nuclide;
		PotentialKoning.EvalKoning();
		string OMPFileName=GetPathToTalysData()+"/structure/optical/";
		Z=Nuclide->Z;
		A=Nuclide->A;
		N=A-Z;
		if(JLM_flag)
		{
			if(goriely)
			{
				OMPFileName+="jlm/goriely/"+GetNucleusName(Z)+".rad";
			}
			else if(hilaire)
			{
				OMPFileName+="jlm/hilaire/"+GetNucleusName(Z)+".rad";
			}
		}
		else
		{
			if(Projectile=="n")
			{
				OMPFileName+="neutron/n-"+GetNucleusName(Z)+".omp";
			}
			else if(Projectile=="p")
			{
				OMPFileName+="proton/p-"+GetNucleusName(Z)+".omp";
			}
		}
		ifstream ifs(OMPFileName);
		if(!ifs.good())
		{
			cout<<"Warning: predefined OMP for "<<GetNucleusName(Z)<<" and projectile "<<Projectile<<" does not exsists! Koning parametrisation will be used.\n";
			Koning=true;
			ifs.close();
		}
		else
		{
			Koning=false;
			string line;
			unsigned int iterator=0;
			while(getline(ifs,line))
			{
				stringstream s(line);
				int _A,_Z;
				s>>_Z>>_A>>nOMP;
				if((Nuclide->A==_A)&&(Nuclide->Z==_Z))
				{
					PointToPasteChangedOMP=ContentOfFile.size();
					Read=true;
					string Buffer=GetPotential(ifs);
					stringstream Str1(Buffer);
					int type;
					Str1>>type;
					if(type==1)
					{
						Potential.Read(Buffer);
					}
					if(type==2)
					{
						PotentialDisp.Read(Buffer);
					}
					if(nOMP==2)
					{
						Buffer=GetPotential(ifs);
						stringstream Str2(Buffer);
						Str2>>type;
						if(type==1)
						{
							Potential.Read(Buffer);
						}
						if(type==2)
						{
							PotentialDisp.Read(Buffer);
						}
					}
					
				}
				else
				{
					ContentOfFile.push_back(line);
				}
			}
			ifs.close();
		}		
	}
}
void OpticalModelParameters::SaveOMP(string filename,int UseKoning)
{
	if(UseKoning<0)
	{
		return ;
	}
	ofstream ofs(filename.c_str());
	TString Insert;
	nOMP=0;
	if(UseKoning==2)
	{
		Insert+=PotentialKoning.GetTString();
		nOMP++;
	}
	else
	{
		if(Potential.ReadFlag)
		{
			Insert+=Potential.GetTString();
			nOMP++;
		}
		else if (UseKoning==1)
		{
			Insert+=PotentialKoning.GetTString();
			nOMP++;
		}
		if(PotentialDisp.ReadFlag)
		{
			Insert+=PotentialDisp.GetTString();
			nOMP++;
		}
	}	
	Insert=TString::Format("%4d%4d%4d\n",Z,A,nOMP)+Insert;
	bool Written=false;
	for(unsigned int i=0;i<ContentOfFile.size();i++)
	{
		if(i==PointToPasteChangedOMP)
		{
			ofs<<Insert;
			Written=true;
		}
		ofs<<ContentOfFile[i]<<"\n";
	}
	if(!Written)
	{
		ofs<<Insert;
		Written=true;
	}
	ofs.close();
}
