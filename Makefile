SUBDIRS := hello_world ex6 ex7 hw1 hw2
TARGETS := all clean

default: all

$(TARGETS): subdirs
	@echo making top $@

subdirs: $(SUBDIRS)

$(SUBDIRS):
	$(MAKE) -C $@ $(filter $(TARGETS),$(MAKECMDGOALS))

.PHONY: subdirs $(TARGETS) $(SUBDIRS)

%::
	@echo making top $@
