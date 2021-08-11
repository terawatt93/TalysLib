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
#include "TXlswriter.cpp"
#include <algorithm>
#pragma once

double ConvertAngleToLab(double angle, double ma, double Ta, double mA, double mb, double mB, double Tb)
{
	double P_mv_b=mb/(mb+mB)*sqrt(2*ma*Ta);
	double P_b_CM=sqrt(2*mb*Tb);
	TVector3 P_b_CM_v(P_b_CM*cos(angle/180*3.1416),P_b_CM*sin(angle/180*3.1416),0);
	TVector3 P_mv_b_v(P_mv_b,0,0);
	TVector3 v_lab=P_b_CM_v+P_mv_b_v;
	return v_lab.Angle(P_mv_b_v)*180/3.1416;
}

void Nucleus::GetFromNucleusData(NucleusData ND)
{
	Name=ND.Name; Reaction=ND.Reaction;
	A=ND.A; Z=ND.Z;
	Abundance=ND.Abundance;
	OMPN=OpticalModelParameters(ND.OMPNData);
	OMPP=OpticalModelParameters(ND.OMPPData);
	OMPN.Nuclide=this;
	OMPP.Nuclide=this;
	OMPoptionN=ND.OMPoptionN; OMPoptionP=ND.OMPoptionN;
	TOTGamProd=ND.TOTGamProd; TOTNProd=ND.TOTNProd; TOTPProd=ND.TOTPProd; TOTDProd=ND.TOTDProd; TOTAProd=ND.TOTAProd;
	TotElastic=ND.TotElastic; CompoundElastic=ND.CompoundElastic; DirectElastic=ND.DirectElastic; TotInelastic=ND.TotInelastic;
	CompoundInelastic=ND.CompoundInelastic; DirectInelastic=ND.DirectInelastic; TotTalys=ND.TotTalys;
	BNECS_g=ND.BNECS_g, BNECS_n=ND.BNECS_n, BNECS_p=ND.BNECS_p, BNECS_d=ND.BNECS_d, BNECS_t=ND.BNECS_t, BNECS_tau=ND.BNECS_tau, BNECS_a=ND.BNECS_a, TEISTot=ND.TEISTot; TEISCont=ND.TEISCont,TEISDiscr=ND.TEISDiscr;
	TalysGroundStateExsists=ND.TalysGroundStateExsists, FastFlag=ND.FastFlag, FastCalculated=ND.FastCalculated;
	EnergyGrid=ND.EnergyGrid;
	Angle=ND.Angle; AngleLab=ND.AngleLab; ElTot=ND.ElTot; ElCompound=ND.ElCompound; ElDirect=ND.ElDirect;
	
	OMPoptionN=ND.OMPoptionN, OMPoptionP=ND.OMPoptionN;
	WriteOMPOrUseKoningP=ND.WriteOMPOrUseKoningP;
	WriteOMPOrUseKoningN=ND.WriteOMPOrUseKoningN;
	ThreadNumber=ND.ThreadNumber;
	WriteDeformation=ND.WriteDeformation;
	
	ElTotValues=ND.ElTotValues;
	ElCompoundValues=ND.ElCompoundValues;
	ElDirectValues=ND.ElDirectValues;
	AngleLabValues=ND.AngleLabValues;
	
	TOTGamProdValues=ND.TOTGamProdValues; TOTNProdValues=ND.TOTNProdValues; TOTPProdValues=ND.TOTPProdValues; TOTDProdValues=ND.TOTDProdValues; TOTAProdValues=ND.TOTAProdValues;TOTTauProdValues=ND.TOTTauProdValues;
	TotElasticValues=ND.TotElasticValues; CompoundElasticValues=ND.CompoundElasticValues; DirectElasticValues=ND.DirectElasticValues; TotInelasticValues=ND.TotInelasticValues; CompoundInelasticValues=ND.CompoundInelasticValues; DirectInelasticValues=ND.DirectInelasticValues; TotTalysValues=ND.TotTalysValues;
	
	BNECS_g_Values=ND.BNECS_g_Values; BNECS_n_Values=ND.BNECS_n_Values; BNECS_p_Values=ND.BNECS_p_Values; BNECS_d_Values=ND.BNECS_d_Values;
	BNECS_t_Values=ND.BNECS_t_Values; BNECS_tau_Values=ND.BNECS_tau_Values; BNECS_a_Values=ND.BNECS_a_Values; TEISTot_Values=ND.TEISTot_Values; TEISCont_Values=ND.TEISCont_Values;TEISDiscr_Values=ND.TEISDiscr_Values;
	
	//OMPN.ReadOMP("n");
	//OMPP.ReadOMP("p");
	for(unsigned int i=0;i<ND.LevelsData.size();i++)
	{
		Levels.emplace_back(ND.LevelsData[i]);
	}
	for(unsigned int i=0;i<ND.ProductsData.size();i++)
	{
		Products.emplace_back(ND.ProductsData[i]);
	}	
	Def=Deformation(ND.DefData);
	
	//Def.SetZA(Z,A);
	//Def.ReadDeformation();
	AssignPointers();
	GenerateGraphs();
}

//Методы класса Nucleus
Nucleus::Nucleus(NucleusData ND)
{
	TH1::AddDirectory(kFALSE);
	GetFromNucleusData(ND);
}
void Nucleus::ReadENSDFFile(string filename,string Nuclide)
{
	if(Nuclide=="")
	{
		Nuclide=Name;
	}
	if(filename=="")
	{
		GetAZ(Nuclide,Z,A);
		char A_char[4];
		sprintf(A_char,"%03d",A);
		filename="ENSDF/ensdf."+string(A_char);
		cout<<"Filename:"<<filename<<" Nuclide:"<<Nuclide<<" "<<A<<"\n";
	}
	Levels.resize(0);
	ifstream ifs(filename.c_str());
	string line;
	std::transform(Nuclide.begin(), Nuclide.end(), Nuclide.begin(), ::toupper);
	cout<<"\n"<<Nuclide<<"\n";
	while(getline(ifs,line))
	{
		if(((int)line.find(Nuclide)>=0))
		{
			Level level;
			
			if(level.ReadLevel(line,Nuclide))
			{
				Levels.push_back(level);
			}
			if(Levels.size()>0)
			{
				Levels[Levels.size()-1].ReadTransition(line);
			}
		}
	}
	for(unsigned int i=0;i<Levels.size();i++)
	{
		Levels[i].fNucleus=this;
		for(unsigned int j=0;j<Levels[i].Gammas.size();j++)
		{
			Levels[i].Gammas[j].fLevel=&Levels[i];
		}
	}
	cout<<"this is ReadENSDFFile:"<<Nuclide<<" "<<Levels.size()<<"\n";
	ifs.close();
}
/*void Nucleus::Print()
{
	for(unsigned int i=0;i<Levels.size();i++)
	{
		Levels[i].Print();
	}
}*/

void Nucleus::SetThreadNumber(int _ThreadNumber)
{
	ROOT::EnableThreadSafety();
	ThreadNumber=_ThreadNumber;
}

void Nucleus::ReadLevelsFromTalysDatabase(string type)
{
	string Filename=GetPathToTalysData()+"/structure/levels/"+type+"/"+GetNucleusName(Z)+".lev";
	ifstream ifs(Filename.c_str());
	string line;
	unsigned int NumberOfLevels=0;
	while(getline(ifs,line))
	{
		if((int)line.find(Name)>-1)
		{
			stringstream s(line);
			string tmp;
			s>>tmp>>tmp>>tmp>>NumberOfLevels;
		}
		if(NumberOfLevels>0)
		{
			for(unsigned int i=0;i<NumberOfLevels;i++)
			{
				float E,J;
				int N=0; int Parity=1; unsigned int NGammas=0;
				getline(ifs,line);
				stringstream s(line);
				string tmp;
				s>>N>>E>>J>>Parity>>NGammas;
				if(E==0)
				{
					TalysGroundStateExsists=true;
				}
				Level lev;
				SpinParity JP(J,Parity);
				lev.SetEnergy(E*1000);
				lev.SetTalysSpinParity(JP);
				lev.Number=N;
				lev.SetOrigin("Talys");
				for(unsigned int j=0;j<NGammas;j++)
				{
					getline(ifs,line);
					stringstream s1(line);
					unsigned int FinalLevelNumber=0;
					float Branch=0;
					s1>>FinalLevelNumber>>Branch;
					lev.Branching.push_back(Branch);
					lev.NumbersOfFinalLevels.push_back(FinalLevelNumber);
				}
				Levels.push_back(lev);
			}
			break;
		}
	}
}
vector<Level*> Nucleus::GetLevelsWithCorrespondingTransitions(float Energy, float tolerancy,float intensity)
{
	vector<Level*> FoundLevels;
	for(unsigned int i=0;i<Levels.size();i++)
	{
		if(Levels[i].CheckEnergy(Energy,tolerancy,intensity))
		{
			FoundLevels.push_back(&Levels[i]);
		}
	}
	return FoundLevels;
}
vector<GammaTransition*> Nucleus::GetGammaTransition(float Energy, float tolerancy,float intensity)
{
	vector<GammaTransition*> result;
	for(unsigned int i=0;i<Levels.size();i++)
	{
		vector<GammaTransition*> r_tmp=Levels[i].GetTransition(Energy,tolerancy,intensity);
		Levels[i].fNucleus=this;
		if(r_tmp.size()>0)
		result.insert(result.end(), r_tmp.begin(), r_tmp.end());
	}
	return result;
}

