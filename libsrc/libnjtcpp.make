# libnjtcpp.make
#
# ident "%Z%  $RCSfile$  v$Revision$  $Date$__ - njt"
#
include LIBNAME
# Note: Sets LIB variable
#
NJT= /home4/njt
#
LIBDIR= $(NJT)/lib
LIBINCL= $(NJT)/include
LIBCPPINCL= $(NJT)/cpp/include
#
HEADERS= File.h FileName.h TextBox.h utildbug.h Boolean.h \
	sstring.h list.h dobject.h
SOURCES= File.cc FileName.cc TextBox.cc utildbug.cc \
	sstring.cc list.cc dobject.cc
OBJECTS= File.o FileName.o TextBox.o utildbug.o \
	sstring.o list.o dobject.o
LPCMD=/devel/njtbin/njtlp
INCLDIRS= -I. -I$(LIBINCL) -I$(LIBCPPINCL) -I/usr/include/CC
NO_LINK_FLAG=-c
CFLAGS=-g -w2 -DNEXCEPTIONS
CPPFLAGS=
#
#	Pseudo commands
#	===============
#
Build:		$(LIB).a
Clean:
	@echo Cleaning intermediate files
	/usr/bin/rm -f ,Build*
	/usr/bin/rm -rf CompileErrs._d Pmak._d
	/usr/bin/rm -f *._* *_.* Errors Errors.misc core
	/usr/bin/rm -f *.lis
	/usr/bin/rm -f *.o
	/usr/bin/rm -f $(LIB).a
Print:
	@echo Printing source files
	$(LPCMD) $(SOURCES) $(PWD)/$(LIB).make $(PWD)/[Mm]akefile
Install:        $(LIB).a
	@echo Installing $(LIB) into $(LIBDIR)
	chmod u+w   $(LIBDIR)/$(LIB).a
	cp -p $(LIB).a $(LIBDIR)
	chmod ugo-w $(LIBDIR)/$(LIB).a
	chmod ugo+x $(LIBDIR)/$(LIB).a
	@echo Installing header files into $(LIBCPPINCL)
	chmod u+w   $(LIBCPPINCL)/*.h
	cp -p *.h $(LIBCPPINCL)
	chmod ugo-w $(LIBCPPINCL)/*.h
	chmod ugo+r $(LIBCPPINCL)/*.h
RunTests:		
	echo "Nothing to do yet"
#
#	Rules
#	=====
#
.cc.o:
		CC  $(NO_LINK_FLAG) $(CFLAGS) $(CPPFLAGS) $(INCLDIRS)  $*.cc
.cc.a:
		CC  $(NO_LINK_FLAG) $(CFLAGS) $(CPPFLAGS) $(INCLDIRS)  $*.cc
		$(AR) $(ARFLAGS) $@ $*.o
		/usr/bin/rm -f $*.o
.c.o:
		cc  $(NO_LINK_FLAG) $(CFLAGS) $(INCLDIRS)  $*.c
.c.a:
		cc  $(NO_LINK_FLAG) $(CFLAGS) $(INCLDIRS)  $*.c
		$(AR) $(ARFLAGS) $@ $*.o
		/usr/bin/rm -f $*.o
#
#	Library build
#	=============
#
$(LIB).a:	$(SOURCES)
		CC  $(NO_LINK_FLAG) $(CFLAGS) $(CPPFLAGS) $(INCLDIRS)  $?
		$(AR) $(ARFLAGS) $@ *.o
		/usr/bin/rm -f *.o
		@echo "Library $(LIB) is now up to date"
#
#	Dependancies
#	============
#
File.o:		File.h Boolean.h FileName.h sstring.h utildbug.h \
		$(LIBCPPINCL)/filter.h $(LIBINCL)/fileutil.h
FileName.o:	FileName.h Boolean.h sstring.h $(LIBINCL)/fileutil.h
TextBox.o:	TextBox.h
utildbug.o:	utildbug.h Boolean.h
sstring.o:	sstring.h
list.o:		list.h
dobject.o:	dobject.h

# EOF #
