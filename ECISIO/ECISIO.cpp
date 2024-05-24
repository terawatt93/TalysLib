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
		cout<<"Start["<<i<<"]: "<<Starts[i]<<"\n";
		ECISinput EI;
		int StrIterator=Starts[i];
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
