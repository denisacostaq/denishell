#SUBDIRS = src po
SUBDIRS = src
EXTRA_DIST = README THANKS TODO HACKING MAINTAINERS doc .gitignore
CLEANFILES = *~

html-doc:
	cd doc ; \
	doxygen Doxfile ; \
	cd ../
	
license:
	if test -f /usr/share/common-licenses/GPL-2 ; then \
		echo Updating license from /usr/share/common-licenses/GPL-2 ; \
		cat /usr/share/common-licenses/GPL-2 > COPYING ; \
	else \
		echo "You need run apt-get install base-files" ; \
	fi
	
details:
	@echo "Building from:"
	@echo "build_cpu = $(build_cpu), build_os = $(build_os), build_vendor = $(build_vendor)"
	@echo "To:"
	@echo "host_cpu = $(host_cpu), host_os = $(host_os), host_vendor = $(host_vendor)"
