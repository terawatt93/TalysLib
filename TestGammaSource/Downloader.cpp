void Downloader()
{
	ifstream ifs("links.txt");
	string line;
	TRandom R;
	while(getline(ifs,line))
	{
		if(line.size()>5)
		{
			gSystem->Exec(("wget "+line).c_str());
			int NSleep=R.Uniform(1,40);
			cout<<"Sleep for "<<NSleep<<"\n";
			sleep(NSleep);
		}
	}
}
