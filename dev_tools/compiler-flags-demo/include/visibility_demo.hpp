#pragma once

#if defined(_WIN32)
#define DEMO_EXPORT __declspec(dllexport)
#else
#define DEMO_EXPORT __attribute__((visibility("default")))
#endif

DEMO_EXPORT int public_sum(int left, int right);
int hidden_subtract(int left, int right);