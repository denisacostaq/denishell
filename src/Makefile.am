CLEANFILES = *~

AM_CFLAGS = -Wall -std=c99 -Werror \
        -DTRACE_TOKENS \
        -DPACKAGE_LOCALE_DIR=\""$(datadir)/locale"\"

#i18n
AM_CPPFLAGS =

bin_PROGRAMS = deni-sh
deni_sh_SOURCES = \
    deni-sh_i18n.h \
    main.c \
    lexer.h \
    lexer.c \
    sintactic.h \
    sintactic.c \
    sintactic_cat.h \
    sintactic_cat.c \
    sintactic_ls.h \
    sintactic_ls.c \
    runtime.h \
    runtime.c
