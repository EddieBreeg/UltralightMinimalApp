#include "App.hpp"

TestApp *TestApp::_instance = nullptr;

#define METHOD_CALLBACK(funcName)                                                                                 \
    [](JSContextRef ctx, JSObjectRef f, JSObjectRef thisObj, size_t n, const JSValueRef *Args, JSValueRef *exc) { \
        return TestApp::instance().funcName(ctx, f, thisObj, n, Args, exc);                                       \
    }

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
    _overlay->view()->set_load_listener(this);
}

TestApp::~TestApp()
{
}
void TestApp::OnClose(Window *)
{
    _app->Quit();
}
void TestApp::OnDOMReady(ultralight::View *caller, uint64_t frame_id, bool is_main_frame,
                         const String &url)
{
    JSContextRef ctx = *caller->LockJSContext();
    ultralight::SetJSContext(ctx);
    DEBUG_LOG("Set javascript context");
    auto setHeaderFunc = getJSFunc("setHeader");

    JSValue str = "Hello from C++!";
    auto args = (JSValueRef)str;

    JSObjectCallAsFunction(ctx, setHeaderFunc, nullptr, 1, &args, nullptr);

    JSString funcName = "OnButton";
    auto func = JSObjectMakeFunctionWithCallback(ctx, (JSStringRef)funcName, METHOD_CALLBACK(OnButton));
    JSObjectSetProperty(ctx, JSContextGetGlobalObject(ctx), funcName, func, 0, 0);
}

JSValueRef TestApp::OnButton(JSContextRef ctx, JSObjectRef, JSObjectRef, size_t, const JSValueRef *, JSValueRef *)
{
    DEBUG_LOG("Button was clicked");
    return nullptr;
}

JSObjectRef TestApp::getJSFunc(const JSString &name)
{
    auto ctx = GetJSContext();
    auto func = JSEvaluateScript(ctx, name, nullptr, nullptr, 1, nullptr);
    auto funcObj = JSValueToObject(ctx, func, nullptr);
    return funcObj;
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