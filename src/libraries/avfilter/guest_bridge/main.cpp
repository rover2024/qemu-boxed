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

unsigned int avfilter_version(void) {
    auto ret = create_empty_ret(avfilter_version);
    auto a = get_addresses_of_parameters();
    qge_CallNativeProc(DynamicApis::pavfilter_version, a.data(), &ret);
    return ret;
}

const char *avfilter_configuration(void) {
    auto ret = create_empty_ret(avfilter_configuration);
    auto a = get_addresses_of_parameters();
    qge_CallNativeProc(DynamicApis::pavfilter_configuration, a.data(), &ret);
    return ret;
}

const char *avfilter_pad_get_name(const AVFilterPad *pads, int pad_idx) {
    auto ret = create_empty_ret(avfilter_pad_get_name);
    auto a = get_addresses_of_parameters(pads, pad_idx);
    qge_CallNativeProc(DynamicApis::pavfilter_pad_get_name, a.data(), &ret);
    return ret;
}

enum AVMediaType avfilter_pad_get_type(const AVFilterPad *pads, int pad_idx) {
    auto ret = create_empty_ret(avfilter_pad_get_type);
    auto a = get_addresses_of_parameters(pads, pad_idx);
    qge_CallNativeProc(DynamicApis::pavfilter_pad_get_type, a.data(), &ret);
    return ret;
}

unsigned int avfilter_filter_pad_count(const AVFilter *filter, int is_output) {
    auto ret = create_empty_ret(avfilter_filter_pad_count);
    auto a = get_addresses_of_parameters(filter, is_output);
    qge_CallNativeProc(DynamicApis::pavfilter_filter_pad_count, a.data(), &ret);
    return ret;
}

int avfilter_link(AVFilterContext *src, unsigned int srcpad, AVFilterContext *dst,
                  unsigned int dstpad) {
    auto ret = create_empty_ret(avfilter_link);
    auto a = get_addresses_of_parameters(src, srcpad, dst, dstpad);
    qge_CallNativeProc(DynamicApis::pavfilter_link, a.data(), &ret);
    return ret;
}

const AVFilter *av_filter_iterate(void **opaque) {
    auto ret = create_empty_ret(av_filter_iterate);
    auto a = get_addresses_of_parameters(opaque);
    qge_CallNativeProc(DynamicApis::pav_filter_iterate, a.data(), &ret);
    return ret;
}

const AVFilter *avfilter_get_by_name(const char *name) {
    auto ret = create_empty_ret(avfilter_get_by_name);
    auto a = get_addresses_of_parameters(name);
    qge_CallNativeProc(DynamicApis::pavfilter_get_by_name, a.data(), &ret);
    return ret;
}

int avfilter_init_str(AVFilterContext *ctx, const char *args) {
    auto ret = create_empty_ret(avfilter_init_str);
    auto a = get_addresses_of_parameters(ctx, args);
    qge_CallNativeProc(DynamicApis::pavfilter_init_str, a.data(), &ret);
    return ret;
}

const AVClass *avfilter_get_class(void) {
    auto ret = create_empty_ret(avfilter_get_class);
    auto a = get_addresses_of_parameters();
    qge_CallNativeProc(DynamicApis::pavfilter_get_class, a.data(), &ret);
    return ret;
}

AVFilterGraph *avfilter_graph_alloc(void) {
    auto ret = create_empty_ret(avfilter_graph_alloc);
    auto a = get_addresses_of_parameters();
    qge_CallNativeProc(DynamicApis::pavfilter_graph_alloc, a.data(), &ret);
    return ret;
}

AVFilterContext *avfilter_graph_alloc_filter(AVFilterGraph *graph, const AVFilter *filter,
                                             const char *name) {
    auto ret = create_empty_ret(avfilter_graph_alloc_filter);
    auto a = get_addresses_of_parameters(graph, filter, name);
    qge_CallNativeProc(DynamicApis::pavfilter_graph_alloc_filter, a.data(), &ret);
    return ret;
}

int avfilter_graph_create_filter(AVFilterContext **filt_ctx, const AVFilter *filt, const char *name,
                                 const char *args, void *opaque, AVFilterGraph *graph_ctx) {
    auto ret = create_empty_ret(avfilter_graph_create_filter);
    auto a = get_addresses_of_parameters(filt_ctx, filt, name, args, opaque, graph_ctx);
    qge_CallNativeProc(DynamicApis::pavfilter_graph_create_filter, a.data(), &ret);
    return ret;
}

