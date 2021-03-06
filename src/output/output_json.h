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

#ifndef OUTPUT_JSON_H
#define OUTPUT_JSON_H

/* json output module */
int output_json_open(char *);
int output_json_write(hmatrix_t *);
void output_json_close(void);

#endif /* OUTPUT_JSON_H */
