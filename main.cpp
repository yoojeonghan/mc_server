#include "stdafx.h"
#include "exception.h"
#include "log.h"
#include "session.h"
#include "iocpManager.h"

int main(int argc, char* argv[]) {
	try 
	{
		int port = 4000;
		if (argc >= 2) {
			port = atoi(argv[1]);
		}

		LThreadType = THREAD_MAIN;

		SetUnhandledExceptionFilter(ExceptionFilter);

		GConsoleLog.reset(new ConsoleLog("C:\\game\\serverOut.log"));

		GIocpManager.reset(new IocpManager);

		if (false == GIocpManager->Initialize(port)) return -1;

		GConsoleLog->PrintOut(true, "Start Server\n");

		GIocpManager->StartAccept(); ///< block here...

		GConsoleLog->PrintOut(true, "Accept Done\n");

		GIocpManager->Finalize();

		GConsoleLog->PrintOut(true, "End Server\n");

		return 0;
	}
	catch (int exception) 
	{
		GConsoleLog->PrintOut(true, "Execption Code:$d\n", exception);
	}
	return 0;
}