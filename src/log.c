/* See LICENSE file for copyright and license details. */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "log.h"

#define NNN_LVL -1 /* NONE LEVEL */
#define DBG_LVL  0
#define INF_LVL  1
#define WRN_LVL  2
#define ERR_LVL  3

#define BUFF_SIZE 256

char *
loglibver(void)
{
	return LIBVER;
}

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
	if (strcmp( str_level, "NONE"    ) == 0) return NNN_LVL;
	if (strcmp( str_level, "DEBUG"   ) == 0) return DBG_LVL;
	if (strcmp( str_level, "INFO"    ) == 0) return INF_LVL;
	if (strcmp( str_level, "WARNING" ) == 0) return WRN_LVL;
	if (strcmp( str_level, "ERROR"   ) == 0) return ERR_LVL;

	return -1;
}

/* Parses the configuration line to get log level and the context */
static int
log_get_level(const char *tag, char *conf_key, char *conf_value)
{
	int default_level = DBG_LVL;
	const char *base_context = "logging.level";
	/* Plus 2 because we need a dot and string terminator */
	char *context = calloc(sizeof(char), strlen(base_context) + strlen(tag) + 2);

	strcat(context, base_context);
	strcat(context, ".");
	strcat(context, tag);

	if (strcmp(conf_key, base_context) == 0) {
		default_level = log_parse_level_property(conf_value);
	} else if (strcmp(conf_key, context) == 0) {
		return log_parse_level_property(conf_value);
	}

	return default_level;
}

/* Initialize the log structure */
static void
log_init(Log *log)
{
	char conf_key[BUFF_SIZE], conf_value[BUFF_SIZE], buff[BUFF_SIZE];
	FILE *file = fopen("log.config", "r");

	/* Use the coded configuration */
	if (file == NULL)
		return;

	while (fgets(buff, BUFF_SIZE, file) != NULL) {
		/* Skip commented lines (very spartan comment) */
		if (buff[0] == '#') continue;

		sscanf(buff, "%[^=]=%s", conf_key, conf_value);
		log->level = log_get_level(log->tag, conf_key, conf_value);
	}

	fclose(file);
}

Log *
log_create(const char *tag) {
	Log *log   = (Log *) malloc(sizeof(Log));
	log->tag   = tag;
	log->level = DBG_LVL; /* This is the default level */

	log_init(log);

	return log;
}

static void
print_log(Log *log, int level, char *msg)
{
	time_t t;
	struct tm *date;
	const char *lvl;

	/* NONE level. Disable log */
	if (log->level == NNN_LVL) return;

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
	       log->tag,
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
