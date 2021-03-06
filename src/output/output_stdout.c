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

/** 
 * @addtogroup output
 * <hr>
 * <em>stdout</em>: The matrix of similarity/dissimilarity measures is written
 * to standard output. No black magic.
 * @{
 */

#include "config.h"
#include "common.h"
#include "util.h"
#include "output.h"
#include "harry.h"


/* External variables */
extern config_t cfg;

/* Local variables */
static int save_indices = 0;
static int save_labels = 0;
static int save_sources = 0;
static cfg_int precision = 0;

static const char *separator = ",";

/**
 * Opens a file for writing stdout format
 * @param fn File name
 * @return number of regular files
 */
int output_stdout_open(char *fn)
{
    assert(fn);

    config_lookup_bool(&cfg, "output.save_indices", &save_indices);
    config_lookup_bool(&cfg, "output.save_labels", &save_labels);
    config_lookup_bool(&cfg, "output.save_sources", &save_sources);
    config_lookup_string(&cfg, "output.separator", &separator);
    config_lookup_int(&cfg, "output.precision", &precision);

    if (!stdout) {
        error("Could not open <stdout>");
        return FALSE;
    }

    /* Write harry header */
    harry_version(stdout, "# ", "Output module for stdout format");

    return TRUE;
}

/**
 * Write similarity matrux to output
 * @param m Matrix of similarity values 
 * @return Number of written values
 */
int output_stdout_write(hmatrix_t *m)
{
    assert(m);
    int i, j, r, k = 0;

    if (save_indices) {
        fprintf(stdout, "#");
        for (j = m->x.i; j < m->x.n; j++) {
            fprintf(stdout, " %d", j);
        }
        fprintf(stdout, "\n");
    }

    if (save_labels) {
        fprintf(stdout, "#");
        for (j = m->x.i; j < m->x.n; j++) {
            fprintf(stdout, " %g", m->labels[j]);
        }
        fprintf(stdout, "\n");
    }

    if (save_sources) {
        fprintf(stdout, "#");
        for (j = m->x.i; j < m->x.n; j++) {
            fprintf(stdout, " %s", m->srcs[j]);
        }
        fprintf(stdout, "\n");
    }

    for (i = m->y.i; i < m->y.n; i++) {
        for (j = m->x.i; j < m->x.n; j++) {
            float val = hround(hmatrix_get(m, j, i), precision);
            r = fprintf(stdout, "%g", val);
            if (r < 0) {
                error("Could not write to output file");
                return -k;
            }

            if (j < m->x.n - 1)
                fprintf(stdout, "%s", separator);

            k++;
        }

        if (save_indices || save_labels || save_sources)
            fprintf(stdout, " #");

        if (save_indices)
            fprintf(stdout, " %d", i);

        if (save_labels)
            fprintf(stdout, " %g", m->labels[i]);

        if (save_sources)
            fprintf(stdout, " %s", m->srcs[i]);

        fprintf(stdout, "\n");
    }

    return k;
}

/**
 * Closes an open output file.
 */
void output_stdout_close()
{
    /* Do nothing */
}

/** @} */
