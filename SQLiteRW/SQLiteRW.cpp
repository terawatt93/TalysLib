#include "SQLiteRW.hh"

vector<string> SplitStr(string s, string delimiter)
{
	vector<string> result;
	size_t pos = 0;
	std::string token;
	while ((pos = s.find(delimiter)) != std::string::npos)
	{
   		token = s.substr(0, pos);
   		result.push_back(token);
   		s.erase(0, pos + delimiter.length());
	}
	if(s.size()>0)
	result.push_back(s);
	return result;
}

string SQLRow::GetValue(string Key)
{
	stringstream sstr;
	for(unsigned int i=0;i<Headers.size();i++)
	{
		if(Headers[i]==Key)
		{
			if(Types[i]=='f')
			{
				sstr<<GetD(i);
			}
			if(Types[i]=='i')
			{
				sstr<<GetI(i);
			}
			if(Types[i]=='s')
			{
				sstr<<"\'"<<GetS(i)<<"\'";
			}
			return sstr.str();
		}
	}
	return "";
}

string SQLRow::AsUpdateString()
{
	stringstream sstr;
	for(int i=0;i<Types.size();i++)
	{
		if(Headers.size()>i)
		{
			sstr<<Headers[i]<<" = ";
			if(Types[i]=='f')
			{
				sstr<<GetD(i);
			}
			if(Types[i]=='i')
			{
				sstr<<GetI(i);
			}
			if(Types[i]=='s')
			{
				sstr<<"\'"<<GetS(i)<<"\'";
			}
			if(Types.size()>1)
			{
				if(i<Types.size()-1)
				sstr<<",";
			}
		}
	}
	return sstr.str();
}

double SQLRow::GetD(int index)
{
	if(index>=Types.size())
	{
		cout<<"This is SQLRow::GetD("<<index<<"): index is out of range. Size of container is "<<Types.size()<<". -1e24 returned\n";
		return -1e24;
	}
	for(unsigned int i=0;i<Content_d.size();i++)
	{
		if(Content_d[i].first==index)
		{
			return (Content_d[i].second);
		}
	}
	cout<<"This is SQLRow::GetD("<<index<<"): value with type double not found in this place. -1e24 returned\n";
	return -1e24;
}
int SQLRow::GetI(int index)
{
	if(index>=Types.size())
	{
		cout<<"This is SQLRow::GetI("<<index<<"): index is out of range. Size of container is "<<Types.size()<<". -2147483647 returned\n";
		return -2147483647;
	}
	for(unsigned int i=0;i<Content_i.size();i++)
	{
		if(Content_i[i].first==index)
		{
			return (Content_i[i].second);
		}
	}
	cout<<"This is SQLRow::GetI("<<index<<"): value with type double not found in this place. -2147483647 returned\n";
	return -2147483647;
}
string SQLRow::GetS(int index)
{
	if(index>=Types.size())
	{
		cout<<"This is SQLRow::GetS("<<index<<"): index is out of range. Size of container is "<<Types.size()<<". empty string returned\n";
		return "";
	}
	for(unsigned int i=0;i<Content_s.size();i++)
	{
		if(Content_s[i].first==index)
		{
			return (Content_s[i].second);
		}
	}
	cout<<"This is SQLRow::GetS("<<index<<"): value with type double not found in this place. empty string returned\n";
	return "";
}

