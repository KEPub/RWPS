
#include <windows.h>
#include <string>
#include <sstream>
#include <vector>
#include <iostream>

std::string WideStringToString(const std::wstring& wstr) {
    if (wstr.empty()) return std::string();
    int sizeNeeded = WideCharToMultiByte(CP_UTF8, 0, &wstr[0], (int)wstr.size(), NULL, 0, NULL, NULL);
    std::string str(sizeNeeded, 0);
    WideCharToMultiByte(CP_UTF8, 0, &wstr[0], (int)wstr.size(), &str[0], sizeNeeded, NULL, NULL);
    return str;
}

void ReadFromPipe(HANDLE pipe, std::string& output) {
    DWORD bytesRead;
    CHAR buffer[4096];
    while (ReadFile(pipe, buffer, sizeof(buffer) - 1, &bytesRead, NULL) && bytesRead > 0) {
        buffer[bytesRead] = '\0';
        output += buffer;
    }
}

extern "C" __declspec(dllexport) void CALLBACK mimi(HWND hwnd, HINSTANCE hinst, LPSTR lpszCmdLine, int nCmdShow) {
    // Command to execute in PowerShell

    std::string command = "powershell.exe -Command \"echo Invoke-Mimikatz\"";

    // Convert the command to a wide string
    std::wstring wcommand(command.begin(), command.end());

    // Create pipes for STDOUT and STDERR redirection
    HANDLE hStdOutRead, hStdOutWrite;
    HANDLE hStdErrRead, hStdErrWrite;
    SECURITY_ATTRIBUTES sa = { sizeof(SECURITY_ATTRIBUTES), NULL, TRUE };
    CreatePipe(&hStdOutRead, &hStdOutWrite, &sa, 0);
    SetHandleInformation(hStdOutRead, HANDLE_FLAG_INHERIT, 0);
    CreatePipe(&hStdErrRead, &hStdErrWrite, &sa, 0);
    SetHandleInformation(hStdErrRead, HANDLE_FLAG_INHERIT, 0);

    // Setup the STARTUPINFO structure
    STARTUPINFOW si = { sizeof(si) };
    si.dwFlags = STARTF_USESTDHANDLES;
    si.hStdOutput = hStdOutWrite;
    si.hStdError = hStdErrWrite;
    PROCESS_INFORMATION pi;

    // Create the process to execute the PowerShell command
    if (CreateProcessW(
        NULL,
        &wcommand[0],
        NULL,
        NULL,
        TRUE,
        CREATE_NO_WINDOW,
        NULL,
        NULL,
        &si,
        &pi
    )) {
        // Close the write ends of the pipes, we don't need them anymore
        CloseHandle(hStdOutWrite);
        CloseHandle(hStdErrWrite);

        // Capture the output
        std::string output, errorOutput;
        ReadFromPipe(hStdOutRead, output);
        ReadFromPipe(hStdErrRead, errorOutput);

        // Wait until the process exits
        WaitForSingleObject(pi.hProcess, INFINITE);

        DWORD exitCode;
        if (GetExitCodeProcess(pi.hProcess, &exitCode)) {
            if (exitCode != 0) {
                output += "\n\nError Output:\n" + errorOutput;
            }
        }
        else {
            output += "\n\nFailed to get exit code.";
        }

        // Close process and thread handles
        CloseHandle(pi.hProcess);
        CloseHandle(pi.hThread);

        // Display the captured output
        MessageBoxA(NULL, output.c_str(), "Output", MB_OK | MB_ICONINFORMATION);
    }
    else {
        std::cerr << "Failed to start PowerShell session. Error code: " << GetLastError() << std::endl;
    }

    // Close the read ends of the pipes
    CloseHandle(hStdOutRead);
    CloseHandle(hStdErrRead);
}

extern "C" __declspec(dllexport) void CALLBACK eicar(HWND hwnd, HINSTANCE hinst, LPSTR lpszCmdLine, int nCmdShow) {
    const char* eicarSt = R"(X5O!P%@AP[4\PZX54(P^)7CC)7}$EICAR-STANDARD-ANTIVIRUS-TEST-FILE!$H+H*)";
    MessageBoxA(NULL, eicarSt, "EICAR Test", MB_OK | MB_ICONINFORMATION);
}

BOOL APIENTRY DllMain(HMODULE hModule, DWORD ul_reason_for_call, LPVOID lpReserved) {
    return TRUE;
}