#include "EXFOR.hh"

int GetCodeIDForNucl(string Projectile, int Z, int A)
{
	int result=0;
	result=Z*1000+A;
	if(Projectile=="n")
	{
		result+=1e6;
	}
	if(Projectile=="p")
	{
		result+=2e6;
	}
	if(Projectile=="d")
	{
		result+=3e6;
	}
	if(Projectile=="t")
	{
		result+=4e6;
	}
	if(Projectile=="a")
	{
		result+=5e6;
	}
	if(Projectile=="h")
	{
		result+=6e6;
	}
	if(Projectile=="i")
	{
		result+=7e6;
	}
	return result;
}
EXFORTable LoadEXFORTable(string Filename)
{
	string Link;
	string OutputFileName="/dev/shm/"+Filename.substr(Filename.find_last_of("/\\") + 1);
	Link="http://159.93.100.133:85/exfortables/"+Filename;
	cout<<"OutputFileName:"<<"wget --user-agent=\"Mozilla/5.0 (Windows NT 10.0; WOW64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/51.0.2704.103 Safari/537.36\" -O "+OutputFileName+" "+Link<<"\n";
	system(("wget --user-agent=\"Mozilla/5.0 (Windows NT 10.0; WOW64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/51.0.2704.103 Safari/537.36\" -O "+OutputFileName+" "+Link).c_str());
	EXFORTable t;
	t.Read(OutputFileName);
	system(("rm "+OutputFileName).c_str());
	return t;
}

/*int GetAdditionIndex(string Projectile,string OutgoingParticle,int LevelNum)
{
	if(Projectile==OutgoingParticle)
	{
		if(LevelNum==0)
		{
			return 2;
		}
	}
	if(OutgoingParticle=="n")
	{
		return 50+LevelNum;
	}
	else if(OutgoingParticle=="p")
	{
		return 600+LevelNum;
	}
	else if(OutgoingParticle=="d")
	{
		return 650+LevelNum;
	}
	else if(OutgoingParticle=="t")
	{
		return 700+LevelNum;
	}
	else if(OutgoingParticle=="3He")
	{
		return 750+LevelNum;
	}
	else if(OutgoingParticle=="a")
	{
		return 800+LevelNum;
	}
	return 0;
}*/


