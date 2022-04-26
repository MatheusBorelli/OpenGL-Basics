BIN		:= bin/Release/OpenGL.exe

SRC		:= src
UTILSRC	:= src/utility
TESTSRC := src/tests

SRC_FILES		:= $(wildcard src/*.c)
UTILSRC_FILES	:= $(wildcard src/utility/*.c)
TESTSRC_FILES	:= $(wildcard src/tests/*.c)

OBJDIR	:= src/objs
OBJS 	:= $(patsubst $(SRC)/%.c, $(OBJDIR)/%.o, $(SRC_FILES))
UTILOBJS:= $(patsubst $(UTILSRC)/%.c, $(OBJDIR)/%.o, $(UTILSRC_FILES))
TESTOBJS:= $(patsubst $(TESTSRC)/%.c, $(OBJDIR)/%.o, $(TESTSRC_FILES))

# Cimgui stuff
DIR 				:= src/vendor/cimgui
IMGUI_INCLDIR		:= src/vendor/cimgui/imgui


CFLAGS					:= -Wall -I$(DIR) -I$(IMGUI_INCLDIR) -g -DIMGUI_IMPL_OPENGL_LOADER_GLEW -DIMGUI_IMPL_API=""
IMPL_CFLAGS_GLFW 		:= -I$(DIR) -I$(IMGUI_INCLDIR) -DIMGUI_IMPL_API="extern \"C\""
IMPL_CFLAGS_OPENGL		:= -I$(DIR) -I$(IMGUI_INCLDIR) -DIMGUI_IMPL_API="extern \"C\""


CIMGUI_LIB			:= -Llib/cimgui -lcimgui
LIB					:=$(CIMGUI_LIB) -lglfw3 -lgdi32 -lopengl32 -lglew32 -lglu32 -static-libstdc++ -static-libgcc -Bstatic -lpthread

all: objFolder linkStage

objFolder:
ifneq ($(wildcard /src/objs/.*),"")
	@echo "$(OBJDIR) already exist"
else
	mkdir src\objs
	@echo "Created $(OBJDIR)"
endif

linkStage: $(OBJS) $(UTILOBJS) $(TESTOBJS) $(OBJDIR)/imgui_impl_opengl3.o $(OBJDIR)/imgui_impl_glfw.o
	g++ -o $(BIN) $(OBJS) $(TESTOBJS) $(UTILOBJS) $(OBJDIR)/imgui_impl_opengl3.o $(OBJDIR)/imgui_impl_glfw.o $(LIB)

#Compile source and utility code
$(OBJDIR)/%.o: $(SRC)/%.c
	gcc -I$(SRC) -I$(UTILSRC) -I$(TESTSRC) $(CFLAGS) -c $< -o $@

$(OBJDIR)/%.o: $(UTILSRC)/%.c
	gcc -I$(SRC) -I$(UTILSRC) $(CFLAGS) -c $< -o $@

$(OBJDIR)/%.o: $(TESTSRC)/%.c
	gcc -I$(SRC) -I$(TESTSRC) $(CFLAGS) -c $< -o $@

#Compile c++ backends of imgui
$(OBJDIR)/imgui_impl_glfw.o: $(DIR)/imgui_impl_glfw.cpp $(DIR)/imgui_impl_glfw.h
	g++ $(IMPL_CFLAGS_GLFW) -c $(DIR)/imgui_impl_glfw.cpp -o $@

$(OBJDIR)/imgui_impl_opengl3.o: $(DIR)/imgui_impl_opengl3.cpp $(DIR)/imgui_impl_opengl3.h
	g++ $(IMPL_CFLAGS_OPENGL) -c $(DIR)/imgui_impl_opengl3.cpp -o $@

#run application
run:
	./bin/Release/openGL.exe

clean:
	del /Q /S $(subst /,\, $(OBJS))
	del /Q /S $(subst /,\, $(UTILOBJS))
	del /Q /S $(subst /,\, $(TESTOBJS))
	del /Q /S $(subst /,\, $(OBJDIR)/imgui_impl_opengl3.o)
	del /Q /S $(subst /,\, $(OBJDIR)/imgui_impl_glfw.o)