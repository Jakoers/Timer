#pragma once
#ifndef TIMERGROUP_F6CBBEF2_5EE8_4F68_87D1_D798594EFA96
#    define TIMERGROUP_F6CBBEF2_5EE8_4F68_87D1_D798594EFA96

#    include "timer_concepts.hpp"
#    include "timer_registry.hpp"

#    include <chrono>
#    include <type_traits>
#    include <utility>
#    include <ostream>

namespace
{
template <typename Tuple, typename F, std::size_t... I>
void tuple_for_each_impl(F &&f, std::index_sequence<I...>)
{
    (f(std::type_identity<std::tuple_element_t<I, Tuple>>{}), ...);
}

template <typename Tuple, typename F>
void tuple_for_each(F &&f)
{
    tuple_for_each_impl<Tuple>(std::forward<F>(f),
        std::make_index_sequence<std::tuple_size_v<Tuple>>{});
}

template <typename Registry, typename Node, Timer_Impl::IsRatio TargetUnit>
// requires TimerRegistryLike<Registry, Node>
double node_time()
{
    if constexpr (Timer_Impl::IsTimerLeaf<Node>)
    {
        return Registry::template get<Node>()
            .template elapsedTime<TargetUnit>();
    }
    else
    {
        double sum     = 0.0;
        using Children = typename Timer::GroupTraits<Node>::Children;

        tuple_for_each<Children>(
            [&](auto child)
            {
                using Child  = typename decltype(child)::type;
                sum         += node_time<Registry, Child, TargetUnit>();
            });
        return sum;
    }
}

template <typename Registry, typename Node, Timer_Impl::IsRatio TargetUnit>
void print_node_impl(std::ostream &os, double parent_time, int indent = 0)
{
    double t     = node_time<Registry, Node, TargetUnit>();
    double ratio = parent_time > 0 ? t / parent_time : 0;

    os << std::string(indent, ' ') << typeid(Node).name() << ": " << t << " ("
       << ratio * 100 << "%)\n";

    if constexpr (Timer_Impl::IsTimerGroup<Node>)
    {
        using Children = typename Timer::GroupTraits<Node>::Children;
        tuple_for_each<Children>(
            [&](auto child)
            {
                using Child = typename decltype(child)::type;
                print_node_impl<Registry, Child, TargetUnit>(os, t, indent + 2);
            });
    }
}

} // namespace

namespace Timer
{
template <typename Registry,
    typename Node,
    Timer_Impl::IsRatio TargetUnit = std::chrono::seconds::period>
void print_node(std::ostream &os, int indent = 0)
{
    return print_node_impl<Registry, Node, TargetUnit>(os,
        node_time<Registry, Node, TargetUnit>());
}
} // namespace Timer

#endif /* TIMERGROUP_F6CBBEF2_5EE8_4F68_87D1_D798594EFA96 */