GammaTransition* Nucleus::GetBestTransition(float Energy,float tolerancy)
{
	vector<GammaTransition*> Transitions;
	if(fMotherNucleus)
	{
		Transitions=GetGammaTransition(Energy,tolerancy,0);
	}
	else
	{
		for(unsigned int i=0;i<Products.size();i++)
		{
			vector<GammaTransition*> TransitionsTmp;
			TransitionsTmp=Products[i].GetGammaTransition(Energy,tolerancy,0);
			if(TransitionsTmp.size()>0)
			Transitions.insert(Transitions.end(),TransitionsTmp.begin(),TransitionsTmp.end());
		}
	}
	GammaTransition* best=0;
	if(Transitions.size()>0)
	{
		best=Transitions[0];
	}
	for(unsigned int i=0;i<Transitions.size();i++)
	{
		if(best->TalysCrossSection<Transitions[i]->TalysCrossSection)
		{
			best=Transitions[i];
		}
	}
	return best;
}
const char* NucleusData::GetName()  const
{
	return Name.c_str();
}
Nucleus::Nucleus(string Name,string Reaction)
{
	TH1::AddDirectory(kFALSE);
	this->Name=Name;
	this->Reaction=Reaction;
	if(Name.find("BKG")==string::npos)
	{
		GetAZ(Name,Z,A);
		TalysCalculated=false;
		fMotherNucleus=0;
		Abundance=GetAbundance(Name);
		ReadLevelsFromTalysDatabase();
		
		Def.SetZA(Z,A);
		Def.ReadDeformation();
		OMPN.Nuclide=this;
		OMPP.Nuclide=this;
		OMPN.ReadOMP("n");
		OMPP.ReadOMP("p");
		AssignPointers();
		TString R_tmp(Reaction.c_str());//получим из реакции вторичную частицу
		R_tmp.ReplaceAll(","," ");
		R_tmp.ReplaceAll(")"," ");
		R_tmp.ReplaceAll("("," ");
		R_tmp.ReplaceAll("'","");
		stringstream s(R_tmp.Data());
		string tmp;
		if(Reaction.size()>1)
		{
			s>>Projectile>>OutgoingParticle;
			OutgoingParticleMass=GetNuclearMass(OutgoingParticle);
			ProjectileMass=GetNuclearMass(Projectile); 
		}
		Mass=GetNuclearMass(Name); 
	}
	else
	{
		stringstream s(Name);
		string tmp;
		string PathToFile;
		s>>tmp>>PathToFile;
		ifstream ifs(PathToFile.c_str());
		string line;
		Levels.resize(1);
		while(getline(ifs,line))
		{
			if(line.find("bkg")!=string::npos)
			{
				stringstream g_stream(line);
				string origin; double E;
				g_stream>>tmp>>E>>origin;
				Levels[0].Gammas.emplace_back(E,"");
				Levels[0].Gammas[Levels[0].Gammas.size()-1].Origin=origin;
			}
		}
		fMotherNucleus=this;
	}
	AssignPointers();
	
}
void Nucleus::SetProjectileEnergy(double E)
{
	ProjectileEnergy=E;
}
void Nucleus::ExecuteCalculationInTalys(string _Projectile)
{
	Projectile=_Projectile;
	PathToCalculationDir=GetPathToTalysData()+"/CalculationResults/";
	if(FastFlag)
	{
		PathToCalculationDir=TString::Format("/dev/shm/CalculationResults%d/",ThreadNumber);
		if(TalysLibManager::Instance().IsEnableWarning())
		{
			system(string("mkdir "+PathToCalculationDir).c_str());
		}
		else
		{
			mkdir(PathToCalculationDir.c_str(),0777);
		}
		FastCalculated=true;
	}
	mkdir((PathToCalculationDir+Name).c_str(),S_IRWXU);
	string filename=PathToCalculationDir+Name+"/input";
	ofstream ofs(filename.c_str());
	ofs<<"projectile "<<Projectile<<"\nelement "<<GetNucleusName(Z)<<"\nmass "<<A<<"\nenergy "<<ProjectileEnergy<<"\noutdiscrete y\noutgamdis y\noutangle y\noutexcitation y\n channels y\n";
	for(unsigned int i=0;i<TalysOptions.size();i++)
	{
		ofs<<TalysOptions[i]<<"\n";
	}
	if(WriteOMPOrUseKoningP>-1)
	{
		if((OMPP.Potential.ReadFlag)||(WriteOMPOrUseKoningP>0))
		{
			ofs<<"optmodfileP "<<Z<<" "<<GetNucleusName(Z)<<"P.omp\n";
			OMPP.SaveOMP(PathToCalculationDir+Name+"/"+GetNucleusName(Z)+"P.omp",WriteOMPOrUseKoningP);
		}
		
	}
	if(WriteOMPOrUseKoningN>-1)
	{
		if((OMPN.Potential.ReadFlag)||(WriteOMPOrUseKoningN>0))
		{
			ofs<<"optmodfileN "<<Z<<" "<<GetNucleusName(Z)<<"N.omp\n";
			OMPN.SaveOMP(PathToCalculationDir+Name+"/"+GetNucleusName(Z)+"N.omp",WriteOMPOrUseKoningN);
		}
	}
	if(WriteDeformation)
	{
		ofs<<"deformfile "<<Z<<" "<<GetNucleusName(Z)<<".def\n";
		Def.WriteDeformation(PathToCalculationDir+Name+"/"+GetNucleusName(Z)+".def");
	}
	ofs.close();
	system(string("cd "+PathToCalculationDir+Name+"/; talys <input >output").c_str());
}

void Nucleus::SortingLevels()
{
	if(Levels.size()<2)
	{
		return;
	}
	for(unsigned int i=0;i<Levels.size()-1;i++)
	{
		for (unsigned int j = 0; j <Levels.size()-i-1; j++)
		{
			//cout<<Levels.size()<<" "<<i<<" "<<j<<"\n";
			if(Levels[j].Energy>Levels[j+1].Energy)
			{
				swap(Levels[j],Levels[j+1]);
			}
		}
	}
}

Level* Nucleus::FindBestLevelByEJP(float Energy,SpinParity JP,float tolerancy)//проверить эту функцию!
{
	Level* result=0;
	float MinJPDifference;
	for(unsigned int i=0;i<Levels.size();i++)
	{
		if(!result)
		{
			if(abs(Levels[i].GetEnergy()-Energy)<tolerancy)
			{
				result=&Levels[i];
				if(Levels[i].GetJPValues().size()>0)
				{
					MinJPDifference=abs(Levels[i].GetJPValues()[0].J);
				}
				for(unsigned int j=0;j<Levels[i].GetJPValues().size();j++)
				{
					if(abs(Levels[i].GetJPValues()[j].J-JP.J)<MinJPDifference)
					{
						MinJPDifference=Levels[i].GetJPValues()[j].J-JP.J;
					}
				}
			}
		}
		else if(abs(Levels[i].GetEnergy()-Energy)<abs(result->Energy-Energy))
		{
			bool DifferenceInJPIsLowerThanBefore=false;
			for(unsigned int j=0;j<Levels[i].GetJPValues().size();j++)
			{
				if(abs(Levels[i].GetJPValues()[j].J-JP.J)<MinJPDifference)
				{
					MinJPDifference=abs(Levels[i].GetJPValues()[j].J-JP.J);
					DifferenceInJPIsLowerThanBefore=true;
				}
			}
			if(DifferenceInJPIsLowerThanBefore&&(result->Mark>Levels[i].Mark))
			{
				result=&Levels[i];
			}
		}
	}
	return result;
}

Level* Nucleus::FindLevelFromTalys(float Energy,SpinParity JP)
{
	for(unsigned int i=0;i<Levels.size();i++)
	{
		if((Levels[i].Origin=="Talys")||(Levels[i].Energy==0))
		{
			if(abs(Levels[i].GetEnergy()-Energy)<1)
			{
				if(Levels[i].GetTalysSpinParity()==JP)
				return &Levels[i];
			}
		}
	}
	return 0;
}

Level* Nucleus::FindLevelByEnergy(float Energy,float tolerancy)
{
	for(unsigned int i=0;i<Levels.size();i++)
	{
		if(abs(Levels[i].GetEnergy()-Energy)<1)
		{
			return &Levels[i];
		}
	}
	return 0;
}

