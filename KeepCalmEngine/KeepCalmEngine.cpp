/*The Organizer , File oganizer
Copyright (C) 2016  Mataoui Chakib Souleyman

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.*/
#include "stdafx.h"
#include "KeepCalmEngine.h"
#define MAX_PATH_SIZE MAX_PATH*126
using namespace std;

//////////////////////////PART I: MAINCLASS/////////////////////////////////////////////
//MAIN ORGANIZER
int KeepCalm::CleanByDate(wchar_t* Src_Path,int Date )
{
	/*
	0<= --> year ,,,, >=5 minutes
	Format of directory : year/mo/da_ho:mi
	*/
	WIN32_FIND_DATA fileinf;
	HANDLE hFind = INVALID_HANDLE_VALUE, hDir = INVALID_HANDLE_VALUE;
	hFind = FindFirstFile(Src_Path, &fileinf);
	if (hFind == INVALID_HANDLE_VALUE)
	{
		MessageBox(NULL, L"Invalid Path Name", L"Error", MB_OK);
		return 0;
	}
	wchar_t *DirPathW = new wchar_t[MAX_PATH_SIZE], *FilePathW = new wchar_t[MAX_PATH_SIZE],*ExtF = NULL;
	SYSTEMTIME FileCreationTime;
	int nb_files = 0;
	//Find First file
	//Find all files and folders
	do
	{
		//Working with files only
		if (fileinf.dwFileAttributes != FILE_ATTRIBUTE_DIRECTORY)
		{
			ExtF = KCU::GetExtOfFile(fileinf.cFileName);
			if (lstrcmp(ExtF,L"lnk"))
			{
				FileTimeToSystemTime(&fileinf.ftCreationTime, &FileCreationTime);
				//create the new path
				lstrcpyW(DirPathW, Src_Path);
				DirPathW[lstrlen(DirPathW) - 1] = '\0';
				if (Date >= 0)
					swprintf_s(DirPathW, MAX_PATH_SIZE, L"%s%i", DirPathW, FileCreationTime.wYear);
				if (Date >= 1)
					swprintf_s(DirPathW, MAX_PATH_SIZE, L"%s-%i", DirPathW, FileCreationTime.wMonth);
				if (Date >= 2)
					swprintf_s(DirPathW, MAX_PATH_SIZE, L"%s-%i", DirPathW, FileCreationTime.wDay);
				if (Date >= 3)
					swprintf_s(DirPathW, MAX_PATH_SIZE, L"%s %ih", DirPathW, FileCreationTime.wHour);
				if (Date >= 4)
					swprintf_s(DirPathW, MAX_PATH_SIZE, L"%s%im", DirPathW, FileCreationTime.wMinute);
				swprintf_s(DirPathW, MAX_PATH_SIZE, L"%s\\", DirPathW);
				CreateDirectory(DirPathW, NULL);
				wprintf(L"%s\n", DirPathW);
				//create the file path
				swprintf_s(DirPathW, MAX_PATH_SIZE, L"%s%s", DirPathW, fileinf.cFileName);
				lstrcpyW(FilePathW, Src_Path);
				FilePathW[lstrlen(FilePathW) - 1] = '\0';
				swprintf_s(FilePathW, MAX_PATH_SIZE, L"%s%s", FilePathW, fileinf.cFileName);
				if (MoveFile(FilePathW, DirPathW) != 0)
				{
					_tprintf(L"%s \t moved \n", FilePathW);
					nb_files++;
				}
			}
			delete[] ExtF;
			
		}
	} while (FindNextFile(hFind, &fileinf) != 0);
	FindClose(hFind);
	delete[] DirPathW, FilePathW;
	return nb_files;
}
int KeepCalm::CleanByExt(wchar_t* Src_Path)
{
	WIN32_FIND_DATA fileinf;
	HANDLE hFind = INVALID_HANDLE_VALUE, hDir = INVALID_HANDLE_VALUE;
	hFind = FindFirstFile(Src_Path, &fileinf);
	if (hFind == INVALID_HANDLE_VALUE)
	{
		MessageBox(NULL, L"Invalid Path Name", L"Error", MB_OK);
		return 0;
	}
	wchar_t *DirPathW = new wchar_t[MAX_PATH_SIZE], *FilePathW = new wchar_t[MAX_PATH_SIZE], *ExtW = NULL;
	int nb_files = 0;
	//Find all files and folders
	do
	{
		//Working with files only
		if (fileinf.dwFileAttributes != FILE_ATTRIBUTE_DIRECTORY)
		{
			//Get Ext
			ExtW = KCU::GetExtOfFile(fileinf.cFileName);
			if (lstrcmp(ExtW, L"lnk")){
				//Create the path from char to wchar_t
				lstrcpyW(DirPathW, Src_Path);
				DirPathW[lstrlenW(DirPathW) - 1] = '\0';
				lstrcatW(DirPathW, ExtW);
				//Create Dir
				CreateDirectory(DirPathW, NULL);
				lstrcatW(DirPathW, L"\\");
				lstrcatW(DirPathW, fileinf.cFileName);
				//Create File Paths names char 
				lstrcpy(FilePathW, Src_Path);
				FilePathW[lstrlen(FilePathW) - 1] = '\0';
				lstrcat(FilePathW, fileinf.cFileName);
				//Move The File 
				if (MoveFile(FilePathW, DirPathW) != 0)
				{
					_tprintf(L"%s \t moved \n", FilePathW);
					nb_files++;
				}
			}
			delete[] ExtW;
		}
	} while (FindNextFile(hFind, &fileinf) != 0);
	FindClose(hFind);
	delete[] DirPathW,FilePathW,ExtW;
  	return nb_files;
}

