#pragma once
#pragma comment(linker, "/SUBSYSTEM:windows /ENTRY:mainCRTStartup")
#include <chrono>
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include "Gui/include/GLFW/glfw3.h"
#include "imgui_app.h"
#include "imgui_spectrum.h"
constexpr auto WIDTH = 720;
constexpr auto LENGTH = 720;







int main() {
	glfwInit();
	
	GLFWwindow* window = glfwCreateWindow(WIDTH, LENGTH, "Powerful Task Manager", NULL, NULL);

	glfwMakeContextCurrent(window);

	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO();
	ImFont* font = io.Fonts->AddFontFromFileTTF("Font\\Inter.ttf", 18.0);
	ImGui_ImplGlfw_InitForOpenGL(window, true);
	ImGui_ImplOpenGL3_Init("#version 130");
	ImGui::Spectrum::StyleColorsSpectrum();

	ImGuiApp app;

	// loop

	while (!glfwWindowShouldClose(window)) {
		glfwSwapInterval(1);
		glfwPollEvents();
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();

		int width, height;
		glfwGetWindowSize(window, &width, &height);
		ImGui::SetNextWindowSize(ImVec2(width, height * 0.98f ));
		ImGui::SetNextWindowPos(ImVec2(0, 0));

		app.PrimaFinestra();
		
		ImGui::SetNextWindowPos(ImVec2(0 , height * 0.98f));
		ImGui::SetNextWindowSize(ImVec2(width, height - (height * 0.98f)));
		app.Sbarra();
		ImGui::Render();
		int display_w, display_h;
		glfwGetFramebufferSize(window, &display_w, &display_h);
		glViewport(0, 0, display_w, display_h);
		glClear(GL_COLOR_BUFFER_BIT);
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
		glfwSwapBuffers(window);



	}




}