Level* Nucleus::FindLevelByNumber(int number)
{
	for(unsigned int i=0;i<Levels.size();i++)
	{
		if(Levels[i].Number==number)
		{
			return &Levels[i];
		}
	}
	return NULL;
}
Nucleus* Nucleus::FindProductByName(string _Name)
{
	Nucleus *MotherNucleus=this;
	if(fMotherNucleus)
	{
		MotherNucleus=fMotherNucleus;
	}
	for(unsigned int i=0;i<MotherNucleus->Products.size();i++)
	{
		if(MotherNucleus->Products[i].Name==_Name)
		{
			return &(MotherNucleus->Products[i]);
		}
	}
	return 0;
}
void Nucleus::ReadTalysCalculationResult()
{
	
	string filename;
	PlottedADist=false;
	if(fMotherNucleus)
	{
		filename=fMotherNucleus->PathToCalculationDir+fMotherNucleus->Name+"/output";
	}
	else
	{
		filename=PathToCalculationDir+Name+"/output";
	}
	ifstream ifs(filename.c_str());
	string line;
	bool read_flag=false;
	
	//сбросим данные для уровней
	for(unsigned int i=0;i<Levels.size();i++)
	{
		Levels[i].Reset();
	}
	//TOTGamProd=0, TOTNProd=0, TOTPProd=0, TOTDProd=0, TOTAProd=0;
	while(getline(ifs,line))
	{
		if(((int)line.find("Nuclide:"))>0)
		{
			if(((int)line.find(Name))>0)
			read_flag=true;
		}
		if(read_flag&&(((int)line.find("--->"))>0))
		{
			int Numi,Numf;
			double Ei,Ef,Egamma,CrossSection;
			string JPi,JPf,tmp;
			stringstream s(line);
			s>>Numi>>JPi>>Ei>>tmp>>Numf>>JPf>>Ef>>Egamma>>CrossSection;
			//float TalysJP=TalysJPToNormalJP(JPi);
			SpinParity TalysJP(JPi);
			SpinParity TalysJPF(JPf);
			Ei=Ei*1000;
			Ef=Ef*1000;
			Egamma=Egamma*1000;
			if(!TalysGroundStateExsists)//add ground state from Talys
			{
				if(Ef==0)//signature of ground state
				{
					Levels.emplace_back();
					Levels[Levels.size()-1].SetEnergy(Ef); Levels[Levels.size()-1].SetTalysSpinParity(TalysJPF);
					Levels[Levels.size()-1].Number=Numf;
					TalysGroundStateExsists=true;
				}
			}
			Level *TalysLevel=FindLevelFromTalys(Ei,TalysJP);
			if(!TalysLevel)
			{
				Levels.emplace_back();
				Levels[Levels.size()-1].SetEnergy(Ei); Levels[Levels.size()-1].SetTalysSpinParity(TalysJP);
				TalysLevel=&Levels[Levels.size()-1];
				Levels[Levels.size()-1].SetOrigin("Talys");
				Levels[Levels.size()-1].AddJPValue(TalysJP);
				Levels[Levels.size()-1].Number=Numi;
			}
			TalysLevel->AddLineFromTalys(Egamma,CrossSection,Ei,Ef,SpinParity(JPi),SpinParity(JPf),Numi,Numf);
			TalysLevel->fNucleus=this;
			/*cout<<"Egamma:"<<Egamma<<"; Level:"<<TalysLevel->Energy<<"; "<<Levels[Levels.size()-1].Energy;
			if(Egamma>TalysLevel->Energy)
			{
				cout<<"!!!!!!!!!";
			}
			cout<<"\n";*/
		}
		if((((int)line.find("Total"))>0)&&read_flag)
		{
			ifs.close();
			read_flag=false;
			//return ;
		}
	}
	//чтобы получить список уровней, сначала нужно прочитать список гамма, позже переделаю для более эффективной работы
	bool ExcitationFlag=false;
	bool ADistFlag=false;
	ifs.open(filename.c_str());
	string TalysExcitationMark=ReactionToTalysNotation(kExcitationCS);
	string TalysADistMark=ReactionToTalysNotation(kAngularDistribution);
	Level* UsedLevel=0;
	int CurrentLevelNumber=0;
	if(TalysExcitationMark!="NDEF")
	{
		while(getline(ifs,line))
		{
			
			if(((int)line.find(TalysExcitationMark))>-1)
			{
				ExcitationFlag=true;
				UsedLevel=0;
				line.resize(0);
			}
			if(((int)line.find(TalysADistMark))>-1)
			{
				ADistFlag=true;
				line.resize(0);
				CurrentLevelNumber=-1;
			}
			if(((int)line.find("---------"))>0)
			{
				ExcitationFlag=false;
				UsedLevel=0;
			}
			if(((int)line.find("Gamma-ray intensities"))>0)
			{
				ADistFlag=false;
				UsedLevel=0;
			}
			if((ExcitationFlag)&&(line.size()>10))
			{
				stringstream s(line);
				
				unsigned int N;
				string tmp;
				float Energy,OutEnergy, Direct, Compound, Total;
				OutEnergy=0;
				s>>N>>Energy>>OutEnergy>>tmp>>Direct>>Compound>>Total;
				UsedLevel=FindLevelByNumber(N);
				if((UsedLevel)&&(line.size()>22)&&(OutEnergy>0))
				{
					UsedLevel->OutgoingParticleEnergy=OutEnergy;
					UsedLevel->TalysCSDirect=Direct;
					UsedLevel->TalysCSCompound=Compound;
					UsedLevel->TalysCS=Total;
				}
			}
			if((ADistFlag)&&line.size()>10)
			{
				if(((int)line.find("Level"))>-1)
				{
					string tmp;
					int NLev;
					stringstream s(line);
					s>>tmp>>NLev;
					if(CurrentLevelNumber>NLev)
					{
						UsedLevel=0;
						ADistFlag=false;
					}
					else
					{
						CurrentLevelNumber=NLev;
						UsedLevel=FindLevelByNumber(CurrentLevelNumber);
					}
					
				}
				stringstream s(line);
				string tmp;
				if((line.size()>22)&&(UsedLevel)&&CurrentLevelNumber>0)
				{
					float Angle=0, Total=0, Compound=0, Direct=0;
					s>>Angle>>Total>>Direct>>Compound;
					if(Total!=0)
					{
						UsedLevel->ADTot.push_back(Total);
						UsedLevel->ADDirect.push_back(Direct);
						UsedLevel->ADCompound.push_back(Compound);
						UsedLevel->Angle.push_back(Angle);
						//ConvertAngleToLab(double angle, double ma, double Ta, double mA, double mb, double mB, double Tb)
						double MNMass, PrEnergy, PrMass;
						if(fMotherNucleus)
						{
							MNMass=fMotherNucleus->Mass;
							PrEnergy=fMotherNucleus->ProjectileEnergy;
							PrMass=fMotherNucleus->ProjectileMass;
						}
						else
						{
							MNMass=Mass;
						}
						UsedLevel->AngleLab.push_back(ConvertAngleToLab(Angle,PrMass,PrEnergy,MNMass,OutgoingParticleMass,Mass,UsedLevel->OutgoingParticleEnergy));
					}
				}
			}
			if((line.find(ReactionToTalysNotation(kTotalInelasticCS))!=string::npos)&&(line.size()>50))//line.size()>50 нужен, чтобы не возникало путаницы с (n,gn), который обозначается абсолютно также
			{
				line=line.substr(22,line.size()-22);
				stringstream s(line);
				s>>DirectInelastic>>CompoundInelastic>>TotInelastic;
			}
			if(line.find("EXCITATION FUNCTIONS")!=string::npos)
			{
				ifs.close();
				return;
			}
		}
	}
	ifs.close();
}
void Nucleus::ReadElastic()
{
	string filename;
	if(fMotherNucleus)
	{
		filename=PathToCalculationDir+fMotherNucleus->Name+"/output";
	}
	else
	{
		filename=PathToCalculationDir+Name+"/output";
	}
	
	ifstream ifs(filename.c_str());
	bool ElasticFlag=false;
	string ElasticMark="Elastic scattering angular distribution";
	int BNECS_iterator=0;
	bool BNECS_flag=false;
	string line;
	bool ProdFlag=false;
	bool ExcitationFunctionsFlag=false;
	int TEIS_iterator=0;
	bool TEIS_flag=false;
	
	Angle.resize(0);
	ElTot.resize(0);
	ElCompound.resize(0);
	ElDirect.resize(0);
	
	while(getline(ifs,line))
	{
		if(line.find("Center-of-mass energy:")!=string::npos)
		{
			string tmp;
			stringstream s(line);
			s>>tmp>>tmp>>ProjectileEnergyCM;
		}		
		if((int)line.find("Total particle production cross sections")>-1)
		{
			ProdFlag=true;
		}
		if((int)line.find("Residual production cross sections")>-1)
		{
			ProdFlag=false;
		}
		if((ProdFlag=true)&&(line.size()>45))
		{
			//TOTGamProd=0, TOTNProd=0, TOTPProd=0, TOTDProd=0, TOTAProd=0
			stringstream s(line);
			if((int)line.find("gamma   =")>-1)
			{
				string tmp;
				s>>tmp>>tmp>>TOTGamProd;
			}
			if((int)line.find("neutron =")>-1)
			{
				string tmp;
				s>>tmp>>tmp>>TOTNProd;
			}
			if((int)line.find("proton  =")>-1)
			{
				string tmp;
				s>>tmp>>tmp>>TOTPProd;
			}
			if((int)line.find("deuteron=")>-1)
			{
				string tmp;
				s>>tmp>>TOTDProd;
			}
			if((int)line.find("alpha   =")>-1)
			{
				string tmp;
				s>>tmp>>tmp>>TOTAProd;
			}
			if((int)line.find("helium-3=")>-1)
			{
				string tmp;
				s>>tmp>>TOTTauProd;
			}
		}
		if(((int)line.find(ElasticMark)>-1))
		{
			ElasticFlag=true;
			line.resize(0);
		}
		if(((int)line.find("Level"))>-1)
		{

			ElasticFlag=false;
		}
		if((ElasticFlag)&&(line.size()>50))
		{
			float A=0, Tot=0, Comp=0, Dir=0;
			stringstream s(line);
			s>>A>>Tot>>Dir>>Comp;
			if(Tot>0)
			{
				Angle.push_back(A);
				//ConvertAngleToLab(double angle, double ma, double Ta, double mA, double mb, double mB, double Tb)
				AngleLab.push_back(ConvertAngleToLab(A,ProjectileMass,ProjectileEnergy,Mass,ProjectileMass,Mass,ProjectileEnergyCM));
				ElTot.push_back(Tot);
				ElCompound.push_back(Comp);
				ElDirect.push_back(Dir);
			}
		}
		if(line.find("Shape elastic")!=string::npos)
		{
			stringstream s(line);
			string tmp;
			s>>tmp>>tmp>>tmp>>DirectElastic;
		}
		if(line.find("Compound elastic")!=string::npos)
		{
			string tmp;
			stringstream s(line);
			s>>tmp>>tmp>>CompoundElastic;
		}
		if(line.find("Total elastic")!=string::npos)
		{
			stringstream s(line);
			string tmp;
			s>>tmp>>tmp>>tmp>>TotElastic;
		}
		if(line.find("Total           =")!=string::npos)
		{
			
			stringstream s(line);
			string tmp;
			s>>tmp>>tmp>>TotTalys;
		}
		if(line.find("EXCITATION FUNCTIONS")!=string::npos)
		{
			ExcitationFunctionsFlag=true;
		}
		if((line.find("2. Binary non-elastic cross sections (non-exclusive)")!=string::npos)&&ExcitationFunctionsFlag)
		{
			BNECS_iterator=0;
			BNECS_flag=true;
		}
		if(BNECS_flag)
		{
			BNECS_iterator++;
		}
		if(BNECS_iterator==5)
		{
			stringstream s(line);
			string tmp;
			s>>tmp>>BNECS_g>>BNECS_n>>BNECS_p>>BNECS_d>>BNECS_t>>BNECS_tau>>BNECS_a;
		}
		if((line.find("Total exclusive Inelastic scattering")!=string::npos)&&ExcitationFunctionsFlag)
		{
			TEIS_flag=true;
		}
		if(TEIS_flag)
		{
			TEIS_iterator++;
		}
		if(TEIS_iterator==5)
		{
			stringstream s(line);
			string tmp;
		//	cout<<line<<"\n";
			s>>tmp>>TEISTot>>TEISDiscr>>TEISCont;
			ifs.close();
			return;
		}
		
		/*if(line.find("EXCITATION FUNCTIONS")!=string::npos)
		{
			ifs.close();
			return;
		}*/
	}
	ifs.close();
}
TGraph* Nucleus::GetElasticAngularDistribution(string type,string option)
{
	if(!fMotherNucleus)
	{
		if((!PlottedADist)||(option=="new")||kAlwaysNewGraphs)
		{
			//ElacticTotTalys, ElasticDirectTalys,ElasticCompoundTalys; Angle, ElTot, ElCompound, ElDirect;
			if(ConvertToLab)
			{
				ElacticTotTalys=TGraph(Angle.size(), &AngleLab[0], &ElTot[0]);
				ElasticCompoundTalys=TGraph(Angle.size(), &AngleLab[0], &ElCompound[0]);
				ElasticDirectTalys=TGraph(Angle.size(), &AngleLab[0], &ElDirect[0]);
			}
			else
			{
				ElacticTotTalys=TGraph(Angle.size(), &Angle[0], &ElTot[0]);
				ElasticCompoundTalys=TGraph(Angle.size(), &Angle[0], &ElCompound[0]);
				ElasticDirectTalys=TGraph(Angle.size(), &Angle[0], &ElDirect[0]);
			}
			
			string TotName="ElTotTalys";
			string CompName="ElCompTalys";
			string DirName="ElDirTalys";
			TString TotTitle=TString::Format("Total #frac{d#sigma_{el}}{d#Omega} for %s;Angle, deg;#frac{d#sigma}{d#Omega},mb",(Name).c_str());
			TString CompTitle=TString::Format("Compound #frac{d#sigma_{el}}{d#Omega} for %s;Angle, deg;#frac{d#sigma}{d#Omega},mb",(Name).c_str());
			TString DirTitle=TString::Format("Direct #frac{d#sigma_{el}}{d#Omega} for %s;Angle, deg;#frac{d#sigma}{d#Omega},mb",(Name).c_str());
			ElacticTotTalys.SetName(TotName.c_str());
			ElasticCompoundTalys.SetName(CompName.c_str());
			ElasticDirectTalys.SetName(DirName.c_str());
			
			ElacticTotTalys.SetTitle(TotTitle);
			ElasticCompoundTalys.SetTitle(CompTitle);
			ElasticDirectTalys.SetTitle(DirTitle);
		}

		if(type=="Total")
		{
			return &ElacticTotTalys;
		}
		if(type=="Compound")
		{
			return &ElasticCompoundTalys;
		}
		if(type=="Direct")
		{
			return &ElasticDirectTalys;
		}
	}
	else
	{
		return fMotherNucleus->GetElasticAngularDistribution(type,option);
	}
	
	return 0;
}

