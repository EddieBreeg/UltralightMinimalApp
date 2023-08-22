#include "App.hpp"

int main()
{
	TestApp &app = TestApp::create("Test app", 1280, 720);
	TRY_OR_LOG(app.run());
	return 0;
}
