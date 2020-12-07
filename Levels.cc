#include "Levels.hh"
#include <sys/stat.h>
#include <bits/stdc++.h>
#include <cstring>
#include <algorithm>
#include <cctype>
#include "Parser.cpp"
#include <TLine.h>
#include <TText.h>
#include <TList.h>
#include <TKey.h>
//Методы класса SpinParity

SpinParity::SpinParity(float J_in, int Parity_in)
{
	J=J_in;
	Parity=Parity_in;
}
SpinParity::SpinParity(float J_in)
{
	J=abs(J_in);
	Parity=sgn(J_in);
}
SpinParity::SpinParity(string str)
{
	if(str[str.size()-1]=='+')
	{
		Parity=1;
	}
	else if(str[str.size()-1]=='-')
	{
		Parity=-1;
	}
	J=abs(atof(str.substr(0,str.size()-1).c_str()));
}
string SpinParity::GetLine()
{
	string s;
	stringstream ss;
	ss<<*this;
	ss>>s;
	return s;
}
/*SpinParity::SpinParity()
{
	J=0;
	Parity=0;
}*/

std::istream& operator >> (std::istream &istr,SpinParity &JP)
{
	int Parity=0;
	string str;
	istr>>str;
	JP=SpinParity(str);
	return istr;
}
std::ostream& operator << (std::ostream &ostr,SpinParity &JP)
{
	ostr<<JP.J;
	if(JP.Parity<0)
	{
		ostr<<"-";
	}
	else
	{
		ostr<<"+";
	}
	return ostr;
}

bool operator == (const SpinParity &JP1, const SpinParity &JP2)
{
	if((JP1.J==JP2.J)&&(JP1.Parity==JP2.Parity))
	{
		return true;
	}
	return false;
}

float abs(SpinParity JP)
{
	return abs(JP);
}

vector<SpinParity> ENSDFJPToNormalJP(string JP, int &Mark)
{
	vector<SpinParity> result;
	int sign=0;
	if(((int)JP.find("+"))>0)
	{
		sign=1;
	}
	if(((int)JP.find("-"))>0)
	{
		sign=-1;
	}
	if(((int)JP.find("TO"))>0)
	{
		stringstream s(JP);
		float low,up;
		string tmp1,tmp2,tmp3;
		s>>tmp1>>tmp2>>tmp3;
		low=atof(tmp1.c_str());
		up=atof(tmp3.c_str());
		float value=low;
		while(value<=up)
		{
			result.push_back(SpinParity(value,sign));
			value+=1;
		}
		Mark=result.size()*2;
		return result;
	}
	
	if(sign!=0)
	{
		string num_str;
		for(unsigned int i=0;i<JP.size();i++)
		{
			
			if(((JP[i]>='0')&&(JP[i]<='9'))||(JP[i]=='/'))
			{
				num_str+=JP[i];
			}
			if(JP[i]==',')
			{
				float value=0;
				int slash_position=(int)num_str.find("/");
				if(slash_position>0)
				{
					value=atof(num_str.substr(0,slash_position).c_str())/atof(num_str.substr(slash_position+1,num_str.size()-1).c_str());
				}
				else
				{
					value=atof(num_str.c_str());
				}
				result.push_back(SpinParity(value,sign));
				num_str.resize(0);
			}
		}
		float value=0;
		int slash_position=(int)num_str.find("/");
		if(slash_position>0)
		{
			value=atof(num_str.substr(0,slash_position).c_str())/atof(num_str.substr(slash_position+1,num_str.size()-1).c_str());
		}
		else
		{
			value=atof(num_str.c_str());
		}
		result.push_back(SpinParity(value,sign));
		
	}
	Mark=result.size();
	if(((int)JP.find("("))>=0)
	{
		Mark=2*result.size();
	}
	if(sign==0)
	{
		Mark=99;
	}
	return result;
}

vector<SpinParity> GenerateGammaMultipolarity(SpinParity &JPi,SpinParity &JPf)
{
	vector<double> J=QuantumSum(JPi.J,JPf.J);
	vector<SpinParity> result;
	for(unsigned int i=0;i<J.size();i++)
	{
		result.emplace_back(J[i],JPi.Parity*JPf.Parity);
	}
	return result;
}

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
		Rv=1.3039 - 0.4054*pow(A,-1/3);
		Av=0.6778 - 1.487e-4*A;
		Rd=1.3424 - 0.01585*pow(A,1/3);
		Ad=0.5446 - 1.656e-4*A;
		Rso=1.1854 - 0.647*pow(A,-1/3);
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
		Rc=1.198 + 0.697*pow(A,-2/3) + 12.994*pow(A,-5/3);
		Rv=1.3039 - 0.4054*pow(A,-1/3);
		Av=0.6778 - 1.487e-4*A;
		Rd=1.3424 - 0.01585*pow(A,1/3);
		Ad=0.5187 + 5.205e-4*A;
		Rso=1.1854 - 0.647*pow(A,-1/3);
		Vc=1.73*Z*pow(A,-1.0/3)/Rc;
	}
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


