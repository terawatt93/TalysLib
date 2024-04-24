#include <TalysLib.hh>
#include <TLine.h>
#include <TFile.h>

void TLineBug()
{
	TFile f("/home/terawatt/server_/ZFSRAID/Ing27-HPGe/root/test117_HPGe_2_LaBr_4_Ing27_75perc_top_Co60_Pb_1mm_SiO2_tree_one_dim.root");
	TH1D h=*((TH1D*)f.Get("E_0_0_stripRmBkg"));
	TLMaterial Mat("SiO2");
	Mat.Calculate();

	TCanvas c;
	c.Print("Bug.pdf[","pdf");
	h.Draw("hist");
	vector<GammaTransition*> Gammas=Mat.GetGammaTransitions();
	for(unsigned int i=0;i<Gammas.size();i++)
	{
		if(Gammas[i]->TalysCrossSection>20)
		{
			TLine l;
			cout<<Gammas[i]->Energy<<"\n";
			l.DrawLine(Gammas[i]->Energy,0,Gammas[i]->Energy,1e5);
			c.Print("Bug.pdf","pdf");
		}
		
	}
	c.Print("Bug.pdf]","pdf");

}