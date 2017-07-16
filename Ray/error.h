#pragma once

#include "logger.h"

extern Logger logger;

extern void release();

void Exit();

void handle_error(int code , const char * msg);