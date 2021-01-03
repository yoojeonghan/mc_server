#include "stdafx.h"
#include "threadLocal.h"

__declspec(thread) int LThreadType = -1;
__declspec(thread) int LWorkerThreadId = -1;
