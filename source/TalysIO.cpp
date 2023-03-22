#include "../TalysLib.hh"
#include "../Parser.cpp"

#pragma once
void TalysInput::Set(string content)
{
	stringstream s(content);
	string line;
	while(getline(s,line));
	{
		stringstream s2(line);
		Keyword k;
		s2>>k.word;
		getline(s2,k.parameters);
		keywords.push_back(k);
	}
}
Keyword* TalysInput::GetKeyword(string word)
{
	for(unsigned int i=0;i<keywords.size();i++)
	{
		if(keywords[i].word==word)
		{
			return &keywords[i];
		}
	}
	return 0;
}
void TalysInput::SetKeyword(string word,int parameter)
{
	Keyword *k=GetKeyword(word);
	if(!k)
	{
		Keyword kk;
		kk.word=word;
		kk.parameters=to_string(parameter);
		kk.ParType=1;
		keywords.push_back(kk);
	}
	else
	{
		k->ParType=2;
		k->parameters=to_string(parameter);
	}
}
void TalysInput::RemoveKeyword(string word)
{
	for(unsigned int i=0;i<keywords.size();i++)
	{
		if(keywords[i].word==word)
		{
			keywords.erase (keywords.begin()+i);
		}
	}
}
void TalysInput::SetKeyword(string keyword,double parameter)
{
	Keyword *k=GetKeyword(word);
	if(!k)
	{
		Keyword kk;
		kk.word=word;
		kk.parameters=to_string(parameter);
		kk.ParType=2;
		keywords.push_back(kk);
	}
	else
	{
		k->ParType=2;
		k->parameters=to_string(parameter);
	}
}
void TalysInput::SetKeyword(string keyword,string parameter)
{
	Keyword *k=GetKeyword(word);
	if(!k)
	{
		Keyword kk;
		kk.word=word;
		kk.parameters=parameter;
		kk.ParType=3;
		keywords.push_back(kk);
	}
	else
	{
		k->ParType=3;
		k->parameters=parameter;
	}
}
string TalysInput::Get()
{
	string result;
	for(unsigned int i=0;i<keywords.size();i++)
	{
		result+=keywords[i].word+" "+keywords[i].parameters+"\n";
	}
	return result;
}
void TalysInput::Write()
{
	while(IsDirectoryAlreadyExsisted(PathToCalculation+to_string(ID)))
	{
		ID++;
	}
	PathToCalculation+=to_string(ID)
	mkdir((PathToCalculationDir).c_str(),S_IRWXU);
	ofstream ofs(PathToCalculation+"/input");
	ofs<<Get();
	if(fNucleus)
	{
		if(!fNucleus->fMotherNucleus)
		{
			if(!fNucleus->fMotherNucleus)
			{
				fNucleus->OMPManager_.WriteOMP(PathToCalculationDir+"/",WriteOMPOrUseKoningP,WriteOMPOrUseKoningN);
				ofs<<fNucleus->OMPManager_.GetAdditionToInputFile();
			}
			else
			{
				if(Reaction=="(n,p)")
				{
					WriteOMPOrUseKoningP=-1;//исправляет segfault в Talys из-за ОП для продукта реакции n,p
				}
				fNucleus->fMotherNucleus->OMPManager_.WriteOMP(PathToCalculationDir+"/",WriteOMPOrUseKoningP,WriteOMPOrUseKoningN);
				ofs<<fNucleus->fMotherNucleus->OMPManager_.GetAdditionToInputFile();
			}
			
			if(fNucleus->WriteDeformation)
			{
				ofs<<"deformfile "<<Z<<" "<<GetNucleusName(Z)<<".def\n";
				fNucleus->Def.WriteDeformation(PathToCalculationDir+"/"+GetNucleusName(Z)+".def");
			}
			if(!fNucleus->fMotherNucleus)
			{
				ofs<<addition;
			}
		}
	}
	ofs.close();
}
void TalysIO::AddInput(string Content, Nucleus *Nucl)
{
	TalysInput Inp;
	Inp.Set(Content);
	Inp.fNucleus=Nucl;
	InputDescriptions.push_back(Inp);
}

void CalculateInThread(TalysInput *inp,string *result)
{
	system(("cd "+inp->PathToCalculation+"; talys <input >output").c_str());
	ifstream ifs((inp->PathToCalculation+"/output").c_str());
	ifs.seekg(0, std::ios::end);
	size_t SizeOfStr = ifs.tellg();
	result->resize(SizeOfStr);
	ifs.seekg(0);
	ifs.read(result[0], SizeOfStr); 
	ifs.close();
	inp->Calculated=true;
}
void CalculateInThread2(unsigned int index, TalysIO *inp,vector<string> *result)
{
	if(inp->InputDescriptions.size()<index)
	{
		if(!inp->InputDescriptions[index].Calculated)
		{
			CalculateInThread(TalysInput *inp,string *result)
		}
	}
	return ;
}


void TalysIO::Calculate(int MaxNThreads)
{
	int NRuns=InputDescriptions.size()/MaxNThreads+1;
}

