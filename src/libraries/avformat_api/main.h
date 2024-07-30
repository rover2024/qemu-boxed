#ifdef __cplusplus
extern "C" {
#endif

#include <libavformat/avformat.h>

#ifdef __cplusplus
}
#endif

// API Declarations
#define BRIDGE_LIBRARY_NAME "libavformat_host_bridge.so"
#define HOST_LIBRARY_NAME   "ffmpeg/libavformat.so"
#define API_FOREACH_FUNCTION(F)                                                                    \
    F(avformat_open_input)                                                                         \
    F(av_guess_codec)                                                                              \
    F(av_find_best_stream)                                                                         \
    F(avformat_free_context)                                                                       \
    F(avio_open)                                                                                   \
    F(av_guess_format)                                                                             \
    F(avformat_write_header)                                                                       \
    F(avio_closep)                                                                                 \
    F(av_read_frame)                                                                               \
    F(avformat_alloc_context)                                                                      \
    F(av_write_frame)                                                                              \
    F(avformat_new_stream)                                                                         \
    F(av_write_trailer)                                                                            \
    F(avformat_find_stream_info)