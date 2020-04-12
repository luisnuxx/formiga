#include "v8_engine.hpp"


// Extracts a C string from a V8 Utf8Value.
const char* ToCString(const v8::String::Utf8Value& value) {
    return *value ? *value : "<string conversion failed>";
}

// The callback that is invoked by v8 whenever the JavaScript 'print'
// function is called.  Prints its arguments on stdout separated by
// spaces and ending with a newline.
void Print(const v8::FunctionCallbackInfo<v8::Value>& args) {
    bool first = true;
    std::cout << "PRINT CALLED C++ SIDE " << std::endl;
    for (int i = 0; i < args.Length(); i++) {
        v8::HandleScope handle_scope(args.GetIsolate());
        if (first) {
            first = false;
        } else {
            printf(" ");
        }
        v8::String::Utf8Value str(args[i]);
        const char* cstr = ToCString(str);
        printf("%s", cstr);
    }
    printf("\n");
    fflush(stdout);
}

static void Returns42(const v8::FunctionCallbackInfo<v8::Value>& args) {
    std::cout << "Returns42 CALLED:: Function args length " << args.Length() << std::endl;
    double value = 42;
    for (int i = 0; i < args.Length(); i++) {
        v8::HandleScope handle_scope(args.GetIsolate());
        value += args[i]->NumberValue();
        std::cout <<  "Arg :: " << i << " :: " << value << std::endl;
    }
    args.GetReturnValue().Set(value);
}



void V8Engine::Initialize() {
    // Initialize V8.
    //argv[0]
    std::cout << "V8Engine::Initialize() :: working dir :: " << luisnuxx::getWorkingDir().c_str() << std::endl;
    V8::InitializeExternalStartupData("./v8/");
    V8::InitializeICUDefaultLocation("./v8/");
    // V8::InitializeICUDefaultLocation(luisnuxx::getWorkingDir().c_str());
    // V8::InitializeExternalStartupData(luisnuxx::getWorkingDir().c_str());
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

        v8::HandleScope scope(isolate);
        Local<Object> global = context->Global();
        Local<v8::Function> function =
                Function::New(context, Returns42).ToLocalChecked();
        global->Set( context, String::NewFromUtf8(isolate,"Returns42F"), function).FromJust();

        // Enter the context for compiling and running the hello world script.
        Context::Scope context_scope(context);
        // Create a string containing the JavaScript source code.
        /*
        Local<String> source = String::NewFromUtf8(isolate,js_script.c_str(),
                NewStringType::kNormal).ToLocalChecked();
        */

        TryCatch trycatch(isolate);
        Handle<String> source = String::NewFromUtf8(isolate,js_script.c_str(),
                                                   NewStringType::kNormal).ToLocalChecked();
        std::string res = "ERROR";
        Handle<Script> script = Script::Compile(source);


        // Compile the source code.
        MaybeLocal<Script> mlContext = Script::Compile( context, source);
        if(script.IsEmpty()) // is script compiled ?
        {
            if (trycatch.HasCaught()) {
                // Inspection of the exception is that it is simply null.
                // There is no real way to tell that execution terminated,
                // unless you implicitly check for null and empty message/stack??
                std::cout << "TryCatch.Exception->IsNull() " <<
                          trycatch.Exception()->IsNull() << std::endl;
                std::cout << "TryCatch.Message.IsEmpty() " <<
                          trycatch.Message().IsEmpty() << std::endl;
                std::cout << "TryCatch.StackTrace.IsEmpty() " <<
                          trycatch.StackTrace().IsEmpty() << std::endl;
            }


            return "Error Compiling Script";
        } else {
            Local<Script> script = mlContext.ToLocalChecked();

            Local<Value> result = script->Run();

            if (trycatch.HasCaught() || result.IsEmpty()) {
                Local<Value> exception = trycatch.Exception();
                String::Utf8Value exception_str(exception);
                printf("Exception :::: \n %s \n::::\n", *exception_str);
                // ...

                if (trycatch.HasCaught()) {
                    // Result will be that execution is *not* terminating and an
                    // exception has been caught.
                    std::cout << "IsExecutionTerminating "
                              << V8::IsExecutionTerminating() << std::endl;
                    std::cout << "TryCatch.HasCaught() "
                              << trycatch.HasCaught() << std::endl;
                    // Inspection of the exception is that it is simply null.
                    // There is no real way to tell that execution terminated,
                    // unless you implicitly check for null and empty message/stack??
                    std::cout << "TryCatch.Exception->IsNull() " <<
                              trycatch.Exception()->IsNull() << std::endl;
                    std::cout << "TryCatch.Message.IsEmpty() " <<
                              trycatch.Message().IsEmpty() << std::endl;
                    std::cout << "TryCatch.StackTrace.IsEmpty() " <<
                              trycatch.StackTrace().IsEmpty() << std::endl;
                }


            } else {
                std::cout << "GOT RESULT";
                String::Utf8Value utf8(result);
                res = *utf8;
            }
        }
        return res;
    }

}




