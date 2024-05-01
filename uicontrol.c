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

