#include "TalysLib.hh"

void GetAngularDistribution()
{
    Nucleus C("12C");
    C.GenerateProducts();
    TCanvas c;
    c.Print("ADIST.pdf[","pdf");
    for(unsigned int i=0;i<4;i++)
    {
		TMultiGraph* mg=C.Products[0].Levels[i].GetEXFORTMultiGraphForAngularDistributions(14,14.5);
		TGraph *g=C.Products[0].Levels[i].GetAngularDistribution("Total");
		mg->Add(g,"l");
		mg->Draw("ap");
		gPad->BuildLegend();
		gPad->SetLogy(1);
		c.Print("ADIST.pdf","pdf");
		c.Clear();
	}
    c.Print("ADIST.pdf]","pdf");
}