TGraph2D* Nucleus::GetElasticAngularDistribution2D(string type,string option)
{
	if(!fMotherNucleus)
	{
		int PointIterator=0;
		if((!PlottedADist2D)||(option=="new")||kAlwaysNewGraphs)
		{
			//ElacticTotTalys, ElasticDirectTalys,ElasticCompoundTalys; Angle, ElTot, ElCompound, ElDirect;
			/*if(ConvertToLab)
			{
				ElacticTotTalys=TGraph(Angle.size(), &AngleLab[0], &ElTot[0]);
				ElasticCompoundTalys=TGraph(Angle.size(), &AngleLab[0], &ElCompound[0]);
				ElasticDirectTalys=TGraph(Angle.size(), &AngleLab[0], &ElDirect[0]);
			}
			else
			{
				ElacticTotTalys=TGraph(Angle.size(), &Angle[0], &ElTot[0]);
				ElasticCompoundTalys=TGraph(Angle.size(), &Angle[0], &ElCompound[0]);
				ElasticDirectTalys=TGraph(Angle.size(), &Angle[0], &ElDirect[0]);
			}*/
			
			for(unsigned int i=0;i<EnergyGrid.size();i++)
			{
				for(unsigned int j=0;j<ElTotValues[i].size();j++)
				{
					ElacticTotTalys2D.SetPoint(PointIterator,EnergyGrid[i],Angle[j],ElTotValues[i][j]);
					ElasticDirectTalys2D.SetPoint(PointIterator,EnergyGrid[i],Angle[j],ElDirectValues[i][j]);
					ElasticCompoundTalys2D.SetPoint(PointIterator,EnergyGrid[i],Angle[j],ElCompoundValues[i][j]);
					PointIterator++;
				}
			}
			
			string TotName="ElTotTalys2D";
			string CompName="ElCompTalys2D";
			string DirName="ElDirTalys2D";
			TString TotTitle=TString::Format("Total #frac{d#sigma_{el}}{d#Omega} for %s; E, MeV; Angle, deg;#frac{d#sigma}{d#Omega},mb",(Name).c_str());
			TString CompTitle=TString::Format("Compound #frac{d#sigma_{el}}{d#Omega} for %s; E, MeV; Angle, deg;#frac{d#sigma}{d#Omega},mb",(Name).c_str());
			TString DirTitle=TString::Format("Direct #frac{d#sigma_{el}}{d#Omega} for %s; E, MeV; Angle, deg;#frac{d#sigma}{d#Omega},mb",(Name).c_str());
			ElacticTotTalys2D.SetName(TotName.c_str());
			ElasticCompoundTalys2D.SetName(CompName.c_str());
			ElasticDirectTalys2D.SetName(DirName.c_str());
			
			ElacticTotTalys2D.SetTitle(TotTitle);
			ElasticCompoundTalys2D.SetTitle(CompTitle);
			ElasticDirectTalys2D.SetTitle(DirTitle);
		}

		if(type=="Total")
		{
			return &ElacticTotTalys2D;
		}
		if(type=="Compound")
		{
			return &ElasticCompoundTalys2D;
		}
		if(type=="Direct")
		{
			return &ElasticDirectTalys2D;
		}
	}
	else
	{
		return fMotherNucleus->GetElasticAngularDistribution2D(type,option);
	}
	PlottedADist2D=true;
	return 0;
}
TGraph* Nucleus::GetElasticAngularDistributionAtEnergy(float Energy, string type, string option)
{
	TGraph2D *refGraph=GetElasticAngularDistribution2D(type,option);
	if((Energy>=MinEnergy)&&(Energy<=MaxEnergy))
	{
		TGraph result;
		for(unsigned int i=0;i<Angle.size();i++)
		{
			result.SetPoint(i,Angle[i],refGraph->Interpolate(Energy,Angle[i]));
		}
		result.SetName(TString::Format("Elastic_at_E%.1f",Energy));
		TString Title=TString::Format("%s #frac{d#sigma_{el}}{d#Omega} for E_{%s}=%.1f; #theta, deg; #frac{d#sigma}{d#Omega}, mb/str",type.c_str(),Projectile.c_str(),Energy);
		result.SetTitle(Title);
		GeneratedGraphsList.push_back(result);
		return &(GeneratedGraphsList.back());
	}
	else
	{
		if(EnergyGrid.size()>0)
		{
			EnergyGrid.push_back(Energy);
			MainNucleusFlag=0;
			GenerateProducts(Projectile);
			return GetElasticAngularDistributionAtEnergy(Energy,type,option);
		}
	}
	return 0;
}
void Nucleus::MergeLevels(float tolerancy)
{
	vector<Level> Levels_tmp;
	for(unsigned int i=0;i<Levels.size();i++)
	{
		bool existed_in_merged_vector=false;
		bool ExsistedInTalys=false;
		
		
		for(unsigned int j=0;j<Levels_tmp.size();j++)
		{		
			for(unsigned int k=0;k<Levels_tmp[j].Gammas.size();k++)
			{
				if(Levels_tmp[j].Gammas[k].TalysCrossSection>0)
				{
					ExsistedInTalys=true;
					break;
				}
			}
			if((abs(Levels_tmp[j].Energy-Levels[i].Energy)<tolerancy)&&(!ExsistedInTalys))
			{
				if(Levels_tmp[j].Mark>Levels[i].Mark)
				{
					Levels_tmp[j]=Levels[i];
				}
				existed_in_merged_vector=true;
			}
		}
		if(!existed_in_merged_vector)
		{
			if((Levels[i].JP_values.size()>0)&&((Levels[i].Gammas.size()>0)||ExsistedInTalys))
			Levels_tmp.push_back(Levels[i]);
		}
	}
	Levels=Levels_tmp;
	SortingLevels();
	for(unsigned int i=0;i<Levels.size();i++)
	{
		Levels[i].fNucleus=this;
	}
}

void Nucleus::GenerateEnergyGrig(float min, float step, float max)
{
	EnergyGrid.resize(0);
	float CurrE=min;
	while(CurrE<max)
	{
		EnergyGrid.push_back(CurrE);
		CurrE+=step;
	}
}

void Nucleus::MergeEnergyGridData(vector<Nucleus*> NucleiInEnergyGrid)
{
	for(unsigned int i=0;i<NucleiInEnergyGrid.size();i++)
	{
		/*for(unsigned int j=0;j<NucleiInEnergyGrid[i]->Products.size();j++)
		{
			
			for(unsigned int k=0;k<NucleiInEnergyGrid[i]->Products[j].Levels.size();k++)
			{
				//if(Products[j].Levels[k].Energy<ProjectileEnergy)
				{
					Products[j].Levels[k].AddPoint(&(NucleiInEnergyGrid[i]->Products[j].Levels[k]));
				}
			}
		}*/
		AddPoint(NucleiInEnergyGrid[i]);
	}
	for(unsigned int i=0;i<EnergyGrid.size();i++)
	{
		ElTotValues.push_back(NucleiInEnergyGrid[i]->ElTot); ElCompoundValues.push_back(NucleiInEnergyGrid[i]->ElCompound); ElDirectValues.push_back(NucleiInEnergyGrid[i]->ElDirect);
		if(NucleiInEnergyGrid[i]->MainNucleusFlag!=2)
		{
			delete NucleiInEnergyGrid[i];
		}
	}
	
	/*for(unsigned int j=0;j<Products.size();j++)
	{
		for(unsigned int k=0;k<Products[j].Levels.size();k++)
		{
			Products[j].Levels[k].AddPoint(&(Products[j].Levels[k]));
		}
	}*/
}

void EvalEdepData(Nucleus* Data, string Proj)
{
	Data->GenerateProducts(Proj);
}

