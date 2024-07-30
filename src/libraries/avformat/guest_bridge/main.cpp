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

const char *avio_find_protocol_name(const char *url) {
    auto ret = create_empty_ret(avio_find_protocol_name);
    auto a = get_addresses_of_parameters(url);
    qge_CallNativeProc(DynamicApis::pavio_find_protocol_name, a.data(), &ret);
    return ret;
}

int avio_check(const char *url, int flags) {
    auto ret = create_empty_ret(avio_check);
    auto a = get_addresses_of_parameters(url, flags);
    qge_CallNativeProc(DynamicApis::pavio_check, a.data(), &ret);
    return ret;
}

void avio_write(AVIOContext *s, const unsigned char *buf, int size) {
    auto a = get_addresses_of_parameters(s, buf, size);
    qge_CallNativeProc(DynamicApis::pavio_write, a.data(), &ret);
}

int64_t avio_seek(AVIOContext *s, int64_t offset, int whence) {
    auto ret = create_empty_ret(avio_seek);
    auto a = get_addresses_of_parameters(s, offset, whence);
    qge_CallNativeProc(DynamicApis::pavio_seek, a.data(), &ret);
    return ret;
}

int64_t avio_size(AVIOContext *s) {
    auto ret = create_empty_ret(avio_size);
    auto a = get_addresses_of_parameters(s);
    qge_CallNativeProc(DynamicApis::pavio_size, a.data(), &ret);
    return ret;
}

void avio_print_string_array(AVIOContext *s, const char *[] strings) {
    auto a = get_addresses_of_parameters(s, strings);
    qge_CallNativeProc(DynamicApis::pavio_print_string_array, a.data(), &ret);
}

void avio_flush(AVIOContext *s) {
    auto a = get_addresses_of_parameters(s);
    qge_CallNativeProc(DynamicApis::pavio_flush, a.data(), &ret);
}

int avio_read(AVIOContext *s, unsigned char *buf, int size) {
    auto ret = create_empty_ret(avio_read);
    auto a = get_addresses_of_parameters(s, buf, size);
    qge_CallNativeProc(DynamicApis::pavio_read, a.data(), &ret);
    return ret;
}

int avio_r8(AVIOContext *s) {
    auto ret = create_empty_ret(avio_r8);
    auto a = get_addresses_of_parameters(s);
    qge_CallNativeProc(DynamicApis::pavio_r8, a.data(), &ret);
    return ret;
}

int avio_open(AVIOContext **s, const char *url, int flags) {
    auto ret = create_empty_ret(avio_open);
    auto a = get_addresses_of_parameters(s, url, flags);
    qge_CallNativeProc(DynamicApis::pavio_open, a.data(), &ret);
    return ret;
}

int avio_open2(AVIOContext **s, const char *url, int flags, const AVIOInterruptCB *int_cb,
               int **options) {
    auto ret = create_empty_ret(avio_open2);
    auto a = get_addresses_of_parameters(s, url, flags, int_cb, options);
    qge_CallNativeProc(DynamicApis::pavio_open2, a.data(), &ret);
    return ret;
}

int avio_close(AVIOContext *s) {
    auto ret = create_empty_ret(avio_close);
    auto a = get_addresses_of_parameters(s);
    qge_CallNativeProc(DynamicApis::pavio_close, a.data(), &ret);
    return ret;
}

int avio_closep(AVIOContext **s) {
    auto ret = create_empty_ret(avio_closep);
    auto a = get_addresses_of_parameters(s);
    qge_CallNativeProc(DynamicApis::pavio_closep, a.data(), &ret);
    return ret;
}

const char *avio_enum_protocols(void **opaque, int output) {
    auto ret = create_empty_ret(avio_enum_protocols);
    auto a = get_addresses_of_parameters(opaque, output);
    qge_CallNativeProc(DynamicApis::pavio_enum_protocols, a.data(), &ret);
    return ret;
}

const int *avio_protocol_get_class(const char *name) {
    auto ret = create_empty_ret(avio_protocol_get_class);
    auto a = get_addresses_of_parameters(name);
    qge_CallNativeProc(DynamicApis::pavio_protocol_get_class, a.data(), &ret);
    return ret;
}

int avio_read_to_bprint(AVIOContext *h, struct AVBPrint *pb, size_t max_size) {
    auto ret = create_empty_ret(avio_read_to_bprint);
    auto a = get_addresses_of_parameters(h, pb, max_size);
    qge_CallNativeProc(DynamicApis::pavio_read_to_bprint, a.data(), &ret);
    return ret;
}

