#include <TalysLib.hh>

void GammaPeak()
{
	TLMaterial mat("Fe");//создаем материал
	mat.Calculate();//запускаем вычисления
	GammaPeakData p=mat.FindGammaTransitionsForPeak(847,10,5);//возвращает объект GammaPeakData, содержащий следующие элементы:
	/*
	 * class GammaPeakData:public TObject//описывается в TLMaterial.cpp
	{
		public:
		vector<GammaTransition*> Gammas; //вектор гамма-переходов, куда попали переходы, имеющие энергию 847+-10 кэВ,
		* оцененное CS*Abun > 5 мб,
		vector<Nucleus*> InitNuclei; //вектор начальных ядер, продукты которых имеют подходящие гамма-переходы
		double E=0,Sigma=0, Centroid=0, StCoeff=0, EffectiveCS=0; //энергия пика, сигма (входные параметры), центроид (неразрешенного пика) на основе результатов Talys, Стех. коэффициент с учетом распространенности, эффективное сечение (с учетом распространенностей начальных ядер) 
		vector<string> Reactions;// список реакций
	};
	 * */
}
