#pragma once

#include <functional>

namespace utils
{
    template <typename Signature>
    class optional_function;

    template <typename Ret, typename... Args>
    class optional_function<Ret(Args...)>
    {
        std::function<Ret(Args...)> func;

      public:
        optional_function() = default;

        optional_function(std::function<Ret(Args...)> f)
            : func(std::move(f))
        {
        }

        template <typename F>
            requires(std::is_invocable_r_v<Ret, F, Args...>)
        optional_function(F&& f)
            : func(std::forward<F>(f))
        {
        }

        template <typename F>
            requires(std::is_invocable_r_v<Ret, F, Args...>)
        optional_function& operator=(F&& f)
        {
            func = std::forward<F>(f);
            return *this;
        }

        Ret operator()(Args... args) const
        {
            if (func)
            {
                return func(std::forward<Args>(args)...);
            }

            if constexpr (!std::is_void_v<Ret>)
            {
                return Ret();
            }
        }

        explicit operator bool() const noexcept
        {
            return static_cast<bool>(func);
        }
    };
}
