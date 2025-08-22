#include <iostream>
#include "C5.hh"
#include "../Parser.cpp"
#include "../TalysLib.hh"
#pragma once

//double tolerancy_gamma = 5;
double tolerancy_level = 100;

EnergyDistribution GetCSP(SubentData& subent, size_t& row_num)
{
	EnergyDistribution ED;
	ED.fSubent = &subent;
	for(; row_num < subent.DataTable.size(); ++row_num)
	{
		double x1 = subent.DataTable[row_num].Row["x1"] / 1e6;
		double dx1 = subent.DataTable[row_num].Row["dx1"] / 1e6;
		double y = subent.DataTable[row_num].Row["y"] * 1e3;
		double dy = subent.DataTable[row_num].Row["dy"] * 1e3;
		if(y != 0 and dy != 0)
		{
			ED.data_points.push_back({x1, y, dx1, dy});
		}
		if(row_num+1 != subent.DataTable.size() && subent.DataTable[row_num].Row["x2"] != subent.DataTable[row_num+1].Row["x2"])
		{
			++row_num;
			break;
		}
	}
	return ED;
}

AngularDistribution GetDAP(SubentData& subent, size_t& row_num)
{
	AngularDistribution AD;
	AD.fSubent = &subent;
	for(; row_num < subent.DataTable.size(); ++row_num)
	{
		double x1 = subent.DataTable[row_num].Row["x1"] / 1e6;
		double x3 = subent.DataTable[row_num].Row["x3"];
		double dx3 = subent.DataTable[row_num].Row["dx3"];
		double y = subent.DataTable[row_num].Row["y"] * 1e3;
		double dy = subent.DataTable[row_num].Row["dy"] * 1e3;
		if(y != 0 and dy != 0)
		{
			AD.data_points.push_back({x1, x3, y, dx3, dy});
		}
		if(row_num+1 != subent.DataTable.size() && subent.DataTable[row_num].Row["x2"] != subent.DataTable[row_num+1].Row["x2"])
		{
			++row_num;
			break;
		}
	}
	return AD;
}

AngularDistribution GetDA(SubentData& subent)
{
	AngularDistribution AD;
	AD.fSubent = &subent;
	for(size_t i = 0; i < subent.DataTable.size(); ++i)
	{
		double x1 = subent.DataTable[i].Row["x1"] / 1e6;
		double x2 = subent.DataTable[i].Row["x2"];
		double dx2 = subent.DataTable[i].Row["dx2"];
		double y = subent.DataTable[i].Row["y"] * 1e3;
		double dy = subent.DataTable[i].Row["dy"] * 1e3;
		AD.data_points.push_back({x1, x2, y, dx2, dy});
	}
	return AD;
}

double Gamma_min_diff(SubentData& subent, double tolerancy_gamma)
{
	auto sub_vec = subent.fEntry->fSubentVec;
	vector<double> x2;
	for(size_t i = 0; i < sub_vec.size(); i++)
	{
		if(sub_vec[i]->Reacode == subent.Reacode)
		{
			for(size_t j = 0; j < sub_vec[i]->DataTable.size(); j++)
			{
				x2.push_back(sub_vec[i]->DataTable[j].Row["x2"] / 1e3);
			}
		}
	}
	sort(x2.begin(), x2.end());
	auto itr = unique(x2.begin(), x2.end());
	x2.resize(distance(x2.begin(), itr));
	double result = tolerancy_gamma;
	for(size_t i = 0; i < x2.size()-1; i++)
	{
		for(size_t j = i+1; j < x2.size(); j++)
		{	
			if(fabs(x2[i] - x2[j]) < result)
				result = fabs(x2[i] - x2[j]);
		}
	}
	if(result < 1)
	{
		return tolerancy_gamma;
	}
	return result;
}

bool Compare_x2(SubentData::DataRow &a, SubentData::DataRow &b)
{
	return a.Row["x2"] < b.Row["x2"];
}

