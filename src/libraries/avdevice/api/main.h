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
    F(av_output_audio_device_next)                                                                 \
    F(avdevice_register_all)                                                                       \
    F(av_input_video_device_next)                                                                  \
    F(avdevice_free_list_devices)                                                                  \
    F(avdevice_version)                                                                            \
    F(avdevice_list_input_sources)                                                                 \
    F(avdevice_list_output_sinks)                                                                  \
    F(avdevice_configuration)                                                                      \
    F(av_input_audio_device_next)                                                                  \
    F(av_output_video_device_next)