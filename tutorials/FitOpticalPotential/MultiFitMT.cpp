#include <iostream>
#include <TString.h>
#include <TSystem.h>
#include <vector>
#include <string>
#include "Parser.cpp"
#include <TalysLib.hh>
#include <TROOT.h>
#include <TMinuit.h>
#include <TVirtualFitter.h>

/*Данный пример показывает аппроксимацию дифсечений упругого и первого неупругого рассеяний на 12С с помощью TalysFitterMT.
 * В TalysFitterMT используется многопоточное вычисление производных, что позволяет сократить время подбора параметров*/
TalysFitterMT *tf;

void ParAssignmentFunction(TalysFitterMT *TF,Nucleus *Nucl, vector<double> Parameters)//функция, описывающая приписывание параметров из вектора Parameters ядру, которое происходит при каждом вычислении \chi^2
{
	Nucl->OMPN->PotentialKoning.v1=Parameters[0];//V_V
	Nucl->OMPN->PotentialKoning.w1=Parameters[1];//W_V
	Nucl->OMPN->PotentialKoning.d1=Parameters[2];//W_D
	Nucl->OMPN->PotentialKoning.vso1=Parameters[3];//=V_SO
	Nucl->OMPN->PotentialKoning.wso1=Parameters[4];//=W_SO
	Nucl->OMPN->PotentialKoning.Rv=Parameters[5];//r_V
	Nucl->OMPN->PotentialKoning.Av=Parameters[6];//a_V
	Nucl->OMPN->PotentialKoning.Rd=Parameters[7];//r_D
	Nucl->OMPN->PotentialKoning.Ad=Parameters[8];//a_D
	Nucl->OMPN->PotentialKoning.Rso=Parameters[9];//r_SO
	Nucl->OMPN->PotentialKoning.Aso=Parameters[10];//a_SO
	Nucl->WriteOMPOrUseKoningN=2;
	char Col_type='R';//тип коллективности ядра "S", "R", "V", "A", см. 
	//int LevelNumber=1;//номер уровня, для которого задаётся деформация
	char Level_type='R';//тип коллективности уровня: "D", "R", "V"
	vector<double> Deformations1;
	vector<double> null;
	Deformations1.push_back(Parameters[11]);
	null.push_back(0.0);
	Nucl->Def.SetTypeOfCollectivity(Col_type);//задаём тип коллективности для ядра
	Nucl->SetLevelDeformation(0,'R', -1, -1, -1, -1,&null);//деформацию для основного соостояния
	Nucl->SetLevelDeformation(4439.82,Level_type, -1, -1, -1, -1,&Deformations1);//деформацию для первого возб. состояния
	Nucl->WriteDeformation=true;

	std::cout<<"ParAssignmentFunction tells this:\n";
	std::cout<<"V_V = "<<Nucl->OMPN->PotentialKoning.v1<<"\n";//изменить значение величины v1 в опт. потенциале для нейтронов//=V_V 
	std::cout<<"W_V = "<<Nucl->OMPN->PotentialKoning.w1<<"\n";//=W_V  
	std::cout<<"W_D = "<<Nucl->OMPN->PotentialKoning.d1<<"\n";//=W_D 
	std::cout<<"V_so = "<<Nucl->OMPN->PotentialKoning.vso1<<"\n";//=V_SO  
	std::cout<<"W_so = "<<Nucl->OMPN->PotentialKoning.wso1<<"\n";//=W_SO  
	std::cout<<"Rv = "<<Nucl->OMPN->PotentialKoning.Rv<<"\n";//r_V
	std::cout<<"Av = "<<Nucl->OMPN->PotentialKoning.Av<<"\n";//a_V
	std::cout<<"Rd = "<<Nucl->OMPN->PotentialKoning.Rd<<"\n";//r_D
	std::cout<<"Ad = "<<Nucl->OMPN->PotentialKoning.Ad<<"\n";//a_D
	std::cout<<"Rso = "<<Nucl->OMPN->PotentialKoning.Rso<<"\n";//r_SO
	std::cout<<"Aso = "<<Nucl->OMPN->PotentialKoning.Aso<<"\n";//a_SO 
}

double GetEvaluationResult(double x_value,TalysFitterMT *PointetToTF,Nucleus *PointerToNucleus)//функция, возвращающая результат расчетов для данного значения x. Экспериментальные данные записаны в графике TalysFitterMT::GraphForMultiFit
{
	double CurrentOffset=0;
	int GraphIterator=0;
	PointetToTF->GetCurrentGraphNumberAndOffset(x_value,GraphIterator,CurrentOffset);//функция, вычисляющая номер графика, которому соответствует данный x и его сдвижку
	if(GraphIterator==0)//Каждому графику соответствует номер, в данном коде нулевой график-упругое рассеяние, первый -неупругое на 4.4 МэВ
	{
		TGraph *Elastic=PointerToNucleus->GetElasticAngularDistribution("Total");
		return Elastic->Eval(x_value,0,"S");
	}
	else if(GraphIterator==1)
	{
		TGraph *INL4=PointerToNucleus->FindProductByReaction("(n,n')")->Levels[1].GetAngularDistribution("Total");
		return INL4->Eval(x_value-CurrentOffset,0,"S");
	}
	return 0;
}

void FCN(Int_t&npar, Double_t*gin, Double_t&f, Double_t*par, Int_t flag)
{
	tf->FCN(npar,gin,f,par,flag);
	tf->DrawFitProgress();
}

