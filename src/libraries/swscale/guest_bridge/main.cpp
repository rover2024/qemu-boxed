#include <dlfcn.h>
#include <limits.h>

#include <cstdio>
#include <cstdlib>
#include <filesystem>

#include <common/wrapper_helper.h>
#include <qemu-guest-entry.h>

#include <api/main.h>

// API Implementions
namespace {

    const char *get_library_path() {
        Dl_info dl_info;
        // 获取当前函数的地址
        if (dladdr((void *) get_library_path, &dl_info)) {
        } else {
            fprintf(stderr, "Error: unable to get library path.\n");
        }
        return dl_info.dli_fname;
    }

    namespace DynamicApis {

// Declare Function Pointers
#define API_HELPER(NAME) void *p##NAME = nullptr;
        API_FOREACH_FUNCTION(API_HELPER)
#undef API_HELPER

        struct initializer {

            initializer() {
                // Load Library
                auto dll = qge_LoadLibrary(
                    (std::filesystem::path(get_library_path()).parent_path() / BRIDGE_LIBRARY_NAME)
                        .c_str(),
                    RTLD_NOW);
                if (!dll) {
                    fprintf(stderr, "Guest Bridge: Load %s error: %s\n", BRIDGE_LIBRARY_NAME,
                            qge_GetErrorMessage());
                    std::abort();
                }

                _hDll = dll;

// Get Function Addresses
#define API_HELPER(NAME)                                                                           \
    {                                                                                              \
        p##NAME = reinterpret_cast<decltype(p##NAME)>(qge_GetProcAddress(dll, "my_" #NAME));       \
        if (!p##NAME) {                                                                            \
            fprintf(stderr, "Guest Bridge: API %s cannot be resolved!\n", #NAME);                  \
            std::abort();                                                                          \
        }                                                                                          \
    }
                API_FOREACH_FUNCTION(API_HELPER)
#undef API_HELPER
            }

            ~initializer() {
                // Kernel with remove at end
                qge_FreeLibrary(_hDll);
            }

            void *_hDll;

        } dummy;

    }

}

unsigned int swscale_version() {
    auto ret = create_empty_ret(swscale_version);
    auto a = get_addresses_of_parameters();
    qge_CallNativeProc(DynamicApis::pswscale_version, a.data(), &ret);
    return ret;
}

const char *swscale_configuration() {
    auto ret = create_empty_ret(swscale_configuration);
    auto a = get_addresses_of_parameters();
    qge_CallNativeProc(DynamicApis::pswscale_configuration, a.data(), &ret);
    return ret;
}

int sws_isSupportedInput(enum AVPixelFormat pix_fmt) {
    auto ret = create_empty_ret(sws_isSupportedInput);
    auto a = get_addresses_of_parameters(pix_fmt);
    qge_CallNativeProc(DynamicApis::psws_isSupportedInput, a.data(), &ret);
    return ret;
}

int sws_isSupportedOutput(enum AVPixelFormat pix_fmt) {
    auto ret = create_empty_ret(sws_isSupportedOutput);
    auto a = get_addresses_of_parameters(pix_fmt);
    qge_CallNativeProc(DynamicApis::psws_isSupportedOutput, a.data(), &ret);
    return ret;
}

const int *sws_get_class() {
    auto ret = create_empty_ret(sws_get_class);
    auto a = get_addresses_of_parameters();
    qge_CallNativeProc(DynamicApis::psws_get_class, a.data(), &ret);
    return ret;
}
