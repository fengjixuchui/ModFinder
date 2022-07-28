#include "Globals/Include.hpp"

int main()
{
	SetConsoleTitleA("ModFinder");

	std::string	processName;

	std::cout << "Process name -> ";
	std::getline(std::cin, processName);

	if (processName.find(".exe") == std::string::npos)
		processName += ".exe";

	if (Process::GetHandle(processName.c_str()))
	{
		system("cls");
		Query::MemoryRegions(processName);
	}
	else
	{
		system("cls");
		printf("Unable to parse process\nClosing in five seconds");
		std::this_thread::sleep_for(std::chrono::milliseconds(5000));
		exit(-1);
	}
}