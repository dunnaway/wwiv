	; Don't even think of reading this code
	; It was automatically generated by bf-586.pl
	; Which is a perl program used to generate the x86 assember for
	; any of elf, a.out, BSDI, Win32, gaswin (for GNU as on Win32) or Solaris
	; eric <eay@cryptsoft.com>
	; 
segment .text
global	_BF_encrypt
_BF_encrypt:
	; 
	push	ebp
	push	ebx
	mov	ebx,		[12+esp]
	mov	ebp,		[16+esp]
	push	esi
	push	edi
	; Load the 2 words
	mov	edi,		[ebx]
	mov	esi,		[4+ebx]
	xor	eax,		eax
	mov	ebx,		[ebp]
	xor	ecx,		ecx
	xor	edi,		ebx
	; 
	; Round 0
	mov	edx,		[4+ebp]
	mov	ebx,		edi
	xor	esi,		edx
	shr	ebx,		16
	mov	edx,		edi
	mov	al,		bh
	and	ebx,		255
	mov	cl,		dh
	and	edx,		255
	mov	eax,		[72+eax*4+ebp]
	mov	ebx,		[1096+ebx*4+ebp]
	add	ebx,		eax
	mov	eax,		[2120+ecx*4+ebp]
	xor	ebx,		eax
	mov	edx,		[3144+edx*4+ebp]
	add	ebx,		edx
	xor	eax,		eax
	xor	esi,		ebx
	; 
	; Round 1
	mov	edx,		[8+ebp]
	mov	ebx,		esi
	xor	edi,		edx
	shr	ebx,		16
	mov	edx,		esi
	mov	al,		bh
	and	ebx,		255
	mov	cl,		dh
	and	edx,		255
	mov	eax,		[72+eax*4+ebp]
	mov	ebx,		[1096+ebx*4+ebp]
	add	ebx,		eax
	mov	eax,		[2120+ecx*4+ebp]
	xor	ebx,		eax
	mov	edx,		[3144+edx*4+ebp]
	add	ebx,		edx
	xor	eax,		eax
	xor	edi,		ebx
	; 
	; Round 2
	mov	edx,		[12+ebp]
	mov	ebx,		edi
	xor	esi,		edx
	shr	ebx,		16
	mov	edx,		edi
	mov	al,		bh
	and	ebx,		255
	mov	cl,		dh
	and	edx,		255
	mov	eax,		[72+eax*4+ebp]
	mov	ebx,		[1096+ebx*4+ebp]
	add	ebx,		eax
	mov	eax,		[2120+ecx*4+ebp]
	xor	ebx,		eax
	mov	edx,		[3144+edx*4+ebp]
	add	ebx,		edx
	xor	eax,		eax
	xor	esi,		ebx
	; 
	; Round 3
	mov	edx,		[16+ebp]
	mov	ebx,		esi
	xor	edi,		edx
	shr	ebx,		16
	mov	edx,		esi
	mov	al,		bh
	and	ebx,		255
	mov	cl,		dh
	and	edx,		255
	mov	eax,		[72+eax*4+ebp]
	mov	ebx,		[1096+ebx*4+ebp]
	add	ebx,		eax
	mov	eax,		[2120+ecx*4+ebp]
	xor	ebx,		eax
	mov	edx,		[3144+edx*4+ebp]
	add	ebx,		edx
	xor	eax,		eax
	xor	edi,		ebx
	; 
	; Round 4
	mov	edx,		[20+ebp]
	mov	ebx,		edi
	xor	esi,		edx
	shr	ebx,		16
	mov	edx,		edi
	mov	al,		bh
	and	ebx,		255
	mov	cl,		dh
	and	edx,		255
	mov	eax,		[72+eax*4+ebp]
	mov	ebx,		[1096+ebx*4+ebp]
	add	ebx,		eax
	mov	eax,		[2120+ecx*4+ebp]
	xor	ebx,		eax
	mov	edx,		[3144+edx*4+ebp]
	add	ebx,		edx
	xor	eax,		eax
	xor	esi,		ebx
	; 
	; Round 5
	mov	edx,		[24+ebp]
	mov	ebx,		esi
	xor	edi,		edx
	shr	ebx,		16
	mov	edx,		esi
	mov	al,		bh
	and	ebx,		255
	mov	cl,		dh
	and	edx,		255
	mov	eax,		[72+eax*4+ebp]
	mov	ebx,		[1096+ebx*4+ebp]
	add	ebx,		eax
	mov	eax,		[2120+ecx*4+ebp]
	xor	ebx,		eax
	mov	edx,		[3144+edx*4+ebp]
	add	ebx,		edx
	xor	eax,		eax
	xor	edi,		ebx
	; 
	; Round 6
	mov	edx,		[28+ebp]
	mov	ebx,		edi
	xor	esi,		edx
	shr	ebx,		16
	mov	edx,		edi
	mov	al,		bh
	and	ebx,		255
	mov	cl,		dh
	and	edx,		255
	mov	eax,		[72+eax*4+ebp]
	mov	ebx,		[1096+ebx*4+ebp]
	add	ebx,		eax
	mov	eax,		[2120+ecx*4+ebp]
	xor	ebx,		eax
	mov	edx,		[3144+edx*4+ebp]
	add	ebx,		edx
	xor	eax,		eax
	xor	esi,		ebx
	; 
	; Round 7
	mov	edx,		[32+ebp]
	mov	ebx,		esi
	xor	edi,		edx
	shr	ebx,		16
	mov	edx,		esi
	mov	al,		bh
	and	ebx,		255
	mov	cl,		dh
	and	edx,		255
	mov	eax,		[72+eax*4+ebp]
	mov	ebx,		[1096+ebx*4+ebp]
	add	ebx,		eax
	mov	eax,		[2120+ecx*4+ebp]
	xor	ebx,		eax
	mov	edx,		[3144+edx*4+ebp]
	add	ebx,		edx
	xor	eax,		eax
	xor	edi,		ebx
	; 
	; Round 8
	mov	edx,		[36+ebp]
	mov	ebx,		edi
	xor	esi,		edx
	shr	ebx,		16
	mov	edx,		edi
	mov	al,		bh
	and	ebx,		255
	mov	cl,		dh
	and	edx,		255
	mov	eax,		[72+eax*4+ebp]
	mov	ebx,		[1096+ebx*4+ebp]
	add	ebx,		eax
	mov	eax,		[2120+ecx*4+ebp]
	xor	ebx,		eax
	mov	edx,		[3144+edx*4+ebp]
	add	ebx,		edx
	xor	eax,		eax
	xor	esi,		ebx
	; 
	; Round 9
	mov	edx,		[40+ebp]
	mov	ebx,		esi
	xor	edi,		edx
	shr	ebx,		16
	mov	edx,		esi
	mov	al,		bh
	and	ebx,		255
	mov	cl,		dh
	and	edx,		255
	mov	eax,		[72+eax*4+ebp]
	mov	ebx,		[1096+ebx*4+ebp]
	add	ebx,		eax
	mov	eax,		[2120+ecx*4+ebp]
	xor	ebx,		eax
	mov	edx,		[3144+edx*4+ebp]
	add	ebx,		edx
	xor	eax,		eax
	xor	edi,		ebx
	; 
	; Round 10
	mov	edx,		[44+ebp]
	mov	ebx,		edi
	xor	esi,		edx
	shr	ebx,		16
	mov	edx,		edi
	mov	al,		bh
	and	ebx,		255
	mov	cl,		dh
	and	edx,		255
	mov	eax,		[72+eax*4+ebp]
	mov	ebx,		[1096+ebx*4+ebp]
	add	ebx,		eax
	mov	eax,		[2120+ecx*4+ebp]
	xor	ebx,		eax
	mov	edx,		[3144+edx*4+ebp]
	add	ebx,		edx
	xor	eax,		eax
	xor	esi,		ebx
	; 
	; Round 11
	mov	edx,		[48+ebp]
	mov	ebx,		esi
	xor	edi,		edx
	shr	ebx,		16
	mov	edx,		esi
	mov	al,		bh
	and	ebx,		255
	mov	cl,		dh
	and	edx,		255
	mov	eax,		[72+eax*4+ebp]
	mov	ebx,		[1096+ebx*4+ebp]
	add	ebx,		eax
	mov	eax,		[2120+ecx*4+ebp]
	xor	ebx,		eax
	mov	edx,		[3144+edx*4+ebp]
	add	ebx,		edx
	xor	eax,		eax
	xor	edi,		ebx
	; 
	; Round 12
	mov	edx,		[52+ebp]
	mov	ebx,		edi
	xor	esi,		edx
	shr	ebx,		16
	mov	edx,		edi
	mov	al,		bh
	and	ebx,		255
	mov	cl,		dh
	and	edx,		255
	mov	eax,		[72+eax*4+ebp]
	mov	ebx,		[1096+ebx*4+ebp]
	add	ebx,		eax
	mov	eax,		[2120+ecx*4+ebp]
	xor	ebx,		eax
	mov	edx,		[3144+edx*4+ebp]
	add	ebx,		edx
	xor	eax,		eax
	xor	esi,		ebx
	; 
	; Round 13
	mov	edx,		[56+ebp]
	mov	ebx,		esi
	xor	edi,		edx
	shr	ebx,		16
	mov	edx,		esi
	mov	al,		bh
	and	ebx,		255
	mov	cl,		dh
	and	edx,		255
	mov	eax,		[72+eax*4+ebp]
	mov	ebx,		[1096+ebx*4+ebp]
	add	ebx,		eax
	mov	eax,		[2120+ecx*4+ebp]
	xor	ebx,		eax
	mov	edx,		[3144+edx*4+ebp]
	add	ebx,		edx
	xor	eax,		eax
	xor	edi,		ebx
	; 
	; Round 14
	mov	edx,		[60+ebp]
	mov	ebx,		edi
	xor	esi,		edx
	shr	ebx,		16
	mov	edx,		edi
	mov	al,		bh
	and	ebx,		255
	mov	cl,		dh
	and	edx,		255
	mov	eax,		[72+eax*4+ebp]
	mov	ebx,		[1096+ebx*4+ebp]
	add	ebx,		eax
	mov	eax,		[2120+ecx*4+ebp]
	xor	ebx,		eax
	mov	edx,		[3144+edx*4+ebp]
	add	ebx,		edx
	xor	eax,		eax
	xor	esi,		ebx
	; 
	; Round 15
	mov	edx,		[64+ebp]
	mov	ebx,		esi
	xor	edi,		edx
	shr	ebx,		16
	mov	edx,		esi
	mov	al,		bh
	and	ebx,		255
	mov	cl,		dh
	and	edx,		255
	mov	eax,		[72+eax*4+ebp]
	mov	ebx,		[1096+ebx*4+ebp]
	add	ebx,		eax
	mov	eax,		[2120+ecx*4+ebp]
	xor	ebx,		eax
	mov	edx,		[3144+edx*4+ebp]
	add	ebx,		edx
	; Load parameter 0 (16) enc=1
	mov	eax,		[20+esp]
	xor	edi,		ebx
	mov	edx,		[68+ebp]
	xor	esi,		edx
	mov	[4+eax],	edi
	mov	[eax],		esi
	pop	edi
	pop	esi
	pop	ebx
	pop	ebp
	ret
