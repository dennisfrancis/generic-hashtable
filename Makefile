
CC=gcc
CFLAGS=-Wall -O3 -march=native

# Linking
FLAGS=

OBJDIR=obj
TESTDIR=test
LIBDIR=lib

# Doubly linked list
LLSRC=dll.c
LLSO=dlnklst
LLOBJ=dlnklst.o
LLTEST=test_ll

# Hash table
HASHSRC=hash.c
HASHSO=genhash
HASHOBJ=genhash.o
HASHTEST=test_hash

OBJS=$(OBJDIR)/$(LLOBJ) $(OBJDIR)/$(HASHOBJ)
TARGET=$(LIBDIR)/lib$(LLSO).so $(LIBDIR)/lib$(HASHSO).so
TESTSUITES=$(TESTDIR)/$(LLTEST) $(TESTDIR)/$(HASHTEST)

all: $(TARGET) $(TESTSUITES)

$(OBJS): $(LLSRC) $(HASHSRC)
	mkdir -p $(OBJDIR)
	$(CC) $(CFLAGS) -fPIC -c -o $(OBJDIR)/$(LLOBJ) $(LLSRC)
	$(CC) $(CFLAGS) -fPIC -c -o $(OBJDIR)/$(HASHOBJ) $(HASHSRC)

$(TARGET): $(OBJS)
	mkdir -p $(LIBDIR)
	$(CC) -shared -Wl,-soname,lib$(LLSO).so -o $(LIBDIR)/lib$(LLSO).so $(OBJDIR)/$(LLOBJ)
	$(CC) -shared -Wl,-soname,lib$(HASHSO).so -o $(LIBDIR)/lib$(HASHSO).so $(OBJDIR)/$(HASHOBJ)

$(TESTSUITES): $(TARGET) $(LLTEST).c $(HASHTEST).c
	mkdir -p $(TESTDIR)
	$(CC) -Wall -I. -L./$(LIBDIR) $(LLTEST).c -l$(LLSO) -o $(TESTDIR)/$(LLTEST)
	$(CC) -Wall -I. -L./$(LIBDIR) $(HASHTEST).c -l$(HASHSO) -l$(LLSO) -o $(TESTDIR)/$(HASHTEST)
	@echo "============================================================================================="
	@echo "Testing Doubly linked list."
	@echo "LD_LIBRARY_PATH=./$(LIBDIR) $(TESTDIR)/$(LLTEST)"
	@LD_LIBRARY_PATH=./$(LIBDIR) $(TESTDIR)/$(LLTEST) > /dev/null 2>&1 && (echo "PASSED") || (echo "FAILED")
	@echo "============================================================================================="
	@echo "Testing Hash table."
	@echo "LD_LIBRARY_PATH=./$(LIBDIR) $(TESTDIR)/$(HASHTEST)"
	@LD_LIBRARY_PATH=./$(LIBDIR) $(TESTDIR)/$(HASHTEST) > /dev/null 2>&1 && (echo "PASSED") || (echo "FAILED")
	@echo "============================================================================================="

clean:
	rm -f $(OBJDIR)/$(LLOBJ)
	rm -f $(OBJDIR)/$(HASHOBJ)
	rm -f $(LIBDIR)/lib$(LLSO).so
	rm -f $(LIBDIR)/lib$(HASHSO).so
	rm -f $(TESTDIR)/$(LLTEST)
	rm -f $(TESTDIR)/$(HASHTEST)

