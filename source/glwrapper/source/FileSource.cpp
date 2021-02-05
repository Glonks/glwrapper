#include <glwrapper/glwpch.h>
#include <glwrapper/FileSource.h>
#include <glwrapper/base/Log.h>

#include <fstream>

namespace glw {

    FileSource::FileSource(const std::string& filePath) : m_filePath{filePath}, m_valid{false} {
        load();
    }

    void FileSource::load() const {
        m_valid = false;

        auto mode = std::ios::in | std::ios::ate;
        std::ifstream file(m_filePath, mode);

        if (!file) {
            GLW_CORE_WARN("Reading from file '{0}' failed", m_filePath);

            m_source = "";
            m_valid = false;

            return;
        }

        const std::size_t end = file.tellg();

        file.seekg(0, std::ios::beg);
        m_source.resize(end);

        file.read(const_cast<char*>(m_source.data()), end);
        m_source.resize(static_cast<std::size_t>(file.gcount()));

        m_valid = true;
    }

    std::string FileSource::string() const {
        return m_source;
    }

    std::string FileSource::info() const {
        return m_filePath;
    }

    bool FileSource::isValid() const {
        return m_valid;
    }

}