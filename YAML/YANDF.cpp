#include "YANDF.hh"

bool CheckPrimeKey(string line)
{
	if(line.size()<2)
	{
		return false;
	}
	bool Prime=false;
	int i_dot=line.size();
	for(unsigned int i=1;i<line.size();i++)
	{
		if(line[i]==':')
		{
			Prime=true;
			i_dot=i;
		}
		if(i>i_dot)
		{
			if(line[i]!=' ')
			{
				Prime=false;
			}
		}
	}
	return Prime;
}
void GetDimension(string &key, string &dim)
{
	bool FindFirst=false;
	string r_key;
	for(unsigned int i=0;i<key.size();i++)
	{
		if(key[i]=='[')
		{
			FindFirst=true;
			continue;
		}
		if(key[i]==']')
		{
			FindFirst=false;
		}
		if(FindFirst)
		{
			dim+=key[i];
		}
		if((dim.size()==0)&&(!FindFirst))
		{
			r_key+=key[i];
		}
	}
	int Space_len=0;
	for(unsigned int i=r_key.size()-1;i>=0;i--)
	{
		if(r_key[i]==' ')
		{
			r_key.pop_back();
		}
		else
		{
			break;
		}
	}
	key=r_key;
}
YANDFMapObject& YANDFMapObject::operator=(const int I)
{
	C_I=I;
	ClassVariables=true;
	return *this;
	//return 0;
}
YANDFMapObject& YANDFMapObject::operator=(const double I)
{
	C_F=I;
	ClassVariables=true;
	return *this;
	//return 0;
}
YANDFMapObject& YANDFMapObject::operator=(const string I)
{
	C_S=I;
	ClassVariables=true;
	return *this;
	//return 0;
}
YANDFMapObject& YANDFMapObject::operator[](string key)
{
	return Content[key];
}
YANDFMapObject& YANDFMapObject::operator[](int key)
{
	return Content[to_string(key)];
}
YANDFMapObject* YANDFMapObject::at(string key)
{
	//if (Content.find(key) != Content.end()) 
	//{
		return &Content[key];
	//}
	//return 0;
}
YANDFMapObject* YANDFMapObject::at(int key)
{
	//if (Content.find(to_string(key)) != Content.end()) 
	//{
		return &Content[to_string(key)];
	//}
	//return 0;
}
void YANDFMapObject::get(int &I)
{
	I=C_I;
}
void YANDFMapObject::get(double &I)
{
	I=C_F;
}
void YANDFMapObject::get(string &I)
{
	I=C_S;
}
void YANDFMapObject::set(int I)
{
	C_I=I;
}
void YANDFMapObject::set(double I)
{
	C_F=I;
}
void YANDFMapObject::set(string I)
{
	C_S=I;
}
void YANDFMapObject::get(string k,int &I)
{
	if (Content.find(k) != Content.end()) 
	{
		Content[k].get(I);
	}
}
void YANDFMapObject::get(string k,double &I)
{
	if (Content.find(k) != Content.end()) 
	{
		Content[k].get(I);
	}
}
void YANDFMapObject::get(string k,string &I)
{
	if (Content.find(k) != Content.end()) 
	{
		Content[k].get(I);
	}
}
void YANDFMapObject::get(string k,YANDFMapObject &I)
{
	if (Content.find(k) != Content.end()) 
	{
		I=Content[k];
	}
}
void YANDFMapObject::ParseYANDF(string inp)
{
	string line;
	stringstream ss(inp);
	string LastKey="";
	int LastIndent=0;
	vector<string> keys;
	vector<int> indents;
	while(getline(ss,line))
	{
		bool IsPrimeKey=false;
		if(line.size()<2)
		{
			continue;
		}
		if((line[0]=='#')&&(line[1]!='#'))
		{
			int Indent=0;
			for(unsigned int i=1;i<line.size();i++)
			{
				if(line[i]==' ')
				{
					Indent++;
				}
				else
				{
					break;
				}
			}
			IsPrimeKey=CheckPrimeKey(line);
			vector<string> STRContent=SplitString(line,':');
			string key=STRContent[0];
			key=key.substr(Indent+1);
			string Dim="";
			GetDimension(key,Dim);
			if(LastIndent>Indent)
			{
				vector<string> real_keys;
				vector<int> real_indents;
				for(unsigned int i=0;i<indents.size();i++)
				{
					if(Indent>indents[i])
					{
						real_keys.push_back(keys[i]);
						real_indents.push_back(indents[i]);
					}
				}
				keys=real_keys;
				indents=real_indents;
			}
			if(IsPrimeKey)
			{
				keys.push_back(key);
				indents.push_back(Indent);
			}
			LastIndent=Indent;
			if(!IsPrimeKey)
			{
				YANDFMapObject *obj=this;
				for(unsigned int i=0;i<keys.size();i++)
				{
					obj=obj->at(keys[i]);
				}
				if(obj)
				{
					if(STRContent.size()>1)
					{
						string Value=STRContent[1];
						if(IsNumber(Value))
						{
							if(IsFloat(Value))
							{
								(obj->at(key))->set(atof(Value.c_str()));
							}
							else
							{
								(obj->at(key))->set(atoi(Value.c_str()));
								(obj->at(key))->Dimension=Dim;
							}
						}
						else
						{
							(obj->at(key))->set(Value);
						}
					}
				}
			}
		}
		else
		{
			if((line[0]=='#')&&(line[1]=='#'))
			{
				this->at("quantity")->at("datablock")->at("columns")->get(NColumns);
				this->at("quantity")->at("datablock")->at("entries")->get(NRows);
				DataContent.resize(NColumns);
				stringstream sstr1(line);
				bool FillDataHeaders=false;
				for(int i=0;i<NColumns;i++)
				{
					DataContent[i].resize(NRows);
				}
				if(DataHeaders.size()==0)
				{
					for(int i=0;i<NColumns+1;i++)
					{
						string str;
						sstr1>>str;
						if(i>0)
						{
							DataHeaders.push_back(str);
						}
					}
					FillDataHeaders=true;
				}
				if((DataDimensions.size()==0)&&(!FillDataHeaders))
				{
					for(int i=0;i<NColumns+1;i++)
					{
						string str;
						sstr1>>str;
						if(i>0)
						{
							DataDimensions.push_back(str);
						}
					}
				}
			}
			else
			{
				if(NRowsRead<NRows)
				{
					stringstream sstr1(line);
					for(int i=0;i<NColumns;i++)
					{
						string str;
						sstr1>>str;
						DataContent[NRowsRead][i]=atof(str.c_str());
					}
					NRowsRead++;
				}
			}
		}
	}
}
void YANDFMapObject::ReadYANDF(string fname)
{
	string dat;
	CopyFileContentToBuffer(fname,dat);
	ParseYANDF(dat);
}

