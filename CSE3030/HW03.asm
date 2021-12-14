TITLE de-cipher text
;author:������
;input:ī�̻縣 ��ȣȭ�� ���ڿ� output: ī�̻縣 ��ȣȭ�� ���ڿ�
;function: ī�̻縣 ��ȣȭ�� ���ڿ��� ��ȣȭ�Ͽ� ���Ͽ� ����ϴ� ����� �����Ѵ�

INCLUDE Irvine32.inc
INCLUDE CSE3030_PHW03.inc

.data
filename BYTE "0s190018_out.txt", 0 ;����� ����� ����
filehandle DWORD ?
;�ε����� key�� 10���� ���� ���� ū ��츦 �� loop������ ��ȣȭ�ϱ� ���ؼ� A-Z���� �� �� �ִ� ���ڿ��� �����. 
list BYTE "ABCDEFGHIJKLMNOPQRSTUVWXYZABCDEFGHIJKLMNOPQRSTUVWXYZ", 0 
BUFSIZE=2
BUFFER BYTE 0Dh,0Ah,0 ;buffer�� ���๮�� �����ϱ�

.code
main PROC
mov edx, OFFSET filename 
call CreateOutputFile  ;����� ������ �����.
mov filehandle, eax

mov esi, 0
mov ecx, Num_Str ;Num_Str��ŭ ù ��° loop�� �ݺ��Ѵ�. 

L1:
 pop edx
 mov edx, OFFSET Cipher_Str ;edx�� ���ڿ��� base address�� �����Ͽ� ���߿� ���� ��½ÿ� ����Ѵ�. 
 add edx, esi
 push edx
 push ecx  ;���ڿ��� ���� 10��ŭ �ι�° loop�� �ݺ��ϱ� ���� �ռ� ecx�� stack�� �����Ѵ�.
 mov ecx, 10 ;���ڿ� ���� 10��ŭ �� ��° loop�� �ݺ��Ѵ�.

L2:
mov al, Cipher_Str[esi] ;��ȣȭ�� ���ڿ����� ���� �ϳ��� al�� �����Ѵ�.
movzx edi, al
sub edi, 'A' ;'A'�� �ƽ�Ű�ڵ� ����ŭ�� ���� list���� �ش� ������ �ε����� ���� �� �ִ�.
sub edi, 10 ;��ȣȭ�ϱ� ���ؼ� key���� 10�� ����
add edi, 26 ; ���� list�� ����, A-Z������ ���̸� �����ش�.
mov al, list[edi] ;list�� ���� index�� �����Ͽ� al�� ��ȣȭ�� ���ڸ� �����Ѵ�.
mov Cipher_Str[esi],al ;Cipher_Str�� ��ȣȭ�� ���ڸ� �����Ͽ� ��ȣȭ�� ���ڿ��� �ٲ۴�.

inc esi ;���� �ε����� �Ѿ��.
LOOP L2

;edx�� ����Ǿ� �ִ� ���ڿ��� �� �� ����Ѵ�. 
pop edx
mov eax,filehandle
mov ecx, sizeof Cipher_Str
call WriteToFile

;���ڿ� �� �� ��� �Ŀ� ���๮�ڸ� ����Ѵ�.
mov eax, filehandle
mov edx, OFFSET BUFFER
mov ecx, BUFSIZE
call WriteToFile

;ù ��° loop�� ���ư���. 
pop ecx
inc esi 
LOOP L1

mov eax, filehandle
call CloseFile
exit

main ENDP
END main