string ConvertReaction(SubentData& subent)
{
	string result;
	string IncidentParticle = subent.SF2;
	string ProductParticle = subent.SF3;
	transform(IncidentParticle.begin(), IncidentParticle.end(), IncidentParticle.begin(), [](unsigned char c){ return tolower(c); });
	transform(ProductParticle.begin(), ProductParticle.end(), ProductParticle.begin(), [](unsigned char c){ return tolower(c); });
	ProductParticle.erase(std::remove(ProductParticle.begin(), ProductParticle.end(), '+'), ProductParticle.end());
	if(subent.SF3 == "INL")
	{
		result = "(n,n')";
	}
	else
	{
		result = "(n," + ProductParticle + ")";
	}
	return result;
}

void Strategy_CSP(SubentData& subent, Nucleus* nucl, double tolerancy_gamma)
{
	size_t row_num = 0;
	if(subent.x2_hdr == "E" || subent.x2_hdr == "E-LVL")
	{
		while(row_num < subent.DataTable.size())
		{
			double particle_energy = subent.DataTable[row_num].Row["x2"];
			GammaTransition* transition = nucl->GetBestTransition(particle_energy / 1e3, tolerancy_gamma);
			//GammaTransition* best_transition = nucl->GetBestTransition(particle_energy / 1e3, tolerancy_gamma);
			if(transition != NULL)
			{
				transition->C5EnergyDistribution.push_back(GetCSP(subent, row_num));
				transition->C5EnergyDistribution.back().Transition = transition;
			}
			else
			{
				++row_num;
			}
		}
		
	}
}

void Strategy_DAP(SubentData& subent, Nucleus* nucl, double tolerancy_gamma)
{
	size_t row_num = 0;
	if(subent.x2_hdr == "E" || subent.x2_hdr == "E-LVL")
	{
		while(row_num < subent.DataTable.size())
		{
			double particle_energy = subent.DataTable[row_num].Row["x2"];
			GammaTransition* transition = nucl->GetBestTransition(particle_energy / 1e3, tolerancy_gamma);
			if(transition != NULL)
			{
				transition->C5AngularDistribution.push_back(GetDAP(subent, row_num));
				transition->C5AngularDistribution.back().Transition = transition;
			}
			else
			{
				++row_num;
			}
		}
	}
	else if(subent.x2_hdr == "E-LVL-FIN/E-LVL-INI")
	{
		while(row_num < subent.DataTable.size())
		{
			json cdat = subent.DataTable[row_num].cdat;
			if(cdat.contains("ilv"))
			{
				double particle_energy = subent.DataTable[row_num].Row["x2"];
				GammaTransition* transition = nucl->GetBestTransition(particle_energy / 1e3, tolerancy_gamma);
				if(transition != NULL)
				{
					transition->C5AngularDistribution.push_back(GetDAP(subent, row_num));
				}
				else
				{
					++row_num;
				}
			}
			else if(cdat.contains("ilvm"))
			{
				double ini_level = nucl->FindLevelByNumber(cdat["ilvm"][1].template get<int>())->Energy;
				double fin_level = nucl->FindLevelByNumber(cdat["ilvm"][0].template get<int>())->Energy;
				double particle_energy = ini_level - fin_level;
				GammaTransition* transition = nucl->GetBestTransition(particle_energy / 1e3, tolerancy_gamma);
				if(transition != NULL)
				{
					transition->C5AngularDistribution.push_back(GetDAP(subent, row_num));
					transition->C5AngularDistribution.back().Transition = transition;
				}
				else
				{
					++row_num;
				}			
			}
		}
	}
}

void Strategy_DA_Scattering(SubentData& subent, Nucleus* nucl)
{
	nucl->Levels[0].C5AngularDistribution.push_back(GetDA(subent));
	nucl->Levels[0].C5AngularDistribution.back().fLevel = &(nucl->Levels[0]);
}

