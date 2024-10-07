include Makefile.in

.PHONY: game ext tests clean

game: ext
	$(MAKE) -C $(GAME_DIR)

ext:
	$(MAKE) -C $(EXT_DIR)

tests: game
	$(MAKE) -C $(TEST_DIR)

clean:
	$(MAKE) -C $(GAME_DIR) clean
	$(MAKE) -C $(EXT_DIR) clean
	$(MAKE) -C $(TEST_DIR) clean
