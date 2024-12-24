	.intel_syntax noprefix
	.text
	.global sum
	
sum:
	mov r9d, ecx
	mov rcx, rdi
for:
	mov r10d, [esi + 4*ecx - 4]
	add r10d, [edx + 4*ecx - 4]
	mov [r9d + 4*ecx - 4], r10d
	loop for

	ret
