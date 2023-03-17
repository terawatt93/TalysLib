#include <TalysLib.hh>
void TestChi2()
{
	Nucleus C("12C");
	C.GenerateProducts();
	EvaluatedDataGraph* g_el1=(EvaluatedDataGraph*)C.Products[1].Levels[0].GetAngularDistribution();
	EvaluatedDataGraph* g_el2=(EvaluatedDataGraph*)C.Products[1].Levels[0].GetAngularDistribution();
	EvaluatedDataGraph* g_inl1=(EvaluatedDataGraph*)C.Products[1].Levels[1].GetAngularDistribution();
	cout<<"Chi2:"<<g_el1->EvalChi2(g_el2)<<" "<<g_el1->EvalChi2(g_inl1)<<"\n";
}