void Nucleus::GenerateProducts(string _Projectile)
{
	Products.resize(0);
	Projectile=_Projectile;
	ProjectileMass=GetNuclearMass(Projectile); 
	if(Name.find("BKG")!=string::npos)
	{
		return;
	}
	vector<Nucleus*> NucleiInEnergyGrid;
	if((EnergyGrid.size()>0)&&(MainNucleusFlag==0))
	{
		sort(EnergyGrid.begin(),EnergyGrid.end());
		ProjectileEnergy=EnergyGrid[EnergyGrid.size()-1];
		MainNucleusFlag=2;//ядро, для которого строится энергетическая зависимость
		if(EnergyGrid.size()>1)
		{
			MinEnergy=EnergyGrid[0]; MaxEnergy=EnergyGrid[EnergyGrid.size()-1];
			for(unsigned int i=0;i<EnergyGrid.size()-1;i++)
			{
				NucleiInEnergyGrid.emplace_back(new Nucleus(this->ToNucleusData()));
				NucleiInEnergyGrid[i]->MainNucleusFlag=1;
				NucleiInEnergyGrid[i]->ProjectileEnergy=EnergyGrid[i];
				NucleiInEnergyGrid[i]->EnergyGrid.resize(0);
				NucleiInEnergyGrid[i]->ThreadNumber=ThreadNumber*10000+i+1;
				NucleiInEnergyGrid[i]->EnergyGridIndex=i;
				NucleiInEnergyGrid[i]->fMotherNucleus=0;
			}
		}
		NucleiInEnergyGrid.push_back(this);
		for(unsigned int i=0;i<NucleiInEnergyGrid.size();i++)
		{
			if(!FastFlag)
			{
				NucleiInEnergyGrid[i]->GenerateProducts(_Projectile);
			}
		}
		if(FastFlag)
		{
			ROOT::EnableThreadSafety();
			vector<thread> Threads;
			for(unsigned int i=0;i<NucleiInEnergyGrid.size();i++)
			{
				Threads.emplace_back(EvalEdepData,NucleiInEnergyGrid[i],Projectile);
			}
			for(unsigned int i=0;i<Threads.size();i++)
			{
				Threads[i].join();
			}
		}
		
	}
	if(NucleiInEnergyGrid.size()>0)
	{
		MergeEnergyGridData(NucleiInEnergyGrid);
		if(TalysLibManager::Instance().GenerateAllGraphs)
		{
			GenerateGraphs();
		}
		SetTGraphNameAndTitle("Energy");
		return;
	}
	ExecuteCalculationInTalys(Projectile);
	int ProjZ,ProjA;
	
	GetAZ(Projectile,ProjZ,ProjA);
	//реакции: (x,n),(x,p),(x,2n),(x,a),(x,d),захват
	
	string name=to_string(A+ProjA-1)+GetNucleusName(Z+ProjZ);
	Products.push_back(Nucleus(name,"("+Projectile+",n')"));
	name=to_string(A+ProjA-1)+GetNucleusName(Z+ProjZ-1);
	Products.push_back(Nucleus(name,"("+Projectile+",p)"));
	name=to_string(A+ProjA-2)+GetNucleusName(Z+ProjZ);
	Products.push_back(Nucleus(name,"("+Projectile+",2n)"));
	name=to_string(A+ProjA-4)+GetNucleusName(Z+ProjZ-2);
	Products.push_back(Nucleus(name,"("+Projectile+",a)"));
	name=to_string(A+ProjA-2)+GetNucleusName(Z+ProjZ-1);
	Products.push_back(Nucleus(name,"("+Projectile+",d)"));
	
	for(unsigned int i=0;i<Products.size();i++)
	{
		Products[i].fMotherNucleus=this;
		Products[i].FastFlag=FastFlag;
		//Products[i].ReadENSDFFile();
	}
	for(unsigned int i=0;i<Products.size();i++)
	{
		Products[i].ReadTalysCalculationResult();
		Products[i].AssignPointers();
	}
	ReadElastic();
	
}
string Nucleus::PrintLevels()
{
	string result;
	result+=Name<+"\n";
	for(unsigned int i=0;i<Levels.size();i++)
	{
		Levels[i].fNucleus=this;
		result+=to_string(Levels[i].Number)+" "+to_string(Levels[i].Energy)+" "+Levels[i].TalysJP.GetLine()+"\n";
	}
	return result;
}
string Nucleus::PrintReactions()
{
	string result;
	for(unsigned int i=0;i<Products.size();i++)
	{
		result+=Name+Products[i].Reaction+Products[i].Name+"\n";
	}
	return result;
}
string Nucleus::ReactionToTalysNotation(char DataSelection)
{
	if(Reaction==("(n,n')"))
	{
		if(DataSelection==kExcitationCS)
		return "Inelastic cross sections";
		if(DataSelection==kAngularDistribution)
		return "Inelastic angular distributions";
		if(DataSelection==kTotalInelasticCS)
		return "Total     Inelastic";
		
	}
	if(Reaction==("(n,p)"))
	{
		if(DataSelection==kExcitationCS)
		return "(n,p)   cross sections";
		if(DataSelection==kAngularDistribution)
		return "(n,p) angular distributions";
		if(DataSelection==kTotalInelasticCS)
		return "Total       (n,p)";
	}
	if(Reaction==("(n,d)"))
	{
		if(DataSelection==kExcitationCS)
		return "(n,d)   cross sections";
		if(DataSelection==kAngularDistribution)
		return "(n,d) angular distributions";
		if(DataSelection==kTotalInelasticCS)
		return "Total       (n,d)";
	}
	if(Reaction==("(n,a)"))
	{
		if(DataSelection==kExcitationCS)
		return "(n,a)   cross sections";
		if(DataSelection==kAngularDistribution)
		return "(n,a) angular distributions";
		if(DataSelection==kTotalInelasticCS)
		return "Total       (n,a)";
	}
		if(Reaction==("(p,p')"))
	{
		if(DataSelection==kExcitationCS)
		return "Inelastic cross sections";
		if(DataSelection==kAngularDistribution)
		return "Inelastic angular distributions";
		if(DataSelection==kTotalInelasticCS)
		return "Total     Inelastic";
	}
	if(Reaction==("(p,n)"))
	{
		if(DataSelection==kExcitationCS)
		return "(p,n)   cross sections";
		if(DataSelection==kAngularDistribution)
		return "(p,n) angular distributions";
		if(DataSelection==kTotalInelasticCS)
		return "Total       (p,n)";
	}
	if(Reaction==("(p,d)"))
	{
		if(DataSelection==kExcitationCS)
		return "(p,d)   cross sections";
		if(DataSelection==kAngularDistribution)
		return "(p,d) angular distributions";
		if(DataSelection==kTotalInelasticCS)
		return "Total       (p,d)";
	}
	if(Reaction==("(p,a)"))
	{
		if(DataSelection==kExcitationCS)
		return "(p,a)   cross sections";
		if(DataSelection==kAngularDistribution)
		return "(p,a) angular distributions";
		if(DataSelection==kTotalInelasticCS)
		return "Total       (p,a)";
	}
	return "NDEF";
}
TString Nucleus::ReactionInTLatexFormat(string option)
{
	TString ReactionS(Reaction.c_str());
	ReactionS.ReplaceAll("a","#alpha");
	if(option=="full")
	{
		return TString::Format("^{%d}%s%s^{%d}%s",fMotherNucleus->A,GetNucleusName(fMotherNucleus->Z).c_str(),ReactionS.Data(),A,GetNucleusName(Z).c_str());
	}
	if(option=="short")
	{
		return TString::Format("^{%d}%s%s",fMotherNucleus->A,GetNucleusName(fMotherNucleus->Z).c_str(),ReactionS.Data());
	}
	return "";
}
TString Nucleus::NucleusNameInTLatexFormat(string option)
{
	string ElementName=GetNucleusName(Z);
	if(option=="full")
	{
		return TString::Format("{}^{%d}_{%d}%s_{%d}",A,Z,ElementName.c_str(),A-Z);
	}
	if(option=="short")
	{
		return TString::Format("{}^{%d}%s",A,ElementName.c_str());
	}
	return "";
}
void Nucleus::GenerateGammaSpectrum(TH1F *Spectrum, TF1* ResolutionFunction, int NEntries)//Доделать!
{
	vector<GammaTransition*> t;
	if(Products.size()>0)
	{
		for(unsigned int i=0;i<Products.size();i++)
		{
			vector<GammaTransition*> t2=GetGammaTransitions();
			t.insert(t.end(), t2.begin(), t2.end());
		}
	}
	else
	{
		t=GetGammaTransitions();
	}
	
/*	int iterator=0;
	TH1F h("h","h",10000,0,10000);*/
	
/*	for(unsigned int i=0;i<h.GetNbinsX();i++)
	{
		for(unsigned int j=0;j<t.size();j++)
		{
			double sigma=ResolutionFunction->Eval(t[j]->Energy);
			h.SetBinContent(h.GetBinContent(i)+);
		}
	}*/
}

