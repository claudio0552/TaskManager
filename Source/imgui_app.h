#pragma once
#include "process_app.h"
#include "imgui.h"

inline bool compare(const Processo& a, const Processo& b) {
	return a.memoryUsage > b.memoryUsage;
}

class ImGuiApp {
public:
	ImGuiApp();
	void render();
	
private:
	int selectedProcessIndex = -1;
	std::string selectedPName = "";
	ProcessManager processmanager;
};