#include "App.hpp"

TestApp *TestApp::_instance = nullptr;

using namespace ultralight;

TestApp::TestApp(const char *title, uint32_t width, uint32_t height)
{
    _app = App::Create();
    _win = Window::Create(_app->main_monitor(), width, height, false, WindowFlags::kWindowFlags_Titled | WindowFlags::kWindowFlags_Maximizable | WindowFlags::kWindowFlags_Resizable);
    _win->SetTitle(title);
    _win->set_listener(this);

    _overlay = Overlay::Create(_win, _win->width(), _win->height(), 0, 0);
    _overlay->view()->LoadURL("file:///index.html");
    _overlay->view()->set_view_listener(this);
}

TestApp::~TestApp()
{
}
void TestApp::OnClose(Window *)
{
    _app->Quit();
}
void TestApp::OnResize(ultralight::Window *, uint32_t w, uint32_t h)
{
    _overlay->Resize(w, h);
}

TestApp &TestApp::create(const char *title, uint32_t width, uint32_t height)
{
    if (_instance)
        return *_instance;
    static TestApp app(title, width, height);
    return *(_instance = &app);
}