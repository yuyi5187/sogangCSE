TITLE uphils-text
;author:김유이
;input:테스트 케이스 개수, 오르막길 고도 개수, 오르막길 고도 output: 가장 경사가 심한 오르막길 고도차이
;function:각 테스트 케이스마다 가장 경사가 심한 오르막길 고도의 차이를 출력한다
INCLUDE Irvine32.inc
INCLUDE CSE3030_PHW04.inc

.data
BUFFER BYTE 0Dh,0Ah,0 ;개행문자

.code
main PROC

mov esi, 0
mov ecx, TN ;테스트 케이스 개수만큼 첫 loop를 반복한다. 
or ecx, ecx ;테스트 케이스 개수가 0인 경우 종료
jz LAST

L1:
push ecx
dec CASE ; 마지막 고도의 경우, 비교할 다음 고도가 없으므로 고도 개수-1 


mov eax, 0 ;오르막길 최대 고도 차이를 저장한다.(max)
mov ebx, 0 ;각 오르막길 마다 고도 차이의 합을 저장한다.(sum)
mov ecx, CASE ;CASE 만큼 두번째 loop를 반복한다. 
or ecx, ecx
jz NEXT3


L2:

mov edi, HEIGHT[esi]
add esi, 4
mov edx, HEIGHT[esi]

cmp edi, edx ;해당 고도와 다음 고도를 비교하여 오르막길인지 판단한다
jae NEXT ;만약 오르막길이 아니면 NEXT로 간다. 
    sub edx, edi
    add ebx, edx ;오르막길인 경우에는 고도 차이를 구해서 ebx(sum)에 더해준다.
    jmp NEXT2 

NEXT:
cmp eax, ebx 
jae NEXT1 ;만약 현재 max보다 sum이 크면 max에 sum 할당한다.
    mov  eax, ebx
    jmp NEXT1
NEXT1:
mov ebx, 0 ;다음 오르막길의 고도 차이를 계산하기 위해 ebx(sum)을 0으로 초기화한다.

NEXT2:
LOOP L2

cmp eax, ebx ;마지막 오르막길의 고도차이를 구한 경우, 기존의 max와 비교하여 더 크면 max에 할당해준다 
jae NEXT3
  mov eax, ebx
  jmp NEXT3

NEXT3:
call WriteDec ;가장 고도차이가 큰 오르막길을 출력한다.
mov edx, OFFSET BUFFER 
call WriteString ;개행문자를 출력한다.



add esi, 4 
mov ebx, HEIGHT[esi]
mov CASE, ebx ;CASE에 다음 등산로 고도의 개수를 저장한다.
add esi, 4 

pop ecx 
LOOP L1

LAST:
exit

main ENDP
END main