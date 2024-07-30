#include <dlfcn.h>
#include <limits.h>

#include <cstdio>
#include <cstdlib>
#include <filesystem>

#include <common/wrapper_helper.h>
#include <qemu-guest-entry.h>

#include <avutil_api/main.h>

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

int av_frame_get_buffer(AVFrame *frame, int align) {
    auto ret = create_empty_ret(av_frame_get_buffer);
    auto a = get_addresses_of_parameters(frame, align);
    qge_CallNativeProc(DynamicApis::pav_frame_get_buffer, a.data(), &ret);
    return ret;
}

AVFrame *av_frame_alloc(void) {
    auto ret = create_empty_ret(av_frame_alloc);
    auto a = get_addresses_of_parameters();
    qge_CallNativeProc(DynamicApis::pav_frame_alloc, a.data(), &ret);
    return ret;
}

int av_strerror(int errnum, char *errbuf, size_t errbuf_size) {
    auto ret = create_empty_ret(av_strerror);
    auto a = get_addresses_of_parameters(errnum, errbuf, errbuf_size);
    qge_CallNativeProc(DynamicApis::pav_strerror, a.data(), &ret);
    return ret;
}

char *av_strdup(const char *s) {
    auto ret = create_empty_ret(av_strdup);
    auto a = get_addresses_of_parameters(s);
    qge_CallNativeProc(DynamicApis::pav_strdup, a.data(), &ret);
    return ret;
}

void av_frame_free(AVFrame **frame) {
    auto a = get_addresses_of_parameters(frame);
    qge_CallNativeProc(DynamicApis::pav_frame_free, a.data(), nullptr);
}

int64_t av_get_default_channel_layout(int nb_channels) {
    auto ret = create_empty_ret(av_get_default_channel_layout);
    auto a = get_addresses_of_parameters(nb_channels);
    qge_CallNativeProc(DynamicApis::pav_get_default_channel_layout, a.data(), &ret);
    return ret;
}