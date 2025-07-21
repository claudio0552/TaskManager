#pragma once
#include <windows.h>
#include <TlHelp32.h>
#include <Psapi.h>
#include <vector>
#include <string>
#include <thread>
#include <mutex>
#include <unordered_map>
#include <atomic>

struct Processo {
    DWORD pid = 0;
    std::string name;
    SIZE_T memoryUsage = 0;
};




class ProcessManager {
public:
    ProcessManager();
    ~ProcessManager();
    bool killProcess(DWORD pid);
    bool KillSameNameProcesses(std::string name);
    void startAutoUpdate();  // Avvia l'aggiornamento automatico
    void stopAutoUpdate();   // Ferma l'aggiornamento
    std::vector<Processo> getProcessesSnapshot();  // Copia dei processi

private:
    std::vector<Processo> getAllProcesses();  // retrieava i processi
     

    void updateLoop();  // Loop 

    std::vector<Processo> processes;
    std::mutex processesMutex;
    std::atomic<bool> isRunning{ false };
    std::thread updateThread;
};