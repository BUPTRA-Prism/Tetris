#pragma once

#include "game/settings.h"

struct Core {
    Settings& settings;

    Core(Settings& s);
};