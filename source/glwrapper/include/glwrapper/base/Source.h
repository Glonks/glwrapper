#pragma once

#include <string>

namespace glwrapper {

    class Source {
    public:
        virtual ~Source() = default;

        virtual std::string string() const = 0;
        virtual std::string info() const;
    };

}