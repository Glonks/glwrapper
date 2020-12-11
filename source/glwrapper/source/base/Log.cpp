#include <glwrapper/base/Log.h>

#include <spdlog/sinks/stdout_color_sinks.h>

namespace glwrapper {

    std::shared_ptr<spdlog::logger> Log::s_coreLogger;
    std::shared_ptr<spdlog::logger> Log::s_clientLogger;

    void Log::init() {
        auto core_stdout_sink = std::make_shared<spdlog::sinks::stdout_color_sink_mt>();
        auto client_stdout_sink = std::make_shared<spdlog::sinks::stdout_color_sink_mt>();

        core_stdout_sink->set_pattern("%^[%T][%l][%n]: %v%$");
        client_stdout_sink->set_pattern("%^[%T][%l][%n]: %v%$");

        s_coreLogger = std::make_shared<spdlog::logger>("Core", core_stdout_sink);

        spdlog::register_logger(s_coreLogger);
        s_coreLogger->set_level(spdlog::level::trace);
        s_coreLogger->flush_on(spdlog::level::trace);

        s_clientLogger = std::make_shared<spdlog::logger>("Client", client_stdout_sink);

        spdlog::register_logger(s_clientLogger);
        s_clientLogger->set_level(spdlog::level::trace);
        s_clientLogger->flush_on(spdlog::level::trace);
    }

    std::shared_ptr<spdlog::logger> Log::getCoreLogger() {
        return s_coreLogger;
    }

    std::shared_ptr<spdlog::logger> Log::getClientLogger() {
        return s_clientLogger;
    }

}