void avfilter_graph_set_auto_convert(AVFilterGraph *graph, unsigned int flags) {
    auto a = get_addresses_of_parameters(graph, flags);
    qge_CallNativeProc(DynamicApis::pavfilter_graph_set_auto_convert, a.data(), nullptr);
}

int avfilter_graph_config(AVFilterGraph *graphctx, void *log_ctx) {
    auto ret = create_empty_ret(avfilter_graph_config);
    auto a = get_addresses_of_parameters(graphctx, log_ctx);
    qge_CallNativeProc(DynamicApis::pavfilter_graph_config, a.data(), &ret);
    return ret;
}

void avfilter_graph_free(AVFilterGraph **graph) {
    auto a = get_addresses_of_parameters(graph);
    qge_CallNativeProc(DynamicApis::pavfilter_graph_free, a.data(), nullptr);
}

void avfilter_inout_free(AVFilterInOut **inout) {
    auto a = get_addresses_of_parameters(inout);
    qge_CallNativeProc(DynamicApis::pavfilter_inout_free, a.data(), nullptr);
}

int avfilter_graph_parse2(AVFilterGraph *graph, const char *filters, AVFilterInOut **inputs,
                          AVFilterInOut **outputs) {
    auto ret = create_empty_ret(avfilter_graph_parse2);
    auto a = get_addresses_of_parameters(graph, filters, inputs, outputs);
    qge_CallNativeProc(DynamicApis::pavfilter_graph_parse2, a.data(), &ret);
    return ret;
}

int avfilter_graph_send_command(AVFilterGraph *graph, const char *target, const char *cmd,
                                const char *arg, char *res, int res_len, int flags) {
    auto ret = create_empty_ret(avfilter_graph_send_command);
    auto a = get_addresses_of_parameters(graph, target, cmd, arg, res, res_len, flags);
    qge_CallNativeProc(DynamicApis::pavfilter_graph_send_command, a.data(), &ret);
    return ret;
}

int avfilter_graph_queue_command(AVFilterGraph *graph, const char *target, const char *cmd,
                                 const char *arg, int flags, double ts) {
    auto ret = create_empty_ret(avfilter_graph_queue_command);
    auto a = get_addresses_of_parameters(graph, target, cmd, arg, flags, ts);
    qge_CallNativeProc(DynamicApis::pavfilter_graph_queue_command, a.data(), &ret);
    return ret;
}

int avfilter_graph_request_oldest(AVFilterGraph *graph) {
    auto ret = create_empty_ret(avfilter_graph_request_oldest);
    auto a = get_addresses_of_parameters(graph);
    qge_CallNativeProc(DynamicApis::pavfilter_graph_request_oldest, a.data(), &ret);
    return ret;
}

int av_buffersink_get_frame_flags(AVFilterContext *ctx, AVFrame *frame, int flags) {
    auto ret = create_empty_ret(av_buffersink_get_frame_flags);
    auto a = get_addresses_of_parameters(ctx, frame, flags);
    qge_CallNativeProc(DynamicApis::pav_buffersink_get_frame_flags, a.data(), &ret);
    return ret;
}

void av_buffersink_set_frame_size(AVFilterContext *ctx, unsigned int frame_size) {
    auto a = get_addresses_of_parameters(ctx, frame_size);
    qge_CallNativeProc(DynamicApis::pav_buffersink_set_frame_size, a.data(), nullptr);
}

enum AVMediaType av_buffersink_get_type(const AVFilterContext *ctx) {
    auto ret = create_empty_ret(av_buffersink_get_type);
    auto a = get_addresses_of_parameters(ctx);
    qge_CallNativeProc(DynamicApis::pav_buffersink_get_type, a.data(), &ret);
    return ret;
}

AVRational av_buffersink_get_time_base(const AVFilterContext *ctx) {
    auto ret = create_empty_ret(av_buffersink_get_time_base);
    auto a = get_addresses_of_parameters(ctx);
    qge_CallNativeProc(DynamicApis::pav_buffersink_get_time_base, a.data(), &ret);
    return ret;
}

int av_buffersink_get_format(const AVFilterContext *ctx) {
    auto ret = create_empty_ret(av_buffersink_get_format);
    auto a = get_addresses_of_parameters(ctx);
    qge_CallNativeProc(DynamicApis::pav_buffersink_get_format, a.data(), &ret);
    return ret;
}

AVRational av_buffersink_get_frame_rate(const AVFilterContext *ctx) {
    auto ret = create_empty_ret(av_buffersink_get_frame_rate);
    auto a = get_addresses_of_parameters(ctx);
    qge_CallNativeProc(DynamicApis::pav_buffersink_get_frame_rate, a.data(), &ret);
    return ret;
}

