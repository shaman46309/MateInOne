#INCLUDES = /usr/include/c++/4.2.1/

#CXXFLAGS =	-O2 -g -Wall -fmessage-length=0 -I $(INCLUDES)

#Apple LLVM version 5.1 (clang-503.0.40) (based on LLVM 3.4svn)
#Target: x86_64-apple-darwin13.4.0
#Thread model: posix
# "/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/clang" "-cc1" "-triple" "x86_64-apple-macosx10.9.0" "-emit-obj" "-disable-free" "-disable-llvm-verifier" "-main-file-name" "MateInOne.cpp" "-mrelocation-model" "pic" "-pic-level" "2" "-mdisable-fp-elim" "-masm-verbose" "-munwind-tables" "-target-cpu" "core2" "-target-linker-version" "236.3" "-gdwarf-2" "-coverage-file" "/Users/pankajm/cpp/eclipse/MateInOne/MateInOne.o" 
#"-resource-dir" "/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/../lib/clang/5.1" "-stdlib=libc++" "-O2" "-Wall" "-fdeprecated-macro" "-fdebug-compilation-dir" "/Users/pankajm/cpp/eclipse/MateInOne" "-ferror-limit" "19" "-fmessage-length" "0" "-stack-protector" "1" "-mstackrealign" "-fblocks" "-fobjc-runtime=macosx-10.9.0" "-fencode-extended-block-signature" "-fcxx-exceptions" "-fexceptions" "-fdiagnostics-show-option" "-fcolor-diagnostics" "-vectorize-loops" "-vectorize-slp" "-o" "MateInOne.o" "-x" "c++" "MateInOne.cpp"

# Cannot find ostream!! Looking:
#/Applications/Xcode.app/Contents/Developer/Platforms/iPhoneOS.platform/Developer/SDKs/iPhoneOS7.1.sdk/usr/include/c++/4.2.1/ostream
#/Applications/Xcode.app/Contents/Developer/Platforms/iPhoneSimulator.platform/Developer/SDKs/iPhoneSimulator7.1.sdk/usr/include/c++/4.2.1/ostream
#/Applications/Xcode.app/Contents/Developer/Platforms/MacOSX.platform/Developer/SDKs/MacOSX10.8.sdk/usr/include/c++/4.2.1/ostream
#/Applications/Xcode.app/Contents/Developer/Platforms/MacOSX.platform/Developer/SDKs/MacOSX10.9.sdk/usr/include/c++/4.2.1/ostream
#/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/lib/c++/v1/ostream
#/usr/include/c++/4.2.1/ostream
#/usr/local/include/boost/tr1/tr1/ostream

# -I /usr/include/c++/4.2.1/ -I /Users/pankajm/cpp/web/boost_1_57_0
CXXFLAGS =	-O2 -g -Wall -fmessage-length=0  -I/usr/local/include/boost/tr1/tr1/ostream -I/Applications/Xcode.app/Contents/Developer/Platforms/MacOSX.platform/Developer/SDKs/MacOSX10.9.sdk/usr/include/c++/4.2.1/ostream -stdlib=libc++ -std=c++11 -ferror-limit=100

OBJS =		MateInOne.o chess_board.o common.o

OBJS_DBG = mate_debug.o chess_board.o common.o

LIBS = /usr/local/lib/*.a

TARGET =	MateInOne
TARGET_DBG =	mate_debug

$(TARGET):	$(OBJS)
	$(CXX) -o $(TARGET) $(OBJS) $(LIBS) 

$(TARGET_DBG):	$(OBJS_DBG)
	$(CXX) -o $(TARGET_DBG) $(OBJS_DBG) $(LIBS) 

all:	$(TARGET) $(TARGET_DBG)

clean:
	rm -f $(OBJS) $(OBJS_DBG) $(TARGET) $(TARGET_DBG)
