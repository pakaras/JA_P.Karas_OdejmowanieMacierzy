.data

sizeX dw ?
sizeY dw ?

.code

subtractionAsm PROC

LOCAL A: dw ,B: dw, rowA: dw ,rowB: dw ,elmCptr: dw , area0: dw , area1: dw

	emms
	movsxd r9,word ptr [rdx]
	xor ax,ax
	
	mov rax,qword ptr[rcx]
	mov A,ax
	mov rax,qword ptr[rcx+8]
	mov B,ax
	
	mov ax,word ptr[rdx]
	mov area0,ax
	mov ax,word ptr[rdx+4]
	mov area1,ax

	mov ax,word ptr[r8]
	mov sizeX,ax
	mov ax,word ptr[r8+4]
	mov sizeY,ax
	
	mov ax,A
	mov ax,word ptr[rax]
	mov rowA,ax

	mov r9,area0

	loop_r:
		cmp r9,area1		;porównywanie czy ju¿ osi¹gniêto koniec przedzia³u
		jge loop_re		;jeœli > lub = skok na koniec pêtli

		mov ax,r9			;przekazanie adresu pierwszego wiersza
		imul ax,8			
		add ax,A			;dodanie do adresu pierwszego wiersza
		mov rax,qword ptr[rax]	;pokazuje gdzie isc, wskaŸnik na pierwszy wiersz
		mov rowA, rax		;zapis do zmniennej lokalnej adres pierwszego elementu danego wiersza
		
		mov rax,r10
		imul rax,8
		add ax,B
		mov rax,qword ptr[rax]
		mov rowB, rax

		mov r10,0

		mov rdx,rowB
		mov rcx,rowA

		mov rax,elmCptr
		movsd mm3,qword ptr[rax]

			loop_j:
				cmp ax,sizeY
				jge loop_je
				
				movq mm0, A[0]	;do mm0 id¹ wartoœci z macierzy A
				movq mm1, B[0]	;do mm1 id¹ wartoœci z macierzy B
				psubb mm0, mm1	;odejmowanie z wykorzystaniem instrukcji wektorowej
				movq B[0], mm0	;zapisanie wartoœci do macierzy B

				add r11,2

				jmp loop_j
			loop_je:

			movq qword ptr[rax],mm3
			add r10,1 
			jmp loop_r

loop_re:	
mov ax,1
ret

	subtractionAsm endp
end

