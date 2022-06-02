//этот код проверяет корректность параметров ОМ
#include <TalysLib.hh>
void testOMP(string nucleus="56Fe")
{
	Nucleus Nuclide(nucleus);
	Nuclide.GenerateProducts();
	cout<<Nuclide.OMPN->DefaultOMP->GetInHumanReadable()<<"\n";
	TGraph gDefault=*(Nuclide.Products[0].Levels[1].GetAngularDistribution());
	Nuclide.SetOMPOption("n",1);
	Nuclide.GenerateProducts();
	cout<<Nuclide.OMPN->DefaultOMP->GetInHumanReadable()<<"\n";
	TGraph g1=*(Nuclide.Products[0].Levels[1].GetAngularDistribution());
	Nuclide.OMPN->SetVv(Nuclide.OMPN->GetVv());
	Nuclide.OMPN->SetWv(Nuclide.OMPN->GetWv());
	Nuclide.OMPN->SetVso(Nuclide.OMPN->GetVso());
	Nuclide.OMPN->SetWso(Nuclide.OMPN->GetWso());
	Nuclide.OMPN->SetWd(Nuclide.OMPN->GetWd());
	Nuclide.GenerateProducts();
	cout<<Nuclide.OMPN->DefaultOMP->GetInHumanReadable()<<"\n";
	TGraph g2=*(Nuclide.Products[0].Levels[1].GetAngularDistribution());
	TCanvas cc1;
	g1.SetLineColor(2);
	g2.SetLineColor(4);
	gDefault.Draw("al");
	g1.Draw("l");
	g2.Draw("l");
	cc1.Print("testOMP.pdf","pdf");
}
