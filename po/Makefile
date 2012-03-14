all: build-mo

# create mo from the po files
%.mo : %.po
	mkdir -p mo/$(subst .po,,$<)/LC_MESSAGES/
	msgfmt $< -o mo/$(subst .po,,$<)/LC_MESSAGES/pastebinit.mo

# generate all *.mo files
build-mo: $(patsubst %.po,%.mo,$(wildcard *.po))

update-po:
	pygettext -a -D ../pastebinit