int KeepCalm::CleanBySize(wchar_t* Src_Path)
{
	WIN32_FIND_DATA fileinf;
	HANDLE hFind = INVALID_HANDLE_VALUE, hDir = INVALID_HANDLE_VALUE;
	hFind = FindFirstFile(Src_Path, &fileinf);
	if (hFind == INVALID_HANDLE_VALUE)
	{
		MessageBox(NULL, L"Invalid Path Name", L"Error", MB_OK);
		return 0;
	}
	wchar_t *DirPathW = new wchar_t[MAX_PATH_SIZE], *FilePathW = new wchar_t[MAX_PATH_SIZE], *ExtW = NULL,*Size = NULL;
	int nb_files = 0;
	//Find all files and folders
	do
	{
		//Working with files only
		if (fileinf.dwFileAttributes != FILE_ATTRIBUTE_DIRECTORY )
		{
			//get size of file B,KB,MB,GB
			Size = KCU::CatSizeOfFile(fileinf.nFileSizeLow, fileinf.nFileSizeHigh);
			ExtW = KCU::GetExtOfFile(fileinf.cFileName);
			if (lstrcmp(ExtW, L"lnk")){
				//Create the path from char to wchar_t
				lstrcpyW(DirPathW, Src_Path);
				DirPathW[lstrlenW(DirPathW) - 1] = '\0';
				lstrcatW(DirPathW, Size);
				//Create Dir
				CreateDirectory(DirPathW, NULL);
				lstrcatW(DirPathW, L"\\");
				lstrcatW(DirPathW, fileinf.cFileName);
				//Create File Paths names char 
				lstrcpy(FilePathW, Src_Path);
				FilePathW[lstrlen(FilePathW) - 1] = '\0';
				lstrcat(FilePathW, fileinf.cFileName);
				//Move The File 
				if (MoveFile(FilePathW, DirPathW) != 0)
				{
					_tprintf(L"%s \t moved \n", FilePathW);
					nb_files++;
				}
			}
			delete[] ExtW;
		}
	} while (FindNextFile(hFind, &fileinf) != 0);
	FindClose(hFind);
	delete[] DirPathW, FilePathW, ExtW;
	return nb_files;
}


