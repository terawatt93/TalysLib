import ROOT
import json
ROOT.TalysLibManager.GetPointer().SetEnableWarning(False)#отключаем warning
Mat=ROOT.TLMaterial("TiO2")
for i in range(0,len(Mat.Nuclides)):
	Mat.Nuclides[i].GenerateEnergyGrid(0.1,0.2,15)
	Mat.Nuclides[i].GenerateProducts()
	
Transitions=Mat.GetGammaTransitions()
#Nucleus=ROOT.Nucleus("48Ti")#создаем ядро Ti-48
#есть несколько способов задать сетку по энергии: 1) GenerateEnergyGrid(Min,Step,Max) 2) SetEnergyGrid([])
#Nucleus.GenerateEnergyGrid(0.1,0.2,15)#сетка от 0,1 до 15 МэВ с шагом 0,5 МэВ
#Nucleus.GenerateProducts()#выполняем расчеты
#Transitions=Nucleus.GetGammaTransitions()
OutputFile=ROOT.TFile("GammaCrossSections.root","recreate")
OutputDict={}
it=0
for gt in Transitions:
	dataDict={}
	Graph=gt.GetCSGraph()
	Graph.SetName("CS_%d" % it)
	E=gt.Energy
	Init=gt.fLevel.fNucleus.fMotherNucleus.Name
	Final=gt.fLevel.fNucleus.Name
	Reaction=gt.fLevel.fNucleus.Reaction
	InitLev=gt.fLevel.Energy
	FinalLev=gt.fFinalLevel.Energy
	InitLevJP=gt.fLevel.TalysJP.J*gt.fLevel.TalysJP.Parity
	FinalLevJP=gt.fFinalLevel.TalysJP.J*gt.fFinalLevel.TalysJP.Parity
	Abundance=gt.fLevel.fNucleus.fMotherNucleus.Abundance
	dataDict["E"]=E
	dataDict["Reaction"]=Reaction
	dataDict["Init"]=Init
	dataDict["Final"]=Final
	dataDict["InitLevel"]=InitLev
	dataDict["FinalLevel"]=FinalLev
	dataDict["InitLevelJP"]=InitLevJP
	dataDict["FinalLevelJP"]=FinalLevJP
	dataDict["Abundance"]=Abundance
	OutputDict[it]=dict(dataDict)
	OutputFile.WriteTObject(Graph)
	print("Writing transition %.1f" % E)
	it=it+1
InfoStr=json.dumps(OutputDict)
InfoStr=ROOT.TString(InfoStr)
OutputFile.WriteObject(InfoStr,"Info")
OutputFile.Close()


