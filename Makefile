CXX = `root-config --cxx`
CXXFLAGS = `root-config --cflags` -fPIC -g
ROOTLIBS = `root-config --glibs`
SHARED = -shared
SRCS = LevelsDict.cxx Levels.cc
HDRS = LevelsLinkDef.h Levels.hh

PROGRAM = Levels.so

all: $(PROGRAM)

LevelsDict.cxx: $(HDRS) LevelsLinkDef.h
	@echo "Generating dictionary ..."
	#@rootcint -f $@ -c -p $^
	@rootcling -f LevelsDict.cxx -rml Levels.so -rmf LevelsDict.rootmap Levels.hh LevelsLinkDef.h

$(PROGRAM): $(SRCS)
	@echo "Building $(PROGRAM) ..."
	@rm -f $(PROGRAM)
	@$(CXX) $(CXXFLAGS) $(SHARED) -o $@ $^ $(ROOTLIBS)
	@echo "done"

clean:; @rm -rf core *~ LevelsDict* $(PROGRAM)
