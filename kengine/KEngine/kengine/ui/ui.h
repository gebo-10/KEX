#pragma once
#include <kengine/core/base/base.h>
#include <kengine/core/math/kmath.h>



#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw.h"
#include "imgui/imgui_impl_opengl3.h"
#include <stdio.h>
//#define CIMGUI_DEFINE_ENUMS_AND_STRUCTS
//#include "cimgui.h"
namespace kengine {
	class UI
	{
	public:
		UI(){}
		~UI(){}

		void init() {
            ImGuiIO& io = ImGui::GetIO();
            io.Fonts->AddFontFromFileTTF("main/font/DroidSans.ttf", 20);
            io.Fonts->Build();
        }

        void new_frame() {
            ImGui_ImplOpenGL3_NewFrame();
            ImGui_ImplGlfw_NewFrame();
            ImGui::NewFrame();
        }

        void end_frame() {
            ImGui::Render();
            ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
        }
		void test() {
            static float f = 0.0f;
            static int counter = 0;

            ImGui::Begin("Hello, world!");                          // Create a window called "Hello, world!" and append into it.

            ImGui::Text("This is some useful text.");               // Display some text (you can use a format strings too)
            // ImGui::Checkbox("Demo Window", &show_demo_window);      // Edit bools storing our window open/close state
            //ImGui::Checkbox("Another Window", &show_another_window);

            ImGui::SliderFloat("float", &f, 0.0f, 1.0f);            // Edit 1 float using a slider from 0.0f to 1.0f
            //ImGui::ColorEdit3("clear color", (float*)&clear_color); // Edit 3 floats representing a color

            if (ImGui::Button("Button"))                            // Buttons return true when clicked (most widgets return true when edited/activated)
                counter++;
            ImGui::SameLine();
            ImGui::Text("counter = %d", counter);

            ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
            ImGui::End();
		}
        //void test2() {
        //    static float f = 0.0f;
        //    static int counter = 0;

        //    
        //    igBegin("Hello, world!",0,0);                          // Create a window called "Hello, world!" and append into it.

        //    igText("This is some useful text.");               // Display some text (you can use a format strings too)
        //    // ImGui::Checkbox("Demo Window", &show_demo_window);      // Edit bools storing our window open/close state
        //    //ImGui::Checkbox("Another Window", &show_another_window);

        //    igSliderFloat("float", &f, 0.0f, 1.0f,"%.3f",0);            // Edit 1 float using a slider from 0.0f to 1.0f
        //    //ImGui::ColorEdit3("clear color", (float*)&clear_color); // Edit 3 floats representing a color

        //    if (igButton("Button", ImVec2(0,0)))                            // Buttons return true when clicked (most widgets return true when edited/activated)
        //        counter++;
        //    igSameLine(0,0);
        //    igText("counter = %d", counter);

        //    igText("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / igGetIO()->Framerate, igGetIO()->Framerate);
        //    igEnd();
        //}
	};

}