PATH 		:= $(DEVKITARM)/bin:$(PATH)
#---------------------------------------------------------------------------------
# Please uncomment (i.e. delete the '#') only one "ARM7_SELECTED" line. If unsure,
# leave it as is (with ARM7_MP3 uncommented).
#---------------------------------------------------------------------------------

#MAXMODUSE=YES
#ARM7_SELECTED = ARM7_MP3
#ARM7_SELECTED = ARM7_MP3_DSWIFI
#ARM7_SELECTED = ARM7_MAXMOD_DSWIFI

USE_EFS = YES
LAUNCH_ROM_AFTER_BUILD = YES

#arm7 included with this makefile
#include $(DEVKITPRO)/PAlib/lib/PA_Makefile2
#ARM7BIN		:= -7 $(PAPATH)/lib/arm7/arm7.bin
TEXT1 		:= Diablo Project
TEXT2 		:= using PAlib-µLib
TEXT3 		:= By Le Rodeur
ICON 			:= -b $(CURDIR)/../logo.bmp

#---------------------------------------------------------------------------------
.SUFFIXES:
#---------------------------------------------------------------------------------
ifeq ($(strip $(DEVKITARM)),)
$(error "Please set DEVKITARM in your environment. export DEVKITARM=<path to>devkitARM)
endif
#---------------------------------------------------------------------------------
# TARGET is the name of the output, if this ends with _mb generates a multiboot image
# BUILD is the directory where object files & intermediate files will be placed
# SOURCES is a list of directories containing source code
# INCLUDES is a list of directories containing extra header files
#---------------------------------------------------------------------------------
TARGET	:=	$(shell basename $(CURDIR))
BUILD		:=	build
SOURCES	:=	gfx/bin source source/objects source/maps data
INCLUDES	:=	include build data gfx $(BUILD)
DATA		:=	data
AUDIO    	:=  audio

EXPORT_DIR := /c/ndsexamples/
#---------------------------------------------------------------------------------
# ARM7BIN is the path to an arm7 binary other than the default
#	usage: ARM7BIN := -7 binaryName.bin
#
# ICON is the path to an icon to be used int the header plus text
#	usage: ICON := -t iconName.bmp "text line one; text line 2; text line 3"
#
#---------------------------------------------------------------------------------



#---------------------------------------------------------------------------------
# options for code generation
#---------------------------------------------------------------------------------
ARCH	:=	-mthumb-interwork

# note: arm9tdmi isn't the correct CPU arch, but anything newer and LD
# *insists* it has a FPU or VFP, and it won't take no for an answer!
CFLAGS	:= -Wall -O2 \
 		-mcpu=arm9tdmi -mtune=arm9tdmi -fomit-frame-pointer\
		-ffast-math \
		$(ARCH)

CFLAGS	+=	$(INCLUDE) -DARM9 -I$(DEVKITPRO)/PAlib/include/nds

ASFLAGS	:=	-g $(ARCH)
LDFLAGS	:=	-g $(ARCH) -mno-fpu -L$(DEVKITPRO)/PAlib/lib -lpa9


#---------------------------------------------------------------------------------
# path to tools - this can be deleted if you set the path in windows
#---------------------------------------------------------------------------------
# export PATH		:=	/d/dev/ds/devkitARM_r11/bin:/bin

#---------------------------------------------------------------------------------
# PATH to ndslib - just make a system variable called NDSLIBPATH and be done with it
#---------------------------------------------------------------------------------
# NDSLIBPATH	:=	/d/dev/ds/ndslib/

#---------------------------------------------------------------------------------
# the prefix on the compiler executables
#---------------------------------------------------------------------------------
PREFIX			:=	arm-eabi-
#---------------------------------------------------------------------------------
# any extra libraries we wish to link with the project
#---------------------------------------------------------------------------------
LIBS	:= -lul -lfilesystem -lmm9 -lpng -lz -lfat -lnds9


#---------------------------------------------------------------------------------
# list of directories containing libraries, this must be the top level containing
# include and lib
#---------------------------------------------------------------------------------
LIBDIRS	:=	$(DEVKITPRO)/libnds


#---------------------------------------------------------------------------------
# no real need to edit anything past this point unless you need to add additional
# rules for different file extensions
#---------------------------------------------------------------------------------
ifneq ($(BUILD),$(notdir $(CURDIR)))
#---------------------------------------------------------------------------------

export OUTPUT	:=	$(CURDIR)/$(TARGET)

export VPATH	:=	$(foreach dir,$(SOURCES),$(CURDIR)/$(dir)) \
					$(foreach dir,$(DATA),$(CURDIR)/$(dir))
export CC		:=	$(PREFIX)gcc
export CXX		:=	$(PREFIX)g++
export AR		:=	$(PREFIX)ar
export OBJCOPY	:=	$(PREFIX)objcopy
#---------------------------------------------------------------------------------
# use CXX for linking C++ projects, CC for standard C
#---------------------------------------------------------------------------------
export LD		:=	$(CXX)
#export LD		:=	$(CC)

CFILES		:=	$(foreach dir,$(SOURCES),$(notdir $(wildcard $(dir)/*.c)))
CPPFILES	:=	$(foreach dir,$(SOURCES),$(notdir $(wildcard $(dir)/*.cpp)))
SFILES		:=	$(foreach dir,$(SOURCES),$(notdir $(wildcard $(dir)/*.s)))
PCXFILES	:=	$(foreach dir,$(SOURCES),$(notdir $(wildcard $(dir)/*.pcx)))
BINFILES	:=	$(foreach dir,$(SOURCES),$(notdir $(wildcard $(dir)/*.bin)))
PNGFILES	:=	$(foreach dir,$(SOURCES),$(notdir $(wildcard $(dir)/*.png)))
PALFILES	:=	$(foreach dir,$(SOURCES),$(notdir $(wildcard $(dir)/*.pal)))
RAWFILES	:=	$(foreach dir,$(SOURCES),$(notdir $(wildcard $(dir)/*.raw)))
MAPFILES	:=	$(foreach dir,$(SOURCES),$(notdir $(wildcard $(dir)/*.map)))
JPEGFILES	:=	$(foreach dir,$(SOURCES),$(notdir $(wildcard $(dir)/*.jpg)))
MODFILES	:=	$(foreach dir,$(SOURCES),$(notdir $(wildcard $(dir)/*.mod)))
GIFFILES	:=	$(foreach dir,$(SOURCES),$(notdir $(wildcard $(dir)/*.gif)))
BMPFILES	:=	$(foreach dir,$(SOURCES),$(notdir $(wildcard $(dir)/*.bmp)))


ifeq ($(strip $(MAXMODUSE)), YES)
	export AUDIOFILES := $(foreach file,$(notdir $(wildcard $(AUDIO)/*.mod)),$(CURDIR)/$(AUDIO)/$(file)) \
	                     $(foreach file,$(notdir $(wildcard $(AUDIO)/*.s3m)),$(CURDIR)/$(AUDIO)/$(file)) \
	                     $(foreach file,$(notdir $(wildcard $(AUDIO)/*.xm)),$(CURDIR)/$(AUDIO)/$(file))  \
	                     $(foreach file,$(notdir $(wildcard $(AUDIO)/*.it)),$(CURDIR)/$(AUDIO)/$(file))  \
	                     $(foreach file,$(notdir $(wildcard $(AUDIO)/*.wav)),$(CURDIR)/$(AUDIO)/$(file))

	ifeq ($(strip $(AUDIOFILES)),)
		TEXT_TO_SAY_2 := No Maxmod-compatible files were found in the audio folder.
		TEXT_TO_SAY_3 := If you are loading the soundbank from the filesystem, ignore this message.
		TEXT_TO_SAY_4 := " "
		DONT_BUILD_MAXMOD_SOUNDBANK := YES
	else
		# Add the Maxmod soundbank to the list of bin files
		BINFILES += soundbank_bin.bin
	endif
endif



export OFILES	:=	$(MAPFILES:.map=.o) $(RAWFILES:.raw=.o) $(PALFILES:.pal=.o) $(BINFILES:.bin=.o) $(PNGFILES:.png=.o) $(PCXFILES:.pcx=.o) $(JPEGFILES:.jpg=.o) $(MODFILES:.mod=.o) $(GIFFILES:.gif=.o) $(BMPFILES:.bmp=.o)\
					$(CPPFILES:.cpp=.o) $(CFILES:.c=.o) $(SFILES:.s=.o)

export INCLUDE	:=	$(foreach dir,$(INCLUDES),-I$(CURDIR)/$(dir)) \
					$(foreach dir,$(LIBDIRS),-I$(dir)/include) \
					$(foreach dir,$(LIBDIRS),-I$(dir)/include/nds) \
					-I$(PAPATH)/include/nds\
					-I$(CURDIR)/$(BUILD)

export LIBPATHS	:=	$(foreach dir,$(LIBDIRS),-L$(dir)/lib)

.PHONY: $(BUILD) clean export

#---------------------------------------------------------------------------------
$(BUILD):
	@[ -d $@ ] || mkdir -p $@
	@make --no-print-directory -C $(BUILD) -f $(CURDIR)/Makefile

#---------------------------------------------------------------------------------
clean:
	@echo clean ...$(TARGET)
	@rm -fr $(BUILD) *.elf *.*ds*

export:
	@echo exporting ...$(TARGET)
	@cp *.nds $(EXPORT_DIR)/$(TARGET).nds

#---------------------------------------------------------------------------------
else

DEPENDS	:=	$(OFILES:.o=.d)

#---------------------------------------------------------------------------------
# main targets
#---------------------------------------------------------------------------------
$(OUTPUT).ds.gba	: 	$(OUTPUT).nds

$(OUTPUT).nds	: 	$(OUTPUT).bin

$(OUTPUT).bin	:	$(OUTPUT).elf

$(OUTPUT).elf	:	$(OFILES)

#---------------------------------------------------------------------------------
# Rule to build the soundbank from audio files
#---------------------------------------------------------------------------------
soundbank_bin.bin : $(AUDIOFILES)
#---------------------------------------------------------------------------------
ifneq ($(strip $(DONT_BUILD_MAXMOD_SOUNDBANK)), YES)
	@echo "Generating soundbank..."
	@echo
	@mmutil $^ -d -osoundbank_bin.bin -hsoundbank.h
endif


#---------------------------------------------------------------------------------
%.ds.gba: %.nds
	@echo built ... $(notdir $@)
	@dsbuild $<

ifeq ($(strip $(USE_EFS)), YES)
#	@$(CURDIR)/../efs $(OUTPUT).ds.gba
else
	@cp $(CURDIR)/../$(notdir $@) ../$(notdir $(OUTPUT)).sc.nds
endif
#---------------------------------------------------------------------------------
%.nds: %.bin
ifeq ($(strip $(USE_EFS)), YES)
	@ndstool -c $@ -9 $(TARGET).bin $(ARM7BIN) $(LOGO) $(ICON) "$(TEXT1);$(TEXT2);$(TEXT3)" -d ../nitrofs
#	@$(CURDIR)/../efs $(OUTPUT).nds


else
	@ndstool -c $@ -9 $(TARGET).bin $(ARM7BIN) $(LOGO) $(ICON) "$(TEXT1);$(TEXT2);$(TEXT3)"
endif

#---------------------------------------------------------------------------------
%.bin: %.elf

	@$(OBJCOPY) -O binary $(TARGET).elf $(TARGET).bin

#---------------------------------------------------------------------------------
%.elf:
	@echo $(LD)  $(LDFLAGS) -specs=ds_arm9.specs $(OFILES) $(LIBPATHS) $(LIBS) -o $(TARGET).elf
	@$(LD)  $(LDFLAGS) -specs=ds_arm9.specs $(OFILES) $(LIBPATHS) $(LIBS) -o $(TARGET).elf



#---------------------------------------------------------------------------------
# Compile Targets for C/C++
#---------------------------------------------------------------------------------

#---------------------------------------------------------------------------------
%.o : %.cpp
	@echo $(notdir $<)
	@$(CXX) -MM $(CFLAGS) -o $*.d $<
	@$(CXX) $(CFLAGS) -c $< -o$@

#---------------------------------------------------------------------------------
%.o : %.c
	@echo $(notdir $<)
	@$(CC) -MM $(CFLAGS) -o $*.d $<
	@$(CC)  $(CFLAGS) -c $< -o$@

#---------------------------------------------------------------------------------
%.o : %.s
	@echo $(notdir $<)
	@$(CC) -MM $(CFLAGS) -o $*.d $<
	@$(CC)  $(ASFLAGS) -c $< -o$@

define bin2o
	cp $(<) $(*).tmp
	$(OBJCOPY) -I binary -O elf32-littlearm -B arm \
	--rename-section .data=.rodata \
	--redefine-sym _binary_$*_tmp_start=$*\
	--redefine-sym _binary_$*_tmp_end=$*_end\
	--redefine-sym _binary_$*_tmp_size=$*_size\
	$(*).tmp $(@)
	echo "extern const u8" $(*)"[];" > $(*).h
	echo "extern const u32" $(*)_size[]";" >> $(*).h
	rm $(*).tmp
endef

#---------------------------------------------------------------------------------
%.o	:	%.pcx
#---------------------------------------------------------------------------------
	@echo $(notdir $<)
	@$(bin2o)

#---------------------------------------------------------------------------------
%.o	:	%.bin
#---------------------------------------------------------------------------------
	@echo $(notdir $<)
	@$(bin2o)

#---------------------------------------------------------------------------------
%.o	:	%.png
#---------------------------------------------------------------------------------
	@echo $(notdir $<)
	@$(bin2o)

#---------------------------------------------------------------------------------
%.o	:	%.raw
#---------------------------------------------------------------------------------
	@echo $(notdir $<)
	@$(bin2o)

#---------------------------------------------------------------------------------
%.o	:	%.pal
#---------------------------------------------------------------------------------
	@echo $(notdir $<)
	@$(bin2o)

#---------------------------------------------------------------------------------
%.o	:	%.map
#---------------------------------------------------------------------------------
	@echo $(notdir $<)
	@$(bin2o)

#---------------------------------------------------------------------------------
%.o	:	%.mdl
#---------------------------------------------------------------------------------
	@echo $(notdir $<)
	@$(bin2o)

#---------------------------------------------------------------------------------
%.o	:	%.jpg
#---------------------------------------------------------------------------------
	@echo $(notdir $<)
	@$(bin2o)

#---------------------------------------------------------------------------------
%.o	:	%.mod
#---------------------------------------------------------------------------------
	@echo $(notdir $<)
	@$(bin2o)

#---------------------------------------------------------------------------------
%.o	:	%.gif
#---------------------------------------------------------------------------------
	@echo $(notdir $<)
	@$(bin2o)

#---------------------------------------------------------------------------------
%.o	:	%.bmp
#---------------------------------------------------------------------------------
	@echo $(notdir $<)
	@$(bin2o)


-include $(DEPENDS)

#---------------------------------------------------------------------------------------
endif

lib:
	$(DEVKITPRO)/devkitARM/arm-eabi/bin/ar -cr test.a build/*.o

#---------------------------------------------------------------------------------------


