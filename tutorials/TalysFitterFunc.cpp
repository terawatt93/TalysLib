#include "TalysLib.hh"

void ParAssignmentFunction(TalysFitter *TF)//функция, описывающая приписывание параметров из вектора Parameters ядру.
{
	TF->Nuclide.OMPN.PotentialKoning.v1=TF->Parameters[0];
	TF->Nuclide.OMPN.PotentialKoning.w1=TF->Parameters[1];
	//TF->Nuclide.OMPN.PotentialKoning.d1=TF->Parameters[2];
	TF->Nuclide.WriteOMPOrUseKoningN=2;
	//TF->Nuclide.ProjectileEnergy=TF->x_val;//если аппроксимируется функция от энергии, например
}
double GetEvaluationResult(double value, TalysFitter *TF)//функция, возвращающая результат вычислений, который подгоняется к графику
{//value - значение по оси абцисс к которому производится подгонка
	TGraph *Elastic=TF->Nuclide.GetElasticAngularDistribution("Total","new");
	return Elastic->Eval(value);
}
void TalysFitterFunc()
{
	TalysFitter tf("12C");
	tf.ParAssignmentFunction=ParAssignmentFunction;
	tf.GetEvaluationResult=GetEvaluationResult;
	vector<double> par;
	par.push_back(tf.Nuclide.OMPN.PotentialKoning.v1);
	par.push_back(tf.Nuclide.OMPN.PotentialKoning.w1);
	//par.push_back(tf.Nuclide.OMPN.PotentialKoning.d1);
	tf.Parameters=par;
	tf.EnableParTracking();
	TF1* Function=tf.GenerateTF1("TotElastic",0,180);
	gStyle->SetOptFit(1111);
	TCanvas cc1;
	TGraphErrors gr("S.Shirato1992_el_14.1MeV_cm");
	gr.Draw("alp");
	gr.Fit(Function);
	gr.Draw();
	gPad->SetLogy(1);
	cc1.Print("TalysTF1.pdf","pdf");
	
}
