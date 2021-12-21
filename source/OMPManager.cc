#include "../TalysLib.hh"
#include "../Parser.cpp"
OMPManager* OMPManager::pointer_to_this = 0;
OMPManager* OMPManager::Instance()
{
	if(!pointer_to_this)
	{
		pointer_to_this=new OMPManager();
	}
	return pointer_to_this;
}

OpticalModelParameters* OMPManager::GetOpticalPotential(int Z, int A, string Projectile)
{
	vector<OpticalModelParameters> *v;
	if((Projectile=="n")||(Projectile=="neutron"))
	{
		v=&OpticalPotentialsN;
	}
	if((Projectile=="p")||(Projectile=="proton"))
	{
		v=&OpticalPotentialsP;
	}
	for(unsigned int i=0;i<v->size();i++)
	{
		if((v->at(i).Z==Z)&&(v->at(i).A==A))
		{
			return &(v->at(i));
		}
	}
	return NULL;
}

void OMPManager::ReadFromBase(Nucleus *Nucl)
{
	//сначала проверим, нет ли оптического потенциала среди уже считанных
	bool ExsistedForP=false, ExsistedForN=false;
	if(GetOpticalPotential(Nucl->Z,Nucl->A,"n"))
	{
		ExsistedForN=true;
	}
	if(GetOpticalPotential(Nucl->Z,Nucl->A,"p"))
	{
		ExsistedForP=true;
	}
	if(ExsistedForN&&ExsistedForP)
	{
		return;
	}
	if(!ExsistedForP)
	{
		string OMPFileName=GetPathToTalysData()+"/structure/optical/";
		OMPFileName+="proton/p-"+GetNucleusName(Nucl->Z)+".omp";
		ifstream ifs(OMPFileName);
		if(!ifs.good())
		{
			if(TalysLibManager::Instance().IsEnableWarning())
			cout<<"Warning: predefined OMP for "<<GetNucleusName(Nucl->Z)<<" and projectile p does not exsists! Koning parametrisation will be used.\n";
			ifs.close();
		}
		else
		{
			string line;
			while(getline(ifs,line))
			{
				stringstream s(line);
				int A=0, Z=0, nOMP=0;
				s>>Z>>A>>nOMP;
				
				OpticalModelParameters OMP;
				OMP.Z=Z; OMP.A=A; OMP.N=A-Z;
				Z_valuesP.push_back(Z);				
				string Buffer=GetPotential(ifs);
				stringstream sstr(Buffer);
				
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
				OpticalPotentialsP.push_back(OMP);	
			}
		}
	}
	if(!ExsistedForN)
	{
		string OMPFileName=GetPathToTalysData()+"/structure/optical/";
		OMPFileName+="neutron/n-"+GetNucleusName(Nucl->Z)+".omp";
		ifstream ifs(OMPFileName);
		if(!ifs.good())
		{
			if(TalysLibManager::Instance().IsEnableWarning())
			cout<<"Warning: predefined OMP for "<<GetNucleusName(Nucl->Z)<<" and projectile n does not exsists! Koning parametrisation will be used.\n";
			ifs.close();
		}
		else
		{
			string line;
			while(getline(ifs,line))
			{
				stringstream s(line);
				int A=0, Z=0, nOMP=0;
				s>>Z>>A>>nOMP;
				Z_valuesN.push_back(Z);
				OpticalModelParameters OMP;
				OMP.Z=Z; OMP.A=A; OMP.N=A-Z;
								
				string Buffer=GetPotential(ifs);
				stringstream sstr(Buffer);
				
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
				OpticalPotentialsN.push_back(OMP);	
			}
		}
	}
}
void OMPManager::SaveOMP(string PathToCalculationDir, string Projectile)
{
	vector<OpticalModelParameters> *v;
	vector<int> *Z_values;
	if((Projectile=="n")||(Projectile=="neutron"))
	{
		v=&OpticalPotentialsN;
		Z_values=&Z_valuesN;
	}
	if((Projectile=="p")||(Projectile=="proton"))
	{
		v=&OpticalPotentialsP;
		Z_values=&Z_valuesP;
	}
	
}
