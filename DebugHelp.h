#pragma once
#include <iostream>

// Handles Printing Colored Text
class Print
{
public:
    // Dont Print New Lines
	static void Red(const char* text)
	{
		// \033[0m To Reset Text Color
		std::cout << "\033[31m" << text << "\033[0m";
	}

    static void Green(const char* text) {
        std::cout << "\033[32m" << text << "\033[0m";
    }

    static void Yellow(const char* text) {
        std::cout << "\033[33m" << text << "\033[0m";
    }

    static void Blue(const char* text) {
        std::cout << "\033[34m" << text << "\033[0m";
    }

    static void Magenta(const char* text) {
        std::cout << "\033[35m" << text << "\033[0m";
    }

    static void Cyan(const char* text) {
        std::cout << "\033[36m" << text << "\033[0m";
    }

    static void Pink(const char* text) 
    {
        std::cout << "\033[95m" << text << "\033[0m";
    }


    // Prints New Lines As Well
    static void RedLine(const char* text)
    {
        // \033[0m To Reset Text Color
        std::cout << "\033[31m" << text << "\033[0m" << std::endl;
    }

    static void GreenLine(const char* text) {
        std::cout << "\033[32m" << text << "\033[0m" << std::endl;
    }

    static void YellowLine(const char* text) {
        std::cout << "\033[33m" << text << "\033[0m" << std::endl;
    }

    static void BlueLine(const char* text) {
        std::cout << "\033[34m" << text << "\033[0m" << std::endl;
    }

    static void MagentaLine(const char* text) {
        std::cout << "\033[35m" << text << "\033[0m" << std::endl;
    }

    static void CyanLine(const char* text) {
        std::cout << "\033[36m" << text << "\033[0m" << std::endl;
    }

    static void PinkLine(const char* text)
    {
        std::cout << "\033[95m" << text << "\033[0m" << std::endl;
    }

};

// Handles Printing Errors
class Error
{
public:
    static void Print(const char* type, const char* msg)
    {
        Print::Red(type);
        Print::RedLine(msg);
    }

    static void PrintExit(const char* type, const char* msg)
    {
        Print::Red(type);
        Print::RedLine(msg);
        exit(0);
    }
    static void PrintExit(std::string type, std::string msg)
    {
        Print::Red(type.c_str());
        Print::RedLine(msg.c_str());
        exit(0);
    }
};

class Debug
{
public:
    static void Error(const char* type, const char* msg)
    {
        Print::Red(type);
        Print::RedLine(msg);
        exit(0);
    }

    static void Warning(const char* type, const char* msg)
    {
        Print::Yellow(type);
        Print::YellowLine(msg);
    }

    static void Print(const char* msg)
    {
        std::cout << msg;
    }


};