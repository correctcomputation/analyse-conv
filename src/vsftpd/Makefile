PROG = vsftpd
SOURCES = 	main.c utility.c prelogin.c ftpcmdio.c postlogin.c privsock.c \
		tunables.c ftpdataio.c secbuf.c ls.c \
		postprivparent.c logging.c str.c netstr.c sysstr.c strlist.c \
    banner.c filestr.c parseconf.c secutil.c \
    ascii.c oneprocess.c twoprocess.c privops.c standalone.c hash.c \
    tcpwrap.c ipaddrparse.c access.c features.c readwrite.c opts.c \
    ssl.c sslslave.c ptracesandbox.c ftppolicy.c sysutil.c sysdeputil.c \
    seccompsandbox.c
HDRS =

CFLAGS = -g -w -O0 -idirafter dummyinc
LDFLAGS = -Wl `./vsf_findlibs.sh`

RUN_OPTIONS =
OUTPUT = 
STDIN_FILENAME = /dev/stdin

PATH_TO_SRC = ../

include $(PATH_TO_SRC)Makefile.common

