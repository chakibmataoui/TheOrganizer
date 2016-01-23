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
#include <iostream>
#include <tchar.h>
#include <vector>
#include <string>
#include <ShlObj.h>
#ifdef KEEPCALMENGINE_EXPORTS
#define KEEPCALMENGINE_API __declspec(dllexport)
#else
#define KEEPCALMENGINE_API __declspec(dllimport)
#endif

/*
How To Clean : 
-While there's files 
	Get File 
	Get ext or date or type or size
	Generate Dir name by the inf
	Check if it already exists 
		if yes then move it there
		else create the dir

*/
//Utility Functions prototyping
namespace  KCU {
	KEEPCALMENGINE_API wchar_t* GetExtOfFile(wchar_t* FileName);
	KEEPCALMENGINE_API wchar_t* CatSizeOfFile(DWORD low, DWORD high);//get if the file is b kb or mb or gb size

}

class KEEPCALMENGINE_API KeepCalm {
public:
	//Automatic Cleanings
	int CleanByExt(wchar_t* Src_Path);		//Re-Ordering automatically according to extension
	int CleanByDate(wchar_t* Src_Path,int Date = 0);		//Re-Ordering automatically according to dates of creations 
	int CleanByType(wchar_t* Src_Path,wchar_t* CurDir);		//Re-Ordering automatically according to types 'extensions' (Document,Images,Video...)
	int CleanBySize(wchar_t* Src_Path);		//Re-Ordering according to size ranges B-Kb Mb Gb Tb
};


//This is the LOT_O that i wasted time working on -_-
/*
I though i can find another useful file model to know automatically what to return which is  :
<ext1,ext2,..,extN>Application;<ext1,ext2,..,extN>Compressed;
I'll do in LOT_O an alphabetical re-organizer to find faster extensions
*/
class KEEPCALMENGINE_API KeepCalmTypeSearch {
public:
	void OpenFileC(wchar_t *FilePath);
	wchar_t* SearchExt(char *Ext);
	void CloseFile();
private:
	bool CheckSyntax();
	HANDLE RFile = NULL;

};