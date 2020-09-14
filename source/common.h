
#ifndef COMMON_H
#define COMMON_H

#pragma intrinsic(memset)
#pragma intrinsic(memcpy)

//! External Includes
#include <intrin.h>
#include <limits.h>
#include <windows.h>
#include <ntstatus.h>

//! Structures / Hashes
#include "hashes.h"
#include "ntpcr.h"
#include "nt.h"

//! Macros
#define KMFUNC			__attribute__((section(".text$B")))
#define ZwCurrentProcess()	((HANDLE)-1)
#define UPTR(x)			((ULONG_PTR)x)
#define CPTR(x)			((PVOID)x)
#define FUNC(x)			__typeof__(x) * x

//! KM Function Table
typedef struct
{
	FUNC(ZwQuerySystemInformation);
	FUNC(KeGetCurrentIrql);
	FUNC(ExQueueWorkItem);
	FUNC(ExAllocatePool);
	FUNC(ExFreePool);
} KM_API;

//! Internal Includes
#include "hash.h"
#include "pcr.h"
#include "pe.h"

#endif // END COMMON_H
