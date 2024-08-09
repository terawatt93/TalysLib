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
/*
multimap<double, C5Row*> SubentData::GroupByData(int col_num)
{
	multimap<double, C5Row*> pair;
	for(int i=0; i<DataTable.size(); i++)
	{
		pair.insert(std::pair<double,C5Row*>(DataTable[i]->Row[col_num], DataTable[i]));
		Keys.insert(DataTable[i]->Row[col_num]);
	}
	return pair;
}
*/

multimap< double, C5Row* > SubentData::GroupEnergyDistribution()
{
	multimap< double, C5Row* > map;
	for(int i=0; i<DataTable.size(); i++)
	{
		map.insert(pair<double, C5Row*>(DataTable[i]->Row[4], DataTable[i]));
		ED_keys.insert(DataTable[i]->Row[4]);
	}
	return map;
}

multimap< pair<double, double>, C5Row* > SubentData::GroupAngularDistribution()
{
	multimap< pair<double, double>, C5Row* > map;
	for(int i=0; i<DataTable.size(); i++)
	{
		pair<double, double> AD_pair = make_pair(DataTable[i]->Row[4], DataTable[i]->Row[2]);
		map.insert(pair<pair<double, double>, C5Row*>(make_pair(AD_pair, DataTable[i])));
		AD_keys.insert(AD_pair);
	}
	return map;
}

void EntryData::GetAuthors(json &authors)
{
	for(auto author: authors)
	{
		Authors.push_back(string(author["ini"]) + string(author["nam"]));
	}
	FirstAuthor = Authors[0];
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
			x4code = string(detector["x4codes"][0]["hlp"]);
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
			
		Detector += x4code + " " + x4freetext + "\n";
	}
}

void C5Manager::SearchSubent(string Target) // эта функция выполняет поиск нужных сабентов и заполняет поля классов C5Row, SubentData, EntryData.
{
	TargetNucl = Target;
	sqlite3_stmt *stmt;
	const char* search_subent_query;
	
	connection = sqlite3_open(db_name.c_str(), &db);
						
	search_subent_query = "SELECT DISTINCT SubentID, zTarg, aTarg, zProd, aProd, Quant, SF1, SF2, SF3, SF4, SF5, SF6, SF7, SF8, SF9\n\
						FROM REACSTR\n\
						WHERE Target = ?\n\
						AND Projectile = 'N'\n\
						AND SubentID IN\n\
						(SELECT DatasetID FROM x4pro_c5dat)\n\
						GROUP BY SubentID\n\
						HAVING COUNT(SubentID) = 1";
					  
	sqlite3_prepare_v2(db, search_subent_query, -1, &stmt, 0);
	
	if (connection == SQLITE_OK)
	{
		sqlite3_bind_text(stmt, 1, Target.c_str(), -1, SQLITE_STATIC);
		//sqlite3_bind_text(stmt, 2, Projectile.c_str(), -1, SQLITE_STATIC);
		
		while(sqlite3_step(stmt) == SQLITE_ROW)
		{
			vector<string> SF;
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
			
			SF.push_back(SF1);
			SF.push_back(SF2);
			SF.push_back(SF3);
			SF.push_back(SF4);
			SF.push_back(SF5);
			SF.push_back(SF6);
			SF.push_back(SF7);
			SF.push_back(SF8);
			SF.push_back(SF9);
			
			ExtractData(SubentID, Quant, SF, zTarg, aTarg, zProd, aProd); // вызывается функция для заполнения полей классов найденного сабента
		}
	}
	sqlite3_finalize(stmt);
	sqlite3_close(db);
}

