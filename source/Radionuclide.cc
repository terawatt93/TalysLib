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
#include <TVector3.h>
#include <string>

#pragma once

using namespace std;

vector<string> SplitToSubstr(string line)
{
	vector<string> result;
	string tmp;
	for(unsigned int i=0;i<line.size();i++)
	{
		if(line[i]==';')
		{
			TString tstr(tmp.c_str());
			tstr.ReplaceAll(" ","");
			result.push_back(tstr.Data());
			tmp.resize(0);
		}
		else
		{
			tmp+=line[i];
		}
	}
	TString tstr(tmp.c_str());
	tstr.ReplaceAll(" ","");
	result.push_back(tstr.Data());
	return result;
}

string ConvertNuclName(string Name)
{
	int Z=0,A=0;
	GetAZ(Name,Z,A);
	return to_string(A)+GetNucleusName(Z);
}

void Radionuclide::AssignPointers()
{
	Nucleus::AssignPointers();
	for(unsigned int i=0;i<Products.size();i++)
	{
		Products[i].fMotherNucleus=this;
		Products[i].AssignPointers();
	}
}
Radionuclide* Radionuclide::FindProductByName(string _Name)
{
	for(unsigned int i=0;i<Products.size();i++)
	{
		if(Products[i].Name==_Name)
		{
			return &(Products[i]);
		}
	}
	Radionuclide* result=0;
	for(unsigned int i=0;i<Products.size();i++)
	{
		result=Products[i].FindProductByName(_Name);
		if(result)
		return result;
	}
	return 0;
}
vector<GammaTransition*> Radionuclide::GetGammaTransitions(double E_thr,double Int_thr)
{
	vector<GammaTransition*> result;
	for(unsigned int i=0;i<Levels.size();i++)
	{
		for(unsigned int j=0;j<Levels[i].Gammas.size();j++)
		{
			GammaTransition* gt=&(Levels[i].Gammas[j]);
			if(gt->Energy>E_thr)
			{
				if((gt->GetRelativeIntensity()>Int_thr)&&(gt->Intensity>0))
				{
					result.push_back(gt);
				}
			}
		}
	}
	for(unsigned int i=0;i<Products.size();i++)
	{
		vector<GammaTransition*> result_tmp=Products[i].GetGammaTransitions(E_thr,Int_thr);
		result.insert(result.end(), result_tmp.begin(), result_tmp.end());
	}
	if(!fMotherNucleus)
	{
		for(unsigned int i=0;i<result.size()-1;i++)
		{
			for (unsigned int j = 0; j <result.size()-i-1; j++)
			{
				//cout<<Levels.size()<<" "<<i<<" "<<j<<"\n";
				if(result[j]->Energy>result[j+1]->Energy)
				{
					swap(result[j],result[j+1]);
				}
			}
		}
	}
	
	
	return result;
}
void Radionuclide::ReadGRDatabase()
{
	if(IsRead)
	{
		return;
	}
	string DBFileName=string(getenv("TALYSLIBDIR"))+"/GRDataBase/"+GetNucleusName(Z)+"-"+to_string(A)+".lara.txt";
	ifstream ifs(DBFileName);
	string line;
	while(getline(ifs,line))
	{
		vector<string> Substr=SplitToSubstr(line);
		if(line.find("Daughter(s)")!=string::npos)
		{
			vector<string> DautherNames, Decays;
			vector<double> Branchings;
			if(Substr.size()>1)
			{
				int NumberOfProducts=(double(Substr.size()-1)/3);
				int FieldIterator=1;
				for(int i=0;i<NumberOfProducts;i++)
				{
					Radionuclide Nucl(ConvertNuclName(Substr[FieldIterator+1]));
					Nucl.BranchRatio=atof(Substr[FieldIterator+2].c_str())/100;
					Nucl.Reaction=Substr[FieldIterator];
					Products.push_back(Nucl);
					FieldIterator+=3;
				}
			}
			for(unsigned int i=0;i<Products.size();i++)
			{
				Products[i].ReadGRDatabase();
			}
		}
		if(line.find("Decay constant")!=string::npos)
		{
			DecayConstant=atof(Substr[1].c_str());
		}
		if(line.size()>30)
		{
			if((line[0]>='0')&&(line[0]<='9')&&(Substr.size()>5))
			{
				double E_gamma=atof(Substr[0].c_str()),Intensity=atof(Substr[2].c_str())/100;
				string Origin=Substr[4];
				int LevNumberI=atoi(Substr[6].c_str());
				int LevNumberF=atoi(Substr[7].c_str());
				GammaTransition *gt;
				
				Radionuclide *Nucl=FindProductByName(ConvertNuclName(Substr[5]));
				gt=GetBestTransition(E_gamma,0.5);
				if((Nucl)&&(E_gamma>0))
				{
					
					if(gt&&(LevNumberI>=0)&&(LevNumberF>=0))
					{
						//cout<<"LevNumberF, LevNumberI:"<<LevNumberF<<" "<<LevNumberI<<"\n";
						int NLevels=Nucl->Levels.size();
						if((LevNumberI<NLevels)&&(((LevNumberF<NLevels)&&(LevNumberI>LevNumberF))||((LevNumberF==0)&&(LevNumberI==0))))
						{
							
							gt->Energy=E_gamma;
							gt->Origin=Origin;
							gt->Intensity=Intensity;
							//Level *Li=&(Nucl->Levels[LevNumberI]);
							//Level *Lf=&(Nucl->Levels[LevNumberF]);
							//gt->fLevel=Li;
							//gt->fFinalLevel=Lf;
							//Li->Gammas.push_back(gt);
						}
					}
					else
					{
						Nucl->Levels[0].Gammas.emplace_back();
						gt=&(Nucl->Levels[0].Gammas[Nucl->Levels[0].Gammas.size()-1]);
						gt->fLevel=&(Nucl->Levels[0]);
						gt->fFinalLevel=&(Nucl->Levels[0]);
						gt->Energy=E_gamma;
						gt->Origin=Origin;
						gt->Intensity=Intensity;
					}
				}
			}
		}
	}
	ifs.close();
	AssignPointers();
	for(unsigned int i=0;i<Products.size();i++)
	{
		Products[i].fMotherNucleus=this;
	}
	IsRead=true;
}
