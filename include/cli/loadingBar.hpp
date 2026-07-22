#pragma once

#include <iostream>
#include <atomic>
#include <thread>
#include <chrono>


extern std::atomic<bool> done;

void spinner();