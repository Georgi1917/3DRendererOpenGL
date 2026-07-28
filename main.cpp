#include "include/imgui/imgui.h"
#include "include/imgui/imgui_impl_glfw.h"
#include "include/imgui/imgui_impl_opengl3.h"
#include "include/imguizmo/ImGuizmo.h"
#include "Window/Window.h"
#include "Window/Time.h"
#include "Shader.h"
#include "MousePicker.h"
#include "Renderer/Renderer.h"
#include "Framebuffer/Framebuffer.h"
#include "ImGUILayer/ImGuizmoLayer.h"
#include "ImGUILayer/HierarchyPanel.h"
#include "ImGUILayer/SceneViewport.h"
#include "ImGUILayer/EntityControllPanel.h"
#include "ImGUILayer/ImGuiLayer.h"

int main()
{

    Window win = Window(1280, 720, "Renderer");

    Shader basicShader("shaders/basic.vs", "shaders/basic.fs");
    Shader lightingShader("shaders/lighting.vs", "shaders/lighting.fs");
    Shader pickingShader("shaders/picking.vs", "shaders/picking.fs");
    Shader skyboxShader("shaders/skybox.vs", "shaders/skybox.fs");

    ImGuizmoLayer       ImGuizmoLayer;
    ImGuiLayer          ImGuiLayer;
    HierarchyPanel      HierarchyPanel;
    EntityControllPanel EntityPanel;
    SceneViewport       SceneViewport;

    Framebuffer picking_fbo{ 0, 0, win.width, win.height };
    Framebuffer main_fbo{ 0, 0, win.width, win.height };

    MousePicker mousePicker;
    Scene scene;
    Renderer renderer; 
    renderer.picking_fbo = picking_fbo;
    renderer.main_fbo = main_fbo;

    ImGuiLayer.Init(win, true);

    while(!win.ShouldClose())
    {

        float deltaTime = GetDeltaTime();

        scene.camera->Update(win.window, deltaTime);

        renderer.BeginFrame();

        ImGuiLayer.NewFrame();
        ImGuiLayer.ShowDockspace();

        renderer.PickingPass(pickingShader, scene);
        main_fbo.Bind();
        renderer.SkyboxPass(skyboxShader, scene);
        renderer.MainPass(basicShader, scene);
        renderer.LightPass(lightingShader, scene);
        main_fbo.Unbind();

        mousePicker.GetClickedEntity(picking_fbo, scene);

        if (picking_fbo.f_width != main_fbo.f_width || picking_fbo.f_height != main_fbo.f_height)
        {

            picking_fbo.ResizeFramebuffer(main_fbo.f_x, main_fbo.f_y, main_fbo.f_width, main_fbo.f_height);
            renderer.picking_fbo = picking_fbo;
            renderer.main_fbo = main_fbo;

        }

        EntityPanel.OnRender("Entity Panel", scene);
        HierarchyPanel.OnRender("Hierarchy Panel", scene);
        SceneViewport.OnRender("Scene", main_fbo, scene);

        ImGuiLayer.DrawRenderData();

        win.SwapBuffers();
        win.PollEvents();

    }

    ImGuiLayer.Shutdown();
    win.Terminate();
    return 0;

}