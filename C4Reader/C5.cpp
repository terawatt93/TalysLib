#include <iostream>
#include "C5.hh"
#include "../Parser.cpp"
#include "../TalysLib.hh"
#pragma once


void strip(string &str)
{
	auto begin = str.begin();
	auto end = str.rbegin();
	while(isspace(*begin))
		++begin;
	while(isspace(*end))
		++end;
	str = string(begin, end.base());
}

void EntryData::GetAuthors(json &authors)
{
	for(auto author: authors)
	{
		Authors.push_back(string(author["ini"]) + string(author["nam"]));
	}
}

void EntryData::GetTitle(json &title)
{
	for(auto item: title)
	{
		string sub_str = string(item);
		strip(sub_str);
		Title += sub_str + " ";
	}
}

void EntryData::GetDetector(json &detectors)
{
	for(auto detector: detectors)
	{
		string x4code;
		string x4freetext;
			
		if(detector.contains("x4codes"))
		{
			x4code = string(detector["x4codes"][0]["code"]);
		}
		else
		{
			x4code = "No info";
		}
			
		if(detector.contains("x4freetext"))
		{
			for(auto item: detector["x4freetext"])
			{
				string sub_str = string(item);
				strip(sub_str);
				x4freetext += sub_str + " ";
			}
		}
		else
		{
			x4freetext = "No info";
		}
		
		Detector.push_back(pair<string, string>(x4code, x4freetext)); 
	}
}

void C5Manager::SearchSubents(const string& Target) // эта функция выполняет поиск нужных сабентов и заполняет поля классов C5Row, SubentData, EntryData.
{
	string natural_isotop = Target.substr(0,Target.find("-")) + "-0";
	sqlite3_stmt *stmt;
	connection = sqlite3_open_v2(db_name.c_str(), &db, SQLITE_OPEN_READONLY, NULL);
	
	const char* search_subent_query;				
	search_subent_query = "SELECT DISTINCT SubentID, zTarg, aTarg, zProd, aProd, Quant, SF1, SF2, SF3, SF4, SF5, SF6, SF7, SF8, SF9\n\
						FROM REACSTR\n\
						WHERE (Target = ? OR Target = ?)\n\
						AND Projectile = 'N'\n\
						GROUP BY SubentID\n\
						HAVING COUNT(SubentID) = 1";
					  
	sqlite3_prepare_v2(db, search_subent_query, -1, &stmt, 0);
	if(connection == SQLITE_OK)
	{
		sqlite3_bind_text(stmt, 1, Target.c_str(), -1, SQLITE_STATIC);
		sqlite3_bind_text(stmt, 2, natural_isotop.c_str(), -1, SQLITE_STATIC);
		while(sqlite3_step(stmt) == SQLITE_ROW)
		{	
			string SubentID = (char*)sqlite3_column_text(stmt, 0);
			int zTarg = sqlite3_column_int(stmt, 1);
			int aTarg = sqlite3_column_int(stmt, 2);
			int zProd = sqlite3_column_int(stmt, 3);
			int aProd = sqlite3_column_int(stmt, 4);
			string Quant = (char*)sqlite3_column_text(stmt, 5);
			string SF1 = (sqlite3_column_type(stmt,6) != SQLITE_NULL) ? (char*)sqlite3_column_text(stmt,6) : "";
			string SF2 = (sqlite3_column_type(stmt,7) != SQLITE_NULL) ? (char*)sqlite3_column_text(stmt,7) : "";
			string SF3 = (sqlite3_column_type(stmt,8) != SQLITE_NULL) ? (char*)sqlite3_column_text(stmt,8) : "";
			string SF4 = (sqlite3_column_type(stmt,9) != SQLITE_NULL) ? (char*)sqlite3_column_text(stmt,9) : "";
			string SF5 = (sqlite3_column_type(stmt,10) != SQLITE_NULL) ? (char*)sqlite3_column_text(stmt,10) : "";
			string SF6 = (sqlite3_column_type(stmt,11) != SQLITE_NULL) ? (char*)sqlite3_column_text(stmt,11) : "";
			string SF7 = (sqlite3_column_type(stmt,12) != SQLITE_NULL) ? (char*)sqlite3_column_text(stmt,12) : "";			
			string SF8 = (sqlite3_column_type(stmt,13) != SQLITE_NULL) ? (char*)sqlite3_column_text(stmt,13) : "";
			string SF9 = (sqlite3_column_type(stmt,14) != SQLITE_NULL) ? (char*)sqlite3_column_text(stmt,14) : "";
			std::array<string, 9> SF = {SF1, SF2, SF3, SF4, SF5, SF6, SF7, SF8, SF9};
			ExtractSubentData(SubentID, Quant, SF, zTarg, aTarg, zProd, aProd); 
		}
	}
	sqlite3_finalize(stmt);
	sqlite3_close(db);
}

