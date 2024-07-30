#include <dlfcn.h>
#include <limits.h>

#include <cstdio>
#include <cstdlib>
#include <filesystem>

#include <common/call_helper.h>

#include <avcodec_api/main.h>

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
#define API_HELPER(NAME) decltype(&::NAME) p##NAME = nullptr;
        API_FOREACH_FUNCTION(API_HELPER)
#undef API_HELPER

        struct initializer {

            initializer() {
                // Load Library
                auto dll = dlopen(
                    (std::filesystem::path(get_library_path()).parent_path() / HOST_LIBRARY_NAME)
                        .c_str(),
                    RTLD_NOW);
                if (!dll) {
                    printf("Host Bridge: Load %s error: %s\n", HOST_LIBRARY_NAME, dlerror());
                    std::abort();
                }

                _hDll = dll;

// Get Function Addresses
#define API_HELPER(NAME)                                                                           \
    {                                                                                              \
        p##NAME = reinterpret_cast<decltype(p##NAME)>(dlsym(dll, #NAME));                          \
        if (!p##NAME) {                                                                            \
            printf("Host Bridge: API %s cannot be resolved!\n", #NAME);                            \
            std::abort();                                                                          \
        }                                                                                          \
    }
                API_FOREACH_FUNCTION(API_HELPER)
#undef API_HELPER
            }

            ~initializer() {
                // Kernel with remove at end
                dlclose(_hDll);
            }

            void *_hDll;

        } dummy;

    }
}

#define API_HELPER(X)                                                                              \
    extern "C" __attribute__((visibility("default"))) void my_##X(void *args, void *ret) {         \
        call_function2(DynamicApis::p##X, (void **) args, ret);                                    \
    }
API_FOREACH_FUNCTION(API_HELPER)
#undef API_HELPER