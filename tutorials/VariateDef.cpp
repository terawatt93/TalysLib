#include "TalysLib.hh"

//Функция, которая меняет параметры расчета на каждом шаге, ОБЯЗАТЕЛЬНО должна иметь аргументы типа (Nucleus *Nuclide,double value)
//При каждой итерации в функцию автоматически передается новое значение Calculation.VarValue[i], 
//вектор этих значений можно задать через TalysCalculation::SetVarValues(min,max,step);
void ChangeDef(Nucleus *Nuclide,double value)
{
	int LevelNumber=1;//номер уровня, для которого задаётся деформация
	char Level_type='D';//тип коллективности "D", "R", "V"
	vector<float> Deformations;
	Deformations.push_back(value);
	Nuclide->SetLevelDeformation(4439.82,Level_type, -1, -1, -1, -1,&Deformations);
	Nuclide->WriteDeformation=true;
	//Nuclide->FastFlag=false;
}

void VariateDef()
{
	TalysCalculation Calculation;
	Calculation.Variable="#beta_{2}";//имя переменной, оно будет на оси х графиков и в легенде
	Calculation.Target="12C";//мишень
	Calculation.Proj="n";//начальная частица
	Calculation.ProjectileEnergy=14.1;//энергия частицы
	Calculation.SetVarValues(-0.4,0.8,0.1);
	Calculation.ExecuteCalculation(ChangeDef);//выполнить вычисления
	Calculation.GenerateGraphs();//создать графики и поместить их в Nucleus *FinalResult
	TCanvas cc1;
	cc1.Print("VarBeta2.pdf[","pdf");
	TGraph CS=Calculation.FinalResult->TotTalysV; //построить полное сечение от Variable
	CS.Draw("alp");
	cc1.Print("VarBeta2.pdf","pdf");
	TLegend l(0.7,0.7,0.9,0.9);
	gPad->SetLogy(1);
	TMultiGraph* mgr=Calculation.GetElasticAngularDistributions("Total","",&l);
	mgr->Draw("alp");
	l.Draw();
	cc1.Print("VarBeta2.pdf","pdf");
	cc1.Clear();
	l.Clear();
	mgr=Calculation.GetElasticAngularDistributions("Compound","",&l);
	mgr->Draw("alp");
	l.Draw();
	cc1.Print("VarBeta2.pdf","pdf");
	cc1.Clear();
	l.Clear();
	mgr=Calculation.GetElasticAngularDistributions("Direct","",&l);
	mgr->Draw("alp");
	l.Draw();
	cc1.Print("VarBeta2.pdf","pdf");
	cc1.Clear();
	l.Clear();
	mgr=Calculation.GetAngularDistributionsForLevel(4439.82 ,"12C","Total","",&l);//построить MultiGraph с сечениями неупругого рассеяния на уровне 846кэВ 
	mgr->Draw("alp");
	l.Draw();
	cc1.Print("VarBeta2.pdf","pdf");
	cc1.Clear();
	l.Clear();
	mgr=Calculation.GetAngularDistributionsForLevel(4439.82 ,"12C","Compound","",&l);//построить MultiGraph с сечениями неупругого рассеяния на уровне 846кэВ 
	mgr->Draw("alp");
	l.Draw();
	cc1.Print("VarBeta2.pdf","pdf");
	cc1.Clear();
	l.Clear();
	mgr=Calculation.GetAngularDistributionsForLevel(4439.82 ,"12C","Direct","",&l);//построить MultiGraph с сечениями неупругого рассеяния на уровне 846кэВ 
	mgr->Draw("alp");
	l.Draw();
	cc1.Print("VarBeta2.pdf","pdf");
	cc1.Clear();
	l.Clear();
	cc1.Print("VarBeta2.pdf]","pdf");
}
