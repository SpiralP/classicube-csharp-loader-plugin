#include "pch.h"

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


using namespace System;

static void TestPlugin_Init(void) {
	cc_string msg = String_FromConst("Hello world!");
	Chat_Add(&msg);
}

extern "C" {
	EXPORT int Plugin_ApiVersion = 1;
	EXPORT struct IGameComponent Plugin_Component = { TestPlugin_Init };
}
