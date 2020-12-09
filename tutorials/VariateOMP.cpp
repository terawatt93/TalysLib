#include "Levels.hh"

//Функция, которая меняет параметры расчета на каждом шаге, ОБЯЗАТЕЛЬНО должна иметь аргументы типа (Nucleus *Nuclide,double value)
//При каждой итерации в функцию автоматически передается новое значение Calculation.VarValue[i], 
//вектор этих значений можно задать через TalysCalculation::SetVarValues(min,max,step);
void ChangeOMP(Nucleus *Nuclide,double value)
{
	Nuclide->OMPN.Potential.v1=value;//изменить значение величины v1 в опт. потенциале для нейтронов
	Nuclide->WriteOMPOrUseKoningN=0;//установить флаг ОМ для нейтронов (Для n и p используются разные параметры и, соответственно, разные флаги)
	//WriteOMPOrUseKoningN=-1: не менять оптический пот-л для нейтронов
	//WriteOMPOrUseKoningN=0: взять потенциал из базы Talys, потом записать его. Если в базе нет потенциала, ничего не делать
	//WriteOMPOrUseKoningN=1: взять потенциал из базы Talys, если его нет, использовать Кенинга, потом записать его.
	//WriteOMPOrUseKoningN=2: использовать Кенинга, потом записать его.
}

void VariateOMP()
{
	TalysCalculation Calculation;
	Calculation.Variable="v1";//имя переменной, оно будет на оси х графиков и в легенде
	Calculation.Target="56Fe";//мишень
	Calculation.Proj="n";//начальная частица
	Calculation.ProjectileEnergy=14.1;//энергия частицы
	Calculation.SetVarValues(30,60,2);//задать значения переменной
	Calculation.ExecuteCalculation(ChangeOMP);//выполнить вычисления
	Calculation.GenerateGraphs();//создать графики и поместить их в Nucleus *FinalResult
	TCanvas cc1;
	//TGraph CS=Calculation.FinalResult->TotTalysV; //построить полное сечение от Variable
	TLegend l(0.7,0.7,0.9,0.9);
	//TMultiGraph* mgr=Calculation.GetAngularDistributionsForLevel(846.8,"56Fe","Direct","",&l);//построить MultiGraph с сечениями неупругого рассеяния на уровне 846кэВ 
	//56Fe
	TMultiGraph* mgr=Calculation.GetElasticAngularDistributions("Compound","",&l);//построить MultiGraph с сечениями упругого рассеяния на уровне 846кэВ 
	//56Fe
	mgr->Draw("alp");
	l.Draw();
	cc1.Print("test.pdf","pdf");
}
