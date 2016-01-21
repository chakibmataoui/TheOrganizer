#include <windows.h>
#include <iostream>
#include <KeepCalmEngine.h>

int main()
{
	KeepCalm keepcalm;
	//std::cout << keepcalm.CleanByExt(L"C:\\Users\\mataoui\\The Organizer\\Ext\\*") << " Files moved" << std::endl;
	//std::cout << keepcalm.CleanBySize(L"C:\\Users\\mataoui\\The Organizer\\Size\\*") << " Files moved" << std::endl;
	//std::cout << keepcalm.CleanByDate(L"C:\\Users\\mataoui\\The Organizer\\Date\\*",4) << " Files moved" << std::endl;
	//std::cout << keepcalm.CleanByType(L"C:\\Users\\mataoui\\The Organizer\\Type\\*") << " Files moved" << std::endl;
	//system("pause");
	for (unsigned int i = 0; i < 65535; i++)
		std::wcout << '\\';
	return 0;
}