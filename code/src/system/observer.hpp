#include <functional>
#include <memory>
#include <vector>
#include <algorithm>

class observer_func
{
public:
    virtual ~observer_func() = default;
    virtual void operator()() const = 0;
};

template <typename T>
class bound_observer_func : public observer_func
{
public:
    using instance_type = T;
    using member_function_type = void (T::*)();

    bound_observer_func(instance_type* instance, member_function_type memberFunction)
        : instance(instance), memberFunction(memberFunction) {}

    void operator()() const override
    {
        if (instance)
        {
            (instance->*memberFunction)();
        }
    }

    instance_type* instance;
    member_function_type memberFunction;
};

class subject
{
public:
    template<typename T>
    void add_listener(T* instance, void (T::* function)())
    {
        auto boundObserver = std::make_shared<bound_observer_func<T>>(instance, function);
        observers.push_back(boundObserver);
    }

    template <typename T>
    void remove_listener(T* instance, void (T::* memberFunction)())
    {
        observers.erase(std::remove_if(observers.begin(), observers.end(),
            [&](const std::shared_ptr<observer_func>& target) {
                auto target_bound_observer = std::dynamic_pointer_cast<bound_observer_func<T>>(target);
        if (target_bound_observer && target_bound_observer->instance == instance && target_bound_observer->memberFunction == memberFunction) {
            return true;
        }
        return false;
            }), observers.end());
    }

    void notify()
    {
        for (const auto& observer : observers)
        {
            (*observer)();
        }
    }

private:
    std::vector<std::shared_ptr<observer_func>> observers;
};
