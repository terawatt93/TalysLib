#include "TalysLib.hh"

void GetEnergyDependenceForGamma()
{
	TalysLibManager::Instance().ExcludeSubEntries = {"23456004"};
	Nucleus Nucl("28Si");
	Nucl.GenerateEnergyGrid(0,0.5,20);//сделать сетку по энергиям от 0 до 20 МэВ с шагом 0,5 МэВ
	Nucl.GenerateProducts();
	vector<GammaTransition*> Gammas=Nucl.GetGammaTransitions();
	TCanvas c;
	c.Print("EnergyDependence.pdf[","pdf");
	for(unsigned int i=0;i<Gammas.size();i++)
	{
		TGraph *gr=Gammas[i]->GetCSGraph();
		gr->Draw("al");
		c.Print("EnergyDependence.pdf","pdf");
	}
	c.Print("EnergyDependence.pdf]","pdf");
}
