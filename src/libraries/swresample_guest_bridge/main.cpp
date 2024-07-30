#include <dlfcn.h>
#include <limits.h>

#include <cstdio>
#include <cstdlib>
#include <filesystem>

#include <common/wrapper_helper.h>
#include <qemu-guest-entry.h>

#include <swresample_api/main.h>

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

int swr_convert(struct SwrContext *s, uint8_t **out, int out_count, const uint8_t **in,
                int in_count) {
    auto ret = create_empty_ret(swr_convert);
    auto a = get_addresses_of_parameters(s, out, out_count, in, in_count);
    qge_CallNativeProc(DynamicApis::pswr_convert, a.data(), &ret);
    return ret;
}

struct SwrContext *swr_alloc_set_opts(struct SwrContext *s, int64_t out_ch_layout,
                                      enum AVSampleFormat out_sample_fmt, int out_sample_rate,
                                      int64_t in_ch_layout, enum AVSampleFormat in_sample_fmt,
                                      int in_sample_rate, int log_offset, void *log_ctx) {
    auto ret = create_empty_ret(swr_alloc_set_opts);
    auto a =
        get_addresses_of_parameters(s, out_ch_layout, out_sample_fmt, out_sample_rate, in_ch_layout,
                                    in_sample_fmt, in_sample_rate, log_offset, log_ctx);
    qge_CallNativeProc(DynamicApis::pswr_alloc_set_opts, a.data(), &ret);
    return ret;
}

void swr_free(struct SwrContext **s) {
    auto a = get_addresses_of_parameters(s);
    qge_CallNativeProc(DynamicApis::pswr_free, a.data(), nullptr);
}

int swr_init(struct SwrContext *s) {
    auto ret = create_empty_ret(swr_init);
    auto a = get_addresses_of_parameters(s);
    qge_CallNativeProc(DynamicApis::pswr_init, a.data(), &ret);
    return ret;
}