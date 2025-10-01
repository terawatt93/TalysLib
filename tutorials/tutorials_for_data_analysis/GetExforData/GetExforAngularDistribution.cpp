#include "TalysLib.hh"

template <typename T> void PrintVec(vector<T> &vec)
{
	cout<<"vec_size: "<<vec.size()<<"\n";
	for(unsigned int i=0;i<vec.size();i++)
	{
		cout<<i<<" "<<vec[i]<<"\n"; 
	}
}

void GetExforAngularDistribution()
{
	//TalysLibManager::Instance().ExcludeSubEntries = {"22188046"};
	TalysLibManager::Instance().ReadC5 = true;
	Nucleus Nucl("12C");
    Nucl.GenerateProducts();
    Nucl.c5_manager.AssignC5ToLevel(10); 
    TCanvas c;
    c.Print("AngularDistribution.pdf[","pdf");
    for(unsigned int i=0;i<4;i++)
    {
		Level *l=&(Nucl.FindProductByReaction("(n,n')")->Levels[i]);
		for(unsigned int j=0;j<l->Gammas.size();j++)
		{
			vector<AngularDistribution*> ad_vec =l->Gammas[j].GetAngularDistribution(12,15);
			for(unsigned int p=0;p<ad_vec.size();p++)
			{
				ad_vec[p]->graph.SetTitle(ad_vec[p]->fSubent->fEntry->EntryID.c_str());
				ad_vec[p]->graph.Draw("ap");
				cout<<"Entry: "<<ad_vec[p]->fSubent->fEntry->EntryID<<"\n";
				PrintVec(ad_vec[p]->fSubent->fEntry->DOI);
				PrintVec(ad_vec[p]->fSubent->fEntry->Authors);
				c.Print("AngularDistribution.pdf","pdf");
			}
		}
	}
	c.Print("AngularDistribution.pdf]","pdf");
}
