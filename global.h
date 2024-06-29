#ifndef GLOBAL_H
#define GLOBAL_H

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <errno.h>
#include <stdbool.h>

#include <iup.h>
#include <pthread.h>

#include "callbacks.h"
#include "fileutils.h"
#include "uicontrol.h"
#include "ui.h"

extern size_t split_processed;
extern size_t split_total;
extern Ihandle* split_process_label;

extern size_t merge_processed;
extern bool should_continue;
extern Ihandle* merge_process_label;

extern Ihandle* mw;

#endif

