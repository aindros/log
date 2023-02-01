/* See LICENSE file for copyright and license details. */

#include "log.h"

int
main(int argc, char **argv)
{
	Log *log = log_create(__FILE__);
	log_debug(log, "test log ");

	return 0;
}
