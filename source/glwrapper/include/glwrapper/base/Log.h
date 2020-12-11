#pragma once

#include <spdlog/spdlog.h>

#include <memory>

namespace glwrapper {

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

#define GLW_CORE_INFO(...) ::glwrapper::Log::getCoreLogger()->info(__VA_ARGS__)
#define GLW_CORE_TRACE(...) ::glwrapper::Log::getCoreLogger()->trace(__VA_ARGS__)
#define GLW_CORE_WARN(...) ::glwrapper::Log::getCoreLogger()->warn(__VA_ARGS__)
#define GLW_CORE_ERROR(...) ::glwrapper::Log::getCoreLogger()->error(__VA_ARGS__)
#define GLW_CORE_CRITICAL(...) ::glwrapper::Log::getCoreLogger()->critical(__VA_ARGS__)

#define GLW_INFO(...) ::glwrapper::Log::getClientLogger()->info(__VA_ARGS__)
#define GLW_TRACE(...) ::glwrapper::Log::getClientLogger()->trace(__VA_ARGS__)
#define GLW_WARN(...) ::glwrapper::Log::getClientLogger()->warn(__VA_ARGS__)
#define GLW_ERROR(...) ::glwrapper::Log::getClientLogger()->error(__VA_ARGS__)
#define GLW_CRITICAL(...) ::glwrapper::Log::getClientLogger()->critical(__VA_ARGS__)