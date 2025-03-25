#pragma once
#include "../TalysLib.hh"

class JSONLikeData
{
	public:
	map<string,string> Content;
}

class YAML
{
	public:
	string Projectile, OutgoingParticle;
	string ReactionType, Quantity;
	double Q=0, Threshold=0;
	int LevelNumber=0;
	int NColumns=0, NRows=0;
	bool WithEDep=false;
	vector<string> Headers, Dimensions;
	vector<vector<float> > Content;
	void ParseYAML(string Content);
	void ParseReaction();
	string Reaction;
};

vector<YAML> ExtractYAMLFromString(string &FileContent);
void AssignDataToLevels(Nucleus *Parent,string &FileContent);
