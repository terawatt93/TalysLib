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
#include "OMP.cc"
#include "Deformations.cc"
#include "GammaTransitions.cc"
#include "LevelProperties.cc"

#pragma once

//Методы класса Nucleus
Nucleus::Nucleus(NucleusData ND)
{
	Name=ND.Name; Reaction=ND.Reaction;
	A=ND.A; Z=ND.Z;
	Abundance=ND.Abundance;
	OMPN.Nuclide=this;
	OMPP.Nuclide=this;
	OMPN.ReadOMP("n");
	OMPP.ReadOMP("p");
	AssignPointers();
	for(unsigned int i=0;i<ND.LevelsData.size();i++)
	{
		Levels.emplace_back(ND.LevelsData[i]);
	}
	for(unsigned int i=0;i<ND.ProductsData.size();i++)
	{
		Products.emplace_back(ND.ProductsData[i]);
	}	
	Def.SetZA(Z,A);
	Def.ReadDeformation();
	AssignDeformationsToLevels();
	AssignPointers();
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
	this->Name=Name;
	this->Reaction=Reaction;
	GetAZ(Name,Z,A);
	TalysCalculated=false;
	fMotherNucleus=0;
	Abundance=GetAbundance(Name);
	ReadLevelsFromTalysDatabase();
	AssignPointers();
	Def.SetZA(Z,A);
	Def.ReadDeformation();
	AssignDeformationsToLevels();
	OMPN.Nuclide=this;
	OMPP.Nuclide=this;
	OMPN.ReadOMP("n");
	OMPP.ReadOMP("p");
	AssignPointers();
}
void Nucleus::SetProjectileEnergy(double E)
{
	ProjectileEnergy=E;
}
void Nucleus::ExecuteCalculationInTalys(string _Projectile)
{
	Projectile=_Projectile;
	string PathToCalculationDir=GetPathToTalysData()+"/CalculationResults/";
	if(FastFlag)
	{
		PathToCalculationDir="/dev/shm/CalculationResults/";
		system("mkdir /dev/shm/CalculationResults");
		FastCalculated=true;
	}
	mkdir((PathToCalculationDir+Name).c_str(),S_IRWXU);
	string filename=PathToCalculationDir+Name+"/input";
	ofstream ofs(filename.c_str());
	string ShellScript;
	ShellScript="#/bin/bash \n cd "+PathToCalculationDir+Name+"\n talys <input >output";//адский костыль!
	ofstream ofs_shell("run_talys.sh");
	ofs_shell<<ShellScript<<"\n";
	ofs_shell.close();
	system("chmod 777 run_talys.sh");
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
	system("./run_talys.sh");
}

