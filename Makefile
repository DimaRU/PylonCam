.PHONY : all
.SUFFIXES: .swift .ui

UIDIR = ./
SWIFTDIR = Sources/PylonCam
UI =	$(UIDIR)/UI_PylonCam.ui

SWIFT  = $(UI:$(UIDIR)/%.ui=$(SWIFTDIR)/%.swift)
UIC    = qlift-uic

$(SWIFTDIR)/%.swift: $(UIDIR)/%.ui
	$(UIC) $< $@

all:	${SWIFT}
