#include "global.h"

int drop_file_cb(Ihandle* ih, const char* filename)
{
	IupSetStrAttribute(ih, "VALUE", filename);
	return IUP_IGNORE;
}

Ihandle* split_tab()
{
	Ihandle* vbox, * filename_box, * amount_box, * size_box, * size_select;
	Ihandle* filename_text, * browse_btn, * amount_text, * size_text, * ok_btn;
	Ihandle* as_amount, * as_size;
	
	filename_text = IupText(NULL);
	browse_btn = IupButton("浏览...", NULL);
	filename_box = IupHbox(filename_text, browse_btn, NULL);
	
	// Building the amount part.
	as_amount = IupToggle("分割数量：      ", NULL);
	amount_text = IupText(NULL);
	amount_box = IupHbox(as_amount, amount_text, NULL);
	
	IupSetAttribute(amount_text, "SPIN", "YES");
	IupSetAttribute(amount_text, "NAME", "NUMBER");
	IupSetAttribute(amount_text, "ALIGNMENT", "ARIGHT");
	IupSetAttribute(amount_text, "EXPAND", "HORIZONTAL");
	IupSetInt(amount_text, "SPINMIN", 2);
	
	IupSetCallback(as_amount, "ACTION", (Icallback)as_amount_cb);
	
	// Building the size part.
	as_size = IupToggle("单个文件大小：", NULL);
	size_text = IupText(NULL);
	size_select = IupList(NULL);
	
	IupSetAttribute(size_text, "NAME", "SIZE_T");
	IupSetAttribute(size_text, "SPIN", "YES");
	IupSetAttribute(size_text, "ALIGNMENT", "ARIGHT");
	IupSetAttribute(size_text, "EXPAND", "HORIZONTAL");
	IupSetInt(size_text, "SPINMIN", 1);
	
	IupSetAttribute(size_select, "NAME", "SIZE_S");
	IupSetAttribute(size_select, "DROPDOWN", "YES");
	IupSetAttribute(size_select, "1", "B");
	IupSetAttribute(size_select, "2", "KiB");
	IupSetAttribute(size_select, "3", "MiB");
	IupSetAttribute(size_select, "4", "GiB");
	IupSetAttribute(size_select, "5", "TiB");
	IupSetInt(size_select, "VALUE", 1);
	
	size_box = IupHbox(as_size, size_text, size_select, NULL);
	
	IupSetCallback(as_size, "ACTION", (Icallback)as_size_cb);
	
	// Building the main window.
	ok_btn = IupButton("确定", NULL);
	vbox = IupVbox(IupLabel("文件名："), filename_box, IupRadio(IupVbox(amount_box, size_box, NULL)), ok_btn, NULL);
	
	IupSetAttribute(vbox, "NMARGIN", "10x10");
	IupSetAttribute(vbox, "GAP", "10");
	IupSetAttribute(vbox, "EXPAND", "YES");
	
	IupSetAttribute(filename_box, "EXPAND", "HORIZONTAL");
	IupSetAttribute(filename_text, "EXPAND", "HORIZONTAL");
	IupSetAttribute(filename_text, "NAME", "FILENAME_TEXT");
	IupSetCallback(filename_text, "DROPFILES_CB", (Icallback)drop_file_cb);
	
	IupSetAttribute(browse_btn, "PADDING", "5x");
	IupSetCallback(browse_btn, "ACTION", (Icallback)split_browse_cb);
	
	IupSetCallback(ok_btn, "ACTION", (Icallback)split_ok_cb);
	IupSetAttribute(ok_btn, "EXPAND", "YES");
	
	return vbox;
}

Ihandle* merge_tab()
{
	Ihandle* vbox;
	Ihandle* filename_text, *browse_btn, *filename_box, *ok_btn;
	
	filename_text = IupText(NULL);
	browse_btn = IupButton("浏览...", NULL);
	filename_box = IupHbox(filename_text, browse_btn, NULL);
	ok_btn = IupButton("确定", NULL);
	
	vbox = IupVbox(IupLabel("请选择分割后的第一个文件，程序会自动查找剩下的部分。\n"), IupLabel("文件名："), filename_box, ok_btn, NULL);
	
	IupSetAttribute(vbox, "NMARGIN", "10x20");
	IupSetAttribute(vbox, "GAP", "10");
	IupSetAttribute(vbox, "EXPAND", "YES");
	
	IupSetAttribute(filename_box, "EXPAND", "HORIZONTAL");
	IupSetAttribute(filename_text, "EXPAND", "HORIZONTAL");
	IupSetAttribute(filename_text, "NAME", "MERGE_TEXT");
	IupSetCallback(filename_text, "DROPFILES_CB", (Icallback)drop_file_cb);
	
	IupSetAttribute(browse_btn, "PADDING", "5x");
	IupSetCallback(browse_btn, "ACTION", (Icallback)merge_browse_cb);
	
	IupSetAttribute(ok_btn, "PADDING", "0x5");
	IupSetAttribute(ok_btn, "EXPAND", "HORIZONTAL");
	
	IupSetCallback(ok_btn, "ACTION", (Icallback)merge_ok_cb);
	
	return vbox;
}