void Nucleus::DrawLevelScheme(double MinTalysCS)
{
	double Min,Max;
	for(unsigned int i=0;i<Levels.size();i++)
	{
		if(Levels[i].Energy<Min)
		{
			Min=Levels[i].Energy;
		}
		if(Levels[i].Energy>Max)
		{
			for(unsigned int j=0;j<Levels[i].Gammas.size();j++)
			{
				if(MinTalysCS<=Levels[i].Gammas[j].TalysCrossSection)
				{
					Max=Levels[i].Energy;
				}
			}
		}
	}
	//пересчитываем координаты в NDC
	double k=(Max-Min)/0.8;
	double a=0.1;
	TLine l,l2;
	TLatex t;
	TLatex t2;
	t.DrawLatexNDC(0.4,0.05,NucleusNameInTLatexFormat("full"));
	t.SetTextSize(0.02);
	t2.SetTextSize(0.02);
	t2.SetTextSize(0.02);
	t2.SetTextAngle(90);
	double step=0.02;
	double Start=0.2;
	int LevelIterator=0;
	
	int NumberOfGammas=0;
	//костыль для подсчета количества гамма
	for(unsigned int i=0;i<Levels.size();i++)
	{
		bool DrawLevel=false;
		for(unsigned int j=0;j<Levels[i].Gammas.size();j++)
		{
			if(MinTalysCS<=Levels[i].Gammas[j].TalysCrossSection)
			{
				DrawLevel=true;
			}
		}
		if(Levels[i].Energy==0)
		{
			DrawLevel=true;
		}
		if(DrawLevel)
		{
			for(unsigned int j=0;j<Levels[i].Gammas.size();j++)
			{
				if(MinTalysCS<=Levels[i].Gammas[j].TalysCrossSection)
				{
					NumberOfGammas++;
				}
			}
		}
	}
	//костыль закончен
	double Step_tmp=0.5/(NumberOfGammas+1);
	if(Step_tmp>step)
	{
		step=Step_tmp;
	}
	for(unsigned int i=0;i<Levels.size();i++)
	{
		bool DrawLevel=false;
		for(unsigned int j=0;j<Levels[i].Gammas.size();j++)
		{
			if(MinTalysCS<=Levels[i].Gammas[j].TalysCrossSection)
			{
				DrawLevel=true;
			}
		}
		if(Levels[i].Energy==0)
		{
			DrawLevel=true;
		}
		if(DrawLevel)
		{
			l.DrawLineNDC(0.2,Levels[i].Energy/k+a,0.7,Levels[i].Energy/k+a);
			t.DrawLatexNDC(0.1,Levels[i].Energy/k+a,TString::Format("%.1f",Levels[i].Energy));
			t.DrawLatexNDC(0.8,Levels[i].Energy/k+a,Levels[i].TalysJP.GetTLatex());
			l2.SetLineColor(LevelIterator%5+2);
			LevelIterator++;
			if(LevelIterator%5+2==5)
			LevelIterator++;
			
			for(unsigned int j=0;j<Levels[i].Gammas.size();j++)
			{
				if(MinTalysCS<=Levels[i].Gammas[j].TalysCrossSection)
				{
					/*l2.DrawLineNDC(Start+step,Levels[i].Energy/k+a,Start+step,(Levels[i].Energy-Levels[i].Gammas[j].Energy)/k+a);
					Start+=step;
					t2.DrawLatexNDC(Start+step,((Levels[i].Energy-Levels[i].Gammas[j].Energy/2)/k)+a,TString::Format("%.1f",Levels[i].Gammas[j].Energy));*/
					
					t2.DrawLatexNDC(Start+step,((Levels[i].Energy-Levels[i].Gammas[j].Energy/2)/k)+a,TString::Format("%.1f",Levels[i].Gammas[j].Energy));
					Start+=step;
					l2.DrawLineNDC(Start,Levels[i].Energy/k+a,Start,(Levels[i].Energy-Levels[i].Gammas[j].Energy)/k+a);
					//l2.SetLineWidth(2);
				}
				if(Start>=0.7)
				{
					Start=0.2;
				}
			}
		}
	}
}
void Nucleus::AssignPointers()
{
	LevelsFromTalys.resize(0);
	for(unsigned int i=0;i<Levels.size();i++)
	{
		Levels[i].fNucleus=this;
		Levels[i].AssignPointers();
		for(unsigned int j=0;j<Levels[i].Gammas.size();j++)
		{
			Levels[i].Gammas[j].FindFinalLevel();
		}
		if(Levels[i].GetOrigin()=="Talys")
		{
			LevelsFromTalys.push_back(&Levels[i]);
		}
		else
		{
			LevelsFromENSDF.push_back(&Levels[i]);
		}
	}
	for(unsigned int i=0;i<Products.size();i++)
	{
		Products[i].AssignPointers();
		Products[i].fMotherNucleus=this;
		Products[i].fTalysCalculation=fTalysCalculation;
	}
	OMPN.AssignPointers(this);
	OMPP.AssignPointers(this); 
	OMPN.SetDefaultOMP(OMPoptionN);
	OMPP.SetDefaultOMP(OMPoptionP);
	AssignDeformationsToLevels();
}
void Nucleus::AssignSimilarLevels(float Tolerancy)
{
	for(unsigned int i=0;i<Levels.size();i++)
	{
		for(unsigned int j=0;j<Levels.size();j++)
		{
			if(abs(Levels[i].GetEnergy()-Levels[j].GetEnergy()))
			{
				Levels[i].AddSimilarLevel(&Levels[j]);
			}
		}
	}
}
float Nucleus::GetMass()
{
	return GetNuclearMass(Name);
}
vector<GammaTransition*> Nucleus::GetGammaTransitions(string option,int BetterThan,float tolerancy,float intensity)
{
	/*опции:
	 * "Talys"-вывести только те линии, для которых есть результат в Talys
	 * "ENSDF"-вывести только те линии, для которых есть результат в ENSDF
	 * "All"-вывести все линии
	 * "not Talys"-все, кроме Talys
	 * "not ENSDF"-все, кроме ENSDF
	 */
	vector<GammaTransition*> result;
	for(unsigned int i=0;i<Levels.size();i++)
	{
		Levels[i].fNucleus=this;
		if(Levels[i].Mark<BetterThan)
		{
			for(unsigned int j=0;j<Levels[i].Gammas.size();j++)
			{
				bool AddFlag=false;
				Levels[i].Gammas[j].fLevel=&Levels[i];
				if(option=="Talys")
				{
					if(Levels[i].Gammas[j].TalysCrossSection>0)
					{
						AddFlag=true;
					}
				}
				if(option=="ENSDF")
				{
					if(Levels[i].Gammas[j].Origin=="ENSDF")
					{
						AddFlag=true;
					}
				}
				if(option=="not Talys")
				{
					if(Levels[i].Gammas[j].TalysCrossSection==0)
					{
						AddFlag=true;
					}
				}
				if(option=="not ENSDF")
				{
					if(Levels[i].Gammas[j].Origin!="ENSDF")
					{
						AddFlag=true;
					}
				}
				if(option=="All")
				{
					AddFlag=true;
				}
				if(AddFlag)
				{
					result.push_back(&Levels[i].Gammas[j]);
				}
			}
		}
	}
	for(unsigned int i=0;i<Products.size();i++)
	{
		vector <GammaTransition*> gt=Products[i].GetGammaTransitions(option,BetterThan,tolerancy,intensity);
		result.insert(end(result), begin(gt), end(gt));
	}
	for(unsigned int i=0;i<result.size();i++)
	{
		for(unsigned int j=0;j<i;j++)
		{
			if(result[i]->Energy<result[j]->Energy)
			{
				swap(result[i],result[j]);
			}
		}
	}
	return result;
}
/*const char *Nucleus::GetName()  const
{
	return Name.c_str();
}*/
void Nucleus::ErasePointers()
{
	for(unsigned int i=0;i<Levels.size();i++)
	{
		Levels[i].ErasePointers();
	}
	LevelsFromTalys.resize(0);
	LevelsFromENSDF.resize(0);
	fMotherNucleus=0;
	for(unsigned int i=0;i<Products.size();i++)
	{
		Products[i].ErasePointers();
	}
}
Nucleus* Nucleus::FindProductsByReaction(string reaction)
{
	for(unsigned int i=0;i<Products.size();i++)
	{
		if(Products[i].Reaction==reaction)
		{
			return &Products[i];
		}
	}
	return 0;
}
NucleusData Nucleus::ToNucleusData()
{
	NucleusData result=(NucleusData)(*this);
	for(unsigned int i=0;i<Levels.size();i++)
	{
		result.LevelsData.emplace_back(Levels[i].ToLevelData());
	}
	for(unsigned int i=0;i<Products.size();i++)
	{
		result.ProductsData.push_back(Products[i].ToNucleusData());
	}
	result.DefData=Def.ToDeformationData();
	result.OMPNData=OMPN.ToOpticalModelParametersData();
	result.OMPPData=OMPN.ToOpticalModelParametersData();
	return result;
}

void Nucleus::AssignDeformationsToLevels()
{
	for(unsigned int i=0;i<Levels.size();i++)
	{
		for(unsigned int j=0;j<Def.LevelDeformations.size();j++)
		{
			if(Levels[i].Number==Def.LevelDeformations[j].NumberOfLevel)
			{
				Levels[i].deformation=&Def.LevelDeformations[j];
				Def.LevelDeformations[j].fLevel=&Levels[i];
			}
		}
	}
}
void Nucleus::SetOMPOption(string Particle, int _OMPoption)
{
	if(Particle=="n")
	{
		OMPoptionN=_OMPoption;
		OMPN.SetDefaultOMP(OMPoptionN);
		WriteOMPOrUseKoningN=OMPoptionN;
		
	}
	if(Particle=="p")
	{
		OMPoptionP=_OMPoption;
		OMPP.SetDefaultOMP(OMPoptionP);
		WriteOMPOrUseKoningP=OMPoptionP;
	}
}
void Nucleus::SetTGraphNameAndTitle(string ValName)
{
	if(ValName=="Energy")
	{
		ValName="E";
	}
	/*if(ValName.find("Beta")!=string::npos())
	{
		ValName="B";
	}*/
	TotTalysV.SetName(TString::Format("Tot_%s",ValName.c_str()));
	TotTalysV.SetTitle(TString::Format("#sigma(tot);%s;#sigma,mb",ValName.c_str()));
	ElasticTotTalysV.SetName(TString::Format("TotEl_%s",ValName.c_str()));
	ElasticTotTalysV.SetTitle(TString::Format("#sigma_{el} total (%s);%s;#sigma,mb",ValName.c_str(),ValName.c_str()));
	ElasticDirectTalysV.SetName(TString::Format("DirEl_%s",ValName.c_str()));
	ElasticDirectTalysV.SetTitle(TString::Format("#sigma_{el} direct (%s);%s;#sigma,mb",ValName.c_str(),ValName.c_str()));
	ElasticCompoundTalysV.SetName(TString::Format("CompEl_%s",ValName.c_str()));
	ElasticCompoundTalysV.SetTitle(TString::Format("#sigma_{el} compound (%s);%s;#sigma,mb",ValName.c_str(),ValName.c_str()));
	InelasticTotTalysV.SetName(TString::Format("TotInl_%s",ValName.c_str()));
	InelasticTotTalysV.SetTitle(TString::Format("#sigma%s total (%s);%s;#sigma,mb",Reaction.c_str(),ValName.c_str(),ValName.c_str()));
	InelasticDirectTalysV.SetName(TString::Format("DirInl_%s",ValName.c_str()));
	InelasticDirectTalysV.SetTitle(TString::Format("#sigma%s direct (%s);%s;#sigma,mb",Reaction.c_str(),ValName.c_str(),ValName.c_str()));
	InelasticCompoundTalysV.SetName(TString::Format("CompInl_%s",ValName.c_str()));
	InelasticCompoundTalysV.SetTitle(TString::Format("#sigma%s compound (%s);%s;#sigma,mb",Reaction.c_str(),ValName.c_str(),ValName.c_str()));
	BNECS_gamma.SetName(TString::Format("BNECS_gamma_%s",ValName.c_str()));
	BNECS_gamma.SetTitle(TString::Format("BNE #sigma_#gamma(%s);%s;#sigma,mb",ValName.c_str(),ValName.c_str()));
	BNECS_neutron.SetName(TString::Format("BNECS_neutron_%s",ValName.c_str()));
	BNECS_neutron.SetTitle(TString::Format("BNE #sigma_n(%s);%s;#sigma,mb",ValName.c_str(),ValName.c_str()));
	BNECS_proton.SetName(TString::Format("BNECS_proton_%s",ValName.c_str()));
	BNECS_proton.SetTitle(TString::Format("BNE #sigma_p(%s);%s;#sigma,mb",ValName.c_str(),ValName.c_str()));
	BNECS_deuteron.SetName(TString::Format("BNECS_deuteron_%s",ValName.c_str()));
	BNECS_deuteron.SetTitle(TString::Format("BNE #sigma_d(%s);%s;#sigma,mb",ValName.c_str(),ValName.c_str()));
	BNECS_triton.SetName(TString::Format("BNECS_triton_%s",ValName.c_str()));
	BNECS_triton.SetTitle(TString::Format("BNE #sigma_t(%s);%s;#sigma,mb",ValName.c_str(),ValName.c_str()));
	BNECS_3He.SetName(TString::Format("BNECS_triton_%s",ValName.c_str()));
	BNECS_3He.SetTitle(TString::Format("BNE #sigma_#tau(%s);%s;#sigma,mb",ValName.c_str(),ValName.c_str()));
	BNECS_alpha.SetName(TString::Format("BNECS_alpha_%s",ValName.c_str()));
	BNECS_alpha.SetTitle(TString::Format("BNE #sigma_#alpha(%s);%s;#sigma,mb",ValName.c_str(),ValName.c_str()));
	TEISGraphTot.SetName(TString::Format("TEISTot_%s",ValName.c_str()));
	TEISGraphTot.SetTitle(TString::Format("TEIS #sigma_{tot}(%s);%s;#sigma,mb",ValName.c_str(),ValName.c_str()));
	TEISGraphCont.SetName(TString::Format("TEISCont_%s",ValName.c_str()));
	TEISGraphCont.SetTitle(TString::Format("TEIS #sigma_{cont}(%s);%s;#sigma,mb",ValName.c_str(),ValName.c_str()));
	TEISGraphDiscr.SetName(TString::Format("TEISDiscr_%s",ValName.c_str()));
	TEISGraphDiscr.SetTitle(TString::Format("TEIS #sigma_{discr}(%s);%s;#sigma,mb",ValName.c_str(),ValName.c_str()));
	for(unsigned int i=0;i<Levels.size();i++)
	{
		Levels[i].SetTGraphNameAndTitle(ValName);
	}
	for(unsigned int i=0;i<Products.size();i++)
	{
		Products[i].SetTGraphNameAndTitle(ValName);
	}
}
void Nucleus::AddPoint(double x_value,Nucleus* Nucl)
{
	if(!Nucl)
	return;
	if((Z!=Nucl->Z)||(A!=Nucl->A))
	return;
	int NPoints=ElasticTotTalysV.GetN();
	TotTalysV.SetPoint(NPoints,x_value,Nucl->TotTalys);
	ElasticTotTalysV.SetPoint(NPoints,x_value,Nucl->TotElastic);
	ElasticDirectTalysV.SetPoint(NPoints,x_value,Nucl->DirectElastic);
	ElasticCompoundTalysV.SetPoint(NPoints,x_value,Nucl->CompoundElastic);
	InelasticTotTalysV.SetPoint(NPoints,x_value,Nucl->TotInelastic);
	InelasticDirectTalysV.SetPoint(NPoints,x_value,Nucl->DirectInelastic);
	InelasticCompoundTalysV.SetPoint(NPoints,x_value,Nucl->CompoundInelastic);
	BNECS_gamma.SetPoint(NPoints,x_value,Nucl->BNECS_g);
	BNECS_neutron.SetPoint(NPoints,x_value,Nucl->BNECS_n);
	BNECS_proton.SetPoint(NPoints,x_value,Nucl->BNECS_p);
	BNECS_deuteron.SetPoint(NPoints,x_value,Nucl->BNECS_d);
	BNECS_triton.SetPoint(NPoints,x_value,Nucl->BNECS_t);
	BNECS_3He.SetPoint(NPoints,x_value,Nucl->BNECS_tau);
	BNECS_alpha.SetPoint(NPoints,x_value,Nucl->BNECS_a);
	TEISGraphTot.SetPoint(NPoints,x_value,Nucl->TEISTot);
	TEISGraphCont.SetPoint(NPoints,x_value,Nucl->TEISCont);
	TEISGraphDiscr.SetPoint(NPoints,x_value,Nucl->TEISDiscr);
	for(unsigned int i=0;i<Levels.size();i++)
	{
		for(unsigned int j=0;j<Nucl->Levels.size();j++)
		{
			Levels[i].AddPoint(x_value,&(Nucl->Levels[j]));
		}
	}
	for(unsigned int i=0;i<Products.size();i++)
	{
		for(unsigned int j=0;j<Nucl->Products.size();j++)
		{
			Products[i].AddPoint(x_value,&(Nucl->Products[j]));
		}
	}
}

