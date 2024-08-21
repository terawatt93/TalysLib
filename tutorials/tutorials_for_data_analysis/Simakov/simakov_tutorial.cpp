#include "TalysLib.hh"

double FitData(vector<TGraphErrors> vec, TCanvas* c, TString title)
{
	c->cd();
	TMultiGraph* mg = new TMultiGraph();
	TF1* pol = new TF1("pol", "[0]*x + [1]", 13, 15);
	for(auto &item: vec)
	{
		mg->Add(&item, "p");
	}
	mg->SetTitle(title);
	mg->Fit(pol);
	mg->Draw("a plc pmc ");
	gStyle->SetOptFit(0);
	c->BuildLegend(0.7, 0.6, 0.9,0.9);
	c->Print("Fit.pdf","pdf");
	return  pol->GetParameters()[0];
}

void DrawHist(vector<double> vec, TCanvas* c, string file_name, TString title)
{
	c->cd();
	TH1* h = new TH1F("hist", title.Data(), 30, 0, 0);
	TF1* g = new TF1("function", "gaus", 0, 900);
	for(auto &item: vec)
	{
		h->Fill(item);
	}
	h->SetDefaultBufferSize();
	h->Fit(g);
	h->Draw();
	
	gStyle->SetOptFit(11);
    gStyle->SetOptStat("n");
	
	auto stats = (TPaveStats*)h->GetListOfFunctions()->FindObject("stats");
    stats->SetX1NDC(0.6);
    stats->SetX2NDC(0.9);
    stats->SetY1NDC(0.5);
    stats->SetY2NDC(0.9);
    
	c->Print(file_name.c_str(),"pdf");
}

void DrawEnergyDistribution(vector<TGraphErrors> vec, TCanvas* c, TString title)
{
	c->cd();
	TMultiGraph* mg = new TMultiGraph();
	for(auto &item: vec)
	{
		mg->Add(&item, "p");
	}
	mg->SetTitle(title);
	mg->Draw("a plc pmc ");
	c->Print("EnergyDistributions.pdf","pdf");
	
}


void simakov_tutorial()
{
	//TalysLibManager::Instance().ExcludeSubEntries = {"23456004"};
	Nucleus Nucl("28Si");
	Nucl.GenerateProducts(); //Встроено извлечения данных из EXFOR 
	Nucl.AssignC5ToLevel(); //Распределить данные извлеченные из EXFOR по реакциям, уровням и гамма переходам. Потом добавить в GenerateProducts с флагом.
	
	TCanvas ed_canvas;
	TCanvas fit_canvas;
	TCanvas hist_canvas1;
	TCanvas hist_canvas2;
	
	string hist1_file_name = "Hist.pdf";
	string hist2_file_name = "HistAfterFit.pdf";
	
	ed_canvas.Print("EnergyDistributions.pdf[","pdf");
	hist_canvas1.Print("Hist.pdf[","pdf");
	hist_canvas2.Print("HistAfterFit.pdf[","pdf");
	fit_canvas.Print("Fit.pdf[","pdf");
	
	vector<GammaTransition*> transitions = Nucl.FindProductByReaction("(n,n')")->GetGammaTransitionsEDWithExforData();

	double Emin = 13;
	double Emax = 15;
	
	for(auto &transition: transitions)
	{
		vector<TGraphErrors*> vec = transition->GetEnergyDistributionGraph(Emin,Emax);
		if(vec.size() != 0)
		{
			vector<TGraphErrors> new_vec;
			vector<double> hist_data_y;
			vector<double> hist_data_x;
			TString Title=TString::Format("%s with excitation of level %.1f in %s (Gamma transition: %.1f);E, MeV; #sigma,mb",transition->fLevel->fNucleus->Reaction.c_str(),transition->fLevel->Energy,transition->fLevel->fNucleus->Name.c_str(), transition->Energy);
			for(auto &graph: vec)
			{
				TGraphErrors new_graph;
				for(int i=0;i<graph->GetN();i++)
				{
					if(graph->GetPointX(i) >= Emin && graph->GetPointX(i) <= Emax)
					{
						int N = new_graph.GetN();
						double x = graph->GetPointX(i);
						double y = graph->GetPointY(i);
						double dx = graph->GetErrorX(i);
						double dy = graph->GetErrorY(i);
						new_graph.SetPoint(N, x, y);
						new_graph.SetPointError(N, dx, dy);
						hist_data_x.push_back(x);
						hist_data_y.push_back(y);
					}
				}
				if(new_graph.GetN() != 0)
				{
					EnergyDistribution *edist=(EnergyDistribution*)graph;
					string graph_title = edist->fSubent->SubentID + " " + edist->fEntry->FirstAuthor + " " + edist->fEntry->Year;
					new_graph.SetTitle(graph_title.c_str());
					new_graph.SetMarkerStyle(21);
					new_graph.SetMarkerSize(0.7);	
					new_vec.push_back(new_graph);
				}
			} 
			DrawEnergyDistribution(new_vec, &ed_canvas, Title);
			DrawHist(hist_data_y, &hist_canvas1, hist1_file_name, Title);
			double par0 = FitData(new_vec, &fit_canvas, Title);
			transform(hist_data_y.begin(), hist_data_y.end(), hist_data_x.begin(), hist_data_y.begin(), [par0](double &y, double &x){return y + par0*(x-14.1);});
			DrawHist(hist_data_y, &hist_canvas2, hist2_file_name, Title);
		}	
	}
	ed_canvas.Print("EnergyDistributions.pdf]","pdf");
	hist_canvas1.Print("Hist.pdf]","pdf");
	hist_canvas2.Print("HistAfterFit.pdf]","pdf");
	fit_canvas.Print("Fit.pdf]","pdf");
}
