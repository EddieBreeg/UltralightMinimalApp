#pragma once
#include <AppCore/AppCore.h>
#include <string_view>

class TestApp : public ultralight::ViewListener,
                public ultralight::WindowListener
{
public:
    ~TestApp();
    static TestApp &create(const char *title, uint32_t width, uint32_t height);
    static TestApp &instance() { return *_instance; }
    void run() { _app->Run(); }

    void OnClose(ultralight::Window *) override;
    void OnResize(ultralight::Window *, uint32_t w, uint32_t h) override;

private:
    TestApp(const char *title, uint32_t width, uint32_t height);

    static TestApp *_instance;
    ultralight::RefPtr<ultralight::App> _app;
    ultralight::RefPtr<ultralight::Window> _win;
    ultralight::RefPtr<ultralight::Overlay> _overlay;
};
