#pragma once
#ifndef F4SANDBOX_HELPERS_H
#define F4SANDBOX_HELPERS_H

#include <spdlog/spdlog.h>
#include <spdlog/sinks/stdout_color_sinks.h>
#include <spdlog/sinks/basic_file_sink.h>
#include <spdlog/async.h>

/// This is using async but isn't really async
#define F4S_LOG_INIT { \
                        auto console = spdlog::stdout_color_mt("console"); \
                        auto async_file = spdlog::create_async<spdlog::sinks::basic_file_sink_mt>("f4mp_logger", "F4Sandbox/sandbox.log");\
                     }

#define F4S_LOG_INFO(a) {                                      \
                            spdlog::get("console")->info(a);    \
                            spdlog::get("f4mp_logger")->info(a); \
                        }

#define F4S_LOG_ERR(a) {                                      \
                            spdlog::get("console")->error(a);    \
                            spdlog::get("f4mp_logger")->error(a); \
                        }

#define F4S_LOG_CRIT(a) {                                      \
                            spdlog::get("console")->critical(a);    \
                            spdlog::get("f4mp_logger")->critical(a); \
                        }

#define F4S_LOG_WARN(a) {                                      \
                            spdlog::get("console")->warn(a);    \
                            spdlog::get("f4mp_logger")->warn(a); \
                        }


#endif //F4SANDBOX_HELPERS_H