global	_BF_decrypt
_BF_decrypt:
	; 
	push	ebp
	push	ebx
	mov	ebx,		[12+esp]
	mov	ebp,		[16+esp]
	push	esi
	push	edi
	; Load the 2 words
	mov	edi,		[ebx]
	mov	esi,		[4+ebx]
	xor	eax,		eax
	mov	ebx,		[68+ebp]
	xor	ecx,		ecx
	xor	edi,		ebx
	; 
	; Round 16
	mov	edx,		[64+ebp]
	mov	ebx,		edi
	xor	esi,		edx
	shr	ebx,		16
	mov	edx,		edi
	mov	al,		bh
	and	ebx,		255
	mov	cl,		dh
	and	edx,		255
	mov	eax,		[72+eax*4+ebp]
	mov	ebx,		[1096+ebx*4+ebp]
	add	ebx,		eax
	mov	eax,		[2120+ecx*4+ebp]
	xor	ebx,		eax
	mov	edx,		[3144+edx*4+ebp]
	add	ebx,		edx
	xor	eax,		eax
	xor	esi,		ebx
	; 
	; Round 15
	mov	edx,		[60+ebp]
	mov	ebx,		esi
	xor	edi,		edx
	shr	ebx,		16
	mov	edx,		esi
	mov	al,		bh
	and	ebx,		255
	mov	cl,		dh
	and	edx,		255
	mov	eax,		[72+eax*4+ebp]
	mov	ebx,		[1096+ebx*4+ebp]
	add	ebx,		eax
	mov	eax,		[2120+ecx*4+ebp]
	xor	ebx,		eax
	mov	edx,		[3144+edx*4+ebp]
	add	ebx,		edx
	xor	eax,		eax
	xor	edi,		ebx
	; 
	; Round 14
	mov	edx,		[56+ebp]
	mov	ebx,		edi
	xor	esi,		edx
	shr	ebx,		16
	mov	edx,		edi
	mov	al,		bh
	and	ebx,		255
	mov	cl,		dh
	and	edx,		255
	mov	eax,		[72+eax*4+ebp]
	mov	ebx,		[1096+ebx*4+ebp]
	add	ebx,		eax
	mov	eax,		[2120+ecx*4+ebp]
	xor	ebx,		eax
	mov	edx,		[3144+edx*4+ebp]
	add	ebx,		edx
	xor	eax,		eax
	xor	esi,		ebx
	; 
	; Round 13
	mov	edx,		[52+ebp]
	mov	ebx,		esi
	xor	edi,		edx
	shr	ebx,		16
	mov	edx,		esi
	mov	al,		bh
	and	ebx,		255
	mov	cl,		dh
	and	edx,		255
	mov	eax,		[72+eax*4+ebp]
	mov	ebx,		[1096+ebx*4+ebp]
	add	ebx,		eax
	mov	eax,		[2120+ecx*4+ebp]
	xor	ebx,		eax
	mov	edx,		[3144+edx*4+ebp]
	add	ebx,		edx
	xor	eax,		eax
	xor	edi,		ebx
	; 
	; Round 12
	mov	edx,		[48+ebp]
	mov	ebx,		edi
	xor	esi,		edx
	shr	ebx,		16
	mov	edx,		edi
	mov	al,		bh
	and	ebx,		255
	mov	cl,		dh
	and	edx,		255
	mov	eax,		[72+eax*4+ebp]
	mov	ebx,		[1096+ebx*4+ebp]
	add	ebx,		eax
	mov	eax,		[2120+ecx*4+ebp]
	xor	ebx,		eax
	mov	edx,		[3144+edx*4+ebp]
	add	ebx,		edx
	xor	eax,		eax
	xor	esi,		ebx
	; 
	; Round 11
	mov	edx,		[44+ebp]
	mov	ebx,		esi
	xor	edi,		edx
	shr	ebx,		16
	mov	edx,		esi
	mov	al,		bh
	and	ebx,		255
	mov	cl,		dh
	and	edx,		255
	mov	eax,		[72+eax*4+ebp]
	mov	ebx,		[1096+ebx*4+ebp]
	add	ebx,		eax
	mov	eax,		[2120+ecx*4+ebp]
	xor	ebx,		eax
	mov	edx,		[3144+edx*4+ebp]
	add	ebx,		edx
	xor	eax,		eax
	xor	edi,		ebx
	; 
	; Round 10
	mov	edx,		[40+ebp]
	mov	ebx,		edi
	xor	esi,		edx
	shr	ebx,		16
	mov	edx,		edi
	mov	al,		bh
	and	ebx,		255
	mov	cl,		dh
	and	edx,		255
	mov	eax,		[72+eax*4+ebp]
	mov	ebx,		[1096+ebx*4+ebp]
	add	ebx,		eax
	mov	eax,		[2120+ecx*4+ebp]
	xor	ebx,		eax
	mov	edx,		[3144+edx*4+ebp]
	add	ebx,		edx
	xor	eax,		eax
	xor	esi,		ebx
	; 
	; Round 9
	mov	edx,		[36+ebp]
	mov	ebx,		esi
	xor	edi,		edx
	shr	ebx,		16
	mov	edx,		esi
	mov	al,		bh
	and	ebx,		255
	mov	cl,		dh
	and	edx,		255
	mov	eax,		[72+eax*4+ebp]
	mov	ebx,		[1096+ebx*4+ebp]
	add	ebx,		eax
	mov	eax,		[2120+ecx*4+ebp]
	xor	ebx,		eax
	mov	edx,		[3144+edx*4+ebp]
	add	ebx,		edx
	xor	eax,		eax
	xor	edi,		ebx
	; 
	; Round 8
	mov	edx,		[32+ebp]
	mov	ebx,		edi
	xor	esi,		edx
	shr	ebx,		16
	mov	edx,		edi
	mov	al,		bh
	and	ebx,		255
	mov	cl,		dh
	and	edx,		255
	mov	eax,		[72+eax*4+ebp]
	mov	ebx,		[1096+ebx*4+ebp]
	add	ebx,		eax
	mov	eax,		[2120+ecx*4+ebp]
	xor	ebx,		eax
	mov	edx,		[3144+edx*4+ebp]
	add	ebx,		edx
	xor	eax,		eax
	xor	esi,		ebx
	; 
	; Round 7
	mov	edx,		[28+ebp]
	mov	ebx,		esi
	xor	edi,		edx
	shr	ebx,		16
	mov	edx,		esi
	mov	al,		bh
	and	ebx,		255
	mov	cl,		dh
	and	edx,		255
	mov	eax,		[72+eax*4+ebp]
	mov	ebx,		[1096+ebx*4+ebp]
	add	ebx,		eax
	mov	eax,		[2120+ecx*4+ebp]
	xor	ebx,		eax
	mov	edx,		[3144+edx*4+ebp]
	add	ebx,		edx
	xor	eax,		eax
	xor	edi,		ebx
	; 
	; Round 6
	mov	edx,		[24+ebp]
	mov	ebx,		edi
	xor	esi,		edx
	shr	ebx,		16
	mov	edx,		edi
	mov	al,		bh
	and	ebx,		255
	mov	cl,		dh
	and	edx,		255
	mov	eax,		[72+eax*4+ebp]
	mov	ebx,		[1096+ebx*4+ebp]
	add	ebx,		eax
	mov	eax,		[2120+ecx*4+ebp]
	xor	ebx,		eax
	mov	edx,		[3144+edx*4+ebp]
	add	ebx,		edx
	xor	eax,		eax
	xor	esi,		ebx
	; 
	; Round 5
	mov	edx,		[20+ebp]
	mov	ebx,		esi
	xor	edi,		edx
	shr	ebx,		16
	mov	edx,		esi
	mov	al,		bh
	and	ebx,		255
	mov	cl,		dh
	and	edx,		255
	mov	eax,		[72+eax*4+ebp]
	mov	ebx,		[1096+ebx*4+ebp]
	add	ebx,		eax
	mov	eax,		[2120+ecx*4+ebp]
	xor	ebx,		eax
	mov	edx,		[3144+edx*4+ebp]
	add	ebx,		edx
	xor	eax,		eax
	xor	edi,		ebx
	; 
	; Round 4
	mov	edx,		[16+ebp]
	mov	ebx,		edi
	xor	esi,		edx
	shr	ebx,		16
	mov	edx,		edi
	mov	al,		bh
	and	ebx,		255
	mov	cl,		dh
	and	edx,		255
	mov	eax,		[72+eax*4+ebp]
	mov	ebx,		[1096+ebx*4+ebp]
	add	ebx,		eax
	mov	eax,		[2120+ecx*4+ebp]
	xor	ebx,		eax
	mov	edx,		[3144+edx*4+ebp]
	add	ebx,		edx
	xor	eax,		eax
	xor	esi,		ebx
	; 
	; Round 3
	mov	edx,		[12+ebp]
	mov	ebx,		esi
	xor	edi,		edx
	shr	ebx,		16
	mov	edx,		esi
	mov	al,		bh
	and	ebx,		255
	mov	cl,		dh
	and	edx,		255
	mov	eax,		[72+eax*4+ebp]
	mov	ebx,		[1096+ebx*4+ebp]
	add	ebx,		eax
	mov	eax,		[2120+ecx*4+ebp]
	xor	ebx,		eax
	mov	edx,		[3144+edx*4+ebp]
	add	ebx,		edx
	xor	eax,		eax
	xor	edi,		ebx
	; 
	; Round 2
	mov	edx,		[8+ebp]
	mov	ebx,		edi
	xor	esi,		edx
	shr	ebx,		16
	mov	edx,		edi
	mov	al,		bh
	and	ebx,		255
	mov	cl,		dh
	and	edx,		255
	mov	eax,		[72+eax*4+ebp]
	mov	ebx,		[1096+ebx*4+ebp]
	add	ebx,		eax
	mov	eax,		[2120+ecx*4+ebp]
	xor	ebx,		eax
	mov	edx,		[3144+edx*4+ebp]
	add	ebx,		edx
	xor	eax,		eax
	xor	esi,		ebx
	; 
	; Round 1
	mov	edx,		[4+ebp]
	mov	ebx,		esi
	xor	edi,		edx
	shr	ebx,		16
	mov	edx,		esi
	mov	al,		bh
	and	ebx,		255
	mov	cl,		dh
	and	edx,		255
	mov	eax,		[72+eax*4+ebp]
	mov	ebx,		[1096+ebx*4+ebp]
	add	ebx,		eax
	mov	eax,		[2120+ecx*4+ebp]
	xor	ebx,		eax
	mov	edx,		[3144+edx*4+ebp]
	add	ebx,		edx
	; Load parameter 0 (1) enc=0
	mov	eax,		[20+esp]
	xor	edi,		ebx
	mov	edx,		[ebp]
	xor	esi,		edx
	mov	[4+eax],	edi
	mov	[eax],		esi
	pop	edi
	pop	esi
	pop	ebx
	pop	ebp
	ret
