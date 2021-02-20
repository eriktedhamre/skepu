FLAGS := -std=c++0x -fopenmp -I /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/include/c++/v1/  -I /Applications/Xcode.app/Contents/Developer/Platforms/MacOSX.platform/Developer/SDKs/MacOSX.sdk/usr/include/

graphgen: graphgen.cpp
	g++-10 $(FLAGS) -o $@ $<

clean: 
	rm graphgen

