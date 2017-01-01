.data
tabA dw 100 dup (?)
tabB dw 100 dup (?)

.code

subtractionAsm PROC

	EMMS				;clears registers for MMX use
	MOVQ mm0, tabA[0]	;mm0 holds eight bytes of a
	MOVQ mm1, tabB[0]	;mm1 holds eight bytes of b
	PSUBB mm0, mm1		;mm0 holds eight bytes a+b
	MOVQ tabA[0], mm0	;eight bytes of result put into memory
	EMMS				;clears registers

	ret

subtractionAsm endp

end
