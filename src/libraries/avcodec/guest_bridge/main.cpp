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

const AVCodec *av_codec_iterate(void **opaque) {
    auto ret = create_empty_ret(av_codec_iterate);
    auto a = get_addresses_of_parameters(opaque);
    qge_CallNativeProc(DynamicApis::pav_codec_iterate, a.data(), &ret);
    return ret;
}

const AVCodec *avcodec_find_decoder(enum AVCodecID id) {
    auto ret = create_empty_ret(avcodec_find_decoder);
    auto a = get_addresses_of_parameters(id);
    qge_CallNativeProc(DynamicApis::pavcodec_find_decoder, a.data(), &ret);
    return ret;
}

const AVCodec *avcodec_find_decoder_by_name(const char *name) {
    auto ret = create_empty_ret(avcodec_find_decoder_by_name);
    auto a = get_addresses_of_parameters(name);
    qge_CallNativeProc(DynamicApis::pavcodec_find_decoder_by_name, a.data(), &ret);
    return ret;
}

const AVCodec *avcodec_find_encoder(enum AVCodecID id) {
    auto ret = create_empty_ret(avcodec_find_encoder);
    auto a = get_addresses_of_parameters(id);
    qge_CallNativeProc(DynamicApis::pavcodec_find_encoder, a.data(), &ret);
    return ret;
}

const AVCodec *avcodec_find_encoder_by_name(const char *name) {
    auto ret = create_empty_ret(avcodec_find_encoder_by_name);
    auto a = get_addresses_of_parameters(name);
    qge_CallNativeProc(DynamicApis::pavcodec_find_encoder_by_name, a.data(), &ret);
    return ret;
}

int av_codec_is_encoder(const AVCodec *codec) {
    auto ret = create_empty_ret(av_codec_is_encoder);
    auto a = get_addresses_of_parameters(codec);
    qge_CallNativeProc(DynamicApis::pav_codec_is_encoder, a.data(), &ret);
    return ret;
}

int av_codec_is_decoder(const AVCodec *codec) {
    auto ret = create_empty_ret(av_codec_is_decoder);
    auto a = get_addresses_of_parameters(codec);
    qge_CallNativeProc(DynamicApis::pav_codec_is_decoder, a.data(), &ret);
    return ret;
}

const AVCodecHWConfig *avcodec_get_hw_config(const AVCodec *codec, int index) {
    auto ret = create_empty_ret(avcodec_get_hw_config);
    auto a = get_addresses_of_parameters(codec, index);
    qge_CallNativeProc(DynamicApis::pavcodec_get_hw_config, a.data(), &ret);
    return ret;
}

const char *avcodec_get_name(enum AVCodecID id) {
    auto ret = create_empty_ret(avcodec_get_name);
    auto a = get_addresses_of_parameters(id);
    qge_CallNativeProc(DynamicApis::pavcodec_get_name, a.data(), &ret);
    return ret;
}

int av_get_exact_bits_per_sample(enum AVCodecID codec_id) {
    auto ret = create_empty_ret(av_get_exact_bits_per_sample);
    auto a = get_addresses_of_parameters(codec_id);
    qge_CallNativeProc(DynamicApis::pav_get_exact_bits_per_sample, a.data(), &ret);
    return ret;
}

const AVCodecDescriptor *avcodec_descriptor_get(enum AVCodecID id) {
    auto ret = create_empty_ret(avcodec_descriptor_get);
    auto a = get_addresses_of_parameters(id);
    qge_CallNativeProc(DynamicApis::pavcodec_descriptor_get, a.data(), &ret);
    return ret;
}

const AVCodecDescriptor *avcodec_descriptor_next(const AVCodecDescriptor *prev) {
    auto ret = create_empty_ret(avcodec_descriptor_next);
    auto a = get_addresses_of_parameters(prev);
    qge_CallNativeProc(DynamicApis::pavcodec_descriptor_next, a.data(), &ret);
    return ret;
}

const AVCodecDescriptor *avcodec_descriptor_get_by_name(const char *name) {
    auto ret = create_empty_ret(avcodec_descriptor_get_by_name);
    auto a = get_addresses_of_parameters(name);
    qge_CallNativeProc(DynamicApis::pavcodec_descriptor_get_by_name, a.data(), &ret);
    return ret;
}

AVCodecParameters *avcodec_parameters_alloc() {
    auto ret = create_empty_ret(avcodec_parameters_alloc);
    auto a = get_addresses_of_parameters();
    qge_CallNativeProc(DynamicApis::pavcodec_parameters_alloc, a.data(), &ret);
    return ret;
}

void avcodec_parameters_free(AVCodecParameters **par) {
    auto a = get_addresses_of_parameters(par);
    qge_CallNativeProc(DynamicApis::pavcodec_parameters_free, a.data(), nullptr);
}

int avcodec_parameters_copy(AVCodecParameters *dst, const AVCodecParameters *src) {
    auto ret = create_empty_ret(avcodec_parameters_copy);
    auto a = get_addresses_of_parameters(dst, src);
    qge_CallNativeProc(DynamicApis::pavcodec_parameters_copy, a.data(), &ret);
    return ret;
}