global	_BF_cbc_encrypt
_BF_cbc_encrypt:
	; 
	push	ebp
	push	ebx
	push	esi
	push	edi
	mov	ebp,		[28+esp]
	; getting iv ptr from parameter 4
	mov	ebx,		[36+esp]
	mov	esi,		[ebx]
	mov	edi,		[4+ebx]
	push	edi
	push	esi
	push	edi
	push	esi
	mov	ebx,		esp
	mov	esi,		[36+esp]
	mov	edi,		[40+esp]
	; getting encrypt flag from parameter 5
	mov	ecx,		[56+esp]
	; get and push parameter 3
	mov	eax,		[48+esp]
	push	eax
	push	ebx
	cmp	ecx,		0
	jz NEAR	$L000decrypt
	and	ebp,		4294967288
	mov	eax,		[8+esp]
	mov	ebx,		[12+esp]
	jz NEAR	$L001encrypt_finish
L002encrypt_loop:
	mov	ecx,		[esi]
	mov	edx,		[4+esi]
	xor	eax,		ecx
	xor	ebx,		edx
	bswap	eax
	bswap	ebx
	mov	[8+esp],	eax
	mov	[12+esp],	ebx
	call	_BF_encrypt
	mov	eax,		[8+esp]
	mov	ebx,		[12+esp]
	bswap	eax
	bswap	ebx
	mov	[edi],		eax
	mov	[4+edi],	ebx
	add	esi,		8
	add	edi,		8
	sub	ebp,		8
	jnz NEAR	L002encrypt_loop
