#ifndef EventHandler_hpp
#define EventHandler_hpp

#include <exception>

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

    void operator()(EventArgs args) const
    {
        if (_stub == nullptr)
            throw InvalidEventHandlerCall();

        (*_stub)(_sender, args);
    }

    template <typename Sender, void (Sender::*MemberFunction)(EventArgs) const>
    void Bind(const Sender *sender)
    {
        _sender = sender;
        _stub = static_cast<stub>([](const void *p, EventArgs args) -> void
        {
            const auto* s = static_cast<const Sender*>(p);
            (s->*MemberFunction)(args); 
        });
    }

    template <typename Sender, void (Sender::*MemberFunction)(EventArgs)>
    void Bind(Sender *sender)
    {
        _sender = sender;
        _stub = static_cast<stub>([](const void *p, EventArgs args) -> void
        {
        
            auto* s = const_cast<Sender*>(static_cast<const Sender*>(p));
            (s->*MemberFunction)(args);
        });
    }

private:
    using stub = void (*)(const void *, EventArgs);
    const void *_sender = nullptr;
    stub _stub = nullptr;
};

#endif