void Strategy_DAP_Scattering(SubentData& subent, Nucleus* nucl, double tolerancy_gamma)
{
	size_t row_num = 0;
	if(subent.x2_hdr == "E-LVL" || subent.x2_hdr == "Q-VAL" || subent.x2_hdr == "E-EXC")
	{
		while(row_num < subent.DataTable.size())
		{
			double level_energy = fabs(subent.DataTable[row_num].Row["x2"]);
			Level* level = nucl->FindLevelByEnergy(level_energy / 1e3, tolerancy_gamma);
			if(level != NULL)
			{
				level->C5AngularDistribution.push_back(GetDAP(subent, row_num));
				level->C5AngularDistribution.back().fLevel = level;
			}
			else
			{
				++row_num;
			}
		}
	}
	else if(subent.x2_hdr == "LVL-NUMB")
	{
		while(row_num < subent.DataTable.size())
		{
			int level_number = subent.DataTable[row_num].Row["x2"];
			Level* level = nucl->FindLevelByNumber(level_number);
			if(level != NULL)
			{
				level->C5AngularDistribution.push_back(GetDAP(subent, row_num));
				level->C5AngularDistribution.back().fLevel = level;
			}
			else
			{
				++row_num;
			}
		}
	}
}


void C5Manager::AssignC5ToLevel(double tolerancy_gamma)
{
	for(SubentData& subent: Subents)
	{
		// Gamma
		if((subent.SF7 == "G" || subent.SF4 == "0-G-0") && subent.Data_basic_units != "NO-DIM")
		{
			if(subent.Quant == "CSP")
			{
				if(subent.SF5 == "PAR" && subent.SF6 == "DA" && subent.SF8 == "4PI")
				{
					if(subent.SF3 == "X")
					{
						sort(subent.DataTable.begin(), subent.DataTable.end(), Compare_x2);
						double tol = Gamma_min_diff(subent, tolerancy_gamma);
						Strategy_CSP(subent, fMotherNucleus, tol);
					}
					else
					{
						sort(subent.DataTable.begin(), subent.DataTable.end(), Compare_x2);
						double tol = Gamma_min_diff(subent, tolerancy_gamma);
						Nucleus* product = fMotherNucleus->FindProductByReaction(ConvertReaction(subent));
						if(product != NULL)
						{
							Strategy_CSP(subent, product, tol);
						}
					}
				}
				else if(subent.SF5 == "PAR" && subent.SF6 == "SIG" && subent.SF8 == "")
				{
					if(subent.SF3 == "X")
					{
						sort(subent.DataTable.begin(), subent.DataTable.end(), Compare_x2);
						double tol = Gamma_min_diff(subent, tolerancy_gamma);
						Strategy_CSP(subent, fMotherNucleus, tol);
					}
					else
					{
						sort(subent.DataTable.begin(), subent.DataTable.end(), Compare_x2);
						double tol = Gamma_min_diff(subent, tolerancy_gamma);
						Nucleus* product = fMotherNucleus->FindProductByReaction(ConvertReaction(subent));
						if(product != NULL)
						{
							Strategy_CSP(subent, product, tol);
						}
					}	
						
				}
			}
			else if(subent.Quant == "DAP")
			{
				if(subent.SF5 == "PAR" && subent.SF6 == "DA" && subent.SF8 == "")
				{
					if(subent.SF3 == "X")
					{
						sort(subent.DataTable.begin(), subent.DataTable.end(), Compare_x2);
						double tol = Gamma_min_diff(subent, tolerancy_gamma);
						Strategy_DAP(subent, fMotherNucleus, tol);
					}
					else
					{
						sort(subent.DataTable.begin(), subent.DataTable.end(), Compare_x2);
						double tol = Gamma_min_diff(subent, tolerancy_gamma);
						Nucleus* product = fMotherNucleus->FindProductByReaction(ConvertReaction(subent));
						if(product != NULL)
						{
							Strategy_DAP(subent, product, tol);
						}
					}
				}
			}
		}
		else if(subent.SF3 == "EL" && subent.SF6 == "DA" && subent.SF8 == "")
		{
			Nucleus* product = fMotherNucleus->FindProductByReaction("(n,n')");
			Strategy_DA_Scattering(subent, product);
		}
		else if(subent.SF3 == "INL" && subent.SF5 == "PAR" && subent.SF6 == "DA" && subent.SF8 == "")
		{
			sort(subent.DataTable.begin(), subent.DataTable.end(), Compare_x2);
			double tol = Gamma_min_diff(subent, tolerancy_gamma);
			Nucleus* product = fMotherNucleus->FindProductByReaction("(n,n')");
			Strategy_DAP_Scattering(subent, product, tol);
		}
	}

}
