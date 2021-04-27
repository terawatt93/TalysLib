CXX = `root-config --cxx`
CXXFLAGS = `root-config --cflags` -fPIC -g
ROOTLIBS = `root-config --glibs`
SHARED = -shared
SRCS = TalysLibDict.cxx TalysLib.cc
HDRS = TalysLinkDef.h TalysLib.hh

PROGRAM = TalysLib.so

all: $(PROGRAM)

TalysLibDict.cxx: $(HDRS) TalysLinkDef.h
	@echo "Generating dictionary ..."
	#@rootcint -f $@ -c -p $^
	@rootcling -f TalysLibDict.cxx -rml TalysLib.so -rmf TalysLib.rootmap TalysLib.hh TalysLinkDef.h 

$(PROGRAM): $(SRCS)
	@echo "Building $(PROGRAM) ..."
	@rm -f $(PROGRAM)
	@$(CXX) $(CXXFLAGS) $(SHARED) -o $@ $^ $(ROOTLIBS)
	@echo "done"

clean:; @rm -rf core *.so *.rootmap *.cxx *.pcm
install:; @echo 'export LD_LIBRARY_PATH=$$LD_LIBRARY_PATH:'`pwd`>>~/.bashrc; echo 'export CPATH=$$CPATH:'`pwd`>>~/.bashrc; echo 'export TALYSLIBDIR='`pwd` >> ~/.bashrc
