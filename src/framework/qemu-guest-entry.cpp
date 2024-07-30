#include <cstdio>

#include "qemu-guest-entry.h"

#include <common/syscall_helper.h>

static const uint64_t MagicCallNumber = 114514;

enum MagicCallType {
    LoadLibrary = 0x1,
    FreeLibrary,
    GetProcAddress,
    GetErrorMessage,
    CallNativeProc,
    NextCallFinished,

    UserCall = 0x1000,
};

void *qge_LoadLibrary(const char *path, int flags) {
    void *a[] = {
        const_cast<char *>(path),
        &flags,
    };
    return (void *) syscall2(MagicCallNumber, (void *) LoadLibrary, a);
}

void qge_FreeLibrary(void *handle) {
    void *a[] = {
        handle,
    };
    syscall2(MagicCallNumber, (void *) FreeLibrary, a);
}

void *qge_GetProcAddress(void *handle, const char *name) {
    void *a[] = {
        handle,
        const_cast<char *>(name),
    };
    return (void *) syscall2(MagicCallNumber, (void *) GetProcAddress, a);
}

char *qge_GetErrorMessage() {
    return (char *) syscall1(MagicCallNumber, (void *) GetErrorMessage);
}

int qge_CallNativeProc(void *func, void *args, void *ret) {
    void *a[] = {
        func,
        args,
        ret,
    };
    uintptr_t next_call[4];

    {
        if (syscall3(MagicCallNumber, (void *) CallNativeProc, a, next_call) == 0) {
            return 0;
        }
        auto args = reinterpret_cast<uintptr_t *>(next_call[2]);
        switch (next_call[1]) {
            case 3: {
                auto func = reinterpret_cast<intptr_t (*)(int[], int, int)>(next_call[0]);
                if (next_call[3]) {
                    *(intptr_t *) next_call[3] = func((int *) args[0], args[1], args[2]);
                } else {
                    func((int *) args[0], args[1], args[2]);
                }
                break;
            }
            default:
                break;
        }
        syscall1(MagicCallNumber, (void *) NextCallFinished);
    }
    return 0;
}