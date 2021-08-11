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

void MultiplyTGraph(TGraphErrors &gr,double multiplier)//функция для домножения значений ординат графика TGraphErrors на определённое число multiplier
{
	for(int i=0;i<gr.GetN();i++)
	{
		double x,y,x_err,y_err;
		gr.GetPoint(i,x,y);
		x_err=gr.GetErrorX(i);
		y_err=gr.GetErrorY(i);
		gr.SetPoint(i,x,y*multiplier);
		gr.SetPointError(i,x_err,y_err*multiplier);
	}
}

TGraphErrors GetFromTXT(string filename)//функция возвращает график, содержащий данные в тектовом файле, название которого передаётся
{//, подразумевается формат файла x dx y dy или x y dy
	TGraphErrors result;//грфаик TGraphErrors, который в конце работы возвратит функция
	ifstream ifs(filename.c_str());//создать поток с содержимым файла filename
	string line;
	int multiplier=1000;//множитель для перевода b/sr -> mb/sr
	bool ReadHearer=false;//флаг того, шапка данного файла не считывалась
	while(getline(ifs,line))//считываем строки до конца файла
	{
		if((line.find("MB/SR")!=string::npos)||(line.find("mb/sr")!=string::npos))//если в файле найдена строка с "MB/SR" или "mb/sr", то домножать значения не надо
		{
			multiplier=1;
			ReadHearer=true;//поднимаем флаг
		}
		else if((line.find("B/SR")!=string::npos)||(line.find("b/sr")!=string::npos))//если в файле найдена строка с "B/SR" или "b/sr", то домножать значения на 1000
		{
			ReadHearer=true;//поднимаем флаг
		}
		else if(ReadHearer)//если шапка файла успешно считана, начинаем считывать данные точек
		{
			vector<double> values;//значения данных в строке
			stringstream s(line);
			while(s)
			{
				string tmp;
				s>>tmp;
				//cout<<"tmp:\""<<tmp<<"\"\n";
				if(tmp.find("#")!=string::npos)//игнорируем строки с "#" - это комментарии
				{
					break;
				}
				if(tmp.size()>0)
				{
					values.push_back(atof(tmp.c_str()));//записываем значение столбца
				}
			}
			int NPoints=result.GetN();//получаем номер точки
			//cout<<"v.size:"<<values.size()<<"\n";
			if(values.size()==4)//если столбцов 4
			{
				result.SetPoint(NPoints,values[0],values[2]);//то ставим точке значения координат из первого и третьего столбцов
				result.SetPointError(NPoints,values[1],values[3]);//и ставим точке обе ошибки
			}
			else if(values.size()==3)//если столбцов 3
			{
				result.SetPoint(NPoints,values[0],values[1]);//то ставим точке значения координат из первых двух столбцов
				result.SetPointError(NPoints,0,values[2]);//и ошибок по x нет
			}
			else if(values.size()==6)//если столбцов 6
			{
				result.SetPoint(NPoints,values[2],values[3]);//то ставим точке значения координат из третьего и четвёртого столбцов (?)
				//result.SetPointError(NPoints,values[1],values[3]);
			}
		}
	}
	ifs.close();//закроем поток с содержимым файла
	MultiplyTGraph(result,multiplier);//функция определена в коде выше
	TString FName(filename.c_str());
	FName.ReplaceAll("_"," ");//в названии файла заменить все пробелы на нижнее подчёркивание _
	stringstream ss(FName.Data());
	string GraphName;
	ss>>GraphName;
	result.SetName(GraphName.c_str());
	//result.SetTitle(GraphName.c_str());
	result.SetTitle(filename.c_str());
	return result;
}

vector<TGraphErrors> GetListOfGraphs(string reaction)//функция возвращает вектор графиков TGraphErrors для выбранной реакции 
{
	vector<string> Filenames=ListFiles(reaction);
	vector<TGraphErrors> result;
	for(unsigned int i=0;i<Filenames.size();i++)
	{
		TGraphErrors g=GetFromTXT(Filenames[i]);
		if(g.GetN()>0)
		result.push_back(g);
	}
	return result;
}

