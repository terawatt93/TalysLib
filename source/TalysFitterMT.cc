#include "../TalysLib.hh"
#include <sys/stat.h>
#include "TalysLibManager.cc"
#include <bits/stdc++.h>
#include <cstring>
#include <algorithm>
#include <cctype>
#include "../Parser.cpp"
#include <TLine.h>
#include <TText.h>
#include <TList.h>
#include <TKey.h>
#include "SpinParity.cc"
#include "OMP.cc"
#include "Deformations.cc"
#include "GammaTransitions.cc"
#include "LevelProperties.cc"
#include "NucleiProperties.cc"

double EvalChi2(TalysFitterMT *TFM,Nucleus* Nucl)
{
	bool FillFitValues=false;
	double result=0;
	if(Nucl==0)
	{
		Nucl=&(TFM->Nuclide);
		FillFitValues=true;
	}
	
	/*if(TFM->UseC4&&TFM->C4DataForFit.size()>0)
	{
		for(unsigned int i=0;i<TFM->C4DataForFit.size();i++)
		{
			result+=TFM->C4DataForFit[i]->EvalChi2(Nucl);
		}
	}*/
	//else
	{
		TGraphErrors GraphForMultiFit=TFM->GraphForMultiFit;
		for(int i=0;i<GraphForMultiFit.GetN();i++)
		{
			double x,y,x_err,y_err;
			GraphForMultiFit.GetPoint(i,x,y);
			x_err=GraphForMultiFit.GetErrorX(i);
			y_err=GraphForMultiFit.GetErrorY(i);
			double FuncValue=TFM->GetEvaluationResult(x,TFM,Nucl);
			//cout<<"Chi2:x,y,x_err,y_err"<<x<<" "<<y<<" "<<x_err<<" "<<y_err<<"\n";
			if(FillFitValues)
			{
				TFM->FitValues.SetPoint(i,x,FuncValue);
			}
			if((!isnan(x))&&(!isnan(y))&&(!isnan(x_err))&&(!isnan(y_err)))
			{
				if(((x_err>0)||(y_err>0)))
				{
					result+=pow(y-FuncValue,2)/(pow(x_err,2)+pow(y_err,2));
				}
				else
				{
					result+=pow(y-FuncValue,2);
				}
			}
		}
	}
	//cout<<"result:"<<result<<"\n";
	return result;
}

double EvalChi2Init(TalysFitterMT *TFM,Nucleus* Nucl)
{
	if(Nucl==0)
	{
		Nucl=&(TFM->Nuclide);
	}
	double result=0;
	TGraph *Init=&(TFM->InitValues);
	if(TFM->UseC4)
	{
		for(unsigned i=0;i<TFM->C4DataForFit.size();i++)
		{
			result+=TFM->C4DataForFit[i]->EvalChi2(Nucl);
		}
	}
	for(int i=0;i<Init->GetN();i++)
	{
		double x,y;
		Init->GetPoint(i,x,y);
		double FuncValue=TFM->GetEvaluationResult(x,TFM,Nucl);
		result+=pow(y-FuncValue,2);
	}
	//cout<<"result:"<<result<<"\n";
	return result;
}

