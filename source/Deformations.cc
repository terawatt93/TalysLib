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
#pragma once

//Методы класса LevelDeformation

bool CheckFieldContent(string s)
{
	for(unsigned int i=0;i<s.length();i++)
	{
		if(s[i]!=' ')
		{
			return true;
		}
	}
	return false;
}
void LevelDeformation::GetFromString(string input)
{
	
	string NumOfLevelS=input.substr(0,4);
	string TypeOfLevelS=input.substr(7,1);
	string NumberOfBandS=input.substr(8,4);
	NumberOfBand=-1; NumberOfLevel=-1; LOfBand=-1; NumberOfPhonons=-1; MagneticNumber=-1;
	//cout<<NumOfLevelS<<"|"<<TypeOfLevelS<<"|"<<NumberOfBandS<<"\n";
	if(input.size()>25)
	{
		string LOfBandS=input.substr(12,4);
		string NumberOfPhononsS=input.substr(16,4);
		string MagneticNumberS=input.substr(20,4);
		stringstream s(input.substr(24,input.size()-24));
		//cout<<NumOfLevelS<<"|"<<TypeOfLevelS<<"|"<<NumberOfBandS<<"|"<<LOfBandS<<"|"<<NumberOfPhononsS<<"|"<<MagneticNumberS<<"|\n";
		while(s)
		{
			float b=0;
			s>>b;
			if(b!=0)
			Beta.push_back(b);
		}
		if(CheckFieldContent(LOfBandS))
		{
			LOfBand=atoi(LOfBandS.c_str());
		}
		if(CheckFieldContent(NumberOfPhononsS))
		{
			NumberOfPhonons=atoi(NumberOfPhononsS.c_str());
		}
		if(CheckFieldContent(MagneticNumberS))
		{
			MagneticNumber=atoi(MagneticNumberS.c_str());
		}
		//cout<<"NBand:"<<NumberOfBand<<" L:"<<LOfBand<<" NF:"<<NumberOfPhonons<<" Mag:"<<MagneticNumber<<" Type:"<<TypeOfLevel<<" ";
		/*for(unsigned int i=0;i<Beta.size();i++)
		{
			cout<<"B"<<i+2<<" "<<Beta[i]<<"\n";
		}*/
	}
	TypeOfLevel=TypeOfLevelS[0];
	NumberOfLevel=atoi(NumOfLevelS.c_str());
	if(CheckFieldContent(NumberOfBandS))
	{
		NumberOfBand=atoi(NumberOfBandS.c_str());
	}
	
	//cout<<NumberOfLevel<<"|"<<TypeOfLevel<<"|"<<NumberOfBand<<"|"<<LOfBand<<"|"<<NumberOfPhonons<<"|"<<MagneticNumber<<"|\n";
}
void LevelDeformation::TurnToBeta(int A)
{
	if(TypeOfDeformation=='D')
	{
		for(unsigned int i=0;i<Beta.size();i++)
		{
			Beta[i]=Beta[i]*pow((float)A,1/3.0);
		}
	}
}

//функции для генерации строк .def файла
TString GenerateMainDefString(int Z, int A, int NLevels, char ColType, char DefUnit)
{
	TString result=TString::Format("%4i%4i%4i   %c   %c",Z,A,NLevels,ColType,DefUnit);
	result.Resize(80);
	return result;
}
TString Add4IValue(int value)//ну реально, их как-то дофига
{
	if(value>=0)
	{
		return TString::Format("%4i",value);
	}
	return "    ";
}
TString GenerateLevelDefString(int LevN, char LevT, int BandN=-1, int BandL=-1, int MagN=-1, int NPhon=-1, vector<float> *Def=0)
{
	TString result=TString::Format("%4i   %c",LevN,LevT);
	result+=(Add4IValue(BandN)+Add4IValue(BandL)+Add4IValue(MagN)+Add4IValue(NPhon));
	if(Def)
	{
		for(unsigned int i=0;i<Def->size();i++)
		{
			result+=TString::Format("%9.5f",Def->at(i));
		}
	}
	result.Resize(80);
	return result;
}
//закончены

