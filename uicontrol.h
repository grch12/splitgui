#ifndef UICONTROL_H
#define UICONTROL_H

#include "global.h"

void set_size_enabled(Ihandle* dlg, char* stat);
void set_amount_enabled(Ihandle* dlg, char* stat);

void split_progress_increase();
void merge_progress_increase();

#endif

