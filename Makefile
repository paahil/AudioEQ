CXXFLAGS := -std=c++17
CPPFLAGS := -DUNICODE -D__WINDOWS_ASIO__

EXE:=AudioEQ.exe
BASEDIR = $(CURDIR)

RTBUILD := $(BASEDIR)/libs/rtaudio/build
RTINCLUDE := $(BASEDIR)/libs/rtaudio

GUIDIR := $(BASEDIR)/libs/imgui
GUISRC := $(subst \,/,$(GUIDIR)/imgui.cpp) $(subst \,/,$(GUIDIR)/imgui_draw.cpp) $(subst \,/, $(GUIDIR)/imgui_tables.cpp) $(subst \,/,$(GUIDIR)/imgui_widgets.cpp)
GUIBESRC := $(subst \,/,$(wildcard $(GUIDIR)/backends/imgui_impl_opengl3.cpp)) $(subst \,/,$(wildcard $(GUIDIR)/backends/imgui_impl_win32.cpp))
BUILDDIR := build
OBJDIR := obj
SRCDIR := src
GUILIBS := --static -mwindows -lopengl32 -lgdi32 -ldwmapi 
LDLIBS := $(GUILIBS) -L$(RTBUILD) -lrtaudio 
SRCS :=  $(subst \,/,$(wildcard $(BASEDIR)/$(SRCDIR)/*.cpp)) $(GUISRC) $(GUIBESRC)    
OBJS := $(patsubst $(BASEDIR)/$(SRCDIR)/%.cpp, $(BASEDIR)/$(OBJDIR)/%.o, $(subst \,/,$(SRCS)))
DESTDLLS := $(patsubst $(RTBUILD)/%.dll, $(BASEDIR)/$(BUILDDIR)/%.dll, $(wildcard $(RTBUILD)/*.dll))
all : makelibs makedir buildexe copydlls

makelibs:
	cmake -S $(BASEDIR)/libs/rtaudio -B $(RTBUILD)  -G"MinGW Makefiles"
	cd $(RTBUILD) && $(MAKE)

makedir:
	if not exist $(BUILDDIR) mkdir $(BUILDDIR)

buildexe: $(BASEDIR)/$(BUILDDIR)/$(EXE)
	$(MAKE) copydlls
$(BASEDIR)/$(BUILDDIR)/$(EXE): $(SRCS)
	$(CXX) $(CXXFLAGS) $(CPPFLAGS) -I$(RTINCLUDE) -I$(GUIDIR) -I$(GUIDIR)/backends  $^ -o $@ $(LDLIBS) 

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