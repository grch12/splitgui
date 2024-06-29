#include "global.h"

void set_size_enabled(Ihandle* dlg, char* stat)
{
	Ihandle* size_text   = IupGetDialogChild(dlg, "SIZE_T");
	Ihandle* size_select = IupGetDialogChild(dlg, "SIZE_S");
	IupSetStrAttribute(size_text,   "ACTIVE", stat);
	IupSetStrAttribute(size_select, "ACTIVE", stat);
}

void set_amount_enabled(Ihandle* dlg, char* stat)
{
	Ihandle* amount_text = IupGetDialogChild(dlg, "NUMBER");
	IupSetAttribute(amount_text, "ACTIVE", stat);
}

void split_progress_increase()
{
	split_processed++;
	char label_text[100] = { '\0' };
	snprintf(label_text, 100, "%llu/%llu", split_processed, split_total);
	IupSetStrAttribute(split_process_label, "TITLE", label_text);
}

void merge_progress_increase()
{
	merge_processed++;
	char label_text[100] = { '\0' };
	snprintf(label_text, 100, "已合并%llu个", merge_processed);
	IupSetStrAttribute(merge_process_label, "TITLE", label_text);
}
