#ifdef __cplusplus
extern "C" {
#endif

#define __STDC_CONSTANT_MACROS

#include <libavformat/avio.h>
#include <libavformat/avformat.h>

#ifdef __cplusplus
}
#endif

// API Declarations
#define BRIDGE_LIBRARY_NAME "lib" CURRENT_LIBRARY_NAME "_host_bridge.so"
#define HOST_LIBRARY_NAME   "ffmpeg/lib" CURRENT_LIBRARY_NAME ".so"
#define API_FOREACH_FUNCTION(F)                                                                    \
    F(av_stream_get_class)                                                                         \
    F(av_stream_new_side_data)                                                                     \
    F(av_guess_format)                                                                             \
    F(av_filename_number_test)                                                                     \
    F(av_codec_get_id)                                                                             \
    F(avformat_write_header)                                                                       \
    F(avformat_free_context)                                                                       \
    F(avformat_version)                                                                            \
    F(avformat_seek_file)                                                                          \
    F(avformat_alloc_context)                                                                      \
    F(avio_check)                                                                                  \
    F(av_guess_frame_rate)                                                                         \
    F(av_codec_get_tag2)                                                                           \
    F(avformat_network_deinit)                                                                     \
    F(avio_flush)                                                                                  \
    F(av_read_frame)                                                                               \
    F(av_find_input_format)                                                                        \
    F(av_stream_get_codec_timebase)                                                                \
    F(av_muxer_iterate)                                                                            \
    F(av_disposition_to_string)                                                                    \
    F(avio_seek)                                                                                   \
    F(avio_protocol_get_class)                                                                     \
    F(avio_find_protocol_name)                                                                     \
    F(avformat_get_class)                                                                          \
    F(avformat_configuration)                                                                      \
    F(av_guess_codec)                                                                              \
    F(avio_open)                                                                                   \
    F(avformat_match_stream_specifier)                                                             \
    F(avio_size)                                                                                   \
    F(avformat_transfer_internal_stream_timing_info)                                               \
    F(avio_read_to_bprint)                                                                         \
    F(av_stream_get_end_pts)                                                                       \
    F(av_interleaved_write_frame)                                                                  \
    F(avformat_new_stream)                                                                         \
    F(avio_close)                                                                                  \
    F(av_write_trailer)                                                                            \
    F(avio_write)                                                                                  \
    F(avio_read)                                                                                   \
    F(avformat_open_input)                                                                         \
    F(avio_closep)                                                                                 \
    F(avformat_close_input)                                                                        \
    F(av_sdp_create)                                                                               \
    F(avio_open2)                                                                                  \
    F(avformat_network_init)                                                                       \
    F(avformat_query_codec)                                                                        \
    F(av_stream_get_parser)                                                                        \
    F(avio_enum_protocols)                                                                         \
    F(av_dump_format)                                                                              \
    F(avformat_alloc_output_context2)                                                              \
    F(avio_print_string_array)                                                                     \
    F(av_pkt_dump_log2)                                                                            \
    F(av_demuxer_iterate)                                                                          \
    F(av_program_add_stream_index)                                                                 \
    F(av_stream_get_side_data)                                                                     \
    F(avformat_find_stream_info)                                                                   \
    F(av_new_program)                                                                              \
    F(avio_r8)