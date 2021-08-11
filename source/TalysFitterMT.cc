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
	if(Nucl==0)
	{
		Nucl=&(TFM->Nuclide);
		FillFitValues=true;
	}
	double result=0;
	TGraphErrors GraphForMultiFit=TFM->GraphForMultiFit;
	for(int i=0;i<GraphForMultiFit.GetN();i++)
	{
		double x,y,x_err,y_err;
		GraphForMultiFit.GetPoint(i,x,y);
		x_err=GraphForMultiFit.GetErrorX(i);
		y_err=GraphForMultiFit.GetErrorY(i);
		double FuncValue=TFM->GetEvaluationResult(x,TFM,Nucl);
		if(FillFitValues)
		{
			TFM->FitValues.SetPoint(i,x,FuncValue);
			/*int NP=TFM->FitValues.GetN();
			if(NP==0)
			{
				TFM->FitValues.SetPoint(0,x,FuncValue);
			}
			else 
			{
				double xF,yF;
				TFM->FitValues.GetPoint(NP-1,xF,yF);
				if(xF<x)
				TFM->FitValues.SetPoint(NP,x,FuncValue);
			}*/
		}
	//	cout<<"i:"<<i<<" x:"<<x<<" y:"<<y<<" f="<<FuncValue<<"\n";
		result+=pow(y-FuncValue,2)/(pow(x_err,2)+pow(y_err,2));
	}
	//cout<<"result:"<<result<<"\n";
	return result;
}

void EvalDiffInThread(TalysFitterMT *TFM, int VarNumber, double &result)
{
	//Nucleus Nucl(TFM->Nuclide.Name);
	Nucleus Nucl=TFM->Nuclide;
	Nucl.SetThreadNumber(TFM->InitThreadNumber+VarNumber);
	cout<<"THREAD:"<<TFM->InitThreadNumber+VarNumber<<"\n";
	Nucl.OMPN.SetDefaultOMP(TFM->Nuclide.OMPoptionN);
	Nucl.OMPP.SetDefaultOMP(TFM->Nuclide.OMPoptionP);
	vector<double> Par_tmp=TFM->Parameters;
	double Epsilon=TFM->EpsilonValues[VarNumber];
	Par_tmp[VarNumber]=TFM->Parameters[VarNumber]+Epsilon;
	TFM->ParAssignmentFunction(TFM,&Nucl,Par_tmp);
	Nucl.GenerateProducts();
	double Chi2Plus=EvalChi2(TFM,&Nucl);
	Par_tmp[VarNumber]=TFM->Parameters[VarNumber]-Epsilon;
	TFM->ParAssignmentFunction(TFM,&Nucl,Par_tmp);
	Nucl.GenerateProducts();
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
		GraphForMultiFit.SetPoint(NMPoints,x+Mv,y);
		GraphForMultiFit.SetPointError(NMPoints,x_err,y_err);
	}
}
void TalysFitterMT::DrawFitProgress()
{
	if(gPad==0)
	{
		new TCanvas();
	}
	TCanvas *c=gPad->GetCanvas();
	c->Clear();
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
			int NumberOfGraphs=GraphList->GetEntries();
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
