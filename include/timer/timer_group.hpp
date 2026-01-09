#pragma once
#ifndef TIMERGROUP_F6CBBEF2_5EE8_4F68_87D1_D798594EFA96
#    define TIMERGROUP_F6CBBEF2_5EE8_4F68_87D1_D798594EFA96

#    include "timer_concepts.hpp"
#    include "timer_registry.hpp"

#    include <chrono>
#    include <type_traits>
#    include <utility>
#    include <ostream>

namespace Timer::Impl
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

template <typename Registry, typename Node, IsRatio TargetUnit>
// requires TimerRegistryLike<Registry, Node>
double node_time()
{
    if constexpr (IsTimerLeaf<Node>)
    {
        return Registry::template get<Node>()
            .template elapsedTime<TargetUnit>();
    }
    else
    {
        using Master = ::Timer::Impl::group_master_t<Node>;
        using Children = typename ::Timer::GroupTraits<Node>::Children;

        if constexpr (std::is_void_v<Master>)
        {
            double sum     = 0.0;

            tuple_for_each<Children>(
                [&](auto child)
                {
                    using Child  = typename decltype(child)::type;
                    sum         += node_time<Registry, Child, TargetUnit>();
                });
            return sum;
        }
        else
        {
            return Registry::template get<Master>()
                .template elapsedTime<TargetUnit>();
        }
    }
}

template <typename Registry, typename Node, IsRatio TargetUnit>
void print_node_impl(std::ostream &os, double parent_time, int indent = 0)
{
    double t     = node_time<Registry, Node, TargetUnit>();
    double ratio = parent_time > 0 ? t / parent_time : 0;

    os << std::string(indent, ' ') << typeid(Node).name() << ": " << t << " ("
       << ratio * 100 << "%)\n";

    if constexpr (IsTimerGroup<Node>)
    {
        using Master   = ::Timer::Impl::group_master_t<Node>;
        using Children = typename ::Timer::GroupTraits<Node>::Children;

        double children_sum = 0.0;

        tuple_for_each<Children>(
            [&](auto child)
            {
                using Child   = typename decltype(child)::type;
                children_sum += node_time<Registry, Child, TargetUnit>();
                print_node_impl<Registry, Child, TargetUnit>(os, t, indent + 2);
            });

        if constexpr (!std::is_void_v<Master>)
        {
            double others = t - children_sum;
            if (others > 0)
            {
                ratio = t > 0 ? others / t : 0;
                os << std::string(indent + 2, ' ') << "Others: " << others
                   << " (" << ratio * 100 << "%)\n";
            }
        }
    }
}

} // namespace Timer::Impl

namespace Timer
{
template <typename Registry, typename Node,
    ::Timer::Impl::IsRatio TargetUnit = std::chrono::seconds::period>
void print_node(std::ostream &os, int indent = 0)
{
    return ::Timer::Impl::print_node_impl<Registry, Node, TargetUnit>(os,
        ::Timer::Impl::node_time<Registry, Node, TargetUnit>(), indent);
}
} // namespace Timer

#endif /* TIMERGROUP_F6CBBEF2_5EE8_4F68_87D1_D798594EFA96 */