//Методы класса GammaTransition
GammaTransition::GammaTransition(GammaTransitionData d)
{
	Energy=d.Energy; EnergyErr=d.EnergyErr; Intensity=d.Intensity; CrossSection=d.CrossSection; E_in=d.E_in; Tolerancy=d.Tolerancy;
	Rel_Cs=d.Rel_Cs; TalysCrossSection=d.TalysCrossSection; TalysE_i=d.TalysE_i; TalysE_f=d.TalysE_f;
	TalysJP_i=d.TalysJP_i; TalysJP_f=d.TalysJP_f;
	TalysMultipolarity=d.TalysMultipolarity;
	Multipolarity=d.Multipolarity; nuclide=d.nuclide; reaction=d.reaction;
}
bool GammaTransition::ReadTransition(string line,string ReadNuclName, float E_in)
{
	this->E_in=E_in;
	//123SB G 381.4 4 100 8 [M1] 0.0170
	string nuclide; string type;
	stringstream s(line);
	s>>nuclide>>type;
	if(type=="G")
	{
		if(ReadNuclName==nuclide)
		{
			Energy=atof(line.substr(9,9).c_str());
			EnergyErr=atof(line.substr(19,1).c_str());
			Intensity=atof(line.substr(21,7).c_str());
			Multipolarity=line.substr(31,9);
			if(Intensity>100)
			{
				Intensity=0;
			}
			Origin="ENSDF";
			return true;
		}
		return false;
	}
	else
	{
		return false;
	}
}
string GammaTransition::GetLine(string option)
{
	if(Multipolarity=="")
	{
		Multipolarity="unknown";
	}
	if(option=="brief")
	{
		return (to_string(Energy)+" "+to_string(Intensity)+" "+to_string(CrossSection)+" "+to_string(TalysCrossSection));
	}
	if(option=="full")
	{
		string result;
		result=to_string(Energy)+" "+to_string(TalysCrossSection)+" "+fLevel->fNucleus->fMotherNucleus->Name+fLevel->fNucleus->Reaction+fLevel->fNucleus->Name+" "+to_string(TalysE_i)+"("+TalysJP_i.GetLine()+"->"+TalysJP_f.GetLine()+")"+to_string(TalysE_f);
		return result;
	}
	return ("E:"+to_string(Energy)+" Mult:"+Multipolarity+"Int:"+to_string(Intensity)+" CS:"+to_string(CrossSection)+" Talys:"+to_string(TalysCrossSection));
}
bool GammaTransition::CheckEnergy(float E,float Tolerancy,float intensity)
{
	this->Tolerancy=Tolerancy;
	if((abs(Energy-E)<=Tolerancy)&&((Intensity>intensity)||(Intensity==0)))
	{
		return true;
	}
	return false;
}
const char *GammaTransition::GetName()  const
{
//	return ("line_"+to_string(Energy)).c_str();
	string Name("line_"+TString::Format("%.2f",Energy));
	return Name.c_str();
}

void GammaTransition::SetInformationExtractedFromTalys(float TalysE_f, float TalysE_i, SpinParity JP_f, SpinParity JP_i)
{
	this->TalysE_f=TalysE_f;
	this->TalysE_i=TalysE_i;
	this->TalysJP_f=JP_f;
	this->TalysJP_i=JP_i;
}
double GammaTransition::GetEnergy()
{
	return Energy;
}
void GammaTransition::FindFinalLevel(double Tolerancy)
{
	if(!fLevel)
	{
		return ;
	}
	
	if(Origin=="Talys")
	{
		if(fLevel->fNucleus)
		{
			for(unsigned int i=0;i<fLevel->fNucleus->Levels.size();i++)
			{
				if((fLevel->fNucleus->Levels[i].Origin=="Talys")||(fLevel->fNucleus->Levels[i].Energy==0))
				{
					if(fLevel->Energy>fLevel->fNucleus->Levels[i].Energy)
					{
						//cout<<"This is GammaTransition::FindFinalLevel("<<Tolerancy<<")\n";
						//cout<<"fLevel->Energy="<<fLevel->Energy<<" fNucleus->Levels[i].Energy="<<fLevel->fNucleus->Levels[i].Energy<<" Energy="<<Energy<<" abs="<<abs(fLevel->Energy-fLevel->fNucleus->Levels[i].Energy-Energy)<<"\n";
						double E_distance=fLevel->Energy-fLevel->fNucleus->Levels[i].Energy;
						if(abs(E_distance-Energy)<Tolerancy)
						{
							fFinalLevel=&(fLevel->fNucleus->Levels[i]);
							//cout<<"Final level found!\n";
							return;
						}
					}
				}
			}
		}
	}
	
	/*
	if(TalysCrossSection>10e-3)
	{
		fFinalLevel=0;
		if(fLevel->JP_values.size()>0)
		{
			fLevel->JP_values[0]=TalysJP_i;
		}
		else
		{
			fLevel->JP_values.push_back(TalysJP_i);
		}		
		if(fLevel->fNucleus)
		{
			Nucleus *Nucl=fLevel->fNucleus;
			for(unsigned int i=0;i<Nucl->LevelsFromTalys.size();i++)
			{
				if(fLevel->GetOrigin()=="Talys")
				{
					if(abs(fLevel->GetEnergy()-Nucl->LevelsFromTalys[i]->GetEnergy())<1)
					{
						fFinalLevel=Nucl->LevelsFromTalys[i];
						fFinalLevel->JP_values[0]=TalysJP_f;
						return ;
					}
				}
			}
			
			
			for(unsigned int i=0;i<Nucl->LevelsFromENSDF.size();i++)
			{
				if((abs(Nucl->LevelsFromENSDF[i]->GetEnergy()-Energy)<Tolerancy)&&(Nucl->Levels[i].GetJPValues().size()>0))
				{
					fFinalLevel=Nucl->LevelsFromENSDF[i];
				}
			}
		}
		if(fFinalLevel)
		{
			fFinalLevel->JP_values[0]=TalysJP_f;
		}
	}
	else
	{
		if(fLevel->fNucleus)
		{
			Nucleus *Nucl=fLevel->fNucleus;
			double E_final=fLevel->Energy-Energy;
			cout<<Energy<<" "<<E_final<<" "<<fLevel->JP_values.size()<<"\n";
			fFinalLevel=0;
			unsigned int iterator=0;
			while((!fFinalLevel)&&(iterator<fLevel->JP_values.size()))
			{
				fFinalLevel=Nucl->FindBestLevelByEJP(Energy,fLevel->JP_values[iterator],3);
				iterator++;
			}
		}
	}*/
}

