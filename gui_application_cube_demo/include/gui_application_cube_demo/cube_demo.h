#pragma once

#include "gui_application/version.h"
#include "gui_application/gui_application.h"

#include "simple_draw_gl/imgui_gl.h"

#include "simple_draw_gl/cameras/cameras.h"
#include "simple_draw_gl/drawing/cube.h"
#include "simple_draw_gl/shader/program.h"
#include "simple_draw_gl/shader/default_program.h"


std::ostream& operator<<(std::ostream &os, glm::mat4 mat)
{
    os << mat[0][0] << ", " << mat[0][1] << ", " << mat[0][2] << ", " << mat[0][3] << "\n";
    os << mat[1][0] << ", " << mat[1][1] << ", " << mat[1][2] << ", " << mat[1][3] << "\n";
    os << mat[2][0] << ", " << mat[2][1] << ", " << mat[2][2] << ", " << mat[2][3] << "\n";
    os << mat[3][0] << ", " << mat[3][1] << ", " << mat[3][2] << ", " << mat[3][3] << "\n";
    return os;
}

namespace gui_application_cube_demo {

    class CubeDemo : public gui_application::GuiApplication
    {
    public:
        CubeDemo() {}
        virtual ~CubeDemo() {}
        void setup() override
        {
            
            m_drawProgram.setup();
            m_cube = simple_draw_gl::drawing::Cube(glm::vec3(0,0,0), 10.0f);
            m_cube.setup();

            // Enable depth test
            glEnable(GL_DEPTH_TEST);
            // Accept fragment if it closer to the camera than the former one
            glDepthFunc(GL_LESS);            
        }
        void frame() override
        {
            int display_w, display_h;
            glfwGetFramebufferSize(m_window, &display_w, &display_h);

            //if (m_showDemoWindow)
            //{
            //    ImGui::ShowDemoWindow(&m_showDemoWindow);
            //}
            
            ImGui::Begin("Camera");
            //ImGui::BeginGroup();
            //ImGui::Text("Choose Camera");
            //ImGui::RadioButton("First Person Camera", &m_activeCamera, 0);
            //ImGui::RadioButton("Orbital Camera", &m_activeCamera, 1);
            //ImGui::EndGroup();

            ImGui::BeginTabBar("Camera Options");
            if (ImGui::BeginTabItem("First Person Camera"))
            {
                ImGui::SliderFloat("position.x", &m_firstPersonCamera.view.position.x, -100, 100);
                ImGui::SliderFloat("position.y", &m_firstPersonCamera.view.position.y, -100, 100);
                ImGui::SliderFloat("position.z", &m_firstPersonCamera.view.position.z, -100, 100);
                ImGui::SliderFloat("roll", &m_firstPersonCamera.view.rollPitchYaw.x, -3.14159 * 2, 3.14159 * 2);
                ImGui::SliderFloat("pitch", &m_firstPersonCamera.view.rollPitchYaw.y, -3.14159 * 2, 3.14159 * 2);
                ImGui::SliderFloat("yaw", &m_firstPersonCamera.view.rollPitchYaw.z, -3.14159 * 2, 3.14159 * 2);
                ImGui::EndTabItem();
                m_activeCamera = 0;
            }
            if (ImGui::BeginTabItem("Orbital Camera"))
            {
                ImGui::SliderFloat("target.x", &m_orbitalCamera.view.target.x, -100, 100);
                ImGui::SliderFloat("target.y", &m_orbitalCamera.view.target.y, -100, 100);
                ImGui::SliderFloat("target.z", &m_orbitalCamera.view.target.z, -100, 100);
                ImGui::SliderFloat("roll", &m_orbitalCamera.view.angles.x, -3.14159 * 2, 3.14159 * 2);
                ImGui::SliderFloat("pitch", &m_orbitalCamera.view.angles.y, -3.14159 * 2, 3.14159 * 2);
                ImGui::SliderFloat("yaw", &m_orbitalCamera.view.angles.z, -3.14159 * 2, 3.14159 * 2);
                ImGui::SliderFloat("distance", &m_orbitalCamera.view.distance, -100, 100);
                ImGui::EndTabItem();
                m_activeCamera = 1;
            }
            if (ImGui::BeginTabItem("Look At Camera"))
            {
                ImGui::SliderFloat("position.x", &m_lookAtCamera.view.position.x, -100, 100);
                ImGui::SliderFloat("position.y", &m_lookAtCamera.view.position.y, -100, 100);
                ImGui::SliderFloat("position.z", &m_lookAtCamera.view.position.z, -100, 100);
                ImGui::SliderFloat("target.x", &m_lookAtCamera.view.target.x, -100, 100);
                ImGui::SliderFloat("target.y", &m_lookAtCamera.view.target.y, -100, 100);
                ImGui::SliderFloat("target.z", &m_lookAtCamera.view.target.z, -100, 100);

                ImGui::EndTabItem();
                m_activeCamera = 2;
            }
            ImGui::EndTabBar();
            ImGui::End();


            glm::mat4 projection_view_model;
            switch (m_activeCamera)
            {
            case 0:
                m_firstPersonCamera.updateViewport({ display_w, display_h });
                projection_view_model = m_firstPersonCamera.projection.mat() * m_firstPersonCamera.view.mat();
                break;
            case 1:
                m_orbitalCamera.updateViewport({ display_w, display_h });
                projection_view_model = m_orbitalCamera.projection.mat() * m_orbitalCamera.view.mat();
                break;
            case 2:
                m_lookAtCamera.updateViewport({ display_w, display_h });
                projection_view_model = m_lookAtCamera.projection.mat() * m_lookAtCamera.view.mat();
                break;
            }
                
            m_drawProgram.use();
            m_drawProgram.projection_view_model.set(projection_view_model);
            // m_camera
            m_cube.draw();
        }
    protected:
        simple_draw_gl::cameras::FirstPersonPerspectiveCamera m_firstPersonCamera;
        simple_draw_gl::cameras::OrbitalPerspectiveCamera m_orbitalCamera;
        simple_draw_gl::cameras::LookAtPerspectiveCamera m_lookAtCamera;
        
        int m_activeCamera = 0;

        simple_draw_gl::drawing::Cube m_cube;
        simple_draw_gl::shader::DefaultProgram m_drawProgram;
        bool m_showDemoWindow;
    };

} // namespace gui_application_cube_demo
