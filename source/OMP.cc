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
	EvalPotential();
	TString result="    V_v    r_v    a_v    Wv    rw    aw    Vd    rvd    avd    Wd    rwd    awd    Vso    rvso    avso    Wso    rwso    awso\n";
	result+=TString::Format("%4.3f %4.3f %4.3f %4.3f %4.3f %4.3f %4.3f %4.3f %4.3f %4.3f %4.3f %4.3f %4.3f %4.3f %4.3f %4.3f %4.3f %4.3f",Vv, Rv, Av, Wv, Rv, Av, 0.0, Rd, Ad, Wd, Rd, Ad, Vso, Rso, Aso, Wso, Rso, Aso);
	result+="\n    v1    v2    v3    v4    w1    w2    d1    d2    d3    vso1    vso2    wso1    wso2\n";
	result+=TString::Format("%4.3f %4.3f %4.3f %4.3f %4.3f %4.3f %4.3f %4.3f %4.3f %4.3f %4.3f %4.3f %4.3f",v1, v2, v3, v4, w1, w2, d1, d2, d3, vso1, vso2, wso1, wso2);
	return result;
	
}
void OMPStorage::SetVv(double value)
{
	if(!SaveEnergyDependence)
	{
		v1=value;
		v2=0; v3=0; v4=0;
	}
	else
	{
		v1=v1*value/GetVv();
	}
}
void OMPStorage::SetWv(double value)
{
	if(!SaveEnergyDependence)
	{
		w1=value;
		w2=0;
	}
	else
	{
		w1=w1*value/GetWv();
	}
}
void OMPStorage::SetRv(double value)
{
	Rv=value;
}
void OMPStorage::SetAv(double value)
{
	Av=value;
}
void OMPStorage::SetWd(double value)
{
	if(!SaveEnergyDependence)
	{
		d1=value;
		d2=0; d3=0;
	}
	else
	{
		d1=d1*value/GetWd();
	}
}
void OMPStorage::SetRd(double value)
{
	Rd=value;
}
void OMPStorage::SetAd(double value)
{
	Ad=value;
}
void OMPStorage::SetVso(double value)
{
	if(!SaveEnergyDependence)
	{
		vso1=value;
		vso2=0;
	}
	else
	{
		vso1=vso1*value/GetVso();
	}
}
void OMPStorage::SetWso(double value)
{
	if(!SaveEnergyDependence)
	{
		wso1=value;
		wso2=0;
	}
	else
	{
		wso1=wso1*value/GetWso();
	}
}
void OMPStorage::SetRso(double value)
{
	Rso=value;
}
void OMPStorage::SetAso(double value)
{
	Aso=value;
}
void OMPStorage::SetRc(double value)
{
	Rc=value;
}
double OMPStorage::GetVv()
{
	double E=Nuclide->ProjectileEnergy;
	return v1*(1 - v2*(E - Ef) + v3*pow((E - Ef),2) - v4*pow((E - Ef),3))+Vc*v1*(v2-2*v3*(E-Ef)+3*v4*pow(E-Ef,2));
}
double OMPStorage::GetWv()
{
	double E=Nuclide->ProjectileEnergy;
	return w1*pow((E-Ef),2)/(pow(E-Ef,2)+pow(w2,2));
}
double OMPStorage::GetWd()
{
	double E=Nuclide->ProjectileEnergy;
	return d1*pow(E-Ef,2)/(pow(E-Ef,2)+pow(d3,2))*exp(-d2*(E-Ef));
}
double OMPStorage::GetVso()
{
	double E=Nuclide->ProjectileEnergy;
	return vso1*exp(-vso2*(E-Ef));
}
double OMPStorage::GetWso()
{
	double E=Nuclide->ProjectileEnergy;
	return wso1*pow(E-Ef,2)/(pow(E-Ef,2)+pow(wso2,2));
}

OMPStorage::OMPStorage(OMPStorageData d)
{
	OMPStorageData* dd;
	*this=*((OMPStorage*)dd);
}
OMPStorageData OMPStorage::ToOMPStorageData()
{
		return *(OMPStorageData*)this;
}

