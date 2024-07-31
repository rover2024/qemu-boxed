#ifdef __cplusplus
extern "C" {
#endif

#define __STDC_CONSTANT_MACROS

#include <libavcodec/avcodec.h>
#include <libavcodec/bsf.h>

#ifdef __cplusplus
}
#endif

// API Declarations
#define BRIDGE_LIBRARY_NAME "lib" CURRENT_LIBRARY_NAME "_host_bridge.so"
#define HOST_LIBRARY_NAME   "ffmpeg/lib" CURRENT_LIBRARY_NAME ".so"
#define API_FOREACH_FUNCTION(F)                                                                    \
    F(av_codec_is_decoder)                                                                         \
    F(avcodec_version)                                                                             \
    F(avcodec_parameters_free)                                                                     \
    F(av_bsf_list_parse_str)                                                                       \
    F(avcodec_decode_subtitle2)                                                                    \
    F(avcodec_parameters_to_context)                                                               \
    F(av_bsf_free)                                                                                 \
    F(avcodec_get_name)                                                                            \
    F(avcodec_find_encoder_by_name)                                                                \
    F(avsubtitle_free)                                                                             \
    F(av_codec_iterate)                                                                            \
    F(avcodec_descriptor_get)                                                                      \
    F(avcodec_alloc_context3)                                                                      \
    F(av_bsf_get_by_name)                                                                          \
    F(av_packet_ref)                                                                               \
    F(avcodec_close)                                                                               \
    F(avcodec_send_packet)                                                                         \
    F(avcodec_configuration)                                                                       \
    F(avcodec_free_context)                                                                        \
    F(av_bsf_get_class)                                                                            \
    F(av_packet_alloc)                                                                             \
    F(avcodec_send_frame)                                                                          \
    F(avcodec_descriptor_get_by_name)                                                              \
    F(avcodec_encode_subtitle)                                                                     \
    F(av_codec_is_encoder)                                                                         \
    F(av_bsf_receive_packet)                                                                       \
    F(av_get_audio_frame_duration)                                                                 \
    F(avcodec_receive_packet)                                                                      \
    F(avcodec_get_hw_config)                                                                       \
    F(avcodec_parameters_from_context)                                                             \
    F(avcodec_find_decoder_by_name)                                                                \
    F(avcodec_find_decoder)                                                                        \
    F(av_packet_free)                                                                              \
    F(av_packet_get_side_data)                                                                     \
    F(avcodec_open2)                                                                               \
    F(avcodec_parameters_alloc)                                                                    \
    F(avcodec_parameters_copy)                                                                     \
    F(av_bsf_init)                                                                                 \
    F(av_get_exact_bits_per_sample)                                                                \
    F(av_packet_unref)                                                                             \
    F(avcodec_flush_buffers)                                                                       \
    F(av_bsf_send_packet)                                                                          \
    F(avcodec_descriptor_next)                                                                     \
    F(av_packet_rescale_ts)                                                                        \
    F(av_packet_new_side_data)                                                                     \
    F(avcodec_get_class)                                                                           \
    F(avcodec_find_encoder)                                                                        \
    F(av_packet_make_refcounted)                                                                   \
    F(av_bsf_iterate)                                                                              \
    F(av_packet_move_ref)                                                                          \
    F(avcodec_receive_frame)