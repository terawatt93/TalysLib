#include "TalysLib.hh"

void ReadENDF()
{
	ENDFFile f;
	f.Read("n_0625_6-C-12.zip");
	ENDFTable* t=f.FindENDFTable(4,51);
	cout<<t->GetRawTable()<<"\n";//напечатать содержимое таблицы в "сыром" виде
	cout<<"ZA="<<t->Header.at(0,0)<<" LTT="<<t->Header.at(3,0)<<" LI="<<t->Header.at(2,1)<<"\n";
}