string SQLRow::AsString()
{
	stringstream sstr;
	for(int i=0;i<Types.size();i++)
	{
		if(Types[i]=='f')
		{
			sstr<<GetD(i);
		}
		if(Types[i]=='i')
		{
			sstr<<GetI(i);
		}
		if(Types[i]=='s')
		{
			sstr<<"\""<<GetS(i)<<"\"";
		}
		if(Types.size()>1)
		{
			if(i<Types.size()-1)
			sstr<<" ";
		}
	}
	return sstr.str();
}
string SQLRow::AsSQLString()
{
	stringstream sstr;
	for(int i=0;i<Types.size();i++)
	{
		if(Types[i]=='f')
		{
			sstr<<GetD(i);
		}
		if(Types[i]=='i')
		{
			sstr<<GetI(i);
		}
		if(Types[i]=='s')
		{
			sstr<<"\'"<<GetS(i)<<"\'";
		}
		if(Types.size()>1)
		{
			if(i<Types.size()-1)
			sstr<<",";
		}
	}
	return sstr.str();
}
SQLRow &operator << (SQLRow &tx, double value)
{
	tx.Content_d.push_back(pair<int,double>(tx.current_index_in,value));
	tx.current_index_in++;
	tx.TotalContent++;
	tx.Types+='f';
	return tx;
}
SQLRow &operator << (SQLRow &tx, int value)
{
	tx.Content_i.push_back(pair<int,int>(tx.current_index_in,value));
	tx.current_index_in++;
	tx.TotalContent++;
	tx.Types+='i';
	return tx;
}
SQLRow &operator << (SQLRow &tx, string value)
{
	tx.Content_s.push_back(pair<int,string>(tx.current_index_in,value));
	tx.current_index_in++;
	tx.TotalContent++;
	tx.Types+='s';
	return tx;
}

SQLRow &operator >> (SQLRow &tx, double &value)
{
	for(unsigned int i=0;i<tx.Content_d.size();i++)
	{
		if(tx.Content_d[i].first==tx.current_index_out)
		{
			value=(tx.Content_d[i].second);
			tx.current_index_out++;
			break;
		}
	}
	return tx;
}
SQLRow &operator >> (SQLRow &tx, int &value)
{
	for(unsigned int i=0;i<tx.Content_i.size();i++)
	{
		if(tx.Content_i[i].first==tx.current_index_out)
		{
			value=(tx.Content_i[i].second);
			tx.current_index_out++;
			break;
		}
	}
	return tx;
}
SQLRow &operator >> (SQLRow &tx, string &value)
{
	for(unsigned int i=0;i<tx.Content_s.size();i++)
	{
		if(tx.Content_s[i].first==tx.current_index_out)
		{
			value=(tx.Content_s[i].second);
			tx.current_index_out++;
			break;
		}
	}
	return tx;
}

void SQLRow::FromSQL(sqlite3_stmt* stmt)
{
	int NColumns=sqlite3_data_count(stmt);
	for(int i=0;i<NColumns;i++)
	{
		Headers.push_back(sqlite3_column_name(stmt,i));
		int Type=sqlite3_column_type(stmt,i);
		
		if(Type==1)
		{
			Content_i.push_back(pair<int,int>(current_index_in,sqlite3_column_int(stmt,i)));
			current_index_in++;
			TotalContent++;
			Types+='i';
		}
		if(Type==2)
		{
			Content_d.push_back(pair<int,double>(current_index_in,sqlite3_column_double(stmt,i)));
			current_index_in++;
			TotalContent++;
			Types+='f';
		}
		if(Type==3)
		{
			string content=reinterpret_cast<const char*>(sqlite3_column_text(stmt,i));
			Content_s.push_back(pair<int,string>(current_index_in,content));
			current_index_in++;
			TotalContent++;
			Types+='s';
		}
		if(Type==5)
		{
			int NullHandlingType=0;
			if(fBase)
			{
				NullHandlingType=fBase->NullHandlingType;
			}
			if(NullHandlingType==0)//пустая строка
			{
				Content_s.push_back(pair<int,string>(current_index_in,""));
				current_index_in++;
				TotalContent++;
				Types+='s';
			}
			if(NullHandlingType==1)//NANI
			{
				Content_i.push_back(pair<int,int>(current_index_in,std::nan("")));
				current_index_in++;
				TotalContent++;
				Types+='i';
			}
			if(NullHandlingType==2)//NANF
			{
				Content_d.push_back(pair<int,double>(current_index_in,std::nan("")));
				current_index_in++;
				TotalContent++;
				Types+='f';
			}
			if(NullHandlingType==3)//0I
			{
				Content_i.push_back(pair<int,int>(current_index_in,0));
				current_index_in++;
				TotalContent++;
				Types+='i';
			}
			if(NullHandlingType==4)//0F
			{
				Content_d.push_back(pair<int,double>(current_index_in,0));
				current_index_in++;
				TotalContent++;
				Types+='f';
			}
		}
	}
}

