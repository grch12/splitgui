#include "global.h"

int main(int argc, char** argv)
{
	IupOpen(&argc, &argv);
	
	Ihandle* tabs = IupTabs(split_tab(), merge_tab(), about_tab(), NULL);
	IupSetAttribute(tabs, "TABTITLE0", "分割");
	IupSetAttribute(tabs, "TABTITLE1", "合并");
	IupSetAttribute(tabs, "TABTITLE2", "关于");
	
	Ihandle* mw = IupDialog(tabs);
	
	IupSetAttribute(mw, "TITLE", "文件分割/合并 by GitHub@grch12");
	IupSetAttribute(mw, "SIZE", "240x120");
	IupSetAttribute(mw, "RESIZE", "NO");
	IupSetAttribute(mw, "MAXBOX", "NO");
	
	IupShow(mw);
	
	if (argc > 1)
	{
		Ihandle* filename_text = IupGetDialogChild(mw, "FILENAME_TEXT");
		Ihandle* merge_text = IupGetDialogChild(mw, "MERGE_TEXT");
		IupSetStrAttribute(filename_text, "VALUE", argv[1]);
		IupSetStrAttribute(merge_text, "VALUE", argv[1]);
	}
	
	set_size_enabled(mw, "NO");
	
	IupMainLoop();
	
	return 0;
}

