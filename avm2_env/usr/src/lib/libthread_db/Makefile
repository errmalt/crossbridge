# $FreeBSD: src/lib/libthread_db/Makefile,v 1.15.2.1.6.1 2010/12/21 17:09:25 kensmith Exp $

.PATH:	${.CURDIR}/arch/${MACHINE_ARCH}

LIB=	thread_db
SHLIB_MAJOR= 3
SRCS=	thread_db.c
SRCS+=	libpthread_md.c
SRCS+=	libpthread_db.c
SRCS+=	libthr_db.c
INCS=	thread_db.h
WARNS?= 6

CFLAGS+=-I. -I${.CURDIR}
SYM_MAPS+=${.CURDIR}/Symbol.map

SYMBOL_MAPS=${SYM_MAPS}
VERSION_DEF=${.CURDIR}/../libc/Versions.def

.include <bsd.lib.mk>
