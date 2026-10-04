#pragma once

#include "../types.h"

codec generate_latest_codec(void);
img run_codec(char* data, size_t data_size, codec codec);