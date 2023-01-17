#include "Parser.cpp"
#include <TalysLib.hh>
#include <TROOT.h>
#include <TMinuit.h>

double EvalChi2(TGraph *GrForFit,Nucleus* Nucl)
{
	double result=0;
	for(int i=0;i<GrForFit->GetN();i++)
	{
		double x=0,y=0,FuncValue=0;
		GrForFit->GetPoint(i,x,y);
		if(x>180)
		{
			FuncValue=Nucl->Products[0].Levels[1].GetAngularDistribution()->Eval(x-180);
		}
		else
		{
			FuncValue=Nucl->GetElasticAngularDistribution()->Eval(x);
		}
		result+=pow(y-FuncValue,2);
	}
	return result;
}
void AddToGraphForFit(TGraph *TargetGraph,TGraph *Data, double Mv)
{
	for(int i=0;i<Data->GetN();i++)
	{
		double x,y;
		Data->GetPoint(i,x,y);
		int NMPoints=TargetGraph->GetN();
		TargetGraph->SetPoint(NMPoints,x+Mv,y);
	}
}

void ParAssignmentFunction(Nucleus *Nucl, vector<double> Parameters)//функция, описывающая приписывание параметров из вектора Parameters ядру, которое происходит при каждом вычислении \chi^2
{
	Nucl->OMPN->PotentialKoning.v1=Parameters[0];//V_V
	Nucl->OMPN->PotentialKoning.v2=Parameters[1];
	Nucl->OMPN->PotentialKoning.w1=Parameters[2];
	Nucl->OMPN->PotentialKoning.w2=Parameters[3];
	Nucl->OMPN->PotentialKoning.d1=Parameters[4];
	Nucl->OMPN->PotentialKoning.d2=Parameters[5];
	Nucl->OMPN->PotentialKoning.vso1=Parameters[6];
	Nucl->OMPN->PotentialKoning.vso2=Parameters[7];
	Nucl->OMPN->PotentialKoning.wso1=Parameters[8];
	Nucl->OMPN->PotentialKoning.wso2=Parameters[9];
	/*Nucl->OMPN->PotentialKoning.w1=Parameters[1];//W_V
	Nucl->OMPN->PotentialKoning.d1=Parameters[2];//W_D
	Nucl->OMPN->PotentialKoning.vso1=Parameters[3];//=V_SO
	Nucl->OMPN->PotentialKoning.wso1=Parameters[4];//=W_SO
	Nucl->OMPN->PotentialKoning.Rv=Parameters[5];//r_V
	Nucl->OMPN->PotentialKoning.Av=Parameters[6];//a_V
	Nucl->OMPN->PotentialKoning.Rd=Parameters[7];//r_D
	Nucl->OMPN->PotentialKoning.Ad=Parameters[8];//a_D
	Nucl->OMPN->PotentialKoning.Rso=Parameters[9];//r_SO
	Nucl->OMPN->PotentialKoning.Aso=Parameters[10];//a_SO*/
	Nucl->WriteOMPOrUseKoningN=2;
	/*char Col_type='R';//тип коллективности ядра "S", "R", "V", "A", см. 
	//int LevelNumber=1;//номер уровня, для которого задаётся деформация
	char Level_type='R';//тип коллективности уровня: "D", "R", "V"
	vector<float> Deformations1;
	vector<float> null;
	Deformations1.push_back(Parameters[11]);
	null.push_back(0.0);
	Nucl->Def.SetTypeOfCollectivity(Col_type);//задаём тип коллективности для ядра
	Nucl->SetLevelDeformation(0,'R', -1, -1, -1, -1,&null);//деформацию для основного соостояния
	Nucl->SetLevelDeformation(4439.82,Level_type, -1, -1, -1, -1,&Deformations1);//деформацию для первого возб. состояния
	Nucl->WriteDeformation=true;*/

}

double EvalDiff(Nucleus Nuclide,TGraph *GrForFit,vector<double> Parameters,int ParNumber,vector<double> Epsilon)
{
	Nuclide.SetThreadNumber(ParNumber);
	Nuclide.OMPN->SetDefaultOMP(2);
	Nuclide.OMPP->SetDefaultOMP(2);
	vector<double> ParPlus=Parameters;
	vector<double> ParMinus=Parameters;
	ParAssignmentFunction(&Nuclide,ParPlus);
	
	ParPlus[ParNumber]=Parameters[ParNumber]+Epsilon[ParNumber];
	ParMinus[ParNumber]=Parameters[ParNumber]-Epsilon[ParNumber];
	ParAssignmentFunction(&Nuclide,ParPlus);
	Nuclide.GenerateProducts();
	double Chi2Plus=EvalChi2(GrForFit,&Nuclide);
	ParAssignmentFunction(&Nuclide,ParMinus);
	Nuclide.GenerateProducts();
	double Chi2Minus=EvalChi2(GrForFit,&Nuclide);
	
	return (Chi2Plus-Chi2Minus);///(2*Epsilon);
	
	//return (Chi2Plus-Chi2Minus)/(2*Epsilon);	
}

