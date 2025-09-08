#include "TalysLib.hh"

void GetExforAngularDistribution()
{
	//TalysLibManager::Instance().ExcludeSubEntries = {"22188046"};
	
	Nucleus Nucl("12C");
    Nucl.GenerateProducts();
    Nucl.AssignC5ToLevel();
    TCanvas c;
    c.Print("AngularDistribution.pdf[","pdf");
    for(unsigned int i=0;i<4;i++)
    {
		Level *l=&(Nucl.FindProductByReaction("(n,n')")->Levels[i]);
		vector<TGraphErrors*> vec = l->GetEXFORAngularDistributions(14,14.2);
		TMultiGraph* mg = new TMultiGraph();
					
		TString Title=TString::Format("%s with excitation of level %.1f in %s; #theta; #sigma,mb",l->fNucleus->Reaction.c_str(),l->Energy,l->fNucleus->Name.c_str());
		
		for(auto &item: vec)
		{
			AngularDistribution *adist=(AngularDistribution*)item;
			item->SetTitle(adist->fSubent->SubentID.c_str());
			//cout << "SubentID: " << adist->fSubent->SubentID.c_str() << "\t" << "Title: " << adist->fEntry->Title << "\n";
			item->SetMarkerStyle(21);
			item->SetMarkerSize(0.7);
			mg->Add(item, "p");
						
		} 
		mg->SetTitle(Title);
		mg->Draw("a plc pmc ");
		gPad->BuildLegend();
		gPad->SetLogy(1);
		c.Print("AngularDistribution.pdf","pdf");
	}
	c.Print("AngularDistribution.pdf]","pdf");
}