void EvalDiffInThread(TalysFitterMT *TFM, int VarNumber, double &result)
{
	//Nucleus Nucl(TFM->Nuclide.Name);
	Nucleus Nucl=TFM->Nuclide;
	Nucl.ProjectileEnergy=TFM->ProjectileEnergy;
	if(TFM->UseC4&&TFM->C4DataForFit.size()>0)
	{
		Nucl.EnergyGrid=TFM->EnergyGrid;
		Nucl.UseEnergyGrid=true;
	}
	Nucl.SetThreadNumber(TFM->InitThreadNumber+VarNumber);
	cout<<"THREAD:"<<TFM->InitThreadNumber+VarNumber<<"\n";
	Nucl.OMPN->SetDefaultOMP(TFM->Nuclide.OMPoptionN);
	Nucl.OMPP->SetDefaultOMP(TFM->Nuclide.OMPoptionP);
	vector<double> Par_tmp=TFM->Parameters;
	//double Epsilon=TFM->EpsilonValues[VarNumber];
	//test
	//double Epsilon=0.02;
	double Epsilon=TFM->EpsilonValues[VarNumber];//0.0454545/100;
	Par_tmp[VarNumber]=TFM->Parameters[VarNumber]+Epsilon;
	TFM->ParAssignmentFunction(TFM,&Nucl,Par_tmp);
	Nucl.GenerateProducts(TFM->Projectile);
	double Chi2Plus=EvalChi2(TFM,&Nucl);
	
	/*Nucl=TFM->Nuclide;
	Nucl.SetThreadNumber(TFM->InitThreadNumber+VarNumber);
	cout<<"THREAD:"<<TFM->InitThreadNumber+VarNumber<<"\n";
	Nucl.OMPN->SetDefaultOMP(TFM->Nuclide.OMPoptionN);
	Nucl.OMPP->SetDefaultOMP(TFM->Nuclide.OMPoptionP);*/
	
	Par_tmp[VarNumber]=TFM->Parameters[VarNumber]-Epsilon;
	TFM->ParAssignmentFunction(TFM,&Nucl,Par_tmp);
	Nucl.GenerateProducts(TFM->Projectile);
	double Chi2Minus=EvalChi2(TFM,&Nucl);
	result=(Chi2Plus-Chi2Minus)/(2*Epsilon);
	
}



vector<double> TalysFitterMT::EvalGrad()
{
	vector<double> result;
	result.resize(Parameters.size());
	vector<thread> threads;
	for(unsigned int i=0;i<Parameters.size();i++)
	{
		threads.emplace_back(EvalDiffInThread,this,i,ref(result[i]));
	}
	for(unsigned int i=0;i<threads.size();i++)
	{
		threads[i].join();
	}
	return result;
}

void TalysFitterMT::InitTVirtualFitter(string type)
{
	if(Parameters.size()==0)
	{
		cout<<"This is TalysFitterMT::InitTVirtualFitter(...) error: Parameters vector is not initialized! Set the parameters first!\n";
		return;
	}
	TVirtualFitter::SetDefaultFitter(type.c_str());
	Fitter = TVirtualFitter::Fitter(0,Parameters.size());
	ParValuesGraphs.resize(Parameters.size());
	Chi2Values.SetName("chi2");
	Chi2Values.SetTitle("#chi^{2}; Iteration; Value");
	FitValues.SetName("Fit");
	FitValues.SetTitle("Fit");
	InitValues.SetName("InitCalculation");
	InitValues.SetTitle("Calculation results with initial parameters");
	FitValues.SetLineColor(2);
	for(unsigned int i=0;i<Parameters.size();i++)
	{
		TString GraphName(ParNames[i].c_str());
		GraphName.ReplaceAll("#","");
		GraphName.ReplaceAll("{","");
		GraphName.ReplaceAll("}","");
		GraphName.ReplaceAll("(","");
		GraphName.ReplaceAll(")","");
		Fitter->SetParameter(i,ParNames[i].c_str(),Parameters[i],EpsilonValues[i],LowLimits[i],HighLimits[i]);
		ParValuesGraphs[i].SetName(ParNames[i].c_str());
		ParValuesGraphs[i].SetTitle((ParNames[i]+"; Iteration; Value").c_str());
	}
	ParAssignmentFunction(this,&Nuclide,Parameters);
	ParAssignmentFunction(this,&InitNuclide,Parameters);
	InitNuclide.GenerateProducts();
	for(int i=0;i<GraphForMultiFit.GetN();i++)
	{
		double x,y;
		GraphForMultiFit.GetPoint(i,x,y);
		double FuncValue=GetEvaluationResult(x,this,&InitNuclide);
		InitValues.SetPoint(i,x,FuncValue);
	}
}
void TalysFitterMT::Minimize(int NCalls, double tolerance)
{
	// minimize
	double arglist[2];
	arglist[0] = NCalls; // number of function calls
	arglist[1] = tolerance; // tolerance
	Fitter->ExecuteCommand("MIGRAD",arglist,2);
	double LastChi2,InitChi2,it;
	if(Chi2Values.GetN()>0)
	{
		Chi2Values.GetPoint(Chi2Values.GetN()-1,it,LastChi2);
		Chi2Values.GetPoint(0,it,InitChi2);
	}
	if(LastChi2>BestChi2)
	{
		cout<<"This is TalysFitterMT::Minimize(): Last LastChi2>BestChi2, possible problems in fit! BestChi2 will be used!\n";
		Nuclide=BestNuclide.Copy();
		Chi2Values.SetPoint(Chi2Values.GetN(),Chi2Values.GetN(),BestChi2);
		for(int i=0;i<GraphForMultiFit.GetN();i++)
		{
			double x,y;
			GraphForMultiFit.GetPoint(i,x,y);
			double FuncValue=GetEvaluationResult(x,this,&Nuclide);
			FitValues.SetPoint(i,x,FuncValue);
		}
	}
}
void TalysFitterMT::SetParameter(unsigned int n, double value, string name, double epsilon, double low, double high)
{
	if(Parameters.size()<=n)
	{
		InitParameters.resize(n+1);
		Parameters.resize(n+1);
		ParNames.resize(n+1);
		EpsilonValues.resize(n+1);
		LowLimits.resize(n+1);
		HighLimits.resize(n+1);
	}
	Parameters[n]=value;
	InitParameters[n]=value;
	ParNames[n]=name;
	EpsilonValues[n]=epsilon;
	LowLimits[n]=low;
	HighLimits[n]=high;
}
void TalysFitterMT::SetParameter(unsigned int n, double value, string name, double epsilon, double range)
{
	if(Parameters.size()<=n)
	{
		InitParameters.resize(n+1);
		Parameters.resize(n+1);
		ParNames.resize(n+1);
		EpsilonValues.resize(n+1);
		LowLimits.resize(n+1);
		HighLimits.resize(n+1);
	}
	Parameters[n]=value;
	InitParameters[n]=value;
	ParNames[n]=name;
	EpsilonValues[n]=epsilon;
	LowLimits[n]=value*(1-range/100.0);
	HighLimits[n]=value*(1+range/100.0);
}

