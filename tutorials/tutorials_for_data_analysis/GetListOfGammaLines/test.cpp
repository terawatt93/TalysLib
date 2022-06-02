#include "TalysLib.hh"

void test()
{
	Nucleus O("16O");
	O.GenerateProducts();
	vector<GammaTransition*> v=O.GetGammaTransitions();
	for(unsigned int i=0;i<v.size();i++)
	{
		if(abs(v[i]->Energy-3853)<2)
		{
			TGraph* g=v[i]->GetENDFAngularDistribution();
			TCanvas c;
			g->Draw("al");
			c.Print("Test.pdf");
		}
	}
}
