#pragma once

#include "../shared/openhack.hpp"
#include "utils.hpp"

#include <Geode/Geode.hpp>

#define L_TRACE(...) geode::prelude::log::debug(__VA_ARGS__)
#define L_INFO(...) geode::prelude::log::info(__VA_ARGS__)
#define L_WARN(...) geode::prelude::log::warn(__VA_ARGS__)
#define L_ERROR(...) geode::prelude::log::error(__VA_ARGS__)
#define L_CRITICAL(...) geode::prelude::log::error(__VA_ARGS__)