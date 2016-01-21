#include <windows.h>
#include <Shlwapi.h>
#include <KeepCalmEngine.h>
#define atoiw _wtoi

wchar_t* ArrangePath(wchar_t* Org){
	//modify the exsiting path and creating a new string and freeing the older one
}

int WINAPI WinMain(HINSTANCE hInstance,HINSTANCE hPrevInstance,LPSTR lpCmdLine,int nCmdShow)
{
	KeepCalm kp;
	int nArgs,dateOp = 0;
	LPWSTR cmdline = GetCommandLineW();
	LPWSTR *cmdArgv = CommandLineToArgvW(cmdline, &nArgs);
	if (nArgs>3)
		dateOp = atoiw(cmdArgv[3]);//get the date parametre
	wchar_t fct[5];//copying the functionallity paramtre because strcat of cmdargv[1] changes it
	lstrcpynW(fct, cmdArgv[2],5);
	if (!cmdArgv[1]){
		MessageBox(NULL, "Error with path name", "Path error", MB_OK);
		goto end;
	}
	//Set program path to send it to cleanbytype
	for (int i = lstrlenW(cmdArgv[0]) - 1; i >= 0; i--){
		if (cmdArgv[0][i] == '\\'){
			cmdArgv[0][i] = '\0';
			break;
		}
	}
	//end
	if (cmdArgv[1][lstrlenW(cmdArgv[1])-2] != '\\')
		lstrcatW(cmdArgv[1], L"\\");
	lstrcatW(cmdArgv[1], L"*");
	if (!StrCmpW(fct, L"date")){
		if (nArgs < 3){
			MessageBox(NULL, "Error with the command", "Command error", MB_OK);
			goto end;
		}
		kp.CleanByDate(cmdArgv[1], dateOp);
	}
	else if (!StrCmpW(fct, L"extn")){
		kp.CleanByExt(cmdArgv[1]);
	}
	else if (!StrCmpW(fct, L"size"))
		kp.CleanBySize(cmdArgv[1]);
	else if (!StrCmpW(fct, L"type"))
		kp.CleanByType(cmdArgv[1],cmdArgv[0]);
	else {
		MessageBox(NULL, "Error with functionality", "Uknown error", MB_OK);
	}
end:
	for (int i = 0; i < nArgs; i++)
		delete[] cmdArgv[i];
	delete[] cmdline;
	return 0;
}