#include "sandbox.h"

Nan::Persistent<v8::Function> SandBox::constructor;

SandBox::SandBox() {
}

SandBox::~SandBox() {
}

void SandBox::Init(v8::Local<v8::Object> exports) {
	Nan::HandleScope scope;

	// Prepare constructor template
	v8::Local<v8::FunctionTemplate> tpl = Nan::New<v8::FunctionTemplate>(New);
	tpl->SetClassName(Nan::New("SandBox").ToLocalChecked());
	tpl->InstanceTemplate()->SetInternalFieldCount(1);

	// Prototype
	Nan::SetPrototypeMethod(tpl, "add", Add);

	constructor.Reset(tpl->GetFunction());
	exports->Set(Nan::New("SandBox").ToLocalChecked(), tpl->GetFunction());
}

void SandBox::New(const Nan::FunctionCallbackInfo<v8::Value>& info) {
	if (info.IsConstructCall()) {
		// Invoked as constructor: `new SandBox(...)`
		SandBox* obj = new SandBox();
		obj->Wrap(info.This());
		info.GetReturnValue().Set(info.This());
	}
	else {
		// Invoked as plain function `SandBox(...)`, turn into construct call.
		const int argc = 0;
		v8::Local<v8::Function> cons = Nan::New<v8::Function>(constructor);
		info.GetReturnValue().Set(cons->NewInstance(argc, nullptr));
	}
}

void SandBox::Add(const Nan::FunctionCallbackInfo<v8::Value>& info) {
	assert(info.Length() == 2);
	if (!info[0]->IsString())
		return;

	info.This()->Set(info[0]->ToString(), info[1]);

	v8::Local<v8::Value> argv[2] = {
		Nan::New("added").ToLocalChecked(),  // event name
		info[0]->ToString()
	};
	Nan::MakeCallback(info.This(), "post", 2, argv);

}

