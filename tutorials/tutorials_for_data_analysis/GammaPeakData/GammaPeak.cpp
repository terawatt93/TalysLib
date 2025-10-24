#include <TalysLib.hh>

void GammaPeak()
{
	TLMaterial mat("Fe");//создаем материал
	mat.GenerateEnergyGrid(0,1,20);
	mat.Calculate();//запускаем вычисления
	GammaPeakData p=mat.FindGammaTransitionsForPeak(3202,30,5);//возвращает объект GammaPeakData, содержащий следующие элементы:
	p.CSGraph.Draw("alp");
	gPad->GetCanvas()->Print("PeakCSGraph.pdf","pdf");
	/*class GammaPeakData:public TObject//описывается в TLMaterial.cpp
	{
		public:
		vector<GammaTransition*> Gammas;//вектор гамма-переходов, куда попали переходы, имеющие энергию 847+-10 кэВ,
		double Multipolarity=0;
		vector<Nucleus*> InitNuclei;//вектор начальных ядер, продукты которых имеют подходящие гамма-переходы
		TGraph CSGraph;
		double E=0,Sigma=0, Centroid=0, StCoeff=0, EffectiveCS=0, NAtoms=0, NAtoms_mb=0;// //энергия пика, сигма (входные параметры), центроид (неразрешенного пика) на основе результатов Talys, Стех. коэффициент с учетом распространенности, эффективное сечение (с учетом распространенностей начальных ядер), для расчета NAtoms требуется задание плотности
		//NAtoms - количество атомов (на 1 см2), NAtoms_mb - количество атомов на 1 мб
		vector<string> Reactions;// список реакций
		string Reacstr;
		TLMaterial *fMaterial=0;
	};*/
	
}
