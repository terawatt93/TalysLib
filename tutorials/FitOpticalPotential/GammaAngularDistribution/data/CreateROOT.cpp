TGraphErrors ReadFromFile(string filename)
{
	TGraphErrors gr;
	ifstream ifs(filename);
	string line;
	int iter=0;
	vector<double> X,Y,EX,EY;
	while(getline(ifs,line))
	{
		stringstream st(line);
		double x,y,ex,ey;
		st>>x>>ex>>y>>ey;
		X.push_back(x);
		Y.push_back(y);
		EX.push_back(ex);
		EY.push_back(ey);
		
	}
	for(unsigned int i=0;i<X.size();i++)
	{
		for(unsigned int j=0;j<X.size()-1;j++)
		{
			if(X[j+1]<X[j])
			{
				swap(X[j+1],X[j]);
				swap(EX[j+1],EX[j]);
				swap(Y[j+1],Y[j]);
				swap(EY[j+1],EY[j]);
			}
		}
	}
	for(unsigned int i=0;i<X.size();i++)
	{
		gr.SetPoint(i,X[i],Y[i]);
		gr.SetPointError(i,EX[i],EY[i]);
	}
	//
	//	gr.SetPointError(iter,ex,ey);
	//	iter++;
	return gr;
}

TGraphErrors ScaleGammaGraph(TGraphErrors &gr)
{
	TF1 fit("fit","[0]*(1+[1]*ROOT::Math::legendre(2,cos(x/180.0*3.1416))+[2]*ROOT::Math::legendre(4,cos(x/180.0*3.1416)))",0,180);
	fit.SetParameter(0,20);
	fit.SetParameter(1,0.5);
	fit.SetParameter(2,-0.5);
	gr.Fit(&fit);
	TGraphErrors gr2;
	gr2.SetName(TString(gr.GetName())+"_Norm");
	gr2.SetTitle(TString(gr.GetTitle())+"_Norm");
	for(int i=0;i<gr.GetN();i++)
	{
		double x,y,ex,ey;
		gr.GetPoint(i,x,y);
		ex=gr.GetErrorX(i);
		ey=gr.GetErrorY(i);
		gr2.SetPoint(i,x,y/fit.GetParameter(0));
		gr2.SetPointError(i,ex,ey/fit.GetParameter(0));
	}
	return gr2;
}

void CreateROOT()
{
	TGraphErrors Elastic=ReadFromFile("neutrons/tangra_2021_(n,n0)_14_1MeV_cm_int_15-50_norm.txt");
	Elastic.SetName("Elastic");
	TGraphErrors Inelastic=ReadFromFile("neutrons/tangra_2021_(n,n1)_14_1MeV_cm_int_15-50_norm.txt");
	Inelastic.SetName("Inelastic");
	TFile f("gammas/CrossSection_c12_90perc_AngStep_5deg_fps_random.root");
	TGraphErrors Gammas=*((TGraphErrors*)f.Get("Cross_section_for_Gamma"));
	f.Close();
	Gammas.SetName("Gamma");
	TGraphErrors GammasNorm=ScaleGammaGraph(Gammas);

	TFile data("Data.root","RECREATE");
	data.WriteTObject(&Elastic);
	data.WriteTObject(&Inelastic);
	data.WriteTObject(&Gammas);
	data.WriteTObject(&GammasNorm);
	data.Close();
}