void GammaTransition::ErasePointers()
{
	fLevel=0;
	fFinalLevel=0;
}
void GammaTransition::SetTGraphNameAndTitle(string ValName)
{
	if(ValName=="Energy")
	{
		ValName="E";
	}
	if(ValName=="Beta")
	{
		ValName="B";
	}
	CSGraph.SetName(("GTCS_"+ValName).c_str());
	CSGraph.SetTitle(TString::Format("#sigma_{#gamma}(%s),E_{#gamma}=%.1f;%s;#sigma,mb",ValName.c_str(),Energy,ValName.c_str()));
}
void GammaTransition::AddPoint(double x_value, double y_value)
{
	int N=CSGraph.GetN();
	CSGraph.SetPoint(N,x_value,y_value);
}
void GammaTransition::AddPoint(double x_value, GammaTransition *g)
{
	if(!g)
	return;
	if((g->InitLevelNumber==InitLevelNumber)&&(g->FinalLevelNumber==FinalLevelNumber))
	{
		AddPoint(x_value,g->TalysCrossSection);
	}
}
TGraph* GammaTransition::GetCSGraph()
{
	return &CSGraph;
}
//Методы класса LevelDeformation
void LevelDeformation::GetFromString(string input)
{
	
	string NumOfLevelS=input.substr(0,4);
	string TypeOfLevelS=input.substr(7,1);
	string NumberOfBandS=input.substr(8,4);
	NumberOfBand=0; NumberOfLevel=0; LOfBand=0; NumberOfPhonons=0; MagneticNumber=0;
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
		LOfBand=atoi(LOfBandS.c_str());
		NumberOfPhonons=atoi(NumberOfPhononsS.c_str());
		MagneticNumber=atoi(MagneticNumberS.c_str());
		//cout<<"NBand:"<<NumberOfBand<<" L:"<<LOfBand<<" NF:"<<NumberOfPhonons<<" Mag:"<<MagneticNumber<<" Type:"<<TypeOfLevel<<" ";
		/*for(unsigned int i=0;i<Beta.size();i++)
		{
			cout<<"B"<<i+2<<" "<<Beta[i]<<"\n";
		}*/
	}
	TypeOfLevel=TypeOfLevelS[0];
	NumberOfLevel=atoi(NumOfLevelS.c_str());
	NumberOfBand=atoi(NumberOfBandS.c_str());
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
	if(value>0)
	{
		return TString::Format("%4i",value);
	}
	return "    ";
}
TString GenerateLevelDefString(int LevN, char LevT, int BandN=-1, int BandL=-1, int NPhon=-1, int MagN=-1, vector<float> *Def=0)
{
	TString result=TString::Format("%4i   %c",LevN,LevT);
	result+=(Add4IValue(BandN)+Add4IValue(BandL)+Add4IValue(NPhon)+Add4IValue(MagN));
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
//Методы класса Deformation
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
		cout<<"Warning: deformation file for "<<GetNucleusName(Z)<<" does not exsists!\n";
	}
	string line;
	while(getline(ifs,line))
	{
		int _Z, _A, Nlevels;
		sscanf(line.c_str(),"%4d%4d%4d   %c   %c",&_Z,&_A,&Nlevels,&TypeOfCollectivity,&TypeOfDeformation);
		if(_Z==Z&&_A==A)
		{
			PointToPastChangedDeformation=ContentOfFile.size();
			NLevels=Nlevels;
			for(unsigned int i=0;i<Nlevels;i++)
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
void Deformation::WriteDeformation()
{
	string Filename=GetPathToTalysData()+"/structure/deformation/"+GetNucleusName(Z)+".def";
	ifstream ifs(Filename.c_str());
	if(ifs.good())
	{
		TDatime t;
		string NewFileName=GetPathToTalysData()+"/CalculationResults/"+to_string(t.Get())+"_"+GetNucleusName(Z)+".def";
		system(("mv "+Filename+" "+NewFileName).c_str());
		ifs.close();
	}
	ofstream ofs(Filename.c_str());
	bool IsDeformationWritten=false;
	for(unsigned int i=0;i<PointToPastChangedDeformation;i++)
	{
		ofs<<ContentOfFile[i]<<"\n";
	}
	NLevels=LevelDeformations.size();
	//ofs<<TString::Format("%4d%4d%4d   %c   %c",Z,A,NLevels,TypeOfCollectivity,TypeOfDeformation)<<"\n";
	ofs<<GenerateMainDefString(Z,A,NLevels,TypeOfCollectivity,TypeOfDeformation)<<"\n";
	for(unsigned int i=0;i<LevelDeformations.size();i++)
	{
		ofs<<LevelDeformations[i].GenerateStringForDefFile()<<"\n";
	}
	IsDeformationWritten=true;
	for(unsigned int i=PointToPastChangedDeformation;i<ContentOfFile.size();i++)
	{
		ofs<<ContentOfFile[i]<<"\n";
	}
	
	ofs.close();
}
void Deformation::RestoreDeformation()
{
	string Path=GetPathToTalysData()+"/CalculationResults/";
	vector<string> p;
	p.push_back(Path);
	string mask="*"+GetNucleusName(Z)+".def";
	vector<string> Files=FindFile(p,mask);
	string OldestFile;
	TDatime dt;
	unsigned int TimeFile=dt.Get();
	
	for(unsigned int i=0;i<Files.size();i++)
	{
		unsigned int LastSlashIndex=0;
		for(unsigned int j=0;j<Files[i].size();j++)
		{
			if(Files[i][j]=='_')
			{
				Files[i][j]=' ';
			}
			if(Files[i][j]=='/')
			{
				Files[i][j]=' ';
				LastSlashIndex=j;
			}
		}
		Files[i]=Files[i].substr(LastSlashIndex,Files[i].size()-LastSlashIndex);
		
		stringstream s(Files[i]);
		unsigned int t;
		s>>t;
		if(t<TimeFile)
		{
			TimeFile=t;
		}
	}
	if(TimeFile>0)
	{
		string OldestFileName=Path+to_string(TimeFile)+"_"+mask.substr(1,mask.size()-1);
		string TalysFileName=GetPathToTalysData()+"/structure/deformation/"+GetNucleusName(Z)+".def";
		system(("mv "+OldestFileName+" "+TalysFileName).c_str());
	}
}
void Deformation::Sort()
{
	
	if(LevelDeformations.size()<2)
	{
		return;
	}
	for(unsigned int i=0;i<LevelDeformations.size()-1;i++)
	{
		for (int j = 0; j <LevelDeformations.size()-i-1; j++)
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
void Deformation::AssignPointers()
{
	for(unsigned int i=0;i<LevelDeformations.size();i++)
	{
		LevelDeformations[i].fDeformation=this;
	}
}
//Методы класса Level
bool Level::ReadLevel(string line,string ReadNuclName)
{
	string type;
	stringstream s(line);
	s>>Nuclide>>type;
	
	char status;
	if(type=="L")
	{
		if(ReadNuclName==Nuclide)
		{
			Energy=atof(line.substr(9,9).c_str());
			EnergyErr=atof(line.substr(19,1).c_str());
			JP=line.substr(21,17);
			JP_values=ENSDFJPToNormalJP(JP,Mark);
			HalfLife=line.substr(39,9);
			HalfLifeErr=line.substr(49,5);
			status=line.substr(79,1)[0];
			if(status=='?')
			{
				return false;
			}
			return true;
		}
		return false;
	}
	else
	{
		return false;
	}
}
void Level::ReadTransition(string line)
{
	GammaTransition transition;
	if(transition.ReadTransition(line,Nuclide,Energy))
	{
		Gammas.push_back(transition);
		Gammas[Gammas.size()-1].fLevel=this;
	}
}
void Level::Reset()
{
	Gammas.resize(0);
}
/*void Level::Print()
{
	cout<<"Level:"<< Energy<<" "<<JP<<"\n";
	for(unsigned int i=0;i<Gammas.size();i++)
	{
		cout<<Gammas[i].GetLine()<<"\n";
	}
}*/
bool Level::CheckEnergy(float E,float Tolerancy,float intensity)
{
	bool result=false;
	for(unsigned int i=0;i<Gammas.size();i++)
	{
		result=result||Gammas[i].CheckEnergy(E,Tolerancy,intensity);
	}
	return result;
}
void Level::AddLineFromTalys(double E, double CS)
{
	GammaTransition g;
	g.Energy=E;
	g.TalysCrossSection=CS;
	g.Origin="Talys";
	Gammas.push_back(g);
	Gammas[Gammas.size()-1].fLevel=this;
	
}
void Level::AddLineFromTalys(double E, double CS, double E_i, double E_f, SpinParity JP_i, SpinParity JP_f, unsigned int InitLevelNumber, unsigned int FinalLevelNumber)
{
	GammaTransition g;
	g.Energy=E;
	g.TalysCrossSection=CS;
	g.Origin="Talys";
	g.TalysE_i=E_i;
	g.TalysE_f=E_f;
	g.TalysJP_f=JP_f;
	g.TalysJP_i=JP_i;
	g.InitLevelNumber=InitLevelNumber;
	g.FinalLevelNumber=FinalLevelNumber;
	Gammas.push_back(g);
}
vector<GammaTransition*> Level::GetTransition(float E,float Tolerancy,float intensity)
{
	vector<GammaTransition*> result;
	for(unsigned int i=0;i<Gammas.size();i++)
	{
		if(Gammas[i].CheckEnergy(E,Tolerancy,intensity))
		{
			result.push_back(&Gammas[i]);
			result[result.size()-1]->fLevel=this;
		}
	}
	return result;
}
const char *Level::GetName()  const
{
	return ("level_"+to_string(Energy)).c_str();
}
void Level::AssignPointers()
{
	for(unsigned int i=0;i<Gammas.size();i++)
	{
		Gammas[i].fLevel=this;
		Gammas[i].fFinalLevel=0;
	}
}
//Методы для работы с данными класса Level: ввод
void Level::SetEnergy(float Energy)
{
	this->Energy=Energy;
}
void Level::SetEnergyErr(float EnergyErr)
{
	this->EnergyErr=EnergyErr;
}
void Level::SetTalysCS(float TalysCS)
{
	this->TalysCS=TalysCS;
}
void Level::SetTalysSpinParity(SpinParity TalysJP)
{
	this->TalysJP=TalysJP;
}
void Level::SetOrigin(string Origin)
{
	this->Origin=Origin;
}
void Level::AddJPValue(SpinParity JPValue)
{
	JP_values.push_back(JPValue);
}
void Level::AddSimilarLevel(Level* SimilarLevel)
{
	SimilarLevels.push_back(SimilarLevel);
}
//Методы для работы с данными класса Level: вывод
float Level::GetEnergy()
{
	return Energy;
}
float Level::GetEnergyErr()
{
	return EnergyErr;
}
float Level::GetTalysCS()
{
	return TalysCS;
}
SpinParity Level::GetTalysSpinParity()
{
	return TalysJP;
}
string Level::GetOrigin()
{
	return Origin;
}
vector<SpinParity>& Level::GetJPValues()
{
	return JP_values;
}
vector<Level*>& Level::GetSimilarLevels()
{
	return SimilarLevels;
}
void Level::ErasePointers()
{
	for(unsigned int i=0;i<Gammas.size();i++)
	{
		Gammas[i].ErasePointers();
	}
	SimilarLevels.resize(0);
	fNucleus=0;
}
LevelData Level::ToLevelData()
{
	LevelData result=(LevelData)(*this);
	for(unsigned int i=0;i<Gammas.size();i++)
	{
		result.GammasData.push_back((GammaTransitionData)Gammas[i]);
	}
	return result;
}
Level::Level(LevelData ld)
{
	deformation=0;
	Nuclide=ld.Nuclide; HalfLife=ld.HalfLife; HalfLifeErr=ld.HalfLifeErr; JP=ld.JP; Origin=ld.Origin;
	JP_values=ld.JP_values;
	
	Mark=ld.Mark;//величина, определяющая достоверность уровня: размер вектора с JP, если JP.size=0, то Mark=99,если есть неопределенность (скобки), то размер ветора*2
	Energy=ld.Energy; EnergyErr=ld.EnergyErr, TalysCS=ld.TalysCS; TalysJP=ld.TalysJP;
	for(unsigned int i=0;i<ld.GammasData.size();i++)
	{
		Gammas.emplace_back(ld.GammasData[i]);
	}
}
TGraph* Level::GetAngularDistribution(string type,string option)//если график уже построен, выдается сохраненный, если нет, или option=="new", строится заново
{
	if((!PlottedADist)||(option=="new"))
	{
		AdistTotalTalys=TGraph(Angle.size(), &Angle[0], &ADTot[0]);
		AdistCompoundTalys=TGraph(Angle.size(), &Angle[0], &ADCompound[0]);
		AdistDirectTalys=TGraph(Angle.size(), &Angle[0], &ADDirect[0]);
		string TotName="ADTotalTalysL"+to_string(Number);
		string CompName="ADCompTalysL"+to_string(Number);
		string DirName="ADDirTalysL"+to_string(Number);
		TString TotTitle=TString::Format("Total #frac{d#sigma}{d#Omega} for %s%s%s, E_{l}=%.1f, JP=%s;Angle, deg;#frac{d#sigma}{d#Omega},mb",(fNucleus->fMotherNucleus->Name).c_str(),(fNucleus->Reaction).c_str(),(fNucleus->Name).c_str(), Energy,TalysJP.GetLine().c_str());
		TString CompTitle=TString::Format("Compound #frac{d#sigma}{d#Omega} for %s%s%s, E_{l}=%.1f, JP=%s;Angle, deg;#frac{d#sigma}{d#Omega},mb",(fNucleus->fMotherNucleus->Name).c_str(),(fNucleus->Reaction).c_str(),(fNucleus->Name).c_str(), Energy,TalysJP.GetLine().c_str());
		TString DirTitle=TString::Format("Direct #frac{d#sigma}{d#Omega} for %s%s%s, E_{l}=%.1f, JP=%s;Angle, deg;#frac{d#sigma}{d#Omega},mb",(fNucleus->fMotherNucleus->Name).c_str(),(fNucleus->Reaction).c_str(),(fNucleus->Name).c_str(), Energy,TalysJP.GetLine().c_str());
		AdistTotalTalys.SetName(TotName.c_str());
		AdistCompoundTalys.SetName(CompName.c_str());
		AdistDirectTalys.SetName(DirName.c_str());
		
		AdistCompoundTalys.SetLineColor(2);
		AdistDirectTalys.SetLineColor(4);
		
		AdistTotalTalys.SetTitle(TotTitle);
		AdistCompoundTalys.SetTitle(CompTitle);
		AdistDirectTalys.SetTitle(DirTitle);
	}

	if(type=="Total")
	{
		return &AdistTotalTalys;
	}
	if(type=="Compound")
	{
		return &AdistCompoundTalys;
	}
	if(type=="Direct")
	{
		return &AdistDirectTalys;
	}
	return 0;
	
}
TMultiGraph* Level::GetTMultiGraphForAngularDistributions(string graphics)
{
	TMultiGraph* AllAngularDistributions=new TMultiGraph();
	GetAngularDistribution();//AdistTotalTalys, AdistCompoundTalys, AdistDirectTalys
	TGraph* elastic;
	if(fNucleus->fMotherNucleus)
	{
		elastic=fNucleus->fMotherNucleus->GetElasticAngularDistribution("Total");
	}
	else if(fNucleus)
	{
		elastic=fNucleus->GetElasticAngularDistribution("Total");
	}
	if(graphics=="all")
	{
		AllAngularDistributions->Add(&AdistTotalTalys);
		AllAngularDistributions->Add(&AdistCompoundTalys);
		AllAngularDistributions->Add(&AdistDirectTalys);
		/*if(elastic)
		{
			AllAngularDistributions->Add(elastic);
		}*/
	}
	else
	{
		if((int)graphics.find("Total")>-1)
		{
			AllAngularDistributions->Add(&AdistTotalTalys);
		}
		if((int)graphics.find("Compound")>-1)
		{
			AllAngularDistributions->Add(&AdistCompoundTalys);
		}
		if((int)graphics.find("Direct")>-1)
		{
			AllAngularDistributions->Add(&AdistDirectTalys);
		}
		if((int)graphics.find("Elastic")>-1)
		{
			AllAngularDistributions->Add(elastic);
		}
	}
	return AllAngularDistributions;
}

void Level::SetTGraphNameAndTitle(string ValName)
{
	if(ValName=="Energy")
	{
		ValName="E";
	}
	if(ValName=="Beta")
	{
		ValName="B";
	}
	CSGraph.SetName(TString::Format("LVExTot_%s_%d",ValName.c_str(),Number));
	CSCompoundGraph.SetName(TString::Format("LVExComp_%s_%d",ValName.c_str(),Number));
	CSDirectGraph.SetName(TString::Format("LVExDir_%s_%d",ValName.c_str(),Number));
	CSGraph.SetTitle(TString::Format("#sigma_{ex}(%s) total,E_{level}=%.1f;%s;#sigma,mb",ValName.c_str(),Energy,ValName.c_str()));
	CSCompoundGraph.SetTitle(TString::Format("#sigma_{ex}(%s) compound,E_{level}=%.1f;%s;#sigma,mb",ValName.c_str(),Energy,ValName.c_str()));
	CSDirectGraph.SetTitle(TString::Format("#sigma_{ex}(%s) direct,E_{level}=%.1f;%s;#sigma,mb",ValName.c_str(),Energy,ValName.c_str()));
	for(unsigned int i=0;i<Gammas.size();i++)
	{
		Gammas[i].SetTGraphNameAndTitle(ValName);
	}
}

void Level::SetDeformation(char LevT, int BandN, int BandL, int NPhon, int MagN, vector<float> *Def)
{
	if(deformation)
	{
		deformation->NumberOfBand=BandN;
		deformation->TypeOfLevel=LevT;
		deformation->NumberOfLevel=Number;
		deformation->LOfBand=BandL;
		deformation->NumberOfPhonons=NPhon;
		deformation->MagneticNumber=MagN;
		
		if(Def!=0)
		{
			deformation->Beta.resize(0);
			for(unsigned int i=0;i<Def->size(); i++)
			{
				deformation->Beta.push_back(Def->at(i));
			}
		}
		deformation->fLevel=this;
	}
	else
	{
		if(!fNucleus)
		{
			cout<<"Error: deformation cannot be assigned to standalone level! (fNucleus does not set). Returned\n";
			return ;
		}
		LevelDeformation d;
		d.NumberOfBand=BandN;
		d.TypeOfLevel=LevT;
		d.NumberOfLevel=Number;
		d.LOfBand=BandL;
		d.NumberOfPhonons=NPhon;
		d.MagneticNumber=MagN;
		d.fLevel=this;
		if(Def)
		{
			d.Beta=*Def;
		}
		fNucleus->Def.LevelDeformations.push_back(d);
		deformation=&(fNucleus->Def.LevelDeformations[fNucleus->Def.LevelDeformations.size()]);
		//fNucleus->Def.AssignPointers();
		fNucleus->Def.Sort();
	}
}

void Level::AddPoint(double x_value,Level *level)
{
	if(!level)
	return ;
	if(Number!=level->Number)
	return ;
	for(unsigned int i=0;i<Gammas.size();i++)
	{
		for(unsigned int j=0;j<level->Gammas.size();j++)
		{
			Gammas[i].AddPoint(x_value,&(level->Gammas[j]));
		}
	}
	int N=CSGraph.GetN();
	CSGraph.SetPoint(N,x_value,level->TalysCS); 
	CSCompoundGraph.SetPoint(N,x_value,level->TalysCSCompound);
	CSDirectGraph.SetPoint(N,x_value,level->TalysCSDirect);
}

TGraph* Level::GetCSGraph(string type)
{
	TGraph* result = 0;
	if(type=="Total")
	{
		result=&CSGraph;
	}
	if(type=="Compound")
	{
		result=&CSCompoundGraph;
	}
	if(type=="Direct")
	{
		result=&CSDirectGraph;
	}
	return result;
}

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
	for(unsigned int i=0;i<ND.LevelsData.size();i++)
	{
		Levels.emplace_back(ND.LevelsData[i]);
	}
	for(unsigned int i=0;i<ND.ProductsData.size();i++)
	{
		Products.emplace_back(ND.ProductsData[i]);
	}	
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
			if((line.find(ReactionToTalysNotation(kTotalInelasticCS))!=string::npos)&&(line.size()>22))
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
			s>>tmp>>tmp>>tmp>>CompoundElastic;
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
void Nucleus::SetLevelDeformation(int LevelNumber,char LevT, int BandN, int BandL, int NPhon, int MagN, vector<float> *Def)
{
	Level *l=FindLevelByNumber(LevelNumber);
	if(l)
	{
		l->SetDeformation(LevT,BandN,BandL,NPhon,MagN,Def);
	}
}
void Nucleus::SetLevelDeformation(double LevelEnergy,char LevT, int BandN, int BandL, int NPhon, int MagN, vector<float> *Def)
{
	Level *l=FindLevelByEnergy(LevelEnergy);
	if(l)
	{
		l->SetDeformation(LevT,BandN,BandL,NPhon,MagN,Def);
	}
}
Nucleus::~Nucleus()
{
	if((FastFlag)&&(FastCalculated))
	{
		system("rm -rf /dev/shm/CalculationResults/");
	}
}	
void TalysCalculation::ReadParametersFromFile(string filename)
{
	ifstream ifs(filename.c_str());
	string line;
	while(getline(ifs,line))
	{
		if(line.find("#")==string::npos)
		{
			if(line.find("Target:")!=string::npos)
			{
				stringstream s(line);
				s>>line>>Target;
			}
			if(line.find("Variation:")!=string::npos)// Например, Variation: Energy 0 15 1
			{
				stringstream s(line);
				double min, max, step,v=0;
				s>>line>>Variable>>min>>max>>step;
				v=min;
				while(v<=max)
				{
					VarValues.push_back(v);
					v+=step;
				}
			}
			if(line.find("Energy:")!=string::npos)
			{
				stringstream s(line);
				s>>line>>ProjectileEnergy;
			}
			if(line.find("Projectile:")!=string::npos)
			{
				stringstream s(line);
				s>>line>>Proj;
			}
			if(line.find("ProjectileEnergy:")!=string::npos)
			{
				stringstream s(line);
				s>>line>>ProjectileEnergy;
			}
			if(line.find("Option:")!=string::npos)
			{
				TalysOptions.push_back(line.substr(7,line.size()-7));
			}
		}
	}
}

void TalysCalculation::SetVarValues(double min,double max,double step)
{
	VarValues.resize(0);
	double value=min;
	if(step==0)
	{
		cout<<"This is TalysCalculation::SetVarValues(): step should be > 0\n";
		return ;
	}
	while(value<max)
	{
		VarValues.push_back(value);
		value+=step;
	}
}

void TalysCalculation::ExecuteCalculation()
{
	if(VarValues.size()>0)
	{
		Nucleus Nucl(Target);
		Nucl.Projectile=Proj;
		Nucl.TalysOptions=TalysOptions;
		for(unsigned int i=0;i<VarValues.size();i++)
		{
			if(Variable=="Energy")
			{
				Nucl.SetProjectileEnergy(VarValues[i]);
				Results.push_back(Nucl);
			}else if(Variable.find("Beta")!=string::npos)
			{
				TString ts(Variable);
				ts.ReplaceAll("_"," ");
				stringstream s(ts.Data());
				string tmp; int LevNumber, BetaIndex;
				s>>tmp>>LevNumber>>BetaIndex;
				
			}
			//позже тут будут и другие параметры
		}
		for(unsigned int i=0;i<Results.size();i++)
		{
			Results[i].GenerateProducts(Proj);
		}
	}
}

void TalysCalculation::ExecuteCalculation(void (*VarChangeFunction)(Nucleus *Nuclide,double value))
{
	if(VarValues.size()>0)
	{
		Nucleus Nucl(Target);
		Nucl.Projectile=Proj;
		Nucl.TalysOptions=TalysOptions;
		Nucl.ProjectileEnergy=ProjectileEnergy;
		for(unsigned int i=0;i<VarValues.size();i++)
		{
			VarChangeFunction(&Nucl,VarValues[i]);
			Results.push_back(Nucl);
		}
		for(unsigned int i=0;i<Results.size();i++)
		{
			Results[i].GenerateProducts(Proj);
		}
	}
}

void TalysCalculation::GenerateGraphs()
{
	if(Results.size()==0)
	{
		cout<<"TalysCalculation::GenerateGraphs() error: size of Results vector = 0; execute ReadParametersFromFile first\n";
		return ;
	}
	FinalResult=&Results[Results.size()-1];
	FinalResult->SetTGraphNameAndTitle(Variable);
	for(unsigned int i=0;i<Results.size();i++)
	{
		FinalResult->AddPoint(VarValues[i],&Results[i]);
	}
	GeneratedGraphs=true;
}

TGraph* TalysCalculation::GetLevelExcitationCrossSection(double LevelEnergy,string NucleusName,string Option)
{
	if(!GeneratedGraphs)
	{
		GenerateGraphs();
	}
	Nucleus* PointerToNucleus=FinalResult->FindProductByName(NucleusName);
	if(!PointerToNucleus)
	{
		cout<<"TalysCalculation::GetLevelExcitationCrossSection(...) error: Nucleus "<<NucleusName<<" not found in Products! 0 returned\n";
		return 0;
	}
	Level* l=PointerToNucleus->FindLevelByEnergy(LevelEnergy,0.5);
	if(!l)
	{
		cout<<"TalysCalculation::GetLevelExcitationCrossSection(...) error: Level with energy "<<LevelEnergy<<" not found in "<<PointerToNucleus->Name<<", 0 returned\n";
		return 0;
	}
	return l->GetCSGraph(Option);
}

TGraph* TalysCalculation::GetGammaTransitionCrossSction(double GammaEnergy,string NucleusName)
{
	if(!GeneratedGraphs)
	{
		GenerateGraphs();
	}
	TGraph* result;	
	Nucleus* PointerToNucleus=FinalResult->FindProductByName(NucleusName);
	if(!PointerToNucleus)
	{
		cout<<"TalysCalculation::GetGammaTransitionCrossSction(...) error: Nucleus "<<NucleusName<<" not found in Products! 0 returned\n";
		return 0;
	}
	GammaTransition *g=PointerToNucleus->GetBestTransition(GammaEnergy,0.5);
	if(!g)
	{
		cout<<"GetGammaTransitionCrossSction(...) error: Gamma with energy "<<GammaEnergy<<" not found in "<<PointerToNucleus->Name<<", 0 returned\n";
		return 0;
	}
	return g->GetCSGraph();
}
TMultiGraph* TalysCalculation::GetAngularDistributionsForLevel(double LevelEnergy,string NucleusName,string type,string option,TLegend *leg)
{
	TMultiGraph* result=0;
	if(!GeneratedGraphs)
	{
		GenerateGraphs();
	}
	Nucleus* PointerToNucleus=FinalResult->FindProductByName(NucleusName);
	if(!PointerToNucleus)
	{
		cout<<"TalysCalculation::GetAngularDistributionsForLevel(...) error: Nucleus "<<NucleusName<<" not found in Products! 0 returned\n";
		return 0;
	}
	Level *l=PointerToNucleus->FindLevelByEnergy(LevelEnergy,0.5);
	if(!l)
	{
		cout<<"TalysCalculation::GetAngularDistributionsForLevel(...) error: Level with energy "<<LevelEnergy<<" not found in "<<PointerToNucleus->Name<<", 0 returned\n";
		return 0;
	}
	
	if(Results.size()>0)
	{
		TGraph *g=l->GetAngularDistribution(type,option);
		result=new TMultiGraph();
		result->SetName(g->GetName());
		result->SetTitle(g->GetTitle());
	}
	for(unsigned int i=0;i<Results.size();i++)
	{
		Nucleus* PTN=Results[i].FindProductByName(NucleusName);
		Level *li=PTN->FindLevelByEnergy(LevelEnergy,0.5);
		TGraph *g=li->GetAngularDistribution(type,option);
		if(type=="Total")
		{
			g->SetLineColor(kViolet-9+i);
		}
		if(type=="Compound")
		{
			g->SetLineColor(kAzure-9+i);
		}
		if(type=="Direct")
		{
			g->SetLineColor(kOrange-9+i);
		}
		result->Add(g);
		if(leg)
		{
			leg->AddEntry(g,TString::Format("%s=%f",Variable.c_str(),VarValues[i]));
		}
	}
	return result;
}
TMultiGraph* TalysCalculation::GetElasticAngularDistributions(string type,string option,TLegend *leg)//выдает TMultiGraph с угловыми распределениями, соответствующими значениям VarValues
{
	TMultiGraph* result=0;
	if(!GeneratedGraphs)
	{
		GenerateGraphs();
	}
	if(Results.size()==0)
	{
		cout<<"TalysCalculation::GetElasticAngularDistributions(...) error! Vector of Results is empty, Execute ExecuteCalculation(...) first! 0 returned \n";
		return 0;
	}
	TGraph *g=Results[0].GetElasticAngularDistribution(type,option);
	result=new TMultiGraph();
	result->SetName(g->GetName());
	result->SetTitle(g->GetTitle());
	for(unsigned int i=0;i<Results.size();i++)
	{
		TGraph *gi=Results[i].GetElasticAngularDistribution(type,option);
		if(type=="Total")
		{
			gi->SetLineColor(kViolet-9+i);
		}
		if(type=="Compound")
		{
			gi->SetLineColor(kAzure-9+i);
		}
		if(type=="Direct")
		{
			gi->SetLineColor(kOrange-9+i);
		}
		result->Add(gi);
		if(leg)
		{
			leg->AddEntry(gi,TString::Format("%s=%f",Variable.c_str(),VarValues[i]));
		}
	}
	return result;
}
/*
void TalysCalculation::ExecuteCalculation()
{
	for(unsigned int i=0;i<Results.size();i++)
	{
		Results[i].GenerateProducts(Proj);
	}
	ElasticOnE=TGraph("ElasticOnE","#sigma_{el}(E);E,MeV;#sigma");
	InelasticOnE=TGraph("InelasticOnE","#sigma_{inl}(E);E,MeV;#sigma");
	for(unsigned int i=0;i<Energies.size();i++)
	{
		//ElasticOnE.SetPoint(i,Energies[i],
	}
}*/

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

#include <TKey.h>
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
