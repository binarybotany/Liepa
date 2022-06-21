#ifndef EventHandler_hpp
#define EventHandler_hpp

#include <exception>
#include <functional>

class InvalidEventHandlerCall : public std::exception
{
};

template <typename EventArgs>
class EventHandler
{
public:
    EventHandler() = default;

    EventHandler(const EventHandler &other) = default;
    EventHandler &operator=(const EventHandler &other) = default;

    template <
        typename UEventArgs,
        typename = std::enable_if_t<std::is_invocable_v<
            void(EventArgs), UEventArgs>
        >
    >
    void operator()(UEventArgs&& args)
    {
        std::invoke(_stub, _sender, std::forward<EventArgs>(args));
    }

    template <
        auto MemberFunction, 
        typename Sender,
        typename = std::enable_if_t<std::is_invocable_v<
            decltype(MemberFunction), const Sender*, EventArgs>
        >
    >
    void Bind(const Sender* sender)
    {
        _sender = sender;
        _stub = static_cast<stub>([](const void *p, EventArgs args) -> void
        {
            const auto* s = static_cast<const Sender*>(p);
            std::invoke(MemberFunction, s, std::forward<EventArgs>(args)); 
        });
    }

    template <
        auto MemberFunction, 
        typename Sender,
        typename = std::enable_if_t<std::is_invocable_v<
            decltype(MemberFunction), Sender*, EventArgs>
        >
    >
    void Bind(Sender *sender)
    {
        _sender = sender;
        _stub = static_cast<stub>([](const void *p, EventArgs args) -> void
        {
        
            auto* s = const_cast<Sender*>(static_cast<const Sender*>(p));
            std::invoke(MemberFunction, s, std::forward<EventArgs>(args));
        });
    }

private:
    using stub = void (*)(const void *, EventArgs);
    const void *_sender = nullptr;
    stub _stub = stubNull;

    [[noreturn]]
    static void stubNull(const void* p, EventArgs) 
    {
        throw InvalidEventHandlerCall();
    }
};

#endif