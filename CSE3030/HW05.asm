TITLE listsum-text
;author:김유이
;input: 정수, 빈칸, +, -로 구성된 문자열  output: 문자열의 정수 값들의 합
;function: 문자열을 입력받고 문자열에서 정수를 추출하는 함수를 만들고, 정수 값들의 합을 출력한다.

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
;입력문구를 출력하고 문자열을 입력받는다.
mov edx, OFFSET prompts
call WriteString
call Crlf

;문자열을 입력받는다.
mov edx, OFFSET inBuffer
mov ecx, BUF_SIZE-1
call ReadString

;eax에 반환된 문자열의 크기를 inBufferN에 저장한다.
mov inBufferN, eax
or eax, eax  ;문자열의 크기가 0이면 L2로 가서 프로그램을 종료한다.
jz L2

mov edi, OFFSET intArray
call StrToInt

mov intArrayN, esi   
or esi, esi  ;문자열에서 추출한 정수의 개수가 0이면 L1으로 가서 다시 문자열을 입력받는다.
jz L1

xor eax, eax  ;eax에 정수 값들의 합을 저장하고 위해 0으로 초기화한다.
mov ecx, esi  ;정수의 개수만큼 LOOP L3를 반복한다.
mov edx, OFFSET intArray ;정수 배열의 offset을 edx에 저장한다.
L3:
add eax, [edx]  ;정수를 하나씩 eax에 더한다.
add edx, 4
LOOP L3

;만약 정수값들의 합이 0보다 작다면 WriteInt를 호출해 -부호까지 출력한다.
; 그렇지 않다면, WriteDec을 이용해 출력한다.

cmp eax, 0 
jl L4

call WriteDec
call Crlf
jmp L1

L4:
call WriteInt
call Crlf
jmp L1


;종료문구를 출력하고 프로그램을 종료한다.
L2:
mov edx, OFFSET prompte
call WriteString
exit
main ENDP

;author: 김유이
;input: 문자열, 정수를 담을 문자열, 문자열의 크기 output: 문자열에 추출된 정수의 배열
;function: 문자열을 parsing하여 정수를 추출하고, 배열 intArray에 정수를 할당하여 반환한다.

StrToInt PROC
mov ebx, 0 ; 정수로 변환할 문자열의 크기
mov esi, 0 ;정수 배열의 개수

mov ecx, eax ;입력받은 문자열의 길이만큼 LOOP S1을 반복한다. 
S1:
;문자가 공백인 경우에 S2로 점프한다.
mov al, [edx]
cmp al, 20h
jz S2
;문자가 공백이 아닌 경우, 변환할 문자열의 길이를 증가시킨다.
inc ebx
jmp S3

S2:
;문자가 공백이고, 이전에도 계속 공백이었던 경우에는 S3로 점프한다.
or ebx, 0
jz S3

;문자가 공백이지만, 이전에 숫자가 나왔던 경우에는 정수로 변환한다.
push edx
push ecx
mov ecx, ebx
sub edx, ebx
call ParseInteger32
pop ecx
pop edx

;변환한 정수를 intArray에 할당한다.
mov [edi+esi*4], eax 
inc esi
;ebx를 0으로 초기화한다.
xor ebx, ebx

S3:
inc edx
LOOP S1

;문자열의 마지막에 숫자가 있는지 공백이었는지를 구분한다.
or ebx, ebx ;공백이라면 S4로 점프한다.
jz S4

;문자열의 마지막 숫자를 정수로 변환하여 intArray에 저장한다.
mov ecx, ebx
sub edx, ebx
call ParseInteger32
mov [edi+esi*4],eax
inc esi

S4:
ret
StrToInt ENDP
END main