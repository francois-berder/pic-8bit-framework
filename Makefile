ifndef CHIP
$(error "CHIP variable must be defined, e.g. CHIP=18f4550")
endif

MCU := pic$(CHIP)

include mcu/$(MCU)/Makefile.mcu

INCLUDES := -Imcu/include -Imcu/include/periph -Imcu/$(MCU)
OBJDIR := obj/$(MCU)/
OUTDIR := bin/$(MCU)/
debug: DEBUG = 1

all: release
release: framework
debug: framework

.PHONY: framework
framework: $(OUTDIR)/framework.lpp

$(OUTDIR)/framework.lpp: $(SOURCES)
	@mkdir -p $(OBJDIR)
	@mkdir -p $(OUTDIR)
	xc8 --chip=$(CHIP) --output=lpp -oframework.lpp --warn=9 $(CFLAGS) \
		--objdir=$(OBJDIR) --outdir=$(OUTDIR) \
		$(SOURCES) $(INCLUDES) $(if $(DEBUG),,-DNDEBUG)

.PHONY: clean
clean:
	rm -Rf $(OBJDIR)
	rm -Rf $(OUTDIR)
