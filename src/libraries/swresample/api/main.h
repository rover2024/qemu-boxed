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
    F(swresample_configuration)                                                                    \
    F(swr_get_class)                                                                               \
    F(swresample_version)