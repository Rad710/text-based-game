#pragma once
#include<string>
#include<iostream>

// Console operations that differ between a native build and a browser build.
// The browser has no blocking stdin, so the WASM build's readLine() suspends
// the program through Asyncify and resumes when the page hands it a line.

void readLine(std::string& line);

inline void clearScreen()
{
#if defined(_WIN32) && !defined(__EMSCRIPTEN__)
	std::system("cls");
#else
	std::cout << "\033[2J\033[H";
#endif
}
