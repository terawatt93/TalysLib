#include "../TalysLib.hh"
#include "../Parser.cpp"

#pragma once
void TalysInput::Set(string content)
{
	stringstream s(content);
	string line;
	while(getline(s,line))
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
void TalysInput::SetKeyword(string word,double parameter)
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
void TalysInput::SetKeyword(string word,string parameter)
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
	PathToCalculation+=to_string(ID);
	mkdir((PathToCalculation).c_str(),S_IRWXU);
	ofstream ofs(PathToCalculation+"/input");
	ofs<<Get();
	if(fNucleus)
	{
		if(!fNucleus->fMotherNucleus)
		{
			if(!fNucleus->fMotherNucleus)
			{
				fNucleus->OMPManager_.WriteOMP(PathToCalculation+"/",fNucleus->WriteOMPOrUseKoningP,fNucleus->WriteOMPOrUseKoningN);
				ofs<<fNucleus->OMPManager_.GetAdditionToInputFile();
			}
			else
			{
				if(fNucleus->Reaction=="(n,p)")
				{
					fNucleus->WriteOMPOrUseKoningP=-1;//исправляет segfault в Talys из-за ОП для продукта реакции n,p
				}
				fNucleus->fMotherNucleus->OMPManager_.WriteOMP(PathToCalculation+"/",fNucleus->WriteOMPOrUseKoningP,fNucleus->WriteOMPOrUseKoningN);
				ofs<<fNucleus->fMotherNucleus->OMPManager_.GetAdditionToInputFile();
			}
			
			if(fNucleus->WriteDeformation)
			{
				ofs<<"deformfile "<<fNucleus->Z<<" "<<GetNucleusName(fNucleus->Z)<<".def\n";
				fNucleus->Def.WriteDeformation(PathToCalculation+"/"+GetNucleusName(fNucleus->Z)+".def");
			}
			if(!fNucleus->fMotherNucleus)
			{
				ofs<<fNucleus->addition;
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
	inp->Calculated=true;
	inp->Write();
	system(("cd "+inp->PathToCalculation+"; talys <input >output").c_str());
	ifstream ifs((inp->PathToCalculation+"/output").c_str());
	ifs.seekg(0, std::ios::end);
	size_t SizeOfStr = ifs.tellg();
	result->resize(SizeOfStr);
	ifs.seekg(0);
	ifs.read(&((*result)[0]), SizeOfStr); 
	ifs.close();
}
void CalculateInThread2(unsigned int index, TalysIO *inp,vector<string> *result)
{
	if(inp->InputDescriptions.size()<index)
	{
		if(!inp->InputDescriptions[index].Calculated)
		{
			CalculateInThread(&(inp->InputDescriptions[index]),&(result->at(index)));
		}
		else
		{
			for(unsigned int i=0;i<inp->InputDescriptions.size();i++)
			{
				if(!inp->InputDescriptions[i].Calculated)
				{
					CalculateInThread2(i,inp,result);
				}
			}
		}
	}
	return ;
}


void TalysIO::Calculate(int MaxNThreads)
{
	vector<thread> threads;
	Outputs.resize(InputDescriptions.size());
	/*if((unsigned int)MaxNThreads>InputDescriptions.size())
	{
		MaxNThreads=InputDescriptions.size();
	}
	for(int i=0;i<MaxNThreads;i++)
	{
		threads.emplace_back(CalculateInThread2,i,this,&Outputs);
	}*/
	for(unsigned int i=0;i<InputDescriptions.size();i++)
	{
		//threads.emplace_back(CalculateInThread2,i,this,&Outputs);
		threads.emplace_back(CalculateInThread,&(InputDescriptions[i]),&(Outputs[i]));
	}
	for(unsigned int i=0;i<threads.size();i++)
	{
		threads[i].join();
	}
}