void SQLiteRW::Open(string Filename)
{
	rc = sqlite3_open(Filename.c_str(), &db);
	if( rc )
	{
		cout<<"Cannot open file with name \""<<Filename<<"\"\n";
	}
}
int SQLiteRW::SelectTable(string TabName)
{
	if(!db)
	{
		cout<<"Db is not opened! Cannot check exsistance of table\n";
		return 0;
	}
	TString Command=TString::Format("select count(type) from sqlite_master where type='table' and name='%s')",TabName.c_str());
	sqlite3_stmt *stmt;
	CurrentTable=TabName;
	rc = sqlite3_prepare_v2(db,Command.Data(), -1, &stmt, NULL);
	rc = sqlite3_step(stmt);
	int result=sqlite3_column_int(stmt, 0);
	return 1;
}
void SQLiteRW::CreateTable(string Headers)
{
	vector<string> HDRS=SplitStr(Headers,";");
	vector<string> Types;
	vector<string> Headers_v;
	for(unsigned int i=0;i<HDRS.size();i++)
	{
		TString ts(HDRS[i].c_str());
		ts.ReplaceAll("<"," ");
		ts.ReplaceAll(">","");
		stringstream sstr(ts.Data());
		string ColName, Type;
		sstr>>ColName>>Type;
		if((Type=="float")||(Type=="double")||(Type=="Float_t")||(Type=="Double_t"))
		{
			Type="FLOAT";
		}
		if((Type=="string")||(Type=="TString"))
		{
			Type="TEXT";
		}
		if((Type=="int")||(Type=="Int_t")||(Type=="unsigned"))
		{
			Type="INTEGER";
		}
		Headers_v.push_back(ColName);
		Types.push_back(Type);
	}
	TString Command=TString::Format("CREATE TABLE %s (",CurrentTable.c_str());
	for(unsigned int i=0;i<Headers_v.size();i++)
	{
		Command+=TString::Format("%s %s",Headers_v[i].c_str(),Types[i].c_str());
		if(Headers.size()>1)
		{
			if(i<Headers_v.size()-1)
			{
				Command+=",";
			}
		}
		
	}
	Command+=")";
	TabHeaders=Headers_v;
	rc = sqlite3_exec(db,Command.Data(), 0, 0, 0);
}

