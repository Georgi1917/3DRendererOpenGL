CXX = g++
CXXFLAGS = -Iinclude

LDFLAGS = -Llib -lglfw3 -lglew32 -lgdi32 -lopengl32

IMGUI = include/imgui/imgui_demo.cpp include/imgui/imgui_draw.cpp include/imgui/imgui_impl_glfw.cpp include/imgui/imgui_impl_opengl3.cpp include/imgui/imgui_tables.cpp include/imgui/imgui_widgets.cpp include/imgui/imgui.cpp
RENDERER = Renderer/VertexArray.cpp Renderer/VertexBuffer.cpp Renderer/Renderer.cpp Renderer/IndexBuffer.cpp Renderer/BufferLayoutObject.cpp
ADDITIONAL_OBJS = Shader.cpp Camera.cpp MousePicker.cpp
SCENE = Scene/Mesh.cpp Scene/Light.cpp Scene/Model.cpp Scene/Scene.cpp
FRAMEBUFFER_OBJS = Framebuffer/Framebuffer.cpp Framebuffer/PickingTexture.cpp Framebuffer/Renderbuffer.cpp
TEXTURES = Textures/Texture.cpp Textures/Cubemap.cpp
WINDOW = Window/Window.cpp

SRC = main.cpp stb_image.cpp tiny_obj_loader.cpp $(IMGUI) $(RENDERER) $(ADDITIONAL_OBJS) $(SCENE) $(FRAMEBUFFER_OBJS) $(TEXTURES) $(WINDOW)

TARGET = main.exe

all: $(TARGET)

$(TARGET): $(SRC)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(SRC) $(LDFLAGS)

clean:
	del /Q $(TARGET)
