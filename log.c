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
#define HALF_SIZE (BUFF_SIZE / 2 - 1)

/* Checks if the terminal supports colors */
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

/* Converts the property values */
static int
log_parse_level_property(char *str_level)
{
	if (strcmp( str_level, "DEBUG"   ) == 0) return DBG_LVL;
	if (strcmp( str_level, "INFO"    ) == 0) return INF_LVL;
	if (strcmp( str_level, "WARNING" ) == 0) return WRN_LVL;
	if (strcmp( str_level, "ERROR"   ) == 0) return ERR_LVL;

	return -1;
}

/* Parses the configuration line to get log level and the context */
static int
log_get_level(const char *filename, char *conf_key, char *conf_value)
{
	char *key = strndup(conf_key, strlen(conf_key));
	char *context = strndup(strtok(key, "."), strlen(key));
	int level_context = strcmp(strtok(NULL, "."), "level");
	char *file_context = strndup(filename, HALF_SIZE);
	int root_level = 0;
	int level = 0;

	file_context = strtok(file_context, ".");

	if (level_context == 0) {
		if (strcmp(context, "root") == 0) {
			root_level = log_parse_level_property(conf_value);
		} else if (strcmp(context, file_context) == 0
				&& (level = log_parse_level_property(conf_value)) >= 0) {
			return level;
		}
	}

	return root_level;
}

/* Initialize the log structure */
static void
log_init(Log *log)
{
	char conf_key[HALF_SIZE], conf_value[HALF_SIZE], buff[BUFF_SIZE];
	FILE *file = fopen("log.config", "r");

	/* Use the coded configuration */
	if (file == NULL)
		return;

	while (fgets(buff, BUFF_SIZE, file) != NULL
			&& buff[0] != '#') {
		sscanf(buff, "%[^=]=%s", conf_key, conf_value);
		log->level = log_get_level(log->filename, conf_key, conf_value);
	}

	fclose(file);
}

Log *
log_create(const char *filename) {
	Log *log = (Log *) malloc(sizeof(Log));
	log->filename = filename;
	log->level = DBG_LVL;

	log_init(log);

	return log;
}

static void
print_log(Log *log, int level, char *msg)
{
	time_t t;
	struct tm *date;
	const char *lvl;

	/* Don't display log if the choosen level is major.
	 * For example: log->level is ERROR and level is INFO, only ERROR logs will be shown. */
	if (log->level > level) return;

	t = time(NULL);
	date = localtime(&t);

	switch (level) {
		case DBG_LVL:
			lvl = "[DEBUG]";
			break;
		case INF_LVL:
			lvl = "[INFO]";
			break;
		case WRN_LVL:
			lvl = "[WARNING]";
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
	       date->tm_year + 1900,
	       date->tm_mon,
	       date->tm_mday,
	       date->tm_hour,
	       date->tm_min,
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
log_warn(Log *log, char *msg)
{
	print_log(log, WRN_LVL, msg);
}
