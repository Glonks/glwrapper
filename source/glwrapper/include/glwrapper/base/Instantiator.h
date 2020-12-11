#pragma once

#include <memory>

namespace glwrapper {

    template <typename Subclass>
    class Instantiator {
    public:
        template <typename ...Args>
        static Subclass* create(Args&& ... args);

        template <typename ...Args>
        static std::unique_ptr<Subclass> createUnique(Args&& ... args);
    };

    template <typename Subclass>
    template <typename... Args>
    Subclass* Instantiator<Subclass>::create(Args&& ... args) {
        return new Subclass(std::forward<Args>(args)...);
    }

    template <typename Subclass>
    template <typename ...Args>
    std::unique_ptr<Subclass> Instantiator<Subclass>::createUnique(Args&& ... args) {
        return std::unique_ptr<Subclass>(new Subclass(std::forward<Args>(args)...));
    }

}