void Nucleus::AddPoint(Nucleus* Nucl)
{
	if(!Nucl)
	return;
	if((Z!=Nucl->Z)||(A!=Nucl->A))
	return;
	
	TOTGamProdValues.push_back(Nucl->TOTGamProd);
	TOTNProdValues.push_back(Nucl->TOTNProd);
	TOTPProdValues.push_back(Nucl->TOTPProd);
	TOTDProdValues.push_back(Nucl->TOTDProd);
	TOTAProdValues.push_back(Nucl->TOTAProd);
	TOTTauProdValues.push_back(Nucl->TOTTauProd);
	TotElasticValues.push_back(Nucl->TotElastic);
	CompoundElasticValues.push_back(Nucl->CompoundElastic);
	DirectElasticValues.push_back(Nucl->DirectElastic);
	TotInelasticValues.push_back(Nucl->TotInelastic);
	CompoundInelasticValues.push_back(Nucl->CompoundInelastic);
	DirectInelasticValues.push_back(Nucl->DirectInelastic);
	TotTalysValues.push_back(Nucl->TotTalys);
	
	BNECS_g_Values.push_back(Nucl->BNECS_g);
	BNECS_n_Values.push_back(Nucl->BNECS_n);
	BNECS_p_Values.push_back(Nucl->BNECS_p);
	BNECS_d_Values.push_back(Nucl->BNECS_d);
	BNECS_t_Values.push_back(Nucl->BNECS_t);
	BNECS_tau_Values.push_back(Nucl->BNECS_tau);
	BNECS_a_Values.push_back(Nucl->BNECS_a);
	TEISTot_Values.push_back(Nucl->TEISTot);
	TEISCont_Values.push_back(Nucl->TEISCont);
	TEISDiscr_Values.push_back(Nucl->TEISDiscr);
	
	for(unsigned int i=0;i<Levels.size();i++)
	{
		for(unsigned int j=0;j<Nucl->Levels.size();j++)
		{
			Levels[i].AddPoint(&(Nucl->Levels[j]));
		}
	}
	for(unsigned int i=0;i<Products.size();i++)
	{
		for(unsigned int j=0;j<Nucl->Products.size();j++)
		{
			Products[i].AddPoint(&(Nucl->Products[j]));
		}
	}
}
void Nucleus::GenerateGraphs()
{
	if(EnergyGrid.size()==0)
	{
		return ;
	}
	TotTalysV=TGraph(EnergyGrid.size(),&EnergyGrid[0],&TotTalysValues[0]);
	ElasticTotTalysV=TGraph(EnergyGrid.size(),&EnergyGrid[0],&TotElasticValues[0]);
	ElasticDirectTalysV=TGraph(EnergyGrid.size(),&EnergyGrid[0],&DirectElasticValues[0]);
	ElasticCompoundTalysV=TGraph(EnergyGrid.size(),&EnergyGrid[0],&CompoundElasticValues[0]);
	InelasticTotTalysV=TGraph(EnergyGrid.size(),&EnergyGrid[0],&TotInelasticValues[0]);
	InelasticDirectTalysV=TGraph(EnergyGrid.size(),&EnergyGrid[0],&DirectInelasticValues[0]);
	InelasticCompoundTalysV=TGraph(EnergyGrid.size(),&EnergyGrid[0],&CompoundInelasticValues[0]);
	BNECS_gamma=TGraph(EnergyGrid.size(),&EnergyGrid[0],&BNECS_g_Values[0]);
	BNECS_neutron=TGraph(EnergyGrid.size(),&EnergyGrid[0],&BNECS_n_Values[0]);
	BNECS_proton=TGraph(EnergyGrid.size(),&EnergyGrid[0],&BNECS_p_Values[0]);
	BNECS_deuteron=TGraph(EnergyGrid.size(),&EnergyGrid[0],&BNECS_d_Values[0]);
	BNECS_triton=TGraph(EnergyGrid.size(),&EnergyGrid[0],&BNECS_t_Values[0]);
	BNECS_3He=TGraph(EnergyGrid.size(),&EnergyGrid[0],&BNECS_tau_Values[0]);
	BNECS_alpha=TGraph(EnergyGrid.size(),&EnergyGrid[0],&BNECS_a_Values[0]);
	TEISGraphTot=TGraph(EnergyGrid.size(),&EnergyGrid[0],&TEISTot_Values[0]);
	TEISGraphCont=TGraph(EnergyGrid.size(),&EnergyGrid[0],&TEISCont_Values[0]);
	TEISGraphDiscr=TGraph(EnergyGrid.size(),&EnergyGrid[0],&TEISDiscr_Values[0]);
}
void Nucleus::SetLevelDeformation(int LevelNumber,char LevT, int BandN, int BandL, int MagN, int NPhon, vector<float> *DefVec)
{
	Level *l=FindLevelByNumber(LevelNumber);
	#if OLD_VERSION!=1
	if(l)
	{
		l->SetDeformation(LevT,BandN,BandL,MagN,NPhon,DefVec);
	}
	else
	{
		if(TalysLibManager::Instance().IsEnableWarning())
		cout<<"Warning in Nucleus::SetLevelDeformation(...): level with number "<<LevelNumber<<" not found!\n";
	}
	#else
	Def.SetDeformation(l,LevT,BandN,BandL,MagN,NPhon,DefVec);
	#endif
}
void Nucleus::SetLevelDeformation(double LevelEnergy,char LevT, int BandN, int BandL,  int MagN,int NPhon, vector<float> *DefVec)
{
	Level *l=FindLevelByEnergy(LevelEnergy);
	#if OLD_VERSION!=1
	if(l)
	{
		l->SetDeformation(LevT,BandN,BandL,MagN,NPhon,DefVec);
	}
	else
	{
		if(TalysLibManager::Instance().IsEnableWarning())
		cout<<"Warning in Nucleus::SetLevelDeformation(...): level with energy "<<LevelEnergy<<" not found!\n";
	}
	#else
	Def.SetDeformation(l,LevT,BandN,BandL,MagN,NPhon,DefVec);
	#endif
}
Nucleus::~Nucleus()
{
	if((FastFlag)&&(FastCalculated))
	{
		system(string("rm -rf "+PathToCalculationDir).c_str());
	}
}	
Nucleus& Nucleus::Copy()
{
	Nucleus& result=*this;
	result.AssignPointers();
	result.OMPN.SetDefaultOMP(WriteOMPOrUseKoningN);
	result.OMPP.SetDefaultOMP(WriteOMPOrUseKoningN);
	return result;
}
void Nucleus::SaveToRootFile(TFile *f,string Addition)
{
	if(!f)
	{
		cout<<"This is Nucleus::SaveToRootFile() error: pointer to file is invalid! returned\n";
		return;
	}
	NucleusData ND=ToNucleusData();
	if(Addition.size()>0)
	{
		ND.Name+="_"+Addition;
	}
	f->WriteTObject(&ND);
}
void Nucleus::ReadFromRootFile(TFile *f,string _Name)
{
	if(!f)
	{
		cout<<"This is Nucleus::ReadFromRootFile() error: pointer to file is invalid! returned\n";
		return;
	}
	NucleusData *ND=(NucleusData*)f->Get(_Name.c_str());
	if(!ND)
	{
		cout<<"This is Nucleus::ReadFromRootFile() error: Nucleus object with name "<<Name<<"Does not exsists! returned\n";
		return ;
	}
	GetFromNucleusData(*ND);
	TString ts(Name.c_str());
	ts.ReplaceAll("_"," ");
	stringstream s(ts.Data());
	s>>Name;
	
}
void Nucleus::ReadFromRootFile(string FileName,string _Name)
{
	TFile f(FileName.c_str());
	ReadFromRootFile(&f,_Name);
}
void PrintDeformationToXLSX(TXlsxwriter &xlsx,LevelDeformation *df)
{
	xlsx<<df->fLevel->Energy<<df->fLevel->TalysJP.GetLine()<<df->fLevel->fNucleus->Name<<df->TypeOfLevel<<df->fLevel->fNucleus->Def.TypeOfCollectivity<<df->NumberOfBand<<df->LOfBand<<df->NumberOfPhonons<<df->MagneticNumber;
	for(unsigned int j=0;j<df->Beta.size();j++)
	{
		xlsx<<df->Beta[j];
	}
	xlsx<<"\n";
}
void PrintOMPToXLSX(TXlsxwriter &xlsx,OpticalModelParameters *OMP)
{
	if(!OMP->DefaultOMP)
	{
		xlsx<<"No user-defined OMP type";
		xlsx<<"Talys default";
		if(OMP->Koning)
		{
			xlsx<<"Koning";
		}
		else
		{
			xlsx<<"PredefSTD";
		}
	}
	else
	{
		xlsx<<"Used:"<<OMP->DefaultOMP->HRPotentialType;
	}
	xlsx<<"\n";
	xlsx<<" "<<"Vv"<<"Wv"<<"Rv"<<"Av"<<"Wd"<<"Rd"<<"Ad"<<"Vso"<<"Wso"<<"Rso"<<"Aso"<<"Rc"<<"Vc"<<"\n";
	if(OMP->Potential.ReadFlag)
	{
		OMP->Potential.EvalPotential();
		xlsx<<"PredefSTD"<<OMP->Potential.Vv<<OMP->Potential.Wv<<OMP->Potential.Rv<<OMP->Potential.Av<<OMP->Potential.Wd<<OMP->Potential.Rd<<OMP->Potential.Ad<<OMP->Potential.Vso<<OMP->Potential.Wso<<OMP->Potential.Rso<<OMP->Potential.Aso<<OMP->Potential.Rc<<OMP->Potential.Vc<<"\n";
	}
	OMP->PotentialKoning.EvalPotential();
	xlsx<<"PotentialKoning"<<OMP->PotentialKoning.Vv<<OMP->PotentialKoning.Wv<<OMP->PotentialKoning.Rv<<OMP->PotentialKoning.Av<<OMP->PotentialKoning.Wd<<OMP->PotentialKoning.Rd<<OMP->PotentialKoning.Ad<<OMP->PotentialKoning.Vso<<OMP->PotentialKoning.Wso<<OMP->PotentialKoning.Rso<<OMP->PotentialKoning.Aso<<OMP->PotentialKoning.Rc<<OMP->PotentialKoning.Vc<<"\n";
	xlsx<<"\n";
	xlsx<<"Energy-dependent coefficients"<<"\n";
	xlsx<<" "<<"v1"<<"v2"<<"v3"<<"v4"<<"w1"<<"w2"<<"d1"<<"d2"<<"d3"<<"vso1"<<"vso2"<<"wso1"<<"wso2"<<"\n";
	if(OMP->Potential.ReadFlag)
	{
		xlsx<<"PredefSTD"<<OMP->Potential.v1<<OMP->Potential.v2<<OMP->Potential.v3<<OMP->Potential.v4<<OMP->Potential.w1<<OMP->Potential.w2<<OMP->Potential.d1<<OMP->Potential.d2<<OMP->Potential.d3<<OMP->Potential.vso1<<OMP->Potential.vso2<<OMP->Potential.wso1<<OMP->Potential.wso2<<"\n";
	}
	xlsx<<"Koning"<<OMP->PotentialKoning.v1<<OMP->PotentialKoning.v2<<OMP->PotentialKoning.v3<<OMP->PotentialKoning.v4<<OMP->PotentialKoning.w1<<OMP->PotentialKoning.w2<<OMP->PotentialKoning.d1<<OMP->PotentialKoning.d2<<OMP->PotentialKoning.d3<<OMP->PotentialKoning.vso1<<OMP->PotentialKoning.vso2<<OMP->PotentialKoning.wso1<<OMP->PotentialKoning.wso2<<"\n";
	xlsx<<"\n";
}
void Nucleus::SaveToXLSX(string filename)
{
	TXlsxwriter xlsx;
	xlsx.Open(filename);
	xlsx.GoToWorksheet("General");
	xlsx<<"Nucleus"<<Name<<"\n";
	xlsx<<"A"<<A<<"\n";
	xlsx<<"Z"<<Z<<"\n";
	xlsx<<"N"<<A-Z<<"\n";
	xlsx<<"Mass,MeV"<<Mass<<"\n";
	xlsx<<"Abundance"<<Abundance<<"\n";
	xlsx<<"Projectile"<<Projectile<<"\n";
	xlsx<<"ProjectileEnergy"<<ProjectileEnergy<<"In CM:"<<ProjectileEnergyCM<<"\n";
	xlsx<<"\n";
	for(unsigned int i=0;i<Products.size();i++)
	{
		xlsx<<"Product:"<<Products[i].Name<<"Reaction"<<Products[i].Reaction<<"\n";
		xlsx<<"A"<<Products[i].A<<"\n";
		xlsx<<"Z"<<Products[i].Z<<"\n";
		xlsx<<"N"<<Products[i].A-Products[i].Z<<"\n";
		xlsx<<"Mass,MeV"<<Products[i].Mass<<"\n";
		xlsx<<"NLevels"<<Products[i].Levels.size()<<"\n";
		xlsx<<"\n";
	}
	xlsx.GoToWorksheet("Gammas");
	vector<GammaTransition*> gs=GetGammaTransitions();
	xlsx<<"E_gamma"<<"E_i"<<"JPi"<<"E_f"<<"JPf"<<"Target"<<"Reaction"<<"Product"<<"CS"<<"\n";
	for(unsigned int i=0;i<gs.size();i++)
	{
		xlsx<<gs[i]->Energy<<gs[i]->TalysE_i<<gs[i]->TalysJP_i.GetLine()<<gs[i]->TalysE_f<<gs[i]->TalysJP_f.GetLine()<<gs[i]->fLevel->fNucleus->fMotherNucleus->Name<<gs[i]->fLevel->fNucleus->Reaction<<gs[i]->fLevel->fNucleus->Name<<gs[i]->TalysCrossSection<<"\n";
	}
	xlsx.GoToWorksheet("LevelExcitationCS");
	xlsx<<"E_level"<<"JP"<<"Nucleus"<<"CSCompound"<<"CSDirect"<<"CSTotal"<<"\n";
	for(unsigned int i=0;i<Products.size();i++)
	{
		for(unsigned int j=0;j<Products[i].Levels.size();j++)
		{
			Level* l=&(Products[i].Levels[j]);
			if((l->TalysCS>0)||(l->Energy==0))
			{
				xlsx<<l->Energy<<l->TalysJP.GetLine()<<l->fNucleus->Name<<l->TalysCSCompound<<l->TalysCSDirect<<l->TalysCS<<"\n";
			}
			
		}
		xlsx<<"\n";
	}
	xlsx.GoToWorksheet("Deformations");
	xlsx<<"E_level"<<"JP"<<"Nucleus"<<"LevelType"<<"CollType"<<"BandNo"<<"BandL"<<"NumberOfPhonons"<<"MagN"<<"Beta"<<"\n";
	for(unsigned int i=0;i<Levels.size();i++)
	{
		if(Levels[i].deformation!=0)
		{
			LevelDeformation* df=Levels[i].deformation;
			PrintDeformationToXLSX(xlsx,df);
		}
	}
	xlsx<<"\n";
	xlsx<<"Products"<<"\n";
	for(unsigned int i=0;i<Products.size();i++)
	{
		for(unsigned int j=0;j<Products[i].Levels.size();j++)
		{
			if(Products[i].Levels[j].deformation!=0)
			{
				LevelDeformation* df=Products[i].Levels[j].deformation;
				PrintDeformationToXLSX(xlsx,df);
			}
		}
		xlsx<<"\n";
	}
	xlsx.GoToWorksheet("OMP(N)");
	xlsx<<"Target"<<Name<<"\n";
	PrintOMPToXLSX(xlsx,&OMPN);
	xlsx<<"Products"<<"\n";
	for(unsigned int i=0;i<Products.size();i++)
	{
		xlsx<<Products[i].Name<<"\n";
		PrintOMPToXLSX(xlsx,&(Products[i].OMPN));
		xlsx<<"\n";
	}
	xlsx.GoToWorksheet("OMP(P)");
	xlsx<<"Target"<<Name<<"\n";
	PrintOMPToXLSX(xlsx,&OMPP);
	xlsx<<"Products"<<"\n";
	for(unsigned int i=0;i<Products.size();i++)
	{
		xlsx<<Products[i].Name<<"\n";
		PrintOMPToXLSX(xlsx,&(Products[i].OMPP));
	}
	xlsx.GoToWorksheet("ParticleProduction");
	xlsx<<" "<<"1"<<"Total"<<"\n";
	xlsx<<"gamma"<<BNECS_g<<TOTGamProd<<"\n";
	xlsx<<"neutron"<<BNECS_n<<TOTNProd<<"\n";
	xlsx<<"proton"<<BNECS_p<<TOTPProd<<"\n";
	xlsx<<"deutron"<<BNECS_d<<TOTDProd<<"\n";
	xlsx<<"3He"<<BNECS_tau<<TOTTauProd<<"\n";
	xlsx<<"alpha"<<BNECS_a<<TOTAProd<<"\n";
	xlsx<<"Cross-sections"<<"\n";
	xlsx<<"Total"<<TotTalys<<"\n";
	xlsx<<"Total elastic"<<TotElastic<<"\n";
	xlsx<<"Shape elastic"<<DirectElastic<<"\n";
	xlsx<<"Compound elastic"<<CompoundElastic<<"\n"<<"\n";
	xlsx<<"Reaction CS"<<"\n";
	for(unsigned int i=0;i<Products.size();i++)
	{
		
		xlsx<<Products[i].Reaction<<Products[i].Name<<"\n";
		xlsx<<"Total"<<Products[i].TotInelastic<<"\n";
		xlsx<<"Direct"<<Products[i].DirectInelastic<<"\n";
		xlsx<<"Compound"<<Products[i].CompoundInelastic<<"\n";
	}
	

}
