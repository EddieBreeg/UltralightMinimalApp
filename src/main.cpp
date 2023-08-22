#include "App.hpp"

#ifndef NDEBUG
#include <iostream>
#define TRY_OR_LOG(expr)               \
	try                                \
	{                                  \
		expr;                          \
	}                                  \
	catch (const std::exception &e)    \
	{                                  \
		std::cerr << e.what() << '\n'; \
	}
#else
#define TRY_OR_LOG(expr) (void *)0
#endif

int main()
{
	TestApp &app = TestApp::create("Test app", 1280, 720);
	TRY_OR_LOG(app.run());
	return 0;
}