AVPacket *av_packet_alloc() {
    auto ret = create_empty_ret(av_packet_alloc);
    auto a = get_addresses_of_parameters();
    qge_CallNativeProc(DynamicApis::pav_packet_alloc, a.data(), &ret);
    return ret;
}

void av_packet_free(AVPacket **pkt) {
    auto a = get_addresses_of_parameters(pkt);
    qge_CallNativeProc(DynamicApis::pav_packet_free, a.data(), nullptr);
}

uint8_t *av_packet_new_side_data(AVPacket *pkt, enum AVPacketSideDataType type, size_t size) {
    auto ret = create_empty_ret(av_packet_new_side_data);
    auto a = get_addresses_of_parameters(pkt, type, size);
    qge_CallNativeProc(DynamicApis::pav_packet_new_side_data, a.data(), &ret);
    return ret;
}

uint8_t *av_packet_get_side_data(const AVPacket *pkt, enum AVPacketSideDataType type,
                                 size_t *size) {
    auto ret = create_empty_ret(av_packet_get_side_data);
    auto a = get_addresses_of_parameters(pkt, type, size);
    qge_CallNativeProc(DynamicApis::pav_packet_get_side_data, a.data(), &ret);
    return ret;
}

int av_packet_ref(AVPacket *dst, const AVPacket *src) {
    auto ret = create_empty_ret(av_packet_ref);
    auto a = get_addresses_of_parameters(dst, src);
    qge_CallNativeProc(DynamicApis::pav_packet_ref, a.data(), &ret);
    return ret;
}

void av_packet_unref(AVPacket *pkt) {
    auto a = get_addresses_of_parameters(pkt);
    qge_CallNativeProc(DynamicApis::pav_packet_unref, a.data(), nullptr);
}

void av_packet_move_ref(AVPacket *dst, AVPacket *src) {
    auto a = get_addresses_of_parameters(dst, src);
    qge_CallNativeProc(DynamicApis::pav_packet_move_ref, a.data(), nullptr);
}

int av_packet_make_refcounted(AVPacket *pkt) {
    auto ret = create_empty_ret(av_packet_make_refcounted);
    auto a = get_addresses_of_parameters(pkt);
    qge_CallNativeProc(DynamicApis::pav_packet_make_refcounted, a.data(), &ret);
    return ret;
}

void av_packet_rescale_ts(AVPacket *pkt, int tb_src, int tb_dst) {
    auto a = get_addresses_of_parameters(pkt, tb_src, tb_dst);
    qge_CallNativeProc(DynamicApis::pav_packet_rescale_ts, a.data(), nullptr);
}

unsigned int avcodec_version() {
    auto ret = create_empty_ret(avcodec_version);
    auto a = get_addresses_of_parameters();
    qge_CallNativeProc(DynamicApis::pavcodec_version, a.data(), &ret);
    return ret;
}

const char *avcodec_configuration() {
    auto ret = create_empty_ret(avcodec_configuration);
    auto a = get_addresses_of_parameters();
    qge_CallNativeProc(DynamicApis::pavcodec_configuration, a.data(), &ret);
    return ret;
}

AVCodecContext *avcodec_alloc_context3(const AVCodec *codec) {
    auto ret = create_empty_ret(avcodec_alloc_context3);
    auto a = get_addresses_of_parameters(codec);
    qge_CallNativeProc(DynamicApis::pavcodec_alloc_context3, a.data(), &ret);
    return ret;
}

void avcodec_free_context(AVCodecContext **avctx) {
    auto a = get_addresses_of_parameters(avctx);
    qge_CallNativeProc(DynamicApis::pavcodec_free_context, a.data(), nullptr);
}

