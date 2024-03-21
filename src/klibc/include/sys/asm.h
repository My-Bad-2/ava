#ifndef KLIBC_INCLUDE_SYS_ASM_H
#define KLIBC_INCLUDE_SYS_ASM_H

#define FUNCTION(x)    \
	.global x;         \
	.type x, STT_FUNC; \
x:
#define DATA(x)          \
	.global x;           \
	.type x, STT_OBJECT; \
x:

#define LOCAL_FUNCTION(x) \
	.type x, STT_FUNC;    \
x:
#define LOCAL_DATA(x)    \
	.type x, STT_OBJECT; \
x:

#define END_FUNCTION(x) .size x, .- x
#define END_DATA(x) .size x, .- x

#endif // KLIBC_INCLUDE_SYS_ASM_H