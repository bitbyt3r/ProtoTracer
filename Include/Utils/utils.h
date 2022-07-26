#pragma once
#include <stdint.h>
#include <sys/time.h>
#include <time.h>

static uint64_t epochMilli, epochMicro;

void initializeTimers()
{
	struct timespec ts;
	clock_gettime(CLOCK_MONOTONIC_RAW, &ts);
	epochMilli = (uint64_t)ts.tv_sec * (uint64_t)1000 + (uint64_t)(ts.tv_nsec / 1000000L);
	epochMicro = (uint64_t)ts.tv_sec * (uint64_t)1000000 + (uint64_t)(ts.tv_nsec / 1000L);
}

//Get elapsed milliseconds
uint64_t millis(void)
{
	uint64_t now;
	struct timespec ts;
	clock_gettime(CLOCK_MONOTONIC_RAW, &ts);
	now = (uint64_t)ts.tv_sec * (uint64_t)1000 + (uint64_t)(ts.tv_nsec / 1000000L);
	return (uint32_t)(now - epochMilli);
}

//Get elapsed microseconds
uint64_t micros(void)
{
	uint64_t now;
	struct timespec ts;
	clock_gettime(CLOCK_MONOTONIC_RAW, &ts);
	now = (uint64_t)ts.tv_sec * (uint64_t)1000000 + (uint64_t)(ts.tv_nsec / 1000);
	return (uint32_t)(now - epochMicro);
}

void delay(unsigned int milliseconds)
{
	struct timespec sleep_time;
	sleep_time.tv_sec = milliseconds / 1000000;
	sleep_time.tv_nsec = (long)((milliseconds % 1000000) * 1000L);
	nanosleep(&sleep_time, NULL);
}