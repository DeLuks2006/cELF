INCLUDEDIR	:= include
SRCDIR			:= src
BUILDDIR		:= build
CACHEDIR		:= $(BUILDDIR)/cache
OUTPUT			:= $(BUILDDIR)/cELF
OUTPUTDBG		:= $(OUTPUT)-dbg

CC					:= clang
STRIP				:= llvm-strip
COMMON_FLAGS = -Wall -Wshadow -Wextra -Werror -flto=thin -O3 -I$(INCLUDEDIR)
LDFLAGS			:= -flto=thin -o $(OUTPUT)
STRIPFLAGS	:= --strip-all

CFILES			:= $(shell find $(SRCDIR) -name "*.c" -type f)
OBJFILES		:= $(CFILES:$(SRCDIR)%.c=$(CACHEDIR)%.o)
DIRECTORIES	 = $(shell find $(SRCDIR) -type d)
DIRECTORIES := $(DIRECTORIES:$(SRCDIR)%=$(CACHEDIR)%)

optimized: dirs $(OBJFILES)
	@echo -e "\e[32m==>\e[0m LD    $(OUTPUT)"
	@$(CC) $(OBJFILES) -o $(OUTPUT) $(LDFLAGS)
	@echo -e "\e[32m==>\e[0m STRIP $(OUTPUT)"
	@$(STRIP) $(STRIPFLAGS) $(OUTPUT)

debug: COMMON_FLAGS += -g
debug: dirs $(OBJFILES)
	@echo -e "\e[32m==>\e[0m LD    $(OUTPUT)"
	@$(CC) $(OBJFILES) -o $(OUTPUTDBG) $(COMMON_FLAGS)

help:
	@echo "Available targets:"
	@echo "==> make optimized"
	@echo "==> make debug"
	@echo "==> make clean"


$(CACHEDIR)/%.o: $(SRCDIR)/%.c
	@echo -e "\e[32m==>\e[0m CC    $@"
	@$(CC) $(COMMON_FLAGS) -c $< -o $@

dirs:
	@mkdir -p $(DIRECTORIES)

clean:
	@rm -rf $(BUILDDIR)
