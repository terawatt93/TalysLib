#include "../TalysLib.hh"
#include "../Parser.cpp"
/*OMPManager* OMPManager::pointer_to_this = 0;
OMPManager* OMPManager::Instance()
{
	if(!pointer_to_this)
	{
		pointer_to_this=new OMPManager();
	}
	return pointer_to_this;
}*/

TLElement* OMPManager::GetTLElement(int Z)
{
	for(unsigned int i=0;i<ElementsInCalculation.size();i++)
	{
		if(ElementsInCalculation[i].Z==Z)
		{
			return &ElementsInCalculation[i];
		}
	}
	TLElement el;
	el.Z=Z;
	el.ReadOMP(Z);
	el.fOMPManager=this;
	ElementsInCalculation.push_back(el);
	return &ElementsInCalculation[ElementsInCalculation.size()-1];
}
void OMPManager::AddElement(int Z)
{
	GetTLElement(Z);
}
void OMPManager::SetOMP(OpticalModelParameters OMP)
{
	//сначала ищем TLElement
	TLElement *el=GetTLElement(OMP.Z);
	vector<OpticalModelParameters> *OMPVector=0;
	if(OMP.Projectile=="n")
	{
		OMPVector=&(el->OpticalPotentialsN);
	}
	if(OMP.Projectile=="p")
	{
		OMPVector=&(el->OpticalPotentialsP);
	}
	if(!OMPVector)
	{
		cout<<"This is OMPManager::SetOMP(...): Invalid projectile in OpticalModelParameters argument! The projectile is \""<<OMP.Projectile<<"\". Returned\n";
		return;
	}
	bool found=false;
	for(unsigned int i=0;i<OMPVector->size();i++)
	{
		if((OMPVector->at(i).Z==OMP.Z)&&(OMPVector->at(i).A==OMP.A))
		{
			found=true;
			OMPVector->at(i)=OMP;
			return;
		}
	}
	if(!found)
	{
		OMPVector->push_back(OMP);
	}
}
OpticalModelParameters* OMPManager::GetOpticalPotential(int Z, int A, string Projectile)
{
	vector<OpticalModelParameters> *v;
	TLElement *el=GetTLElement(Z);
	if((Projectile=="n")||(Projectile=="neutron"))
	{
		v=&(el->OpticalPotentialsN);
	}
	if((Projectile=="p")||(Projectile=="proton"))
	{
		v=&(el->OpticalPotentialsP);
	}
	for(unsigned int i=0;i<v->size();i++)
	{
		if((v->at(i).Z==Z)&&(v->at(i).A==A))
		{
			return &(v->at(i));
		}
	}
	OpticalModelParameters OMP;
	OMP.SetZA(Z,A);
	OMP.SetProjectile(Projectile);
	OMP.PotentialKoning.EvalKoning();
	
	v->push_back(OMP);
	return &(v->at(v->size()-1));
}

void OMPManager::WriteOMP(string path,int UseKoningP,int UseKoningN)
{
	Addition="";
	for(unsigned int i=0;i<ElementsInCalculation.size();i++)
	{
		ElementsInCalculation[i].fOMPManager=this;
		ElementsInCalculation[i].WriteOMP(path,UseKoningP,UseKoningN);
	}
}
string OMPManager::GetAdditionToInputFile()
{
	if((Addition.size()==0)&&(TalysLibManager::Instance().IsEnableWarning()))
	{
		cout<<"This is OMPManager::GetAdditionToInputFile(): Addition is empty. Execute WriteOMP procedure first!\n";
	}
	return Addition;
}
