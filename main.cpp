#include <iostream>
#include <vector>
#include <string>
#include <thread>
#include <queue>
#include <exception>
#include <chrono>

/*
engine work queue
clean work queue

engine crew and clean crew should be represented by one thread each

input 100 to stop, 1 to engine ctew, 2 to clean crew

if the running thread find any command in the queue, it should execute 
the command and sleep for 1 second, if not thread should sleep for 2 seconds

captain(main thread) does not have to wait for any command to finish
and it should take 1 command for every 1 second

*/

class Engine_Crew
{
private:
	std::queue<int> engine_commands{};

public:
	void addCommand(int n)
	{
		if (n == 1)
			engine_commands.push(n);
		else printf("the command number for engine is \n");
		//else throw std::runtime_error("wrong command");
	}

	void executeCommand()
	{
		auto it = engine_commands.front();
		while (it != engine_commands.back()+1)
		{
			if (it == 1)
			{
				printf("engine crew starts work...\n");
				std::this_thread::sleep_for(std::chrono::seconds(1));
			}
			it++;
		}
	}
};

class Clean_Crew
{
private:
	std::queue<int> clean_commands{};

public:
	void addCommand(int n)
	{
		if (n == 2)
			clean_commands.push(n);
		else printf("the command number for clean is 2\n");
	}

	void executeCommand()
	{
		auto it = clean_commands.front();
		while (it != clean_commands.back()+1)
		{
			if (it == 2)
			{
				printf("clean crew starts work...\n");
				std::this_thread::sleep_for(std::chrono::seconds(1));
			}
			it++;
		}
	}
};

void handle_engine(int command)
{
	Engine_Crew e;
	e.addCommand(command);
	e.executeCommand();
}

void handle_clean(int command)
{
	Clean_Crew c;
	c.addCommand(command);
	c.executeCommand();
}

int main()
{
	Engine_Crew EC;
	Clean_Crew CC;


	while (true)
	{
		int command;
		printf("enter a command: ");
		std::cin >> command;
		
		if (command == 1)
		{
			std::thread engine_thread(handle_engine, command);
			engine_thread.join();

		}
		else if (command == 2)
		{
			std::thread clean_thread(handle_clean, command);
			clean_thread.join();
		}

		else if (command == 100) break;


	}

	printf("END OF PROGRAM");

	return 0;

}
