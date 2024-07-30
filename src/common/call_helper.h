#ifndef CALL_HELPER_H
#define CALL_HELPER_H

#include <iostream>
#include <tuple>
#include <functional>
#include <type_traits>

// 助手模板用于提取函数参数类型
template <typename T>
struct function_traits;

template <typename Ret, typename... Args>
struct function_traits<Ret (*)(Args...)> {
    using return_type = Ret;
    using tuple_type = std::tuple<Args...>;
};

// 将void指针数组转换为元组
template <typename Tuple, std::size_t... I>
Tuple void_pointers_to_tuple(void *arr[], std::index_sequence<I...>) {
    return std::make_tuple(*static_cast<typename std::tuple_element<I, Tuple>::type *>(arr[I])...);
}

// 用户调用的函数
template <typename Func, typename... Args>
decltype(auto) call_function(Func func, void **ptrs) {
    using tuple_type = typename function_traits<Func>::tuple_type;
    constexpr auto tuple_size = std::tuple_size_v<tuple_type>;
    auto args_tuple =
        void_pointers_to_tuple<tuple_type>(ptrs, std::make_index_sequence<tuple_size>{});
    return std::apply(func, args_tuple);
}

template <typename Func, typename... Args>
void call_function2(Func func, void **ptrs, void *ret) {
    using traits = function_traits<Func>;
    using tuple_type = typename traits::tuple_type;
    using return_type = typename traits::return_type;
    constexpr auto tuple_size = std::tuple_size<tuple_type>::value;

    auto args_tuple =
        void_pointers_to_tuple<tuple_type>(ptrs, std::make_index_sequence<tuple_size>{});

    if constexpr (std::is_void<return_type>::value) {
        // 如果返回类型为void
        std::apply(func, args_tuple);
    } else {
        // 如果返回类型不是void
        *static_cast<return_type *>(ret) = std::apply(func, args_tuple);
    }
}

#endif // CALL_HELPER_H
