AM_CFLAGS = -Wall -Werror -O3 -g -fexceptions

lib_LTLIBRARIES = libnumC.la
libnumC_la_SOURCES = Matrix_gsl.C \
										 Matrix.C \
										 Stats.C \
										 Utils.C
libnumC_la_LIBADD = -lgsl -lgslcblas -lm

otherincludedir =$(includedir)/numC
otherinclude_HEADERS = Matrix_gsl.h \
											 Matrix.h \
											 Stats.h \
											 Utils.h
