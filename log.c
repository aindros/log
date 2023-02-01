/* See LICENSE file for copyright and license details. */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "log.h"

#define DBG_LVL 0
#define INF_LVL 1
#define WRN_LVL 2
#define ERR_LVL 3

#define BUFF_SIZE 256

static int
check_term_colors()
{
	FILE *fp;
	char path[1024];

	/* Open the command for reading. */
	fp = popen("echo $COLORTERM", "r");
	if (fp == NULL) {
		printf("Failed to run command\n" );
		exit(1);
	}

	/* Read the output a line at a time - output it. */
	while (fgets(path, sizeof(path), fp) != NULL) {
		/* printf("%s", path); */
		if (strcmp(path, "truecolor\n") == 0) {
			pclose(fp);
			return 0;
		}
	}

	/* close */
	pclose(fp);

	return -1;
}

static void
log_init(Log *log)
{
	char buff[BUFF_SIZE];
	FILE *file = fopen("log.config", "r");

	/* Use the coded configuration */
	if (file == NULL)
		return;

	while (fgets(buff, BUFF_SIZE, file) != NULL) {
		/*printf("%s", strtok(buff, "="));*/
	}

	fclose(file);
}

Log *
log_create(const char *filename) {
	Log *log = (Log *) malloc(sizeof(Log));
	/*log->filename = filename;
	log->level = DBG_LVL;*/

	log_init(log);

	return log;
}

static void
print_log(Log *log, int level, char *msg)
{
	time_t t;
	t = time(NULL);
	struct tm tm = *localtime(&t);
	const char *lvl;

	/* Don't display log if the choosen level is major.
	 * For example: log->level is ERROR and level is INFO, only ERROR logs will be shown. */
	if (log->level > level) return;

	switch (level) {
		case DBG_LVL:
			lvl = "[DEBUG]";
			break;
		case INF_LVL:
			lvl = "[INFO]";
			break;
		case ERR_LVL:
			lvl = "[ERROR]";
			break;
		default:
			lvl = "[DEFAULT]";
			break;
	}

	check_term_colors();
	printf("%d-%02d-%02d %02d:%02d %10s: <%s> %s\n",
	       tm.tm_year + 1900,
	       tm.tm_mon,
	       tm.tm_mday,
	       tm.tm_hour,
	       tm.tm_min,
	       lvl,
	       log->filename,
	       msg);
}

void
log_debug(Log *log, char *msg)
{
	print_log(log, DBG_LVL, msg);
}

void
log_error(Log *log, char *msg)
{
	print_log(log, ERR_LVL, msg);
}

void
log_info(Log *log, char *msg)
{
	print_log(log, INF_LVL, msg);
}

void
log_warning(Log *log, char *msg)
{
	print_log(log, WRN_LVL, msg);
}
