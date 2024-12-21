CXXFLAGS := -std=c++11 -g -Wall -Wextra -Wno-missing-field-initializers
CPPFLAGS := -c -D__WINDOWS_ASIO__

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
WXLDLIBS := -lwxjpeg -lwxexpat -lwxmsw31u_adv -lwxbase31u -lwxbase31u_xml -lwxbase31u_net -lwxmsw31u_core -mwindows
LDLIBS := -L$(WXLIB) $(WXLDLIBS) -L$(RTBUILD) -lrtaudio 
SRCS := $(shell dir  $(subst /,\,$(BASEDIR)/$(SRCDIR)) /s /b | findstr /i .cpp)
OBJS := $(patsubst $(BASEDIR)/$(SRCDIR)/%.cpp, $(BASEDIR)/$(OBJDIR)/%.o, $(subst \,/,$(SRCS)))
DESTDLLS := $(patsubst $(RTBUILD)/%.dll, $(BASEDIR)/$(BUILDDIR)/%.dll, $(wildcard $(RTBUILD)/*.dll))\
$(patsubst $(WXLIB)/%.dll, $(BASEDIR)/$(BUILDDIR)/%.dll, $(wildcard $(WXLIB)/*.dll))
all : makelibs makedirs buildexe clean

makelibs:
	cmake -S $(BASEDIR)/libs/rtaudio -B $(RTBUILD)  -G"MinGW Makefiles"
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
	$(CXX) $(CXXFLAGS) $(CPPFLAGS) $< -o $@ -I$(WXMAIN) -I$(RTINCLUDE) -I$(WXINCLUDE) 


copydlls: $(DESTDLLS)

$(BASEDIR)/$(BUILDDIR)/%.dll : $(WXLIB)/%.dll
	cd $(WXLIB) && copy /y $(notdir $<) $(subst /,\,$(BASEDIR)/$(BUILDDIR))
$(BASEDIR)/$(BUILDDIR)/%.dll : $(RTBUILD)/%.dll
	cd $(RTBUILD) && copy /y $(notdir $<) $(subst /,\,$(BASEDIR)/$(BUILDDIR))

clean: 
	rmdir /s /q $(subst /,\,$(BASEDIR)/$(OBJDIR))

buildaudiotest: $(BASEDIR)/test/thrputtest.exe

$(BASEDIR)/test/thrputtest.exe: $(BASEDIR)/test/thrputtest.o
	$(CXX) $(BASEDIR)/test/thrputtest.o -o $(BASEDIR)/test/thrputtest.exe -L$(RTBUILD) -lrtaudio
$(BASEDIR)/test/thrputtest.o: $(BASEDIR)/test/thrputtest.cpp
	$(CXX) $(CXXFLAGS) $(CPPFLAGS) $< -o $@ -I$(RTINCLUDE)