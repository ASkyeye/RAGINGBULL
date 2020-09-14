global EnterKmMode
global LeaveKmMode

segment .text$A

EnterKmMode:
	%ifidn __OUTPUT_FORMAT__, win32
		incbin	'source/asm/get_pos.x86.bin'	
		push	ebp
		mov	ebp, esp
	%else
		incbin	'source/asm/get_pos.x64.bin'
		push	rsi
		mov	rsi, rsp
		and	rsp, 0FFFFFFFFFFFFFFF0h
		sub	rsp, 020h
	%endif

	%ifidn __OUTPUT_FORMAT__, win32
		extern	_KmEntryPoint
		extern	_IrqlLowerIrql

		push	0x41414141
		push	eax

		call	_IrqlLowerIrql
		cmp	eax, 1
		je	ExitClean
		call	_KmEntryPoint
	%else
		extern	KmEntryPoint
		extern	IrqlLowerIrql

		push	rax
		pop	rcx
		push	0x41414141
		pop	rdx

		call	IrqlLowerIrql
		cmp	rax, 1
		je	ExitClean
		call	KmEntryPoint
	%endif

ExitClean:

	%ifidn __OUTPUT_FORMAT__, win32	
		leave;
	%else
		mov	rsp, rsi;
		pop	rsi;
	%endif

	ret


segment .text$C

LeaveKmMode:
	int3
	int3
	int3
	int3
