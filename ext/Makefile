CBASE_DIR=CBase
HASHMAP_DIR=c-hashmap
SDL3_BUILD_SCRIPT=build_sdl3.sh
SDL3_IMAGE_BUILD_SCRIPT=build_sdl3_image.sh
SDL3_TTF_BUILD_SCRIPT=build_sdl3_ttf.sh
SDL3_MIXER_BUILD_SCRIPT=build_sdl3_mixer.sh
CJSON_BUILD_SCRIPT=build_cjson.sh
CIMGUI_BUILD_SCRIPT=build_cimgui.sh
LUA_DIR=lua

CPP=g++

.PHONY: imgui_impl licenses cimgui lua all sdl3_mixer sdl3_image sdl3 hashmap cjson cbase clean

all: lua sdl3 sdl3_mixer sdl3_image sdl3_ttf cbase hashmap cjson cimgui licenses

sdl3:
	./$(SDL3_BUILD_SCRIPT)

sdl3_image:
	./$(SDL3_IMAGE_BUILD_SCRIPT)

sdl3_ttf:
	./$(SDL3_TTF_BUILD_SCRIPT)

sdl3_mixer:
	./$(SDL3_MIXER_BUILD_SCRIPT)

cimgui:
ifeq ($(EDITOR),1)
	./$(CIMGUI_BUILD_SCRIPT)
endif

imgui_impl: sdl3
ifeq ($(IMPL),SDL3)
	$(CPP) -I. -Icimgui/imgui -Iinclude -O2 -fno-threadsafe-statics -fno-exceptions -fno-rtti -c -DIMGUI_DISABLE_OBSOLETE_FUNCTIONS -DIMGUI_IMPL_API="extern \"C\" " -DIMGUI_USER_CONFIG="\"cimgui/cimconfig.h\"" cimgui/imgui/backends/imgui_impl_sdl3.cpp -o cimgui/imgui/backends/imgui_impl_sdl3.o
	$(CPP) -I. -Icimgui/imgui -Iinclude -O2 -fno-threadsafe-statics -fno-exceptions -fno-rtti -c -DIMGUI_DISABLE_OBSOLETE_FUNCTIONS -DIMGUI_IMPL_API="extern \"C\" " -DIMGUI_USER_CONFIG="\"cimgui/cimconfig.h\"" cimgui/imgui/backends/imgui_impl_sdlrenderer3.cpp -o cimgui/imgui/backends/imgui_impl_sdlrenderer3.o
	#$(CPP) -Wl,-rpath,`realpath lib` -shared cimgui/imgui/backends/imgui_impl_sdl3.o cimgui/imgui/backends/imgui_impl_sdlrenderer3.o -o lib/sdl3Impl.so
	ar r lib/sdl3Impl.a cimgui/imgui/backends/imgui_impl_sdl3.o cimgui/imgui/backends/imgui_impl_sdlrenderer3.o
endif

cjson:
	./$(CJSON_BUILD_SCRIPT)

lua:
	$(MAKE) -C $(LUA_DIR) all install INSTALL_TOP=$(CURDIR)
	rm -rf man

hashmap:
	$(MAKE) -C $(HASHMAP_DIR) lib

cbase:
	$(MAKE) -C $(CBASE_DIR) lib

clean:
	$(MAKE) -C $(CBASE_DIR) clean
	$(MAKE) -C $(HASHMAP_DIR) clean
	rm -rf include/* lib/* man share

licenses: $(LICENSES)
	rm -f ../licenses/*
	cp -f luaLICENSE.txt ../licenses/lua_LICENSE.txt
	cp -f $(HASHMAP_DIR)/LICENSE  ../licenses/c-hamshmap_LICENSE.txt
	cp -f cJSON_LICENSE ../licenses/cJSON_LICENSE.txt
	cp -f cimgui_LICENSE ../licenses/cimgui_LICENSE.txt
	cp -f imgui_LICENSE ../licenses/imgui_LICENSE.txt
	cp -f share/licenses/SDL3/LICENSE.txt  ../licenses/SDL3_LICENSE.txt
	cp -f share/licenses/SDL3_image/LICENSE.txt  ../licenses/SDL3_IMAGE_LICENSE.txt
	cp -f share/licenses/SDL3_mixer/LICENSE.txt  ../licenses/SDL3_MIXER_LICENSE.txt
	cp -f share/licenses/SDL3_ttf/LICENSE.txt  ../licenses/SDL3_TTF_LICENSE.txt