void C5Manager::ExtractData(string SubentID, string Quant, vector<string> SF, int zTarg, int aTarg, int zProd, int aProd) // эта функция извлекает данные из x4pro
{
	//sqlite3 *db;
	sqlite3_stmt *stmt;
	string EntryID = SubentID.substr(0,5);
	const char* extract_subent_query = "SELECT * FROM x4pro_c5dat WHERE DatasetID = ?";
	const char* extract_columns_name = "SELECT expansion FROM x4pro_hdr WHERE DatasetID = ? AND typ = 'c' "; // идентифицируем колонки в x4pro_c5dat
	const char* extract_entry_query =  "SELECT * FROM\n\
										(SELECT SUBSTR(Subent,0,6) AS EntryID, json_extract(jx4z, '$.BIB.AUTHOR[0].x4codes'), json_extract(jx4z, '$.BIB.TITLE[0].x4freetext'), json_extract(jx4z, '$.BIB.DETECTOR')\n\
										FROM x4pro_x4z\n\
										WHERE Subent = ?) AS a\n\
										INNER JOIN\n\
										(SELECT YearRef1, DOI, EntryID FROM ENTRY) AS b\n\
										ON a.EntryID = b.EntryID";
										
										// список авторов, название статьи и информация о детекторах извлекаются из x4pro_x4z в json формате и дальше обрабатываются в string 
										// год, DOI извлекаются из Entry
										// может быть нужно добавить reference, но пока не знаю в каком формате.
	
	//int connection = sqlite3_open(db_name.c_str(), &db);
	
	SubentData Subent;
	Subent.SubentID = SubentID;
	Subent.Quant = Quant;
	Subent.SF = SF;
	Subent.zTarg = zTarg;
	Subent.aTarg = aTarg;
	Subent.zProd = zProd;
	Subent.aProd = aProd;
	Subents.push_back(Subent);
				
	sqlite3_prepare_v2(db, extract_subent_query, -1, &stmt, 0);
	if(connection == SQLITE_OK)
	{
		sqlite3_bind_text(stmt, 1, SubentID.c_str(), -1, SQLITE_STATIC);
			
		while(sqlite3_step(stmt) == SQLITE_ROW)
		{
			C5Row new_row;
			new_row.Row.push_back(sqlite3_column_double(stmt, 3));
			new_row.Row.push_back(sqlite3_column_double(stmt, 4));
			new_row.Row.push_back(sqlite3_column_double(stmt, 5));
			new_row.Row.push_back(sqlite3_column_double(stmt, 6));
			new_row.Row.push_back(sqlite3_column_double(stmt, 7));
			new_row.Row.push_back(sqlite3_column_double(stmt, 8));
			new_row.Row.push_back(sqlite3_column_double(stmt, 9));
			new_row.Row.push_back(sqlite3_column_double(stmt, 10));
			if(sqlite3_column_type(stmt, 25) != SQLITE_NULL)
				new_row.cdat = json::parse((char*)sqlite3_column_text(stmt,25));
			new_row.fSubent = &Subents.back();
			Rows.push_back(new_row);
			Subents.back().DataTable.push_back(&Rows.back());
		}
	}
	
	sqlite3_finalize(stmt);
	
	vector<string> col_names;
	sqlite3_prepare_v2(db, extract_columns_name, -1, &stmt, 0);
	if(connection == SQLITE_OK)
	{
		sqlite3_bind_text(stmt, 1, SubentID.c_str(), -1, SQLITE_STATIC);
		while(sqlite3_step(stmt) == SQLITE_ROW)
		{
			col_names.push_back((char*)sqlite3_column_text(stmt,0));
		}
	} 
	Subents.back().col_names = col_names;
	
	sqlite3_finalize(stmt);

	
	if(Entries.back().EntryID != EntryID)
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
					Entries.back().GetAuthors(authors); // заполняем vector<string> Authors и FirstAuthor
				}
				
				if(sqlite3_column_type(stmt, 2) == SQLITE_NULL)
				{
					Entries.back().Title = "no title";
				}
				else
				{
					json title = json::parse((char*)sqlite3_column_text(stmt,2));
					Entries.back().GetTitle(title); // заполняем Title
				}
				
				if(sqlite3_column_type(stmt, 3) == SQLITE_NULL) // sqlite не обрабатывает null если это текст
				{
					Entries.back().Detector = "no detector info";
				}
				else
				{
					json detectors = json::parse((char*)sqlite3_column_text(stmt,3));
					Entries.back().GetDetector(detectors); // заполняем Detector
				}

				Entries.back().Year = (char*)sqlite3_column_text(stmt,4); // год
				
				if(sqlite3_column_type(stmt, 5) == SQLITE_NULL)
				{
					Entries.back().DOI = "";
				}
				else
				{
					Entries.back().DOI = (char*)sqlite3_column_text(stmt,5); // DOI
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
	
}

void C5Manager::GetC5EnergyDistribution(multimap<double, C5Row*> table, double key)
{
	EnergyDistribution ED;
	
	auto itr = table.begin();
	ED.fEntry = itr->second->fSubent->fEntry;
	ED.fSubent = itr->second->fSubent;
	
	for(auto[itr, end] = table.equal_range(key); itr!=end; itr++)
	{
		int N = ED.GetN();
		double y = itr->second->Row[0]*1e3;
		double dy = itr->second->Row[1]*1e3;
		double En = itr->second->Row[2]/1e6;
		double dEn = itr->second->Row[3]/1e6; 
		ED.SetPoint(N, En, y);
		ED.SetPointError(N, dEn, dy);						
	}
	ED_vec.push_back(ED);
}

void C5Manager::GetC5AngularDistribution(multimap<pair<double, double>, C5Row*> table, pair<double, double> key)
{	
	AngularDistribution AD;
	
	auto itr = table.begin();
	AD.fEntry = itr->second->fSubent->fEntry;
	AD.fSubent = itr->second->fSubent;
	string x3_name = itr->second->fSubent->col_names[1];
	
	for(auto[itr, end] = table.equal_range(key); itr!=end; ++itr)
	{
		int N = AD.GetN();
		double y = itr->second->Row[0]*1e3;
		double dy = itr->second->Row[1]*1e3;
		double Angle = itr->second->Row[6];
		double dAngle = itr->second->Row[7];
		
		if(x3_name == "Angle: cosine")
		{
			Angle = acos(Angle)/3.1416*180;
			dAngle = abs(acos(Angle+dAngle)-acos(Angle-dAngle))/3.1416*180;
		}
		/*
		else if(x3_name == "Anngle: q (momentum transfer)")
		{
			
		} 
		*/
		
		AD.SetPoint(N, Angle, y);
		AD.SetPointError(N, dAngle, dy);	
		AD.En = key.second/1e6;				
	}
	AD_vec.push_back(AD);
}







