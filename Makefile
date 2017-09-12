all: framework

ifndef CHIP
$(error "CHIP variable must be defined, e.g. CHIP=18f4550")
endif

MCU := pic$(CHIP)

include mcu/$(MCU)/Makefile.mcu

INCLUDES := -Imcu/include -Imcu/include/periph -Imcu/$(MCU)
OBJDIR := obj/$(MCU)/
OUTDIR := bin/$(MCU)/

framework:
	@mkdir -p $(OBJDIR)
	@mkdir -p $(OUTDIR)
	xc8 --chip=$(CHIP) --output=lpp -oframework.lpp --warn=9 \
	--objdir=$(OBJDIR) --outdir=$(OUTDIR) \
	$(SOURCES) $(INCLUDES)

clean:
	rm -Rf $(OBJDIR)
	rm -Rf $(OUTDIR)
