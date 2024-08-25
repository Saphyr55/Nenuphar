#pragma once

#include <functional>

namespace Nenuphar::Internal
{
    template<typename T>
    class Success;

    template<typename T>
    class Failure;

    template<typename SuccessT, typename FailureT>
    class Result;

    struct failure_t
    {
        explicit failure_t() = default;
    };

    static constexpr failure_t failure_internal{};

    template<typename T, typename U>
    constexpr bool operator==(const Success<T>& lhs, const Success<U>& rhs) noexcept
    {
        // Does not allow comparison with other types.
        if constexpr (!std::is_same_v<T, U>)
        {
            return false;
        }
        else
        {
            return lhs.Value() == rhs.Value();
        }
    }

    template<typename T, typename U>
    constexpr bool operator!=(const Success<T>& lhs, const Success<U>& rhs) noexcept
    {
        return !(lhs == rhs);
    }

    template<typename Exp, typename F>
    constexpr auto AndThen(Exp&& exp, F&& f) noexcept
    {
        using T = std::remove_cvref_t<decltype(exp.Value())>;
        using E = std::remove_cvref_t<decltype(exp.Error())>;

        auto invoke_f = [&]() -> decltype(auto) {
            if constexpr (!std::is_void_v<T>)
            {
                return std::invoke(std::forward<F>(f), std::forward<Exp>(exp).Value());
            }
            else
            {
                return std::invoke(std::forward<F>(f));
            }
        };

        using U = decltype(invoke_f());

        return exp.HasValue()
                       ? invoke_f()
                       : U(failure_internal, std::forward<Exp>(exp).Error());
    }

    template<typename Exp, typename F>
    constexpr auto OrElse(Exp&& exp, F&& f) noexcept
    {
        using T = std::remove_cvref_t<decltype(exp.Value())>;
        using G = std::invoke_result_t<F, decltype(std::forward<Exp>(exp).Error())>;

        if (!exp.HasValue())
        {
            return std::invoke(std::forward<F>(f), std::forward<Exp>(exp).Error());
        }

        if constexpr (!std::is_void_v<T>)
        {
            return G(std::in_place, std::forward<Exp>(exp).Value());
        }
        else
        {
            return G();
        }
    }

    template<typename Exp, typename F>
    constexpr auto Map(Exp&& exp, F&& f) noexcept
    {

        using T = std::remove_cvref_t<decltype(exp.Value())>;
        using E = std::remove_cvref_t<decltype(exp.Error())>;

        auto invoke_f = [&]() -> decltype(auto) {
            if constexpr (!std::is_void_v<T>)
            {
                return std::invoke(std::forward<F>(f), std::forward<Exp>(exp).Value());
            }
            else
            {
                return std::invoke(std::forward<F>(f));
            }
        };

        using U = std::remove_cv_t<decltype(invoke_f())>;

        if (!exp.HasValue())
        {
            return Result<U, E>(failure_internal, std::forward<Exp>(exp).Error());
        }

        if constexpr (!std::is_void_v<U>)
        {
            return Result<U, E>(std::in_place, invoke_f());
        }
        else
        {
            invoke_f();
            return Result<U, E>();
        }
    }

    template<typename Exp, typename F>
    constexpr auto MapError(Exp&& exp, F&& f) noexcept
    {
        using T = std::remove_cvref_t<decltype(exp.Value())>;
        using G = std::remove_cv_t<
                std::invoke_result_t<F, decltype(std::forward<Exp>(exp).Error())>>;
        
        if (!exp.HasValue())
        {
            return Result<T, G>(
                    failure_internal,
                    std::invoke(std::forward<F>(f), std::forward<Exp>(exp).Error()));
        }

        if constexpr (std::is_void_v<T>)
        {
            return Result<T, G>();
        }
        else
        {
            return Result<T, G>(std::in_place, std::forward<Exp>(exp).Value());
        }

    }
}