$L001encrypt_finish:
	mov	ebp,		[52+esp]
	and	ebp,		7
	jz NEAR	$L003finish
	xor	ecx,		ecx
	xor	edx,		edx
	mov	ebp,		[$L004cbc_enc_jmp_table+ebp*4]
	jmp	 ebp
L005ej7:
	mov	dh,		[6+esi]
	shl	edx,		8
L006ej6:
	mov	dh,		[5+esi]
L007ej5:
	mov	dl,		[4+esi]
L008ej4:
	mov	ecx,		[esi]
	jmp	$L009ejend
L010ej3:
	mov	ch,		[2+esi]
	shl	ecx,		8
L011ej2:
	mov	ch,		[1+esi]
L012ej1:
	mov	cl,		[esi]
$L009ejend:
	xor	eax,		ecx
	xor	ebx,		edx
	bswap	eax
	bswap	ebx
	mov	[8+esp],	eax
	mov	[12+esp],	ebx
	call	_BF_encrypt
	mov	eax,		[8+esp]
	mov	ebx,		[12+esp]
	bswap	eax
	bswap	ebx
	mov	[edi],		eax
	mov	[4+edi],	ebx
	jmp	$L003finish
$L000decrypt:
	and	ebp,		4294967288
	mov	eax,		[16+esp]
	mov	ebx,		[20+esp]
	jz NEAR	$L013decrypt_finish
