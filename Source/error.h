#pragma once

#include "logger.h"

extern Logger logger;

extern void release();

void Exit();

void error(int code , const char * msg);