const char *av_disposition_to_string(int disposition) {
    auto ret = create_empty_ret(av_disposition_to_string);
    auto a = get_addresses_of_parameters(disposition);
    qge_CallNativeProc(DynamicApis::pav_disposition_to_string, a.data(), &ret);
    return ret;
}

struct AVCodecParserContext *av_stream_get_parser(const AVStream *s) {
    auto ret = create_empty_ret(av_stream_get_parser);
    auto a = get_addresses_of_parameters(s);
    qge_CallNativeProc(DynamicApis::pav_stream_get_parser, a.data(), &ret);
    return ret;
}

int64_t av_stream_get_end_pts(const AVStream *st) {
    auto ret = create_empty_ret(av_stream_get_end_pts);
    auto a = get_addresses_of_parameters(st);
    qge_CallNativeProc(DynamicApis::pav_stream_get_end_pts, a.data(), &ret);
    return ret;
}

unsigned int avformat_version() {
    auto ret = create_empty_ret(avformat_version);
    auto a = get_addresses_of_parameters();
    qge_CallNativeProc(DynamicApis::pavformat_version, a.data(), &ret);
    return ret;
}

const char *avformat_configuration() {
    auto ret = create_empty_ret(avformat_configuration);
    auto a = get_addresses_of_parameters();
    qge_CallNativeProc(DynamicApis::pavformat_configuration, a.data(), &ret);
    return ret;
}

int avformat_network_init() {
    auto ret = create_empty_ret(avformat_network_init);
    auto a = get_addresses_of_parameters();
    qge_CallNativeProc(DynamicApis::pavformat_network_init, a.data(), &ret);
    return ret;
}

int avformat_network_deinit() {
    auto ret = create_empty_ret(avformat_network_deinit);
    auto a = get_addresses_of_parameters();
    qge_CallNativeProc(DynamicApis::pavformat_network_deinit, a.data(), &ret);
    return ret;
}

const AVOutputFormat *av_muxer_iterate(void **opaque) {
    auto ret = create_empty_ret(av_muxer_iterate);
    auto a = get_addresses_of_parameters(opaque);
    qge_CallNativeProc(DynamicApis::pav_muxer_iterate, a.data(), &ret);
    return ret;
}

const AVInputFormat *av_demuxer_iterate(void **opaque) {
    auto ret = create_empty_ret(av_demuxer_iterate);
    auto a = get_addresses_of_parameters(opaque);
    qge_CallNativeProc(DynamicApis::pav_demuxer_iterate, a.data(), &ret);
    return ret;
}

AVFormatContext *avformat_alloc_context() {
    auto ret = create_empty_ret(avformat_alloc_context);
    auto a = get_addresses_of_parameters();
    qge_CallNativeProc(DynamicApis::pavformat_alloc_context, a.data(), &ret);
    return ret;
}

void avformat_free_context(AVFormatContext *s) {
    auto a = get_addresses_of_parameters(s);
    qge_CallNativeProc(DynamicApis::pavformat_free_context, a.data(), &ret);
}

const int *avformat_get_class() {
    auto ret = create_empty_ret(avformat_get_class);
    auto a = get_addresses_of_parameters();
    qge_CallNativeProc(DynamicApis::pavformat_get_class, a.data(), &ret);
    return ret;
}

const int *av_stream_get_class() {
    auto ret = create_empty_ret(av_stream_get_class);
    auto a = get_addresses_of_parameters();
    qge_CallNativeProc(DynamicApis::pav_stream_get_class, a.data(), &ret);
    return ret;
}

AVStream *avformat_new_stream(AVFormatContext *s, const int *c) {
    auto ret = create_empty_ret(avformat_new_stream);
    auto a = get_addresses_of_parameters(s, c);
    qge_CallNativeProc(DynamicApis::pavformat_new_stream, a.data(), &ret);
    return ret;
}

uint8_t *av_stream_new_side_data(AVStream *stream, enum AVPacketSideDataType type, size_t size) {
    auto ret = create_empty_ret(av_stream_new_side_data);
    auto a = get_addresses_of_parameters(stream, type, size);
    qge_CallNativeProc(DynamicApis::pav_stream_new_side_data, a.data(), &ret);
    return ret;
}

