#include "TalysLib.hh"
#include "TTeXDump.h"

void GetAngularDistributionC4LAB()
{
    Nucleus C("12C");
    C.GenerateProducts();
    TCanvas c;
    c.Print("ADIST_LAB.pdf[","pdf");
    
    for(unsigned int i=0;i<4;i++)
    {
		Level *l=&(C.FindProductByReaction("(n,n')")->Levels[i]);
		TMultiGraph* mg=l->GetEXFORTMultiGraphForAngularDistributions(13,15,"LAB");
		TGraph *g_talys_total=l->GetAngularDistribution("Total");
		TGraph *g_talys_dir=l->GetAngularDistribution("Direct");
		TGraph *g_talys_com=l->GetAngularDistribution("Compound");
		TGraph *g_endf=l->GetAngularDistribution("ENDF");
		mg->Add(g_talys_total,"l");
		mg->Add(g_talys_dir,"l");
		mg->Add(g_talys_com,"l");
		mg->Add(g_endf,"l");
		mg->Draw("a plc pmc ");
		gPad->BuildLegend();
		gPad->SetLogy(1);
		c.Print("ADIST_LAB.pdf","pdf");
		c.Clear();
	}
    c.Print("ADIST_LAB.pdf]","pdf");
}