void MultiFitMT()
{
	string NuclName="12C";
	ROOT::EnableThreadSafety();
	tf=new TalysFitterMT(NuclName);
	tf->Nuclide.GenerateProducts();
	Nucleus NuclForExpData(NuclName);
	NuclForExpData.GenerateProducts();
	TCanvas c1;	
	
	TMultiGraph *mgrElastic=NuclForExpData.GetEXFORTMultiGraphForAngularDistributions(14,14.5);
	TMultiGraph *mgrInelastic=NuclForExpData.FindProductByReaction("(n,n')")->Levels[1].GetEXFORTMultiGraphForAngularDistributions(14,14.5);
	
	TalysLibManager::Instance().SetC4Flag(false);
	
	/*tf->Nuclide.OMPN->PotentialKoning.v1=48.0;//=V_V
	tf->Nuclide.OMPN->PotentialKoning.v2=0.0;
	tf->Nuclide.OMPN->PotentialKoning.v3=0.0; 
	tf->Nuclide.OMPN->PotentialKoning.v4=0.0; 
	tf->Nuclide.OMPN->PotentialKoning.w1=1.0;//=W_V  
	tf->Nuclide.OMPN->PotentialKoning.w2=0.0; 
	tf->Nuclide.OMPN->PotentialKoning.d1=3;//=W_D 
	tf->Nuclide.OMPN->PotentialKoning.d2=0.0;
	tf->Nuclide.OMPN->PotentialKoning.d3=0.0;*/
	///зададим свойства подбираемых параметров:
	tf->SetParameter(0,tf->Nuclide.OMPN->PotentialKoning.v1,"V_{V}",0.1,20,70);
	tf->SetParameter(1,tf->Nuclide.OMPN->PotentialKoning.w1,"W_{V}",0.1,0,10);
	tf->SetParameter(2,tf->Nuclide.OMPN->PotentialKoning.d1,"W_{D}",0.1,0,10);
	tf->SetParameter(3,tf->Nuclide.OMPN->PotentialKoning.vso1,"V_{SO}",0.1,-1,10);
	tf->SetParameter(4,tf->Nuclide.OMPN->PotentialKoning.wso1,"W_{SO}",0.01,0,10);	
	tf->SetParameter(5,tf->Nuclide.OMPN->PotentialKoning.Rv,"r_{V}",0.001,0.5,2);
	tf->SetParameter(6,tf->Nuclide.OMPN->PotentialKoning.Av,"a_{V}",0.001,0.1,2);
	tf->SetParameter(7,tf->Nuclide.OMPN->PotentialKoning.Rd,"r_{D}",0.001,0.5,2);
	tf->SetParameter(8,tf->Nuclide.OMPN->PotentialKoning.Ad,"a_{D}",0.001,0.1,2);
	tf->SetParameter(9,tf->Nuclide.OMPN->PotentialKoning.Rso,"r_{SO}",0.001,0.5,2);
	tf->SetParameter(10,tf->Nuclide.OMPN->PotentialKoning.Aso,"a_{SO}",0.001,0.1,2);
	tf->SetParameter(11,-0.62,"#beta_{2}",0.001,-1,1);//это деформация, beta_2
	
	tf->ParAssignmentFunction=ParAssignmentFunction;
	tf->GetEvaluationResult=GetEvaluationResult;
	
	vector<TObject*> Graphs;
	Graphs.push_back(mgrElastic);
	Graphs.push_back(mgrInelastic);
	vector<double> Offsets;
	Offsets.push_back(0);
	Offsets.push_back(181);
	cout<<"size:"<<Offsets.size()<<"\n";
	tf->GenerateGraphForMultiFit(Graphs,Offsets);	
	
	tf->InitTVirtualFitter("Minuit");
	tf->Fitter->SetFCN(FCN);
	
	double arglist[100];
	arglist[0] = 1;
	// set print level
	tf->Fitter->ExecuteCommand("SET PRINT",arglist,3);
	int int_tmp=1;
	double GradOption[]={1};
	//minuit->ExecuteCommand("SET GRA",GradOption,1);
	tf->Fitter->ExecuteCommand("SET GRA",GradOption,1);

	// minimize
	arglist[0] = 5000; // number of function calls
	arglist[1] = 1; // tolerance
	tf->Fitter->ExecuteCommand("MIGRAD",arglist,2);
	tf->Fitter->ExecuteCommand("HESSE",0,0);
	
	TFile f("TestMultiFitMT.root","RECREATE");
	for(unsigned int i=0;i<tf->ParValuesGraphs.size();i++)
	{
		f.WriteTObject(&(tf->ParValuesGraphs[i]));
	}
	f.WriteTObject(&(tf->Chi2Values));
	
	TGraph *Elastic=tf->Nuclide.GetElasticAngularDistribution("Total","new");
	TGraph *INL4=tf->Nuclide.FindProductByReaction("(n,n')")->Levels[1].GetAngularDistribution("Total","new");
	f.WriteTObject(Elastic);
	f.WriteTObject(INL4);
	f.WriteTObject(&(tf->GraphForMultiFit));
	f.Close();
	c1.Clear();
	c1.Print("TestMultiFitMT.pdf[","pdf");
	gPad->SetLogy(1);
	mgrElastic->Draw("a plc pmc");
	Elastic->SetLineColor(2);
	Elastic->Draw("l");
	gPad->BuildLegend();
	c1.Print("TestMultiFitMT.pdf","pdf");
	mgrInelastic->Draw("a plc pmc");
	INL4->SetLineColor(2);
	INL4->Draw("l");
	gPad->BuildLegend();
	c1.Print("TestMultiFitMT.pdf","pdf");
	
	tf->GraphForMultiFit.Draw("ap");
	tf->FitValues.Draw("l");
	TPaveText p=tf->GenerateTPaveTextForFitResult();
	p.Draw();
	c1.Print("TestMultiFitMT.pdf","pdf");
	
	c1.Print("TestMultiFitMT.pdf]","pdf");
}

