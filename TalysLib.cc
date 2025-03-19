#include "TalysLib.hh"
#include <sys/stat.h>
#include <bits/stdc++.h>
#include <cstring>
#include <algorithm>
#include <cctype>
#include <TLine.h>
#include <TText.h>
#include <TList.h>
#include <TKey.h>
#include "source/SpinParity.cc" //contains SpinParity class methods
#include "source/OMP.cc" //contains OpticalModelParameters class methods
#include "source/OMPManager.cc" //contains OMPManager class methods
#include "source/Deformations.cc" //contains LevelDeformation and Deformation classes methods
#include "source/GammaTransitions.cc" //contains GammaTransition class methods
#include "source/LevelProperties.cc" //contains Level class methods
#include "source/NucleiProperties.cc" //contains Nucleus class methods
#include "source/TalysCalculation.cc" //contains TalysCalculation class methods
#include "source/Radionuclide.cc" 
#include "source/TalysFitter.cc" 
#include "source/TalysFitterMT.cc" 
#include "source/AdditionalInformation.cc"
#include "source/TLElement.cc"
#include "source/TLMaterial.cc"
#include "ENDFReader/ENDFLib.cpp"
#include "ENDFReader/EXFOR.cpp"
#include "C4Reader/C4.cpp"
#include "C4Reader/C5.cpp"
#include "C4Reader/Strategy.cpp"
#include "SMatrix/SMatrix.cpp"
#include "SQLiteRW/SQLiteRW.cpp"

GammaTransition* GetBestTransitionFromVector(float Energy, float Tolerancy,vector<Nucleus> &Nuclei)
{
	vector<GammaTransition*> Transitions;
	GammaTransition* BestTransition=0;
	cout<<"GetBestTransitionFromVector started: "<<Energy<<"\n";
	for(unsigned int i=0;i<Nuclei.size();i++)
	{
		for(unsigned int j=0;j<Nuclei[i].Products.size();j++)
		{
			cout<<"Nuclei[i]:"<<Nuclei[i].Name<<":"<<Nuclei[i].Products[j].Name<<" "<<Nuclei[i].Products[j].Levels.size()<<"\n";
		}
		GammaTransition *gm_tmp=Nuclei[i].GetBestTransition(Energy,Tolerancy);
		if(gm_tmp)
		{
			cout<<"GammaTransition E:"<<Energy<<" gm_tmp_energy:"<<gm_tmp->Energy<<" "<<gm_tmp->fLevel->fNucleus->Name<<"\n";
			Transitions.push_back(gm_tmp);
		}
	}
	if(Transitions.size()>0)
	{
		BestTransition=Transitions[0];
	}
	else
	{
		return 0;
	}
	for(unsigned int i=0;i<Transitions.size();i++)
	{
		if(BestTransition&&Transitions[i])
		{
			double BestCS=BestTransition->TalysCrossSection;
			double BestAbundance=BestTransition->fLevel->fNucleus->fMotherNucleus->Abundance;
			double CurrentCS=Transitions[i]->TalysCrossSection;
			double CurrentAbundance=Transitions[i]->fLevel->fNucleus->fMotherNucleus->Abundance;
			//cout<<Energy<<" BestCS:"<<BestCS<<" BestAbundance:"<<BestAbundance<<" CurrentCS:"<<CurrentCS<<" CurrentAbundance:"<<CurrentAbundance<<"\n";
			if(BestCS*BestAbundance<CurrentCS*CurrentAbundance)
			{
				BestTransition=Transitions[i];
			}
		}
	}
	return BestTransition;
}
GammaTransition* GetBestTransitionFromVector(float Energy, float Tolerancy,vector<Nucleus*> Nuclei)
{
	vector<GammaTransition*> Transitions;
	GammaTransition* BestTransition=0;
	cout<<"GetBestTransitionFromVector started: "<<Energy<<"\n";
	for(unsigned int i=0;i<Nuclei.size();i++)
	{
		for(unsigned int j=0;j<Nuclei[i]->Products.size();j++)
		{
			cout<<"Nuclei[i]:"<<Nuclei[i]->Name<<":"<<Nuclei[i]->Products[j].Name<<" "<<Nuclei[i]->Products[j].Levels.size()<<"\n";
		}
		GammaTransition *gm_tmp=Nuclei[i]->GetBestTransition(Energy,Tolerancy);
		if(gm_tmp)
		{
			cout<<"GammaTransition E:"<<Energy<<" gm_tmp_energy:"<<gm_tmp->Energy<<" "<<gm_tmp->fLevel->fNucleus->Name<<"\n";
			Transitions.push_back(gm_tmp);
		}
	}
	if(Transitions.size()>0)
	{
		BestTransition=Transitions[0];
	}
	else
	{
		return 0;
	}
	for(unsigned int i=0;i<Transitions.size();i++)
	{
		if(BestTransition&&Transitions[i])
		{
			double BestCS=BestTransition->TalysCrossSection;
			double BestAbundance=BestTransition->fLevel->fNucleus->fMotherNucleus->Abundance;
			double CurrentCS=Transitions[i]->TalysCrossSection;
			double CurrentAbundance=Transitions[i]->fLevel->fNucleus->fMotherNucleus->Abundance;
			//cout<<Energy<<" BestCS:"<<BestCS<<" BestAbundance:"<<BestAbundance<<" CurrentCS:"<<CurrentCS<<" CurrentAbundance:"<<CurrentAbundance<<"\n";
			if(BestCS*BestAbundance<CurrentCS*CurrentAbundance)
			{
				BestTransition=Transitions[i];
			}
		}
	}
	return BestTransition;
}
int CheckGammaTransitionIntegrality(GammaTransition* gt)
{
	if(gt)
	{
		if(gt->fLevel)
		{
			if(gt->fLevel->fNucleus)
			{
				if(gt->fLevel->fNucleus->fMotherNucleus)
				{
					if(gt->fFinalLevel)
					{
						return 5;
					}
					return 4;
					
				}
				return 3;
			}
			return 2;
		}
		return 1;
	}
	return 0;
}
void ReadNucleiFromRootFile(vector<Nucleus> &Nuclei,TFile *f)
{
	if(!f)
	{
		cout<<"This is ReadNucleiFromRootFile: Cannot read a root file!\n";
		return ;
	}
	TList* list = f->GetListOfKeys();
	if(!list)
	{
		cout<<"This isReadNucleiFromRootFile: List cannot be created\n";
		return ;
	}
	TIter next(list);
	TKey* key=(TKey*)next();
	while(key)
	{
		TObject* obj = key->ReadObj();
		if(obj)
		{
			if((obj->InheritsFrom("NucleusData")))
			{
				Nuclei.emplace_back(*((NucleusData*)obj));
			}
		}
		key=(TKey*)next();
	}
	for(unsigned int i=0;i<Nuclei.size();i++)
	{
		Nuclei[i].AssignPointers();
	}
}
