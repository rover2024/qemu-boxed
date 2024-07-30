#include <dlfcn.h>
#include <limits.h>

#include <cstdio>
#include <cstdlib>
#include <filesystem>

#include <common/wrapper_helper.h>
#include <qemu-guest-entry.h>

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

int avcodec_parameters_from_context(AVCodecParameters *par, const AVCodecContext *codec) {
    auto ret = create_empty_ret(avcodec_parameters_from_context);
    auto a = get_addresses_of_parameters(par, codec);
    qge_CallNativeProc(DynamicApis::pavcodec_parameters_from_context, a.data(), &ret);
    return ret;
}

int avcodec_parameters_to_context(AVCodecContext *codec, const AVCodecParameters *par) {
    auto ret = create_empty_ret(avcodec_parameters_to_context);
    auto a = get_addresses_of_parameters(codec, par);
    qge_CallNativeProc(DynamicApis::pavcodec_parameters_to_context, a.data(), &ret);
    return ret;
}

const AVCodec *avcodec_find_encoder(enum AVCodecID id) {
    auto ret = create_empty_ret(avcodec_find_encoder);
    auto a = get_addresses_of_parameters(id);
    qge_CallNativeProc(DynamicApis::pavcodec_find_encoder, a.data(), &ret);
    return ret;
}

void avcodec_free_context(AVCodecContext **avctx) {
    auto a = get_addresses_of_parameters(avctx);
    qge_CallNativeProc(DynamicApis::pavcodec_free_context, a.data(), nullptr);
}

int avcodec_receive_packet(AVCodecContext *avctx, AVPacket *avpkt) {
    auto ret = create_empty_ret(avcodec_receive_packet);
    auto a = get_addresses_of_parameters(avctx, avpkt);
    qge_CallNativeProc(DynamicApis::pavcodec_receive_packet, a.data(), &ret);
    return ret;
}

int avcodec_close(AVCodecContext *avctx) {
    auto ret = create_empty_ret(avcodec_close);
    auto a = get_addresses_of_parameters(avctx);
    qge_CallNativeProc(DynamicApis::pavcodec_close, a.data(), &ret);
    return ret;
}

int avcodec_send_frame(AVCodecContext *avctx, const AVFrame *frame) {
    auto ret = create_empty_ret(avcodec_send_frame);
    auto a = get_addresses_of_parameters(avctx, frame);
    qge_CallNativeProc(DynamicApis::pavcodec_send_frame, a.data(), &ret);
    return ret;
}

int avcodec_send_packet(AVCodecContext *avctx, const AVPacket *avpkt) {
    auto ret = create_empty_ret(avcodec_send_packet);
    auto a = get_addresses_of_parameters(avctx, avpkt);
    qge_CallNativeProc(DynamicApis::pavcodec_send_packet, a.data(), &ret);
    return ret;
}

int avcodec_receive_frame(AVCodecContext *avctx, AVFrame *frame) {
    auto ret = create_empty_ret(avcodec_receive_frame);
    auto a = get_addresses_of_parameters(avctx, frame);
    qge_CallNativeProc(DynamicApis::pavcodec_receive_frame, a.data(), &ret);
    return ret;
}

void av_init_packet(AVPacket *pkt) {
    auto a = get_addresses_of_parameters(pkt);
    qge_CallNativeProc(DynamicApis::pav_init_packet, a.data(), nullptr);
}

int avcodec_open2(AVCodecContext *avctx, const AVCodec *codec, AVDictionary **options) {
    auto ret = create_empty_ret(avcodec_open2);
    auto a = get_addresses_of_parameters(avctx, codec, options);
    qge_CallNativeProc(DynamicApis::pavcodec_open2, a.data(), &ret);
    return ret;
}

void av_packet_unref(AVPacket *pkt) {
    auto a = get_addresses_of_parameters(pkt);
    qge_CallNativeProc(DynamicApis::pav_packet_unref, a.data(), nullptr);
}

AVCodecContext *avcodec_alloc_context3(const AVCodec *codec) {
    auto ret = create_empty_ret(avcodec_alloc_context3);
    auto a = get_addresses_of_parameters(codec);
    qge_CallNativeProc(DynamicApis::pavcodec_alloc_context3, a.data(), &ret);
    return ret;
}