TMultiGraph *GenerateTMultiGraph(vector<TGraphErrors> *Graphs)//функция создаёт указатель на TMultiGraph содержащий поданные как аргументы графики TGraph
{
	TMultiGraph *mgr=new TMultiGraph();
	for(unsigned int i=0;i<Graphs->size();i++)
	{
		Graphs->at(i).SetMarkerColor(kViolet-9+2*i);
		Graphs->at(i).SetMarkerStyle(20+i);
		Graphs->at(i).SetMarkerSize(0.8);
		Graphs->at(i).SetLineColor(kViolet-9+2*i);
		mgr->Add(&(Graphs->at(i)));
	}
	return mgr;
}

void ParAssignmentFunction(TalysFitterMT *TF,Nucleus *Nucl, vector<double> Parameters)//функция, описывающая приписывание параметров из вектора Parameters ядру, которое происходит при каждом вычислении \chi^2
{
	Nucl->OMPN.PotentialKoning.v1=Parameters[0];//V_V
	Nucl->OMPN.PotentialKoning.w1=Parameters[1];//W_V
	Nucl->OMPN.PotentialKoning.d1=Parameters[2];//W_D
	Nucl->OMPN.PotentialKoning.vso1=Parameters[3];//=V_SO
	Nucl->OMPN.PotentialKoning.wso1=Parameters[4];//=W_SO
	Nucl->OMPN.PotentialKoning.Rv=Parameters[5];//r_V
	Nucl->OMPN.PotentialKoning.Av=Parameters[6];//a_V
	Nucl->OMPN.PotentialKoning.Rd=Parameters[7];//r_D
	Nucl->OMPN.PotentialKoning.Ad=Parameters[8];//a_D
	Nucl->OMPN.PotentialKoning.Rso=Parameters[9];//r_SO
	Nucl->OMPN.PotentialKoning.Aso=Parameters[10];//a_SO
	Nucl->WriteOMPOrUseKoningN=2;
	char Col_type='R';//тип коллективности ядра "S", "R", "V", "A", см. 
	//int LevelNumber=1;//номер уровня, для которого задаётся деформация
	char Level_type='R';//тип коллективности уровня: "D", "R", "V"
	vector<float> Deformations1;
	vector<float> null;
	Deformations1.push_back(Parameters[11]);
	null.push_back(0.0);
	Nucl->Def.SetTypeOfCollectivity(Col_type);//задаём тип коллективности для ядра
	Nucl->SetLevelDeformation(0,'R', -1, -1, -1, -1,&null);//деформацию для основного соостояния
	Nucl->SetLevelDeformation(4439.82,Level_type, -1, -1, -1, -1,&Deformations1);//деформацию для первого возб. состояния
	Nucl->WriteDeformation=true;

	std::cout<<"ParAssignmentFunction tells this:\n";
	std::cout<<"V_V = "<<Nucl->OMPN.PotentialKoning.v1<<"\n";//изменить значение величины v1 в опт. потенциале для нейтронов//=V_V 
	std::cout<<"W_V = "<<Nucl->OMPN.PotentialKoning.w1<<"\n";//=W_V  
	std::cout<<"W_D = "<<Nucl->OMPN.PotentialKoning.d1<<"\n";//=W_D 
	std::cout<<"V_so = "<<Nucl->OMPN.PotentialKoning.vso1<<"\n";//=V_SO  
	std::cout<<"W_so = "<<Nucl->OMPN.PotentialKoning.wso1<<"\n";//=W_SO  
	std::cout<<"Rv = "<<Nucl->OMPN.PotentialKoning.Rv<<"\n";//r_V
	std::cout<<"Av = "<<Nucl->OMPN.PotentialKoning.Av<<"\n";//a_V
	std::cout<<"Rd = "<<Nucl->OMPN.PotentialKoning.Rd<<"\n";//r_D
	std::cout<<"Ad = "<<Nucl->OMPN.PotentialKoning.Ad<<"\n";//a_D
	std::cout<<"Rso = "<<Nucl->OMPN.PotentialKoning.Rso<<"\n";//r_SO
	std::cout<<"Aso = "<<Nucl->OMPN.PotentialKoning.Aso<<"\n";//a_SO 
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
		TGraph *INL4=PointerToNucleus->Products[0].Levels[1].GetAngularDistribution("Total");
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
	ROOT::EnableThreadSafety();
	tf=new TalysFitterMT("12C");
	TCanvas c1;	
	vector<TGraphErrors> gr_Elastic=GetListOfGraphs("exp/12C/dif/good/*,n0*");
	vector<TGraphErrors> gr_Inelastic=GetListOfGraphs("exp/12C/dif/good/*,n1*");
	
	TMultiGraph *mgrElastic=GenerateTMultiGraph(&gr_Elastic);
	TMultiGraph *mgrInelastic=GenerateTMultiGraph(&gr_Inelastic);
	
	tf->Nuclide.OMPN.PotentialKoning.v1=48.0;//=V_V
	tf->Nuclide.OMPN.PotentialKoning.v2=0.0;
	tf->Nuclide.OMPN.PotentialKoning.v3=0.0; 
	tf->Nuclide.OMPN.PotentialKoning.v4=0.0; 
	tf->Nuclide.OMPN.PotentialKoning.w1=1.0;//=W_V  
	tf->Nuclide.OMPN.PotentialKoning.w2=0.0; 
	tf->Nuclide.OMPN.PotentialKoning.d1=3;//=W_D 
	tf->Nuclide.OMPN.PotentialKoning.d2=0.0;
	tf->Nuclide.OMPN.PotentialKoning.d3=0.0;
	///зададим свойства подбираемых параметров:
	tf->SetParameter(0,tf->Nuclide.OMPN.PotentialKoning.v1,"V_{V}",0.1,20,70);
	tf->SetParameter(1,tf->Nuclide.OMPN.PotentialKoning.w1,"W_{V}",0.1,0,10);
	tf->SetParameter(2,tf->Nuclide.OMPN.PotentialKoning.d1,"W_{D}",0.1,0,10);
	tf->SetParameter(3,tf->Nuclide.OMPN.PotentialKoning.vso1,"V_{SO}",0.1,-1,10);
	tf->SetParameter(4,tf->Nuclide.OMPN.PotentialKoning.wso1,"W_{SO}",0.01,0,10);	
	tf->SetParameter(5,tf->Nuclide.OMPN.PotentialKoning.Rv,"r_{V}",0.001,0.5,2);
	tf->SetParameter(6,tf->Nuclide.OMPN.PotentialKoning.Av,"a_{V}",0.001,0.1,2);
	tf->SetParameter(7,tf->Nuclide.OMPN.PotentialKoning.Rd,"r_{D}",0.001,0.5,2);
	tf->SetParameter(8,tf->Nuclide.OMPN.PotentialKoning.Ad,"a_{D}",0.001,0.1,2);
	tf->SetParameter(9,tf->Nuclide.OMPN.PotentialKoning.Rso,"r_{SO}",0.001,0.5,2);
	tf->SetParameter(10,tf->Nuclide.OMPN.PotentialKoning.Aso,"a_{SO}",0.001,0.1,2);
	tf->SetParameter(11,-0.62,"#beta_{2}",0.001,-1,1);//это деформация, beta_2
	///
	tf->ParAssignmentFunction=ParAssignmentFunction;
	tf->GetEvaluationResult=GetEvaluationResult;
	
	vector<TObject*> Graphs;
	Graphs.push_back(mgrElastic);
	Graphs.push_back(mgrInelastic);
	vector<double> Offsets;
	Offsets.push_back(0);
	Offsets.push_back(180);
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
	TGraph *INL4=tf->Nuclide.Products[0].Levels[1].GetAngularDistribution("Total","new");
	f.WriteTObject(Elastic);
	f.WriteTObject(INL4);
	f.WriteTObject(&(tf->GraphForMultiFit));
	f.Close();
	c1.Clear();
	c1.Print("TestMultiFitMT.pdf[","pdf");
	gPad->SetLogy(1);
	mgrElastic->Draw("ap");
	Elastic->SetLineColor(2);
	Elastic->Draw("l");
	gPad->BuildLegend();
	c1.Print("TestMultiFitMT.pdf","pdf");
	mgrInelastic->Draw("ap");
	INL4->SetLineColor(2);
	INL4->Draw("l");
	gPad->BuildLegend();
	c1.Print("TestMultiFitMT.pdf","pdf");
	
	tf->GraphForMultiFit.Draw("ap");
	tf->FitValues.Draw("l");
	c1.Print("TestMultiFitMT.pdf","pdf");
	
	c1.Print("TestMultiFitMT.pdf]","pdf");
}

