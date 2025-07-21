#include "process_app.h"

bool ProcessManager::killProcess(DWORD pid) {
    HANDLE hProcess = OpenProcess(PROCESS_TERMINATE, FALSE, pid);
    if (hProcess == nullptr) {
        return false;
    }
    BOOL result = TerminateProcess(hProcess, 0);
    
    CloseHandle(hProcess);
    return result != 0;
}


std::vector<Processo> ProcessManager::getAllProcesses() {
        std::vector<Processo> processes;

        HANDLE hSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
        if (hSnapshot == INVALID_HANDLE_VALUE) {
            return processes;
        }

        PROCESSENTRY32 pe32;
        pe32.dwSize = sizeof(PROCESSENTRY32);

        SYSTEM_INFO sysInfo;
        GetSystemInfo(&sysInfo);
        int cpuCount = sysInfo.dwNumberOfProcessors;

        auto currentTime = std::chrono::steady_clock::now();

        if (Process32First(hSnapshot, &pe32)) {
            do {
                Processo proc;
                proc.pid = pe32.th32ProcessID;
                std::wstring ws(pe32.szExeFile);
                std::string str(ws.begin(), ws.end());
                proc.name = str;

                // Utilizzo della memoria
                HANDLE hProcess = OpenProcess(PROCESS_QUERY_INFORMATION | PROCESS_VM_READ, FALSE, pe32.th32ProcessID);
                if (hProcess) {
                    PROCESS_MEMORY_COUNTERS pmc;
                    if (GetProcessMemoryInfo(hProcess, &pmc, sizeof(pmc))) {
                        proc.memoryUsage = pmc.WorkingSetSize;
                    }
                    

                    CloseHandle(hProcess);
                }
                if(proc.memoryUsage != 0)
                processes.push_back(proc);
            } while (Process32Next(hSnapshot, &pe32));
        }

        CloseHandle(hSnapshot);
        return processes;
    
}


bool ProcessManager::KillSameNameProcesses(std::string name) {
    bool killed = true;
    for (size_t i = 0; i < processes.size(); i++) {
        if (processes[i].name == name) {
            if (!this->killProcess(processes[i].pid))
                killed = false;
        }
    } return killed;
}

ProcessManager::ProcessManager() {
    startAutoUpdate();
}

ProcessManager::~ProcessManager() {
    stopAutoUpdate();
}

void ProcessManager::startAutoUpdate() {
    isRunning = true;
    updateThread = std::thread(&ProcessManager::updateLoop, this);
}

void ProcessManager::stopAutoUpdate() {
    isRunning = false;
    if (updateThread.joinable()) {
        updateThread.join();
    }
}

void ProcessManager::updateLoop() {
    while (isRunning) {
        auto newProcesses = getAllProcesses();  
        {
            std::lock_guard<std::mutex> lock(processesMutex);
            processes = std::move(newProcesses);
        }
        std::this_thread::sleep_for(std::chrono::seconds(1));  // Aggiorna ogni 1 secondo
    }
}

std::vector<Processo> ProcessManager::getProcessesSnapshot() {
    std::lock_guard<std::mutex> lock(processesMutex);
    return processes;  
}

