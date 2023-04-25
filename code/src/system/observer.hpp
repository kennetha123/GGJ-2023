#include <functional>
#include <memory>
#include <vector>
#include <algorithm>

class ObserverFunc
{
public:
    virtual ~ObserverFunc() = default;
    virtual void operator()() const = 0;
};

template <typename T>
class BoundObserverFunc : public ObserverFunc
{
public:
    using InstanceType = T;
    using MemberFunctionType = void (T::*)();

    BoundObserverFunc(InstanceType* instance, MemberFunctionType memberFunction)
        : instance(instance), memberFunction(memberFunction) {}

    void operator()() const override
    {
        if (instance)
        {
            (instance->*memberFunction)();
        }
    }

    InstanceType* instance;
    MemberFunctionType memberFunction;
};

class Subject
{
public:
    template<typename T>
    void addObserver(T* instance, void (T::* function)())
    {
        auto boundObserver = std::make_shared<BoundObserverFunc<T>>(instance, function);
        observers.push_back(boundObserver);
    }

    template <typename T>
    void removeObserver(T* instance, void (T::* memberFunction)())
    {
        observers.erase(std::remove_if(observers.begin(), observers.end(),
            [&](const std::shared_ptr<ObserverFunc>& target) {
                auto targetBoundObserver = std::dynamic_pointer_cast<BoundObserverFunc<T>>(target);
        if (targetBoundObserver && targetBoundObserver->instance == instance && targetBoundObserver->memberFunction == memberFunction) {
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
    std::vector<std::shared_ptr<ObserverFunc>> observers;
};
