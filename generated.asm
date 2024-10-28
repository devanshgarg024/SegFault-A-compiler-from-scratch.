section .data
  printf_format: db '%d', 10, 0
extern printf
global main
section .text
main:
  push 0
  push 0
  push 0
  push 1
loop0:
  push QWORD [rsp + 0]
  pop rax
  push rax
  mov rbx, 100
  push rbx
  pop rbx
  pop rax
  cmp rax, rbx
  je label0
  pop rax
  mov QWORD [rsp + 8], rax
  push QWORD [rsp + 8]
  pop rax
  mov QWORD [rsp + 18446744073709551608], rax
  push QWORD [rsp + 18446744073709551608]
  push QWORD [rsp + 0]
  pop rax
  push rax
  pop rax
  push QWORD [rsp + 8]
  pop rbx
  add rax, rbx
  push rax
  pop rax
  mov QWORD [rsp + 18446744073709551600], rax
  push QWORD [rsp + 18446744073709551600]
  push QWORD [rsp + 18446744073709551600]
  pop rax
  push rax
  pop rax
  mov rbx, 1
  add rax, rbx
  push rax
  pop rax
  mov QWORD [rsp + 18446744073709551592], rax
  push QWORD [rsp + 18446744073709551592]
 jmp loop0
label0:
  pop rsi
  pop rsi
  pop rsi
