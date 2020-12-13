#pragma once

#include <glwrapper/base/Instantiator.h>
#include <glwrapper/base/Source.h>

namespace glwrapper {

    class StringSource : public Source, public Instantiator<StringSource> {
    public:
        explicit StringSource(const std::string& string);
        explicit StringSource(std::string&& string);
        StringSource(const char* data, std::size_t length);

        std::string string() const override;
        std::string info() const override;

        void setString(const std::string& string);
        void setString(std::string&& string);

    private:
        std::string m_source;
    };

}