int KeepCalm::CleanByType(wchar_t* Src_Path, wchar_t* CurDir)
{
	/*
	-Create 5 Dir Doc/Img/Vid/Mus/Prog/Compr-Arch/Code using vector with all the llnks 
	*/
	lstrcatW(CurDir, L"\\ExtFile.lot");
	WIN32_FIND_DATA fileinf;
	HANDLE hFind = INVALID_HANDLE_VALUE, hDir = INVALID_HANDLE_VALUE;
	hFind = FindFirstFile(Src_Path, &fileinf);
	if (hFind == INVALID_HANDLE_VALUE)
	{
		MessageBox(NULL, L"Invalid Path Name", L"Error", MB_OK);
		return 0;
	}
	KeepCalmTypeSearch TypeSearch;
	TypeSearch.OpenFileC(CurDir);
	wchar_t *DirPathW = new wchar_t[MAX_PATH_SIZE], *FilePathW = new wchar_t[MAX_PATH_SIZE], *ExtW = NULL ,*Type = NULL;
	char* Ext = NULL;
	int nb_files = 0;
	//Find all files and folders
	do
	{
		//Working with files only
		if (fileinf.dwFileAttributes != FILE_ATTRIBUTE_DIRECTORY)
		{
			//Get Ext
			ExtW = KCU::GetExtOfFile(fileinf.cFileName);
			if (lstrcmp(ExtW, L"lnk")){
				Ext = new char[lstrlen(ExtW) + 1];
				wcstombs_s(0, Ext, lstrlen(ExtW) + 1, ExtW, lstrlen(ExtW) + 1);
				Type = TypeSearch.SearchExt(Ext);
				//Create the path from char to wchar_t
				lstrcpyW(DirPathW, Src_Path);
				DirPathW[lstrlenW(DirPathW) - 1] = '\0';
				lstrcatW(DirPathW, Type);
				//Create Dir
				CreateDirectory(DirPathW, NULL);
				lstrcatW(DirPathW, L"\\");
				lstrcatW(DirPathW, fileinf.cFileName);
				//Create File Paths names char 
				lstrcpy(FilePathW, Src_Path);
				FilePathW[lstrlen(FilePathW) - 1] = '\0';
				lstrcat(FilePathW, fileinf.cFileName);
				//Move The File 
				if (MoveFile(FilePathW, DirPathW) != 0)
				{
					_tprintf(L"%s \t moved \n", FilePathW);
					nb_files++;
				}
			}
			delete[] ExtW,Ext;
		}
	} while (FindNextFile(hFind, &fileinf) != 0);
	FindClose(hFind);
	delete[] DirPathW, FilePathW, ExtW;
	TypeSearch.CloseFile();
	return nb_files;
}
//EXTENSION MINI-SEARCH ENGINE
void KeepCalmTypeSearch::OpenFileC(wchar_t *FilePath){
	RFile = CreateFile(FilePath, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
	if (RFile == INVALID_HANDLE_VALUE) {
		MessageBox(NULL, L"Invalid Ressource Path ", L"Error", MB_OK);
		exit(0);
	}
}
void KeepCalmTypeSearch::CloseFile(){
	CloseHandle(RFile);
}
bool KeepCalmTypeSearch::CheckSyntax(){
	if (RFile == NULL) {
		MessageBox(NULL, L"Can't find extension file ressource", L"Error", MB_OK);
		exit(0);
	}
	//first step check the  markups and then that we have at least 1 char after it and ; and that until the eof
	//UPDATE : I could have done it using a stack but i didn't study about compilers design at the time i wrote this ,i will update it 
	SetFilePointer(RFile, 0, 0, FILE_BEGIN);
	int starting_markups = 0;
	int dot_comma = 0;
	int ext_nbr = 0;
	BOOL EOFR, found_dot_comma = FALSE, inside_markup = FALSE, at_least_oneE_inside_markup = FALSE,at_least_a_type = FALSE,emptyfile = TRUE;
	DWORD ByteRead;
	char Buffer = 0;
	while (EOFR = ReadFile(RFile, &Buffer, 1, &ByteRead, 0) && ByteRead != 0){
		if (emptyfile == TRUE)
			emptyfile = FALSE;
		if (Buffer == '<'){ 
			starting_markups++; 
			inside_markup = TRUE;
		}
		else if (Buffer == '>') {
			starting_markups--; 
			dot_comma++;
			ext_nbr--;
			inside_markup = FALSE;
			if (!at_least_oneE_inside_markup)
				return FALSE;
			else
				at_least_oneE_inside_markup = FALSE;
		}
		else if (Buffer == '/') {
			if (!at_least_a_type)
				return FALSE;
			dot_comma--;
		}
		else if (Buffer == '|'){
			ext_nbr--;
		}
		else
		{
			if (inside_markup){
				at_least_oneE_inside_markup = TRUE;
				ext_nbr++;
			}
			else
				at_least_a_type = TRUE;
			do{
				EOFR = ReadFile(RFile, &Buffer, 1, &ByteRead, 0);
			} while (EOFR && Buffer != '|' && Buffer != '/' && Buffer != '<' && Buffer != '>');
			SetFilePointer(RFile, -1, 0, FILE_CURRENT);
		}
	}
	if (!starting_markups && !dot_comma && !ext_nbr && !emptyfile)
		return TRUE;
	else
		return FALSE;
	return TRUE;
}
wchar_t* KeepCalmTypeSearch::SearchExt(char *Ext){
	if (RFile == NULL) {
		MessageBox(NULL, L"Can't find extension file ressource", L"Error", MB_OK);
		exit(0);
	}
	if (this->CheckSyntax()){
		SetFilePointer(RFile,0, 0, FILE_BEGIN);
		char Buffer = 0;
		string ExtFF;
		wstring ExtT = L"Others";
		wchar_t* ExtType = NULL;
		int sizeoftype = 0,sizeofext = 0;
		DWORD ReadBytes;
		BOOL EOFR;
		while (EOFR = ReadFile(RFile, &Buffer, 1, &ReadBytes, 0) && ReadBytes != 0){
			//The file is well syntaxed so we're sure that we start with a markup
			ExtFF.clear();
			do{
				ReadFile(RFile, &Buffer, 1, 0, 0);
				if (Buffer != '|' && Buffer != '>')
					ExtFF.push_back(Buffer);
			}while (Buffer != '|' && Buffer != '>');
			if (!strcmp(Ext, ExtFF.c_str())){
				ExtT.clear();
				//We found the extension so we place the pointer to end markup
				while (Buffer != '>'){
					ReadFile(RFile, &Buffer, 1, &ReadBytes, 0);
				}
				do{
					ReadFile(RFile, &Buffer, 1, 0, 0);
					if (Buffer != '/')
						ExtT.push_back(Buffer);
				} while (Buffer != '/');
				break;
			}
			if (Buffer == '>'){
				do{
					ReadFile(RFile, &Buffer, 1, 0, 0);
				} while (Buffer != '/');
			}
			else if (Buffer == '|')
				SetFilePointer(RFile, (LONG)(-1), 0, FILE_CURRENT);

		}
		ExtType = new wchar_t[(int)ExtT.length()+1];
		lstrcpyW(ExtType, ExtT.c_str());
		return ExtType;
	}
	return L"Others";
}

//////////////////////////PART II: FUNCTIONS/////////////////////////////////////////////
wchar_t* KCU::GetExtOfFile(wchar_t* FileName)
{
	int PPos = lstrlen(FileName)-1;
	wchar_t *Ret = NULL;
	while (PPos >= 0 && FileName[PPos] != '.'){
		FileName[PPos] = towlower(FileName[PPos]);
		PPos--;
	}
	PPos++;
	Ret = new wchar_t[lstrlen(FileName) - PPos + 1];
	lstrcpy(Ret, FileName + PPos);
	return Ret;
}
wchar_t* KCU::CatSizeOfFile(DWORD low, DWORD high){
	wchar_t *sizees[] = { L"B", L"Kb", L"Mb", L"Gb", L"Tb" };
	int i = 0;
	DWORD64  a = (high * (MAXDWORD + 1)) + low;//C4307
	do{
		a /= 1000;
		if (a > 0)
			i++;
	} while (a > 0);
	return sizees[i];
}