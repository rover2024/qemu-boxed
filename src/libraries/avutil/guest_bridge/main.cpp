#include <dlfcn.h>
#include <limits.h>

#include <cstdio>
#include <cstdlib>
#include <filesystem>

#include <common/wrapper_helper.h>
#include <qemu-guest-entry.h>

#include <api/main.h>

// API Implementions
namespace {

    const char *get_library_path() {
        Dl_info dl_info;
        // 获取当前函数的地址
        if (dladdr((void *) get_library_path, &dl_info)) {
        } else {
            fprintf(stderr, "Error: unable to get library path.\n");
        }
        return dl_info.dli_fname;
    }

    namespace DynamicApis {

// Declare Function Pointers
#define API_HELPER(NAME) void *p##NAME = nullptr;
        API_FOREACH_FUNCTION(API_HELPER)
#undef API_HELPER

        struct initializer {

            initializer() {
                // Load Library
                auto dll = qge_LoadLibrary(
                    (std::filesystem::path(get_library_path()).parent_path() / BRIDGE_LIBRARY_NAME)
                        .c_str(),
                    RTLD_NOW);
                if (!dll) {
                    fprintf(stderr, "Guest Bridge: Load %s error: %s\n", BRIDGE_LIBRARY_NAME,
                            qge_GetErrorMessage());
                    std::abort();
                }

                _hDll = dll;

// Get Function Addresses
#define API_HELPER(NAME)                                                                           \
    {                                                                                              \
        p##NAME = reinterpret_cast<decltype(p##NAME)>(qge_GetProcAddress(dll, "my_" #NAME));       \
        if (!p##NAME) {                                                                            \
            fprintf(stderr, "Guest Bridge: API %s cannot be resolved!\n", #NAME);                  \
            std::abort();                                                                          \
        }                                                                                          \
    }
                API_FOREACH_FUNCTION(API_HELPER)
#undef API_HELPER
            }

            ~initializer() {
                // Kernel with remove at end
                qge_FreeLibrary(_hDll);
            }

            void *_hDll;

        } dummy;

    }

}

int av_log_get_level(void) {
    auto ret = create_empty_ret(av_log_get_level);
    auto a = get_addresses_of_parameters();
    qge_CallNativeProc(DynamicApis::pav_log_get_level, a.data(), &ret);
    return ret;
}

void av_log_set_level(int level) {
    auto a = get_addresses_of_parameters(level);
    qge_CallNativeProc(DynamicApis::pav_log_set_level, a.data(), nullptr);
}

const char *av_default_item_name(void *ctx) {
    auto ret = create_empty_ret(av_default_item_name);
    auto a = get_addresses_of_parameters(ctx);
    qge_CallNativeProc(DynamicApis::pav_default_item_name, a.data(), &ret);
    return ret;
}

void av_log_set_flags(int arg) {
    auto a = get_addresses_of_parameters(arg);
    qge_CallNativeProc(DynamicApis::pav_log_set_flags, a.data(), nullptr);
}

int av_log_get_flags(void) {
    auto ret = create_empty_ret(av_log_get_flags);
    auto a = get_addresses_of_parameters();
    qge_CallNativeProc(DynamicApis::pav_log_get_flags, a.data(), &ret);
    return ret;
}

unsigned int avutil_version(void) {
    auto ret = create_empty_ret(avutil_version);
    auto a = get_addresses_of_parameters();
    qge_CallNativeProc(DynamicApis::pavutil_version, a.data(), &ret);
    return ret;
}

const char *avutil_configuration(void) {
    auto ret = create_empty_ret(avutil_configuration);
    auto a = get_addresses_of_parameters();
    qge_CallNativeProc(DynamicApis::pavutil_configuration, a.data(), &ret);
    return ret;
}

const char *av_get_media_type_string(enum AVMediaType media_type) {
    auto ret = create_empty_ret(av_get_media_type_string);
    auto a = get_addresses_of_parameters(media_type);
    qge_CallNativeProc(DynamicApis::pav_get_media_type_string, a.data(), &ret);
    return ret;
}

char av_get_picture_type_char(enum AVPictureType pict_type) {
    auto ret = create_empty_ret(av_get_picture_type_char);
    auto a = get_addresses_of_parameters(pict_type);
    qge_CallNativeProc(DynamicApis::pav_get_picture_type_char, a.data(), &ret);
    return ret;
}

int av_log2(unsigned int v) {
    auto ret = create_empty_ret(av_log2);
    auto a = get_addresses_of_parameters(v);
    qge_CallNativeProc(DynamicApis::pav_log2, a.data(), &ret);
    return ret;
}

int av_strerror(int errnum, char *errbuf, size_t errbuf_size) {
    auto ret = create_empty_ret(av_strerror);
    auto a = get_addresses_of_parameters(errnum, errbuf, errbuf_size);
    qge_CallNativeProc(DynamicApis::pav_strerror, a.data(), &ret);
    return ret;
}

int av_reduce(int *dst_num, int *dst_den, int64_t num, int64_t den, int64_t max) {
    auto ret = create_empty_ret(av_reduce);
    auto a = get_addresses_of_parameters(dst_num, dst_den, num, den, max);
    qge_CallNativeProc(DynamicApis::pav_reduce, a.data(), &ret);
    return ret;
}

AVRational av_mul_q(AVRational b, AVRational c) {
    auto ret = create_empty_ret(av_mul_q);
    auto a = get_addresses_of_parameters(b, c);
    qge_CallNativeProc(DynamicApis::pav_mul_q, a.data(), &ret);
    return ret;
}

AVRational av_add_q(AVRational b, AVRational c) {
    auto ret = create_empty_ret(av_add_q);
    auto a = get_addresses_of_parameters(b, c);
    qge_CallNativeProc(DynamicApis::pav_add_q, a.data(), &ret);
    return ret;
}

int av_find_nearest_q_idx(AVRational q, const AVRational *q_list) {
    auto ret = create_empty_ret(av_find_nearest_q_idx);
    auto a = get_addresses_of_parameters(q, q_list);
    qge_CallNativeProc(DynamicApis::pav_find_nearest_q_idx, a.data(), &ret);
    return ret;
}

int64_t av_rescale(int64_t a, int64_t b, int64_t c) {
    auto ret = create_empty_ret(av_rescale);
    auto a1 = get_addresses_of_parameters(a, b, c);
    qge_CallNativeProc(DynamicApis::pav_rescale, a1.data(), &ret);
    return ret;
}

int64_t av_rescale_q(int64_t a, AVRational bq, AVRational cq) {
    auto ret = create_empty_ret(av_rescale_q);
    auto a1 = get_addresses_of_parameters(a, bq, cq);
    qge_CallNativeProc(DynamicApis::pav_rescale_q, a1.data(), &ret);
    return ret;
}

int64_t av_rescale_q_rnd(int64_t a, AVRational bq, AVRational cq, enum AVRounding rnd) {
    auto ret = create_empty_ret(av_rescale_q_rnd);
    auto a1 = get_addresses_of_parameters(a, bq, cq, rnd);
    qge_CallNativeProc(DynamicApis::pav_rescale_q_rnd, a1.data(), &ret);
    return ret;
}

int av_compare_ts(int64_t ts_a, AVRational tb_a, int64_t ts_b, AVRational tb_b) {
    auto ret = create_empty_ret(av_compare_ts);
    auto a = get_addresses_of_parameters(ts_a, tb_a, ts_b, tb_b);
    qge_CallNativeProc(DynamicApis::pav_compare_ts, a.data(), &ret);
    return ret;
}

int64_t av_rescale_delta(AVRational in_tb, int64_t in_ts, AVRational fs_tb, int duration,
                         int64_t *last, AVRational out_tb) {
    auto ret = create_empty_ret(av_rescale_delta);
    auto a = get_addresses_of_parameters(in_tb, in_ts, fs_tb, duration, last, out_tb);
    qge_CallNativeProc(DynamicApis::pav_rescale_delta, a.data(), &ret);
    return ret;
}

void *av_malloc(size_t size) {
    auto ret = create_empty_ret(av_malloc);
    auto a = get_addresses_of_parameters(size);
    qge_CallNativeProc(DynamicApis::pav_malloc, a.data(), &ret);
    return ret;
}

void *av_mallocz(size_t size) {
    auto ret = create_empty_ret(av_mallocz);
    auto a = get_addresses_of_parameters(size);
    qge_CallNativeProc(DynamicApis::pav_mallocz, a.data(), &ret);
    return ret;
}

void *av_malloc_array(size_t nmemb, size_t size) {
    auto ret = create_empty_ret(av_malloc_array);
    auto a = get_addresses_of_parameters(nmemb, size);
    qge_CallNativeProc(DynamicApis::pav_malloc_array, a.data(), &ret);
    return ret;
}

void *av_calloc(size_t nmemb, size_t size) {
    auto ret = create_empty_ret(av_calloc);
    auto a = get_addresses_of_parameters(nmemb, size);
    qge_CallNativeProc(DynamicApis::pav_calloc, a.data(), &ret);
    return ret;
}

void *av_realloc_f(void *ptr, size_t nelem, size_t elsize) {
    auto ret = create_empty_ret(av_realloc_f);
    auto a = get_addresses_of_parameters(ptr, nelem, elsize);
    qge_CallNativeProc(DynamicApis::pav_realloc_f, a.data(), &ret);
    return ret;
}

void *av_realloc_array(void *ptr, size_t nmemb, size_t size) {
    auto ret = create_empty_ret(av_realloc_array);
    auto a = get_addresses_of_parameters(ptr, nmemb, size);
    qge_CallNativeProc(DynamicApis::pav_realloc_array, a.data(), &ret);
    return ret;
}

int av_reallocp_array(void *ptr, size_t nmemb, size_t size) {
    auto ret = create_empty_ret(av_reallocp_array);
    auto a = get_addresses_of_parameters(ptr, nmemb, size);
    qge_CallNativeProc(DynamicApis::pav_reallocp_array, a.data(), &ret);
    return ret;
}

void av_free(void *ptr) {
    auto a = get_addresses_of_parameters(ptr);
    qge_CallNativeProc(DynamicApis::pav_free, a.data(), nullptr);
}

void av_freep(void *ptr) {
    auto a = get_addresses_of_parameters(ptr);
    qge_CallNativeProc(DynamicApis::pav_freep, a.data(), nullptr);
}

char *av_strdup(const char *s) {
    auto ret = create_empty_ret(av_strdup);
    auto a = get_addresses_of_parameters(s);
    qge_CallNativeProc(DynamicApis::pav_strdup, a.data(), &ret);
    return ret;
}

char *av_strndup(const char *s, size_t len) {
    auto ret = create_empty_ret(av_strndup);
    auto a = get_addresses_of_parameters(s, len);
    qge_CallNativeProc(DynamicApis::pav_strndup, a.data(), &ret);
    return ret;
}

void *av_memdup(const void *p, size_t size) {
    auto ret = create_empty_ret(av_memdup);
    auto a = get_addresses_of_parameters(p, size);
    qge_CallNativeProc(DynamicApis::pav_memdup, a.data(), &ret);
    return ret;
}

int av_dynarray_add_nofree(void *tab_ptr, int *nb_ptr, void *elem) {
    auto ret = create_empty_ret(av_dynarray_add_nofree);
    auto a = get_addresses_of_parameters(tab_ptr, nb_ptr, elem);
    qge_CallNativeProc(DynamicApis::pav_dynarray_add_nofree, a.data(), &ret);
    return ret;
}

void av_max_alloc(size_t max) {
    auto a = get_addresses_of_parameters(max);
    qge_CallNativeProc(DynamicApis::pav_max_alloc, a.data(), nullptr);
}

const char *av_get_sample_fmt_name(enum AVSampleFormat sample_fmt) {
    auto ret = create_empty_ret(av_get_sample_fmt_name);
    auto a = get_addresses_of_parameters(sample_fmt);
    qge_CallNativeProc(DynamicApis::pav_get_sample_fmt_name, a.data(), &ret);
    return ret;
}

enum AVSampleFormat av_get_sample_fmt(const char *name) {
    auto ret = create_empty_ret(av_get_sample_fmt);
    auto a = get_addresses_of_parameters(name);
    qge_CallNativeProc(DynamicApis::pav_get_sample_fmt, a.data(), &ret);
    return ret;
}

char *av_get_sample_fmt_string(char *buf, int buf_size, enum AVSampleFormat sample_fmt) {
    auto ret = create_empty_ret(av_get_sample_fmt_string);
    auto a = get_addresses_of_parameters(buf, buf_size, sample_fmt);
    qge_CallNativeProc(DynamicApis::pav_get_sample_fmt_string, a.data(), &ret);
    return ret;
}

int av_get_bytes_per_sample(enum AVSampleFormat sample_fmt) {
    auto ret = create_empty_ret(av_get_bytes_per_sample);
    auto a = get_addresses_of_parameters(sample_fmt);
    qge_CallNativeProc(DynamicApis::pav_get_bytes_per_sample, a.data(), &ret);
    return ret;
}

AVFifo *av_fifo_alloc2(size_t elems, size_t elem_size, unsigned int flags) {
    auto ret = create_empty_ret(av_fifo_alloc2);
    auto a = get_addresses_of_parameters(elems, elem_size, flags);
    qge_CallNativeProc(DynamicApis::pav_fifo_alloc2, a.data(), &ret);
    return ret;
}

size_t av_fifo_can_read(const AVFifo *f) {
    auto ret = create_empty_ret(av_fifo_can_read);
    auto a = get_addresses_of_parameters(f);
    qge_CallNativeProc(DynamicApis::pav_fifo_can_read, a.data(), &ret);
    return ret;
}

size_t av_fifo_can_write(const AVFifo *f) {
    auto ret = create_empty_ret(av_fifo_can_write);
    auto a = get_addresses_of_parameters(f);
    qge_CallNativeProc(DynamicApis::pav_fifo_can_write, a.data(), &ret);
    return ret;
}

int av_fifo_grow2(AVFifo *f, size_t inc) {
    auto ret = create_empty_ret(av_fifo_grow2);
    auto a = get_addresses_of_parameters(f, inc);
    qge_CallNativeProc(DynamicApis::pav_fifo_grow2, a.data(), &ret);
    return ret;
}

int av_fifo_write(AVFifo *f, const void *buf, size_t nb_elems) {
    auto ret = create_empty_ret(av_fifo_write);
    auto a = get_addresses_of_parameters(f, buf, nb_elems);
    qge_CallNativeProc(DynamicApis::pav_fifo_write, a.data(), &ret);
    return ret;
}

int av_fifo_read(AVFifo *f, void *buf, size_t nb_elems) {
    auto ret = create_empty_ret(av_fifo_read);
    auto a = get_addresses_of_parameters(f, buf, nb_elems);
    qge_CallNativeProc(DynamicApis::pav_fifo_read, a.data(), &ret);
    return ret;
}

void av_fifo_freep2(AVFifo **f) {
    auto a = get_addresses_of_parameters(f);
    qge_CallNativeProc(DynamicApis::pav_fifo_freep2, a.data(), nullptr);
}

int av_strstart(const char *str, const char *pfx, const char **ptr) {
    auto ret = create_empty_ret(av_strstart);
    auto a = get_addresses_of_parameters(str, pfx, ptr);
    qge_CallNativeProc(DynamicApis::pav_strstart, a.data(), &ret);
    return ret;
}

size_t av_strlcpy(char *dst, const char *src, size_t size) {
    auto ret = create_empty_ret(av_strlcpy);
    auto a = get_addresses_of_parameters(dst, src, size);
    qge_CallNativeProc(DynamicApis::pav_strlcpy, a.data(), &ret);
    return ret;
}

size_t av_strlcat(char *dst, const char *src, size_t size) {
    auto ret = create_empty_ret(av_strlcat);
    auto a = get_addresses_of_parameters(dst, src, size);
    qge_CallNativeProc(DynamicApis::pav_strlcat, a.data(), &ret);
    return ret;
}

char *av_get_token(const char **buf, const char *term) {
    auto ret = create_empty_ret(av_get_token);
    auto a = get_addresses_of_parameters(buf, term);
    qge_CallNativeProc(DynamicApis::pav_get_token, a.data(), &ret);
    return ret;
}

char *av_strtok(char *s, const char *delim, char **saveptr) {
    auto ret = create_empty_ret(av_strtok);
    auto a = get_addresses_of_parameters(s, delim, saveptr);
    qge_CallNativeProc(DynamicApis::pav_strtok, a.data(), &ret);
    return ret;
}

int av_strcasecmp(const char *a, const char *b) {
    auto ret = create_empty_ret(av_strcasecmp);
    auto a1 = get_addresses_of_parameters(a, b);
    qge_CallNativeProc(DynamicApis::pav_strcasecmp, a1.data(), &ret);
    return ret;
}

int av_match_name(const char *name, const char *names) {
    auto ret = create_empty_ret(av_match_name);
    auto a = get_addresses_of_parameters(name, names);
    qge_CallNativeProc(DynamicApis::pav_match_name, a.data(), &ret);
    return ret;
}

void av_bprint_init(AVBPrint *buf, unsigned int size_init, unsigned int size_max) {
    auto a = get_addresses_of_parameters(buf, size_init, size_max);
    qge_CallNativeProc(DynamicApis::pav_bprint_init, a.data(), nullptr);
}

void av_bprint_chars(AVBPrint *buf, char c, unsigned int n) {
    auto a = get_addresses_of_parameters(buf, c, n);
    qge_CallNativeProc(DynamicApis::pav_bprint_chars, a.data(), nullptr);
}

void av_bprint_clear(AVBPrint *buf) {
    auto a = get_addresses_of_parameters(buf);
    qge_CallNativeProc(DynamicApis::pav_bprint_clear, a.data(), nullptr);
}

int av_bprint_finalize(AVBPrint *buf, char **ret_str) {
    auto ret = create_empty_ret(av_bprint_finalize);
    auto a = get_addresses_of_parameters(buf, ret_str);
    qge_CallNativeProc(DynamicApis::pav_bprint_finalize, a.data(), &ret);
    return ret;
}

AVBufferRef *av_buffer_ref(const AVBufferRef *buf) {
    auto ret = create_empty_ret(av_buffer_ref);
    auto a = get_addresses_of_parameters(buf);
    qge_CallNativeProc(DynamicApis::pav_buffer_ref, a.data(), &ret);
    return ret;
}

void av_buffer_unref(AVBufferRef **buf) {
    auto a = get_addresses_of_parameters(buf);
    qge_CallNativeProc(DynamicApis::pav_buffer_unref, a.data(), nullptr);
}

AVDictionaryEntry *av_dict_get(const AVDictionary *m, const char *key,
                               const AVDictionaryEntry *prev, int flags) {
    auto ret = create_empty_ret(av_dict_get);
    auto a = get_addresses_of_parameters(m, key, prev, flags);
    qge_CallNativeProc(DynamicApis::pav_dict_get, a.data(), &ret);
    return ret;
}

int av_dict_set(AVDictionary **pm, const char *key, const char *value, int flags) {
    auto ret = create_empty_ret(av_dict_set);
    auto a = get_addresses_of_parameters(pm, key, value, flags);
    qge_CallNativeProc(DynamicApis::pav_dict_set, a.data(), &ret);
    return ret;
}

int av_dict_set_int(AVDictionary **pm, const char *key, int64_t value, int flags) {
    auto ret = create_empty_ret(av_dict_set_int);
    auto a = get_addresses_of_parameters(pm, key, value, flags);
    qge_CallNativeProc(DynamicApis::pav_dict_set_int, a.data(), &ret);
    return ret;
}

int av_dict_parse_string(AVDictionary **pm, const char *str, const char *key_val_sep,
                         const char *pairs_sep, int flags) {
    auto ret = create_empty_ret(av_dict_parse_string);
    auto a = get_addresses_of_parameters(pm, str, key_val_sep, pairs_sep, flags);
    qge_CallNativeProc(DynamicApis::pav_dict_parse_string, a.data(), &ret);
    return ret;
}

int av_dict_copy(AVDictionary **dst, const AVDictionary *src, int flags) {
    auto ret = create_empty_ret(av_dict_copy);
    auto a = get_addresses_of_parameters(dst, src, flags);
    qge_CallNativeProc(DynamicApis::pav_dict_copy, a.data(), &ret);
    return ret;
}

void av_dict_free(AVDictionary **m) {
    auto a = get_addresses_of_parameters(m);
    qge_CallNativeProc(DynamicApis::pav_dict_free, a.data(), nullptr);
}

int64_t av_gettime_relative(void) {
    auto ret = create_empty_ret(av_gettime_relative);
    auto a = get_addresses_of_parameters();
    qge_CallNativeProc(DynamicApis::pav_gettime_relative, a.data(), &ret);
    return ret;
}

int av_usleep(unsigned int usec) {
    auto ret = create_empty_ret(av_usleep);
    auto a = get_addresses_of_parameters(usec);
    qge_CallNativeProc(DynamicApis::pav_usleep, a.data(), &ret);
    return ret;
}

uint64_t av_get_channel_layout(const char *name) {
    auto ret = create_empty_ret(av_get_channel_layout);
    auto a = get_addresses_of_parameters(name);
    qge_CallNativeProc(DynamicApis::pav_get_channel_layout, a.data(), &ret);
    return ret;
}

int av_channel_name(char *buf, size_t buf_size, enum AVChannel channel) {
    auto ret = create_empty_ret(av_channel_name);
    auto a = get_addresses_of_parameters(buf, buf_size, channel);
    qge_CallNativeProc(DynamicApis::pav_channel_name, a.data(), &ret);
    return ret;
}

int av_channel_description(char *buf, size_t buf_size, enum AVChannel channel) {
    auto ret = create_empty_ret(av_channel_description);
    auto a = get_addresses_of_parameters(buf, buf_size, channel);
    qge_CallNativeProc(DynamicApis::pav_channel_description, a.data(), &ret);
    return ret;
}

int av_channel_layout_from_mask(AVChannelLayout *channel_layout, uint64_t mask) {
    auto ret = create_empty_ret(av_channel_layout_from_mask);
    auto a = get_addresses_of_parameters(channel_layout, mask);
    qge_CallNativeProc(DynamicApis::pav_channel_layout_from_mask, a.data(), &ret);
    return ret;
}

int av_channel_layout_from_string(AVChannelLayout *channel_layout, const char *str) {
    auto ret = create_empty_ret(av_channel_layout_from_string);
    auto a = get_addresses_of_parameters(channel_layout, str);
    qge_CallNativeProc(DynamicApis::pav_channel_layout_from_string, a.data(), &ret);
    return ret;
}

void av_channel_layout_default(AVChannelLayout *ch_layout, int nb_channels) {
    auto a = get_addresses_of_parameters(ch_layout, nb_channels);
    qge_CallNativeProc(DynamicApis::pav_channel_layout_default, a.data(), nullptr);
}

const AVChannelLayout *av_channel_layout_standard(void **opaque) {
    auto ret = create_empty_ret(av_channel_layout_standard);
    auto a = get_addresses_of_parameters(opaque);
    qge_CallNativeProc(DynamicApis::pav_channel_layout_standard, a.data(), &ret);
    return ret;
}

void av_channel_layout_uninit(AVChannelLayout *channel_layout) {
    auto a = get_addresses_of_parameters(channel_layout);
    qge_CallNativeProc(DynamicApis::pav_channel_layout_uninit, a.data(), nullptr);
}

int av_channel_layout_copy(AVChannelLayout *dst, const AVChannelLayout *src) {
    auto ret = create_empty_ret(av_channel_layout_copy);
    auto a = get_addresses_of_parameters(dst, src);
    qge_CallNativeProc(DynamicApis::pav_channel_layout_copy, a.data(), &ret);
    return ret;
}

int av_channel_layout_describe(const AVChannelLayout *channel_layout, char *buf, size_t buf_size) {
    auto ret = create_empty_ret(av_channel_layout_describe);
    auto a = get_addresses_of_parameters(channel_layout, buf, buf_size);
    qge_CallNativeProc(DynamicApis::pav_channel_layout_describe, a.data(), &ret);
    return ret;
}

int av_channel_layout_describe_bprint(const AVChannelLayout *channel_layout, struct AVBPrint *bp) {
    auto ret = create_empty_ret(av_channel_layout_describe_bprint);
    auto a = get_addresses_of_parameters(channel_layout, bp);
    qge_CallNativeProc(DynamicApis::pav_channel_layout_describe_bprint, a.data(), &ret);
    return ret;
}

int av_channel_layout_index_from_channel(const AVChannelLayout *channel_layout,
                                         enum AVChannel channel) {
    auto ret = create_empty_ret(av_channel_layout_index_from_channel);
    auto a = get_addresses_of_parameters(channel_layout, channel);
    qge_CallNativeProc(DynamicApis::pav_channel_layout_index_from_channel, a.data(), &ret);
    return ret;
}

int av_channel_layout_check(const AVChannelLayout *channel_layout) {
    auto ret = create_empty_ret(av_channel_layout_check);
    auto a = get_addresses_of_parameters(channel_layout);
    qge_CallNativeProc(DynamicApis::pav_channel_layout_check, a.data(), &ret);
    return ret;
}

int av_channel_layout_compare(const AVChannelLayout *chl, const AVChannelLayout *chl1) {
    auto ret = create_empty_ret(av_channel_layout_compare);
    auto a = get_addresses_of_parameters(chl, chl1);
    qge_CallNativeProc(DynamicApis::pav_channel_layout_compare, a.data(), &ret);
    return ret;
}

int av_opt_show2(void *obj, void *av_log_obj, int req_flags, int rej_flags) {
    auto ret = create_empty_ret(av_opt_show2);
    auto a = get_addresses_of_parameters(obj, av_log_obj, req_flags, rej_flags);
    qge_CallNativeProc(DynamicApis::pav_opt_show2, a.data(), &ret);
    return ret;
}

int av_opt_set_dict(void *obj, struct AVDictionary **options) {
    auto ret = create_empty_ret(av_opt_set_dict);
    auto a = get_addresses_of_parameters(obj, options);
    qge_CallNativeProc(DynamicApis::pav_opt_set_dict, a.data(), &ret);
    return ret;
}

int av_opt_get_key_value(const char **ropts, const char *key_val_sep, const char *pairs_sep,
                         unsigned int flags, char **rkey, char **rval) {
    auto ret = create_empty_ret(av_opt_get_key_value);
    auto a = get_addresses_of_parameters(ropts, key_val_sep, pairs_sep, flags, rkey, rval);
    qge_CallNativeProc(DynamicApis::pav_opt_get_key_value, a.data(), &ret);
    return ret;
}

int av_opt_eval_flags(void *obj, const AVOption *o, const char *val, int *flags_out) {
    auto ret = create_empty_ret(av_opt_eval_flags);
    auto a = get_addresses_of_parameters(obj, o, val, flags_out);
    qge_CallNativeProc(DynamicApis::pav_opt_eval_flags, a.data(), &ret);
    return ret;
}

int av_opt_eval_int(void *obj, const AVOption *o, const char *val, int *int_out) {
    auto ret = create_empty_ret(av_opt_eval_int);
    auto a = get_addresses_of_parameters(obj, o, val, int_out);
    qge_CallNativeProc(DynamicApis::pav_opt_eval_int, a.data(), &ret);
    return ret;
}

const AVOption *av_opt_find(void *obj, const char *name, const char *unit, int opt_flags,
                            int search_flags) {
    auto ret = create_empty_ret(av_opt_find);
    auto a = get_addresses_of_parameters(obj, name, unit, opt_flags, search_flags);
    qge_CallNativeProc(DynamicApis::pav_opt_find, a.data(), &ret);
    return ret;
}

const AVClass *av_opt_child_class_iterate(const AVClass *parent, void **iter) {
    auto ret = create_empty_ret(av_opt_child_class_iterate);
    auto a = get_addresses_of_parameters(parent, iter);
    qge_CallNativeProc(DynamicApis::pav_opt_child_class_iterate, a.data(), &ret);
    return ret;
}

int av_opt_set(void *obj, const char *name, const char *val, int search_flags) {
    auto ret = create_empty_ret(av_opt_set);
    auto a = get_addresses_of_parameters(obj, name, val, search_flags);
    qge_CallNativeProc(DynamicApis::pav_opt_set, a.data(), &ret);
    return ret;
}

int av_opt_set_int(void *obj, const char *name, int64_t val, int search_flags) {
    auto ret = create_empty_ret(av_opt_set_int);
    auto a = get_addresses_of_parameters(obj, name, val, search_flags);
    qge_CallNativeProc(DynamicApis::pav_opt_set_int, a.data(), &ret);
    return ret;
}

int av_get_cpu_flags(void) {
    auto ret = create_empty_ret(av_get_cpu_flags);
    auto a = get_addresses_of_parameters();
    qge_CallNativeProc(DynamicApis::pav_get_cpu_flags, a.data(), &ret);
    return ret;
}

void av_force_cpu_flags(int flags) {
    auto a = get_addresses_of_parameters(flags);
    qge_CallNativeProc(DynamicApis::pav_force_cpu_flags, a.data(), nullptr);
}

int av_parse_cpu_caps(unsigned int *flags, const char *s) {
    auto ret = create_empty_ret(av_parse_cpu_caps);
    auto a = get_addresses_of_parameters(flags, s);
    qge_CallNativeProc(DynamicApis::pav_parse_cpu_caps, a.data(), &ret);
    return ret;
}

void av_cpu_force_count(int count) {
    auto a = get_addresses_of_parameters(count);
    qge_CallNativeProc(DynamicApis::pav_cpu_force_count, a.data(), nullptr);
}

AVFrame *av_frame_alloc(void) {
    auto ret = create_empty_ret(av_frame_alloc);
    auto a = get_addresses_of_parameters();
    qge_CallNativeProc(DynamicApis::pav_frame_alloc, a.data(), &ret);
    return ret;
}

void av_frame_free(AVFrame **frame) {
    auto a = get_addresses_of_parameters(frame);
    qge_CallNativeProc(DynamicApis::pav_frame_free, a.data(), nullptr);
}

AVFrame *av_frame_clone(const AVFrame *src) {
    auto ret = create_empty_ret(av_frame_clone);
    auto a = get_addresses_of_parameters(src);
    qge_CallNativeProc(DynamicApis::pav_frame_clone, a.data(), &ret);
    return ret;
}

void av_frame_unref(AVFrame *frame) {
    auto a = get_addresses_of_parameters(frame);
    qge_CallNativeProc(DynamicApis::pav_frame_unref, a.data(), nullptr);
}

void av_frame_move_ref(AVFrame *dst, AVFrame *src) {
    auto a = get_addresses_of_parameters(dst, src);
    qge_CallNativeProc(DynamicApis::pav_frame_move_ref, a.data(), nullptr);
}

int av_frame_get_buffer(AVFrame *frame, int align) {
    auto ret = create_empty_ret(av_frame_get_buffer);
    auto a = get_addresses_of_parameters(frame, align);
    qge_CallNativeProc(DynamicApis::pav_frame_get_buffer, a.data(), &ret);
    return ret;
}

int av_frame_copy_props(AVFrame *dst, const AVFrame *src) {
    auto ret = create_empty_ret(av_frame_copy_props);
    auto a = get_addresses_of_parameters(dst, src);
    qge_CallNativeProc(DynamicApis::pav_frame_copy_props, a.data(), &ret);
    return ret;
}

AVFrameSideData *av_frame_get_side_data(const AVFrame *frame, enum AVFrameSideDataType type) {
    auto ret = create_empty_ret(av_frame_get_side_data);
    auto a = get_addresses_of_parameters(frame, type);
    qge_CallNativeProc(DynamicApis::pav_frame_get_side_data, a.data(), &ret);
    return ret;
}

double av_display_rotation_get(const int32_t matrix[9]) {
    auto ret = create_empty_ret(av_display_rotation_get);
    auto a = get_addresses_of_parameters(matrix);
    qge_CallNativeProc(DynamicApis::pav_display_rotation_get, a.data(), &ret);
    return ret;
}

void av_display_rotation_set(int32_t matrix[9], double angle) {
    auto a = get_addresses_of_parameters(matrix, angle);
    qge_CallNativeProc(DynamicApis::pav_display_rotation_set, a.data(), nullptr);
}

int av_expr_parse(AVExpr **expr, const char *s, const char *const *const_names,
                  const char *const *func1_names, double (*const *funcs1)(void *, double),
                  const char *const *func2_names, double (*const *funcs2)(void *, double, double),
                  int log_offset, void *log_ctx) {
    auto ret = create_empty_ret(av_expr_parse);
    auto a = get_addresses_of_parameters(expr, s, const_names, func1_names, funcs1, func2_names,
                                         funcs2, log_offset, log_ctx);
    qge_CallNativeProc(DynamicApis::pav_expr_parse, a.data(), &ret);
    return ret;
}

double av_expr_eval(AVExpr *e, const double *const_values, void *opaque) {
    auto ret = create_empty_ret(av_expr_eval);
    auto a = get_addresses_of_parameters(e, const_values, opaque);
    qge_CallNativeProc(DynamicApis::pav_expr_eval, a.data(), &ret);
    return ret;
}

void av_expr_free(AVExpr *e) {
    auto a = get_addresses_of_parameters(e);
    qge_CallNativeProc(DynamicApis::pav_expr_free, a.data(), nullptr);
}

double av_strtod(const char *numstr, char **tail) {
    auto ret = create_empty_ret(av_strtod);
    auto a = get_addresses_of_parameters(numstr, tail);
    qge_CallNativeProc(DynamicApis::pav_strtod, a.data(), &ret);
    return ret;
}

int av_get_bits_per_pixel(const AVPixFmtDescriptor *pixdesc) {
    auto ret = create_empty_ret(av_get_bits_per_pixel);
    auto a = get_addresses_of_parameters(pixdesc);
    qge_CallNativeProc(DynamicApis::pav_get_bits_per_pixel, a.data(), &ret);
    return ret;
}

const AVPixFmtDescriptor *av_pix_fmt_desc_get(enum AVPixelFormat pix_fmt) {
    auto ret = create_empty_ret(av_pix_fmt_desc_get);
    auto a = get_addresses_of_parameters(pix_fmt);
    qge_CallNativeProc(DynamicApis::pav_pix_fmt_desc_get, a.data(), &ret);
    return ret;
}

const AVPixFmtDescriptor *av_pix_fmt_desc_next(const AVPixFmtDescriptor *prev) {
    auto ret = create_empty_ret(av_pix_fmt_desc_next);
    auto a = get_addresses_of_parameters(prev);
    qge_CallNativeProc(DynamicApis::pav_pix_fmt_desc_next, a.data(), &ret);
    return ret;
}

enum AVPixelFormat av_pix_fmt_desc_get_id(const AVPixFmtDescriptor *desc) {
    auto ret = create_empty_ret(av_pix_fmt_desc_get_id);
    auto a = get_addresses_of_parameters(desc);
    qge_CallNativeProc(DynamicApis::pav_pix_fmt_desc_get_id, a.data(), &ret);
    return ret;
}

enum AVPixelFormat av_get_pix_fmt(const char *name) {
    auto ret = create_empty_ret(av_get_pix_fmt);
    auto a = get_addresses_of_parameters(name);
    qge_CallNativeProc(DynamicApis::pav_get_pix_fmt, a.data(), &ret);
    return ret;
}

const char *av_get_pix_fmt_name(enum AVPixelFormat pix_fmt) {
    auto ret = create_empty_ret(av_get_pix_fmt_name);
    auto a = get_addresses_of_parameters(pix_fmt);
    qge_CallNativeProc(DynamicApis::pav_get_pix_fmt_name, a.data(), &ret);
    return ret;
}

enum AVPixelFormat av_find_best_pix_fmt_of_2(enum AVPixelFormat dst_pix_fmt1,
                                             enum AVPixelFormat dst_pix_fmt2,
                                             enum AVPixelFormat src_pix_fmt, int has_alpha,
                                             int *loss_ptr) {
    auto ret = create_empty_ret(av_find_best_pix_fmt_of_2);
    auto a =
        get_addresses_of_parameters(dst_pix_fmt1, dst_pix_fmt2, src_pix_fmt, has_alpha, loss_ptr);
    qge_CallNativeProc(DynamicApis::pav_find_best_pix_fmt_of_2, a.data(), &ret);
    return ret;
}

enum AVHWDeviceType av_hwdevice_find_type_by_name(const char *name) {
    auto ret = create_empty_ret(av_hwdevice_find_type_by_name);
    auto a = get_addresses_of_parameters(name);
    qge_CallNativeProc(DynamicApis::pav_hwdevice_find_type_by_name, a.data(), &ret);
    return ret;
}

const char *av_hwdevice_get_type_name(enum AVHWDeviceType type) {
    auto ret = create_empty_ret(av_hwdevice_get_type_name);
    auto a = get_addresses_of_parameters(type);
    qge_CallNativeProc(DynamicApis::pav_hwdevice_get_type_name, a.data(), &ret);
    return ret;
}

enum AVHWDeviceType av_hwdevice_iterate_types(enum AVHWDeviceType prev) {
    auto ret = create_empty_ret(av_hwdevice_iterate_types);
    auto a = get_addresses_of_parameters(prev);
    qge_CallNativeProc(DynamicApis::pav_hwdevice_iterate_types, a.data(), &ret);
    return ret;
}

int av_hwdevice_ctx_create(AVBufferRef **device_ctx, enum AVHWDeviceType type, const char *device,
                           AVDictionary *opts, int flags) {
    auto ret = create_empty_ret(av_hwdevice_ctx_create);
    auto a = get_addresses_of_parameters(device_ctx, type, device, opts, flags);
    qge_CallNativeProc(DynamicApis::pav_hwdevice_ctx_create, a.data(), &ret);
    return ret;
}

int av_hwdevice_ctx_create_derived(AVBufferRef **dst_ctx, enum AVHWDeviceType type,
                                   AVBufferRef *src_ctx, int flags) {
    auto ret = create_empty_ret(av_hwdevice_ctx_create_derived);
    auto a = get_addresses_of_parameters(dst_ctx, type, src_ctx, flags);
    qge_CallNativeProc(DynamicApis::pav_hwdevice_ctx_create_derived, a.data(), &ret);
    return ret;
}

int av_hwframe_transfer_data(AVFrame *dst, const AVFrame *src, int flags) {
    auto ret = create_empty_ret(av_hwframe_transfer_data);
    auto a = get_addresses_of_parameters(dst, src, flags);
    qge_CallNativeProc(DynamicApis::pav_hwframe_transfer_data, a.data(), &ret);
    return ret;
}

int av_parse_ratio(AVRational *q, const char *str, int max, int log_offset, void *log_ctx) {
    auto ret = create_empty_ret(av_parse_ratio);
    auto a = get_addresses_of_parameters(q, str, max, log_offset, log_ctx);
    qge_CallNativeProc(DynamicApis::pav_parse_ratio, a.data(), &ret);
    return ret;
}

int av_parse_video_size(int *width_ptr, int *height_ptr, const char *str) {
    auto ret = create_empty_ret(av_parse_video_size);
    auto a = get_addresses_of_parameters(width_ptr, height_ptr, str);
    qge_CallNativeProc(DynamicApis::pav_parse_video_size, a.data(), &ret);
    return ret;
}

int av_parse_video_rate(AVRational *rate, const char *str) {
    auto ret = create_empty_ret(av_parse_video_rate);
    auto a = get_addresses_of_parameters(rate, str);
    qge_CallNativeProc(DynamicApis::pav_parse_video_rate, a.data(), &ret);
    return ret;
}

const char *av_get_known_color_name(int color_idx, const uint8_t **rgb) {
    auto ret = create_empty_ret(av_get_known_color_name);
    auto a = get_addresses_of_parameters(color_idx, rgb);
    qge_CallNativeProc(DynamicApis::pav_get_known_color_name, a.data(), &ret);
    return ret;
}

int av_parse_time(int64_t *timeval, const char *timestr, int duration) {
    auto ret = create_empty_ret(av_parse_time);
    auto a = get_addresses_of_parameters(timeval, timestr, duration);
    qge_CallNativeProc(DynamicApis::pav_parse_time, a.data(), &ret);
    return ret;
}

int av_thread_message_queue_alloc(AVThreadMessageQueue **mq, unsigned int nelem,
                                  unsigned int elsize) {
    auto ret = create_empty_ret(av_thread_message_queue_alloc);
    auto a = get_addresses_of_parameters(mq, nelem, elsize);
    qge_CallNativeProc(DynamicApis::pav_thread_message_queue_alloc, a.data(), &ret);
    return ret;
}

void av_thread_message_queue_free(AVThreadMessageQueue **mq) {
    auto a = get_addresses_of_parameters(mq);
    qge_CallNativeProc(DynamicApis::pav_thread_message_queue_free, a.data(), nullptr);
}

int av_thread_message_queue_send(AVThreadMessageQueue *mq, void *msg, unsigned int flags) {
    auto ret = create_empty_ret(av_thread_message_queue_send);
    auto a = get_addresses_of_parameters(mq, msg, flags);
    qge_CallNativeProc(DynamicApis::pav_thread_message_queue_send, a.data(), &ret);
    return ret;
}

int av_thread_message_queue_recv(AVThreadMessageQueue *mq, void *msg, unsigned int flags) {
    auto ret = create_empty_ret(av_thread_message_queue_recv);
    auto a = get_addresses_of_parameters(mq, msg, flags);
    qge_CallNativeProc(DynamicApis::pav_thread_message_queue_recv, a.data(), &ret);
    return ret;
}

void av_thread_message_queue_set_err_send(AVThreadMessageQueue *mq, int err) {
    auto a = get_addresses_of_parameters(mq, err);
    qge_CallNativeProc(DynamicApis::pav_thread_message_queue_set_err_send, a.data(), nullptr);
}

void av_thread_message_queue_set_err_recv(AVThreadMessageQueue *mq, int err) {
    auto a = get_addresses_of_parameters(mq, err);
    qge_CallNativeProc(DynamicApis::pav_thread_message_queue_set_err_recv, a.data(), nullptr);
}

void av_log_set_callback_help(void) {
    auto a = get_addresses_of_parameters();
    qge_CallNativeProc(DynamicApis::pav_log_set_callback_help, a.data(), nullptr);
}

void av_log_set_callback_report(int *_p_report_file_level, FILE *_report_file) {
    auto a = get_addresses_of_parameters(_p_report_file_level, _report_file);
    qge_CallNativeProc(DynamicApis::pav_log_set_callback_report, a.data(), nullptr);
}

void av_vlog(void *avcl, int level, const char *fmt, va_list vl) {
    auto a = get_addresses_of_parameters(avcl, level, fmt, vl);
    qge_CallNativeProc(DynamicApis::pav_vlog, a.data(), nullptr);
}

int av_bprint_alloc(AVBPrint *buf, unsigned room) {
    auto ret = create_empty_ret(av_bprint_alloc);
    auto a = get_addresses_of_parameters(buf, room);
    qge_CallNativeProc(DynamicApis::pav_bprint_alloc, a.data(), &ret);
    return ret;
}

void av_bprint_grow(AVBPrint *buf, unsigned extra_len) {
    auto a = get_addresses_of_parameters(buf, extra_len);
    qge_CallNativeProc(DynamicApis::pav_bprint_grow, a.data(), nullptr);
}

int avutil_decode_interrupt_cb(void *ctx) {
    auto ret = create_empty_ret(avutil_decode_interrupt_cb);
    auto a = get_addresses_of_parameters(ctx);
    qge_CallNativeProc(DynamicApis::pavutil_decode_interrupt_cb, a.data(), &ret);
    return ret;
}

void avutil_transcode_init_done(int *val, int get) {
    auto a = get_addresses_of_parameters(val, get);
    qge_CallNativeProc(DynamicApis::pavutil_transcode_init_done, a.data(), nullptr);
}

volatile int *avutil_received_nb_signals_ptr(void) {
    auto ret = create_empty_ret(avutil_received_nb_signals_ptr);
    auto a = get_addresses_of_parameters();
    qge_CallNativeProc(DynamicApis::pavutil_received_nb_signals_ptr, a.data(), &ret);
    return ret;
}