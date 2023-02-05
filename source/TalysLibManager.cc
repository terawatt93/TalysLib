#include "../TalysLib.hh"
#pragma once

bool TalysLibManager::ThereAreIncludedSubentries()//проверка, что есть "белый" список SubEntry
{
	if(IncludeSubEntries.size()>0)
	{
		return true;
	}
	return false;
}
bool TalysLibManager::ThereAreIncludedAuthors()//проверка, что есть "белый" список авторов
{
	if(IncludeAuthors.size()>0)
	{
		return true;
	}
	return false;
}
bool TalysLibManager::IsInIncludedAuthors(string Author)//проверка автора на наличие в списке Included
{
	for(unsigned int i=0;i<IncludeAuthors.size();i++)
	{
		if(IncludeAuthors[i]==Author)
		{
			return true;
		}
	}
	return false;
}
void TalysLibManager::AddAuthorToIncludeList(string Author)//добавить автора в список Included
{
	for(unsigned int i=0;i<IncludeAuthors.size();i++)
	{
		if(IncludeAuthors[i]==Author)
		{
			return;
		}
	}
	IncludeAuthors.push_back(Author);
}
bool TalysLibManager::IsInIncludedSubEntries(string SubEntry)//проверка SubEntry на наличие в списке Included
{
	for(unsigned int i=0;i<IncludeSubEntries.size();i++)
	{
		if(IncludeSubEntries[i]==SubEntry)
		{
			return true;
		}
	}
	return false;
}
void TalysLibManager::AddSubentryToIncludeList(string SubEntry)//добавить SubEntry в список используемых
{
	for(unsigned int i=0;i<IncludeSubEntries.size();i++)
	{
		if(IncludeSubEntries[i]==SubEntry)
		{
			return;
		}
	}
	IncludeSubEntries.push_back(SubEntry);

}
bool TalysLibManager::IsInExcludedAuthors(string Author)//проверка автора
{
	for(unsigned int i=0;i<ExcludeAuthors.size();i++)
	{
		if(ExcludeAuthors[i]==Author)
		{
			return true;
		}
	}
	return false;
}
void TalysLibManager::AddAuthorToExcludeList(string Author)//добавить автора в список исключений
{
	for(unsigned int i=0;i<ExcludeAuthors.size();i++)
	{
		if(ExcludeAuthors[i]==Author)
		{
			return;
		}
	}
	ExcludeAuthors.push_back(Author);
}

bool TalysLibManager::IsInExcludedSubEntries(string SubEntry)//проверка SubEntry
{
	for(unsigned int i=0;i<ExcludeSubEntries.size();i++)
	{
		if(ExcludeSubEntries[i]==SubEntry)
		{
			return true;
		}
	}
	return false;
}
void TalysLibManager::AddSubentryToExcludeList(string SubEntry)//добавить SubEntry в список исключений
{
	for(unsigned int i=0;i<ExcludeSubEntries.size();i++)
	{
		if(ExcludeSubEntries[i]==SubEntry)
		{
			return;
		}
	}
	ExcludeSubEntries.push_back(SubEntry);
}

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
	//Pointer=&s;
	return s;
}

TalysLibManager* TalysLibManager::GetPointer()
{
	return &(Instance());
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
/*void TalysLibManager::AddAuthorToExcludeList(string Author)
{
	ExcludeAuthors.push_back(Author);
}
bool TalysLibManager::IsInExcludedAuthors(string Author)
{
	for(unsigned int i=0;i<ExcludeAuthors.size();i++)
	{
		if(ExcludeAuthors[i].find(Author)!=string::npos)
		{
			return true;
		}
	}
	return false;
}*/
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