Ihandle* about_tab()
{
	Ihandle* vbox;
	Ihandle* row, *label1, *link;
	
	Ihandle* label2, *license;
	
	label1 = IupLabel("GitHub 仓库：");
	link = IupLink("https://github.com/grch12/splitgui", "https://github.com/grch12/splitgui");
	
	row = IupHbox(label1, link, NULL);
	
	label2 = IupLabel("许可证");
	license = IupText(NULL);
	
	IupSetAttribute(license, "MULTILINE", "YES");
	IupSetAttribute(license, "EXPAND", "YES");
	IupSetAttribute(license, "READONLY", "YES");
	IupSetAttribute(license, "FONT", "Consolas, 8");
	IupSetAttribute(license, "VALUE", "splitgui\n\n\
MIT License\n\n\
Copyright (c) 2024 grch12\n\n\
Permission is hereby granted, free of charge, to any person obtaining a copy\n\
of this software and associated documentation files (the \"Software\"), to deal\n\
in the Software without restriction, including without limitation the rights\n\
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell\n\
copies of the Software, and to permit persons to whom the Software is\n\
furnished to do so, subject to the following conditions:\n\
\n\
The above copyright notice and this permission notice shall be included in all\n\
copies or substantial portions of the Software.\n\
\n\
THE SOFTWARE IS PROVIDED \"AS IS\", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR\n\
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,\n\
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE\n\
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER\n\
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,\n\
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE\n\
SOFTWARE.\n\n\
IUP (https://www.tecgraf.puc-rio.br/iup)\n\n\
Copyright (c) 1994-2023 Tecgraf/PUC-Rio.\n\
Permission is hereby granted, free of charge, to any person obtaining a copy\n\
of this software and associated documentation files (the \"Software\"), to deal\n\
in the Software without restriction, including without limitation the rights\n\
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell\n\
copies of the Software, and to permit persons to whom the Software is\n\
furnished to do so, subject to the following conditions:\n\
\n\
The above copyright notice and this permission notice shall be included in all\n\
copies or substantial portions of the Software.\n\
\n\
THE SOFTWARE IS PROVIDED \"AS IS\", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR\n\
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,\n\
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE\n\
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER\n\
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,\n\
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE\n\
SOFTWARE.\
");
	
	vbox = IupVbox(row, label2, license, NULL);
	IupSetAttribute(vbox, "NMARGIN", "10x10");
	IupSetAttribute(vbox, "GAP", "10");
	
	return vbox;
}

void* split_process_show_dialog(void *pvoid)
{
	char label_text[100] = { '\0' };
	snprintf(label_text, 100, "0/%llu", split_total);
	split_process_label = IupLabel(label_text);
	Ihandle* dlg = IupDialog(IupVbox(IupLabel("分割中..."), split_process_label, NULL));
	IupSetAttribute(dlg, "MENUBOX", "NO");
	IupSetAttribute(dlg, "MAXBOX", "NO");
	IupSetAttribute(dlg, "MINBOX", "NO");
	IupSetAttribute(dlg, "RESIZE", "NO");
	IupSetAttribute(dlg, "SIZE", "100x30");
	IupSetAttribute(dlg, "SIMULATEMODAL", "YES");
	IupShowXY(dlg, IUP_CENTER, IUP_MOUSEPOS);
	while (split_processed != split_total) {
		IupLoopStepWait();
	}
	return NULL;
}

pthread_t split_process_indicator()
{
	split_processed = 0;
	pthread_t thread;
	pthread_create(&thread, NULL, split_process_show_dialog, NULL);
	return thread;
}

void* merge_process_show_dialog(void *pvoid)
{
	char label_text[100] = { '\0' };
	snprintf(label_text, 100, "已合并%llu个", 0llu);
	merge_process_label = IupLabel(label_text);
	Ihandle* dlg = IupDialog(IupVbox(IupLabel("合并中..."), merge_process_label, NULL));
	IupSetAttribute(dlg, "MENUBOX", "NO");
	IupSetAttribute(dlg, "MAXBOX", "NO");
	IupSetAttribute(dlg, "MINBOX", "NO");
	IupSetAttribute(dlg, "RESIZE", "NO");
	IupSetAttribute(dlg, "SIZE", "100x30");
	IupSetAttribute(dlg, "SIMULATEMODAL", "YES");
	IupShowXY(dlg, IUP_CENTER, IUP_MOUSEPOS);
	while (should_continue) {
		IupLoopStepWait();
	}
	return NULL;
}

pthread_t merge_process_indicator()
{
	merge_processed = 0;
	should_continue = true;
	pthread_t thread;
	pthread_create(&thread, NULL, merge_process_show_dialog, NULL);
	return thread;
}
