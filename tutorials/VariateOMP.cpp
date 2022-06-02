#include "TalysLib.hh"

//Функция, которая меняет параметры расчета на каждом шаге, ОБЯЗАТЕЛЬНО должна иметь аргументы типа (Nucleus *Nuclide,double value)
//При каждой итерации в функцию автоматически передается новое значение Calculation.VarValue[i], 
//вектор этих значений можно задать через TalysCalculation::SetVarValues(min,max,step);
void ChangeOMP(Nucleus *Nuclide,double value)
{
	Nuclide->OMPN->PotentialKoning.v1=value;//изменить значение величины v1 в опт. потенциале для нейтронов
	Nuclide->SetOMPOption("n",2);//установить флаг ОМ для нейтронов (Для n и p используются разные параметры и, соответственно, разные флаги)
	//WriteOMPOrUseKoningN=-1: не менять оптический пот-л для нейтронов
	//WriteOMPOrUseKoningN=0: взять потенциал из базы Talys, потом записать его. Если в базе нет потенциала, ничего не делать
	//WriteOMPOrUseKoningN=1: взять потенциал из базы Talys, если его нет, использовать Кенинга, потом записать его.
	//WriteOMPOrUseKoningN=2: использовать Кенинга, потом записать его.
}

void VariateOMP()
{
	TalysCalculation Calculation;
	Calculation.EnableMultiThreading=true;
	Calculation.Variable="v1";//имя переменной, оно будет на оси х графиков и в легенде
	Calculation.Target="12C";//мишень
	Calculation.Proj="n";//начальная частица
	Calculation.ProjectileEnergy=14.1;//энергия частицы
	Calculation.SetVarValues(10,60,1);//задать значения переменной
	Calculation.ExecuteCalculation(ChangeOMP);//выполнить вычисления
	Calculation.GenerateGraphs();//создать графики и поместить их в Nucleus *FinalResult
	TCanvas cc1;
	cc1.Print("VarV1.pdf[","pdf");
	TGraph CS=Calculation.FinalResult->TotTalysV; //построить полное сечение от Variable
	CS.Draw("alp");
	cc1.Print("VarV1.pdf","pdf");
	TLegend l(0.7,0.7,0.9,0.9);
	gPad->SetLogy(1);
	TMultiGraph* mgr=Calculation.GetElasticAngularDistributions("Total","",&l);
	mgr->Draw("alp");
	l.Draw();
	cc1.Print("VarV1.pdf","pdf");
	cc1.Clear();
	l.Clear();
	mgr=Calculation.GetElasticAngularDistributions("Compound","",&l);
	mgr->Draw("alp");
	l.Draw();
	cc1.Print("VarV1.pdf","pdf");
	cc1.Clear();
	l.Clear();
	mgr=Calculation.GetElasticAngularDistributions("Direct","",&l);
	mgr->Draw("alp");
	l.Draw();
	cc1.Print("VarV1.pdf","pdf");
	cc1.Clear();
	l.Clear();
	mgr=Calculation.GetAngularDistributionsForLevel(4439.82 ,"12C","Total","",&l);//построить MultiGraph с сечениями неупругого рассеяния на уровне 846кэВ 
	mgr->Draw("alp");
	l.Draw();
	cc1.Print("VarV1.pdf","pdf");
	cc1.Clear();
	l.Clear();
	mgr=Calculation.GetAngularDistributionsForLevel(4439.82 ,"12C","Compound","",&l);//построить MultiGraph с сечениями неупругого рассеяния на уровне 846кэВ 
	mgr->Draw("alp");
	l.Draw();
	cc1.Print("VarV1.pdf","pdf");
	cc1.Clear();
	l.Clear();
	mgr=Calculation.GetAngularDistributionsForLevel(4439.82 ,"12C","Direct","",&l);//построить MultiGraph с сечениями неупругого рассеяния на уровне 846кэВ 
	mgr->Draw("alp");
	l.Draw();
	cc1.Print("VarV1.pdf","pdf");
	cc1.Clear();
	l.Clear();
	cc1.Print("VarV1.pdf]","pdf");
}
