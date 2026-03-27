#include "logger.h"

#include <stdarg.h>

#include <SDL3/SDL_log.h>

void log_debug(const char *fmt, ...) {
    va_list args;
    va_start(args, format);

    SDL_LogMessageV(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_DEBUG, fmt, args);

    va_end(args);
}

void log_info(const char *fmt, ...) {
    va_list args;
    va_start(args, format);

    SDL_LogMessageV(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_INFO, fmt, args);

    va_end(args);
}

void log_warn(const char *fmt, ...) {
    va_list args;
    va_start(args, format);

    SDL_LogMessageV(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_WARN, fmt, args);

    va_end(args);
}

void log_error(const char *fmt, ...) {
    va_list args;
    va_start(args, format);

    SDL_LogMessageV(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_ERROR, fmt, args);

    va_end(args);
}