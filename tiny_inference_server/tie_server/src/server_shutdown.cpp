#include "server_shutdown.hpp"
#include <csignal>

namespace tie::server
{
volatile sig_atomic_t shutdown_signal = 0;

bool shutdown_server() noexcept
{
    return shutdown_signal != 0;
}

void signal_handler(int signal) noexcept
{
    shutdown_signal = signal;
}

void install_shutdown_signal_handlers() noexcept
{
    std::signal(SIGINT, signal_handler);
    std::signal(SIGILL, signal_handler);
    std::signal(SIGABRT, signal_handler);
    std::signal(SIGTERM, signal_handler);
}

void reset_shutdown_signal_handlers() noexcept
{
    shutdown_signal = 0;
}

}