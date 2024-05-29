#include <TalysLib.hh>

void CreateListOfGammaLines()
{
	TalysLibManager::Instance().SetEnableWarning(false);
	TLMaterial Cr2O3("NaCl");
	Cr2O3.Calculate();
	Cr2O3.AddBackground("background.txt");
	cout<<"In Material:\n";
	for(unsigned int i=0;i<Cr2O3.Nuclides.size();i++)
	{
		cout<<Cr2O3.Nuclides[i]->Name<<"\n";
	}
	//GetGammaTransitionsE(double EnergyThreshold=0,double CrossSectionThreshold=0,bool UseAbundancy=true);
	vector<GammaTransition*> Gammas=Cr2O3.GetGammaTransitionsE(400,20);//получить вектор указателей на гамма-линии с сечениями больше 20 мб с учетом распространенности элементов
	for(unsigned int i=0;i<Gammas.size();i++)
	{
		cout<<"E_gamma:"<<Gammas[i]->Energy<<" CS:"<<Gammas[i]->TalysCrossSection<<" in "<<Gammas[i]->fLevel->fNucleus->Name<<" Reaction:"<<Gammas[i]->fLevel->fNucleus->fMotherNucleus->Name<<Gammas[i]->fLevel->fNucleus->Reaction<<Gammas[i]->fLevel->fNucleus->Name<<" "<<Gammas[i]->GetMostProbableMultipolarity().J<<"\n";
	}
	
}