TalysFitterMT::TalysFitterMT(string NuclName, unsigned int ThreadNumber)
{
	InitThreadNumber=ThreadNumber;
	cout<<"InitThreadNumber"<<InitThreadNumber<<"\n";
	Nuclide=Nucleus(NuclName);
	Nuclide.SetThreadNumber(InitThreadNumber);
	InitNuclide=Nucleus(NuclName);
	InitNuclide.SetThreadNumber(InitThreadNumber);
	InitNuclide.AssignPointers();
	Nuclide.AssignPointers();
}
void TalysFitterMT::AddToGraphForMultiFit(TGraphErrors *gr, double Mv)
{
	for(int i=0;i<gr->GetN();i++)
	{
		double x,y,x_err,y_err;
		gr->GetPoint(i,x,y);
		x_err=gr->GetErrorX(i);
		y_err=gr->GetErrorY(i);
		int NMPoints=GraphForMultiFit.GetN();
		if((x>=0)&&(y>=0))
		{
			//cout<<"x,y,x_err,y_err"<<x+Mv<<" "<<y<<" "<<x_err<<" "<<y_err<<"\n";
			GraphForMultiFit.SetPoint(NMPoints,x+Mv,y);
			GraphForMultiFit.SetPointError(NMPoints,x_err,y_err);
		}
	}
}

void TalysFitterMT::AddToGraphForMultiFit(TGraph *gr, double Mv)
{
	for(int i=0;i<gr->GetN();i++)
	{
		double x,y,x_err,y_err;
		gr->GetPoint(i,x,y);
		x_err=0;
		y_err=0;
		int NMPoints=GraphForMultiFit.GetN();
		if((x>=0)&&(y>=0))
		{
			GraphForMultiFit.SetPoint(NMPoints,x+Mv,y);
			GraphForMultiFit.SetPointError(NMPoints,x_err,y_err);
		}
		
	}
}

