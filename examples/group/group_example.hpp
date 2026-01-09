#ifndef CROSSTU_EXAMPLE_ABB3EBE1_044D_477A_9E07_E4C32C0965C9
#define CROSSTU_EXAMPLE_ABB3EBE1_044D_477A_9E07_E4C32C0965C9

#include "timer/timer.hpp"

struct Timer11: Timer::TimerNode
{
};

template <>
struct Timer::NodeName<Timer11>
{
    static constexpr std::string_view name = "11";
};

struct Timer12: Timer::TimerNode
{
};

template <>
struct Timer::NodeName<Timer12>
{
    static constexpr std::string_view name = "12";
};

struct Timer21: Timer::TimerNode
{
};

template <>
struct Timer::NodeName<Timer21>
{
    static constexpr std::string_view name = "21";
};

struct Timer22: Timer::TimerNode
{
};

template <>
struct Timer::NodeName<Timer22>
{
    static constexpr std::string_view name = "22";
};

struct Timer2: Timer::TimerNode
{
};

template <>
struct Timer::NodeName<Timer2>
{
    static constexpr std::string_view name = "No naming required";
};

struct Group1: Timer::GroupNode
{
};

template <>
struct Timer::GroupTraits<Group1>
{
    using Children = std::tuple<Timer11, Timer12>;
};

template <>
struct Timer::NodeName<Group1>
{
    static constexpr std::string_view name = "G1";
};

struct Group2: Timer::GroupNode
{
};

template <>
struct Timer::GroupTraits<Group2>
{
    using Children = std::tuple<Timer21, Timer22>;
    using Master   = Timer2;
};

template <>
struct Timer::NodeName<Group2>
{
    static constexpr std::string_view name = "G2";
};

struct GroupAll: Timer::GroupNode
{
};

template <>
struct Timer::GroupTraits<GroupAll>
{
    using Children = std::tuple<Group1, Group2>;
};

template <>
struct Timer::NodeName<GroupAll>
{
    static constexpr std::string_view name = "summary";
};

using myTimers =
    Timer::TimerRegistry<Timer11, Timer12, Timer21, Timer22, Timer2>;

void run_func();

#endif /* CROSSTU_EXAMPLE_ABB3EBE1_044D_477A_9E07_E4C32C0965C9 */
