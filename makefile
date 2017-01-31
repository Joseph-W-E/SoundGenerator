all: sndinfo sndcat sndmix sndgen


sndgen: sndgen.o song.o util.o adsr.o
	g++ -o sndgen sndgen.o song.o util.o adsr.o

sndmix: sndmix.o song.o util.o adsr.o
	g++ -o sndmix sndmix.o song.o util.o adsr.o

sndcat: sndcat.o song.o util.o adsr.o
	g++ -o sndcat sndcat.o song.o util.o adsr.o

sndinfo: sndinfo.o song.o util.o adsr.o
	g++ -o sndinfo sndinfo.o song.o util.o adsr.o




sndgen.o: sndgen.cpp util.h adsr.h
	g++ -c sndgen.cpp


sndmix.o: sndmix.cpp util.h
	g++ -c sndmix.cpp


sndcat.o: sndcat.cpp util.h
	g++ -c sndcat.cpp


sndinfo.o: sndinfo.cpp util.h
	g++ -c sndinfo.cpp


adsr.o: adsr.cpp adsr.h
	g++ -c adsr.cpp

util.o: util.cpp util.h
	g++ -c util.cpp


song.o: song.cpp song.h adsr.h
	g++ -c song.cpp


clean:
	rm -f *.o all
	rm sndinfo
	rm sndcat
	rm sndmix
	rm sndgen