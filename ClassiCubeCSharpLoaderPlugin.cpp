#include "pch.h"
#include <msclr/gcroot.h>

extern "C" {
#include "src/Chat.h"
#include "src/Game.h"
#include "src/String.h"
}

#ifdef _WIN32
#define EXPORT __declspec(dllexport)
#else
#define EXPORT __attribute__((visibility("default")))
#endif


#using <System.dll>
#using <System.Runtime.dll>

using namespace System;
using namespace System::Reflection;
using namespace msclr;


gcroot<Assembly^> assembly = nullptr;


void callMethod(String^ methodName) {
    if (static_cast<Assembly^>(assembly) == nullptr) {
        assembly = System::Reflection::Assembly::LoadFile("F:\\ClassiCube\\plugins-csharp\\csharp-classicube-plugin.dll");
    }

    array<Type^>^ typeArray = assembly->GetTypes();
    // classes
    for (int i = 0; i < typeArray->Length; i++) {
        auto initFn = typeArray[i]->GetMethod(methodName);

        if (initFn) {
            initFn->Invoke(nullptr, nullptr);
        }
    }
}

void Init() {
    callMethod("Init");
}

void Free() {
    callMethod("Free");
}

void Reset() {
    callMethod("Reset");
}

void OnNewMap() {
    callMethod("OnNewMap");
}

void OnNewMapLoaded() {
    callMethod("OnNewMapLoaded");
}

extern "C" {
	EXPORT int Plugin_ApiVersion = 1;
	EXPORT struct IGameComponent Plugin_Component = {
		Init,
		Free,
		Reset,
		OnNewMap,
		OnNewMapLoaded
    };
}
