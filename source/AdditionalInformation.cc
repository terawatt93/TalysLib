#include "../TalysLib.hh"

/*double& AdditionalInformationContainer::operator() (string Key)
{
	return AdditionalInformationMap[Key];
}*/
void AdditionalInformationContainer::AddInformation(string key,double value)
{
	DataContainer[key]=value;
}
void AdditionalInformationContainer::AddInformation(string key,int value)
{
	DataContainer[key]=value;
}
void AdditionalInformationContainer::AddInformation(string key,string value)
{
	DataContainer[key]=value;
}
double AdditionalInformationContainer::GetInformationD(string key)
{
	return DataContainer[key];
}
string AdditionalInformationContainer::GetInformationS(string key)
{
	return DataContainer[key];
}
int AdditionalInformationContainer::GetInformationI(string key)
{
	return DataContainer[key];
}
