#include "../TalysLib.hh"
#include <sys/stat.h>

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

double EvalChi2(TalysFitterMTM2 *TFM,Nucleus* Nucl)
{
	bool FillFitValues=false;
	if(Nucl==0)
	{
		Nucl=&(TFM->Nuclide);
		FillFitValues=true;
	}
	double result;
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

void EvalDiffInThread2(TalysFitterMTM2 *TFM, int VarNumber, double &result)
{
	cout<<"StartEvalDiff:"<<VarNumber<<"\n";
	//Nucleus Nucl(TFM->Nuclide.Name);
	Nucleus Nucl=TFM->Nuclide;
	Nucl.SetThreadNumber(VarNumber);
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
	cout<<"EndEvalDiff"<<Chi2Plus<<" "<<Chi2Minus<<" Diff: "<<VarNumber<<" "<<result<<"\n";
}



vector<double> TalysFitterMTM2::EvalGrad()
{
	vector<double> result;
	result.resize(Parameters.size());
	vector<thread> threads;
	for(int i=0;i<Parameters.size();i++)
	{
		threads.emplace_back(EvalDiffInThread2,this,i,ref(result[i]));
	}
	for(unsigned int i=0;i<threads.size();i++)
	{
		threads[i].join();
	}
	/*for(int i=0;i<Parameters.size();i++)
	{
		EvalDiffInThread2(this,i, ref(result[i]));
	}*/
	/*cout<<" \n";
	result.Print();
	cout<<" \n";*/
	cout<<"Grad: ";
	for(unsigned int i=0;i<result.size();i++)
	{
		cout<<result[i]<<" ";
	}
	cout<<"\n";
	return result;
}

void TalysFitterMTM2::InitTVirtualFitter(string type)
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
	FitValues.SetLineColor(2);
	for(unsigned int i=0;i<Parameters.size();i++)
	{
		Fitter->SetParameter(i,ParNames[i].c_str(),Parameters[i],EpsilonValues[i],LowLimits[i],HighLimits[i]);
		ParValuesGraphs[i].SetName(ParNames[i].c_str());
		ParValuesGraphs[i].SetTitle((ParNames[i]+"; Iteration; Value").c_str());
	}
}
void TalysFitterMTM2::Minimize()
{
	// minimize
	double arglist[2];
	arglist[0] = 1000; // number of function calls
	arglist[1] = 0.01; // tolerance
	Fitter->ExecuteCommand("MIGRAD",arglist,2);
}
void TalysFitterMTM2::SetParameter(unsigned int n, double value, string name, double epsilon, double low, double high)
{
	if(Parameters.size()<=n)
	{
		Parameters.resize(n+1);
		ParNames.resize(n+1);
		EpsilonValues.resize(n+1);
		LowLimits.resize(n+1);
		HighLimits.resize(n+1);
	}
	Parameters[n]=value;
	ParNames[n]=name;
	EpsilonValues[n]=epsilon;
	LowLimits[n]=low;
	HighLimits[n]=high;
}

TalysFitterMTM2::TalysFitterMTM2(string NuclName)
{
	Nuclide=Nucleus(NuclName);
	Nuclide.AssignPointers();
}
void TalysFitterMTM2::EnableParTracking()
{
	ParTrackingFlag=true;
	//ParAssignmentFunction(this);
	ParChanged=false;
}
void TalysFitterMTM2::DisableParTracking()
{
	ParTrackingFlag=false;
}
void TalysFitterMTM2::TrackParChanges()
{
	if(ParTrackingFlag)
	{
		if(PreviousParameters.size()!=Parameters.size())
		{
			PreviousParameters=Parameters;
			ParChanged=true;
			//Size=Parameters.size();
			return;
		}
		for(int i=0;i<PreviousParameters.size();i++)
		{
			if(PreviousParameters[i]!=Parameters[i])
			{
				PreviousParameters=Parameters;
				ParChanged=true;
				return;
			}
		}
		ParChanged=false;
	}
}
void TalysFitterMTM2::AddToGraphForMultiFit(TGraphErrors *gr, double Mv)
{
	for(unsigned int i=0;i<gr->GetN();i++)
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
void TalysFitterMTM2::DrawFitProgress()
{
	if(gPad==0)
	{
		TCanvas *c=new TCanvas();
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
void TalysFitterMTM2::FCN(int &npar, double *gin, double &f, double *par, int flag)
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
		Chi2Values.SetPoint(Chi2Values.GetN(),Chi2Values.GetN(),f);
		break;
	}
}
/*TPaveText TalysFitterMTM2::GenerateTPaveTextForFitResult(double x1,double y1,double x2,double y2,string Option)
{
	TPaveText result(x1,y1,x2,y2,Option.c_str());
	result.AddText("Fit results");
	result.AddText(("#chi^{2} / NDF="+to_string(FitFunction.GetChisquare()/(double)FitFunction.GetNDF())).c_str());
	for(unsigned int i=0;i<FitFunction.GetNpar();i++)
	{
		result.AddText((string(FitFunction.GetParName(i))+":"+to_string(FitFunction.GetParameter(i))+"#pm"+to_string(FitFunction.GetParError(i))).c_str());
	}
	return result;
}*/
void TalysFitterMTM2::GenerateGraphForMultiFit(vector<TObject*> &PointersToGraphs,vector<double> &_Offsets)
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
			for(unsigned int j=0;j<NumberOfGraphs;j++)
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
}
