CXXFLAGS := -std=c++17 -g -Wall -Wextra -Wno-missing-field-initializers
CPPFLAGS := -c

EXE:=AudioEQ.exe
BASEDIR = $(CURDIR)

AQBUILD := $(BASEDIR)/libs/aquila/build
AQINCLUDE := $(BASEDIR)/libs/aquila/aquila

RTBUILD := $(BASEDIR)/libs/rtaudio/build
RTINCLUDE := $(BASEDIR)/libs/rtaudio

WXLIB := $(BASEDIR)/libs/wxWidgets/lib
WXMAIN := $(BASEDIR)/libs/wxWidgets/lib/mswu
WXINCLUDE := $(BASEDIR)/libs/wxWidgets/include
BUILDDIR := build
OBJDIR := obj
SRCDIR := src
WXLDLIBS := -lwxjpeg -lwxexpat -lwxmsw31u_adv -lwxbase31u -lwxbase31u_xml -lwxbase31u_net -lwxmsw31u_core
LDLIBS := -L$(WXLIB) $(WXLDLIBS) -mwindows -L$(RTBUILD) -lrtaudio -L$(AQBUILD) -laquila -L$(AQBUILD)/lib -lOoura_fft
SRCS := $(shell dir  $(subst /,\,$(BASEDIR)/$(SRCDIR)) /s /b | findstr /i .cpp)
OBJS := $(patsubst $(BASEDIR)/$(SRCDIR)/%.cpp, $(BASEDIR)/$(OBJDIR)/%.o, $(subst \,/,$(SRCS)))
DESTDLLS := $(patsubst $(AQBUILD)/%.dll, $(BASEDIR)/$(BUILDDIR)/%.dll, $(wildcard $(AQBUILD)/*.dll))\
$(patsubst $(RTBUILD)/%.dll, $(BASEDIR)/$(BUILDDIR)/%.dll, $(wildcard $(RTBUILD)/*.dll))\
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
$(BASEDIR)/$(BUILDDIR)/%.dll : $(AQBUILD)/%.dll
	cd $(AQBUILD) && copy /y $(notdir $<) $(subst /,\,$(BASEDIR)/$(BUILDDIR))

$(BASEDIR)/$(BUILDDIR)/%.dll : $(WXLIB)/%.dll
	cd $(WXLIB) && copy /y $(notdir $<) $(subst /,\,$(BASEDIR)/$(BUILDDIR))
$(BASEDIR)/$(BUILDDIR)/%.dll : $(RTBUILD)/%.dll
	cd $(RTBUILD) && copy /y $(notdir $<) $(subst /,\,$(BASEDIR)/$(BUILDDIR))

run:
	$(BUILDDIR)/$(EXE)

clean: 
	rmdir /s /q $(subst /,\,$(BASEDIR)/$(OBJDIR))