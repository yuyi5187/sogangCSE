TITLE listsum-text
;author:������
;input: ����, ��ĭ, +, -�� ������ ���ڿ�  output: ���ڿ��� ���� ������ ��
;function: ���ڿ��� �Է¹ް� ���ڿ����� ������ �����ϴ� �Լ��� �����, ���� ������ ���� ����Ѵ�.

INCLUDE Irvine32.inc

.data
BUF_SIZE EQU 256
inBuffer BYTE BUF_SIZE DUP (?)
inBufferN DWORD ?
intArray SDWORD BUF_SIZE/2 DUP (?)
intArrayN DWORD ?
prompts BYTE "Enter numbers(<ent> to exit) :", 0
prompte BYTE "Bye!", 0

.code
main PROC

L1:
;�Է¹����� ����ϰ� ���ڿ��� �Է¹޴´�.
mov edx, OFFSET prompts
call WriteString
call Crlf

;���ڿ��� �Է¹޴´�.
mov edx, OFFSET inBuffer
mov ecx, BUF_SIZE-1
call ReadString

;eax�� ��ȯ�� ���ڿ��� ũ�⸦ inBufferN�� �����Ѵ�.
mov inBufferN, eax
or eax, eax  ;���ڿ��� ũ�Ⱑ 0�̸� L2�� ���� ���α׷��� �����Ѵ�.
jz L2

mov edi, OFFSET intArray
call StrToInt

mov intArrayN, esi   
or esi, esi  ;���ڿ����� ������ ������ ������ 0�̸� L1���� ���� �ٽ� ���ڿ��� �Է¹޴´�.
jz L1

xor eax, eax  ;eax�� ���� ������ ���� �����ϰ� ���� 0���� �ʱ�ȭ�Ѵ�.
mov ecx, esi  ;������ ������ŭ LOOP L3�� �ݺ��Ѵ�.
mov edx, OFFSET intArray ;���� �迭�� offset�� edx�� �����Ѵ�.
L3:
add eax, [edx]  ;������ �ϳ��� eax�� ���Ѵ�.
add edx, 4
LOOP L3

;���� ���������� ���� 0���� �۴ٸ� WriteInt�� ȣ���� -��ȣ���� ����Ѵ�.
; �׷��� �ʴٸ�, WriteDec�� �̿��� ����Ѵ�.

cmp eax, 0 
jl L4

call WriteDec
call Crlf
jmp L1

L4:
call WriteInt
call Crlf
jmp L1


;���Ṯ���� ����ϰ� ���α׷��� �����Ѵ�.
L2:
mov edx, OFFSET prompte
call WriteString
exit
main ENDP

;author: ������
;input: ���ڿ�, ������ ���� ���ڿ�, ���ڿ��� ũ�� output: ���ڿ��� ����� ������ �迭
;function: ���ڿ��� parsing�Ͽ� ������ �����ϰ�, �迭 intArray�� ������ �Ҵ��Ͽ� ��ȯ�Ѵ�.

StrToInt PROC
mov ebx, 0 ; ������ ��ȯ�� ���ڿ��� ũ��
mov esi, 0 ;���� �迭�� ����

mov ecx, eax ;�Է¹��� ���ڿ��� ���̸�ŭ LOOP S1�� �ݺ��Ѵ�. 
S1:
;���ڰ� ������ ��쿡 S2�� �����Ѵ�.
mov al, [edx]
cmp al, 20h
jz S2
;���ڰ� ������ �ƴ� ���, ��ȯ�� ���ڿ��� ���̸� ������Ų��.
inc ebx
jmp S3

S2:
;���ڰ� �����̰�, �������� ��� �����̾��� ��쿡�� S3�� �����Ѵ�.
or ebx, 0
jz S3

;���ڰ� ����������, ������ ���ڰ� ���Դ� ��쿡�� ������ ��ȯ�Ѵ�.
push edx
push ecx
mov ecx, ebx
sub edx, ebx
call ParseInteger32
pop ecx
pop edx

;��ȯ�� ������ intArray�� �Ҵ��Ѵ�.
mov [edi+esi*4], eax 
inc esi
;ebx�� 0���� �ʱ�ȭ�Ѵ�.
xor ebx, ebx

S3:
inc edx
LOOP S1

;���ڿ��� �������� ���ڰ� �ִ��� �����̾������� �����Ѵ�.
or ebx, ebx ;�����̶�� S4�� �����Ѵ�.
jz S4

;���ڿ��� ������ ���ڸ� ������ ��ȯ�Ͽ� intArray�� �����Ѵ�.
mov ecx, ebx
sub edx, ebx
call ParseInteger32
mov [edi+esi*4],eax
inc esi

S4:
ret
StrToInt ENDP
END main