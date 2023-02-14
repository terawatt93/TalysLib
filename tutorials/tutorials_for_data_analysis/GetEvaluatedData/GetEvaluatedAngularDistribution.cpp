#include "TalysLib.hh"
#include "TTeXDump.h"

void GetEvaluatedAngularDistribution()
{
    Nucleus C("12C");
    C.GenerateProducts();
    TalysLibManager::Instance().SetAOption("A>=0");
    TCanvas c;
    c.Print("ADIST.pdf[","pdf");
    ofstream ofs("references.txt");
    ofs<<"Level#\tData#\tSubEntry\tAuthor\tTitle\tYear\treference\n";
    for(unsigned int i=0;i<4;i++)
    {
		Level *l=&(C.FindProductByReaction("(n,n')")->Levels[i]);
		TMultiGraph* mg=l->GetTMultiGraphForAngularDistributions("all evaluated");
		mg->SetTitle(TString::Format("Evaluated #frac{d#sigma}{d#Omega} for level %d;#theta, deg; #frac{d#sigma}{d#Omega}, mb/str",i));
		mg->Draw("a plc pmc ");
		gPad->BuildLegend();
		gPad->SetLogy(1);
		c.Print("ADIST.pdf","pdf");
		c.Clear();
	}
    c.Print("ADIST.pdf]","pdf");
}
