# Background

So, before the stream I began doing some initial concept designs: I wanted to be able to hook a virtual table entry in the srv2.sys , which may or may not be RW ( If its Read-Only, I can circumvent this with ease by swapping bits in CR0 off memory. ).

One entry that popped off as interesting on the few versions of Windows 10 I analyzed ( Looked @ Windows 10 1909 , 1607 and 2004 ) was the dispatch handlers for the various commands such as SMB2_COM_ECHO. There are validation and execution routines ( I guess to validate the packet is valid and the other to actually execute it if the request is valid? In that case I may have to hook both to succeed ).

![](https://i.imgur.com/Ymy9qWB.png)

I plan on targeting the Smb2ExecuteEcho() / Smb2ValidateEcho() routines. If we swap the pointer entries, we should be able to then control the execution. In this case, we'll be using it to I guess deploy additional userland shellcode.

The section ( at least on Windows 10 1909 ) the routines are located in was .rdata - So we're going to have to write a quick section parser in source/pe.c to find the section's virtual address.

I need to validate what IRQL level the code is executed at - this could help us avoid having to include the IRQL migration tactic into the kernel shellcode. If we need to though, it wont be an issue. 