TString LevelDeformation::GenerateStringForDefFile()
{
	return GenerateLevelDefString(NumberOfLevel,TypeOfLevel,NumberOfBand,LOfBand,NumberOfPhonons,MagneticNumber,&Beta);
}
LevelDeformationData LevelDeformation::ToLevelDeformationData()
{
	LevelDeformationData result = *((LevelDeformationData*)this);
	result.Beta=Beta;
	return result;
}
//Методы класса Deformation
LevelDeformation::LevelDeformation(LevelDeformationData d)
{
	TypeOfLevel=d.TypeOfLevel; TypeOfDeformation=d.TypeOfDeformation;
	NumberOfBand=d.NumberOfBand; NumberOfLevel=d.NumberOfLevel; LOfBand=d.LOfBand; NumberOfPhonons=d.NumberOfPhonons; MagneticNumber=d.MagneticNumber;
	Beta=d.Beta;
}
void Deformation::SetZA(int _Z,int _A)
{
	Z=_Z; A=_A;
}
void Deformation::SetTypeOfCollectivity( char _Type)
{
	TypeOfCollectivity=_Type;
}
void Deformation::ReadDeformation()
{
	string Filename=GetPathToTalysData()+"/structure/deformation/"+GetNucleusName(Z)+".def";
	ifstream ifs(Filename.c_str());
	if(!ifs.good())
	{
		if(TalysLibManager::Instance().IsEnableWarning())
		cout<<"Warning: deformation file for "<<GetNucleusName(Z)<<" does not exsists!\n";
	}
	string line;
	while(getline(ifs,line))
	{
		int _Z=0, _A=0, Nlevels=0;
		char _TypeOfCollectivity,_TypeOfDeformation;
		sscanf(line.c_str(),"%4d%4d%4d   %c   %c",&_Z,&_A,&Nlevels,&_TypeOfCollectivity,&_TypeOfDeformation);
		if(_Z==Z&&_A==A)
		{
			TypeOfCollectivity=_TypeOfCollectivity; TypeOfDeformation=_TypeOfDeformation;
			PointToPastChangedDeformation=ContentOfFile.size();
			NLevels=Nlevels;
			for(int i=0;i<Nlevels;i++)
			{
				LevelDeformation d(TypeOfDeformation);
				getline(ifs,line);
				d.GetFromString(line);
				LevelDeformations.push_back(d);
			}
		}
		else
		{
			ContentOfFile.push_back(line);
		}
	}
	AssignPointers();
}
void Deformation::WriteDeformation(string filename)
{
	ofstream ofs(filename.c_str());
	//IsDeformationWritten=false;
	for(unsigned int i=0;i<PointToPastChangedDeformation;i++)
	{
		ofs<<ContentOfFile[i]<<"\n";
	}
	NLevels=LevelDeformations.size();
	ofs<<GenerateMainDefString(Z,A,NLevels,TypeOfCollectivity,TypeOfDeformation)<<"\n";
	for(unsigned int i=0;i<LevelDeformations.size();i++)
	{
		ofs<<LevelDeformations[i].GenerateStringForDefFile()<<"\n";
	}
	//IsDeformationWritten=true;
	for(unsigned int i=PointToPastChangedDeformation;i<ContentOfFile.size();i++)
	{
		ofs<<ContentOfFile[i]<<"\n";
	}
	
	ofs.close();
}
void Deformation::Sort()
{
	
	if(LevelDeformations.size()<2)
	{
		return;
	}
	for(unsigned int i=0;i<LevelDeformations.size()-1;i++)
	{
		for (unsigned int j = 0; j <LevelDeformations.size()-i-1; j++)
		{
			//cout<<Levels.size()<<" "<<i<<" "<<j<<"\n";
			if(LevelDeformations[j].NumberOfLevel>LevelDeformations[j+1].NumberOfLevel)
			{
				swap(LevelDeformations[j],LevelDeformations[j+1]);
			}
		}
	}
	
	for(unsigned int i=0;i<LevelDeformations.size();i++)
	{
		if(LevelDeformations[i].fLevel!=0)
		{
			LevelDeformations[i].fLevel->deformation=&LevelDeformations[i];
		}
	}
}
void Deformation::SetDeformation(Level *l,char LevT, int BandN, int BandL, int MagN, int NPhon, vector<float> *Def)//для совместимости с root6.14
{
	LevelDeformation *ld=0;
	if(l==0)
	{
		cout<<"Deformation::SetDeformation(...) error: level not defined. return \n";
		return;
	}
	int LevN=l->Number;
	if(kUseLevelJP==BandL)
	{
		BandL=l->TalysJP.J;
	}
	for(unsigned int i=0;i<LevelDeformations.size();i++)
	{
		if(LevelDeformations[i].NumberOfLevel==LevN)
		{
			ld=&LevelDeformations[i];
			break;
		}
	}
	if(ld==0)
	{
		LevelDeformations.resize(LevelDeformations.size()+1);
		ld=&LevelDeformations[LevelDeformations.size()-1];
	}
	ld->NumberOfBand=BandN;
	ld->TypeOfLevel=LevT;
	ld->NumberOfLevel=LevN;
	ld->LOfBand=BandL;
	ld->NumberOfPhonons=NPhon;
	ld->MagneticNumber=MagN;
	
	if(Def!=0)
	{
		ld->Beta.resize(0);
		for(unsigned int i=0;i<Def->size(); i++)
		{
			ld->Beta.push_back(Def->at(i));
		}
	}
	ld->fLevel=l;
	l->deformation=ld;
	Sort();
}
vector<float> Deformation::GetDeformationBeta(Level *l)
{
	vector<float> result;
	if(l==0)
	{
		cout<<"Deformation::GetDeformationBeta(...) error: level is not defined. Return empty beta2 vector!\n";
		return result;
	}
	if(l->deformation==0)
	{
		cout<<"Deformation::GetDeformationBeta(...) error: level deformation is not defined. Return empty vector! \n";
		return result;
	}
	return l->deformation->Beta;
}
void Deformation::AssignPointers()
{
	for(unsigned int i=0;i<LevelDeformations.size();i++)
	{
		LevelDeformations[i].fDeformation=this;
	}
}
DeformationData Deformation::ToDeformationData()
{
	DeformationData result=*((DeformationData*)this);
	for(unsigned int i=0;i<LevelDeformations.size();i++)
	{
		result.LevelDeformationsData.push_back(LevelDeformations[i].ToLevelDeformationData());
	}
	return result;
}
Deformation::Deformation(DeformationData d)
{
	A=d.A; Z=d.Z; NLevels=d.NLevels;
	TypeOfCollectivity=d.TypeOfCollectivity; TypeOfDeformation=d.TypeOfDeformation;
	ContentOfFile=d.ContentOfFile;
	for(unsigned int i=0;i<d.LevelDeformationsData.size();i++)
	{
		LevelDeformations.emplace_back(d.LevelDeformationsData[i]);
	}
	AssignPointers();
}
void Deformation::SetDefaultDeformationType(char _Type)
{
	for(unsigned int i=0;i<LevelDeformations.size();i++)
	{
		LevelDeformations[i].TypeOfLevel=_Type;
	}
}
