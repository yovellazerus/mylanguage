
#include "../inc/common.h"

void run_time_error(const char* msg, ...){
    va_list args;
    va_start(args, msg);
	fprintf(stderr, COLOR_RED "RUN TIME ERROR: `");
	vfprintf(stderr, msg, args);
	fprintf(stderr, "` ");
    va_end(args);
}
