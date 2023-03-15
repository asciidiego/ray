CXX := clang++
CXXFLAGS := -std=c++11 -MMD
SRCDIR := src
BUILDDIR := build
TARGET := render

SOURCES := $(wildcard $(SRCDIR)/*.cc)
OBJECTS := $(patsubst $(SRCDIR)/%.cc,$(BUILDDIR)/%.o,$(SOURCES))
DEPENDS := $(patsubst $(SRCDIR)/%.cc,$(BUILDDIR)/%.d,$(SOURCES))

$(BUILDDIR)/$(TARGET): $(OBJECTS)
	$(CXX) $(CXXFLAGS) $^ -o $@

$(BUILDDIR)/%.o: $(SRCDIR)/%.cc
	$(CXX) $(CXXFLAGS) -c $< -o $@

-include $(DEPENDS)

clean:
	rm -f $(BUILDDIR)/*.o $(BUILDDIR)/$(TARGET)

