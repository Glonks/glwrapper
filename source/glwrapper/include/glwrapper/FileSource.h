#pragma once

#include <glwrapper/base/Instantiator.h>
#include <glwrapper/base/Source.h>

namespace glwrapper {

    class FileSource : public Source, public Instantiator<FileSource> {
    public:
        explicit FileSource(const std::string& filePath);

        void load() const;

        std::string string() const override;
        std::string info() const override;
        bool isValid() const;

    private:
        std::string m_filePath;
        mutable std::string m_source;
        mutable bool m_valid;
    };

}