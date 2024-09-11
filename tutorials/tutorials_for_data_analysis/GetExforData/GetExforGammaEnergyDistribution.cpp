#include "TalysLib.hh"

// Отрисовать все сечения гамма из EXFOR.

void GetExforGammaEnergyDistribution()
{
	TalysLibManager::Instance().ExcludeSubEntries = {"23456004"};
	Nucleus Nucl("28Si");
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
					if(vec.size() != 0)
					{
						TMultiGraph* mg = new TMultiGraph();
						
						TString Title=TString::Format("%s with excitation of level %.1f in %s (Gamma transition: %.1f);E, MeV; #sigma,mb",l->fNucleus->Reaction.c_str(),l->Energy,l->fNucleus->Name.c_str(), l->Gammas[j].Energy);
						
						for(auto &item: vec)
						{
							TGraphErrors* new_graph = new TGraphErrors();
							for(int i=0;i<item->GetN();i++)
							{
								if(item->GetPointX(i) >= 13 && item->GetPointX(i) <= 15)
								{
									int N = new_graph->GetN();
									double x = item->GetPointX(i);
									double y = item->GetPointY(i);
									double dx = item->GetErrorX(i);
									double dy = item->GetErrorY(i);
									new_graph->SetPoint(N, x, y);
									new_graph->SetPointError(N, dx, dy);
								}
							}
							if(new_graph->GetN() != 0)
							{
								EnergyDistribution *edist=(EnergyDistribution*)item;
								new_graph->SetTitle(edist->fSubent->SubentID.c_str());
								cout << edist->fSubent->SubentID << "\n";
								for(auto item: edist->fEntry->Detector)
								{
									cout << item.first << "\n";
								}
								new_graph->SetMarkerStyle(21);
								new_graph->SetMarkerSize(0.7);
									
								mg->Add(new_graph, "p");
							}
						} 
						mg->SetTitle(Title);
						mg->GetXaxis()->SetRangeUser(8,10);
						mg->Draw("a plc pmc ");
						gPad->BuildLegend();
						//gPad->SetLogy(1);
						c.Print("EnergyDistribution.pdf","pdf");
					}
				}
			}
		}
	}
	
	c.Print("EnergyDistribution.pdf]","pdf");
}
