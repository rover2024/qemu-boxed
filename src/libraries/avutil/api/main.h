#ifdef __cplusplus
extern "C" {
#endif

#define __STDC_CONSTANT_MACROS

#include <libavutil/avutil.h>
#include <libavutil/fifo.h>
#include <libavutil/samplefmt.h>
#include <libavutil/channel_layout.h>
#include <libavutil/buffer.h>
#include <libavutil/dict.h>
#include <libavutil/frame.h>
#include <libavutil/eval.h>
#include <libavutil/pixdesc.h>
#include <libavutil/hwcontext.h>
#include <libavutil/threadmessage.h>
#include <libavutil/bprint.h>
#include <libavutil/time.h>
#include <libavutil/opt.h>
#include <libavutil/cpu.h>
#include <libavutil/parseutils.h>
#include <libavutil/display.h>

#ifdef __cplusplus
}
#endif

// API Declarations
#define BRIDGE_LIBRARY_NAME "lib" CURRENT_LIBRARY_NAME "_host_bridge.so"
#define HOST_LIBRARY_NAME   "ffmpeg/lib" CURRENT_LIBRARY_NAME ".so"
#define API_FOREACH_FUNCTION(F)                                                                    \
    F(av_bprint_chars)                                                                             \
    F(av_frame_unref)                                                                              \
    F(av_pix_fmt_desc_get_id)                                                                      \
    F(av_get_bytes_per_sample)                                                                     \
    F(av_strtod)                                                                                   \
    F(av_calloc)                                                                                   \
    F(av_usleep)                                                                                   \
    F(av_fifo_read)                                                                                \
    F(av_find_best_pix_fmt_of_2)                                                                   \
    F(av_log_set_level)                                                                            \
    F(av_dict_free)                                                                                \
    F(av_rescale_q_rnd)                                                                            \
    F(av_thread_message_queue_set_err_recv)                                                        \
    F(av_realloc_array)                                                                            \
    F(av_mul_q)                                                                                    \
    F(av_opt_child_class_iterate)                                                                  \
    F(av_dict_get)                                                                                 \
    F(av_get_picture_type_char)                                                                    \
    F(av_get_bits_per_pixel)                                                                       \
    F(av_strstart)                                                                                 \
    F(av_opt_set)                                                                                  \
    F(av_dynarray_add_nofree)                                                                      \
    F(avutil_configuration)                                                                        \
    F(av_get_channel_layout)                                                                       \
    F(av_strlcpy)                                                                                  \
    F(av_max_alloc)                                                                                \
    F(av_cpu_force_count)                                                                          \
    F(av_strdup)                                                                                   \
    F(av_parse_video_rate)                                                                         \
    F(av_opt_set_int)                                                                              \
    F(av_memdup)                                                                                   \
    F(av_opt_find)                                                                                 \
    F(av_frame_copy_props)                                                                         \
    F(av_strndup)                                                                                  \
    F(av_hwdevice_get_type_name)                                                                   \
    F(av_get_media_type_string)                                                                    \
    F(av_get_known_color_name)                                                                     \
    F(av_get_token)                                                                                \
    F(av_channel_layout_from_string)                                                               \
    F(av_fifo_freep2)                                                                              \
    F(av_get_pix_fmt)                                                                              \
    F(av_channel_description)                                                                      \
    F(av_expr_eval)                                                                                \
    F(av_thread_message_queue_set_err_send)                                                        \
    F(av_hwdevice_iterate_types)                                                                   \
    F(av_expr_parse)                                                                               \
    F(av_rescale)                                                                                  \
    F(av_match_name)                                                                               \
    F(av_strlcat)                                                                                  \
    F(av_add_q)                                                                                    \
    F(av_opt_eval_int)                                                                             \
    F(av_parse_cpu_caps)                                                                           \
    F(av_frame_get_buffer)                                                                         \
    F(av_thread_message_queue_send)                                                                \
    F(av_gettime_relative)                                                                         \
    F(av_log_set_callback_help)                                                                    \
    F(av_hwdevice_ctx_create_derived)                                                              \
    F(av_channel_name)                                                                             \
    F(av_get_sample_fmt)                                                                           \
    F(av_channel_layout_uninit)                                                                    \
    F(av_channel_layout_standard)                                                                  \
    F(av_frame_move_ref)                                                                           \
    F(av_frame_get_side_data)                                                                      \
    F(av_channel_layout_default)                                                                   \
    F(av_fifo_write)                                                                               \
    F(av_parse_ratio)                                                                              \
    F(av_parse_video_size)                                                                         \
    F(av_bprint_init)                                                                              \
    F(av_expr_free)                                                                                \
    F(av_reduce)                                                                                   \
    F(av_hwdevice_ctx_create)                                                                      \
    F(av_fifo_alloc2)                                                                              \
    F(av_opt_eval_flags)                                                                           \
    F(av_find_nearest_q_idx)                                                                       \
    F(av_opt_get_key_value)                                                                        \
    F(av_fifo_can_write)                                                                           \
    F(av_pix_fmt_desc_next)                                                                        \
    F(av_frame_alloc)                                                                              \
    F(av_thread_message_queue_free)                                                                \
    F(av_thread_message_queue_alloc)                                                               \
    F(av_malloc)                                                                                   \
    F(av_strcasecmp)                                                                               \
    F(av_fifo_grow2)                                                                               \
    F(av_buffer_ref)                                                                               \
    F(av_display_rotation_get)                                                                     \
    F(av_hwframe_transfer_data)                                                                    \
    F(av_channel_layout_describe_bprint)                                                           \
    F(av_display_rotation_set)                                                                     \
    F(avutil_version)                                                                              \
    F(av_reallocp_array)                                                                           \
    F(av_frame_clone)                                                                              \
    F(av_log_get_flags)                                                                            \
    F(av_log2)                                                                                     \
    F(av_get_sample_fmt_name)                                                                      \
    F(av_get_pix_fmt_name)                                                                         \
    F(av_malloc_array)                                                                             \
    F(av_thread_message_queue_recv)                                                                \
    F(av_channel_layout_from_mask)                                                                 \
    F(av_free)                                                                                     \
    F(av_realloc_f)                                                                                \
    F(av_log_get_level)                                                                            \
    F(av_channel_layout_check)                                                                     \
    F(av_bprint_finalize)                                                                          \
    F(av_compare_ts)                                                                               \
    F(av_get_cpu_flags)                                                                            \
    F(av_frame_free)                                                                               \
    F(av_opt_show2)                                                                                \
    F(av_dict_parse_string)                                                                        \
    F(av_channel_layout_compare)                                                                   \
    F(av_dict_set)                                                                                 \
    F(av_default_item_name)                                                                        \
    F(av_opt_set_dict)                                                                             \
    F(av_channel_layout_copy)                                                                      \
    F(av_pix_fmt_desc_get)                                                                         \
    F(av_dict_set_int)                                                                             \
    F(av_strtok)                                                                                   \
    F(av_log_set_callback_report)                                                                  \
    F(av_log_set_flags)                                                                            \
    F(av_get_sample_fmt_string)                                                                    \
    F(av_force_cpu_flags)                                                                          \
    F(av_bprint_clear)                                                                             \
    F(av_mallocz)                                                                                  \
    F(av_strerror)                                                                                 \
    F(av_freep)                                                                                    \
    F(av_buffer_unref)                                                                             \
    F(av_channel_layout_index_from_channel)                                                        \
    F(av_fifo_can_read)                                                                            \
    F(av_hwdevice_find_type_by_name)                                                               \
    F(av_channel_layout_describe)                                                                  \
    F(av_rescale_q)                                                                                \
    F(av_rescale_delta)                                                                            \
    F(av_dict_copy)                                                                                \
    F(av_parse_time)                                                                               \
    F(av_vlog)                                                                                     \
    F(av_bprint_alloc)                                                                             \
    F(av_bprint_grow)                                                                              \
    F(avutil_decode_interrupt_cb)                                                                  \
    F(avutil_transcode_init_done)                                                                  \
    F(avutil_received_nb_signals_ptr)
