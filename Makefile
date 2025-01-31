include Makefile.in

.PHONY: game meta ext tests clean full_clean

game: ext
	$(MAKE) -C $(GAME_DIR)

meta:
	$(MAKE) -C $(META_DIR) meta

ext:
	$(MAKE) -C $(EXT_DIR) EDITOR=1

tests: game
	$(MAKE) -C $(TEST_DIR)

clean:
	$(MAKE) -C $(GAME_DIR) clean
	$(MAKE) -C $(TEST_DIR) clean

full_clean: clean
	$(MAKE) -C $(EXT_DIR) clean
