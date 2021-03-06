#include <jni.h>

#include "hellov8.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <v8.h>
#include "libplatform/libplatform.h"

#include <android/log.h>

#define  LOG_TAG    "hellov8"
#define  LOGI(...)  __android_log_print(ANDROID_LOG_INFO,LOG_TAG,__VA_ARGS__)

using namespace v8;

void Plus(const FunctionCallbackInfo<Value>& args) {
    LOGI("line:%d", __LINE__);
    HandleScope scope(args.GetIsolate());
    unsigned int a = args[0]->Uint32Value();
    unsigned int b = args[1]->Uint32Value();
    
    LOGI("result = %d", a+b);
    args.GetReturnValue().Set(Int32::New(args.GetIsolate(), a+b));
}

class ArrayBufferAllocator : public v8::ArrayBuffer::Allocator {
public:
    virtual void* Allocate(size_t length) {
        void* data = AllocateUninitialized(length);
        return data == NULL ? data : memset(data, 0, length);
    }
    virtual void* AllocateUninitialized(size_t length) {
        return malloc(length);
    }
    virtual void Free(void* data, size_t) {
        free(data);
    }
};



JNIEXPORT void JNICALL Java_com_example_hellov8_MainActivity_runJs(JNIEnv* env, jobject obj,
        jstring jsCode) {
    Platform* platform = v8::platform::CreateDefaultPlatform();
    V8::InitializePlatform(platform);
    V8::Initialize();
    // Create a new Isolate and make it the current one.
    ArrayBufferAllocator allocator;
    Isolate::CreateParams create_params;
    create_params.array_buffer_allocator = &allocator;
    Isolate* isolate = Isolate::New(create_params);
    {
        Isolate::Scope isolate_scope(isolate);

        // Create a stack-allocated handle scope.
        HandleScope handle_scope(isolate);

        Handle<ObjectTemplate> global = ObjectTemplate::New(isolate);
        global->Set(v8::String::NewFromUtf8(isolate,"plus"), FunctionTemplate::New(isolate, Plus));

        // Create a new context.
        Local<Context> context = Context::New(isolate, NULL, global);

        // Enter the context for compiling and running the hello world script.
        Context::Scope context_scope(context);

        LOGI("line:%d", __LINE__);

        // Create a string containing the JavaScript source code.
        Local<String> source =
            String::NewFromUtf8(isolate, "'Hello' + 'World!'; plus(1,2);",
                                NewStringType::kNormal).ToLocalChecked();

        // Compile the source code.
        Local<Script> script = Script::Compile(context, source).ToLocalChecked();
        LOGI("line:%d", __LINE__);

        // Run the script to get the result.
        Local<Value> result = script->Run(context).ToLocalChecked();
        LOGI("line:%d", __LINE__);

        // Convert the result to an UTF8 string and print it.
        /*
        String::Utf8Value utf8(result);
        LOGI("result:%s", *utf8);
        */
    }

    // Dispose the isolate and tear down V8.
    isolate->Dispose();
    V8::Dispose();
    V8::ShutdownPlatform();
    delete platform;


}

