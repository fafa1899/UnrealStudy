#include "Output.h"

#include <Engine.h>
#include <Logging/LogMacros.h>

#include <array>

namespace Output
{
	void PrintScreen(const char* lpszFormat, ...)
	{
		char szInfo[512];

		va_list argList;
		va_start(argList, lpszFormat);
		vsnprintf(szInfo, 512, lpszFormat, argList);
		va_end(argList);

		//GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, FString::Printf(TEXT("Print Message this is %f"), 2.3f));
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, FString(UTF8_TO_TCHAR(szInfo)));
	}

	void PrintLogWarning(const char* lpszFormat, ...)
	{
		char szInfo[512];

		va_list argList;
		va_start(argList, lpszFormat);
		vsnprintf(szInfo, 512, lpszFormat, argList);
		va_end(argList);
		
		UE_LOG(LogTemp, Warning, TEXT("%s"), UTF8_TO_TCHAR(szInfo));
	}

	void PrintLogError(const char* lpszFormat, ...)
	{
		char szInfo[512];

		va_list argList;
		va_start(argList, lpszFormat);
		vsnprintf(szInfo, 512, lpszFormat, argList);
		va_end(argList);

		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, FString(UTF8_TO_TCHAR(szInfo)));
		UE_LOG(LogTemp, Error, TEXT("%s"), UTF8_TO_TCHAR(szInfo));
	}
	
};