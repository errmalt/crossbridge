#	from @(#)Makefile.inc	8.1 (Berkeley) 6/4/93
# $FreeBSD: src/lib/libc/quad/Makefile.inc,v 1.11.10.1.6.1 2010/12/21 17:09:25 kensmith Exp $

# Quad support, if needed
.PATH: ${.CURDIR}/${MACHINE_ARCH}/quad ${.CURDIR}/quad

.if ${MACHINE_ARCH} == "i386"

SRCS+=	cmpdi2.c divdi3.c moddi3.c qdivrem.c ucmpdi2.c udivdi3.c umoddi3.c

.elif ${MACHINE_ARCH} == "avm2"

SRCS+=  adddi3.c anddi3.c cmpdi2.c floatunsdidf.c iordi3.c lshldi3.c qdivrem.c \
        subdi3.c xordi3.c

.else

SRCS+=	adddi3.c anddi3.c ashldi3.c ashrdi3.c cmpdi2.c divdi3.c fixdfdi.c \
	fixsfdi.c fixunsdfdi.c fixunssfdi.c floatdidf.c floatdisf.c \
	floatunsdidf.c iordi3.c lshldi3.c lshrdi3.c moddi3.c muldi3.c \
	negdi2.c notdi2.c qdivrem.c subdi3.c ucmpdi2.c udivdi3.c umoddi3.c \
	xordi3.c

.endif

SYM_MAPS+=${.CURDIR}/quad/Symbol.map