void C5Manager::ExtractSubentData(const string& SubentID, const string& Quant, const array<string,9>& SF, int zTarg, int aTarg, int zProd, int aProd) // эта функция извлекает данные из x4pro
{
	sqlite3_stmt *stmt;
	const char* extract_subent_query = "SELECT * FROM x4pro_c5dat WHERE DatasetID = ?";
	const char* extract_columns_name = "SELECT famCode, expansion FROM x4pro_hdr WHERE DatasetID = ? AND typ = 'c' "; // идентифицируем колонки в x4pro_c5dat
	const char* extract_entry_query =  "SELECT * FROM\n\
										(SELECT SUBSTR(Subent,0,6) AS EntryID, json_extract(jx4z, '$.BIB.AUTHOR[0].x4codes'), json_extract(jx4z, '$.BIB.TITLE[0].x4freetext'),\n\
										json_extract(jx4z, '$.BIB.DETECTOR'), json_extract(jx4z, '$.BIB.METHOD')\n\
										FROM x4pro_x4z\n\
										WHERE Subent = ?) AS a\n\
										INNER JOIN\n\
										(SELECT YearRef1, DOI, EntryID FROM ENTRY) AS b\n\
										ON a.EntryID = b.EntryID";
										
										// список авторов, название статьи и информация о детекторах извлекаются из x4pro_x4z в json формате и дальше обрабатываются в string 
										// год, DOI извлекаются из Entry
										// может быть нужно добавить reference, но пока не знаю в каком формате.
										
	string EntryID = SubentID.substr(0,5);
	
	SubentData Subent;
	Subent.SubentID = SubentID;
	Subent.Quant = Quant;
	Subent.SF = SF;
	Subent.zTarg = zTarg;
	Subent.aTarg = aTarg;
	Subent.zProd = zProd;
	Subent.aProd = aProd;
	///////////////////
	sqlite3_prepare_v2(db, extract_columns_name, -1, &stmt, 0);
	sqlite3_bind_text(stmt, 1, SubentID.c_str(), -1, SQLITE_STATIC);
	if(sqlite3_step(stmt) == SQLITE_DONE)
	{
		return;
	}
	sqlite3_reset(stmt);

	if(connection == SQLITE_OK)
	{
		//sqlite3_bind_text(stmt, 1, SubentID.c_str(), -1, SQLITE_STATIC);
		while(sqlite3_step(stmt) == SQLITE_ROW)
		{
			string data_col_EXFOR = (char*)sqlite3_column_text(stmt,0);
			Subent.col_names_expansion.push_back((char*)sqlite3_column_text(stmt,1));
			string error_col_EXFOR = "d"+data_col_EXFOR;
			Subent.col_names_EXFOR.push_back(data_col_EXFOR);
			Subent.col_names_EXFOR.push_back(error_col_EXFOR);
		}
	}
	sqlite3_finalize(stmt);
	Subents.push_back(Subent);
	///////////////////
				
	///////////////////				
	sqlite3_prepare_v2(db, extract_subent_query, -1, &stmt, 0);
	if(connection == SQLITE_OK)
	{
		sqlite3_bind_text(stmt, 1, SubentID.c_str(), -1, SQLITE_STATIC);
		while(sqlite3_step(stmt) == SQLITE_ROW)
		{
			C5Row row;
			vector<double> vec;
			vec.push_back(sqlite3_column_double(stmt, 3));
			vec.push_back(sqlite3_column_double(stmt, 4));
			vec.push_back(sqlite3_column_double(stmt, 5));
			vec.push_back(sqlite3_column_double(stmt, 6));
			vec.push_back(sqlite3_column_double(stmt, 7));
			vec.push_back(sqlite3_column_double(stmt, 8));
			vec.push_back(sqlite3_column_double(stmt, 9));
			vec.push_back(sqlite3_column_double(stmt, 10));
			if(sqlite3_column_type(stmt, 25) != SQLITE_NULL)
				row.cdat = json::parse((char*)sqlite3_column_text(stmt,25));
			for(size_t i=0;i<Subent.col_names_EXFOR.size();i++)
			{
				row.Row.insert(pair<std::string, double>(Subent.col_names_EXFOR[i], vec[i]));
			}
			row.fSubent = &Subents.back();
			Rows.push_back(row);
			Subents.back().DataTable.push_back(&Rows.back());
		}
	}
	sqlite3_finalize(stmt);
	///////////////////
	
	//////////////////
	if(Entries.empty() || Entries.back().EntryID != EntryID)
	{
		EntryData Entry;
		Entry.EntryID = EntryID;
		Entries.push_back(Entry);
		
		sqlite3_prepare_v2(db, extract_entry_query, -1, &stmt, 0);
		if(connection == SQLITE_OK)
		{
			sqlite3_bind_text(stmt, 1, (EntryID + "001").c_str(), -1, SQLITE_STATIC);
			while(sqlite3_step(stmt) == SQLITE_ROW)
			{
				if(sqlite3_column_type(stmt,1) != SQLITE_NULL)
				{
					json authors = json::parse((char*)sqlite3_column_text(stmt,1));
					Entries.back().GetAuthors(authors); // заполняем vector<string> Authors 
				}
				else
				{
					Entries.back().Authors.push_back("No info");
				}
				
				if(sqlite3_column_type(stmt, 2) != SQLITE_NULL)
				{
					json title = json::parse((char*)sqlite3_column_text(stmt,2));
					Entries.back().GetTitle(title); // заполняем Title
				}
				else
				{
					Entries.back().Title = "No info";
				}
				
				if(sqlite3_column_type(stmt, 3) != SQLITE_NULL) 
				{
					json detectors = json::parse((char*)sqlite3_column_text(stmt,3));
					Entries.back().GetDetector(detectors); // заполняем Detector
				}
				else
				{
					Entries.back().Detector.push_back(pair<string, string>("No info", "No info"));
				}
				Entries.back().Year = (char*)sqlite3_column_text(stmt,5); // год
					
				if(sqlite3_column_type(stmt, 6) != SQLITE_NULL)
				{
					Entries.back().DOI = (char*)sqlite3_column_text(stmt,6); // DOI
				}
				else
				{
					Entries.back().DOI = "No info";
				}
			}
		}	
		sqlite3_finalize(stmt);
		Subents.back().fEntry = &Entries.back();
		Entries.back().fSubentVec.push_back(&Subents.back());
	}
	else
	{
		Subents.back().fEntry = &Entries.back();
		Entries.back().fSubentVec.push_back(&Subents.back());
	}
	///////////////////
}

