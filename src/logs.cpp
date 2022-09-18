/**
 * \file
 * \brief Contains LOG_FILE init
*/

#include "logs.hpp"

FILE *LOG_FILE = fopen("debug/log.txt", "w");
