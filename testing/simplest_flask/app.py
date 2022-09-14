from flask import Flask, request, render_template
import os
import ROOT


NuclName=""
Projectile=""
PrEnergy=0
OutputContent=''

def GenerateGammaTable(GammaTransitions):
	Table='<script src="https://polyfill.io/v3/polyfill.min.js?features=es6"></script><script id="MathJax-script" async src="https://cdn.jsdelivr.net/npm/mathjax@3/es5/tex-mml-chtml.js"></script>'
	Table+='<table border="1"> \n <caption>γ-переходы</caption> \n  <tr> \n <th>Энергия, кэВ</th><th>Реакция</th><th>Уровни</th><th>Сечение, мб</th>\n </tr>'
	for x in GammaTransitions:
		#print(x.fLevel.fNucleus.ReactionInTLatexFormat())
		Table+='<tr><td>'+str(round(x.Energy,2))+'</td><td>$$'+str(x.fLevel.fNucleus.ReactionInTLatexFormat()).replace('#','\\')+'$$</td><td>'+x.GetLine("custom LEV")+'</td><td>'+str(round(x.TalysCrossSection,2))+'</th>\n </tr>'
	return Table

def GenerateTGraph(TGraph,ID):
	result='<body>\n<div id="object_draw{}" style="width: 500px; height:500px"></div>\n</body>'.format(ID)
	result+="<script type='module'>\n import {createTGraph, redraw } from 'https://root.cern/js/latest/modules/main.mjs';\n"
	result+="let x=["
	i=0
	while i<TGraph.GetN():
		result+=str(TGraph.GetPointX(i))
		if i < TGraph.GetN()-1:
			result+=","
		i+=1
	result+="];\nlet y=["
	i=0
	while i<TGraph.GetN():
		result+=str(TGraph.GetPointY(i))
		if i < TGraph.GetN()-1:
			result+=","
		i+=1
	result+="];\n"
	result+="let graph1 = createTGraph({}, x, y);\ngraph1.fLineColor = 2;\ngraph1.fTitle=\"{}\"\nredraw('object_draw{}', graph1, \"al\");".format(TGraph.GetN(),TGraph.GetTitle(),ID)
	result+="</script>\n"
	return result
	
def GenerateResultTable(Nucleus):
	Table='<script src="https://polyfill.io/v3/polyfill.min.js?features=es6"></script><script id="MathJax-script" async src="https://cdn.jsdelivr.net/npm/mathjax@3/es5/tex-mml-chtml.js"></script>'
	Table+='<table border="1"> \n <caption>Уровни ядер-продуктов</caption> \n  <tr> \n <th>Энергия, кэВ</th><th>Реакция</th><th>$$J^P$$</th><th>Сечение возбуждения, мб</th><th>Угловое распределение рассеянных частиц</th><th>Гамма-переходы</th>\n </tr>\n'
	ID=0
	for Product in Nucleus.Products:
		for Level in Product.Levels:
			if Level.GetAngularDistribution().GetN() > 0:
				NGamma=Level.Gammas.size()+1
				Table+='<tr>\n<td rowspan="{}" > <a name="{}"></a>'.format(NGamma,str(Level.Energy))+str(round(Level.Energy,2))+'</td><td rowspan="{}">$$'.format(NGamma)+str(Level.fNucleus.ReactionInTLatexFormat()).replace('#','\\')+'$$</td><td rowspan="{}">$$'.format(NGamma)+str(Level.TalysJP.GetTLatex())+'$$</td><td rowspan="{}">'.format(NGamma)+str(round(Level.TalysCS,2))+'</td><td rowspan="{}">'.format(NGamma)
				Table+=GenerateTGraph(Level.GetAngularDistribution(),ID)
				ID+=1
				if NGamma==0:
					Table+='</td><td> </td></tr>'
				else:
					Table+='</td></tr>'
					for Gamma in Level.Gammas:
						Table+='<tr>\n<td>'+str(round(Gamma.Energy,2))+' ('+str(round(Gamma.TalysCrossSection,2))+' мб) на уровень <a href="#{}">{} кэВ</a> </td></tr>'.format(str(Gamma.fFinalLevel.Energy),str(round(Gamma.fFinalLevel.Energy,2)))
			#Table+='</td>\n </tr>'
	GT=Nucleus.GetGammaTransitions()
	Table+='\n'+GenerateGammaTable(GT)
	return Table

# create the Flask app
app = Flask(__name__)

@app.route('/', methods=['GET', 'POST'])

