/* See LICENSE file for copyright and license details. */

#ifndef __LOG_H__
#define __LOG_H__

typedef struct Log {
	const char *tag;
	int level;
} Log;

Log		*log_create(const char *);

void	 log_debug(Log *, char *);
void	 log_error(Log *, char *);
void	 log_info(Log *, char *);
void	 log_warn(Log *, char *);

int		 log_is_debug(Log *);
int		 log_is_error(Log *);
int		 log_is_info(Log *);
int		 log_is_warn(Log *);

char    *loglibver(void);

#endif /* __LOG_H__ */
