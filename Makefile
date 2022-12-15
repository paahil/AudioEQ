CXXFLAGS := -std=c++17 -g -Wall -Wextra -Wno-missing-field-initializers
CPPFLAGS := -c

EXE:=AudioEQ.exe
BASEDIR = $(CURDIR)

RTBUILD := $(BASEDIR)/libs/rtaudio/build
RTINCLUDE := $(BASEDIR)/libs/rtaudio

WXLIB := $(BASEDIR)/libs/wxWidgets/lib/gcc_dll
WXBUILD := $(BASEDIR)/libs/wxWidgets/build
WXMAIN := $(WXLIB)/mswu
WXINCLUDE := $(BASEDIR)/libs/wxWidgets/include
BUILDDIR := build
OBJDIR := obj
SRCDIR := src
WXLDLIBS := -lwxjpeg -lwxexpat -lwxmsw31u_adv -lwxbase31u -lwxbase31u_xml -lwxbase31u_net -lwxmsw31u_core
LDLIBS := -L$(WXLIB) $(WXLDLIBS) -mwindows -L$(RTBUILD) -lrtaudio 
SRCS := $(shell dir  $(subst /,\,$(BASEDIR)/$(SRCDIR)) /s /b | findstr /i .cpp)
OBJS := $(patsubst $(BASEDIR)/$(SRCDIR)/%.cpp, $(BASEDIR)/$(OBJDIR)/%.o, $(subst \,/,$(SRCS)))
DESTDLLS := $(patsubst $(RTBUILD)/%.dll, $(BASEDIR)/$(BUILDDIR)/%.dll, $(wildcard $(RTBUILD)/*.dll))\
$(patsubst $(WXLIB)/%.dll, $(BASEDIR)/$(BUILDDIR)/%.dll, $(wildcard $(WXLIB)/*.dll))
all : makelibs makedirs buildexe clean

makelibs:
	cmake -S $(BASEDIR)/libs/aquila -B $(AQBUILD) -G"MinGW Makefiles"
	cmake -S $(BASEDIR)/libs/rtaudio -B $(RTBUILD)  -G"MinGW Makefiles"
	cd $(AQBUILD) && $(MAKE)
	cd $(RTBUILD) && $(MAKE)
	cd $(WXBUILD)/msw && $(MAKE) -f makefile.gcc BUILD=release SHARED=1

makedirs:
	if not exist $(BUILDDIR) mkdir $(BUILDDIR)
	if not exist $(OBJDIR) mkdir $(OBJDIR)
	echo $(OBJS)


buildexe: $(BASEDIR)/$(BUILDDIR)/$(EXE)
	$(MAKE) copydlls
$(BASEDIR)/$(BUILDDIR)/$(EXE): $(OBJS)
	$(CXX) $^ -o $@ $(LDLIBS) 

$(BASEDIR)/$(OBJDIR)/%.o: $(BASEDIR)/$(SRCDIR)/%.cpp
	if not exist $(patsubst $(BASEDIR)/%, "%",$(dir $@)) mkdir $(patsubst $(BASEDIR)/%,"%",$(dir $@))
	$(CXX) $(CXXFLAGS) $(CPPFLAGS) $< -o $@ -I$(WXMAIN) -I$(AQINCLUDE) -I$(RTINCLUDE) -I$(WXINCLUDE) 


copydlls: $(DESTDLLS)

$(BASEDIR)/$(BUILDDIR)/%.dll : $(WXLIB)/%.dll
	cd $(WXLIB) && copy /y $(notdir $<) $(subst /,\,$(BASEDIR)/$(BUILDDIR))
$(BASEDIR)/$(BUILDDIR)/%.dll : $(RTBUILD)/%.dll
	cd $(RTBUILD) && copy /y $(notdir $<) $(subst /,\,$(BASEDIR)/$(BUILDDIR))

run:
	$(BUILDDIR)/$(EXE)

TESTSRC:= $(wildcard $(BASEDIR)/test/*.cpp)
TESTEXES:= $(subst .cpp,.exe,$(TESTSRC))
TESTOBJS:= $(subst .cpp,.o,$(TESTSRC))
TESTLDLIBS := -L$(WXLIB) $(WXLDLIBS) -L$(RTBUILD) -lrtaudio
test: $(TESTEXES)
	del $(subst /,\,$(TESTOBJS))
	$(MAKE) copytestdlls
$(BASEDIR)/test/%.exe : $(BASEDIR)/test/%.o
	@echo $<
	@echo $^
	@echo $@
	$(CXX) $< -o $@ $(TESTLDLIBS) 
$(BASEDIR)/test/%.o : $(BASEDIR)/test/%.cpp
	@echo $<
	@echo $@
	$(CXX) $< $(CPPFLAGS) -o $@ -I$(WXMAIN) -I$(RTINCLUDE) -I$(WXINCLUDE)

testexe: $(BASEDIR)/$(BUILDDIR)/$(EXE)
	rmdir /s /q $(subst /,\,$(BASEDIR)/$(OBJDIR))
	$(MAKE) copydlls
$(BASEDIR)/$(BUILDDIR)/$(EXE): $(OBJS)
	$(CXX) $^ -o $@ $(TESTLDLIBS) 

$(BASEDIR)/$(OBJDIR)/%.o: $(BASEDIR)/$(SRCDIR)/%.cpp
	if not exist $(patsubst $(BASEDIR)/%, "%",$(dir $@)) mkdir $(patsubst $(BASEDIR)/%, "%",$(dir $@))
	$(CXX) $(CXXFLAGS) $(CPPFLAGS) $< -o $@ -I$(WXMAIN) -I$(RTINCLUDE) -I$(WXINCLUDE) 

TESTDLLS:= $(patsubst $(BASEDIR)/$(BUILDDIR)/%.dll,$(BASEDIR)/test/%.dll,$(DESTDLLS))
copytestdlls: $(TESTDLLS)
$(BASEDIR)/test/%.dll : $(AQBUILD)/%.dll
	cd $(AQBUILD) && copy /y $(notdir $<) $(subst /,\,$(BASEDIR)/test)

$(BASEDIR)/test/%.dll : $(WXLIB)/%.dll
	cd $(WXLIB) && copy /y $(notdir $<) $(subst /,\,$(BASEDIR)/test)
$(BASEDIR)/test/%.dll : $(RTBUILD)/%.dll
	cd $(RTBUILD) && copy /y $(notdir $<) $(subst /,\,$(BASEDIR)/test)

clean: 
	rmdir /s /q $(subst /,\,$(BASEDIR)/$(OBJDIR))