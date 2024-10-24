CBASE_DIR=CBase
HASHMAP_DIR=c-hashmap
SDL3_BUILD_SCRIPT=build_sdl3.sh
SDL3_IMAGE_BUILD_SCRIPT=build_sdl3_image.sh

.PHONY: all sdl3_image sdl3 hashmap cbase clean

all: sdl3 sdl3_image cbase hashmap

sdl3:
	./$(SDL3_BUILD_SCRIPT)

sdl3_image:
	./$(SDL3_IMAGE_BUILD_SCRIPT)

hashmap:
	$(MAKE) -C $(HASHMAP_DIR) lib

cbase:
	$(MAKE) -C $(CBASE_DIR) lib

clean:
	$(MAKE) -C $(CBASE_DIR) clean
	$(MAKE) -C $(HASHMAP_DIR) clean
	rm -rf include/* lib/* share