def form_example():
	# handle the POST request
	
	global NuclName
	global Projectile
	global PrEnergy
	global OutputContent
	
	Nucleus=ROOT.Nucleus(NuclName)
	Nucleus.SetProjectileEnergy(float(PrEnergy))
	if request.method == 'POST':
		if request.form.get('nucleus'):
			NuclNameL = request.form.get('nucleus')
			ProjectileL = request.form.get('projectile')
			PrEnergyL = request.form.get('prEnergy')
			#максимально тупо, потом переделать
			if (len(NuclNameL)>0) and (len(ProjectileL)>0) and (len(PrEnergyL)>0):
				NuclName=NuclNameL
				Projectile=ProjectileL
				PrEnergy=PrEnergyL
				Nucleus=ROOT.Nucleus(NuclName)
				Nucleus.SetProjectileEnergy(float(PrEnergy))
			
			
		if 'submitPar' in request.form:
			Nucleus.GenerateProducts(Projectile)
			OutputContent=''
			f = open(Nucleus.PathToCalculationDir+'/'+Nucleus.Name+str(Nucleus.ID)+'/output','r',newline='')
			for x in f:
				OutputContent+=x+'</br>'
			#print(OutputContent)
		if 'OMP' in request.form:
			return render_template('OMP.html',nucleus=Nucleus.Name,v1n=Nucleus.OMPN.Getv1(),v2n=Nucleus.OMPN.Getv2(),v3n=Nucleus.OMPN.Getv3(),w1n=Nucleus.OMPN.Getw1(),w2n=Nucleus.OMPN.Getw2(),d1n=Nucleus.OMPN.Getd1(),d2n=Nucleus.OMPN.Getd2(),d3n=Nucleus.OMPN.Getd3(),vso1n=Nucleus.OMPN.Getvso1(),vso2n=Nucleus.OMPN.Getvso2(),wso1n=Nucleus.OMPN.Getwso1(),wso2n=Nucleus.OMPN.Getwso2(),v1p=Nucleus.OMPP.Getv1(),v2p=Nucleus.OMPP.Getv2(),v3p=Nucleus.OMPP.Getv3(),w1p=Nucleus.OMPP.Getw1(),w2p=Nucleus.OMPP.Getw2(),d1p=Nucleus.OMPP.Getd1(),d2p=Nucleus.OMPP.Getd2(),d3p=Nucleus.OMPP.Getd3(),vso1p=Nucleus.OMPP.Getvso1(),vso2p=Nucleus.OMPP.Getvso2(),wso1p=Nucleus.OMPP.Getwso1(),wso2p=Nucleus.OMPP.Getwso2())
		if 'submitOMP' in request.form:
			Nucleus.OMPN.Setv1(float(request.form.get('v1n')))
			Nucleus.OMPN.Setv2(float(request.form.get('v2n')))
			Nucleus.OMPN.Setv3(float(request.form.get('v3n')))
			Nucleus.OMPN.Setw1(float(request.form.get('w1n')))
			Nucleus.OMPN.Setw2(float(request.form.get('w2n')))
			Nucleus.OMPN.Setd1(float(request.form.get('d1n')))
			Nucleus.OMPN.Setd2(float(request.form.get('d2n')))
			Nucleus.OMPN.Setd3(float(request.form.get('d3n')))
			Nucleus.OMPN.Setvso1(float(request.form.get('vso1n')))
			Nucleus.OMPN.Setvso2(float(request.form.get('vso2n')))
			Nucleus.OMPN.Setwso1(float(request.form.get('wso1n')))
			Nucleus.OMPN.Setwso2(float(request.form.get('wso2n')))
			
			Nucleus.OMPP.Setv1(float(request.form.get('v1p')))
			Nucleus.OMPP.Setv2(float(request.form.get('v2p')))
			Nucleus.OMPP.Setv3(float(request.form.get('v3p')))
			Nucleus.OMPP.Setw1(float(request.form.get('w1p')))
			Nucleus.OMPP.Setw2(float(request.form.get('w2p')))
			Nucleus.OMPP.Setd1(float(request.form.get('d1p')))
			Nucleus.OMPP.Setd2(float(request.form.get('d2p')))
			Nucleus.OMPP.Setd3(float(request.form.get('d3p')))
			Nucleus.OMPP.Setvso1(float(request.form.get('vso1p')))
			Nucleus.OMPP.Setvso2(float(request.form.get('vso2p')))
			Nucleus.OMPP.Setwso1(float(request.form.get('wso1p')))
			Nucleus.OMPP.Setwso2(float(request.form.get('wso2p')))
			
			Nucleus.SetOMPOption("n",1)
			Nucleus.SetOMPOption("p",1)
			Nucleus.GenerateProducts(Projectile)
		if 'Back' in request.form:
			return render_template('index.html')
		if 'DownloadOutput' in request.form:
			return render_template('Output.html',result=OutputContent)
		#return render_template('ResultGamma.html',result=GenerateGammaTable(GT))
		# GraphAddition='<table>\n'
		# ID=0
		# for Product in Nucleus.Products:
			# for Level in Product.Levels:
				# if Level.GetAngularDistribution().GetN() > 0:
					# GraphAddition+='<tr>\n<td>Уровень</td><td>\n'+GenerateTGraph(Level.GetAngularDistribution(),ID)+'</tr>\n</td>\n'
					# ID+=1
		# GraphAddition+='</table>\n'
		# print(render_template('ResultGamma.html',result=GraphAddition))
		return render_template('ResultGamma.html',result=GenerateResultTable(Nucleus))
		
    # otherwise handle the GET request
    
	return render_template('index.html')

@app.route('/output')
def SendOutput():
	f = open('output')
	return f.read()

if __name__ == '__main__':
    # run app in debug mode on port 5000
    app.run(host="0.0.0.0",debug=False, port=81)


