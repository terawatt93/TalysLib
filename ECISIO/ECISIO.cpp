#include "ECISIO.hh"
#include "../Parser.cpp"

bool DetectFlag(string str)
{
	if(str.size()==0)
	{
		return false;
	}
	for(unsigned int i=0;i<str.size();i++)
	{
		if(!((str[i]=='T')||(str[i]=='F')))
		{
			return false;
		}
	}
	return true;
}

vector<int> FindStartsOfRecords(vector<string> &Buffer)
{
	vector<int> result;
	unsigned int PrevFlag=0;
	for(unsigned int i=0;i<Buffer.size();i++)
	{
		bool FlagSection=DetectFlag(Buffer[i]);

		if(FlagSection)
		{
			cout<<"I:"<<i<<" "<<Buffer[i]<<"\n";
			if(result.size()==0)
			{
				result.push_back(int(i)-1);
				PrevFlag=i;
			}
			else
			{
				if(PrevFlag+1<i)
				{
					result.push_back(i-1);
					PrevFlag=i;
				}
			}
		}
	}
	return result;
}

vector<ECISinput> ECISinput::ReadFromBuffer(string Buffer)
{
	vector<string> BufSplit=SplitString(Buffer,'\n');
	vector<int> Starts=FindStartsOfRecords(BufSplit); 
	vector<ECISinput> result;
	for(unsigned int i=0;i<Starts.size();i++)
	{
		ECISinput EI;
		int StrIterator=Starts[i];
		int MaxStrIterator=int(BufSplit.size())-2;
		if(i<Starts.size()-1)
		{
			MaxStrIterator=Starts[i+1]-1;
		}

		cout<<"MaxStrIterator:"<<MaxStrIterator<<"\n";
		int StrInBlockIterator=0;
		if(!DetectFlag(BufSplit[StrIterator]))
		{
			EI.title=BufSplit[StrIterator];
			StrInBlockIterator++;
			StrIterator++;
		}
		for(int i=0;i<50;i++)
		{
			if(BufSplit[StrIterator][i]=='T')
			{
				EI.ecis1.push_back(true);
			}
			else
			{
				EI.ecis1.push_back(false);
			}
			if(BufSplit[StrIterator+1][i]=='T')
			{
				EI.ecis2.push_back(true);
			}
			else
			{
				EI.ecis2.push_back(false);
			}
		}
		StrIterator+=2;
		vector<string> v1=FromFortranFormat(BufSplit[StrIterator],"(4i5)");
		EI.ncoll=atoi(v1[0].c_str());
		EI.njmax=atoi(v1[1].c_str());
		EI.iterm=atoi(v1[2].c_str());
		EI.npp=atoi(v1[3].c_str());
		StrIterator++;
		v1=FromFortranFormat(BufSplit[StrIterator],"(2f10.5)");
		EI.hint=atof(v1[0].c_str()); EI.rmatch=atof(v1[1].c_str());
		StrIterator++;
		if(BufSplit[StrIterator]=="")
		{
			EI.legendre=true;
			StrIterator++;
		}
		v1=FromFortranFormat(BufSplit[StrIterator],"(f5.2,2i2,a1,5f10.5)");
		EI.tarspin=atof(v1[0].c_str());//idvb пока не читаем
		EI.tarparity=atoi(v1[3].c_str());
		EI.e=atof(v1[4].c_str());
		EI.spin=atof(v1[5].c_str());
		EI.projmass=atof(v1[6].c_str());
		EI.resmass=atof(v1[7].c_str());
		EI.prodZ=atof(v1[8].c_str());
		StrIterator++;
		if(BufSplit[StrIterator].size()==0)
		{
			EI.vibrational=true;
			StrIterator++;
		}
		for(int i=0;i<EI.ncoll-1;i++)
		{
			v1=FromFortranFormat(BufSplit[StrIterator],"(f5.2,2i2,a1,5f10.5)");
			EI.Jlevel.push_back(atof(v1[0].c_str()));
			EI.Elevel.push_back(atof(v1[4].c_str()));
			if(v1[3]=="+")
			{
				EI.Plevel.push_back(1);
			}
			else
			{
				EI.Plevel.push_back(-1);
			}
			StrIterator++;
			if(EI.vibrational)
			{
				v1=FromFortranFormat(BufSplit[StrIterator],"(2i5)");
				EI.iph.push_back(atoi(v1[0].c_str()));
				EI.iband.push_back(atoi(v1[1].c_str()));
				StrIterator++;
			}
			else
			{
				v1=FromFortranFormat(BufSplit[StrIterator],"(2i5)");
				EI.iph.push_back(atoi(v1[0].c_str()));
				EI.iband.push_back(atoi(v1[1].c_str()));
				StrIterator++;
				if(BufSplit[StrIterator].size()==0)
				{
					StrIterator++;
				}
			}
		}
		//проверим, что используется ДОМ:
		for(int j=StrIterator;j<MaxStrIterator;j++)
		{
			if(BufSplit[j].find("          ")!=string::npos)
			{
				EI.disp=true;
			}
		}
		//и пока не будем с ним возиться!
		//А теперь изврат! читаем в обратном порядке
		v1=FromFortranFormat(BufSplit[MaxStrIterator],"(3f10.5)");
		EI.angbeg=atof(v1[0].c_str()); EI.anginc=atof(v1[1].c_str()); EI.angend=atof(v1[2].c_str());
		MaxStrIterator-=2;
		v1=FromFortranFormat(BufSplit[MaxStrIterator],"(3f10.5)");
		EI.rc=atof(v1[0].c_str());
		MaxStrIterator--;
		v1=FromFortranFormat(BufSplit[MaxStrIterator],"(3f10.5)"); //1
		EI.wso=atof(v1[0].c_str()); EI.rwso=atof(v1[1].c_str());  EI.awso=atof(v1[2].c_str()); 
		MaxStrIterator--;
		v1=FromFortranFormat(BufSplit[MaxStrIterator],"(3f10.5)");//2
		MaxStrIterator--;
		EI.vso=atof(v1[0].c_str()); EI.rvso=atof(v1[1].c_str());  EI.avso=atof(v1[2].c_str()); 
		v1=FromFortranFormat(BufSplit[MaxStrIterator],"(3f10.5)");//3
		MaxStrIterator--;
		EI.wd=atof(v1[0].c_str()); EI.rwd=atof(v1[1].c_str());  EI.awd=atof(v1[2].c_str()); 
		v1=FromFortranFormat(BufSplit[MaxStrIterator],"(3f10.5)");//4
		MaxStrIterator--;
		EI.vd=atof(v1[0].c_str()); EI.rvd=atof(v1[1].c_str());  EI.avd=atof(v1[2].c_str()); 
		v1=FromFortranFormat(BufSplit[MaxStrIterator],"(3f10.5)");//5
		MaxStrIterator--;
		EI.w=atof(v1[0].c_str()); EI.rw=atof(v1[1].c_str());  EI.aw=atof(v1[2].c_str()); 
		v1=FromFortranFormat(BufSplit[MaxStrIterator],"(3f10.5)");//6
		MaxStrIterator--;
		EI.v=atof(v1[0].c_str()); EI.rv=atof(v1[1].c_str());  EI.av=atof(v1[2].c_str());
		result.push_back(EI);
		//=atof(v1[7].c_str());

	}
	return result;
}
vector<ECISinput> ECISinput::ReadFromFile(string Filename)
{
	ifstream ifs(Filename);
	string Buf;
	CopyFileContentToBuffer(ifs,Buf);
	return ReadFromBuffer(Buf);
}
