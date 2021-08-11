#include <TalysLib.hh>

void CreateListOfGammaLines()
{
	TalysLibManager::Instance().SetEnableWarning(false);
	Radionuclide Nucl("22Na");
	vector<GammaTransition*> Gammas=Nucl.GetGammaTransitions();//получить вектор указателей на гамма-линии
	for(unsigned int i=0;i<Gammas.size();i++)
	{
		cout<<"E_gamma:"<<Gammas[i]->Energy<<" I_gamma:"<<Gammas[i]->GetRelativeIntensity()<<" in "<<Gammas[i]->fLevel->fNucleus->Name<<"\n";
	}
	
}
