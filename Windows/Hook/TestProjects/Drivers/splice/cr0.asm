_text				SEGMENT

PUBLIC	Cr0off
PUBLIC	Cr0on						


Cr0off	PROC
		push   rax
		mov    rax, cr0        ; ��㧨� �ࠢ���騩 ॣ���� cr0 � ॣ���� rax
		and    rax, 0FFFEFFFFh ; ���뢠�� ��� WP, ������騩 ������
		mov    cr0, rax        ; ������塞 �ࠢ���騩 ॣ���� cr0
		pop    rax
		ret
Cr0off	ENDP

Cr0on	PROC
		mov    rax, cr0      ; ��㧨� �ࠢ���騩 ॣ���� cr0 � ॣ���� rax
		or     rax, 10000h   ; ���뢠�� ��� WP, ������騩 ������
		mov    cr0, rax
		ret
Cr0on	ENDP

_text				ENDS

					END