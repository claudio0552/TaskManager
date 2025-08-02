#pragma once
#include "process_app.h"
#include "imgui.h"

inline bool compare(const Processo& a, const Processo& b) {
	return a.memoryUsage < b.memoryUsage;
}

inline bool comparebyName(const Processo& a, const Processo& b) {
	return a.name < b.name;
}

class ImGuiApp {
public:
	ImGuiApp();
	void PrimaFinestra();
	void Sbarra();
	
private:
	int selectedProcessIndex = -1;
	std::string selectedPName = "";
	ProcessManager processmanager;
};