void SQLiteRW::Close()
{
	sqlite3_close(db);
}
void SQLiteRW::Insert()
{
	TString Command;
	for(unsigned int i=0;i<ToInsert.size();i++)
	{
		//cout<<ToInsert[i].TotalContent<<"\n";
		if(ToInsert[i].TotalContent>0)
		{
			Command+=TString::Format("INSERT INTO %s(",CurrentTable.c_str());
			for(unsigned int j=0;j<ToInsert[i].Headers.size();j++)
			{
				Command+=ToInsert[i].Headers[j];
				if(ToInsert[i].Headers.size()>1)
				{
					if(j<ToInsert[i].Headers.size()-1)
					{
						Command+=",";
					}
				}
			}
			Command+=") VALUES ("+TString((ToInsert[i].AsSQLString()).c_str())+");";
		}
		
	}
	//cout<<Command<<"\n";
	rc = sqlite3_exec(db,Command.Data(), 0, 0, 0);
}
void SQLiteRW::Update(string Condition)
{
	stringstream Command;
	
	for(unsigned int i=0;i<ToInsert.size();i++)
	{
		if(Condition.find("UPDATE")==string::npos)
		{
			vector<string> Values=SplitStr(Condition,"{");
			for(unsigned int j=0;j<Values.size();j++)
			{
				if(Values[j].find("}")!=string::npos)
				{
					TString Key=Values[j];
					Key.ReplaceAll("}","");
					Values[j]=ToInsert[i].GetValue(Key.Data());
				}
			}
			Condition="";
			for(unsigned int j=0;j<Values.size();j++)
			{
				Condition+=Values[j];
			}
			
			Command<<TString::Format("UPDATE %s SET ",CurrentTable.c_str());
			Command<<ToInsert[i].AsUpdateString();
			
			if(Condition.size()>0)
			{
				TString cond(Condition.c_str());
				cond.ReplaceAll("&&","AND");
				cond.ReplaceAll("||","OR");
				cond.ReplaceAll("! ","NOT");
				Command<<" WHERE "+cond;
			}
		}
		Command<<";";
	}
	rc = sqlite3_exec(db,(Command.str()).c_str(), 0, 0, 0);
}
SQLiteRW &operator << (SQLiteRW &tx, double value)
{
	if(tx.ToInsert.size()==0)
	{
		tx.ToInsert.emplace_back();
		tx.ToInsert[tx.ToInsert.size()-1].Headers=tx.TabHeaders;
	}
	tx.ToInsert[tx.ToInsert.size()-1]<<value;
	return tx;
}
SQLiteRW &operator << (SQLiteRW &tx, int value)
{
	if(tx.ToInsert.size()==0)
	{
		tx.ToInsert.emplace_back();
		tx.ToInsert[tx.ToInsert.size()-1].Headers=tx.TabHeaders;
	}
	tx.ToInsert[tx.ToInsert.size()-1]<<value;
	return tx;
}
SQLiteRW &operator << (SQLiteRW &tx, string value)
{
	if(value.size()==1)
	{
		if(value=="\n")
		{
			tx.ToInsert.emplace_back();
			tx.ToInsert[tx.ToInsert.size()-1].Headers=tx.TabHeaders;
			return tx;
		}
	}
	if(tx.ToInsert.size()==0)
	{
		tx.ToInsert.emplace_back();
		tx.ToInsert[tx.ToInsert.size()-1].Headers=tx.TabHeaders;
	}
	tx.ToInsert[tx.ToInsert.size()-1]<<value;
	return tx;
}

vector<SQLRow> SQLiteRW::Select(string Condition)
{
	vector<SQLRow> result;
	TString Command;
	if(Condition.find("SELECT")==string::npos)
	{
		Command+=TString::Format("SELECT * FROM %s",CurrentTable.c_str());
		if(Condition.size()>0)
		{
			TString cond(Condition.c_str());
			cond.ReplaceAll("&&","AND");
			cond.ReplaceAll("||","OR");
			cond.ReplaceAll("! ","NOT");
			Command+=" WHERE "+cond;
		}
	}
	Command+=";";
	//cout<<"Command:"<<Command<<"\n";
	sqlite3_stmt* stmt;
	sqlite3_prepare_v2(db, Command.Data(),Command.Length(), &stmt, NULL);
	bool done=false;
	while (!done) 
	{
		if(sqlite3_step (stmt)==SQLITE_ROW)
		{
			SQLRow r;
			r.fBase=this;
			r.FromSQL(stmt);
			result.push_back(r);
		}
		else
		{
			done=true;
		}
	}
	return result;
}

void Test()
{
	SQLiteRW rw;
	rw.Open("test.db");
	rw.SelectTable("test_table");
	rw.CreateTable("test_d<double>;test_i<int>;test_s<string>,test_n<string>");
	//SQLRow r;
	//r.Headers=rw.TabHeaders;
	rw<<gRandom->Uniform()<<2<<"a"<<"\n";
	//rw<<12.0<<23<<"ab"<<"\n";
	rw.Insert();
	//rw.Update("test_s={test_s}");
	rw.Close();
	
	rw.Open("test.db");
	rw.SelectTable("test_table");
}

void TestRead()
{
	SQLiteRW rw;
	rw.Open("test.db");
	rw.SelectTable("test_table");
	vector<SQLRow> lines=rw.Select("");
	for(unsigned int i=0;i<lines.size();i++)
	{
		cout<<lines[i].AsString()<<"\n";
	}
}

