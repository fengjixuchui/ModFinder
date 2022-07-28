#include "Globals/Include.hpp"

int main()
{
	SetConsoleTitleA("ModFinder");

	std::string	processName;

	std::cout << "Process name: ";
	std::getline(std::cin, processName);

	if (processName.find(".exe") == std::string::npos)
		processName += ".exe";

	if (Process::GetHandle(processName.c_str()))
	{
		system("cls");
		Query::LinkedProcessAddresses(processName);
		Query::MemoryRegions(processName);
	}
	else
	{
		system("cls");
		std::cout << "Unable to parse process\n" << "Closing in 2 seconds\n";
		std::this_thread::sleep_for(std::chrono::milliseconds(2000));
		exit(0);
	}
}