#ifdef __cplusplus
extern "C" {
#endif

#include <libavcodec/packet.h>
#include <libavcodec/avcodec.h>

#ifdef __cplusplus
}
#endif

// API Declarations
#define BRIDGE_LIBRARY_NAME "libavutil_host_bridge.so"
#define HOST_LIBRARY_NAME   "ffmpeg/libavutil.so"
#define API_FOREACH_FUNCTION(F)                                                                    \
    F(av_frame_get_buffer)                                                                         \
    F(av_frame_alloc)                                                                              \
    F(av_strerror)                                                                                 \
    F(av_strdup)                                                                                   \
    F(av_frame_free)                                                                               \
    F(av_get_default_channel_layout)