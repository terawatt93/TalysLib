#include "../TalysLib.hh"
#pragma once

void TalysLibManager::SetAOption(string value)//управляет запросом данных с A=0
{
	AOption=value;
}
string TalysLibManager::GetAOption()//управляет запросом данных с A=0
{
	return AOption;
}

TalysLibManager& TalysLibManager::Instance()
{
	// согласно стандарту, этот код ленивый и потокобезопасный
	static TalysLibManager s;
	return s;
}
void TalysLibManager::SetEnableWarning(bool flag)
{
	EnableWarning=flag;
}
bool TalysLibManager::IsEnableWarning()
{
	return EnableWarning;
}
void TalysLibManager::Purge()
{
	system("rm -rf /dev/shm/CalculationResults*");
}
void TalysLibManager::DeleteExpDataForAuthor(string Author)
{
	ExcludeAuthors.push_back(Author);
}
bool TalysLibManager::IsInExcludeAuthors(string Author)
{
	for(unsigned int i=0;i<ExcludeAuthors.size();i++)
	{
		if(ExcludeAuthors[i].find(Author)!=string::npos)
		{
			return true;
		}
	}
	return false;
}
void TalysLibManager::SetC4Flag(bool flag)
{
	ReadC4=flag;
}
bool TalysLibManager::GetC4Flag()
{
	return ReadC4;
}
void TalysLibManager::SetEXFORSource(string Source)
{
	if(Source=="C4")
	{
		EXFORSource=1;
	}
	if(Source=="EXFORTABLES")
	{
		EXFORSource=0;
	}
}
int TalysLibManager::GetEXFORSource()
{
	return EXFORSource;
}
