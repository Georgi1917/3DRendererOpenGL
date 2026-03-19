#include "include/imgui/imgui.h"
#include "include/imgui/imgui_impl_glfw.h"
#include "include/imgui/imgui_impl_opengl3.h"
#include "include/imguizmo/ImGuizmo.h"
#include "Window/Window.h"
#include "Window/Time.h"
#include "Shader.h"
#include "MousePicker.h"
#include "Renderer/Renderer.h"
#include "Framebuffer/PickingFramebuffer.h"
#include "ImGUILayer/ImGuizmoLayer.h"
#include "ImGUILayer/HierarchyPanel.h"

int main()
{

    Window win = Window(1280, 720, "Renderer");

    Shader basicShader("shaders/basic.vs", "shaders/basic.fs");
    Shader lightingShader("shaders/lighting.vs", "shaders/lighting.fs");
    Shader pickingShader("shaders/picking.vs", "shaders/picking.fs");
    Shader skyboxShader("shaders/skybox.vs", "shaders/skybox.fs");

    ImGuizmoLayer ImGuizmoLayer;
    HierarchyPanel HierarchyPanel;
    MousePicker mousePicker;
    FramebufferSpecification fbo_spec{ win.width, win.height };
    PickingFramebuffer fbo{ fbo_spec };
    Scene scene;
    Renderer renderer; renderer.fbo = fbo;

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
        renderer.SkyboxPass(skyboxShader, scene);
        renderer.MainPass(basicShader, scene);
        renderer.LightPass(lightingShader, scene);

        activeEntity = mousePicker.GetClickedEntity(fbo, scene);

        ImGuizmoLayer.BeginFrame(0, 0, win.width, win.height);
        ImGuizmoLayer.UpdateEntity(activeEntity, scene.camera->GetViewMatrix(), scene.projection);

        if (fbo_spec.width != win.width || fbo_spec.height != win.height)
        {

            fbo_spec.width = win.width; fbo_spec.height = win.height;
            fbo.ResizeFramebuffer(fbo_spec);
            renderer.fbo = fbo;
            scene.ResetProjection(win.width, win.height);

        }

        HierarchyPanel.OnRender("Window", scene);

        win.SwapBuffers();
        win.PollEvents();

    }

    HierarchyPanel.Shutdown();
    win.Terminate();
    return 0;

}