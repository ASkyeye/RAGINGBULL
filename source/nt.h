
#ifndef NT_H
#define NT_H

typedef enum _KIRQL
{
	PASSIVE_LEVEL	= 0,
	APC_LEVEL	= 1,
	DISPATCH_LEVEL	= 2
} KIRQL;

typedef enum _WORK_QUEUE_TYPE
{
	CriticalWorkQueue,
	DelayedWorkQueue
} WORK_QUEUE_TYPE;

typedef enum _SYSTEM_INFORMATION_CLASS
{
	SystemModuleInformation = 11
} SYSTEM_INFORMATION_CLASS;

typedef enum _POOL_TYPE
{
	NonPagedPool,
	PagedPool,
	NonPagedPoolMustSucceed,
	ReservedType,
	NonPagedPoolCacheAligned,
	PagedPoolCacheAligned
} POOL_TYPE;

typedef struct _WORK_QUEUE_ITEM
{
	LIST_ENTRY	List;
	PVOID		Routine;
	PVOID		Parameter;
} WORK_QUEUE_ITEM, *PWORK_QUEUE_ITEM;

typedef struct _SYSTEM_MODULE_ENTRY
{
	HANDLE	Section;
	PVOID	MappedBase;
	PVOID	ImageBase;
	ULONG	ImageSize;
	ULONG	Flags;
	USHORT	LoadOrderIndex;
	USHORT	InitOrderIndex;
	USHORT	LoadCount;
	USHORT	OffsetToFileName;
	UCHAR	FullPathName[ MAX_PATH - 4 ];
} SYSTEM_MODULE_ENTRY, *PSYSTEM_MODULE_ENTRY;

typedef struct _SYSTEM_MODULE_INFORMATION
{
	ULONG			Count;
	SYSTEM_MODULE_ENTRY 	Module[1];
} SYSTEM_MODULE_INFORMATION, *PSYSTEM_MODULE_INFORMATION;

NTSTATUS
NTAPI
ZwQuerySystemInformation(
	IN SYSTEM_INFORMATION_CLASS SystemInformationClass,
	IN PVOID SystemInformation,
	IN ULONG SystemInformationLength,
	IN PVOID ReturnLength
	);

PVOID
NTAPI
ExAllocatePool(
	IN POOL_TYPE PoolType,
	IN SIZE_T NumberOfBytes
	);

VOID
NTAPI
ExFreePool(
	IN PVOID a
	);

VOID
NTAPI
ExQueueWorkItem(
	IN PWORK_QUEUE_ITEM WorkItem,
	IN WORK_QUEUE_TYPE QueueType
	);

KIRQL
NTAPI
KeGetCurrentIrql(
	IN VOID
	);

#endif
