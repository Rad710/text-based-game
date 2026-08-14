#include "Platform.h"

#ifdef __EMSCRIPTEN__
#include<emscripten.h>
#include<cstdio>
#include<cstdlib>

// Bracket notation is load-bearing: Closure (--closure 1) renames dotted
// properties on Module, so Module.readLine would become Module.Yb at runtime.
EM_ASYNC_JS(char*, platformReadLineJs, (), {
	const line = await Module["readLine"]();
	return stringToNewUTF8(line);
});

void readLine(std::string& line)
{
	std::cout.flush();
	std::fflush(stdout); // push the prompt out before we suspend
	char* text = platformReadLineJs();
	line = text ? text : "";
	std::free(text);
}

#else

void readLine(std::string& line) { std::getline(std::cin, line); }

#endif