void GetProductsFromCalculationDir(vector<string> Filenames,int Z, int A,string Projectile, vector<pair<int,int> > &ZA, vector<string> &Reactions, vector<string> &OutParticles)
{
	int Zproj=0, Aproj=0;
	GetAZ(Projectile,Zproj,Aproj);
	for(unsigned int i=0;i<Filenames.size();i++)
	{
		if(Filenames[i].size()>8)
		{
			if((Filenames[i][0]=='r')&&(Filenames[i][1]=='p'))
			{
				string Zstr=Filenames[i].substr(2,3);
				string Astr=Filenames[i].substr(5,3);
				int ZZ=atoi(Zstr.c_str()), AA=atoi(Astr.c_str());
				ZA.push_back({ZZ,AA});
				int Zout=Z+Zproj-ZZ;
				int Aout=A+Aproj-AA;
				string OutgoingParticle=GetParticleName(Zout,Aout);
				OutParticles.push_back(OutgoingParticle);
				Reactions.push_back("("+Projectile+","+OutgoingParticle+")");
			}
		}
	}
}

/*void Test()
{
	string s;
	CopyFileContentToBuffer("gam021047L17L02.tot",s);
	YANDFMapObject m;
	m.ParseYANDF(s);
	double LevNumber=0;
	m["reaction"]["gamma energy"].get(LevNumber);
	cout<<m["quantity"]["datablock"]["columns"].C_I<<"\n";
	cout<<LevNumber<<"\n";
}
void Test2()
{
	vector<string> Filenames=ListFiles("/dev/shm/CalculationResults0/48Ti0/"), Reactions, OutParticles;
	int Z=22,A=48;
	string Projectile="n";
	vector<pair<int,int> > ZA;
	GetProductsFromCalculationDir(Filenames,Z,A,Projectile,ZA,Reactions,OutParticles);
	for(unsigned int i=0;i<ZA.size();i++)
	{
		cout<<"Z="<<ZA[i].first<<" A="<<ZA[i].second<<" Reaction="<<Reactions[i]<<"\n";
	}
}*/