void OMPStorage::GenerateOMPGraph()
{
	TF1 WoodsSaxon("WoodsSaxon","1/(1+exp((x-[0])/[1]))",0,10);
	TF1 WoodsSaxonDiff("WoodsSaxonDiff","-((1+exp((x-[0])/[1]))^-2)*exp((x-[0])/[1])/[1]",0,10);
	GrVv.SetName("RealPart");
	GrWv.SetName("ImPart");
	GrVso.SetName("RealSOPart");
	GrWso.SetName("ImSOPart");
	GrVv.SetTitle("Real part; r,fm; V,MeV");
	GrVv.SetLineColor(2);
	GrWv.SetLineColor(4);
	GrVso.SetLineColor(6);
	GrWso.SetLineColor(7);
	GrWv.SetTitle("Imaginary part;r,fm; V,MeV");
	GrVso.SetTitle("Real SO part;r,fm; V,MeV");
	GrWso.SetTitle("Imaginary SO part;r,fm; V,MeV");
	double r=0.01;
	for(unsigned int i=0;i<100;i++)
	{
		
		WoodsSaxon.SetParameters(Rv,Av);
		WoodsSaxonDiff.SetParameters(Rd,Ad);
		GrVv.SetPoint(i,r,-Vv*WoodsSaxon.Eval(r)+Vc);
		GrWv.SetPoint(i,r,-Wv*WoodsSaxon.Eval(r)-4*Ad*Wd*WoodsSaxonDiff.Eval(r));
		WoodsSaxonDiff.SetParameters(Rso,Aso);
		GrVso.SetPoint(i,r,Vso*1.991*WoodsSaxonDiff.Eval(r)/r);
		GrWso.SetPoint(i,r,Wso*1.991*WoodsSaxonDiff.Eval(r)/r);
		r+=0.1;
	}
}
void OMPStorage::Draw(string option)
{
	if(!gPad)
	{
		TCanvas *cc1=new TCanvas();
	}
	/*if(!gPad->GetCanvas())
	{
		TCanvas *cc1=new TCanvas();
	}*/
	if((GrVv.GetN()==0)||(option=="new"))
	{
		GenerateOMPGraph();
	}
	TCanvas *cc1=gPad->GetCanvas();	
	cc1->Clear();
	cc1->Divide(2,1);
	cc1->cd(1);
	GrVv.Draw("al");
	GrVv.SetMinimum(-60);
	GrVv.SetMaximum(10);
	GrWv.Draw("l");
	cc1->cd(2);
	GrVso.Draw("al");
	GrVso.SetMinimum(-60);
	GrVso.SetMaximum(10);
	GrWso.Draw("l");
} 

void OpticalModelParameters::SetVv(double value)
{
	if(DefaultOMP!=0)
	{
		DefaultOMP->SetVv(value);
	}
	else
	{
		cout<<"OpticalModelParameters::SetVv() error: DefaultOMP does not set!\n";
	}
}
void OpticalModelParameters::SetWv(double value)
{
	if(DefaultOMP!=0)
	{
		DefaultOMP->SetWv(value);
	}
	else
	{
		cout<<"OpticalModelParameters::SetWv() error: DefaultOMP does not set!\n";
	}
}
void OpticalModelParameters::SetRv(double value)
{
	if(DefaultOMP!=0)
	{
		DefaultOMP->SetRv(value);
	}
	else
	{
		cout<<"OpticalModelParameters::SetRv() error: DefaultOMP does not set!\n";
	}

}
void OpticalModelParameters::SetAv(double value)
{
	if(DefaultOMP!=0)
	{
		DefaultOMP->SetAv(value);
	}
	else
	{
		cout<<"OpticalModelParameters::SetAv() error: DefaultOMP does not set!\n";
	}

}

void OpticalModelParameters::SetRd(double value)
{
	if(DefaultOMP!=0)
	{
		DefaultOMP->SetRd(value);
	}
	else
	{
		cout<<"OpticalModelParameters::SetRd() error: DefaultOMP does not set!\n";
	}

}
void OpticalModelParameters::SetAd(double value)
{
	if(DefaultOMP!=0)
	{
		DefaultOMP->SetAd(value);
	}
	else
	{
		cout<<"OpticalModelParameters::SetAd() error: DefaultOMP does not set!\n";
	}

}
void OpticalModelParameters::SetRso(double value)
{
	if(DefaultOMP!=0)
	{
		DefaultOMP->SetRso(value);
	}
	else
	{
		cout<<"OpticalModelParameters::SetRso() error: DefaultOMP does not set!\n";
	}

}
void OpticalModelParameters::SetAso(double value)
{
	if(DefaultOMP!=0)
	{
		DefaultOMP->SetAso(value);
	}
	else
	{
		cout<<"OpticalModelParameters::SetAso() error: DefaultOMP does not set!\n";
	}

}

