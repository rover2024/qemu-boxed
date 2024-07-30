#include <dlfcn.h>
#include <limits.h>

#include <cstdio>
#include <cstdlib>
#include <filesystem>

#include <common/wrapper_helper.h>
#include <qemu-guest-entry.h>

#include <avformat_api/main.h>

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

int avformat_open_input(AVFormatContext **ps, const char *url, const AVInputFormat *fmt,
                        AVDictionary **options) {
    auto ret = create_empty_ret(avformat_open_input);
    auto a = get_addresses_of_parameters(ps, url, fmt, options);
    qge_CallNativeProc(DynamicApis::pavformat_open_input, a.data(), &ret);
    return ret;
}

enum AVCodecID av_guess_codec(const AVOutputFormat *fmt, const char *short_name,
                              const char *filename, const char *mime_type, enum AVMediaType type) {
    auto ret = create_empty_ret(av_guess_codec);
    auto a = get_addresses_of_parameters(fmt, short_name, filename, mime_type, type);
    qge_CallNativeProc(DynamicApis::pav_guess_codec, a.data(), &ret);
    return ret;
}

int av_find_best_stream(AVFormatContext *ic, enum AVMediaType type, int wanted_stream_nb,
                        int related_stream, const AVCodec **decoder_ret, int flags) {
    auto ret = create_empty_ret(av_find_best_stream);
    auto a =
        get_addresses_of_parameters(ic, type, wanted_stream_nb, related_stream, decoder_ret, flags);
    qge_CallNativeProc(DynamicApis::pav_find_best_stream, a.data(), &ret);
    return ret;
}

void avformat_free_context(AVFormatContext *s) {
    auto a = get_addresses_of_parameters(s);
    qge_CallNativeProc(DynamicApis::pavformat_free_context, a.data(), nullptr);
}

int avio_open(AVIOContext **s, const char *url, int flags) {
    auto ret = create_empty_ret(avio_open);
    auto a = get_addresses_of_parameters(s, url, flags);
    qge_CallNativeProc(DynamicApis::pavio_open, a.data(), &ret);
    return ret;
}

const AVOutputFormat *av_guess_format(const char *short_name, const char *filename,
                                      const char *mime_type) {
    auto ret = create_empty_ret(av_guess_format);
    auto a = get_addresses_of_parameters(short_name, filename, mime_type);
    qge_CallNativeProc(DynamicApis::pav_guess_format, a.data(), &ret);
    return ret;
}

int avformat_write_header(AVFormatContext *s, AVDictionary **options) {
    auto ret = create_empty_ret(avformat_write_header);
    auto a = get_addresses_of_parameters(s, options);
    qge_CallNativeProc(DynamicApis::pavformat_write_header, a.data(), &ret);
    return ret;
}

int avio_closep(AVIOContext **s) {
    auto ret = create_empty_ret(avio_closep);
    auto a = get_addresses_of_parameters(s);
    qge_CallNativeProc(DynamicApis::pavio_closep, a.data(), &ret);
    return ret;
}

int av_read_frame(AVFormatContext *s, AVPacket *pkt) {
    auto ret = create_empty_ret(av_read_frame);
    auto a = get_addresses_of_parameters(s, pkt);
    qge_CallNativeProc(DynamicApis::pav_read_frame, a.data(), &ret);
    return ret;
}

AVFormatContext *avformat_alloc_context(void) {
    auto ret = create_empty_ret(avformat_alloc_context);
    auto a = get_addresses_of_parameters();
    qge_CallNativeProc(DynamicApis::pavformat_alloc_context, a.data(), &ret);
    return ret;
}

int av_write_frame(AVFormatContext *s, AVPacket *pkt) {
    auto ret = create_empty_ret(av_write_frame);
    auto a = get_addresses_of_parameters(s, pkt);
    qge_CallNativeProc(DynamicApis::pav_write_frame, a.data(), &ret);
    return ret;
}

AVStream *avformat_new_stream(AVFormatContext *s, const AVCodec *c) {
    auto ret = create_empty_ret(avformat_new_stream);
    auto a = get_addresses_of_parameters(s, c);
    qge_CallNativeProc(DynamicApis::pavformat_new_stream, a.data(), &ret);
    return ret;
}

int av_write_trailer(AVFormatContext *s) {
    auto ret = create_empty_ret(av_write_trailer);
    auto a = get_addresses_of_parameters(s);
    qge_CallNativeProc(DynamicApis::pav_write_trailer, a.data(), &ret);
    return ret;
}

int avformat_find_stream_info(AVFormatContext *ic, AVDictionary **options) {
    auto ret = create_empty_ret(avformat_find_stream_info);
    auto a = get_addresses_of_parameters(ic, options);
    qge_CallNativeProc(DynamicApis::pavformat_find_stream_info, a.data(), &ret);
    return ret;
}