#объявим переменные, которые будем использовать ниже
#флаги команд:
CXX = `root-config --cxx`
CXXFLAGS = `root-config --cflags` -fPIC -g
ROOTLIBS = `root-config --glibs`
SHARED = -shared
#и названия файлов для сборки:
SRCS = TalysLibDict.cxx TalysLib.cc
HDRS = TalysLinkDef.h TalysLib.hh

PROGRAM = TalysLib.so

#цель по-умолчанию - cборка библиотеки (TalysLib.so), зависит от цель2
all: $(PROGRAM) 

#цель1 - ?
TalysLibDict.cxx: $(HDRS) TalysLinkDef.h
	@echo "Generating dictionary ..."
	#@rootcint -f $@ -c -p $^
	@rootcling -f TalysLibDict.cxx -rml TalysLib.so -rmf TalysLib.rootmap TalysLib.hh TalysLinkDef.h

#цель2 - ?, зависит от цель1 и TalysLib.cc через переменную SRCS
$(PROGRAM): $(SRCS)
	@echo "Building $(PROGRAM) ..."
	@rm -f $(PROGRAM)
	@$(CXX) $(CXXFLAGS) $(SHARED) -o $@ $^ $(ROOTLIBS)
	@echo "done"

clean:; @rm -rf core *~ LevelsDict* $(PROGRAM)
install:; @echo 'export LD_LIBRARY_PATH=$$LD_LIBRARY_PATH:'`pwd`>>~/.bashrc; echo 'export CPATH=$$CPATH:'`pwd`>>~/.bashrc
