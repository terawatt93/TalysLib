#include "TalysLib.hh"

void GetExperimentalData()
{
	TalysLibManager::Instance().DeleteExpDataForAuthor("Voss");
	TalysLibManager::Instance().DeleteExpDataForAuthor("Shcherbakov");
	TalysLibManager::Instance().DeleteExpDataForAuthor("Litvinski");
	TalysLibManager::Instance().DeleteExpDataForAuthor("Pomerance");
	
	Nucleus Nucl("56Fe");
	//Nucl.FastFlag=false;
	Nucl.GenerateEnergyGrid(0,1,20);//установить сетку энергий : от 0 до 20 МэВ с шагом 0.2 МэВ
	Nucl.GenerateProducts();//выполнить расчеты в Talys
	vector<Level*> LevelsWithData=Nucl.GetLevelsWithAvalibleData("CS","EXFOR");//получить вектор уровней, для которых доступны данные в EXFOR в рассматриваемом диапазоне энергий
	TCanvas c;
	c.Print("Cross-sections.pdf[","pdf");//открыть pdf-файл для печати
	for(unsigned int i=0;i<LevelsWithData.size();i++)
	{
		TString Title;
		if(LevelsWithData[i]->Energy==0)
		{
			Title=TString::Format("Elastic scattering cross-section on %s;E, MeV; #sigma,mb",LevelsWithData[i]->fNucleus->Name.c_str());
		}
		else
		{
			Title=TString::Format("%s with excitation of level %.1f in %s;E, MeV; #sigma,mb",LevelsWithData[i]->fNucleus->Reaction.c_str(),LevelsWithData[i]->Energy,LevelsWithData[i]->fNucleus->Name.c_str());
		}
		TMultiGraph* mgr=LevelsWithData[i]->GetEXFORTMultiGraphForCrossSections(0,20);//получить TMultiGraph с экспериментальными данными, покрывающими диапазон 0-20 МэВ
		mgr->SetTitle(Title);
		
		TGraph *ENDF=LevelsWithData[i]->GetCSGraph("ENDF");//получить TGraph с оценками ENDF
		ENDF->SetTitle("ENDF");//Задать название
		ENDF->SetLineColor(2);//задать цвет (красный)
		TGraph *Talys=LevelsWithData[i]->GetCSGraph();//получить TGraph с результатами Talys
		Talys->SetLineColor(4);
		Talys->SetTitle("Talys");
		mgr->Add(ENDF,"l");//добавить ENDF к TMultiGraph
		mgr->Add(Talys,"l");//добавить Talys к TMultiGraph
		mgr->Draw("ap");//отрисовать TMultiGraph с осями ("a и точками p")
		mgr->GetXaxis()->SetRangeUser(0,20);
		gPad->BuildLegend();
		/*ENDF->Draw("l");//отрисовать Graph линией ("l") в предыдущих осях
		Talys->Draw("l");*/
		c.Print("Cross-sections.pdf","pdf");//сохранить страницу в pdf
	}
	c.Print("Cross-sections.pdf]","pdf");//закрыть pdf-файл
}
