#ifdef __cplusplus
extern "C" {
#endif

#include <libavcodec/packet.h>
#include <libavcodec/avcodec.h>

#ifdef __cplusplus
}
#endif

// API Declarations
#define BRIDGE_LIBRARY_NAME "libavcodec_host_bridge.so"
#define HOST_LIBRARY_NAME   "ffmpeg/libavcodec.so"
#define API_FOREACH_FUNCTION(F)                                                                    \
    F(avcodec_parameters_from_context)                                                             \
    F(avcodec_parameters_to_context)                                                               \
    F(avcodec_find_encoder)                                                                        \
    F(avcodec_free_context)                                                                        \
    F(avcodec_receive_packet)                                                                      \
    F(avcodec_close)                                                                               \
    F(avcodec_send_frame)                                                                          \
    F(avcodec_send_packet)                                                                         \
    F(avcodec_receive_frame)                                                                       \
    F(av_init_packet)                                                                              \
    F(avcodec_open2)                                                                               \
    F(av_packet_unref)                                                                             \
    F(avcodec_alloc_context3)