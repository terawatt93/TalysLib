#include "TalysLib.hh"

// Отрисовать все сечения гамма из EXFOR.

void GetExforGammaEnergyDistribution()
{
	Nucleus Nucl("16O");
	Nucl.GenerateProducts(); //Встроено извлечения данных из EXFOR 
	Nucl.AssignC5ToLevel(); //Распределить данные извлеченные из EXFOR по реакциям, уровням и гамма переходам. Потом добавить в GenerateProducts с флагом.
	
	TCanvas c;
	c.Print("EnergyDistribution.pdf[","pdf");
	
	for(int i=0;i<Nucl.FindProductByReaction("(n,n')")->Levels.size();i++)
	{
		Level *l = &(Nucl.FindProductByReaction("(n,n')")->Levels[i]);
		if(l->Gammas.size() != 0)
		{	
			for(int j=0; j<l->Gammas.size();j++)
			{
				if(l->Gammas[j].C5EnergyDistribution.size() != 0)
				{
					vector<TGraphErrors*> vec = l->Gammas[j].GetEnergyDistributionGraph(13,15); // GetEnergyDistribution возвращает вектор указателей TGraphErrors. параметры En min и En max.
					TMultiGraph* mg = new TMultiGraph();
					
					TString Title=TString::Format("%s with excitation of level %.1f in %s (Gamma transition: %.1f);E, MeV; #sigma,mb",l->fNucleus->Reaction.c_str(),l->Energy,l->fNucleus->Name.c_str(), l->Gammas[j].Energy);
					
					for(auto &item: vec)
					{
						EnergyDistribution *edist=(EnergyDistribution*)item;
						item->SetTitle(edist->fEntry->EntryID.c_str());
						item->SetMarkerStyle(21);
						item->SetMarkerSize(0.7);
						mg->Add(item, "p");
						
					} 
					mg->SetTitle(Title);
					mg->Draw("a plc pmc ");
					gPad->BuildLegend();
					gPad->SetLogy(1);
					c.Print("EnergyDistribution.pdf","pdf");
				}
			}
		}
	}
	
	c.Print("EnergyDistribution.pdf]","pdf");
}
