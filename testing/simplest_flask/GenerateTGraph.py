import ROOT

def GenerateTGraph(TGraph):
	result='<body>\n<div id="object_draw" style="width: 1200px; height:800px"></div>\n</body>'
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
	result+="let graph1 = createTGraph({}, x, y);\ngraph1.fLineColor = 2;\ngraph1.fTitle=\"{}\"\nredraw('object_draw', graph1, \"al\");".format(TGraph.GetN(),TGraph.GetTitle())
	result+="</script>"
	return result

Fe=ROOT.Nucleus("56Fe")
Fe.GenerateProducts()
result=GenerateTGraph(Fe.Products[0].Levels[1].GetAngularDistribution())
print(result)
