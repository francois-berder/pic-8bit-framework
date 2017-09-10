all: framework

MCU := pic$(CHIP)

include mcu/$(MCU)/Makefile.mcu

INCLUDES := -Imcu/include
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
