/* See LICENSE file for copyright and license details. */

#include <stdio.h>
#include "log.h"

int
main(int argc, char **argv)
{
	printf("Init tests\n\n");

	Log *log = log_create(__FILE__);
	log_debug(log, "debug log");
	log_info(log, "info log");
	log_warn(log, "warning log");
	log_error(log, "error log");

	printf("Version: %s\n", loglibver());

	return 0;
}
