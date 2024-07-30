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

unsigned int avdevice_version(void) {
    auto ret = create_empty_ret(avdevice_version);
    auto a = get_addresses_of_parameters();
    qge_CallNativeProc(DynamicApis::pavdevice_version, a.data(), &ret);
    return ret;
}

const char *avdevice_configuration(void) {
    auto ret = create_empty_ret(avdevice_configuration);
    auto a = get_addresses_of_parameters();
    qge_CallNativeProc(DynamicApis::pavdevice_configuration, a.data(), &ret);
    return ret;
}

void avdevice_register_all(void) {
    auto a = get_addresses_of_parameters();
    qge_CallNativeProc(DynamicApis::pavdevice_register_all, a.data(), nullptr);
}

const AVInputFormat *av_input_audio_device_next(const AVInputFormat *d) {
    auto ret = create_empty_ret(av_input_audio_device_next);
    auto a = get_addresses_of_parameters(d);
    qge_CallNativeProc(DynamicApis::pav_input_audio_device_next, a.data(), &ret);
    return ret;
}

const AVInputFormat *av_input_video_device_next(const AVInputFormat *d) {
    auto ret = create_empty_ret(av_input_video_device_next);
    auto a = get_addresses_of_parameters(d);
    qge_CallNativeProc(DynamicApis::pav_input_video_device_next, a.data(), &ret);
    return ret;
}

const AVOutputFormat *av_output_audio_device_next(const AVOutputFormat *d) {
    auto ret = create_empty_ret(av_output_audio_device_next);
    auto a = get_addresses_of_parameters(d);
    qge_CallNativeProc(DynamicApis::pav_output_audio_device_next, a.data(), &ret);
    return ret;
}

const AVOutputFormat *av_output_video_device_next(const AVOutputFormat *d) {
    auto ret = create_empty_ret(av_output_video_device_next);
    auto a = get_addresses_of_parameters(d);
    qge_CallNativeProc(DynamicApis::pav_output_video_device_next, a.data(), &ret);
    return ret;
}

void avdevice_free_list_devices(AVDeviceInfoList **device_list) {
    auto a = get_addresses_of_parameters(device_list);
    qge_CallNativeProc(DynamicApis::pavdevice_free_list_devices, a.data(), nullptr);
}

int avdevice_list_input_sources(const AVInputFormat *device, const char *device_name,
                                AVDictionary *device_options, AVDeviceInfoList **device_list) {
    auto ret = create_empty_ret(avdevice_list_input_sources);
    auto a = get_addresses_of_parameters(device, device_name, device_options, device_list);
    qge_CallNativeProc(DynamicApis::pavdevice_list_input_sources, a.data(), &ret);
    return ret;
}

int avdevice_list_output_sinks(const AVOutputFormat *device, const char *device_name,
                               AVDictionary *device_options, AVDeviceInfoList **device_list) {
    auto ret = create_empty_ret(avdevice_list_output_sinks);
    auto a = get_addresses_of_parameters(device, device_name, device_options, device_list);
    qge_CallNativeProc(DynamicApis::pavdevice_list_output_sinks, a.data(), &ret);
    return ret;
}
