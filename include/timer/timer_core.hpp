#pragma once
#ifndef TIMER_ACF53343_4EFA_45E1_9E22_6603F5CCAE69
#    define TIMER_ACF53343_4EFA_45E1_9E22_6603F5CCAE69

#    include "timer_fwd.hpp"
#    include "timer_concepts.hpp"

#    include <chrono>
#    include <cassert>
#    include <utility>
#    include <type_traits>
#    include <functional>
#    include <ostream>
#    include <concepts>

namespace Timer
{ /**
   * @brief 通用高精度计时器，支持 start/stop 累积计时、peek
   * 查询当前时间、measure 执行函数计时等功能
   *
   */

class Timer
{
    friend std::ostream &operator<<(std::ostream &os, Timer const &timer)
    {
        return os << timer.elapsedTime<>();
    }

public:
    Timer() : elapsed(), epoch(), isrunning(false) {}

    /**
     * @brief 重置计时器，清空累积时间并设置为未计时状态
     *
     */
    void reset()
    {
        elapsed   = {};
        epoch     = {};
        isrunning = false;
    }

    /**
     * @brief 开始计时（不清空累计时间）
     *
     */
    void start() noexcept
    {
        assert(!isrunning && "Timer is already running.");
        isrunning = true;
        epoch     = st_clock::now();
    }

    /**
     * @brief 停止计时并更新累计时间
     *
     */
    void stop() noexcept
    {
        assert(isrunning && "Timer has not been started.");
        isrunning  = false;
        elapsed   += st_clock::now() - epoch;
    }

    /**
     * @brief 获取累计时间
     *
     * @tparam TargetUnit 单位比例，默认为 std::chrono::seconds::period
     */
    template <Timer_Impl::IsRatio TargetUnit = std::chrono::seconds::period>
    double elapsedTime() const
    {
        assert(isrunning == false);
        return std::chrono::duration_cast<
            std::chrono::duration<double, TargetUnit>>(elapsed)
            .count();
    }

    /**
     * @brief 获取当前（包括尚未 stop 的正在进行部分）累计的计时
     *
     * @tparam TargetUnit 单位比例 默认为 std::chrono::seconds::period
     */
    template <Timer_Impl::IsRatio TargetUnit = std::chrono::seconds::period>
    double peek() const
    {
        auto nowElapsed = elapsed;
        if (isrunning) nowElapsed += st_clock::now() - epoch;
        return std::chrono::duration_cast<
            std::chrono::duration<double, TargetUnit>>(nowElapsed)
            .count();
    }

    /**
     * @brief 记录函数执行时间，并返回函数返回值
     *
     * @tparam Func 被调用的函数类型
     * @tparam Args 函数参数类型
     * @param func 被调用的函数
     * @param args 函数参数
     * @return func的返回值
     */
    template <typename Func, typename... Args>
    auto measure(Func &&func, Args &&...args) &;

    friend class ScopedTimer;

private:
    using st_clock = std::chrono::steady_clock;
    st_clock::duration                elapsed;
    std::chrono::time_point<st_clock> epoch;
    bool                              isrunning;

    void addTime(st_clock::duration time) { elapsed += time; }
};

/**
 * @brief
 * Timer的辅助类，用于作用域内的计时（进入构造函数开始计时，析构自动加入计时器）
 *
 */
class ScopedTimer
{
public:
    [[nodiscard]] explicit ScopedTimer(Timer &timer) :
    timer(timer), isrunning(true), epoch(st_clock::now())
    {
    }

    ScopedTimer(ScopedTimer const &)            = delete;
    ScopedTimer &operator=(ScopedTimer const &) = delete;

    ScopedTimer(ScopedTimer &&)            = delete;
    ScopedTimer &operator=(ScopedTimer &&) = delete;

    ~ScopedTimer() noexcept { stop(); }

    /**
     * @brief 提前手动结束本次作用域计时，防止析构时重复累加
     *
     */
    void stop()
    {
        if (isrunning)
        {
            timer.addTime(st_clock::now() - epoch);
            isrunning = false;
        }
    }

private:
    using st_clock = std::chrono::steady_clock;
    Timer                            &timer;
    bool                              isrunning;
    std::chrono::time_point<st_clock> epoch;
};

template <typename Func, typename... Args>
auto Timer::measure(Func &&func, Args &&...args) &
{
    auto guard = ScopedTimer(*this);
    if constexpr (std::is_void_v<std::invoke_result_t<Func, Args...>>)
    {
        std::invoke(std::forward<Func>(func), std::forward<Args>(args)...);
        return;
    }
    else
    {
        auto &&result =
            std::invoke(std::forward<Func>(func), std::forward<Args>(args)...);
        return std::forward<decltype(result)>(result);
    }
}

template <typename Func, typename... Args>
auto measure(Timer &t, Func &&func, Args &&...args)
{
    auto guard = ScopedTimer(t);
    if constexpr (std::is_void_v<std::invoke_result_t<Func, Args...>>)
    {
        std::invoke(std::forward<Func>(func), std::forward<Args>(args)...);
        return;
    }
    else
    {
        auto &&result =
            std::invoke(std::forward<Func>(func), std::forward<Args>(args)...);
        return std::forward<decltype(result)>(result);
    }
}
} // namespace Timer
#endif /* TIMER_ACF53343_4EFA_45E1_9E22_6603F5CCAE69 */
