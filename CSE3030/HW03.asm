TITLE de-cipher text
;author:김유이
;input:카이사르 암호화된 문자열 output: 카이사르 복호화된 문자열
;function: 카이사르 암호화된 문자열을 복호화하여 파일에 출력하는 기능을 구현한다

INCLUDE Irvine32.inc
INCLUDE CSE3030_PHW03.inc

.data
filename BYTE "0s190018_out.txt", 0 ;결과를 출력할 파일
filehandle DWORD ?
;인덱스가 key값 10보다 작은 경우와 큰 경우를 한 loop내에서 복호화하기 위해서 A-Z까지 두 번 있는 문자열을 만든다. 
list BYTE "ABCDEFGHIJKLMNOPQRSTUVWXYZABCDEFGHIJKLMNOPQRSTUVWXYZ", 0 
BUFSIZE=2
BUFFER BYTE 0Dh,0Ah,0 ;buffer에 개행문자 저장하기

.code
main PROC
mov edx, OFFSET filename 
call CreateOutputFile  ;출력할 파일을 만든다.
mov filehandle, eax

mov esi, 0
mov ecx, Num_Str ;Num_Str만큼 첫 번째 loop를 반복한다. 

L1:
 pop edx
 mov edx, OFFSET Cipher_Str ;edx에 문자열의 base address를 저장하여 나중에 파일 출력시에 사용한다. 
 add edx, esi
 push edx
 push ecx  ;문자열의 길이 10만큼 두번째 loop를 반복하기 위해 앞선 ecx를 stack에 저장한다.
 mov ecx, 10 ;문자열 길이 10만큼 두 번째 loop를 반복한다.

L2:
mov al, Cipher_Str[esi] ;암호화된 문자열에서 문자 하나를 al에 저장한다.
movzx edi, al
sub edi, 'A' ;'A'의 아스키코드 값만큼을 빼서 list에서 해당 문자의 인덱스를 구할 수 있다.
sub edi, 10 ;복호화하기 위해서 key값인 10을 뺀다
add edi, 26 ; 원래 list의 길이, A-Z까지의 길이를 더해준다.
mov al, list[edi] ;list에 구한 index를 대입하여 al에 복호화된 문자를 저장한다.
mov Cipher_Str[esi],al ;Cipher_Str에 복호화된 문자를 저장하여 복호화된 문자열로 바꾼다.

inc esi ;다음 인덱스로 넘어간다.
LOOP L2

;edx에 저장되어 있는 문자열을 한 줄 출력한다. 
pop edx
mov eax,filehandle
mov ecx, sizeof Cipher_Str
call WriteToFile

;문자열 한 줄 출력 후에 개행문자를 출력한다.
mov eax, filehandle
mov edx, OFFSET BUFFER
mov ecx, BUFSIZE
call WriteToFile

;첫 번째 loop로 돌아간다. 
pop ecx
inc esi 
LOOP L1

mov eax, filehandle
call CloseFile
exit

main ENDP
END main