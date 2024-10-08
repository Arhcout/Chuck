CBASE_DIR=CBase
HASHMAP_DIR=c-hashmap

.PHONY: all hashmap cbase clean

all: cbase hashmap

hashmap:
	$(MAKE) -C $(HASHMAP_DIR) lib

cbase:
	$(MAKE) -C $(CBASE_DIR) lib

clean:
	$(MAKE) -C $(CBASE_DIR) clean
	$(MAKE) -C $(HASHMAP_DIR) clean
