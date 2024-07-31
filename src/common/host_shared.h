#define API_HELPER(X)                                                                              \
    extern "C" __attribute__((visibility("default"))) void my_##X(void *args, void *ret) {         \
        call_function2(DynamicApis::p##X, (void **) args, ret);                                    \
    }
API_FOREACH_FUNCTION(API_HELPER)
#undef API_HELPER


// printf("Call " #X "\n");                                                                   \