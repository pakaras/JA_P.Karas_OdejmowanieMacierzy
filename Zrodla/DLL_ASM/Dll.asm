.code

subtractionAsm PROC

	EMMS			;clears registers for MMX use
	MOVQ mm0, a[0]	;mm0 holds eight bytes of a
	MOVQ mm1, b[0]	;mm1 holds eight bytes of b
	PSUBB mm0, mm1	;mm0 holds eight bytes a+b
	MOVQ c[0], mm0	;eight bytes of result put into memory
	EMMS			;clears registers

	ret

subtractionAsm endp

end
