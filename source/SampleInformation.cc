#include "../TalysLib.hh"
#include <sys/stat.h>
#include "TalysLibManager.cc"
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
#include "OMP.cc"
#include "Deformations.cc"
#include "GammaTransitions.cc"
#include "LevelProperties.cc"
#include "NucleiProperties.cc"
#include "TalysCalculation.cc"

#pragma once

void SampleInformation::GenerateNucleiListFromSubstance()
{
	vector<Nucleus> NucleiTmp;
	GenerateListOfElements(Substance,Elements,Quantities);
	for(unsigned int i=0;i<Elements.size();i++)
	{
		vector<double> Abundances;
		vector<int> A_values;
		GetAbundance(Elements[i],A_values,Abundances);
		for(unsigned int j=0;j<A_values.size();j++)
		{
			NucleiTmp.emplace_back(to_string(A_values[j])+Elements[i]);
			NucleiTmp[NucleiTmp.size()-1].GenerateProducts();
		}
	}
	Nuclei.resize(0);
	for(unsigned int i=0;i<NucleiTmp.size();i++)
	{
		Nuclei.emplace_back(NucleiTmp[i].ToNucleusData());
	}
}

void SampleInformation::SetSubstance(string Substance)
{
	this->Substance=Substance;
	GenerateNucleiListFromSubstance();
}

