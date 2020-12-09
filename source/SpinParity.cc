#include "../TalysLib.hh"
#include <sys/stat.h>
#include <bits/stdc++.h>
#include <cstring>
#include <algorithm>
#include <cctype>
#include "../Parser.cpp"
#include <TLine.h>
#include <TText.h>
#include <TList.h>
#include <TKey.h>
#pragma once
//Методы класса SpinParity

SpinParity::SpinParity(float J_in, int Parity_in)
{
	J=J_in;
	Parity=Parity_in;
}
SpinParity::SpinParity(float J_in)
{
	J=abs(J_in);
	Parity=sgn(J_in);
}
SpinParity::SpinParity(string str)
{
	if(str[str.size()-1]=='+')
	{
		Parity=1;
	}
	else if(str[str.size()-1]=='-')
	{
		Parity=-1;
	}
	J=abs(atof(str.substr(0,str.size()-1).c_str()));
}
string SpinParity::GetLine()
{
	string s;
	stringstream ss;
	ss<<*this;
	ss>>s;
	return s;
}
/*SpinParity::SpinParity()
{
	J=0;
	Parity=0;
}*/

std::istream& operator >> (std::istream &istr,SpinParity &JP)
{
	int Parity=0;
	string str;
	istr>>str;
	JP=SpinParity(str);
	return istr;
}
std::ostream& operator << (std::ostream &ostr,SpinParity &JP)
{
	ostr<<JP.J;
	if(JP.Parity<0)
	{
		ostr<<"-";
	}
	else
	{
		ostr<<"+";
	}
	return ostr;
}

bool operator == (const SpinParity &JP1, const SpinParity &JP2)
{
	if((JP1.J==JP2.J)&&(JP1.Parity==JP2.Parity))
	{
		return true;
	}
	return false;
}

float abs(SpinParity JP)
{
	return abs(JP);
}

vector<SpinParity> ENSDFJPToNormalJP(string JP, int &Mark)
{
	vector<SpinParity> result;
	int sign=0;
	if(((int)JP.find("+"))>0)
	{
		sign=1;
	}
	if(((int)JP.find("-"))>0)
	{
		sign=-1;
	}
	if(((int)JP.find("TO"))>0)
	{
		stringstream s(JP);
		float low,up;
		string tmp1,tmp2,tmp3;
		s>>tmp1>>tmp2>>tmp3;
		low=atof(tmp1.c_str());
		up=atof(tmp3.c_str());
		float value=low;
		while(value<=up)
		{
			result.push_back(SpinParity(value,sign));
			value+=1;
		}
		Mark=result.size()*2;
		return result;
	}
	
	if(sign!=0)
	{
		string num_str;
		for(unsigned int i=0;i<JP.size();i++)
		{
			
			if(((JP[i]>='0')&&(JP[i]<='9'))||(JP[i]=='/'))
			{
				num_str+=JP[i];
			}
			if(JP[i]==',')
			{
				float value=0;
				int slash_position=(int)num_str.find("/");
				if(slash_position>0)
				{
					value=atof(num_str.substr(0,slash_position).c_str())/atof(num_str.substr(slash_position+1,num_str.size()-1).c_str());
				}
				else
				{
					value=atof(num_str.c_str());
				}
				result.push_back(SpinParity(value,sign));
				num_str.resize(0);
			}
		}
		float value=0;
		int slash_position=(int)num_str.find("/");
		if(slash_position>0)
		{
			value=atof(num_str.substr(0,slash_position).c_str())/atof(num_str.substr(slash_position+1,num_str.size()-1).c_str());
		}
		else
		{
			value=atof(num_str.c_str());
		}
		result.push_back(SpinParity(value,sign));
		
	}
	Mark=result.size();
	if(((int)JP.find("("))>=0)
	{
		Mark=2*result.size();
	}
	if(sign==0)
	{
		Mark=99;
	}
	return result;
}

vector<SpinParity> GenerateGammaMultipolarity(SpinParity &JPi,SpinParity &JPf)
{
	vector<double> J=QuantumSum(JPi.J,JPf.J);
	vector<SpinParity> result;
	for(unsigned int i=0;i<J.size();i++)
	{
		result.emplace_back(J[i],JPi.Parity*JPf.Parity);
	}
	return result;
}
