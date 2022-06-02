#include "../TalysLib.hh"

double& AdditionalInformationContainer::operator() (string Key)
{
	return AdditionalInformationMap[Key];
}