const int *avcodec_get_class() {
    auto ret = create_empty_ret(avcodec_get_class);
    auto a = get_addresses_of_parameters();
    qge_CallNativeProc(DynamicApis::pavcodec_get_class, a.data(), &ret);
    return ret;
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

int avcodec_open2(AVCodecContext *avctx, const AVCodec *codec, int **options) {
    auto ret = create_empty_ret(avcodec_open2);
    auto a = get_addresses_of_parameters(avctx, codec, options);
    qge_CallNativeProc(DynamicApis::pavcodec_open2, a.data(), &ret);
    return ret;
}

int avcodec_close(AVCodecContext *avctx) {
    auto ret = create_empty_ret(avcodec_close);
    auto a = get_addresses_of_parameters(avctx);
    qge_CallNativeProc(DynamicApis::pavcodec_close, a.data(), &ret);
    return ret;
}

void avsubtitle_free(AVSubtitle *sub) {
    auto a = get_addresses_of_parameters(sub);
    qge_CallNativeProc(DynamicApis::pavsubtitle_free, a.data(), nullptr);
}

int avcodec_decode_subtitle2(AVCodecContext *avctx, AVSubtitle *sub, int *got_sub_ptr,
                             AVPacket *avpkt) {
    auto ret = create_empty_ret(avcodec_decode_subtitle2);
    auto a = get_addresses_of_parameters(avctx, sub, got_sub_ptr, avpkt);
    qge_CallNativeProc(DynamicApis::pavcodec_decode_subtitle2, a.data(), &ret);
    return ret;
}

int avcodec_send_packet(AVCodecContext *avctx, const AVPacket *avpkt) {
    auto ret = create_empty_ret(avcodec_send_packet);
    auto a = get_addresses_of_parameters(avctx, avpkt);
    qge_CallNativeProc(DynamicApis::pavcodec_send_packet, a.data(), &ret);
    return ret;
}

int avcodec_receive_frame(AVCodecContext *avctx, int *frame) {
    auto ret = create_empty_ret(avcodec_receive_frame);
    auto a = get_addresses_of_parameters(avctx, frame);
    qge_CallNativeProc(DynamicApis::pavcodec_receive_frame, a.data(), &ret);
    return ret;
}

int avcodec_send_frame(AVCodecContext *avctx, const int *frame) {
    auto ret = create_empty_ret(avcodec_send_frame);
    auto a = get_addresses_of_parameters(avctx, frame);
    qge_CallNativeProc(DynamicApis::pavcodec_send_frame, a.data(), &ret);
    return ret;
}

int avcodec_receive_packet(AVCodecContext *avctx, AVPacket *avpkt) {
    auto ret = create_empty_ret(avcodec_receive_packet);
    auto a = get_addresses_of_parameters(avctx, avpkt);
    qge_CallNativeProc(DynamicApis::pavcodec_receive_packet, a.data(), &ret);
    return ret;
}

int avcodec_encode_subtitle(AVCodecContext *avctx, uint8_t *buf, int buf_size,
                            const AVSubtitle *sub) {
    auto ret = create_empty_ret(avcodec_encode_subtitle);
    auto a = get_addresses_of_parameters(avctx, buf, buf_size, sub);
    qge_CallNativeProc(DynamicApis::pavcodec_encode_subtitle, a.data(), &ret);
    return ret;
}

void avcodec_flush_buffers(AVCodecContext *avctx) {
    auto a = get_addresses_of_parameters(avctx);
    qge_CallNativeProc(DynamicApis::pavcodec_flush_buffers, a.data(), nullptr);
}

int av_get_audio_frame_duration(AVCodecContext *avctx, int frame_bytes) {
    auto ret = create_empty_ret(av_get_audio_frame_duration);
    auto a = get_addresses_of_parameters(avctx, frame_bytes);
    qge_CallNativeProc(DynamicApis::pav_get_audio_frame_duration, a.data(), &ret);
    return ret;
}

const AVBitStreamFilter *av_bsf_get_by_name(const char *name) {
    auto ret = create_empty_ret(av_bsf_get_by_name);
    auto a = get_addresses_of_parameters(name);
    qge_CallNativeProc(DynamicApis::pav_bsf_get_by_name, a.data(), &ret);
    return ret;
}

const AVBitStreamFilter *av_bsf_iterate(void **opaque) {
    auto ret = create_empty_ret(av_bsf_iterate);
    auto a = get_addresses_of_parameters(opaque);
    qge_CallNativeProc(DynamicApis::pav_bsf_iterate, a.data(), &ret);
    return ret;
}

int av_bsf_init(AVBSFContext *ctx) {
    auto ret = create_empty_ret(av_bsf_init);
    auto a = get_addresses_of_parameters(ctx);
    qge_CallNativeProc(DynamicApis::pav_bsf_init, a.data(), &ret);
    return ret;
}

int av_bsf_send_packet(AVBSFContext *ctx, AVPacket *pkt) {
    auto ret = create_empty_ret(av_bsf_send_packet);
    auto a = get_addresses_of_parameters(ctx, pkt);
    qge_CallNativeProc(DynamicApis::pav_bsf_send_packet, a.data(), &ret);
    return ret;
}

int av_bsf_receive_packet(AVBSFContext *ctx, AVPacket *pkt) {
    auto ret = create_empty_ret(av_bsf_receive_packet);
    auto a = get_addresses_of_parameters(ctx, pkt);
    qge_CallNativeProc(DynamicApis::pav_bsf_receive_packet, a.data(), &ret);
    return ret;
}

void av_bsf_free(AVBSFContext **ctx) {
    auto a = get_addresses_of_parameters(ctx);
    qge_CallNativeProc(DynamicApis::pav_bsf_free, a.data(), nullptr);
}

const int *av_bsf_get_class() {
    auto ret = create_empty_ret(av_bsf_get_class);
    auto a = get_addresses_of_parameters();
    qge_CallNativeProc(DynamicApis::pav_bsf_get_class, a.data(), &ret);
    return ret;
}

int av_bsf_list_parse_str(const char *str, AVBSFContext **bsf) {
    auto ret = create_empty_ret(av_bsf_list_parse_str);
    auto a = get_addresses_of_parameters(str, bsf);
    qge_CallNativeProc(DynamicApis::pav_bsf_list_parse_str, a.data(), &ret);
    return ret;
}
