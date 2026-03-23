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

    FramebufferSpecification picking_spec{ win.width, win.height };
    FramebufferSpecification main_spec { 800, 600 };
    PickingFramebuffer fbo{ picking_spec };
    PickingFramebuffer main_fbo{ main_spec };

    MousePicker mousePicker;
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
        main_fbo.Bind();
        renderer.SkyboxPass(skyboxShader, scene);
        renderer.MainPass(basicShader, scene);
        renderer.LightPass(lightingShader, scene);
        main_fbo.Unbind();

        activeEntity = mousePicker.GetClickedEntity(fbo, scene);

        if (picking_spec.width != main_spec.width || picking_spec.height != main_spec.height)
        {

            picking_spec.width = main_spec.width; picking_spec.height = main_spec.height;
            fbo.ResizeFramebuffer(picking_spec);
            renderer.fbo = fbo;
            scene.ResetProjection(main_spec.width, main_spec.height);

        }

        HierarchyPanel.OnRender("Hierarchy Panel", scene);
        ImGuizmoLayer.BeginFrame(SceneViewport.x, SceneViewport.y, SceneViewport.width, SceneViewport.height, SceneViewport.drawList);
        ImGuizmoLayer.UpdateEntity(activeEntity, scene.camera->GetViewMatrix(), scene.projection);
        SceneViewport.OnRender("Scene", main_fbo, main_spec);

        win.SwapBuffers();
        win.PollEvents();

    }

    HierarchyPanel.Shutdown();
    win.Terminate();
    return 0;

}