CXX = g++
CXXFLAGS = -Iinclude

LDFLAGS = -Llib -lglfw3 -lglew32 -lgdi32 -lopengl32

IMGUI = include/imgui/imgui_demo.cpp include/imgui/imgui_draw.cpp include/imgui/imgui_impl_glfw.cpp include/imgui/imgui_impl_opengl3.cpp include/imgui/imgui_tables.cpp include/imgui/imgui_widgets.cpp include/imgui/imgui.cpp
ADDITIONAL_OBJS = VertexBuffer.cpp IndexBuffer.cpp VertexArray.cpp BufferLayoutObject.cpp Renderer.cpp Shader.cpp Camera.cpp MousePicker.cpp
RENDERABLES_OBJS = Renderables/Renderable.cpp Renderables/Cube.cpp Renderables/Sphere.cpp Renderables/LightSource.cpp Renderables/Surface_c.cpp
MESH = Renderables/Mesh.cpp
FRAMEBUFFER_OBJS = Framebuffer/Framebuffer.cpp Framebuffer/PickingTexture.cpp Framebuffer/Renderbuffer.cpp
TEXTURES = Textures/Texture.cpp

SRC = main.cpp stb_image.cpp $(IMGUI) $(ADDITIONAL_OBJS) $(RENDERABLES_OBJS) $(MESH) $(FRAMEBUFFER_OBJS) $(TEXTURES)

TARGET = main.exe

all: $(TARGET)

$(TARGET): $(SRC)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(SRC) $(LDFLAGS)

clean:
	del /Q $(TARGET)
