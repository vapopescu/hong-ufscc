
CC= g++
OBJS = scc_main.o my_work_queue.o scc_tarjan.o  scc_ufscc.o scc_color.o scc_trim1.o scc_fb_seq.o scc_post_analyze.o scc_trim2.o scc_fb_global.o scc_weak.o scc_fb_seq2.o scc_trim2_new.o
INCDIR = -I../gm_graph/inc
OUTDIR = ./

CFLAGS = -O3 -g -I. $(INCDIR) -fopenmp -std=gnu++0x
LFLAGS = -L../gm_graph/lib -lgmgraph

ifeq ($(OS),Windows_NT)
	LFLAGS += -L"C:/Program Files (x86)/Windows Kits/10/Lib/10.0.19041.0/um/x64" -lws2_32
endif

INCFILES = $(shell ls $(INCDIR))
H_FILES = $(addprefix $(INCDIR)/, $(INCFILES))

NAME = ../scc
LIBNAME = ../libhongufscc.a
all : $(NAME) $(LIBNAME)

$(NAME) : $(OBJS) ../gm_graph/lib/libgmgraph.a
	$(CC) $(CFLAGS) $^ $(LFLAGS) -o $@

$(LIBNAME) : $(filter-out scc_main.o, $(OBJS)) scc_nomain.o
	ar rcs $@ $^

%.o:%.cc
	$(CC) $(CFLAGS) -c $^ -o $@

scc_nomain.o: scc_main.cc
	$(CC) $(CFLAGS) -D_NO_MAIN -c $^ -o $@	

clean :
	\rm $(NAME) $(LIBNAME) *.o
