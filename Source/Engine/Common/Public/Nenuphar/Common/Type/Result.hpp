#pragma once

#include <type_traits>
#include <utility>
#include <variant>

#include "Nenuphar/Common/Internal/ResultInternal.hpp"

namespace Nenuphar
{

    template<typename T>
    class Success final
    {
    public:
        template<typename U = T>
            requires (!std::is_same_v<std::remove_cvref_t<U>, Success<T>>) &&
                     (!std::is_same_v<std::remove_cvref_t<U>, std::in_place_t>) &&
                     std::is_constructible_v<T, U>
        constexpr explicit Success(U && val) noexcept
            : m_value(std::forward<U>(val))
        {
        }

        template<typename... Args>
        constexpr explicit Success(std::in_place_t, Args&&... args) noexcept
            : m_value(std::forward<Args>(args)...)
        {
        }

        template<typename U, typename... Args>
        constexpr explicit Success(std::in_place_t,
                                   std::initializer_list<U> il,
                                   Args&&... args) noexcept
            : m_value(il, std::forward<Args>(args)...)
        {
        }

        constexpr T& Value() & noexcept
        {
            return m_value;
        }

        constexpr const T& Value() const& noexcept
        {
            return m_value;
        }

        constexpr T&& Value() && noexcept
        {
            return std::move(Value());
        }

        constexpr const T&& Value() const&& noexcept
        {
            return std::move(Value());
        }

        constexpr void Swap(Success& other) noexcept
        {
            using std::swap;
            swap(Value(), other.Value());
        }

        friend constexpr void Swap(Success& x, Success& y) noexcept
        {
            x.swap(y);
        }

    private:
        T m_value;
    };

    template<typename T>
        requires(std::is_void_v<T>)
    class Success<T> final
    {
    public:
        constexpr explicit Success() noexcept = default;
    };

    template<typename E>
    class Failure final
    {
    public:

        template<typename Err = E>
            requires 
                    (!std::is_same_v<std::remove_cvref_t<Err>, Failure<E>>) &&
                    (!std::is_same_v<std::remove_cvref_t<Err>, std::in_place_t>) &&
                    std::is_constructible_v<E, Err>
        constexpr explicit Failure(Err&& err) noexcept
            : m_error(std::forward<Err>(err))
        {
        }

        template<typename... Args>
        constexpr explicit Failure(std::in_place_t, Args&&... args) noexcept
            : m_error(std::forward<Args>(args)...)
        {
        }

        template<typename U, typename... Args>
        constexpr explicit Failure(std::in_place_t,
                                      std::initializer_list<U> il,
                                      Args&&... args) noexcept
            : m_error(il, std::forward<Args>(args)...)
        {
        }

        constexpr E& Error() & noexcept
        {
            return m_error;
        }

        constexpr const E& Error() const& noexcept
        {
            return m_error;
        }

        constexpr E&& Error() && noexcept
        {
            return std::move(Error());
        }

        constexpr const E&& Error() const&& noexcept
        {
            return std::move(Error());
        }

        constexpr void Swap(Failure& other) noexcept
        {
            using std::swap;
            swap(Error(), other.Error());
        }

        friend constexpr void Swap(Failure& x, Failure& y) noexcept
        {
            x.Swap(y);
        }

    private:
        E m_error;
    };


    template<typename T, typename E>
    class Result
    {
    public:
        static constexpr size_t kValIdx = 1;
        static constexpr size_t kErrIdx = 2;
        static constexpr std::in_place_index_t<1> kValTag{};
        static constexpr std::in_place_index_t<2> kErrTag{};

        template<typename U, typename G>
        friend class Result;

        constexpr Result() noexcept
            requires(std::default_initializable<T>)
            : m_data(kValTag)
        {
        }

        constexpr Result(const Result& rhs) noexcept
            : m_data(rhs.m_data)
        {
        }

        constexpr Result(Result&& rhs) noexcept
            : m_data(std::move(rhs.m_data))
        {
            rhs.SetIsMovedFrom();
        }

        template<typename U, typename G>
        constexpr explicit Result(const Result<U, G>& rhs) noexcept
        {
            if (rhs.HasValue())
            {
                EmplaceValue(rhs.Value());
            }
            else
            {
                EmplaceError(rhs.Error());
            }
        }

        template<typename U, typename G>
        constexpr explicit Result(Result<U, G>&& rhs) noexcept
        {
            if (rhs.HasValue())
            {
                EmplaceValue(std::move(rhs.Value()));
            }
            else
            {
                EmplaceError(std::move(rhs.Error()));
            }
            rhs.SetIsMovedFrom();
        }

        template<typename... Args>
        constexpr explicit Result(decltype(kValTag), Args&&... args) noexcept
            : m_data(kValTag, std::forward<Args>(args)...)
        {
        }

        template<typename U, typename... Args>
        constexpr explicit Result(decltype(kValTag),
                                        std::initializer_list<U> il,
                                        Args&&... args) noexcept
            : m_data(kValTag, il, std::forward<Args>(args)...)
        {
        }

        template<typename... Args>
        constexpr explicit Result(decltype(kErrTag), Args&&... args) noexcept
            : m_data(kErrTag, std::forward<Args>(args)...)
        {
        }