EnergyDistribution C5Manager::GetC5EnergyDistribution(SubentData& subent)
{
	EnergyDistribution ED;
	size_t& i = subent.it;
	ED.fSubent = &subent;
	for(;i<subent.DataTable.size();++i)
	{
		ED.Y.push_back(subent.DataTable[i]->Row["Data"]*1e3);
		ED.X.push_back(subent.DataTable[i]->Row["EN"]/1e6);
		ED.ErrorY.push_back(subent.DataTable[i]->Row["dData"]*1e3);
		ED.ErrorX.push_back(subent.DataTable[i]->Row["dEN"]/1e6);
		if(i+1 == subent.DataTable.size() || subent.DataTable[i]->Row["E2"] != subent.DataTable[i+1]->Row["E2"])
		{
			++i;
			break;
		}
	}
	return ED;
}

AngularDistribution C5Manager::GetC5AngularDistribution(SubentData& subent)
{	
	AngularDistribution AD;
	size_t& i = subent.it;
	AD.fSubent = &subent;
	AD.ProjectileEnergy = subent.DataTable[i]->Row["EN"]/1e6;
	for(;i<subent.DataTable.size();++i)
	{
		AD.Y.push_back(subent.DataTable[i]->Row["Data"]*1e3);
		AD.X.push_back(subent.DataTable[i]->Row["ANG"]);
		AD.ErrorY.push_back(subent.DataTable[i]->Row["dData"]*1e3);
		AD.ErrorX.push_back(subent.DataTable[i]->Row["dANG"]);
		if(i+1 == subent.DataTable.size() || subent.DataTable[i]->Row["EN"] != subent.DataTable[i+1]->Row["EN"] || subent.DataTable[i]->Row["E2"] != subent.DataTable[i+1]->Row["E2"])
		{
			++i;
			break;
		}
	}
	return AD;
}	

AngularDistribution C5Manager::GetC5ElasticAngularDistribution(SubentData& subent)
{
	AngularDistribution AD;
	size_t& i = subent.it;
	AD.fSubent = &subent;
	AD.ProjectileEnergy = subent.DataTable[i]->Row["EN"]/1e6;
	for(;i<subent.DataTable.size();++i)
	{
		AD.Y.push_back(subent.DataTable[i]->Row["Data"]*1e3);
		AD.X.push_back(subent.DataTable[i]->Row["ANG"]);
		AD.ErrorY.push_back(subent.DataTable[i]->Row["dData"]*1e3);
		AD.ErrorX.push_back(subent.DataTable[i]->Row["dANG"]);
		if(i+1 == subent.DataTable.size() || subent.DataTable[i]->Row["EN"] != subent.DataTable[i+1]->Row["EN"])
		{
			++i;
			break;
		}
	}
	return AD;
}

bool EnergyDistribution::InRange(double emin, double emax)
{
	size_t left = 0;
	size_t right = X.size()-1;
	
	if(!(emax < X[left] || X[right] < emin)){
		if(X[right] < emax)
			emax = X[right];
		if(X[left] > emin)
			emin = X[left];
		while((X[right] - X[left] > emax - emin) || ((X[left] < emin) || (X[right] > emax))){
			if(X[left] < emin)
				++left;
			if(X[right] > emax)
				--right;
		}
		if(left <= right){
			Y = vector<double>(Y.begin() + left, Y.begin() + right + 1);
			X = vector<double>(X.begin() + left, X.begin() + right + 1);
			ErrorY = vector<double>(ErrorY.begin() + left, ErrorY.begin() + right + 1);
			ErrorX = vector<double>(ErrorX.begin() + left, ErrorX.begin() + right + 1);
			return true;
		} else return false;
	}
	return false;
}







