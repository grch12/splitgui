#ifndef CALLBACKS_H
#define CALLBACKS_H

#include "global.h"

int split_browse_cb(Ihandle* dlg);
int split_ok_cb(Ihandle* dlg);
int as_amount_cb(Ihandle* dlg);
int as_size_cb(Ihandle* dlg);

int merge_browse_cb(Ihandle* dlg);
int merge_ok_cb(Ihandle* dlg);

extern char mode;

#endif

