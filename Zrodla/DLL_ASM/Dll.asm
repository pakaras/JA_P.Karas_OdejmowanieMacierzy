.data

sizeX dw ?
sizeY dw ?

.code

subtractionAsm PROC

LOCAL A: dw ,B: dw, rowA: dw ,rowB: dw ,elmCptr: dw , area0: dw , area1: dw

	emms
	movsxd r9,dword ptr [rdx]
	xor rax,rax
	
	mov rax,qword ptr[rcx]
	mov A,rax
	mov rax,qword ptr[rcx+8]
	mov B,rax
	
	mov eax,dword ptr[rdx]
	mov area0,rax
	mov eax,dword ptr[rdx+4]
	mov area1,rax

	mov eax,dword ptr[r8]
	mov sizeX,ax
	mov eax,dword ptr[r8+4]
	mov sizeY,ax
	
	mov rax,A
	mov rax,qword ptr[rax]
	mov rowA,rax

	mov r9,area0

	loop_r:
		cmp r9,area1		;w r9 jest area1
		jge loop_re

		mov rax,r9			;przesuwanie po liniach tablicy
		imul rax,8			
		add rax,A			;dodanie do adresu pierwszego wiersza
		mov rax,qword ptr[rax]	;pokazuje gdzie isc wskaünik na pierwszy wiersz
		mov rowA, rax		;zapis do zmniennej lokalnej adres pierwszego elementu danego wiersza
		
		mov rax,r10
		imul rax,8
		add rax,B
		mov rax,qword ptr[rax]
		mov rowB, rax

		mov r10,0

		mov rdx,rowB
		mov rcx,rowA

		mov rax,elmCptr
		movsd xmm3,qword ptr[rax]

			loop_j:
				cmp ax,sizeY
				jge loop_je

				movaps xmm2,oword ptr[rdx] 
				add rdx,16

				movaps xmm1,oword ptr[rcx] 
				add rcx,16

				
				movq xmm0, A[0]
				movq xmm1, B[0]
				psubw xmm0, xmm1	
				movq B[0], xmm0	

				add r11,2

				jmp loop_j
			loop_je:

			movq qword ptr[rax],mm3
			add r10,1 
			jmp loop_r


loop_re:	
mov rax,1
ret


	subtractionAsm endp
end

