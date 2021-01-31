#pragma once

#include <spdlog/spdlog.h>
#include <spdlog/fmt/ostr.h>

#include <memory>

namespace glw {

    class Log {
    public:
        static void init();

        static std::shared_ptr<spdlog::logger> getCoreLogger();
        static std::shared_ptr<spdlog::logger> getClientLogger();

    private:
        static std::shared_ptr<spdlog::logger> s_coreLogger;
        static std::shared_ptr<spdlog::logger> s_clientLogger;
    };

}

#define GLW_CORE_INFO(...) ::glw::Log::getCoreLogger()->info(__VA_ARGS__)
#define GLW_CORE_TRACE(...) ::glw::Log::getCoreLogger()->trace(__VA_ARGS__)
#define GLW_CORE_WARN(...) ::glw::Log::getCoreLogger()->warn(__VA_ARGS__)
#define GLW_CORE_ERROR(...) ::glw::Log::getCoreLogger()->error(__VA_ARGS__)
#define GLW_CORE_CRITICAL(...) ::glw::Log::getCoreLogger()->critical(__VA_ARGS__)

#define GLW_INFO(...) ::glw::Log::getClientLogger()->info(__VA_ARGS__)
#define GLW_TRACE(...) ::glw::Log::getClientLogger()->trace(__VA_ARGS__)
#define GLW_WARN(...) ::glw::Log::getClientLogger()->warn(__VA_ARGS__)
#define GLW_ERROR(...) ::glw::Log::getClientLogger()->error(__VA_ARGS__)
#define GLW_CRITICAL(...) ::glw::Log::getClientLogger()->critical(__VA_ARGS__)