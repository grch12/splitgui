#include "global.h"

char mode = 0;

int split_browse_cb(Ihandle* dlg)
{
	Ihandle* browse_dialog = IupFileDlg();
	IupSetAttribute(browse_dialog, "DIALOGTYPE", "OPEN");
	IupPopup(browse_dialog, IUP_DEFAULT, IUP_DEFAULT);
	
	if (IupGetInt(browse_dialog, "STATUS") != -1)
	{
		Ihandle* text = IupGetDialogChild(dlg, "FILENAME_TEXT");
		IupSetStrAttribute(text, "VALUE", IupGetAttribute(browse_dialog, "VALUE"));
	}
	return IUP_DEFAULT;
}

int split_ok_cb(Ihandle* dlg)
{
	Ihandle* filename_text = IupGetDialogChild(dlg, "FILENAME_TEXT");
	
	char* filename = IupGetAttribute(filename_text, "VALUE");
	
	if (strcmp(filename, "") == 0 || filename == NULL) return IUP_DEFAULT;
	
	FILE* source_file = fopen(filename, "rb");
	if (source_file == NULL)
	{
		char errmsg[256] = { '\0'};
		sprintf(errmsg, "%s%s", "无法打开文件，原因：", strerror(errno));
		
		IupMessageError(dlg, errmsg);
		return IUP_DEFAULT;
	}
	
	int result;
	if (mode == 0)
	{
		Ihandle* number_text = IupGetDialogChild(dlg, "NUMBER");
		int number = IupGetInt(number_text, "VALUE");
		
		if (number < 2)
		{
			IupMessageError(dlg, "至少需要分割为2个");
			return IUP_DEFAULT;
		}
		else if (number > flength(source_file))
		{
			IupMessageError(dlg, "分割数量太多");
			return IUP_DEFAULT;
		}
		
		result = split_file_by_amount(source_file, filename, number);
	}
	else
	{
		Ihandle* size_text = IupGetDialogChild(dlg, "SIZE_T");
		Ihandle* size_select = IupGetDialogChild(dlg, "SIZE_S");
		
		size_t size = IupGetInt(size_text, "VALUE");
		size_t size_unit = IupGetInt(size_select, "VALUE");
		
		if (size < 1)
		{
			IupMessageError(dlg, "大小至少需要1");
			return IUP_DEFAULT;
		}
		
		result = split_file_by_size(source_file, filename, size * (size_t)pow(1024, size_unit - 1));
	}
	
	if (result != 0)
	{
		if (result == -1) IupMessageError(dlg, "无法分配空间，可能是内存不足");
		if (result == -2) {
			char errmsg[256] = { '\0'};
			sprintf(errmsg, "%s%s", "无法创建新文件，原因：", strerror(errno));
			IupMessageError(dlg, errmsg);
		};
	}
	else
	{
		IupMessage("", "操作成功完成");
	}
	
	fclose(source_file);
	return IUP_DEFAULT;
}

int as_amount_cb(Ihandle* dlg)
{
	set_amount_enabled(dlg, "YES");
	set_size_enabled(dlg, "NO");
	mode = 0;
	return IUP_DEFAULT;
}

int as_size_cb(Ihandle* dlg)
{
	set_amount_enabled(dlg, "NO");
	set_size_enabled(dlg, "YES");
	mode = 1;
	return IUP_DEFAULT;
}

int merge_browse_cb(Ihandle* dlg)
{
	Ihandle* browse_dialog = IupFileDlg();
	IupSetAttribute(browse_dialog, "DIALOGTYPE", "OPEN");
	IupPopup(browse_dialog, IUP_DEFAULT, IUP_DEFAULT);
	
	if (IupGetInt(browse_dialog, "STATUS") != -1)
	{
		Ihandle* text = IupGetDialogChild(dlg, "MERGE_TEXT");
		IupSetStrAttribute(text, "VALUE", IupGetAttribute(browse_dialog, "VALUE"));
	}
	return IUP_DEFAULT;
}

int merge_ok_cb(Ihandle* dlg)
{
	Ihandle* filename_text = IupGetDialogChild(dlg, "MERGE_TEXT");
	
	char* filename = IupGetAttribute(filename_text, "VALUE");
	
	if (strcmp(filename, "") == 0 || filename == NULL) return IUP_DEFAULT;
	
	char* original_name = malloc(strlen(filename) + 1 - 2);
	memset(original_name, '\0', strlen(filename) + 1 - 2);
	strncpy(original_name, filename, strlen(filename) - 2);
	
	int result = merge_file(original_name);
	if (result == -1)
	{
		char errmsg[256] = { '\0'};
		sprintf(errmsg, "%s%s", "无法打开文件，原因：", strerror(errno));
		
		IupMessageError(dlg, errmsg);
		return IUP_DEFAULT;
	}
	else if (result == -2)
	{
		IupMessageError(dlg, "无法分配空间，可能是内存不足");
		return IUP_DEFAULT;
	}
	else if (result == -3) {
		char errmsg[256] = { '\0'};
		sprintf(errmsg, "%s%s", "无法创建文件，原因：", strerror(errno));
		
		IupMessageError(dlg, errmsg);
		return IUP_DEFAULT;
	}
	
	IupMessage("", "操作成功完成");
	
	free(original_name);
	
	return IUP_DEFAULT;
}

