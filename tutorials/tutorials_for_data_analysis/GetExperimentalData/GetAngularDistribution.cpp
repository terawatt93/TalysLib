#include "TalysLib.hh"

void GetAngularDistribution()
{
    Nucleus C("12C");
    C.GenerateProducts();
    TCanvas c;
    c.Print("ADIST.pdf[","pdf");
    for(unsigned int i=0;i<4;i++)
    {
		TMultiGraph* mg=C.FindProductByReaction("n,n'")->Levels[i].GetEXFORTMultiGraphForAngularDistributions(14,14.5);
		TGraph *g_talys_total=C.FindProductByReaction("n,n'")->Levels[i].GetAngularDistribution("Total");
		TGraph *g_talys_dir=C.FindProductByReaction("n,n'")->Levels[i].GetAngularDistribution("Direct");
		TGraph *g_talys_com=C.FindProductByReaction("n,n'")->Levels[i].GetAngularDistribution("Compound");
		TGraph *g_endf=C.FindProductByReaction("n,n'")->Levels[i].GetAngularDistribution("ENDF");
		mg->Add(g_talys_total,"l");
		mg->Add(g_talys_dir,"l");
		mg->Add(g_talys_com,"l");
		mg->Add(g_endf,"l");
		mg->Draw("ap");
		gPad->BuildLegend();
		gPad->SetLogy(1);
		c.Print("ADIST.pdf","pdf");
		c.Clear();
	}
    c.Print("ADIST.pdf]","pdf");
}