double TalysFitterMT::EvalInitDiff(int parNumber, double Epsilon)
{
	vector<double> ParametersTMP=Parameters;
	ParametersTMP[parNumber]=Parameters[parNumber]-Epsilon;
	Nucleus Nucl=Nuclide;
	ParAssignmentFunction(this,&Nucl,ParametersTMP);
	
	Nucl.SetThreadNumber(InitThreadNumber+parNumber);
	Nucl.SetProjectileEnergy(ProjectileEnergy);
	Nucl.GenerateProducts(Projectile);
	//double Chi2Minus=EvalChi2Init(this,&Nucl);
	double Chi2Minus=EvalChi2(this,&Nucl);
	//Chi2Minus:"<<Chi2Minus<<"\n";
	ParametersTMP[parNumber]=Parameters[parNumber]+Epsilon;
	ParAssignmentFunction(this,&Nucl,ParametersTMP);
	Nucl.SetProjectileEnergy(ProjectileEnergy);
	Nucl.GenerateProducts(Projectile);
	//cout<<"Chi2Plus:"<<Chi2Minus<<"\n";
	//double Chi2Plus=EvalChi2Init(this,&Nucl);
	double Chi2Plus=EvalChi2(this,&Nucl);
	return (Chi2Plus-Chi2Minus)/(2*Epsilon);
}

void TalysFitterMT::EstimateEpsilonValues()//функция, оценивающая величины эпсилон для каждого из параметров
{
	vector<thread> threads;
	InitThreadNumber=1000;
	//thread t1(thread(&TalysFitterMT::EstimateEpsilonValueForParameterThread,this,0,&EpsilonValues[0]));
	for(unsigned int i=0;i<Parameters.size();i++)
	{
		threads.emplace_back(&TalysFitterMT::EstimateEpsilonValueForParameterThread,this,0,&EpsilonValues[0]);
	}
	for(unsigned int i=0;i<threads.size();i++)
	{
		threads[i].join();
	}
}

void  TalysFitterMT::EstimateEpsilonValueForParameterThread(int parNumber, double *result)
{
	double resValue=EstimateEpsilonValueForParameter(parNumber);
	*result=resValue;
}

double TalysFitterMT::EstimateEpsilonValueForParameter(int parNumber)
{
	if(parNumber>=(int)InitParameters.size())
	{
		cout<<"This is TalysFitterMT::EstimateEpsilonValueForParameter("<<parNumber<<"): size of InitParameters is "<<InitParameters.size()<<" that is less than parNumber! NaN returned\n";
		return NAN;
	}
	double Epsilon=abs(InitParameters[parNumber])/1e4;
	double LeftLimit=Epsilon,RidhtLimit=Epsilon;
	double Diff=EvalInitDiff(parNumber,Epsilon);
	//cout<<"Epsilon:"<<Epsilon<<"\n";
	while(Diff==0)
	{
		Diff=EvalInitDiff(parNumber,Epsilon);
		if(Diff==0)
		{
			LeftLimit=Epsilon;
		}
		else
		{
			RidhtLimit=Epsilon;
			break;
		}
		//cout<<"Epsilon (while:):"<<Epsilon<<"\n";
		Epsilon=2*Epsilon;
	}
	double Middle=(LeftLimit+RidhtLimit)/2;
	double StopCriterium=abs(RidhtLimit-LeftLimit)/RidhtLimit;
	
	while(StopCriterium>0.01)
	{
		Diff=EvalInitDiff(parNumber,Middle);
		if(Diff==0)
		{
			LeftLimit=Middle;
		}
		else
		{
			Epsilon=Middle;
			RidhtLimit=Middle;
		}
		//cout<<"Middle:"<<Middle<<" "<<Diff<<" "<<LeftLimit<<" "<<RidhtLimit<<"\n";
		StopCriterium=abs(RidhtLimit-LeftLimit)/RidhtLimit;
		Middle=(LeftLimit+RidhtLimit)/2;
	}
	return Epsilon;
}

