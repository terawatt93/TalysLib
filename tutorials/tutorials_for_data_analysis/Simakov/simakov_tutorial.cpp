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
// Si
// 1: 32,60
// 2: 10,12,15,32


void DrawHist(vector<double> vec, TCanvas* c, string file_name, TString title)
{
	c->cd();
	double sum = accumulate(vec.begin(), vec.end(), 0.0); 
	double avg = sum/vec.size();
	double min = *min_element(vec.begin(),vec.end());
	double max =  *max_element(vec.begin(),vec.end());
	TH1* h = new TH1F("hist", title.Data(), 24, 0, avg*2);
	TF1* g = new TF1("function", "gaus", min, max);

	for(auto &item: vec)
	{
		cout << item << "\n";
		h->Fill(item);
	}
	
	double p0,p1,p2;
	p0 = h->Integral();
	p1 = h->GetMean(1);
	p2 = pow(h->GetStdDev(1),2);
	
	g->SetParameters(p0,p1,p2);
	g->SetParLimits(1,min,max);
	
	h->Fit(g);
	h->GetYaxis()->SetTitle("N");
	h->GetXaxis()->SetTitle("#sigma,mb");
	h->Draw();
	
	gStyle->SetOptFit(11);
    gStyle->SetOptStat("n");
	
	auto stats = (TPaveStats*)h->GetListOfFunctions()->FindObject("stats");
    stats->SetX1NDC(0.6);
    stats->SetX2NDC(0.9);
    stats->SetY1NDC(0.5);
    stats->SetY2NDC(0.9);
    
    cout << h->Integral() << "\n"; 
    
    TFile f("TEST.root","recreate");
    f.WriteTObject(h);
    f.Close();
    
	c->Print(file_name.c_str(),"pdf");
}

void DrawEnergyDistribution(vector<TGraphErrors> vec, TCanvas* c, string file_name, TString title)
{
	c->cd();
	TMultiGraph* mg = new TMultiGraph();
	for(auto &item: vec)
	{
		mg->Add(&item, "p");
	}
	mg->SetTitle(title);
	mg->Draw("a plc pmc ");
	c->BuildLegend(0.7, 0.6, 0.9,0.9);
	c->Print(file_name.c_str(),"pdf");
	
}

void DrawEnergyDistribution2(vector<TGraph> vec, TCanvas* c, string file_name, TString title)
{
	c->cd();
	TMultiGraph* mg = new TMultiGraph();
	for(auto &item: vec)
	{
		mg->Add(&item, "p");
	}
	mg->SetTitle(title);
	mg->Draw("a plc pmc ");
	c->BuildLegend(0.7, 0.6, 0.9,0.9);
	c->Print(file_name.c_str(),"pdf");
	
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
	TCanvas transform_canvas;
	
	string hist1_file_name = "Hist.pdf";
	string hist2_file_name = "HistAfterFit.pdf";
	string ed_file_name1 = "EnergyDistributions.pdf";
	string ed_file_name2 = "EdTransform.pdf";
	
	ed_canvas.Print("EnergyDistributions.pdf[","pdf");
	hist_canvas1.Print("Hist.pdf[","pdf");
	hist_canvas2.Print("HistAfterFit.pdf[","pdf");
	fit_canvas.Print("Fit.pdf[","pdf");
	transform_canvas.Print("EdTransform.pdf[","pdf");
	
	vector<GammaTransition*> transitions{&(Nucl.FindProductByReaction("(n,n')")->Levels[1].Gammas[0])};

	double Emin = 13;
	double Emax = 15;
	
	for(auto &transition: transitions)
	{
		vector<TGraphErrors*> vec = transition->GetEnergyDistributionGraph(Emin,Emax);
		if(vec.size() != 0)
		{
			vector<TGraphErrors> new_vec;
			vector<TGraph> transform_vec;
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
						EnergyDistribution *edist=(EnergyDistribution*)graph;
						int N = new_graph.GetN();
						double x = graph->GetPointX(i);
						double y = graph->GetPointY(i);
						double dx = graph->GetErrorX(i);
						double dy = graph->GetErrorY(i);
						new_graph.SetPoint(N, x, y);
						new_graph.SetPointError(N, dx, dy);
						if(edist->fSubent->SubentID == "23173002")
						{
							hist_data_x.push_back(x);
							hist_data_y.push_back(y);
						}
					}
				}
				if(new_graph.GetN() != 0)
				{
					EnergyDistribution *edist=(EnergyDistribution*)graph;
					string graph_title = edist->fSubent->SubentID + " " + edist->fEntry->Authors[0] + " " + edist->fEntry->Year;
					new_graph.SetTitle(graph_title.c_str());
					new_graph.SetMarkerStyle(21);
					new_graph.SetMarkerSize(0.7);	
					new_vec.push_back(new_graph);
				}
			} 
			DrawEnergyDistribution(new_vec, &ed_canvas, ed_file_name1, Title);
			DrawHist(hist_data_y, &hist_canvas1, hist1_file_name, Title);
			double par0 = FitData(new_vec, &fit_canvas, Title);
			transform(hist_data_y.begin(), hist_data_y.end(), hist_data_x.begin(), hist_data_y.begin(), [par0](double &y, double &x){return par0 *(14.1) + (y-par0*x);});

			
			for(auto &graph: new_vec)
			{
				TGraph transform_graph;
				for(int i=0;i<graph.GetN();i++)
				{
					int N = transform_graph.GetN();
					double x = graph.GetPointX(i);
					double y = graph.GetPointY(i);
					y = y + par0*(x-14.1);
					transform_graph.SetPoint(N,x,y);
				}
				transform_graph.SetMarkerStyle(21);
				transform_graph.SetMarkerSize(0.7);	
				transform_vec.push_back(transform_graph);
			}
		
			DrawEnergyDistribution2(transform_vec, &transform_canvas, ed_file_name2, Title);
			DrawHist(hist_data_y, &hist_canvas2, hist2_file_name, Title);
		}	
	}
	ed_canvas.Print("EnergyDistributions.pdf]","pdf");
	hist_canvas1.Print("Hist.pdf]","pdf");
	hist_canvas2.Print("HistAfterFit.pdf]","pdf");
	fit_canvas.Print("Fit.pdf]","pdf");
	transform_canvas.Print("EdTransform.pdf]","pdf");
}
