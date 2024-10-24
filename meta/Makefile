include ../Makefile.in
PREFIX=../

SPRITES_DIR=$(PREFIX)testlevel/sprites
ATLASTOOL=$(PREFIX)meta/AtlasTool/AtlasTool.py
ATLAS_SIZE=1024x1024


.PHONY: meta atlas clean

meta: atlas

atlas:
	$(ATLASTOOL) -d $(SPRITES_DIR) -s $(ATLAS_SIZE) -o $(PREFIX)testlevel/atlas/atlas
