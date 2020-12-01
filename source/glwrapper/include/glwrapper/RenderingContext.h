#pragma once

#include <glwrapper/base/Instantiator.h>

namespace glwrapper {

    class RenderingContext : public Instantiator<RenderingContext> {
    public:
        virtual ~RenderingContext() = default;

        virtual void initialize() = 0;
        virtual void swapBuffers() = 0;

    private:

    };

}