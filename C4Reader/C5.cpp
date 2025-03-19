#include <iostream>
#include "C5.hh"
#include "../Parser.cpp"
#include "../TalysLib.hh"
#pragma once

string StringJoin(const vector<string> &strs, const string delim)
{
    if (strs.size() == 0) return "";
    vector<char> res;
    for (int i = 0; i < strs.size()-1; ++i)
    {
        for (auto c: strs[i]) res.push_back(c);
        for (auto c: delim) res.push_back(c);
    }
    for (auto c: strs[strs.size()-1]) res.push_back(c);
    return string{res.begin(), res.end()};
}

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

void C5Manager::SearchSubents() // эта функция выполняет поиск нужных сабентов и заполняет поля классов C5Row, SubentData, EntryData.
{
	string target = fMotherNucleus->Element + "-" + to_string(fMotherNucleus->A);
	string natural_isotop = fMotherNucleus->Element + "-0";
	sqlite3_stmt *stmt;
	connection = sqlite3_open_v2(db_name.c_str(), &db, SQLITE_OPEN_READONLY, NULL);
	
	const char* search_subent_query;
	const char* search_subent_query_v2;
	const char* extract_x2_hdr;
	const char* extract_c5_expansion;
	
	search_subent_query_v2 = "SELECT SubentID, zTarg, aTarg, zProd, aProd, Quant, SF1, SF2, SF3, SF4, SF5, SF6, SF7, SF8, SF9, MF, MT, reacode \n\
						FROM (SELECT DatasetID, MF, MT, compNotes, reacode FROM x4pro_ds WHERE Proj = ? AND (Targ1 = ? OR Targ1 = ?) \n\
						AND (reacode NOT LIKE '(%)/(%)' \n\
						AND reacode NOT LIKE '(%)//(%)' \n\
						AND reacode NOT LIKE '(%)*(%)' \n\
						AND reacode NOT LIKE '(%)+(%)' \n\
						AND reacode NOT LIKE '(%)-(%)')) AS table1 \n\
						INNER JOIN (SELECT * FROM REACSTR) AS table2 ON table1.DatasetID = table2.SubentID ";				
						
	search_subent_query = "SELECT SubentID, zTarg, aTarg, zProd, aProd, Quant, SF1, SF2, SF3, SF4, SF5, SF6, SF7, SF8, SF9, MF, MT FROM \n\
                        (SELECT DISTINCT SubentID, zTarg, aTarg, zProd, aProd, Quant, SF1, SF2, SF3, SF4, SF5, SF6, SF7, SF8, SF9 \n\
                        FROM REACSTR \n\
                        WHERE (Target = ? OR Target = ?) \n\
                        AND Projectile = 'N' \n\
                        GROUP BY SubentID \n\
                        HAVING COUNT(SubentID) = 1) AS table1 \n\
                        INNER JOIN \n\
                        (SELECT DatasetID, MF, MT FROM x4pro_ds) AS table2 \n\
                        ON table1.SubentID = table2.DatasetID ";              
    
					  
	sqlite3_prepare_v2(db, search_subent_query_v2, -1, &stmt, 0);
	if(connection == SQLITE_OK)
	{
		sqlite3_bind_text(stmt, 1, fMotherNucleus->Projectile.c_str(), -1, SQLITE_STATIC);
		sqlite3_bind_text(stmt, 2, target.c_str(), -1, SQLITE_STATIC);
        sqlite3_bind_text(stmt, 3, natural_isotop.c_str(), -1, SQLITE_STATIC);
        while(sqlite3_step(stmt) == SQLITE_ROW)
        {
            SubentData Subent;
            Subent.SubentID = (char*)sqlite3_column_text(stmt, 0);
            Subent.zTarg = sqlite3_column_int(stmt, 1);
            Subent.aTarg = sqlite3_column_int(stmt, 2);
            Subent.zProd = sqlite3_column_int(stmt, 3);
            Subent.aProd = sqlite3_column_int(stmt, 4);
            Subent.Quant = (char*)sqlite3_column_text(stmt, 5);
            Subent.SF1 = (sqlite3_column_type(stmt,6) != SQLITE_NULL) ? (char*)sqlite3_column_text(stmt,6) : "";
            Subent.SF2 = (sqlite3_column_type(stmt,7) != SQLITE_NULL) ? (char*)sqlite3_column_text(stmt,7) : "";
            Subent.SF3 = (sqlite3_column_type(stmt,8) != SQLITE_NULL) ? (char*)sqlite3_column_text(stmt,8) : "";
            Subent.SF4 = (sqlite3_column_type(stmt,9) != SQLITE_NULL) ? (char*)sqlite3_column_text(stmt,9) : "";
            Subent.SF5 = (sqlite3_column_type(stmt,10) != SQLITE_NULL) ? (char*)sqlite3_column_text(stmt,10) : "";
            Subent.SF6 = (sqlite3_column_type(stmt,11) != SQLITE_NULL) ? (char*)sqlite3_column_text(stmt,11) : "";
            Subent.SF7 = (sqlite3_column_type(stmt,12) != SQLITE_NULL) ? (char*)sqlite3_column_text(stmt,12) : "";          
            Subent.SF8 = (sqlite3_column_type(stmt,13) != SQLITE_NULL) ? (char*)sqlite3_column_text(stmt,13) : "";
            Subent.SF9 = (sqlite3_column_type(stmt,14) != SQLITE_NULL) ? (char*)sqlite3_column_text(stmt,14) : "";
            Subent.MF = sqlite3_column_int(stmt, 15);
            Subent.MT = sqlite3_column_int(stmt, 16);
            Subent.Reacode = (char*)sqlite3_column_text(stmt, 17);
            Subents.push_back(Subent);
            ExtractSubentData(); 
        }
    }
	sqlite3_finalize(stmt);
	
	sqlite3_close(db);
}

