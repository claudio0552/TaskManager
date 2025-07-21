#pragma once
#include "imgui_app.h"
#include "imgui_spectrum.h"
#include <algorithm>
#include <iostream>

ImGuiApp::ImGuiApp() {}


void ImGuiApp::secondWind() {
	ImGui::Begin("Gestisci Processi", nullptr, ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoTitleBar);
	
	static std::string message = "";
	static int messageFrames = 0;
	if (ImGui::Button("Chiudi processo")) {
		if (selectedPName != "") {
			if (processmanager.KillSameNameProcesses(selectedPName)) {
				message = "Processo terminato con successo";
				messageFrames = 180;
			}
			else {
				message = "Errore: Impossibie terminare il processo";
				messageFrames = 180;
			}
		}
		else {
			message = "Seleziona prima un processo";
			messageFrames = 180;
		}
	}

	if (messageFrames > 0) {
		ImGui::Text("%s", message.c_str());
		messageFrames--;
	}


	ImGui::End();
}




void ImGuiApp::render() {
	ImGui::Begin("Gestione processi", nullptr, ImGuiWindowFlags_NoTitleBar|ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoResize );
	static bool sortByMemory = true;
	if (ImGui::Button(sortByMemory ? "Ordine per PID ▲" : "Ordine per memoria ▲")) {
		sortByMemory = !sortByMemory;
	}

	if (ImGui::BeginTable("Processes", 3, ImGuiTableFlags_Borders | ImGuiTableFlags_RowBg)) {
		ImGui::TableSetupColumn("PID");
		ImGui::TableSetupColumn("Nome");
	
		ImGui::TableSetupColumn("Memoria (MB)");
		ImGui::TableHeadersRow();

		auto processes = processmanager.getProcessesSnapshot();

		if (sortByMemory) {
			std::sort(processes.begin(), processes.end(), compare);
		}

		



		for (int i = 0; i < processes.size(); i++) {
			
				const auto& proc = processes[i];
				ImGui::TableNextRow();
				ImGui::TableSetColumnIndex(0);
				ImGui::PushID(i);
				if (ImGui::Selectable(std::to_string(proc.pid).c_str(), selectedProcessIndex == i, ImGuiSelectableFlags_SpanAllColumns)){
					
					if (selectedProcessIndex == i) {
						selectedProcessIndex = -1;
						selectedPName = "";
					}
					else {
						selectedProcessIndex = i;
						selectedPName = proc.name;
					}
				}
				ImGui::PopID();
				
				ImGui::TableSetColumnIndex(1);
				ImGui::Text("%s", proc.name.c_str());
				ImGui::TableSetColumnIndex(2);
				ImGui::Text("%lu", (proc.memoryUsage / 1024) / 1024);
			
		}
		ImGui::EndTable();
	}
	ImGui::End();
}