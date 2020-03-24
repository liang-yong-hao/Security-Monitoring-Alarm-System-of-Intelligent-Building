##############################
# DlexServ Makefile
##############################

INSTALLROOT=$(PWD)

CC=arm-linux-gcc
INSTALL=install
BIN=/usr/local/bin


SERVFLAGS= -O2 -DLINUX $(WARNINGS) -I /UP-Magic/kernel/linux-2.6.24.4/include

SERVLIBS= -lpthread

#WARNINGS = -Wall \
#           -Wundef -Wpointer-arith -Wbad-function-cast \
#           -Wcast-align -Wwrite-strings -Wstrict-prototypes \
#           -Wmissing-prototypes -Wmissing-declarations \
#           -Wnested-externs -Winline -Wcast-qual -W \
#           -Wno-unused
#           -Wunused



OBJSERVER= server.o spcav4l.o utils.o tcputils.o sht11.o gpio_test.o irst_test.o s3c2410-smog.o 
		
all:	 DlexServ 

clean:
	@echo "Cleaning up directory."
	rm -f *.a *.o DlexServ   core *~ log errlog


DlexServ: $(OBJSERVER)
	$(CC) $(SERVFLAGS) -o DlexServ $(OBJSERVER) $(SERVLIBS) -lm
	

	
server.o:	server.c intruder.h 
		$(CC) $(SERVFLAGS) -c -o $@ $<
	
spcav4l.o:	spcav4l.c spcav4l.h 
		$(CC) $(SERVFLAGS) -c -o $@ $<
		
utils.o:	utils.c utils.h
		$(CC) $(SERVFLAGS) -c -o $@ $<
				
tcputils.o:	tcputils.c tcputils.h
		$(CC) $(SERVFLAGS) -c -o $@ $<

sht11.o:	sht11.c sht11.h 
		$(CC) $(SERVFLAGS) -c -o $@ $<		

gpio_test.o:	gpio_test.c gpio_test.h
		$(CC) $(SERVFLAGS) -c -o $@ $<

irst_test.o:    irst_test.c irst_test.h 
		$(CC) $(SERVFLAGS) -c -o $@ $<
s3c2410-smog.o:	s3c2410-smog.c s3c2410-smog.h 
		$(CC) $(SERVFLAGS) -c -o $@ $<



install_DlexServ: spcafox
	$(INSTALL) -s -m 755 -g root -o root DlexServ $(BIN) 
	

	 
install: DlexServ 
	$(INSTALL) -s -m 755 -g root -o root DlexServ $(BIN) 
	
