#!/usr/bin/make -f
include ../i-nex.mk 
make: make-binary

make-binary: compile-i-nex-edid \
	     compile-i-nex-cpuid
	
compile-i-nex-edid:
	@echo -e '$(OK_COLOR)Compile i-nex-edid $(OK_STRING)$(NO_COLOR)'
	$(CC) -o i-nex-edid i-nex-edid.c $(CFLAGS) $(additional_confflags)
	
install: install-set-executables install-bin
install-set-executables: set-executable-i-nex-edid
			 
set-executable-i-nex-edid:
	chmod +x i-nex-edid

install-bin: install-bin-i-nex-edid \
	     install-bin-i-nex-dimms
	     
	     

install-bin-i-nex-edid:
	test -d $(DESTDIR)$(bindir) || mkdir $(DESTDIR)$(bindir)
	$(INSTALL) 0755 i-nex-edid $(DESTDIR)$(bindir)
install-bin-i-nex-dimms:
	test -d $(DESTDIR)$(bindir) || mkdir $(DESTDIR)$(bindir)
	$(INSTALL) 0755 i-nex-dimms $(DESTDIR)$(bindir)
clean:
	@echo -e '$(ACTION_COLOR)Clean JSON$(NO_COLOR)'
	$(RM_COM) $(RMFILE_OPT) i-nex-edid
