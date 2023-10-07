#include "TalysLib.hh"

void TestENDFStat()
{
	TH1::AddDirectory(false);
	ENDFAnalyser a;
	vector<int> MT, MF;
	MT.push_back(51);
	MF.push_back(4);
	vector<vector<TH2F> > v=a.GetNZDistributionForTables("n",MT,MF);
	v[0][0].DrawClone("colz");
	TFile f("ENDFStat.root","recreate");
	f.WriteTObject(&v[0][0]);
	f.Close();
}
