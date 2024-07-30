#ifndef QEMU_GUEST_ENTRY_H
#define QEMU_GUEST_ENTRY_H

#ifdef __cplusplus
extern "C" {
#endif

#define QGE_DECLSPEC __attribute__((visibility("default")))

QGE_DECLSPEC void *qge_LoadLibrary(const char *path, int flags);

QGE_DECLSPEC void qge_FreeLibrary(void *handle);

QGE_DECLSPEC void *qge_GetProcAddress(void *handle, const char *name);

QGE_DECLSPEC char *qge_GetErrorMessage();

QGE_DECLSPEC int qge_CallNativeProc(void *func, void *args, void *ret);

#ifdef __cplusplus
}
#endif

#endif // QEMU_GUEST_ENTRY_H
