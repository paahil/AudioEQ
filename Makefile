CXXFLAGS := -std=c++17 -g -Wall -Wextra -Wno-missing-field-initializers
CPPFLAGS := -c

EXE:=AudioEQ.exe
BASEDIR = $(CURDIR)

AQBUILD := $(BASEDIR)/libs/aquila/build
AQINCLUDE := $(BASEDIR)/libs/aquila/aquila

RTBUILD := $(BASEDIR)/libs/rtaudio/build
RTLIB := $(BASEDIR)/libs/rtaudio/build/lib
RTINCLUDE := $(BASEDIR)/libs/rtaudio/include

WXLIB := $(BASEDIR)/libs/wxWidgets/lib
WXMAIN := $(BASEDIR)/libs/wxWidgets/lib/mswu
WXINCLUDE := $(BASEDIR)/libs/wxWidgets/include
BUILDDIR := build
OBJDIR := obj
SRCDIR := src
WXLDLIBS := -lwxjpeg -lwxexpat -lwxmsw31u_adv -lwxbase31u -lwxbase31u_xml -lwxbase31u_net -lwxmsw31u_core
LDLIBS := -L$(WXLIB) $(WXLDLIBS) -mwindows -L$(RTLIB) 
SRCS := $(shell dir  $(subst /,\,$(BASEDIR)/$(SRCDIR)) /s /b | findstr /i .cpp)
OBJS := $(patsubst $(BASEDIR)/$(SRCDIR)/%.cpp, $(BASEDIR)/$(OBJDIR)/%.o, $(subst \,/,$(SRCS)))
DESTDLLS := $(patsubst $(AQLIB)/%.dll, $(BASEDIR)/$(BUILDDIR)/%.dll, $(wildcard $(AQLIB)/*.dll))\
$(patsubst $(RTLIB)/%.dll, $(BASEDIR)/$(BUILDDIR)/%.dll, $(wildcard $(RTLIB)/*.dll))\
$(patsubst $(WXLIB)/%.dll, $(BASEDIR)/$(BUILDDIR)/%.dll, $(wildcard $(WXLIB)/*.dll))
all : makelibs makedirs buildexe clean

makelibs:
	cmake -S $(BASEDIR)/libs/aquila -B $(AQBUILD) -G"MinGW Makefiles"
	cmake -S $(BASEDIR)/libs/rtaudio -B $(RTBUILD)  -G"MinGW Makefiles"
	cd $(AQBUILD) && $(MAKE)
	cd $(RTBUILD) && $(MAKE)

makedirs:
	if not exist $(BUILDDIR) mkdir $(BUILDDIR)
	if not exist $(OBJDIR) mkdir $(OBJDIR)
	echo $(OBJS)


buildexe: $(BASEDIR)/$(BUILDDIR)/$(EXE)
	$(MAKE) copydlls
$(BASEDIR)/$(BUILDDIR)/$(EXE): $(OBJS)
	$(CXX) $^ -o $@ $(LDLIBS) 

$(BASEDIR)/$(OBJDIR)/%.o: $(BASEDIR)/$(SRCDIR)/%.cpp
	if not exist $(patsubst $(BASEDIR)/%, "%",$(dir $@)) mkdir $(patsubst $(BASEDIR)/%, "%",$(dir $@))
	$(CXX) $(CXXFLAGS) $(CPPFLAGS) $< -o $@ -I$(WXMAIN) -I$(AQINCLUDE) -I$(RTINCLUDE) -I$(WXINCLUDE) 


copydlls: $(DESTDLLS)
$(BASEDIR)/$(BUILDDIR)/%.dll : $(AQLIB)/%.dll
	cd $(AQLIB) && copy /y $(notdir $<) $(subst /,\,$(BASEDIR)/$(BUILDDIR))
$(BASEDIR)/$(BUILDDIR)/%.dll : $(WXLIB)/%.dll
	cd $(WXLIB) && copy /y $(notdir $<) $(subst /,\,$(BASEDIR)/$(BUILDDIR))
$(BASEDIR)/$(BUILDDIR)/%.dll : $(RTLIB)/%.dll
	cd $(RTLIB) && copy /y $(notdir $<) $(subst /,\,$(BASEDIR)/$(BUILDDIR))

run:
	$(BUILDDIR)/$(EXE)

clean: 
	rmdir /s /q $(subst /,\,$(BASEDIR)/$(OBJDIR))