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
	glfwSwapInterval(1);
	GLFWwindow* window = glfwCreateWindow(WIDTH, LENGTH, "Powerful Task Manager", NULL, NULL);

	glfwMakeContextCurrent(window);

	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO();
	ImFont* font = io.Fonts->AddFontFromFileTTF("Fonts\\Inter.ttf", 18.0);
	ImGui_ImplGlfw_InitForOpenGL(window, true);
	ImGui_ImplOpenGL3_Init("#version 130");
	ImGui::Spectrum::StyleColorsSpectrum();

	ImGuiApp app;

	// loop

	while (!glfwWindowShouldClose(window)) {
		glfwPollEvents();
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();

		int width, height;
		glfwGetWindowSize(window, &width, &height);
		float heightTop = height * 0.8f;
		float heightBottom = height - heightTop;
		ImGui::SetNextWindowSize(ImVec2(width, heightTop));
		ImGui::SetNextWindowPos(ImVec2(0, 0));

		app.render();
		ImGui::SetNextWindowPos(ImVec2(0, heightTop));
		ImGui::SetNextWindowSize(ImVec2(width, heightBottom));
		app.secondWind();
		ImGui::Render();
		int display_w, display_h;
		glfwGetFramebufferSize(window, &display_w, &display_h);
		glViewport(0, 0, display_w, display_h);
		glClear(GL_COLOR_BUFFER_BIT);
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
		glfwSwapBuffers(window);
		std::this_thread::sleep_for(std::chrono::milliseconds(16));


	}




}