void Nucleus::SortingLevels()
{
	if(Levels.size()<2)
	{
		return;
	}
	for(unsigned int i=0;i<Levels.size()-1;i++)
	{
		for (int j = 0; j <Levels.size()-i-1; j++)
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
	
	string filename=GetPathToTalysData();
	if(FastFlag)
	{
		filename="/dev/shm";
	}
	if(fMotherNucleus)
	{
		filename+="/CalculationResults/"+fMotherNucleus->Name+"/output";
	}
	else
	{
		filename+="/CalculationResults/"+Name+"/output";
	}
	ifstream ifs(filename.c_str());
	string line;
	bool read_flag=false;
	
	//сбросим данные для уровней
	for(unsigned int i=0;i<Levels.size();i++)
	{
		Levels[i].ADTot.resize(0);
		Levels[i].ADDirect.resize(0);
		Levels[i].ADCompound.resize(0);
		Levels[i].Angle.resize(0);
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
	string filename=GetPathToTalysData();

	if(fMotherNucleus)
	{
		if(fMotherNucleus->FastFlag)
		{
			filename="/dev/shm";
		}
		filename+="/CalculationResults/"+fMotherNucleus->Name+"/output";
	}
	else
	{
		if(FastFlag)
		{
			filename="/dev/shm";
		}
		filename+="/CalculationResults/"+Name+"/output";
	}
	ifstream ifs(filename.c_str());
	bool ElasticFlag=false;
	string ElasticMark="Elastic scattering angular distribution";
	float LastAngle=-1;
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
				s>>tmp>>tmp>>TOTDProd;
			}
			if((int)line.find("alpha   =")>-1)
			{
				string tmp;
				s>>tmp>>tmp>>TOTAProd;
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
			cout<<line<<"\n";
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
		if((!PlottedADist)||(option=="new"))
		{
			//ElacticTotTalys, ElasticDirectTalys,ElasticCompoundTalys; Angle, ElTot, ElCompound, ElDirect;
			ElacticTotTalys=TGraph(Angle.size(), &Angle[0], &ElTot[0]);
			ElasticCompoundTalys=TGraph(Angle.size(), &Angle[0], &ElCompound[0]);
			ElasticDirectTalys=TGraph(Angle.size(), &Angle[0], &ElDirect[0]);
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

void Nucleus::GenerateProducts(string _Projectile)
{
	Products.resize(0);
	Projectile=_Projectile;
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
void Nucleus::GenerateGammaSpectrum(TH1F *Spectrum, TF1* ResolutionFunction, int NEntries)
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
	
	int iterator=0;
	TH1F h("h","h",10000,0,10000);
	
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
	TText t;
	TText t2;
	t.DrawTextNDC(0.5,0.05,Name.c_str());
	t.SetTextSize(0.02);
	t2.SetTextSize(0.02);
	t2.SetTextSize(0.02);
	t2.SetTextAngle(90);
	double step=0.02;
	double Start=0.2;
	int LevelIterator=0;
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
			t.DrawTextNDC(0.1,Levels[i].Energy/k+a,TString::Format("%.1f",Levels[i].Energy));
			t.DrawTextNDC(0.8,Levels[i].Energy/k+a,Levels[i].JP.c_str());
			l2.SetLineColor(LevelIterator%5+2);
			LevelIterator++;
			if(LevelIterator%5+2==5)
			LevelIterator++;
			
			for(unsigned int j=0;j<Levels[i].Gammas.size();j++)
			{
				if(MinTalysCS<=Levels[i].Gammas[j].TalysCrossSection)
				{
					l2.DrawLineNDC(Start+step,Levels[i].Energy/k+a,Start+step,(Levels[i].Energy-Levels[i].Gammas[j].Energy)/k+a);
					Start+=step;
					t2.DrawTextNDC(Start+step,((Levels[i].Energy-Levels[i].Gammas[j].Energy/2)/k)+a,TString::Format("%.1f",Levels[i].Gammas[j].Energy));
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
	}
	OMPN.Nuclide=this;
	OMPP.Nuclide=this; 
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
void Nucleus::SetLevelDeformation(int LevelNumber,char LevT, int BandN, int BandL, int NPhon, int MagN, vector<float> *DefVec)
{
	Level *l=FindLevelByNumber(LevelNumber);
	#if OLD_VERSION!=1
	if(l)
	{
		l->SetDeformation(LevT,BandN,BandL,NPhon,MagN,DefVec);
	}
	else
	{
		cout<<"Warning in Nucleus::SetLevelDeformation(...): level with number "<<LevelNumber<<" not found!\n";
	}
	#else
	Def.SetDeformation(l,LevT,BandN,BandL,NPhon,MagN,DefVec);
	#endif
}
void Nucleus::SetLevelDeformation(double LevelEnergy,char LevT, int BandN, int BandL, int NPhon, int MagN, vector<float> *DefVec)
{
	Level *l=FindLevelByEnergy(LevelEnergy);
	#if OLD_VERSION!=1
	if(l)
	{
		l->SetDeformation(LevT,BandN,BandL,NPhon,MagN,DefVec);
	}
	else
	{
		cout<<"Warning in Nucleus::SetLevelDeformation(...): level with energy "<<LevelEnergy<<" not found!\n";
	}
	#else
	Def.SetDeformation(l,LevT,BandN,BandL,NPhon,MagN,DefVec);
	#endif
}
Nucleus::~Nucleus()
{
	if((FastFlag)&&(FastCalculated))
	{
		system("rm -rf /dev/shm/CalculationResults/");
	}
}	