SampleInformation::SampleInformation(string Substance, double Density, double SizeX, double SizeY, double SizeZ, double PositionX, double PositionY, double PositionZ)
{
	this->Substance=Substance;
	this->Density=Density;
	this->SizeX=SizeX;
	this->SizeY=SizeY;
	this->SizeZ=SizeZ;
	this->PositionX=PositionX;
	this->PositionY=PositionY;
	this->PositionZ=PositionZ;
	GenerateNucleiListFromSubstance();
}
void SampleInformation::SetListOfNucleiInMedia(string List)
{
	NucleiInMedia.resize(0);
	stringstream s(List);
	vector<string> NuclTmp;
	vector<Nucleus> NucleiTmp;
	while(s)
	{
		string StrTmp;
		s>>StrTmp;
		if(StrTmp.size()>0)
		{
			if((StrTmp[0]>='1')&&(StrTmp[0]<='9'))
			{
				NucleiTmp.emplace_back(StrTmp);
				NucleiTmp[NucleiTmp.size()-1].Abundance=GetAbundance(StrTmp);
			}
			else
			{
				vector<double> Abundances;
				vector<int> A_values;
				GetAbundance(StrTmp,A_values,Abundances);
				for(unsigned int i=0;i<A_values.size();i++)
				{
					NucleiTmp.emplace_back(to_string(A_values[i])+StrTmp);
					NucleiTmp[NucleiTmp.size()-1].Abundance=Abundances[i];
				}
			}
		}
	}
	for(unsigned int i=0;i<NucleiTmp.size();i++)
	{
		NucleiTmp[i].GenerateProducts();
		NucleiInMedia.push_back(NucleiTmp[i].ToNucleusData());
	}
}
void SampleInformation::SetListOfNuclei(string List)
{
	Nuclei.resize(0);
	stringstream s(List);
	vector<string> NuclTmp;
	vector<Nucleus> NucleiTmp;
	while(s)
	{
		string StrTmp;
		s>>StrTmp;
		if(StrTmp.size()>0)
		{
			if((StrTmp[0]>='1')&&(StrTmp[0]<='9'))
			{
				NucleiTmp.emplace_back(StrTmp);
				NucleiTmp[NucleiTmp.size()-1].Abundance=GetAbundance(StrTmp);
			}
			else
			{
				vector<double> Abundances;
				vector<int> A_values;
				GetAbundance(StrTmp,A_values,Abundances);
				for(unsigned int i=0;i<A_values.size();i++)
				{
					NucleiTmp.emplace_back(to_string(A_values[i])+StrTmp);
					NucleiTmp[NucleiTmp.size()-1].Abundance=Abundances[i];
				}
			}
		}
	}
	for(unsigned int i=0;i<NucleiTmp.size();i++)
	{
		NucleiTmp[i].GenerateProducts();
		Nuclei.push_back(NucleiTmp[i].ToNucleusData());
	}
}
void SampleInformation::SetListOfNuclei(vector<Nucleus> &Nuclei)
{
	this->Nuclei.resize(0);
	for(unsigned int i=0;i<Nuclei.size();i++)
	{
		this->Nuclei.push_back(Nuclei[i].ToNucleusData());
	}
}
void SampleInformation::SetListOfNucleiInMedia(vector<Nucleus> &Nuclei)
{
	this->NucleiInMedia.resize(0);
	for(unsigned int i=0;i<Nuclei.size();i++)
	{
		this->NucleiInMedia.push_back(Nuclei[i].ToNucleusData());
	}
}
void SampleInformation::SetPosition(double PositionX, double PositionY, double PositionZ)
{
	this->PositionX=PositionX;
	this->PositionY=PositionY;
	this->PositionZ=PositionZ;
}
void SampleInformation::SetSizes(double SizeX, double SizeY, double SizeZ)
{
	this->SizeX=SizeX;
	this->SizeY=SizeY;
	this->SizeZ=SizeZ;
}
void SampleInformation::SetDensity(double Density)
{
	this->Density=Density;
}
vector<NucleusData> SampleInformation::GetListOfNuclei()
{
	return Nuclei;
}
vector<NucleusData> SampleInformation::GetListOfNucleiInMedia()
{
	return NucleiInMedia;
}
string SampleInformation::GetSubstance()
{
	return Substance;
}
vector<string> SampleInformation::GetElements()
{
	return Elements;
}
vector<string> SampleInformation::GetElementsInMedia()
{
	return ElementsInMedia;
}
vector<int> SampleInformation::GetQuantities()
{
	return Quantities;
}
void SampleInformation::SaveToRootFile(TFile *f)
{
	if(f)
	{
		f->WriteTObject(this);
	}
	else
	{
		cout<<"This is SampleInformation::SaveToRootFile: file cannot be opened\n";
	}
}
void SampleInformation::ReadFromRootFile(TFile *f, string Name)
{
	if(f)
	{
		TList* list = f->GetListOfKeys();
		if(!list)
		{
			cout<<"List cannot be created\n";
			return ;
		}
		TIter next(list);
		TKey* key;
		while(key = (TKey*)next())
		{
			TObject* obj = key->ReadObj();
			if(obj)
			{
				if(obj->InheritsFrom("SampleInformation"))
				{
					if((string(obj->GetName())==Name)||(Name==""))
					*this=*(SampleInformation*)obj;
				}
			}
		}
		f->Close();
	}
	else
	{
		cout<<"This is SampleInformation::SaveToRootFile: file cannot be opened\n";
	}
}
void SampleInformation::SetName(string Name)
{
	this->Name=Name;
}
void SampleInformation::SetSampleType(string Type)
{
	SampleType=Type;
}
const char* SampleInformation::GetName()
{
	return Name.c_str();
}
void SampleInformation::ReadFromTXTFile(string filename)
{
	ifstream ifs(filename.c_str());
	string line;
	while(getline(ifs,line))
	{
		string tmp;
		stringstream s(line);
		s>>tmp;
		if(tmp=="Substance:")
		{
			s>>Substance;
			GenerateNucleiListFromSubstance();
		}
		if(tmp=="Sizes:")
		{
			s>>SizeX>>SizeY>>SizeZ;
		}
		if(tmp=="Density:")
		{
			s>>Density;
			Density=Density/1000;
		}
		if(tmp=="Container:")
		{
			s>>SampleType;
		}
	}
}
double SampleInformation::GetConcentration(string Nucl)
{
	if(Nucl=="")
	{
		double Mass;
		for(unsigned int i=0;i<Elements.size();i++)
		{
			Mass+=GetAverageMass(Elements[i])*Quantities[i];
		}
		return Density/Mass;
	}
	else
	{
		string NuclSymbol;
		for(unsigned int i=0;i<Nucl.size();i++)
		{
			if((Nucl[i]>='A')&&(Nucl[i]<='z'))
			{
				NuclSymbol+=Nucl[i];
			}
		}
		for(unsigned int i=0;i<Elements.size();i++)
		{
			if(NuclSymbol==Elements[i])
			{
				return GetConcentration()*Quantities[i]*GetAbundance(Nucl);
			}
		}
	}
	return 0;
}
double SampleInformation::GetDensity()
{
	return Density;
}
string SampleInformation::GetSampleType()
{
	return SampleType;
}
void SampleInformation::GetSizes(double &SizeX, double &SizeY, double &SizeZ)
{
	SizeX=this->SizeX; SizeY=this->SizeY; SizeZ=this->SizeZ;
}
void SampleInformation::GetPosition(double &PositionX, double &PositionY, double &PositionZ)
{
	PositionX=this->PositionX; PositionY=this->PositionY; PositionZ=this->PositionZ;
}
void SampleInformation::ReadFromRootFile(string FileName,string Name)
{
	TFile *f=new TFile(FileName.c_str());
	if(!f)
	{
		cout<<"This is SampleInformation::ReadFromRootFile(string FileName): file "<<FileName<<" cannot be opened!\n";
		return;
	}
	ReadFromRootFile(f,Name);
	f->Close();
	
}
