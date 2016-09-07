#!/usr/bin/make -f
include ../i-nex.mk 
make: check-static make-binary
check-static:
ifeq ($(STATIC),true)
	@echo -e '$(WARN_COLOR)Compile Static $(WARN_STRING)$(NO_COLOR)'
else
	@echo -e '$(OK_COLOR)Compile Not Static $(OK_STRING)$(NO_COLOR)'
endif

make-binary: compile-i-nex-edid \
	     compile-i-nex-cpuid
	
compile-i-nex-edid:
	@echo -e '$(OK_COLOR)Compile i-nex-edid $(OK_STRING)$(NO_COLOR)'
	$(CC) -o i-nex-edid i-nex-edid.c $(CFLAGS) $(additional_confflags)
	
compile-i-nex-cpuid:
	@echo -e '$(OK_COLOR)Compile i-nex-cpuid $(OK_STRING)$(NO_COLOR)'
	$(CC) -o i-nex-cpuid i-nex-cpuid.c $(CC_OPTS_LIBCPUID) $(additional_confflags)
	
install: install-set-executables install-bin
install-set-executables: set-executable-i-nex-edid \
			 set-executable-i-nex-cpuid
			 
set-executable-i-nex-edid:
	chmod +x i-nex-edid
set-executable-i-nex-cpuid:
	chmod +x i-nex-cpuid

install-bin: install-bin-i-nex-edid \
	     install-bin-i-nex-cpuid \
	     install-bin-i-nex-dimms
	     
	     

install-bin-i-nex-edid:
	test -d $(DESTDIR)$(bindir) || mkdir $(DESTDIR)$(bindir)
	$(INSTALL) 0755 i-nex-edid $(DESTDIR)$(bindir)
install-bin-i-nex-cpuid:
	test -d $(DESTDIR)$(bindir) || mkdir $(DESTDIR)$(bindir)
	$(INSTALL) 0755 i-nex-cpuid $(DESTDIR)$(bindir)
install-bin-i-nex-dimms:
	test -d $(DESTDIR)$(bindir) || mkdir $(DESTDIR)$(bindir)
	$(INSTALL) 0755 i-nex-dimms $(DESTDIR)$(bindir)
clean:
	@echo -e '$(ACTION_COLOR)Clean JSON$(NO_COLOR)'
	$(RM_COM) $(RMFILE_OPT) i-nex-edid
	$(RM_COM) $(RMFILE_OPT) i-nex-cpuid
	$(RM_COM) $(RMFILE_OPT) i-nex-usage
