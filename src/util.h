/*
 * Harry - A Tool for Measuring String Similarity
 * Copyright (C) 2013-2014 Konrad Rieck (konrad@mlsec.org)
 * --
 * This program is free software; you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation; either version 3 of the License, or (at your
 * option) any later version.  This program is distributed without any
 * warranty. See the GNU General Public License for more details. 
 */


#ifndef UTIL_H
#define UTIL_H

#include <zlib.h>
#include "config.h"
#include "harry.h"

/* Fatal message */
#ifndef fatal
#define fatal(...)     {err_msg("Error", __func__, __VA_ARGS__); exit(-1);}
#endif
/* Error message */
#ifndef error
#define error(...)     {err_msg("Error", __func__, __VA_ARGS__);}
#endif
/* Warning message */
#ifndef warning
#define warning(...)   {err_msg("Warning", __func__, __VA_ARGS__);}
#endif

/* Utility functions */
void err_msg(char *, const char *, char *, ...);
void info_msg(int, char *, ...);
double time_stamp();
void prog_bar(long, long, long);
size_t gzgetline(char **s, size_t * n, gzFile f);
void strtrim(char *x);
int decode_str(char *str);
uint64_t hash_str(char *s, int l);
int strip_newline(char *s, int l);
void debug_msg(char *m, ...);

void log_print(long, long, long);


#define MIN(a, b) (a < b ? a : b)
#define MAX(a, b) (a > b ? a : b)

#define UNUSED(x) (void)(x)

#if LIBCONFIG_VER_MAJOR > 1 || LIBCONFIG_VER_MINOR > 3
#define CONFIG_LOOKUP_INT(cfg, s, i) config_lookup_int(cfg, s, i)
#define CONFIG_SETTING_LOOKUP_INT(cfgsetting, s, i) config_setting_lookup_int(cfgsetting, s, i)

#else
#define CONFIG_LOOKUP_INT(cfg, s, i) { \
	long l; \
	config_lookup_int(cfg, s, &l); \
	*i = (int) l; \
}

#define CONFIG_SETTING_LOOKUP_INT(cfgsetting, s, i) { \
	long l; \
	config_setting_lookup_int(cfgsetting, s, &l); \
	*i = (int) l; \
}
#endif

#endif /* UTIL_H */
