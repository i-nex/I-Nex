#!/usr/bin/make -f
include ../i-nex.mk 

make-binary:
	@echo -e '\033[1;32mCompile i-nex-edid\033[0m'
	$(CC) -o i-nex-edid i-nex-edid.c $(CFLAGS) $(additional_confflags)
	@echo -e '\033[1;32mCompile i-nex-cpuid\033[0m'
	$(CC) -o i-nex-cpuid i-nex-cpuid.c -static $(CC_OPTS_LIBCPUID) $(additional_confflags)
	@echo -e '\033[1;32mCompile i-nex-usage\033[0m'
	$(CC) -o i-nex-usage i-nex-usage.c -static $(CC_OPTS_LIBPROCPS) $(additional_confflags)
	@echo -e '\033[1;32mCompile i-nex-cpusage\033[0m'
	$(CC) -o i-nex-cpusage i-nex-cpusage.c $(additional_confflags)
	@echo -e '\033[1;32mCompile i-nex-glinfo\033[0m'
	$(CC) -o i-nex-glinfo i-nex-glinfo.c $(libx11) $(libgl) $(libxext) $(additional_confflags)
	@echo -e '\033[1;32mCompile i-nex-uname\033[0m'
	$(CC) -o i-nex-uname i-nex-uname.c $(additional_confflags)
	
install-bin:

	mkdir -p $(DESTDIR)$(bindir)
	chmod +x i-nex-edid
	chmod +x i-nex-cpuid
	chmod +x i-nex-usage
	chmod +x i-nex-cpusage
	chmod +x i-nex-glinfo
	chmod +x i-nex-uname
	$(INSTALL) 0755 i-nex-edid $(DESTDIR)$(bindir)
	$(INSTALL) 0755 i-nex-cpuid $(DESTDIR)$(bindir)
	$(INSTALL) 0755 i-nex-usage $(DESTDIR)$(bindir)
	$(INSTALL) 0755 i-nex-cpusage $(DESTDIR)$(bindir)
	$(INSTALL) 0755 i-nex-glinfo $(DESTDIR)$(bindir)
	$(INSTALL) 0755 i-nex-uname $(DESTDIR)$(bindir)
clean:
	$(RM_COM) $(RMFILE_OPT) i-nex-edid
	$(RM_COM) $(RMFILE_OPT) i-nex-cpuid
	$(RM_COM) $(RMFILE_OPT) i-nex-usage
	$(RM_COM) $(RMFILE_OPT) i-nex-cpusage
	$(RM_COM) $(RMFILE_OPT) i-nex-glinfo
	$(RM_COM) $(RMFILE_OPT) i-nex-uname
	
install: make-binary install-bin