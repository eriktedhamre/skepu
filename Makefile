.DEFAULT_GOAL := all

BUILD_DIR=build
PKG_DIR=skepu

LLVM_CLANG=llvm/llvm/tools/clang
CLANG_HEADERS=llvm/clang/lib/Headers

SKEPU_TOOL=llvm/clang/tools/skepu-tool
SKEPU_HEADERS=skepu-headers/src

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

$(SKEPU_TOOL):
	cd llvm; \
		git apply ../llvm.patch;

$(BUILD_DIR)/Makefile: $(BUILD_DIR) $(SKEPU_TOOL)
	@cd build; \
	cmake -G "Unix Makefiles" ../llvm/llvm \
		-DCMAKE_BUILD_TYPE=Release \
		-DLLVM_ENABLE_PROJECTS=clang

skepu-tool: $(BUILD_DIR)/Makefile
	$(MAKE) -C build skepu-tool

all: skepu-tool

$(PKG_DIR):
	install -Dm755 build/bin/skepu-tool $(PKG_DIR)/bin/skepu-tool
	cp -R $(CLANG_HEADERS) $(PKG_DIR)/clang_headers
	cp -R $(SKEPU_HEADERS) $(PKG_DIR)/include
	install -Dm644 PKG_README.in $(PKG_DIR)/README

skepu.tgz: $(PKG_DIR)
	tar cpzf skepu.tgz $(PKG_DIR)

pkg: skepu.tgz

clean-skepu:
	rm -Rf $(PKG_DIR)

clean-pkg:
	rm -f skepu.tgz

clean-build:
	rm -rf $(BUILD_DIR)

clean-llvm:
	cd llvm; git add . && git reset --hard

clean: clean-build
distclean: clean clean-pkg clean-skepu
