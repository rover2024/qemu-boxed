#ifdef __cplusplus
extern "C" {
#endif

#ifdef __cplusplus
}
#endif

// API Declarations
#define BRIDGE_LIBRARY_NAME "lib" CURRENT_LIBRARY_NAME "_host_bridge.so"
#define HOST_LIBRARY_NAME   "ffmpeg/lib" CURRENT_LIBRARY_NAME ".so"
#define API_FOREACH_FUNCTION(F)                                                                    \
    F(sws_isSupportedInput)                                                                        \
    F(sws_get_class)                                                                               \
    F(sws_isSupportedOutput)                                                                       \
    F(swscale_version)                                                                             \
    F(swscale_configuration)