uint8_t *av_stream_get_side_data(const AVStream *stream, enum AVPacketSideDataType type,
                                 size_t *size) {
    auto ret = create_empty_ret(av_stream_get_side_data);
    auto a = get_addresses_of_parameters(stream, type, size);
    qge_CallNativeProc(DynamicApis::pav_stream_get_side_data, a.data(), &ret);
    return ret;
}

AVProgram *av_new_program(AVFormatContext *s, int id) {
    auto ret = create_empty_ret(av_new_program);
    auto a = get_addresses_of_parameters(s, id);
    qge_CallNativeProc(DynamicApis::pav_new_program, a.data(), &ret);
    return ret;
}

int avformat_alloc_output_context2(AVFormatContext **ctx, const AVOutputFormat *oformat,
                                   const char *format_name, const char *filename) {
    auto ret = create_empty_ret(avformat_alloc_output_context2);
    auto a = get_addresses_of_parameters(ctx, oformat, format_name, filename);
    qge_CallNativeProc(DynamicApis::pavformat_alloc_output_context2, a.data(), &ret);
    return ret;
}

const AVInputFormat *av_find_input_format(const char *short_name) {
    auto ret = create_empty_ret(av_find_input_format);
    auto a = get_addresses_of_parameters(short_name);
    qge_CallNativeProc(DynamicApis::pav_find_input_format, a.data(), &ret);
    return ret;
}

int avformat_open_input(AVFormatContext **ps, const char *url, const AVInputFormat *fmt,
                        int **options) {
    auto ret = create_empty_ret(avformat_open_input);
    auto a = get_addresses_of_parameters(ps, url, fmt, options);
    qge_CallNativeProc(DynamicApis::pavformat_open_input, a.data(), &ret);
    return ret;
}

int avformat_find_stream_info(AVFormatContext *ic, int **options) {
    auto ret = create_empty_ret(avformat_find_stream_info);
    auto a = get_addresses_of_parameters(ic, options);
    qge_CallNativeProc(DynamicApis::pavformat_find_stream_info, a.data(), &ret);
    return ret;
}

void av_program_add_stream_index(AVFormatContext *ac, int progid, unsigned int idx) {
    auto a = get_addresses_of_parameters(ac, progid, idx);
    qge_CallNativeProc(DynamicApis::pav_program_add_stream_index, a.data(), &ret);
}

int av_read_frame(AVFormatContext *s, int *pkt) {
    auto ret = create_empty_ret(av_read_frame);
    auto a = get_addresses_of_parameters(s, pkt);
    qge_CallNativeProc(DynamicApis::pav_read_frame, a.data(), &ret);
    return ret;
}

int avformat_seek_file(AVFormatContext *s, int stream_index, int64_t min_ts, int64_t ts,
                       int64_t max_ts, int flags) {
    auto ret = create_empty_ret(avformat_seek_file);
    auto a = get_addresses_of_parameters(s, stream_index, min_ts, ts, max_ts, flags);
    qge_CallNativeProc(DynamicApis::pavformat_seek_file, a.data(), &ret);
    return ret;
}

void avformat_close_input(AVFormatContext **s) {
    auto a = get_addresses_of_parameters(s);
    qge_CallNativeProc(DynamicApis::pavformat_close_input, a.data(), &ret);
}

int avformat_write_header(AVFormatContext *s, int **options) {
    auto ret = create_empty_ret(avformat_write_header);
    auto a = get_addresses_of_parameters(s, options);
    qge_CallNativeProc(DynamicApis::pavformat_write_header, a.data(), &ret);
    return ret;
}

int av_interleaved_write_frame(AVFormatContext *s, int *pkt) {
    auto ret = create_empty_ret(av_interleaved_write_frame);
    auto a = get_addresses_of_parameters(s, pkt);
    qge_CallNativeProc(DynamicApis::pav_interleaved_write_frame, a.data(), &ret);
    return ret;
}

int av_write_trailer(AVFormatContext *s) {
    auto ret = create_empty_ret(av_write_trailer);
    auto a = get_addresses_of_parameters(s);
    qge_CallNativeProc(DynamicApis::pav_write_trailer, a.data(), &ret);
    return ret;
}

const AVOutputFormat *av_guess_format(const char *short_name, const char *filename,
                                      const char *mime_type) {
    auto ret = create_empty_ret(av_guess_format);
    auto a = get_addresses_of_parameters(short_name, filename, mime_type);
    qge_CallNativeProc(DynamicApis::pav_guess_format, a.data(), &ret);
    return ret;
}