L014decrypt_loop:
	mov	eax,		[esi]
	mov	ebx,		[4+esi]
	bswap	eax
	bswap	ebx
	mov	[8+esp],	eax
	mov	[12+esp],	ebx
	call	_BF_decrypt
	mov	eax,		[8+esp]
	mov	ebx,		[12+esp]
	bswap	eax
	bswap	ebx
	mov	ecx,		[16+esp]
	mov	edx,		[20+esp]
	xor	ecx,		eax
	xor	edx,		ebx
	mov	eax,		[esi]
	mov	ebx,		[4+esi]
	mov	[edi],		ecx
	mov	[4+edi],	edx
	mov	[16+esp],	eax
	mov	[20+esp],	ebx
	add	esi,		8
	add	edi,		8
	sub	ebp,		8
	jnz NEAR	L014decrypt_loop
$L013decrypt_finish:
	mov	ebp,		[52+esp]
	and	ebp,		7
	jz NEAR	$L003finish
	mov	eax,		[esi]
	mov	ebx,		[4+esi]
	bswap	eax
	bswap	ebx
	mov	[8+esp],	eax
	mov	[12+esp],	ebx
	call	_BF_decrypt
	mov	eax,		[8+esp]
	mov	ebx,		[12+esp]
	bswap	eax
	bswap	ebx
	mov	ecx,		[16+esp]
	mov	edx,		[20+esp]
	xor	ecx,		eax
	xor	edx,		ebx
	mov	eax,		[esi]
	mov	ebx,		[4+esi]
L015dj7:
	ror	edx,		16
	mov	[6+edi],	dl
	shr	edx,		16
L016dj6:
	mov	[5+edi],	dh
L017dj5:
	mov	[4+edi],	dl
L018dj4:
	mov	[edi],		ecx
	jmp	$L019djend
L020dj3:
	ror	ecx,		16
	mov	[2+edi],	cl
	shl	ecx,		16
L021dj2:
	mov	[1+esi],	ch
L022dj1:
	mov	[esi],		cl
$L019djend:
	jmp	$L003finish
$L003finish:
	mov	ecx,		[60+esp]
	add	esp,		24
	mov	[ecx],		eax
	mov	[4+ecx],	ebx
	pop	edi
	pop	esi
	pop	ebx
	pop	ebp
	ret
$L004cbc_enc_jmp_table:
	DD	0
	DD	L012ej1
	DD	L011ej2
	DD	L010ej3
	DD	L008ej4
	DD	L007ej5
	DD	L006ej6
	DD	L005ej7
L023cbc_dec_jmp_table:
	DD	0
	DD	L022dj1
	DD	L021dj2
	DD	L020dj3
	DD	L018dj4
	DD	L017dj5
	DD	L016dj6
	DD	L015dj7
