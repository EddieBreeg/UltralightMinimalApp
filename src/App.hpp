#pragma once
#include <AppCore/AppCore.h>
#include <string_view>
#include "macros.h"

class TestApp : public ultralight::ViewListener,
                public ultralight::LoadListener,
                public ultralight::WindowListener
{
public:
    ~TestApp();
    static TestApp &create(const char *title, uint32_t width, uint32_t height);
    static TestApp &instance() { return *_instance; }
    void run() { _app->Run(); }

    void OnClose(ultralight::Window *) override;
    void OnResize(ultralight::Window *, uint32_t w, uint32_t h) override;
    void OnDOMReady(ultralight::View *caller, uint64_t frame_id, bool is_main_frame,
                    const ultralight::String &url) override;

private:
    JSValueRef OnButton(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef *, JSValueRef *);
    void setHeader(const char *header);
    JSObjectRef getJSFunc(const ultralight::JSString &funcName);

    using MemberCallback = JSValueRef (TestApp::*)(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef *, JSValueRef *);

    TestApp(const char *title, uint32_t width, uint32_t height);

    static TestApp *_instance;
    ultralight::RefPtr<ultralight::App> _app;
    ultralight::RefPtr<ultralight::Window> _win;
    ultralight::RefPtr<ultralight::Overlay> _overlay;
};
