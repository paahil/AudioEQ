OUT_DIR := Debug
OUT_EXE := example_win32_opengl3
INCLUDES := -I../libs/imgui -I../libs/imgui/backends
SOURCES := imguitest.cpp ../libs/imgui/backends/imgui_impl_opengl3.cpp ../libs/imgui/backends/imgui_impl_win32.cpp ../libs/imgui/imgui.cpp ../libs/imgui/imgui_widgets.cpp ../libs/imgui/imgui_tables.cpp ../libs/imgui/imgui_draw.cpp ../libs/imgui/imgui_demo.cpp 
LIBS := -lopengl32 -lgdi32 -ldwmapi
all:
	if not exist $(OUT_DIR) mkdir $(OUT_DIR)
	g++ -DUNICODE $(INCLUDES) $(SOURCES) -o $(OUT_DIR)/$(OUT_EXE).exe --static -mwindows $(LIBS)