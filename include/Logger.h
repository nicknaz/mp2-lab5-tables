#pragma once
#include <iostream>
#include <fstream>
#include <string>

class Logger
{
public:
	Logger() {
		std::ofstream out;
		out.open("../Logs.txt");
		if (out.is_open())
		{
			out << "------------" << std::endl;
		}
	};

	void DebugLog(std::string str) {
		std::ofstream out("../Logs.txt", std::ios::app);
		if (out.is_open())
		{
			out << str << std::endl;
		}
		out.close();
	}
};
