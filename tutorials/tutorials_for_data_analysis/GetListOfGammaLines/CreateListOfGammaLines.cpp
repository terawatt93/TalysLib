#include <TalysLib.hh>

void CreateListOfGammaLines()
{
	TLMaterial Cr2O3("NaCl");
	Cr2O3.AddBackground("background.txt");
	cout<<"In Material:\n";
	for(unsigned int i=0;i<Cr2O3.Nuclides.size();i++)
	{
		cout<<Cr2O3.Nuclides[i]->Name<<"\n";
	}
	vector<GammaTransition*> Gammas=Cr2O3.GetGammaTransitions(20);//получить вектор указателей на гамма-линии с сечениями больше 20 мб с учетом распространенности элементов
	for(unsigned int i=0;i<Gammas.size();i++)
	{
		cout<<"E_gamma:"<<Gammas[i]->Energy<<" CS:"<<Gammas[i]->TalysCrossSection<<" in "<<Gammas[i]->fLevel->fNucleus->Name<<" Reaction:"<<Gammas[i]->fLevel->fNucleus->fMotherNucleus->Name<<Gammas[i]->fLevel->fNucleus->Reaction<<Gammas[i]->fLevel->fNucleus->Name<<"\n";
	}
	
}
