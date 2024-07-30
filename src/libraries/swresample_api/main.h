#ifdef __cplusplus
extern "C" {
#endif

#include <libswresample/swresample.h>

#ifdef __cplusplus
}
#endif

// API Declarations
#define BRIDGE_LIBRARY_NAME "libswresample_host_bridge.so"
#define HOST_LIBRARY_NAME "ffmpeg/libswresample.so"
#define API_FOREACH_FUNCTION(F)                                                                    \
    F(swr_convert)                                                                                 \
    F(swr_alloc_set_opts)                                                                          \
    F(swr_free)                                                                                    \
    F(swr_init)