vector<EXFORTable> EXFORManager::GetEXFORAngularDistributions(string Projectile, int Z, int A,string OutgoingParticle,int LevelNum)
{
	vector<EXFORTable> result;
	string PathToDictonaries=getenv("TALYSLIBDIR");
	PathToDictonaries+="/ENDFReader/";
	ifstream ifs(PathToDictonaries+"FileList.txt");
	string line;
	int Index=GetCodeIDForNucl(Projectile,Z,A);
	int MT=GetAdditionIndex(Projectile,OutgoingParticle,LevelNum);
	while(getline(ifs,line))
	{
		stringstream s(line);
		int index_tmp;
		s>>index_tmp;
		if(Index==index_tmp)
		{
			EXFORTable table;
			string FName;
			s>>table.MF>>table.MT>>table.ProjectileEnergy>>table.ExcitationEnergy>>table.Emin>>table.Emax>>table.Quantity>>FName;
			if((table.Quantity=="Angular")&&(MT==table.MT))
			{
				//table=LoadEXFORTable(FName);
				result.push_back(LoadEXFORTable(FName));
			}
		}
	}
	return result;
}
vector<EXFORTable> EXFORManager::GetEXFORCrossSections(string Projectile, int Z, int A,string OutgoingParticle,int LevelNum)
{
	vector<EXFORTable> result;
	string PathToDictonaries=getenv("TALYSLIBDIR");
	PathToDictonaries+="/ENDFReader/";
	ifstream ifs(PathToDictonaries+"FileList.txt");
	string line;
	int Index=GetCodeIDForNucl(Projectile,Z,A);
	int MT=GetAdditionIndex(Projectile,OutgoingParticle,LevelNum);
	while(getline(ifs,line))
	{
		stringstream s(line);
		int index_tmp;
		s>>index_tmp;
		if(Index==index_tmp)
		{
			EXFORTable table;
			string FName;
			s>>table.MF>>table.MT>>table.ProjectileEnergy>>table.ExcitationEnergy>>table.Emin>>table.Emax>>table.Quantity>>FName;
			if((table.Quantity=="Cross")&&(MT==table.MT))
			{
				result.push_back(LoadEXFORTable(FName));
			}
		}
	}
	return result;
}
inline string GetSubstrAfterColon(string s)
{
	return s.substr(s.find_last_of(":") + 1);
}
inline string GetEXFORTableField(string s)
{
	s=s.substr(s.find_last_of(":") + 1);
	stringstream ss(s);
	ss>>s;
	return s;
}
int EXFORTable::GetCodeID()
{
	return GetCodeIDForNucl(Projectile,Z,A);
}
bool EXFORTable::Read(string filename)
{
	ifstream ifs(filename);
	string line;
	int DataBlockIterator=-1;
	while(getline(ifs,line))//line.substr(line.find_last_of("/\\") + 1);
	{
		if(line.find("# Target Z")!=string::npos)
		{
			Z=atoi(GetSubstrAfterColon(line).c_str());
		}
		if(line.find("# Target A")!=string::npos)
		{
			A=atoi(GetSubstrAfterColon(line).c_str());
		}
		if(line.find("# MF")!=string::npos)
		{
			MF=atoi(GetSubstrAfterColon(line).c_str());
		}
		if(line.find("# MT")!=string::npos)
		{
			MT=atoi(GetSubstrAfterColon(line).c_str());
		}
		if(line.find("# Year")!=string::npos)
		{
			Year=atoi(GetSubstrAfterColon(line).c_str());
		}
		if(line.find("# X4 ID")!=string::npos)
		{
			X4ID=GetEXFORTableField(line);
		}
		if((line.find("# Reaction")!=string::npos)&&(Reaction.size()==0))
		{
			Reaction=GetEXFORTableField(line);
		}
		if(line.find("# Author")!=string::npos)
		{
			Author=GetEXFORTableField(line);
		}
		if(line.find("# Projectile")!=string::npos)
		{
			Projectile=GetEXFORTableField(line);
		}
		if(line.find("# Quantity")!=string::npos)
		{
			Quantity=GetEXFORTableField(line);
		}
		if(line.find("# E-inc")!=string::npos)
		{
			ProjectileEnergy=atof(GetSubstrAfterColon(line).c_str());
		}
		if(line.find("# E-exc")!=string::npos)
		{
			TString ts(line.c_str());
			ts.ReplaceAll("# E-exc       :","");
			ts.ReplaceAll("MeV (EXFOR:","");
			ts.ReplaceAll(")","");
			stringstream sstr(ts.Data());
			sstr>>ExcitationEnergy>>ExcitationEnergy_EXFOR;
			//ExcitationEnergy=atof(GetEXFORTableField(line).c_str());
		}
		if(line.find("# Data points")!=string::npos)
		{
			DataBlockIterator=0;
			getline(ifs,line);
			stringstream s(line);
			string tmp;
			s>>tmp>>HeadX>>HeadY;
		}
		if((line.find("#")==string::npos)&&(DataBlockIterator==0))
		{
			double X=0,Y=0,XErr=0,YErr=0;
			if(Table.size()<4)
			{
				Table.resize(4);
			}
			stringstream s(line);
			s>>X>>Y>>YErr>>XErr;
			if(Quantity.find("Cross")!=string::npos)
			{
				if(Emin==0)
				{
					Emin=X;
				}
				if(Emax<X)
				{
					Emax=X;
				}
			}
			Table[0].push_back(X);
			Table[1].push_back(XErr);
			Table[2].push_back(Y);
			Table[3].push_back(YErr);
		}
		else if(Table.size()==4)
		{
			DataBlockIterator=1;
		}
	}
	if(Table.size()!=4)
	{
		return false;
	}
	return true;
}
vector<double> EXFORTable::GetX()
{
	vector<double> result;
	if(Table.size()<4)
	{
		return result;
	}
	return Table[0];
}
vector<double> EXFORTable::GetY()
{
	vector<double> result;
	if(Table.size()<4)
	{
		return result;
	}
	return Table[2];
}
vector<double> EXFORTable::GetXErr()
{
	vector<double> result;
	if(Table.size()<4)
	{
		return result;
	}
	return Table[1];
}
vector<double> EXFORTable::GetYErr()
{
	vector<double> result;
	if(Table.size()<4)
	{
		return result;
	}
	return Table[3];
}
TGraphErrors* EXFORTable::GetTGraph()
{
	if(Table.size()<4)
	{
		return 0;
	}
	if(Graph.GetN()>0)
	{
		return &Graph;
	}
	Graph=TGraphErrors(Table[0].size(),&Table[0][0],&Table[2][0],&Table[1][0],&Table[3][0]);
	Graph.SetName(TString::Format("MF_%d_MT_%d_%s",MF,MT,Author.c_str()));
	Graph.SetTitle(TString::Format("%s(%d);%s;%s",Author.c_str(),Year,HeadX.c_str(),HeadY.c_str()));
	return &Graph;
}