        template<typename U, typename... Args>
        constexpr explicit Result(decltype(kErrTag),
                                        std::initializer_list<U> il,
                                        Args&&... args) noexcept
            : m_data(kErrTag, il, std::forward<Args>(args)...)
        {
        }

        constexpr Result& operator=(const Result& rhs) noexcept
        {
            m_data = rhs.m_data;
            return *this;
        }

        constexpr Result& operator=(Result&& rhs) noexcept
        {
            m_data = std::move(rhs.m_data);
            rhs.SetIsMovedFrom();
            return *this;
        }

        template<typename... Args>
        constexpr T& EmplaceValue(Args&&... args) noexcept
        {
            return m_data.template emplace<kValIdx>(std::forward<Args>(args)...);
        }

        template<typename U, typename... Args>
        constexpr T& EmplaceValue(std::initializer_list<U> il,
                                   Args&&... args) noexcept
        {
            return m_data.template emplace<kValIdx>(il, std::forward<Args>(args)...);
        }

        template<typename... Args>
        constexpr E& EmplaceError(Args&&... args) noexcept
        {
            return m_data.template emplace<kErrIdx>(std::forward<Args>(args)...);
        }

        template<typename U, typename... Args>
        constexpr E& EmplaceError(std::initializer_list<U> il,
                                  Args&&... args) noexcept
        {
            return m_data.template emplace<kErrIdx>(il, std::forward<Args>(args)...);
        }

        void Swap(Result& rhs) noexcept
        {
            m_data.swap(rhs.m_data);
        }

        constexpr bool HasValue() const noexcept
        {
            return m_data.index() == kValIdx;
        }

        constexpr T& Value() noexcept
        {
            return std::get<kValIdx>(m_data);
        }

        constexpr const T& Value() const noexcept
        {
            return std::get<kValIdx>(m_data);
        }

        constexpr E& Error() noexcept
        {
            return std::get<kErrIdx>(m_data);
        }

        constexpr const E& Error() const noexcept
        {
            return std::get<kErrIdx>(m_data);
        }

        template<typename F>
            requires(std::copy_constructible<E>)
        constexpr auto AndThen(F&& f) & noexcept
        {
            return Internal::AndThen(*this, std::forward<F>(f));
        }

        template<typename F>
            requires(std::copy_constructible<E>)
        constexpr auto AndThen(F&& f) const& noexcept
        {
            return Internal::AndThen(*this, std::forward<F>(f));
        }

        template<typename F>
            requires(std::move_constructible<E>)
        constexpr auto AndThen(F&& f) && noexcept
        {
            return Internal::AndThen(std::move(*this), std::forward<F>(f));
        }

        template<typename F>
            requires(std::move_constructible<E>)
        constexpr auto AndThen(F&& f) const&& noexcept
        {
            return Internal::AndThen(std::move(*this), std::forward<F>(f));
        }

        template<typename F>
        constexpr auto OrElse(F&& f) & noexcept
        {
            return Internal::OrElse(*this, std::forward<F>(f));
        }

        template<typename F>
        constexpr auto OrElse(F&& f) const& noexcept
        {
            return Internal::OrElse(*this, std::forward<F>(f));
        }

        template<typename F>
        constexpr auto OrElse(F&& f) && noexcept
        {
            return Internal::OrElse(std::move(*this), std::forward<F>(f));
        }

        template<typename F>
        constexpr auto OrElse(F&& f) const&& noexcept
        {
            return Internal::OrElse(std::move(*this), std::forward<F>(f));
        }

        template<typename F>
            requires(std::copy_constructible<E>)
        constexpr auto Map(F&& f) & noexcept
        {
            return Internal::Map(*this, std::forward<F>(f));
        }

        template<typename F>
            requires(std::copy_constructible<E>)
        constexpr auto Map(F&& f) const& noexcept
        {
            return Internal::Map(*this, std::forward<F>(f));
        }

        template<typename F>
            requires(std::move_constructible<E>)
        constexpr auto Map(F&& f) && noexcept
        {
            return Internal::Map(std::move(*this), std::forward<F>(f));
        }

        template<typename F>
            requires(std::move_constructible<E>)
        constexpr auto Map(F&& f) const&& noexcept
        {
            return Internal::Map(std::move(*this), std::forward<F>(f));
        }

        template<typename F>
        constexpr auto MapError(F&& f) & noexcept
        {
            return Internal::MapError(*this, std::forward<F>(f));
        }

        template<typename F>
        constexpr auto MapError(F&& f) const& noexcept
        {
            return Internal::MapError(*this, std::forward<F>(f));
        }

        template<typename F>
        constexpr auto MapError(F&& f) && noexcept
        {
            return Internal::MapError(std::move(*this), std::forward<F>(f));
        }

        template<typename F>
        constexpr auto MapError(F&& f) const&& noexcept
        {
            return Internal::MapError(std::move(*this), std::forward<F>(f));
        }

    private:
        static constexpr size_t kNulIdx = 0;
        static_assert(kNulIdx != kValIdx);
        static_assert(kNulIdx != kErrIdx);

        constexpr bool IsMovedFrom() const noexcept
        {
            return m_data.index() == kNulIdx;
        }

        constexpr void SetIsMovedFrom() noexcept
        {
            m_data.template emplace<kNulIdx>();
        }

        std::variant<std::monostate, T, E> m_data;
    };


}