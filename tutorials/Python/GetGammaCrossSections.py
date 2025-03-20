import ROOT
ROOT.TalysLibManager.GetPointer().SetEnableWarning(False)#отключаем warning
Nucleus=ROOT.Nucleus("48Ti")#создаем ядро Ti-48
#есть несколько способов задать сетку по энергии: 1) GenerateEnergyGrid(Min,Step,Max) 2) SetEnergyGrid([])
Nucleus.GenerateEnergyGrid(0.1,0.5,15)#сетка от 0,1 до 15 МэВ с шагом 0,5 МэВ
Nucleus.GenerateProducts()#выполняем расчеты
GammaTransition=Nucleus.GetBestTransition(983.5)#найти гамма-переход по энергии
Graph=GammaTransition.GetCSGraph()#получаем TGraph с энергетической зависимостью сечений
CS=Graph.Eval(13.5,0,"S")#получаем величину сечения в мб для энергии нейтрона 13.5 МэВ
print("Cross-section %.1f" % CS)

#нарисуем график
canvas=ROOT.TCanvas()
Graph.Draw()
canvas.Print("CS.pdf","pdf")

