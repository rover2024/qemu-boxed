#ifdef __cplusplus
extern "C" {
#endif

#define __STDC_CONSTANT_MACROS

#include <libavfilter/buffersrc.h>
#include <libavfilter/buffersink.h>
#include <libavfilter/avfilter.h>

#ifdef __cplusplus
}
#endif

// API Declarations
#define BRIDGE_LIBRARY_NAME "lib" CURRENT_LIBRARY_NAME "_host_bridge.so"
#define HOST_LIBRARY_NAME   "ffmpeg/lib" CURRENT_LIBRARY_NAME ".so"
#define API_FOREACH_FUNCTION(F)                                                                    \
    F(av_buffersink_get_h)                                                                         \
    F(av_buffersink_get_time_base)                                                                 \
    F(av_buffersink_set_frame_size)                                                                \
    F(avfilter_graph_send_command)                                                                 \
    F(avfilter_configuration)                                                                      \
    F(av_filter_iterate)                                                                           \
    F(avfilter_graph_parse2)                                                                       \
    F(av_buffersrc_parameters_set)                                                                 \
    F(av_buffersink_get_frame_flags)                                                               \
    F(av_buffersink_get_w)                                                                         \
    F(av_buffersrc_get_nb_failed_requests)                                                         \
    F(av_buffersink_get_type)                                                                      \
    F(avfilter_pad_get_type)                                                                       \
    F(avfilter_graph_queue_command)                                                                \
    F(av_buffersrc_close)                                                                          \
    F(avfilter_version)                                                                            \
    F(avfilter_graph_config)                                                                       \
    F(avfilter_graph_alloc_filter)                                                                 \
    F(avfilter_graph_set_auto_convert)                                                             \
    F(av_buffersink_get_format)                                                                    \
    F(av_buffersink_get_sample_aspect_ratio)                                                       \
    F(avfilter_graph_create_filter)                                                                \
    F(avfilter_init_str)                                                                           \
    F(avfilter_filter_pad_count)                                                                   \
    F(avfilter_get_by_name)                                                                        \
    F(avfilter_get_class)                                                                          \
    F(avfilter_graph_free)                                                                         \
    F(av_buffersink_get_sample_rate)                                                               \
    F(avfilter_pad_get_name)                                                                       \
    F(avfilter_graph_request_oldest)                                                               \
    F(avfilter_graph_alloc)                                                                        \
    F(av_buffersink_get_ch_layout)                                                                 \
    F(av_buffersrc_parameters_alloc)                                                               \
    F(av_buffersrc_add_frame_flags)                                                                \
    F(av_buffersink_get_frame_rate)                                                                \
    F(av_buffersink_get_hw_frames_ctx)                                                             \
    F(av_buffersrc_add_frame)                                                                      \
    F(avfilter_link)                                                                               \
    F(avfilter_inout_free)