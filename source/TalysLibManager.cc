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
