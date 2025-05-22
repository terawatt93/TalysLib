#include "TalysLib.hh"
#include "TTeXDump.h"

void GetEvaluatedCS()
{
    Nucleus C("48Ti");
    C.GenerateProducts();
    TalysLibManager::Instance().SetAOption("A>=0");
    TCanvas c;
    c.Print("CS.pdf[","pdf");
    ofstream ofs("references.txt");
    TFile f("out.root","recreate");
    ofs<<"Level#\tData#\tSubEntry\tAuthor\tTitle\tYear\treference\n";
    for(unsigned int i=0;i<4;i++)
    {
		Level *l=&(C.FindProductByReaction("(n,n')")->Levels[i]);
		TMultiGraph* mg=l->GetTMultiGraphForCrossSections("all evaluated");
		mg->SetTitle(TString::Format("Evaluated #sigma(E_{n}) for level %d;#theta, deg; #frac{d#sigma}{d#Omega}, mb/str",i));
		mg->Draw("a plc pmc ");
		mg->GetXaxis()->SetRangeUser(0,9);
		mg->SetMaximum(1100);
		mg->SetMinimum(0);
		gPad->BuildLegend();
		//gPad->SetLogy(1);
		//gPad->SetLogx(1);
		c.Print("CS.pdf","pdf");
		f.WriteTObject(&c);
		c.Clear();
	}
	f.Close();
    c.Print("CS.pdf]","pdf");
}
