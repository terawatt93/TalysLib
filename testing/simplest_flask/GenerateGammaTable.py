import ROOT

def GenerateGammaTable(GammaTransitions):
	Table='<script src="https://polyfill.io/v3/polyfill.min.js?features=es6"></script><script id="MathJax-script" async src="https://cdn.jsdelivr.net/npm/mathjax@3/es5/tex-mml-chtml.js"></script>'
	Table+='<table border="1"> \n <caption>Гамма-переходы</caption> \n  <tr> \n <th>Энергия</th><th>Реакция</th><th>Уровни</th><th>Сечение, мб</th>\n </tr>'
	for x in GammaTransitions:
		print(x.fLevel.fNucleus.ReactionInTLatexFormat())
		Table+='<tr><td>'+str(round(x.Energy,2))+'</td><td>$$'+str(x.fLevel.fNucleus.ReactionInTLatexFormat())+'$$</td><td>'+x.GetLine("custom LEV")+'</td><td>'+str(round(x.TalysCrossSection,2))+'</th>\n </tr>'
	return Table

Fe=ROOT.Nucleus("56Fe")
Fe.GenerateProducts()
GT=Fe.GetGammaTransitions()
Table=GenerateGammaTable(GT)
print(Table)
