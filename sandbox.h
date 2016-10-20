#ifndef SANDBOX_H 
#define SANDBOX_H

#include <nan.h>

class SandBox: public Nan::ObjectWrap {
 public:
  static void Init(v8::Local<v8::Object> exports);

 private:
  SandBox();
  ~SandBox();

  static void New(const Nan::FunctionCallbackInfo<v8::Value>& info);
  static void Add(const Nan::FunctionCallbackInfo<v8::Value>& info);
  static Nan::Persistent<v8::Function> constructor;
};

#endif
