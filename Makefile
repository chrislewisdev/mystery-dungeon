PATH := $(DEVKITARM)/bin:$(DEVKITPRO)/tools/bin:$(PATH)

ROM := md

# Collect all source/data files to be built
SRC = $(wildcard src/*.cpp)
GFX = $(wildcard gfx/*.png)

# C files will depend on headers generated for our image data
GFXH = $(GFX:gfx/%.png=build/%.h)

# Both C files and gfx data will need to be compiled into the final rom
OFILES = $(SRC:src/%.cpp=build/%.o)
OFILES += $(GFX:gfx/%.png=build/%.o)

# Converts our .elf file into a proper nds rom using ndstool, setting some metadata options.
build/$(ROM).nds: build/$(ROM).elf
	ndstool -c ./build/$(ROM).nds -9 ./build/$(ROM).elf \
		-b /opt/devkitpro/libnds/icon.bmp "$(ROM);built with devkitARM;http://devkitpro.org"

# Links together all our object files into a '.elf' file, a kind of raw binary with our code.
build/$(ROM).elf: $(OFILES)
	arm-none-eabi-g++ -specs=ds_arm9.specs -g -mthumb -mthumb-interwork -Wl,-Map,build/$(ROM).map \
		$(OFILES) -L/opt/devkitpro/libnds/lib -lnds9 -o ./build/$(ROM).elf

# grit outputs .s (assembly) files which must also be compiled into .o files.
%.o: %.s
	arm-none-eabi-g++ -x assembler-with-cpp -g -marm -mthumb-interwork -march=armv5te -mtune=arm946e-s -c $< -o $@

# Compiles any cpp file into a .o file to be linked. the generation of gfx headers must happen first.
build/%.o: src/%.cpp $(GFXH) | build/
	arm-none-eabi-g++ -g -Wall -O2 \
		-march=armv5te -mtune=arm946e-s -mthumb -mthumb-interwork \
		-fomit-frame-pointer -ffast-math -fno-rtti -fno-exceptions \
		-I/opt/devkitpro/libnds/include -Ibuild -DARM9 \
		-c $< -o $@

# PNG files must be converted into both .h and .s files for both the definitions and data to be referenced elsewhere
build/%.s build/%.h: gfx/%.png | build/
	grit $< -ff $<.grit -o $(basename $@)

build/:
	mkdir build

run: build/$(ROM).nds
	~/gamedev/melonDS build/$(ROM).nds

clean:
	rm -rf build