void TalysFitterMT::DrawFitProgress()
{
	if(gPad==0)
	{
		new TCanvas("c","c",1024,1450);
	}
	TCanvas *c=gPad->GetCanvas();
	c->Clear();
	if(!UseC4)
	{
		c->Divide(1,2);
		c->cd(1);
		Chi2Values.Draw("al");
		gPad->SetLogy(1);
		c->cd(2);
		GraphForMultiFit.Draw("ap");
		FitValues.Draw("l");
		gPad->SetLogy(1);
		c->Update();
	}
	else
	{
		int nx,ny;
		nx=sqrt(C4DataForFit.size());
		ny=(C4DataForFit.size())/nx+1;
		
		vector<TPad*> Pads=GeneratePadsOnCanvas(0.1,0.1,0.9,0.7,nx,ny,c);
		TPad *p=new TPad("p","p",0.1,0.8,0.9,0.9);
		p->Draw();
		p->cd();
		Chi2Values.Draw("al");
		for(unsigned int i=0;i<C4DataForFit.size();i++)
		{
			Pads[i]->cd();
			C4DataForFit[i]->DrawWithCalculationResult("alp",&Nuclide);
		}
	}
}
void TalysFitterMT::FCN(int &npar, double *gin, double &f, double *par, int flag)
{
	vector<double> grad;
	for(unsigned int i=0;i<Parameters.size();i++)
	{
		Parameters[i]=par[i];
	}
	
	switch(flag)
	{
		case 1: 

		break;
		case 2:
			grad=EvalGrad();
			for(unsigned int i=0;i<grad.size();i++)
			{
				gin[i]=grad[i];
			}
		break;
		case 3:
			ParAssignmentFunction(this,&Nuclide,Parameters);
			Nuclide.GenerateProducts();
			f=EvalChi2(this,0);
		break;
		default:
		ParAssignmentFunction(this,&Nuclide,Parameters);
		if((ParValuesGraphs.size()==Parameters.size())&&(ParValuesGraphs.size()>0))
		{
			int NPoints=ParValuesGraphs[0].GetN();
			for(unsigned int i=0;i<ParValuesGraphs.size();i++)
			{
				ParValuesGraphs[i].SetPoint(NPoints,NPoints,Parameters[i]);
			}
		}
		
		Nuclide.GenerateProducts();
		f=EvalChi2(this,0);
		if(f<BestChi2)
		{
			BestChi2=f;
			BestNuclide=Nuclide.Copy();
		}
		Chi2Values.SetPoint(Chi2Values.GetN(),Chi2Values.GetN(),f);
		break;
	}
}
void TalysFitterMT::GetCurrentGraphNumberAndOffset(double x, int &GraphIterator, double &Offset)
{
	Offset=0;
	GraphIterator=0;
	bool FoundInterval=false;
	for(unsigned int i=0;i<Offsets.size();i++)
	{
		if(i>0)
		{
			if((x>=Offsets[i-1])&&(x<=Offsets[i]))
			{
				GraphIterator=i-1;
				Offset=Offsets[i-1];
				FoundInterval=true;
			}
		}
	}
	if(!FoundInterval)
	{
		GraphIterator=Offsets.size()-1;
		Offset=Offsets[Offsets.size()-1];
	}
	
}
TPaveText TalysFitterMT::GenerateTPaveTextForFitResult(double x1,double y1,double x2,double y2,string Option)
{
	TPaveText result(x1,y1,x2,y2,Option.c_str());
	result.AddText("Fit results");
	double LastChi2,InitChi2,it;
	if(Chi2Values.GetN()>0)
	{
		Chi2Values.GetPoint(Chi2Values.GetN()-1,it,LastChi2);
		Chi2Values.GetPoint(0,it,InitChi2);
	}
	
	result.AddText(("#chi^{2} / NDF="+to_string(LastChi2/GraphForMultiFit.GetN())+" (init:"+to_string(InitChi2/GraphForMultiFit.GetN())+")").c_str());
	cout<<"#chi^{2} / NDF="+to_string(LastChi2/GraphForMultiFit.GetN())<<"\n";
	for(unsigned int i=0;i<Parameters.size();i++)
	{
		result.AddText(TString::Format("%s: %.3f#pm %.3f (init:%.3f)",ParNames[i].c_str(),Fitter->GetParameter(i),Fitter->GetParError(i),InitParameters[i]));
		//cout<<string(ParNames[i])+":"+to_string(Fitter->GetParameter(i))+"#pm"+to_string(Fitter->GetParError(i))<<"\n";
	}
	result.SetFillColor(0);
	result.SetBorderSize(1);
	return result;
}
void TalysFitterMT::GenerateGraphForMultiFit(vector<TObject*> &PointersToGraphs,vector<double> &_Offsets)
{
	Offsets=_Offsets;
	if(PointersToGraphs.size()!=Offsets.size())
	{
		cout<<"Cannot set TGraph for MultiFit: sizes of Graphs and Offsets are not same!\n";
		return ;
	}
	Offsets=_Offsets;
	for(unsigned int i=0;i<PointersToGraphs.size();i++)
	{
		if(PointersToGraphs[i]->InheritsFrom("TMultiGraph"))
		{
			TList* GraphList=((TMultiGraph*)PointersToGraphs[i])->GetListOfGraphs();
			cout<<"i="<<i<<"\n";
			if(!GraphList)
			{
				cout<<"!GraphList\n";
			}
			int NumberOfGraphs=GraphList->GetEntries();
			cout<<"NumberOfGraphs:"<<NumberOfGraphs<<"\n";
			for(int j=0;j<NumberOfGraphs;j++)
			{
				TObject* obj=GraphList->At(j);
				if(obj->InheritsFrom("TGraphErrors"))
				{
					AddToGraphForMultiFit((TGraphErrors*)obj,Offsets[i]);
				}
			}
			TIter next(GraphList);
		}
		else if(PointersToGraphs[i]->InheritsFrom("TGraphErrors"))
		{
			AddToGraphForMultiFit((TGraphErrors*)PointersToGraphs[i],Offsets[i]);
		}
		else if(PointersToGraphs[i]->InheritsFrom("TGraph"))
		{
			AddToGraphForMultiFit((TGraph*)PointersToGraphs[i],Offsets[i]);
		}
	}
	GraphForMultiFit.Sort();
	GraphForMultiFit.SetName("MultiFitGraph");
	GraphForMultiFit.SetTitle("MultiFitGraph");
}
void TalysFitterMT::SaveToRootFile(TFile *f)
{
	if(!f)
	{
		cout<<"This is TalysFitterMT::SaveToRootFile() error: invalid pointer to TFile. Returned\n";
		return ;
	}
	InitNuclide.SaveToRootFile(f,"Init");
	Nuclide.SaveToRootFile(f,"Final");
	for(unsigned int i=0;i<ParValuesGraphs.size();i++)
	{
		f->WriteTObject(&ParValuesGraphs[i]);
	}
	f->WriteTObject(&Chi2Values);
	f->WriteTObject(&FitValues);
	f->WriteTObject(&GraphForMultiFit);
	f->WriteTObject(&InitValues);
}
void TalysFitterMT::AddC4GraphVector(vector<TGraphErrors*> ExpData)
{
	for(unsigned int i=0;i<ExpData.size();i++)
	{
		C4Graph* data=(C4Graph*)ExpData[i];
		C4DataForFit.push_back(data);
		vector<double> ProjectileEnergies=data->GetProjectileEnergies();//в С4 приняты энергии в эВ!
		for(unsigned int j=0;j<ProjectileEnergies.size();j++)
		{
			ProjectileEnergies[j]=ProjectileEnergies[j]/1e6;
		}
		//сразу же сгенерируем сетку энергий:
		EnergyGrid.insert(EnergyGrid.end(), ProjectileEnergies.begin(), ProjectileEnergies.end());
	}
	sort( EnergyGrid.begin(), EnergyGrid.end() );
	EnergyGrid.erase( unique( EnergyGrid.begin(), EnergyGrid.end() ), EnergyGrid.end() );
	UseC4=true;
	Nuclide.EnergyGrid=EnergyGrid;
	Nuclide.UseEnergyGrid=true;
	InitNuclide.EnergyGrid=EnergyGrid;
	InitNuclide.UseEnergyGrid=true;
}

