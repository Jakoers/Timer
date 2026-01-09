#pragma once
#ifndef TIMER_CONCEPTS_A03540BD_3FE4_4B26_BB76_862C1EC3950A
#    define TIMER_CONCEPTS_A03540BD_3FE4_4B26_BB76_862C1EC3950A

#    include "timer_fwd.hpp"

#    include <ratio>
#    include <type_traits>
#    include <concepts>

#    include <string_view>

namespace Timer
{
template <typename Group>
struct GroupTraits
{
};

template <typename Node>
struct NodeName
{
    static constexpr std::string_view name = "<unnamed>";
};

} // namespace Timer

namespace Timer::Impl
{
template <typename T>
struct is_ratio: std::false_type
{
};

template <int64_t... Ns>
struct is_ratio<std::ratio<Ns...>>: std::true_type
{
};

template <typename T>
constexpr bool is_ratio_v = is_ratio<T>::value;

template <typename T>
concept IsRatio = is_ratio_v<T>;

template <typename R, typename T>
concept TimerRegistryLike = requires {
    { R::template get<T>() } -> std::same_as<::Timer::Timer &>;
};

template <typename T>
concept IsTimerLeaf = std::is_base_of_v<::Timer::TimerNode, T>;

template <typename T>
concept IsTimerGroup = std::is_base_of_v<::Timer::GroupNode, T>;

template <typename T, typename = void>
struct group_master
{
    using type = void;
};

template <typename T>
struct group_master<T, std::void_t<typename ::Timer::GroupTraits<T>::Master>>
{
    using type = typename ::Timer::GroupTraits<T>::Master;
};

template <typename T>
using group_master_t = typename group_master<T>::type;

} // namespace Timer::Impl

#endif /* TIMER_CONCEPTS_A03540BD_3FE4_4B26_BB76_862C1EC3950A */
