#pragma once
#include "Includes.hpp"
#include "DbgLog.hpp"

namespace  BE
{
    namespace Listener
    {
        class Listener
        {
        public:
            Listener();
            ~Listener();
            static Listener* GetInstance();
            bool Init(), Uninit();
        private:
            bool detour_DriverConnection(bool Status);
            static NTSTATUS NTAPI NtCreateFile_Hook(PHANDLE FileHandle, ACCESS_MASK DesiredAccess, POBJECT_ATTRIBUTES ObjectAttributes, PIO_STATUS_BLOCK IoStatusBlock, PLARGE_INTEGER AllocationSize, ULONG FileAttributes, ULONG ShareAccess, ULONG CreateDisposition, ULONG CreateOptions, PVOID EaBuffer, ULONG EaLength);
            static NTSTATUS NTAPI Listener::ZwReadFile_Hook(HANDLE FileHandle, HANDLE Event, PIO_APC_ROUTINE  ApcRoutine, PVOID ApcContext, PIO_STATUS_BLOCK IoStatusBlock, PVOID Buffer, ULONG Length, PLARGE_INTEGER   ByteOffset, PULONG Key);
            static NTSTATUS NTAPI Listener::ZwWriteFile_Hook(HANDLE FileHandle, HANDLE Event, PIO_APC_ROUTINE  ApcRoutine, PVOID ApcContext, PIO_STATUS_BLOCK IoStatusBlock, PVOID Buffer, ULONG Length, PLARGE_INTEGER   ByteOffset, PULONG Key);
            static DWORD WINAPI Listener::CloseOldPipe_Thread(LPVOID lpParam);
        protected:
            typedef NTSTATUS(NTAPI*p_NtQueryInformationThread)(HANDLE ThreadHandle, THREADINFOCLASS ThreadInformationClass, PVOID ThreadInformation, ULONG ThreadInformationLength, PULONG ReturnLength);
            typedef NTSTATUS(NTAPI*p_NtCreateFile)(PHANDLE FileHandle, ACCESS_MASK DesiredAccess, POBJECT_ATTRIBUTES ObjectAttributes, PIO_STATUS_BLOCK IoStatusBlock, PLARGE_INTEGER AllocationSize, ULONG FileAttributes, ULONG ShareAccess, ULONG CreateDisposition, ULONG CreateOptions, PVOID EaBuffer, ULONG EaLength);
            typedef NTSTATUS(NTAPI*p_ZwReadFile)(HANDLE FileHandle, HANDLE Event, PIO_APC_ROUTINE ApcRoutine, PVOID ApcContext, PIO_STATUS_BLOCK IoStatusBlock, PVOID Buffer, ULONG Length, PLARGE_INTEGER  ByteOffset, PULONG Key);
            typedef NTSTATUS(NTAPI*p_ZwWriteFile)(HANDLE FileHandle, HANDLE Event, PIO_APC_ROUTINE  ApcRoutine, PVOID ApcContext, PIO_STATUS_BLOCK IoStatusBlock, PVOID Buffer, ULONG Length, PLARGE_INTEGER ByteOffset, PULONG Key);
            typedef VOID(WINAPI*p_RtlInitUnicodeString)(PUNICODE_STRING Object, LPCWSTR String);
            typedef NTSTATUS(NTAPI*p_NtQuerySystemInformation)(SYSTEM_INFORMATION_CLASS SystemInformationClass, PVOID SystemInformation, ULONG SystemInformationLength, PULONG ReturnLength);
            typedef NTSTATUS(NTAPI*p_NtQueryObject)(_In_opt_ HANDLE Handle, _In_ OBJECT_INFORMATION_CLASS ObjectInformationClass, _Out_writes_bytes_opt_(ObjectInformationLength) PVOID ObjectInformation, _In_ ULONG ObjectInformationLength, _Out_opt_ PULONG ReturnLength);


            static p_NtCreateFile o_NtCreateFile;
            static p_ZwReadFile o_ZwReadFile;
            static p_ZwWriteFile o_ZwWriteFile;
            static p_NtQuerySystemInformation o_NtQuerySystemInformation;
            static p_NtQueryObject o_NtQueryObject;
            static Listener* Instance;
        };
    }
}