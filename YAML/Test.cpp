#include <unordered_map>
#include <string>
#include <memory>
#include <any>
#include <stdexcept>
#include <iostream>
#include "../Parser.cpp"


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

class YANDFMapObject
{
	public:
	map<string,YANDFMapObject> Content;
	int C_I=0;
	double C_F=0;
	string C_S;
	bool ClassVariables=false;
	string BackKey="";
	YANDFMapObject& operator=(const int I)
	{
		C_I=I;
		ClassVariables=true;
		return *this;
		//return 0;
	}
	YANDFMapObject& operator=(const double I)
	{
		C_F=I;
		ClassVariables=true;
		return *this;
		//return 0;
	}
	YANDFMapObject& operator=(const string I)
	{
		C_S=I;
		ClassVariables=true;
		return *this;
		//return 0;
	}
	YANDFMapObject& operator[](string key)
	{
		return Content[key];
	}
	YANDFMapObject& operator[](int key)
	{
		return Content[to_string(key)];
	}
	void get(int &I)
	{
		I=C_I;
	}
	void get(double &I)
	{
		I=C_F;
	}
	void get(string &I)
	{
		I=C_S;
	}
	void get(string k,int &I)
	{
		if (Content.find(k) != Content.end()) 
		{
			Content[k].get(I);
		}
	}
	void get(string k,double &I)
	{
		if (Content.find(k) != Content.end()) 
		{
			Content[k].get(I);
		}
	}
	void get(string k,string &I)
	{
		if (Content.find(k) != Content.end()) 
		{
			Content[k].get(I);
		}
	}
	void get(string k,YANDFMapObject &I)
	{
		if (Content.find(k) != Content.end()) 
		{
			I=Content[k];
		}
	}
	void ParseYANDF(string inp)
	{
		string line;
		stringstream ss(inp);
		string LastKey="";
		int LastIndent=0;
		vector<string> keys;
		while(getline(ss,line))
		{
			bool IsPrimeKey=false;
			if(line.size()<2)
			{
				continue;
			}
			if(line[0]=='#')
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
				if(LastIndent>Indent)
				{
					for(unsigned int i=0;i<keys.size();i++)
					{
						cout<<"key "<<i<<":"<<keys[i]<<"\n";
					}
					keys.resize(0);
				}
				if(IsPrimeKey)
				{
					keys.push_back(key);
				}
				LastIndent=Indent;
			}
		}
	}
};

void Test()
{
	string s;
	CopyFileContentToBuffer("gam021047L17L02.tot",s);
	YANDFMapObject m;
	m.ParseYANDF(s);
}