void C5Manager::ExtractSubentData()
{
	sqlite3_stmt *stmt;
	const char* extract_x2_hdr = "SELECT hdr FROM x4pro_hdr WHERE DatasetID = ? AND typ = 'x' AND varName = 'x2'";
	const char* extract_basic_units = "SELECT BasicUnits FROM x4pro_hdr WHERE DatasetID = ? AND typ = 'x' AND varName = 'y'";
	const char* extract_c5_expansion = "SELECT varName, expansion FROM x4pro_hdr WHERE DatasetID = ? AND typ = 'c' ";
	const char* extract_subent_query = "SELECT * FROM x4pro_c5dat WHERE DatasetID = ?";
	const char* extract_entry_query =  "SELECT * FROM\n\
										(SELECT SUBSTR(Subent,0,6) AS EntryID, json_extract(jx4z, '$.BIB.AUTHOR[0].x4codes'), json_extract(jx4z, '$.BIB.TITLE[0].x4freetext'),\n\
										json_extract(jx4z, '$.BIB.DETECTOR'), json_extract(jx4z, '$.BIB.METHOD')\n\
										FROM x4pro_x4z\n\
										WHERE Subent = ?) AS a\n\
										INNER JOIN\n\
										(SELECT YearRef1, DOI, EntryID FROM ENTRY) AS b\n\
										ON a.EntryID = b.EntryID";
	
	string SubentID = Subents.back().SubentID;
	string EntryID = SubentID.substr(0,5);

	sqlite3_prepare_v2(db, extract_c5_expansion, -1, &stmt, 0);
	sqlite3_bind_text(stmt, 1, SubentID.c_str(), -1, SQLITE_STATIC);
	if(connection == SQLITE_OK)
	{
		while(sqlite3_step(stmt) == SQLITE_ROW)
		{
            Subents.back().col_keys.push_back((char*)sqlite3_column_text(stmt,0));
            Subents.back().c5_expansion.insert(pair<string, string>(Subents.back().col_keys.back(), (char*)sqlite3_column_text(stmt,1)));
            Subents.back().col_keys.push_back("d" + Subents.back().col_keys.back());
		}
	}
	sqlite3_finalize(stmt);
	
	vector<string> x2_hdr;
	sqlite3_prepare_v2(db, extract_x2_hdr, -1, &stmt, 0);
	sqlite3_bind_text(stmt, 1, SubentID.c_str(), -1, SQLITE_STATIC);
	if(connection == SQLITE_OK)
	{
		while(sqlite3_step(stmt) == SQLITE_ROW)
		{
			x2_hdr.push_back((char*)sqlite3_column_text(stmt,0));
		}
	}
	Subents.back().x2_hdr = StringJoin(x2_hdr, "/");
	sqlite3_finalize(stmt);
	
	sqlite3_prepare_v2(db, extract_basic_units, -1, &stmt, 0);
	sqlite3_bind_text(stmt, 1, SubentID.c_str(), -1, SQLITE_STATIC);
	if(connection == SQLITE_OK)
	{
		while(sqlite3_step(stmt) == SQLITE_ROW)
		{
			Subents.back().Data_basic_units = (char*)sqlite3_column_text(stmt,0); 
		}
	}
	sqlite3_finalize(stmt);
			
	sqlite3_prepare_v2(db, extract_subent_query, -1, &stmt, 0);
	if(connection == SQLITE_OK)
	{
		sqlite3_bind_text(stmt, 1, SubentID.c_str(), -1, SQLITE_STATIC);
		while(sqlite3_step(stmt) == SQLITE_ROW)
		{
			SubentData::DataRow row;
			for(size_t i = 0; i < Subents.back().col_keys.size(); i++)
			{
				row.Row.insert(pair<string, double>(Subents.back().col_keys[i], sqlite3_column_double(stmt,i+3)));
			}
			if(sqlite3_column_type(stmt, 25) != SQLITE_NULL)
				row.cdat = json::parse((char*)sqlite3_column_text(stmt,25));
			Subents.back().DataTable.push_back(row);
		}
	}
	sqlite3_finalize(stmt);
	
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
}








