TITLE uphils-text
;author:������
;input:�׽�Ʈ ���̽� ����, �������� �� ����, �������� �� output: ���� ��簡 ���� �������� ������
;function:�� �׽�Ʈ ���̽����� ���� ��簡 ���� �������� ���� ���̸� ����Ѵ�
INCLUDE Irvine32.inc
INCLUDE CSE3030_PHW04.inc

.data
BUFFER BYTE 0Dh,0Ah,0 ;���๮��

.code
main PROC

mov esi, 0
mov ecx, TN ;�׽�Ʈ ���̽� ������ŭ ù loop�� �ݺ��Ѵ�. 
or ecx, ecx ;�׽�Ʈ ���̽� ������ 0�� ��� ����
jz LAST

L1:
push ecx
dec CASE ; ������ ���� ���, ���� ���� ���� �����Ƿ� �� ����-1 


mov eax, 0 ;�������� �ִ� �� ���̸� �����Ѵ�.(max)
mov ebx, 0 ;�� �������� ���� �� ������ ���� �����Ѵ�.(sum)
mov ecx, CASE ;CASE ��ŭ �ι�° loop�� �ݺ��Ѵ�. 
or ecx, ecx
jz NEXT3


L2:

mov edi, HEIGHT[esi]
add esi, 4
mov edx, HEIGHT[esi]

cmp edi, edx ;�ش� ���� ���� ���� ���Ͽ� ������������ �Ǵ��Ѵ�
jae NEXT ;���� ���������� �ƴϸ� NEXT�� ����. 
    sub edx, edi
    add ebx, edx ;���������� ��쿡�� �� ���̸� ���ؼ� ebx(sum)�� �����ش�.
    jmp NEXT2 

NEXT:
cmp eax, ebx 
jae NEXT1 ;���� ���� max���� sum�� ũ�� max�� sum �Ҵ��Ѵ�.
    mov  eax, ebx
    jmp NEXT1
NEXT1:
mov ebx, 0 ;���� ���������� �� ���̸� ����ϱ� ���� ebx(sum)�� 0���� �ʱ�ȭ�Ѵ�.

NEXT2:
LOOP L2

cmp eax, ebx ;������ ���������� �����̸� ���� ���, ������ max�� ���Ͽ� �� ũ�� max�� �Ҵ����ش� 
jae NEXT3
  mov eax, ebx
  jmp NEXT3

NEXT3:
call WriteDec ;���� �����̰� ū ���������� ����Ѵ�.
mov edx, OFFSET BUFFER 
call WriteString ;���๮�ڸ� ����Ѵ�.



add esi, 4 
mov ebx, HEIGHT[esi]
mov CASE, ebx ;CASE�� ���� ���� ���� ������ �����Ѵ�.
add esi, 4 

pop ecx 
LOOP L1

LAST:
exit

main ENDP
END main