#include <nan.h>
#include "myobject.h"
#include "sandbox.h"
#include "nodeWindow.h"

void InitAll(v8::Local<v8::Object> exports) {
	MyObject::Init(exports);
	SandBox::Init(exports);
	Window::Init(exports);
}

NODE_MODULE(addon, InitAll)
