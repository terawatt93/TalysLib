#include "../TalysLib.hh"
#pragma once
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
