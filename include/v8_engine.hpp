//
// Created by Luis Rodrigues on 24/03/2018.
//

#ifndef FORMIGA_V8_HW_HPP
#define FORMIGA_V8_HW_HPP
#include <first_include.hpp>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "libv8/include/libplatform/libplatform.h"
#include "libv8/include/v8.h"
#include <utils.hpp>
#include <exception>

using namespace v8;

class V8Engine {

    private:
        Platform* platform;
        Isolate* isolate;
        Isolate::CreateParams create_params;
    public:

        std::string Execute(std::string script);
        void Destroy();
        void Initialize();

};


#endif //FORMIGA_V8_HW_HPP
