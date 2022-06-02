void DrawEpsGraphs()
{
	vector<string> GrNames={"Epsilon_v1","Epsilon_v2","Epsilon_w1","Epsilon_w2","Epsilon_d1","Epsilon_d2","Epsilon_vso1","Epsilon_vso2","Epsilon_wso1","Epsilon_wso2"};
	TFile f("EpsilonValues.root");
	TCanvas c;
	c.Divide(3,4);
	for(unsigned int i=0;i<GrNames.size();i++)
	{
		TGraph *g=(TGraph*)f.Get(GrNames[i].c_str());
		c.cd(i+1);
		g->Draw("al");
		gPad->SetLogx(1);
	}
	c.Print("Var.png","png");
	f.Close();
}
