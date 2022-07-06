#include "../TalysLib.hh"
#include "../Parser.cpp"

void ReadOMPFromBase(OpticalModelParameters &OMP,string line, ifstream &ifs)
{
	stringstream s(line);
	int A=0, Z=0, nOMP=0;
	s>>Z>>A>>nOMP;
	OMP.SetZA(Z,A);
	string Buffer=GetPotential(ifs);
	stringstream sstr(Buffer);
	OMP.nOMP=nOMP;
	int type;
	sstr>>type;
	if(type==1)
	{
		OMP.Potential.Read(Buffer);
	}
	else if(type==2)
	{
		OMP.PotentialDisp.Read(Buffer);
	}
	if(nOMP==2)
	{
		Buffer=GetPotential(ifs);
		stringstream Str2(Buffer);
		Str2>>type;
		if(type==1)
		{
			OMP.Potential.Read(Buffer);
		}
		if(type==2)
		{
			OMP.PotentialDisp.Read(Buffer);
		}
	}
}

void TLElement::ReadOMP(int _Z)
{
	if(_Z>0)
	{
		Z=_Z;
	}
	string OMPFileName=GetPathToTalysData()+"/structure/optical/";
	OMPFileName+="proton/p-"+GetNucleusName(Z)+".omp";
	ifstream ifs(OMPFileName);
	if(!ifs.good())
	{
		if(TalysLibManager::Instance().IsEnableWarning())
		cout<<"Warning: predefined OMP for "<<GetNucleusName(Z)<<" and projectile p does not exsists! Koning parametrisation will be used.\n";
		ifs.close();
	}
	else
	{
		string line;
		while(getline(ifs,line))
		{
			OpticalModelParameters OMP;	
			OMP.SetProjectile("p");		
			ReadOMPFromBase(OMP,line,ifs);
			OMP.PotentialKoning.EvalKoning();
			OpticalPotentialsP.push_back(OMP);	
		}
		ifs.close();
	}
	OMPFileName=GetPathToTalysData()+"/structure/optical/";
	OMPFileName+="neutron/n-"+GetNucleusName(Z)+".omp";
	ifs.open(OMPFileName);
	if(!ifs.good())
	{
		if(TalysLibManager::Instance().IsEnableWarning())
		cout<<"Warning: predefined OMP for "<<GetNucleusName(Z)<<" and projectile n does not exsists! Koning parametrisation will be used.\n";
		ifs.close();
	}
	else
	{
		string line;
		while(getline(ifs,line))
		{
			OpticalModelParameters OMP;
			OMP.SetProjectile("n");
			ReadOMPFromBase(OMP,line,ifs);
			OMP.PotentialKoning.EvalKoning();
			OpticalPotentialsN.push_back(OMP);	
		}
		ifs.close();
	}
}

string TLElement::GenerateFileContent(string Projectile,int UseKoning)
{
	TString result;
	vector<OpticalModelParameters> *v=0;
	if(Projectile=="n")
	{
		v=&OpticalPotentialsN;
	}
	if(Projectile=="p")
	{
		v=&OpticalPotentialsP;
	}
	for(unsigned int i=0;i<v->size();i++)
	{
		if(UseKoning==2)
		{
			result+=TString::Format("%4d%4d%4d\n",v->at(i).Z,v->at(i).A,1);
			result+=v->at(i).PotentialKoning.GetTString();
		}
		else if(UseKoning==1)
		{
			result+=TString::Format("%4d%4d%4d\n",v->at(i).Z,v->at(i).A,1);
			if(v->at(i).Potential.v1>0)//проверка на правильность обычного потенциала
			{
				result+=v->at(i).Potential.GetTString();
			}
			else
			{
				result+=v->at(i).PotentialKoning.GetTString();
			}
		}
		else if((!v->at(i).DefaultOMP)||(UseKoning==3))
		{
			if(v->at(i).nOMP>0)
			{
				result+=TString::Format("%4d%4d%4d\n",v->at(i).Z,v->at(i).A,v->at(i).nOMP);
				if(v->at(i).Potential.v1>0)//проверка на правильность обычного потенциала
				{
					result+=v->at(i).Potential.GetTString();
				}
				if(v->at(i).PotentialDisp.v1>0)//проверка на правильность дисп потенциала
				{
					result+=v->at(i).PotentialDisp.GetTString();
				}
			}
		}
		else if(v->at(i).DefaultOMP)
		{
			result+=TString::Format("%4d%4d%4d\n",v->at(i).Z,v->at(i).A,1);
			result+=v->at(i).DefaultOMP->GetTString();
		}
	}
	return string(result.Data());
}

void TLElement::WriteOMP(string path,int UseKoningP,int UseKoningN)
{
	string FileContent=GenerateFileContent("n",UseKoningN);
	if(UseKoningN>-1)
	{
		if(FileContent.size()>0)
		{
			ofstream ofs(path+to_string(Z)+"N.loc");
			ofs<<FileContent;
			if(fOMPManager)
			{
				fOMPManager->Addition+="optmodfileN "+to_string(Z)+" "+to_string(Z)+"N.loc\n";
			}
			ofs.close();
		}
	}
	if(UseKoningP>-1)
	{
		FileContent=GenerateFileContent("p",UseKoningP);
		if(FileContent.size()>0)
		{
			ofstream ofs(path+to_string(Z)+"P.loc");
			ofs<<FileContent;
			if(fOMPManager)
			{
				fOMPManager->Addition+="optmodfileP "+to_string(Z)+" "+to_string(Z)+"P.loc\n";
			}
			
			ofs.close();
		}
	}
	
	
}
