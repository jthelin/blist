# njt Standard Makefile
# =====================
#
include APPLNAME
# The current directory should contain a file called APPLNAME
# with the line:
#   APPL=<app>
# where <app> is the name of this application.
# The file <app>.make will be used to drive the application specific
#  portions of the build
#
# Pseudo-commands
#
Local:		do_build
Instal:		do_install
Install:	do_install
Build:		do_build
ReBuild:	do_tidy do_build
Lint:		do_lint_check
Clean:		do_tidy
Print:		print_src
Tests:		run_tests
RunTests:	run_tests
#
# Actions
#
do_install:	
	$(MAKE) -f $(APPL).make Install
do_build:	
	$(MAKE) -f $(APPL).make Build
do_tidy:
	$(MAKE) -f $(APPL).make Clean
print_src:
	$(MAKE) -f $(APPL).make Print
do_lint_check:
	$(MAKE) -f $(APPL).make Lint
run_tests:
	$(MAKE) -f $(APPL).make RunTests
