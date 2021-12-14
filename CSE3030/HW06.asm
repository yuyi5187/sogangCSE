TITLE redirection
;author: 김유이
;input: 입출력 핸들과 숫자와 문자로 구성된 문자열 output: 숫자만큼 문자가 반복된 문자열
;function: 입출력핸들을 입력받아 입력된 핸들로 숫자만큼 반복된 문자열을 출력한다.
BUF_SIZE EQU 256 

INCLUDE Irvine32.inc

.data 
stdinHandle HANDLE ?
stdoutHandle HANDLE ?
inBuffer BYTE BUF_SIZE DUP(?)
inBufferN DWORD ?  
outBuffer BYTE BUF_SIZE DUP(?)
outWRITTEN DWORD ?
CRLF_ BYTE 0dh, 0ah ;개행문자 선언

.code
main PROC

;표준입출력 handle 불러와서 각각 stdinHandle과 stdoutHandle에 저장한다.
INVOKE GetStdHandle, STD_INPUT_HANDLE
mov stdinHandle, eax
INVOKE GetStdHandle, STD_OUTPUT_HANDLE
mov stdoutHandle, eax

L1: 
mov eax, stdinHandle
mov edx, OFFSET inBuffer
push edx
call Read_a_Line ;handle로부터 한줄씩 입력받는다.
pop edx ;문자열의 시작주소를 다시 불러온다


mov bl, [edx] 
cmp bl, 20h ;만약 빈칸이 입력된 경우, 프로그램을 종료한다.
jz ProgramEnd
or bl, bl ;아무것도 입력되지 않은 경우, 빈줄이 입력된 경우에 프로그램을 종료한다.
jz ProgramEnd

mov inBufferN, ecx ;문자열의 길이를 inBufferN에 저장한다.
mov edi, OFFSET outBuffer ;edi에 출력 문자열의 시작주소를 저장한다.

;문자열의 첫 문자인 숫자를 정수로 변환한다.
mov ecx, 1 
call ParseInteger32

sub inBufferN, 2
mov ecx, inBufferN  ;문자열 길이만큼 toString을 반복호출한다.
call toString

;outBuffer에 저장되어 있는 문자열을 출력한다.
mov edx, OFFSET outBuffer
INVOKE WriteFile, stdoutHandle, edx, esi, OFFSET outWRITTEN, 0
;개행문자를 출력한다. 
pushad
INVOKE WriteFile, stdoutHandle, OFFSET CRLF_, 2, OFFSET outWRITTEN, 0
popad
;L1으로 돌아가 다시 문자열을 입력받는다.
jmp L1

ProgramEnd:
exit
main ENDP

; argument: ecx, edi, eax
; return: esi
; function: output 문자열의 주소와 반복할 숫자, input 문자을의 길이를 입력받아서 반복숫자만큼 문자열의 문자가 반복된 문자열의 크기를 반환한다.

toString PROC
mov esi, 0 ;esi에는 함수 실행 이후 문자열의 길이를 저장한다.
add edx, 2 ;문자열의 시작위치로 이동한다.

L2:
push ecx
mov bl, [edx]
mov ecx, eax ;숫자만큼 문자열의 문자 하나씩 반복하여 edi가 가리키는 문자열에 저장한다.

L3:
mov [edi], bl
inc edi
inc esi
LOOP L3

pop ecx
inc edx
LOOP L2

ret
toString ENDP


Read_a_Line PROC

.data
Single_Buf_ BYTE ?
Byte_Read_ DWORD ?

.code

xor ecx, ecx

Read_Loop:
push eax
push ecx 
push edx

INVOKE ReadFile, EAX, OFFSET Single_Buf_,
                  1, OFFSET Byte_Read_, 0


pop edx
pop ecx
pop eax
cmp DWORD PTR Byte_Read_, 0
je Read_End

mov bl, Single_Buf_
cmp bl, 0Dh
je Read_LOOP
cmp bl, 0Ah
je Read_End

mov [edx], bl
inc edx
inc ecx
jmp Read_Loop

Read_End:
mov BYTE PTR [edx], 0
ret
Read_a_Line ENDP

END main