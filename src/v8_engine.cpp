#include "v8_engine.hpp"


void V8Engine::Initialize() {
    // Initialize V8.
    //argv[0]

    V8::InitializeICUDefaultLocation(luisnuxx::getWorkingDir().c_str());
    V8::InitializeExternalStartupData(luisnuxx::getWorkingDir().c_str());
    platform = platform::CreateDefaultPlatform();
    V8::InitializePlatform(platform);
    V8::Initialize();
}
void V8Engine::Destroy() {
    // Dispose the isolate and tear down V8.
    isolate->Dispose();
    V8::Dispose();
    V8::ShutdownPlatform();
    delete platform;
    delete create_params.array_buffer_allocator;
}
std::string V8Engine::Execute(std::string js_script) {

    create_params.array_buffer_allocator =
            v8::ArrayBuffer::Allocator::NewDefaultAllocator();
    //Isolate*
    isolate = Isolate::New(create_params);
    {
        Isolate::Scope isolate_scope(isolate);
        // Create a stack-allocated handle scope.
        HandleScope handle_scope(isolate);
        // Create a new context.
        Local<Context> context = Context::New(isolate);
        // Enter the context for compiling and running the hello world script.
        Context::Scope context_scope(context);
        // Create a string containing the JavaScript source code.
        Local<String> source =

                String::NewFromUtf8(isolate,js_script.c_str(),
                                    NewStringType::kNormal).ToLocalChecked();
        // Compile the source code.
        Local<Script> script;

        script = Script::Compile(context, source).ToLocalChecked();

        TryCatch trycatch(isolate);

        Local<Value> result = script->Run();
        if (result.IsEmpty()) {
            Local<Value> exception = trycatch.Exception();
            String::Utf8Value exception_str(exception);
            printf("Exception:::: %s\n", *exception_str);
            // ...
        }
        String::Utf8Value utf8(result);
        std::string res = *utf8;

        //delete result;

        return res;

        //String::Utf8Value utf8(result);
        //printf("%s\n", *utf8);

        /*
        // Run the script to get the result.
        Local<Value> result = script->Run(context).ToLocalChecked();
        // Convert the result to an UTF8 string and print it.
        String::Utf8Value utf8(result);
        printf("%s\n", *utf8);
         */
    }

}


