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

int main()
{

    Window win = Window(1280, 720, "Renderer");

    Shader basicShader("shaders/basic.vs", "shaders/basic.fs");
    Shader lightingShader("shaders/lighting.vs", "shaders/lighting.fs");
    Shader pickingShader("shaders/picking.vs", "shaders/picking.fs");
    Shader skyboxShader("shaders/skybox.vs", "shaders/skybox.fs");

    ImGuizmoLayer ImGuizmoLayer;
    HierarchyPanel HierarchyPanel;
    SceneViewport SceneViewport;

    Framebuffer picking_fbo{ win.width, win.height };
    Framebuffer main_fbo{ win.width, win.height };

    MousePicker mousePicker;
    Scene scene;
    Renderer renderer; renderer.fbo = picking_fbo;

    HierarchyPanel.Init(win, true);

    Model* activeEntity = nullptr;

    while(!win.ShouldClose())
    {

        float deltaTime = GetDeltaTime();

        scene.camera->Update(win.window, deltaTime);

        renderer.BeginFrame();

        HierarchyPanel.NewFrame();
        HierarchyPanel.ShowDockspace();

        renderer.PickingPass(pickingShader, scene);
        main_fbo.Bind();
        renderer.SkyboxPass(skyboxShader, scene);
        renderer.MainPass(basicShader, scene);
        renderer.LightPass(lightingShader, scene);
        main_fbo.Unbind();

        activeEntity = mousePicker.GetClickedEntity(picking_fbo, scene);

        if (picking_fbo.f_width != main_fbo.f_width || picking_fbo.f_height != main_fbo.f_height)
        {

            picking_fbo.ResizeFramebuffer(main_fbo.f_width, main_fbo.f_height);
            renderer.fbo = picking_fbo;
            scene.ResetProjection(main_fbo.f_width, main_fbo.f_height);

        }

        HierarchyPanel.OnRender("Hierarchy Panel", scene);
        SceneViewport.OnRender("Scene", main_fbo, scene);

        win.SwapBuffers();
        win.PollEvents();

    }

    HierarchyPanel.Shutdown();
    win.Terminate();
    return 0;

}