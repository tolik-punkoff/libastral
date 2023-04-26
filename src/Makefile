#
# ------------------------------------------------------------------------------
# "THE MODIFIED BEER-WARE LICENSE" (Revision 1):
# <zmey20000@yahoo.com> wrote this file. As long as you retain this notice you
# can do whatever you want with this stuff. If we meet some day, and you think
# this stuff is worth it, you can buy me a beer in return Mikhail E. Zakharov
# ------------------------------------------------------------------------------

# Don't forget to export LD_LIBRARY_PATH=/usr

CC =	gcc
PREFIX = /usr

all:	obj lib tst

obj:
	${CC} -fPIC -g -c -Wall libastral.c

lib:
	${CC} -shared -o libastral.so libastral.c

tst: 
	${CC} -o astral_test astral_test.c libastral.so

install:
	install -s libastral.so ${PREFIX}/lib/
	install -s astral_test ${PREFIX}/bin/
clean:
	rm *.so *.o astral_test