int av_buffersink_get_w(const AVFilterContext *ctx) {
    auto ret = create_empty_ret(av_buffersink_get_w);
    auto a = get_addresses_of_parameters(ctx);
    qge_CallNativeProc(DynamicApis::pav_buffersink_get_w, a.data(), &ret);
    return ret;
}

int av_buffersink_get_h(const AVFilterContext *ctx) {
    auto ret = create_empty_ret(av_buffersink_get_h);
    auto a = get_addresses_of_parameters(ctx);
    qge_CallNativeProc(DynamicApis::pav_buffersink_get_h, a.data(), &ret);
    return ret;
}

AVRational av_buffersink_get_sample_aspect_ratio(const AVFilterContext *ctx) {
    auto ret = create_empty_ret(av_buffersink_get_sample_aspect_ratio);
    auto a = get_addresses_of_parameters(ctx);
    qge_CallNativeProc(DynamicApis::pav_buffersink_get_sample_aspect_ratio, a.data(), &ret);
    return ret;
}

int av_buffersink_get_ch_layout(const AVFilterContext *ctx, AVChannelLayout *ch_layout) {
    auto ret = create_empty_ret(av_buffersink_get_ch_layout);
    auto a = get_addresses_of_parameters(ctx, ch_layout);
    qge_CallNativeProc(DynamicApis::pav_buffersink_get_ch_layout, a.data(), &ret);
    return ret;
}

int av_buffersink_get_sample_rate(const AVFilterContext *ctx) {
    auto ret = create_empty_ret(av_buffersink_get_sample_rate);
    auto a = get_addresses_of_parameters(ctx);
    qge_CallNativeProc(DynamicApis::pav_buffersink_get_sample_rate, a.data(), &ret);
    return ret;
}

AVBufferRef *av_buffersink_get_hw_frames_ctx(const AVFilterContext *ctx) {
    auto ret = create_empty_ret(av_buffersink_get_hw_frames_ctx);
    auto a = get_addresses_of_parameters(ctx);
    qge_CallNativeProc(DynamicApis::pav_buffersink_get_hw_frames_ctx, a.data(), &ret);
    return ret;
}

unsigned int av_buffersrc_get_nb_failed_requests(AVFilterContext *buffer_src) {
    auto ret = create_empty_ret(av_buffersrc_get_nb_failed_requests);
    auto a = get_addresses_of_parameters(buffer_src);
    qge_CallNativeProc(DynamicApis::pav_buffersrc_get_nb_failed_requests, a.data(), &ret);
    return ret;
}

AVBufferSrcParameters *av_buffersrc_parameters_alloc(void) {
    auto ret = create_empty_ret(av_buffersrc_parameters_alloc);
    auto a = get_addresses_of_parameters();
    qge_CallNativeProc(DynamicApis::pav_buffersrc_parameters_alloc, a.data(), &ret);
    return ret;
}

int av_buffersrc_parameters_set(AVFilterContext *ctx, AVBufferSrcParameters *param) {
    auto ret = create_empty_ret(av_buffersrc_parameters_set);
    auto a = get_addresses_of_parameters(ctx, param);
    qge_CallNativeProc(DynamicApis::pav_buffersrc_parameters_set, a.data(), &ret);
    return ret;
}

int av_buffersrc_add_frame(AVFilterContext *ctx, AVFrame *frame) {
    auto ret = create_empty_ret(av_buffersrc_add_frame);
    auto a = get_addresses_of_parameters(ctx, frame);
    qge_CallNativeProc(DynamicApis::pav_buffersrc_add_frame, a.data(), &ret);
    return ret;
}

int av_buffersrc_add_frame_flags(AVFilterContext *buffer_src, AVFrame *frame, int flags) {
    auto ret = create_empty_ret(av_buffersrc_add_frame_flags);
    auto a = get_addresses_of_parameters(buffer_src, frame, flags);
    qge_CallNativeProc(DynamicApis::pav_buffersrc_add_frame_flags, a.data(), &ret);
    return ret;
}

int av_buffersrc_close(AVFilterContext *ctx, int64_t pts, unsigned int flags) {
    auto ret = create_empty_ret(av_buffersrc_close);
    auto a = get_addresses_of_parameters(ctx, pts, flags);
    qge_CallNativeProc(DynamicApis::pav_buffersrc_close, a.data(), &ret);
    return ret;
}
