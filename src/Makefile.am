EXTRA_DIST = $(PACKAGE)

all:
	@(if test "$(COMPONENT_build)" = "1"; then \
	 echo "Building $(PACKAGE) component..."; \
	else \
	 echo "Compiling $(PACKAGE) project..."; \
	fi)
	@(cd $(srcdir)/$(PACKAGE); \
	$(GAMBAS_path)/gbc3 -e -a -g -p -m -x ; \
	$(GAMBAS_path)/gba3)

install-exec-local:
	@(cd $(srcdir)/$(PACKAGE); \
	if test "$(COMPONENT_build)" = "1"; then \
	 echo "Installing $(PACKAGE).gambas in $(GBLIBRARY_path)"; \
	 $(INSTALL) -d $(DESTDIR)/$(GBLIBRARY_path); \
	 $(INSTALL) $(PACKAGE).gambas $(DESTDIR)/$(GBLIBRARY_path); \
	 echo "Installing $(PACKAGE).component in $(GBLIBRARY_path)"; \
	 $(INSTALL) -d $(DESTDIR)/$(GBLIBRARY_path); \
	 $(INSTALL) .component $(DESTDIR)/$(GBLIBRARY_path)/$(PACKAGE).component; \
	 chmod a-x $(DESTDIR)/$(GBLIBRARY_path)/$(PACKAGE).component; \
	 echo "Installing $(PACKAGE).info in $(GBINFO_path)"; \
	 $(INSTALL) -d .info $(DESTDIR)/$(GBINFO_path); \
	 $(INSTALL) .info $(DESTDIR)/$(GBINFO_path)/$(PACKAGE).info; \
	 chmod a-x $(DESTDIR)/$(GBINFO_path)/$(PACKAGE).info; \
	 echo "Installing $(PACKAGE).list in $(GBINFO_path)"; \
	 $(INSTALL) .list $(DESTDIR)/$(GBINFO_path)/$(PACKAGE).list; \
	 chmod a-x $(DESTDIR)/$(GBINFO_path)/$(PACKAGE).list; \
	 if test -d .hidden/control; then \
	  echo "Installing controls in $(GBCONTROL_path)"; \
	  $(INSTALL) -d $(DESTDIR)/$(GBCONTROL_path)/$(PACKAGE); \
	  $(INSTALL) .hidden/control/*.png $(DESTDIR)/$(GBCONTROL_path)/$(PACKAGE); \
	  chmod a-x $(DESTDIR)/$(GBCONTROL_path)/$(PACKAGE)/*.png; \
	 fi \
	else \
	 echo "Installing $(PACKAGE).gambas file in $(bindir)..."; \
	 $(INSTALL) -d $(DESTDIR)$(bindir); \
	 $(INSTALL) $(PACKAGE).gambas $(DESTDIR)$(bindir); \
	fi)

uninstall-local:
	@(if test "$(COMPONENT_build)" = "1"; then \
	 echo "Removing $(PACKAGE) component..."; \
	 rm -f $(DESTDIR)/$(GBLIBRARY_path)/$(PACKAGE).gambas; \
	 rm -f $(DESTDIR)/$(GBLIBRARY_path)/$(PACKAGE).component; \
	 rm -f $(DESTDIR)/$(GBINFO_path)/$(PACKAGE).info; \
	 rm -f $(DESTDIR)/$(GBINFO_path)/$(PACKAGE).list; \
	 rm -rf $(DESTDIR)/$(GBCONTROL_path)/$(PACKAGE); \
	else \
	 echo "Removing $(PACKAGE).gambas file..."; \
	 rm -f $(DESTDIR)$(bindir)/$(PACKAGE).gambas; \
	fi)

dist-hook:
	@(cd $(distdir)/$(PACKAGES); \
	rm -rf `find . -name ".gambas" -o -name ".lock" -o -name ".xvpics" -o -name "*~" -o -name "*.out"  -o -name "*.pot" -o -name "*.gambas" -o -name "core.*" -o -name ".kdbg*" -o -name ".svn"`;)
