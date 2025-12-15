#ifndef CROSSTU_EXAMPLE_ABB3EBE1_044D_477A_9E07_E4C32C0965C9
#define CROSSTU_EXAMPLE_ABB3EBE1_044D_477A_9E07_E4C32C0965C9

#include "timer/timer.hpp"

struct Timer11: Timer::TimerNode
{
};

struct Timer12: Timer::TimerNode
{
};

struct Timer21: Timer::TimerNode
{
};

struct Timer22: Timer::TimerNode
{
};

struct Group1: Timer::GroupNode
{
};

template <>
struct Timer::GroupTraits<Group1>
{
    using Children = std::tuple<Timer11, Timer12>;
};

struct Group2: Timer::GroupNode
{
};

template <>
struct Timer::GroupTraits<Group2>
{
    using Children = std::tuple<Timer21, Timer22>;
};

struct GroupAll: Timer::GroupNode
{
};

template <>
struct Timer::GroupTraits<GroupAll>
{
    using Children = std::tuple<Group1, Group2>;
};

using myTimers = Timer::TimerRegistry<Timer11, Timer12, Timer21, Timer22>;

void run_func();

#endif /* CROSSTU_EXAMPLE_ABB3EBE1_044D_477A_9E07_E4C32C0965C9 */
