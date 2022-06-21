#ifndef Delegate_hpp
#define Delegate_hpp

#include <exception>
#include <functional>

class BadDelegateCall : public std::exception { };

template <typename Signature>
class Delegate;

template <typename R, typename...Args>
class Delegate<R(Args...)>
{
public:
    Delegate() = default;

    Delegate(const Delegate& other) = default;
    auto operator=(const Delegate& other)->Delegate & = default;

    auto operator()(Args... args) const -> R
    {
        return std::invoke(_stub, _instance, args...);
    }

    template <
        typename...UArgs, 
        typename = std::enable_if_t<std::is_invocable_v<R(Args...), UArgs...>>
    >
    auto operator()(UArgs&&...args) -> R
    {
        return std::invoke(_stub, _instance, std::forward<Args>(args)...);
    }

    template <
        auto Function, 
        typename = std::enable_if_t<
            std::is_invocable_r_v<R, decltype(Function), Args...>
            >
        >
    auto bind() -> void
    {
        _instance = nullptr;
        _stub = static_cast<stub_function>([](const void*, Args... args) -> R
        {
            return std::invoke(Function, std::forward<Args>(args)...);
        });
    }

    template <
        auto MemberFunction, 
        typename Class,
        typename = std::enable_if_t<
            std::is_invocable_r_v<
                R, decltype(MemberFunction), const Class*, Args...
            >
        >
    >
    auto bind(const Class* cls) -> void
    {
        _instance = cls;
        _stub = static_cast<stub_function>(
            [](const void* p, Args...args) -> R 
            {
                const auto* c = static_cast<const Class*>(p);
                return std::invoke(
                    MemberFunction, 
                    c, 
                    std::forward<Args>(args)...
                );
            }
        );
    }

    template <
        auto MemberFunction, 
        typename Class, 
        typename = std::enable_if_t<
            std::is_invocable_r_v<
                R, decltype(MemberFunction), Class*, Args...
            >
        >
    >
    auto bind(Class* cls) -> void
    {
        _instance = cls;
        _stub = static_cast<stub_function>(
            [](const void* p, Args... args) -> R
            {
                auto* c = const_cast<Class*>(static_cast<const Class*>(p));
                return std::invoke(
                    MemberFunction, 
                    c, 
                    std::forward<Args>(args)...
                );
            }
        );
    }

    template <typename Class, R(Class::*MemberFunction)(Args...)>
    auto bind(Class* c) -> void
    {
        _instance = c;
        _stub = static_cast<stub_function>(
            [](const void* p, Args... args) -> R
            {
                auto* cls = const_cast<Class*>(static_cast<const Class*>(p));
                return (cls->*MemberFunction)(args...);
            }
        );
    }

private:
    using stub_function = R(*)(const void*, Args...);

    const void* _instance = nullptr;
    stub_function _stub = &stub_null;

    template <R(*Function)(Args...)>
    static auto nonmember_stub(const void* /* unused */, Args... args) -> R
    {
        return (*Function)(args...);
    }

    [[noreturn]]
    static auto stub_null(const void* p, Args...) -> R
    {
        throw BadDelegateCall{};
    }
};

#endif