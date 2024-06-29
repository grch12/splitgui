#ifndef UI_H
#define UI_H

#include "global.h"

Ihandle* split_tab();
Ihandle* merge_tab();
Ihandle* about_tab();

void* split_process_show_dialog(void *pvoid);
pthread_t split_process_indicator();

void* merge_process_show_dialog(void *pvoid);
pthread_t merge_process_indicator();

#endif

