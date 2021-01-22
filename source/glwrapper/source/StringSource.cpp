#include <glwrapper/StringSource.h>

namespace glw {

    StringSource::StringSource(const std::string& string) : m_source{string} {}

    StringSource::StringSource(std::string&& string) : m_source{std::move(string)} {}

    StringSource::StringSource(const char* data, std::size_t length) : m_source{data, length} {}

    std::string StringSource::string() const {
        return m_source;
    }

    std::string StringSource::info() const {
        return "<StringSource>";
    }

    void StringSource::setString(const std::string& string) {
        m_source = string;
    }

    void StringSource::setString(std::string&& string) {
        m_source = std::move(string);
    }

}