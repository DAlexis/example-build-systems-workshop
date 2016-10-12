CXXFLAGS += -Wall -std=c++0x $(include_dirs)
CFLAGS += -Wall $(include_dirs)
CC = gcc
CXX = g++

GLOBAL_BUILD_DIR = $(HOME_DIR)/build

ifndef cfg
    cfg=debug
endif

ifeq ($(cfg), debug)
    CXXFLAGS += -O0 -D_DEBUG -g $(defines)
    CFLAGS += -O0 -D_DEBUG -g $(defines)
    BUILD_DIR +=$(GLOBAL_BUILD_DIR)/debug
else
    ifeq ($(cfg), release)
        CXXFLAGS += -O3 -DNDEBUG
        CFLAGS += -O3 -DNDEBUG
        BUILD_DIR +=$(GLOBAL_BUILD_DIR)/release
    else
        $(error Error! Can not build with configuration $(cfg))
    endif
endif

c_sources_full   = $(c_sources:%.c=$(sources_dir)/%.c)
cpp_sources_full = $(cpp_sources:%.cpp=$(sources_dir)/%.cpp)
static_libs_full = $(static_libs:%.a=$(BUILD_DIR)/%.a)

exe_name_full    = $(exe_name:%=$(BUILD_DIR)/%)
aname_full       = $(aname:%.a=$(BUILD_DIR)/%.a)
soname_full      = $(soname:%.so=$(BUILD_DIR)/%.so)

c_objs = $(c_sources:%.c=$(BUILD_DIR)/%.o)
cpp_objs = $(cpp_sources:%.cpp=$(BUILD_DIR)/%.o)

c_depends = $(c_objs:%.o=%.d)
cpp_depends = $(cpp_objs:%.o=%.d)

all: deps $(pre_build) $(aname) $(soname) $(exe_name) $(post_build)

cleanall: clean deps_clean

-include $(c_depends)
-include $(cpp_depends)

# Making .d files for .c sources
$(c_depends):
	mkdir -p $(BUILD_DIR)
	$(CC) -MM -MT '$(patsubst %.d,%.o,$@) $@' -MF $@ $(patsubst $(BUILD_DIR)/%.d,$(sources_dir)/%.c,$@) $(CFLAGS) 

# Making .d files for .cpp sources
$(cpp_depends):
	mkdir -p $(BUILD_DIR)
	$(CXX) -MM -MT '$(patsubst %.d,%.o,$@) $@' -MF $@ $(patsubst $(BUILD_DIR)/%.d,$(sources_dir)/%.cpp,$@) $(CXXFLAGS) 

# Patently talk make to build .d files for each .o file
%.o: %.d

# Compiling .c sources
$(c_objs): $(c_sources_full)
	mkdir -p $(BUILD_DIR)
	$(CC) -c -o $@ $(patsubst $(BUILD_DIR)/%.o,$(sources_dir)/%.c,$@) $(CFLAGS)

# Compiling .cpp sources
$(cpp_objs):
	mkdir -p $(BUILD_DIR)
	$(CXX) -c -o $@ $(patsubst $(BUILD_DIR)/%.o,$(sources_dir)/%.cpp,$@) $(CXXFLAGS)

# Linking executable
$(exe_name): $(c_objs) $(cpp_objs) 
	mkdir -p $(BUILD_DIR)
	$(CXX) -o $(BUILD_DIR)/$@ $^ $(static_libs_full) $(CXXFLAGS) $(LDFLAGS)

# Making static libraries
$(aname): $(c_objs) $(cpp_objs) 
	mkdir -p $(BUILD_DIR)
	ar r $(BUILD_DIR)/$(aname) $^

# Making dynamic libraries
$(soname): $(c_objs) $(cpp_objs)
	$(CXX) -shared -Wl,-soname,$(soname) -o $(BUILD_DIR)/$(soname) $(c_objs) $(cpp_objs)

deps:
	for i in $(dependencies) ; do make -C $$i cfg=$(cfg); done

deps_clean:
	for i in $(dependencies) ; do make cleanall -C $$i cfg=$(cfg); done

clean:
	rm -rf $(c_objs) $(cpp_objs)
	rm -rf $(c_depends) $(cpp_depends)
	rm -rf $(aname_full) $(soname_full) $(exe_name_full)
