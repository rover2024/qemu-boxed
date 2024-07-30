#ifndef WRAPPER_HELPER_H
#define WRAPPER_HELPER_H

#include <array>
#include <tuple>
#include <type_traits>

// 助手模板用于提取函数参数类型
template <typename T>
struct function_traits;

template <typename Ret, typename... Args>
struct function_traits<Ret (*)(Args...)> {
    using return_type = Ret;
    using tuple_type = std::tuple<Args...>;
};

// 辅助函数模板，用于移除参数的const修饰符并获取其地址
template <typename T>
constexpr auto remove_const_and_get_address(T &&value) {
    using NonConstType = std::remove_const_t<std::remove_reference_t<T>>;
    return const_cast<NonConstType *>(&value);
}

// 主函数模板，用于处理函数参数，并返回一个包含所有参数地址的std::array
template <typename... Args>
constexpr auto get_addresses_of_parameters(Args &&...args) {
    return std::array<void *, sizeof...(Args)>{
        remove_const_and_get_address(std::forward<Args>(args))...,
    };
}

template <typename Func>
constexpr decltype(auto) create_empty_ret(Func func) {
    using ret_type = typename function_traits<Func>::return_type;
    if constexpr (std::is_const_v<ret_type>) {
        return std::remove_const_t<ret_type>{};
    }
    return ret_type{};
}

#endif // WRAPPER_HELPER_H
