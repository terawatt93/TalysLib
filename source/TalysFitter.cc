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
TalysFitter::TalysFitter(string NuclName)
{
	Nuclide=Nucleus(NuclName);
	Nuclide.AssignPointers();
}
void TalysFitter::EnableParTracking()
{
	ParTrackingFlag=true;
	ParAssignmentFunction(this);
	ParChanged=false;
}
void TalysFitter::DisableParTracking()
{
	ParTrackingFlag=false;
}
void TalysFitter::TrackParChanges()
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
		for(unsigned int i=0;i<PreviousParameters.size();i++)
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
double TalysFitter::Eval(double *x, double *p)
{
	for(unsigned int i=0;i<Parameters.size();i++)
	{
		Parameters[i]=p[i];
	}
	x_val=x[0];
	TrackParChanges();
	if(ParChanged)
	{
		ParAssignmentFunction(this);
		Nuclide.GenerateProducts();
	}
	if(!Calculated)
	{
		Nuclide.GenerateProducts();
		Calculated=true;
	}
	return GetEvaluationResult(x_val,this);
}
TF1 *TalysFitter::GenerateTF1(string name, double x_min,double x_max)
{
	FitFunction=TF1(name.c_str(),this,&TalysFitter::Eval,x_min,x_max,Parameters.size(),"TalysFitter","Eval");
	for(unsigned int i=0;i<Parameters.size();i++)
	{
		FitFunction.SetParameter(i,Parameters[i]);
	}
	for(unsigned int i=0;i<ParNames.size();i++)
	{
		if(i==Parameters.size())
		break;
		FitFunction.SetParName(i,ParNames[i].c_str());
	}
	GeneratedTF1=true;
	return &FitFunction;
}
void TalysFitter::AddToGraphForMultiFit(TGraphErrors *gr, double Mv)
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
void TalysFitter::FitMulti()
{
	if(GraphForMultiFit.GetN()==0)
	{
		cout<<"This is TalysFitter::FitMulti() function: GraphForMultiFit is empty\n";//продолжить тут
		return ;
	}
	if(!GeneratedTF1)
	{
		cout<<"This is TalysFitter::FitMulti() function: The fit function is not generated. Generate it first!\n";//продолжить тут
		return ;
	}
	GraphForMultiFit.Fit(&FitFunction);
}
TPaveText TalysFitter::GenerateTPaveTextForFitResult(double x1,double y1,double x2,double y2,string Option)
{
	TPaveText result(x1,y1,x2,y2,Option.c_str());
	result.AddText("Fit results");
	result.AddText(("#chi^{2} / NDF="+to_string(FitFunction.GetChisquare()/(double)FitFunction.GetNDF())).c_str());
	for(int i=0;i<FitFunction.GetNpar();i++)
	{
		result.AddText((string(FitFunction.GetParName(i))+":"+to_string(FitFunction.GetParameter(i))+"#pm"+to_string(FitFunction.GetParError(i))).c_str());
	}
	return result;
}
void TalysFitter::GenerateGraphForMultiFit(vector<TObject*> &PointersToGraphs,vector<double> &_Offsets)
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
}
