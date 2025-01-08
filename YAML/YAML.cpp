#include "YAML.hh"
#include "../Parser.cpp"

void YAML::ParseReaction()
{
	TString ts(ReactionType.c_str());
	ts.ReplaceAll("(","");
	ts.ReplaceAll(","," ");
	ts.ReplaceAll("_"," ");
	ts.ReplaceAll(")","");
	stringstream sstr(ts.Data());
	string Mark;
	sstr>>Projectile>>OutgoingParticle>>Mark;
	WithEDep=false;
	if(Mark.size()>0)
	{
		WithEDep=true;
	}
	/*if(OutgoingParticle=="el")
	{
		OutgoingParticle=Projectile;
	}*/
	Reaction="("+Projectile+","+OutgoingParticle;
	if(WithEDep&&(Projectile==OutgoingParticle))
	{
		Reaction+="')";
	}
	else
	{
		Reaction+=")";
	}
}

void YAML::ParseYAML(string Content_)
{
	stringstream ifs(Content_);
	string line;
	while(getline(ifs,line))
	{
		vector<string> v=SplitString(line,' ');
		if(v.size()>0)
		{
			if(v[0]=="#")
			{
				if(v[1]=="type:")
				{
					ReactionType=v[2];
					ParseReaction();
				}
				if(v[1]=="Q-value")
				{
					Q=atof(v[2].c_str());
				}
				if(v[1]=="number:")
				{
					LevelNumber=atoi(v[2].c_str());
				}
				if(v[1]=="columns:")
				{
					NColumns=atoi(v[2].c_str());
				}
				if(v[1]=="entries:")
				{
					NRows=atoi(v[2].c_str());
				}
				if(v[1]=="quantity:")
				{
					for(unsigned int i=2;i<v.size();i++)
					{
						Quantity+=v[i];
						if(i<v.size()-1)
						{
							Quantity+=" ";
						}
					}
				}
			}
			else if(v[0]=="##")
			{
				v.erase(v.begin());
				if(Headers.size()==0)
				{
					Headers=v;
					Content.resize(NColumns);
					continue;
				}
				else if(Dimensions.size()==0)
				{
					Dimensions=v;
					continue;
				}
			}
			else
			{
				if(int(v.size())==NColumns)
				{
					for(unsigned int i=0;i<v.size();i++)
					{
						Content[i].push_back(atof(v[i].c_str()));
					}
				}
			}
		}
	}
}

vector<string> SplitStringByEmptyString(string input)
{
	vector<string> result;
	stringstream ifs(input);
	string line,line_tmp;
	while(getline(ifs,line))
	{
		if(line.size()==0)
		{
			result.push_back(line_tmp);
			line_tmp="";
		}
		else
		{
			line_tmp+=line+"\n";
		}
	}
	return result;
}
vector<string> GetYAMLStrings(string input)
{
	vector<string> result;
	stringstream ifs(input);
	string line,line_tmp;
	while(getline(ifs,line))
	{
		if(line.size()==0)
		{
			if(line_tmp.find("# reaction:")!=string::npos)
			{
				result.push_back(line_tmp);
			}
			line_tmp="";
		}
		else
		{
			line_tmp+=line+"\n";
		}
	}
	return result;
}

vector<YAML> ExtractYAMLFromString(string &FileContent)
{
	vector<string> YAMLData = GetYAMLStrings(FileContent);
	vector<YAML> result;
	result.resize(YAMLData.size());
	
	for(unsigned int i=0;i<YAMLData.size();i++)
	{
		result[i].ParseYAML(YAMLData[i]);
	}
	
	return result;
}
void AssignDataToLevels(Nucleus *Parent,string &FileContent)
{
	vector<YAML> YAMLData=ExtractYAMLFromString(FileContent);
	for(unsigned int i=0;i<YAMLData.size();i++)
	{
		
		if(YAMLData[i].Quantity=="angular distribution")
		{
			if(YAMLData[i].OutgoingParticle=="el")
			{
				Parent->Angle=YAMLData[i].Content[0];
				Parent->ElTot=YAMLData[i].Content[1];
				Parent->ElCompound=YAMLData[i].Content[3];
				Parent->ElDirect=YAMLData[i].Content[2];
			}
			else
			{
				Nucleus *Product=Parent->FindProductByReaction(YAMLData[i].Reaction);
				
				if(Product)
				{
					if(Product->Levels.size()>YAMLData[i].LevelNumber)
					{
						//ADTot,ADDirect, ADCompound, Angle
						
						Product->Levels[YAMLData[i].LevelNumber].ADTot=YAMLData[i].Content[1];
						Product->Levels[YAMLData[i].LevelNumber].ADCompound=YAMLData[i].Content[3];
						Product->Levels[YAMLData[i].LevelNumber].ADDirect=YAMLData[i].Content[2];
						Product->Levels[YAMLData[i].LevelNumber].Angle=YAMLData[i].Content[0];
					}
				}
			}
		}
	}
}