enum AVCodecID av_guess_codec(const AVOutputFormat *fmt, const char *short_name,
                              const char *filename, const char *mime_type, enum AVMediaType type) {
    auto ret = create_empty_ret(av_guess_codec);
    auto a = get_addresses_of_parameters(fmt, short_name, filename, mime_type, type);
    qge_CallNativeProc(DynamicApis::pav_guess_codec, a.data(), &ret);
    return ret;
}

void av_pkt_dump_log2(void *avcl, int level, const int *pkt, int dump_payload, const AVStream *st) {
    auto a = get_addresses_of_parameters(avcl, level, pkt, dump_payload, st);
    qge_CallNativeProc(DynamicApis::pav_pkt_dump_log2, a.data(), &ret);
}

enum AVCodecID av_codec_get_id(const struct AVCodecTag *const *tags, unsigned int tag) {
    auto ret = create_empty_ret(av_codec_get_id);
    auto a = get_addresses_of_parameters(tags, tag);
    qge_CallNativeProc(DynamicApis::pav_codec_get_id, a.data(), &ret);
    return ret;
}

int av_codec_get_tag2(const struct AVCodecTag *const *tags, enum AVCodecID id, unsigned int *tag) {
    auto ret = create_empty_ret(av_codec_get_tag2);
    auto a = get_addresses_of_parameters(tags, id, tag);
    qge_CallNativeProc(DynamicApis::pav_codec_get_tag2, a.data(), &ret);
    return ret;
}

void av_dump_format(AVFormatContext *ic, int index, const char *url, int is_output) {
    auto a = get_addresses_of_parameters(ic, index, url, is_output);
    qge_CallNativeProc(DynamicApis::pav_dump_format, a.data(), &ret);
}

int av_filename_number_test(const char *filename) {
    auto ret = create_empty_ret(av_filename_number_test);
    auto a = get_addresses_of_parameters(filename);
    qge_CallNativeProc(DynamicApis::pav_filename_number_test, a.data(), &ret);
    return ret;
}

int av_sdp_create(AVFormatContext *[] ac, int n_files, char *buf, int size) {
    auto ret = create_empty_ret(av_sdp_create);
    auto a = get_addresses_of_parameters(ac, n_files, buf, size);
    qge_CallNativeProc(DynamicApis::pav_sdp_create, a.data(), &ret);
    return ret;
}

int avformat_query_codec(const AVOutputFormat *ofmt, enum AVCodecID codec_id, int std_compliance) {
    auto ret = create_empty_ret(avformat_query_codec);
    auto a = get_addresses_of_parameters(ofmt, codec_id, std_compliance);
    qge_CallNativeProc(DynamicApis::pavformat_query_codec, a.data(), &ret);
    return ret;
}

int av_guess_frame_rate(AVFormatContext *ctx, AVStream *stream, int *frame) {
    auto ret = create_empty_ret(av_guess_frame_rate);
    auto a = get_addresses_of_parameters(ctx, stream, frame);
    qge_CallNativeProc(DynamicApis::pav_guess_frame_rate, a.data(), &ret);
    return ret;
}

int avformat_match_stream_specifier(AVFormatContext *s, AVStream *st, const char *spec) {
    auto ret = create_empty_ret(avformat_match_stream_specifier);
    auto a = get_addresses_of_parameters(s, st, spec);
    qge_CallNativeProc(DynamicApis::pavformat_match_stream_specifier, a.data(), &ret);
    return ret;
}

int avformat_transfer_internal_stream_timing_info(const AVOutputFormat *ofmt, AVStream *ost,
                                                  const AVStream *ist,
                                                  enum AVTimebaseSource copy_tb) {
    auto ret = create_empty_ret(avformat_transfer_internal_stream_timing_info);
    auto a = get_addresses_of_parameters(ofmt, ost, ist, copy_tb);
    qge_CallNativeProc(DynamicApis::pavformat_transfer_internal_stream_timing_info, a.data(), &ret);
    return ret;
}

int av_stream_get_codec_timebase(const AVStream *st) {
    auto ret = create_empty_ret(av_stream_get_codec_timebase);
    auto a = get_addresses_of_parameters(st);
    qge_CallNativeProc(DynamicApis::pav_stream_get_codec_timebase, a.data(), &ret);
    return ret;
}
