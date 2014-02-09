#!/usr/bin/make -f
include ../i-nex.mk 
make: check-static make-binary
check-static:
ifeq ($(STATIC),true)
	@echo -e '$(WARN_COLOR)Compile Static $(WARN_STRING)$(NO_COLOR)'
else
	@echo -e '$(OK_COLOR)Compile Not Static $(OK_STRING)$(NO_COLOR)'
endif

make-binary:

	@echo -e '$(OK_COLOR)Compile i-nex-edid $(OK_STRING)$(NO_COLOR)'
	$(CC) -o i-nex-edid i-nex-edid.c $(CFLAGS) $(additional_confflags)
	@echo -e '$(OK_COLOR)Compile i-nex-cpuid $(OK_STRING)$(NO_COLOR)'
	$(CC) -o i-nex-cpuid i-nex-cpuid.c $(YESNO_LINK) $(CC_OPTS_LIBCPUID) $(additional_confflags)
	@echo -e '$(OK_COLOR)Compile i-nex-usage $(OK_STRING)$(NO_COLOR)'
	$(CC) -o i-nex-usage i-nex-usage.c $(YESNO_LINK) $(CC_OPTS_LIBPROCPS) $(additional_confflags)
	@echo -e '$(OK_COLOR)Compile i-nex-cpusage $(OK_STRING)$(NO_COLOR)'
	$(CC) -o i-nex-cpusage i-nex-cpusage.c $(additional_confflags)
	@echo -e '$(OK_COLOR)Compile i-nex-glinfo $(OK_STRING)$(NO_COLOR)'
	$(CC) -o i-nex-glinfo i-nex-glinfo.c $(libx11) $(libgl) $(libxext) $(additional_confflags)
	@echo -e '$(OK_COLOR)Compile i-nex-uname $(OK_STRING)$(NO_COLOR)'
	$(CC) -o i-nex-uname i-nex-uname.c $(additional_confflags)
	
install: install-set-executables install-bin
install-set-executables:

	chmod +x i-nex-edid
	chmod +x i-nex-cpuid
	chmod +x i-nex-usage
	chmod +x i-nex-cpusage
	chmod +x i-nex-glinfo
	chmod +x i-nex-uname

install-bin:
	mkdir -p $(DESTDIR)$(bindir)
	$(INSTALL) 0755 i-nex-edid $(DESTDIR)$(bindir)
	$(INSTALL) 0755 i-nex-cpuid $(DESTDIR)$(bindir)
	$(INSTALL) 0755 i-nex-usage $(DESTDIR)$(bindir)
	$(INSTALL) 0755 i-nex-cpusage $(DESTDIR)$(bindir)
	$(INSTALL) 0755 i-nex-glinfo $(DESTDIR)$(bindir)
	$(INSTALL) 0755 i-nex-uname $(DESTDIR)$(bindir)
clean:
	@echo -e '$(ACTION_COLOR)Clean JSON$(NO_COLOR)'
	$(RM_COM) $(RMFILE_OPT) i-nex-edid
	$(RM_COM) $(RMFILE_OPT) i-nex-cpuid
	$(RM_COM) $(RMFILE_OPT) i-nex-usage
	$(RM_COM) $(RMFILE_OPT) i-nex-cpusage
	$(RM_COM) $(RMFILE_OPT) i-nex-glinfo
	$(RM_COM) $(RMFILE_OPT) i-nex-uname