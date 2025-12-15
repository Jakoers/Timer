#ifndef CROSSTU_EXAMPLE_ABB3EBE1_044D_477A_9E07_E4C32C0965C9
#define CROSSTU_EXAMPLE_ABB3EBE1_044D_477A_9E07_E4C32C0965C9

#include "Timer.hpp"
#include "TimerGroup.hpp"

struct Timer11: TimerNode
{
};

struct Timer12: TimerNode
{
};

struct Timer21: TimerNode
{
};

struct Timer22: TimerNode
{
};

struct Group1: GroupNode
{
};

template <>
struct GroupTraits<Group1>
{
    using Children = std::tuple<Timer11, Timer12>;
};

struct Group2: GroupNode
{
};

template <>
struct GroupTraits<Group2>
{
    using Children = std::tuple<Timer21, Timer22>;
};

struct GroupAll: GroupNode
{
};

template <>
struct GroupTraits<GroupAll>
{
    using Children = std::tuple<Group1, Group2>;
};

using myTimers = TimerRegistry<Timer11, Timer12, Timer21, Timer22>;

void run_func();

#endif /* CROSSTU_EXAMPLE_ABB3EBE1_044D_477A_9E07_E4C32C0965C9 */