void OpticalModelParameters::SetWd(double value)
{
	if(DefaultOMP!=0)
	{
		DefaultOMP->SetWd(value);
	}
	else
	{
		cout<<"OpticalModelParameters::SetWd() error: DefaultOMP does not set!\n";
	}

}
void OpticalModelParameters::SetVso(double value)
{
	if(DefaultOMP!=0)
	{
		DefaultOMP->SetVso(value);
	}
	else
	{
		cout<<"OpticalModelParameters::SetVso() error: DefaultOMP does not set!\n";
	}
}
void OpticalModelParameters::SetWso(double value)
{
	if(DefaultOMP!=0)
	{
		DefaultOMP->SetWso(value);
	}
	else
	{
		cout<<"OpticalModelParameters::SetWso() error: DefaultOMP does not set!\n";
	}
}
/*void OpticalModelParameters::SetRd(double value)
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

double OpticalModelParameters::GetVv()
{
	if(DefaultOMP!=0)
	{
		return DefaultOMP->GetVv();
	}
	else
	{
		cout<<"OpticalModelParameters::GetVv() error: DefaultOMP does not set! -1 returned\n";
	}
}
double OpticalModelParameters::GetWv()
{
	if(DefaultOMP!=0)
	{
		return DefaultOMP->GetWv();
	}
	else
	{
		cout<<"OpticalModelParameters::GetWv() error: DefaultOMP does not set! -1 returned\n";
	}
}
double OpticalModelParameters::GetWd()
{
	if(DefaultOMP!=0)
	{
		return DefaultOMP->GetWd();
	}
	else
	{
		cout<<"OpticalModelParameters::GetWd() error: DefaultOMP does not set! -1 returned\n";
	}
}
double OpticalModelParameters::GetVso()
{
	if(DefaultOMP!=0)
	{
		return DefaultOMP->GetVso();
	}
	else
	{
		cout<<"OpticalModelParameters::GetVso() error: DefaultOMP does not set! -1 returned\n";
	}
}
double OpticalModelParameters::GetWso()
{
	if(DefaultOMP!=0)
	{
		return DefaultOMP->GetWso();
	}
	else
	{
		cout<<"OpticalModelParameters::GetWso() error: DefaultOMP does not set! -1 returned\n";
	}
}
double OMPStorage::GetRv()
{
	return Rv;
}
double OMPStorage::GetAv()
{
	return Av;
}
double OMPStorage::GetRd()
{
	return Rd;
}
double OMPStorage::GetAd()
{
	return Ad;
}
double OMPStorage::GetRso()
{
	return Rso;
}
double OMPStorage::GetAso()
{
	return Aso;
}

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
	if(Projectile=="p")
	Vc=1.73*Z*pow(A,-1.0/3)/Rc;
}
void OMPStorage::Read(string &Buffer)
{
	stringstream s(Buffer);
	s>>Type>>Ef>>Rc;
	s>>Rv>>Av>>v1>>v2>>v3>>w1>>w2;
	s>>Rd>>Ad>>d1>>d2>>d3;
	s>>Rso>>Aso>>vso1>>vso2>>wso1>>wso2;
	EvalPotential();
	ReadFlag=true;
}
OpticalModelParameters::OpticalModelParameters()
{
	Potential.Type=1;
	Potential.HRPotentialType="PredefSTD";
	PotentialDisp.Type=2;
	PotentialDisp.HRPotentialType="PredefDISP";
	PotentialKoning.Type=3;
	PotentialKoning.HRPotentialType="Koning";
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

double OpticalModelParameters::GetRv()
{
	if(DefaultOMP!=0)
	{
		return DefaultOMP->GetRv();
	}
	else
	{
		cout<<"OpticalModelParameters::GetRv() error: DefaultOMP does not set! -1 returned\n";
	}
}
double OpticalModelParameters::GetAv()
{
	if(DefaultOMP!=0)
	{
		return DefaultOMP->GetAv();
	}
	else
	{
		cout<<"OpticalModelParameters::GetAv() error: DefaultOMP does not set! -1 returned\n";
	}
}
double OpticalModelParameters::GetRd()
{
	if(DefaultOMP!=0)
	{
		return DefaultOMP->GetRd();
	}
	else
	{
		cout<<"OpticalModelParameters::GetRd() error: DefaultOMP does not set! -1 returned\n";
	}
}
double OpticalModelParameters::GetAd()
{
	if(DefaultOMP!=0)
	{
		return DefaultOMP->GetAd();
	}
	else
	{
		cout<<"OpticalModelParameters::GetAd() error: DefaultOMP does not set! -1 returned\n";
	}
}
double OpticalModelParameters::GetRso()
{
	if(DefaultOMP!=0)
	{
		return DefaultOMP->GetRso();
	}
	else
	{
		cout<<"OpticalModelParameters::GetRso() error: DefaultOMP does not set! -1 returned\n";
	}
}
double OpticalModelParameters::GetAso()
{
	if(DefaultOMP!=0)
	{
		return DefaultOMP->GetAso();
	}
	else
	{
		cout<<"OpticalModelParameters::GetAso() error: DefaultOMP does not set! -1 returned\n";
	}
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
void OpticalModelParameters::SetDefaultOMP(int option)
{
	if(option==2)
	{
		DefaultOMP=&PotentialKoning;
	}
	else
	{
		if((Potential.ReadFlag)&&(option==1))
		{
			DefaultOMP=&Potential;
		}
		else if (option==1)
		{
			DefaultOMP=&PotentialKoning;
		}
	}
}
void OpticalModelParameters::AssignPointers(Nucleus *N)
{
	if(N!=0)
	{
		Nuclide=N;
	}
	Potential.Nuclide=Nuclide;
	PotentialKoning.Nuclide=Nuclide;
	PotentialDisp.Nuclide=Nuclide;
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
	bool CouldBeWritten=false;
	if(UseKoning==2)
	{
		Insert+=PotentialKoning.GetTString();
		nOMP++;
		CouldBeWritten=true;
		DefaultOMP=&PotentialKoning;
	}
	else
	{
		if((Potential.ReadFlag)&&(UseKoning==1))
		{
			Insert+=Potential.GetTString();
			nOMP++;
			CouldBeWritten=true;
			DefaultOMP=&Potential;
		}
		else if (UseKoning==1)
		{
			Insert+=PotentialKoning.GetTString();
			nOMP++;
			CouldBeWritten=true;
			DefaultOMP=&PotentialKoning;
		}
		else if(UseKoning==kUseDefaultOMP)
		{
			if(DefaultOMP!=0)
			{
				Insert+=DefaultOMP->GetTString();
				nOMP++;
				CouldBeWritten=true;
			}
			else
			{
				cout<<" This is OpticalModelParameters::SaveOMP() error! Cannot use DefaultOMP because pointer is invalid\n";
				return;
			}
		}
		/*if(PotentialDisp.ReadFlag)
		{
			Insert+=PotentialDisp.GetTString();
			nOMP++;
			CouldBeWritten=true;
		}*/
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
	if(!Written&&CouldBeWritten)
	{
		ofs<<Insert;
		Written=true;
	}
	else
	{
		cout<<"This is OpticalModelParameters::SaveOMP error: cannot write OMP because potential with option "<<UseKoning<<" is empty!\n";
	}
	ofs.close();
}
OpticalModelParameters::OpticalModelParameters(OpticalModelParametersData d)
{
	nOMP=d.nOMP;
	NormalisationMode=d.NormalisationMode;
	Read=d.Read;
	JLM_flag=d.JLM_flag;
	goriely=d.goriely;
	hilaire=d.hilaire;
	Koning=d.Koning;
	Dispersive=d.Dispersive;
	Projectile=d.Projectile;
	ContentOfFile=d.ContentOfFile;
	A=d.A; Z=d.Z; N=d.N;
	Potential=OMPStorage(d.PotentialData);
	PotentialKoning=OMPStorage(d.PotentialKoningData);
	PotentialDisp=OMPStorage(d.PotentialDispData);
}
void OpticalModelParameters::SaveEnergyDependence(bool State)
{
	Potential.SaveEnergyDependence=State; PotentialDisp.SaveEnergyDependence=State; PotentialKoning.SaveEnergyDependence=State;
}
OpticalModelParametersData OpticalModelParameters::ToOpticalModelParametersData()
{
	OpticalModelParametersData result=*(OpticalModelParametersData*)this;
	result.PotentialData=Potential.ToOMPStorageData();
	result.PotentialKoningData=PotentialKoning.ToOMPStorageData();
	result.PotentialDispData=PotentialDisp.ToOMPStorageData();
	return result;
}
