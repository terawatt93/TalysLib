#include "TalysLib.hh"
#include "TTeXDump.h"

void GetAngularDistributionC4WithHref()
{
    Nucleus C("12C");
    C.GenerateProducts();
    TCanvas c;
    c.Print("ADIST.pdf[","pdf");
    ofstream ofs("references.txt");
    ofs<<"Level#\tData#\tSubEntry\tAuthor\tTitle\tYear\treference\n";
    for(unsigned int i=0;i<4;i++)
    {
		Level *l=&(C.FindProductByReaction("(n,n')")->Levels[i]);
		TMultiGraph* mg=l->GetEXFORTMultiGraphForAngularDistributions(14,14.5);
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
		c.Print(TString::Format("%d.tex",i));
		string TexFileName(TString::Format("%d.tex",i).Data());
		l->AddHyperlinksToTeX(TexFileName);
		system((string("pdflatex ")+TString::Format("%d.tex",i).Data()).c_str());
		c.Print("ADIST.pdf","pdf");
		
		vector<TGraphErrors*> ExpData=l->GetEXFORAngularDistributions(14,14.5);
		for(unsigned int j=0;j<ExpData.size();j++)
		{
			C4AngularDistribution *adist=(C4AngularDistribution*)ExpData[j];
			ofs<<i<<"\t"<<j<<"\t"<<adist->fEntry->DataSet.DataSet<<"\t"<<adist->fEntry->Author1<<"\t"<<adist->fEntry->Title<<"\t"<<adist->fEntry->Year<<"\t"<<adist->fEntry->Reference<<"\n";
		}
		
		c.Clear();
	}
    c.Print("ADIST.pdf]","pdf");
}
