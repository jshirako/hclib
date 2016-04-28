#ifdef USE_XML
PROJECT_CFLAGS=-I$(HCLIB_ROOT)/include -I$(LIBXML2_INCLUDE)
PROJECT_LDFLAGS=-L$(LIBXML2_LIBS) -L$(HCLIB_ROOT)/lib
PROJECT_LDLIBS=-lhclib -lxml2
#else
PROJECT_CFLAGS=-I$(HCLIB_ROOT)/include
PROJECT_LDFLAGS=-L$(HCLIB_ROOT)/lib
PROJECT_LDLIBS=-lhclib
#endif
PROJECT_CXXFLAGS=-std=c++11 $(PROJECT_CFLAGS)
ifdef TBB_MALLOC
  PROJECT_LDFLAGS+=-L$(TBB_MALLOC)
  PROJECT_LDLIBS+=-ltbbmalloc_proxy
endif
ifdef HC_CUDA_FLAGS
  PROJECT_LDFLAGS+=-L$(CUDA_HOME)/lib
  PROJECT_LDFLAGS+=-L$(CUDA_HOME)/lib64
  PROJECT_CFLAGS+=-I$(CUDA_HOME)/include
  PROJECT_LDLIBS+=-lcudart
  PROJECT_CFLAGS+=-DHC_CUDA
  PROJECT_CXXFLAGS+=-DHC_CUDA
endif
