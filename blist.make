# blist.make
#
# ident "%Z%  $RCSfile$  v$Revision$  $Date$__ - njt"
#
include APPLNAME
# Note: Sets APPL variable
#
NJT= /home2/njt
INSTALLDIR= $(NJT)/bin
#
LIBDIR= $(NJT)/lib
LIBINCL= $(NJT)/include
LIBCPPINCL= $(NJT)/cpp/include
#
LPCMD=/devel/njtbin/njtlp
SOURCES= blist.cc
OBJECTS= blist.o
INCLDIRS= -I../include -I$(LIBINCL) -I$(LIBCPPINCL) -I/usr/include/CC
LIBRARIES= $(LIBDIR)/libnjtcpp.a $(LIBDIR)/libnjt.a -lc -lgen
CFLAGS=-c -g -w2
CPPFLAGS=
#
#	Pseudo commands
#	===============
#
Build:		$(APPL)
Clean:
	@echo Cleaning intermediate files
	/usr/bin/rm -f ,Build*
	/usr/bin/rm -rf CompileErrs._d Pmak._d
	/usr/bin/rm -f *._* *_.* Errors Errors.misc core
	/usr/bin/rm -f *.lis
	/usr/bin/rm -f *.o
	/usr/bin/rm -f $(APPL)
Print:
	@echo Printing source files
	$(LPCMD) $(SOURCES) $(PWD)/$(APPL).make $(PWD)/[Mm]akefile
Install:        $(APPL)
	echo Installing $(APPL) into $(INSTALLDIR)
	chmod u+w   $(INSTALLDIR)/$(APPL)
	cp -p $(APPL) $(INSTALLDIR)
	chmod ugo-w $(INSTALLDIR)/$(APPL)
	chmod ugo+x $(INSTALLDIR)/$(APPL)
RunTests:	$(APPL)
	ksh -c "cd Tests ; RunTests"
#
#	Rules
#	=====
#
.cc.o:
		CC  $(CFLAGS) $(CPPFLAGS) $(INCLDIRS)  $*.cc
.c.o:
		cc  $(CFLAGS) $(INCLDIRS)  $*.c
#
#	blist: Bulk list text file contents
#	===================================
#
$(APPL): 	$(OBJECTS) $(APPL).make
		CC -o $(APPL)  $(OBJECTS) $(LIBRARIES) 
#
#	Dependancies
#	============
#
blist.o:	$(LIBCPPINCL)/File.h \
		$(LIBCPPINCL)/TextBox.h \
		$(LIBCPPINCL)/utildbug.h

# EOF #