void EvalDiffInThread(Nucleus Nuclide,TGraph *GrForFit,vector<double> Parameters,int ParNumber,vector<double> Epsilon,double *result,int ThreadID)
{
	Nuclide.SetThreadNumber(ParNumber+ThreadID*100);
	Nuclide.OMPN->SetDefaultOMP(2);
	Nuclide.OMPP->SetDefaultOMP(2);
	vector<double> ParPlus=Parameters;
	vector<double> ParMinus=Parameters;
	ParAssignmentFunction(&Nuclide,ParPlus);
	
	ParPlus[ParNumber]=Parameters[ParNumber]+Epsilon[ParNumber];
	ParMinus[ParNumber]=Parameters[ParNumber]-Epsilon[ParNumber];
	ParAssignmentFunction(&Nuclide,ParPlus);
	Nuclide.GenerateProducts();
	double Chi2Plus=EvalChi2(GrForFit,&Nuclide);
	ParAssignmentFunction(&Nuclide,ParMinus);
	Nuclide.GenerateProducts();
	double Chi2Minus=EvalChi2(GrForFit,&Nuclide);
	
	double DiffValue=(Chi2Plus-Chi2Minus);///(2*Epsilon);
	*result=DiffValue;
}

void DetermineEpsilonForOMP()
{
	ROOT::EnableThreadSafety();
	TH1::AddDirectory(0);
	TalysLibManager::Instance().SetC4Flag(false);
	TGraph ElasticInit,InelasticInit;
	TFile f0("C12-Koning.root");
	ElasticInit=*((TGraph*)f0.Get("Elastic"));
	InelasticInit=*((TGraph*)f0.Get("Inelastic"));
	f0.Close();
	
	TGraph GraphForFit;
	AddToGraphForFit(&GraphForFit,&ElasticInit,0);
	AddToGraphForFit(&GraphForFit,&InelasticInit,180);
	vector<string> GrNames={"Epsilon_v1","Epsilon_v2","Epsilon_w1","Epsilon_w2","Epsilon_d1","Epsilon_d2","Epsilon_vso1","Epsilon_vso2","Epsilon_wso1","Epsilon_wso2"};
	vector<string> VarNames;
	vector<TGraph> DiffGraphs;
	DiffGraphs.resize(GrNames.size());
	for(unsigned int i=0;i<DiffGraphs.size();i++)
	{
		DiffGraphs[i].SetName(GrNames[i].c_str());
		TString ts(GrNames[i].c_str());
		ts.ReplaceAll("_"," ");
		stringstream sstr(ts.Data());
		string tmp;
		sstr>>tmp>>tmp;
		VarNames.push_back(tmp);
		DiffGraphs[i].SetTitle(TString::Format("#frac{d(#chi^2)}{d%s}(#epsilon);#epsilon;#frac{d(#chi^2)}{d%s}",tmp.c_str(),tmp.c_str()));
	}
	Nucleus Nucl("12C");
	vector<double> Parameters{Nucl.OMPN->PotentialKoning.v1,Nucl.OMPN->PotentialKoning.v2,Nucl.OMPN->PotentialKoning.w1,Nucl.OMPN->PotentialKoning.w2,Nucl.OMPN->PotentialKoning.d1,Nucl.OMPN->PotentialKoning.d2,Nucl.OMPN->PotentialKoning.vso1,Nucl.OMPN->PotentialKoning.vso2,Nucl.OMPN->PotentialKoning.wso1,Nucl.OMPN->PotentialKoning.wso2};
	//double Epsilon0=1;
	//double Epsilon=1;
	vector<double> ValidEpsilonValues;
	vector<double> Epsilon;
	for(unsigned int j=0;j<Parameters.size();j++)
	{
		Epsilon.push_back(abs(Parameters[j])/1000);
		cout<<"Parameters[j]:"<<Parameters[j]<<"\n";
	}
	ValidEpsilonValues.resize(Parameters.size());
	for(unsigned int i=0;i<1000;i++)
	{	
		//vector<thread> thr;
		cout<<"iteration: "<<i<<"\n";
		vector<double> DiffValues;
		DiffValues.resize(Parameters.size());
		for(unsigned int j=0;j<Parameters.size();j++)
		{
			EvalDiffInThread(Nucl,&GraphForFit,Parameters,j,Epsilon,&(DiffValues[j]),j);
		}
		/*for(unsigned int j=0;j<Parameters.size();j++)
		{
			thr[j].join();
		}*/
		//
		for(unsigned int j=0;j<Parameters.size();j++)
		{
			Epsilon[j]=2*Epsilon[j];
			cout<<"I="<<i<<"\n";
		}
			
		/*if(i<50)
		{
			Epsilon=Epsilon0/(i+1);
		}
		else
		{
			Epsilon=Epsilon0/pow(i+1,2);
		}
		
		/*for(unsigned int j=0;j<Parameters.size();j++)
		{
			DiffGraphs[j].SetPoint(i,Epsilon,DiffValues[j]);
			if(DiffValues[j]!=0)
			{
				ValidEpsilonValues[j]=Epsilon;
			}
		}*/
	}
	cout<<"File write:\n";
	TFile f("EpsilonValues.root","RECREATE");
	for(unsigned int j=0;j<Parameters.size();j++)
	{
		f.WriteTObject(&DiffGraphs[j]);
	}
	f.Close();
	ofstream ofs("EpsilonValues.txt");
	/*for(unsigned int j=0;j<Parameters.size();j++)
	{
		ofs<<VarNames[j]<<" "<<ValidEpsilonValues[j]<<"\n";
	}*/
}
