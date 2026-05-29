#include "TimeManagement.h"

TimeManagement::TimeManagement() {
    initialSeconds = 0.0;
    running = false;
    paused = false;
    std::chrono::steady_clock::time_point startTime;
    std::chrono::steady_clock::time_point pauseTimePoint;
    pausedDuration = 0;
}
TimeManagement::TimeManagement(int seconds)
    : initialSeconds(seconds), running(false), paused(false), pausedDuration(0) {
}

void TimeManagement::setTime(int seconds) {
    initialSeconds = seconds;
    startTime = std::chrono::steady_clock::now();
    pausedDuration = 0;
    paused = false;
    running = false; // Optional: reset timer state
}

void TimeManagement::startTimer() {
    startTime = std::chrono::steady_clock::now();
    running = true;
    paused = false;
    pausedDuration = 0;
}

void TimeManagement::pauseTime() {
    if (running && !paused) {
        pauseTimePoint = std::chrono::steady_clock::now();
        paused = true;
    }
}

void TimeManagement::resumeTime() {
    if (running && paused) {
        auto now = std::chrono::steady_clock::now();
        pausedDuration += std::chrono::duration_cast<std::chrono::seconds>(now - pauseTimePoint).count();
        paused = false;
    }
}

int TimeManagement::currentTime() {
    if (!running) {
        return initialSeconds;
    }

    int elapsed;
    if (paused) {
        elapsed = std::chrono::duration_cast<std::chrono::seconds>(
            pauseTimePoint - startTime
        ).count() - pausedDuration;
    }
    else {
        auto now = std::chrono::steady_clock::now();
        elapsed = std::chrono::duration_cast<std::chrono::seconds>(
            now - startTime
        ).count() - pausedDuration;
    }

    int remaining = initialSeconds - elapsed;
    return remaining > 0 ? remaining : 0;  // Clamp to 0
}

void TimeManagement::resetTime() {
    running = false;
    paused = false;
    pausedDuration = 0;
    startTime = std::chrono::steady_clock::now();
}

