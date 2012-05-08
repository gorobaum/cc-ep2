# dependencies
.temp/mutex.o: src/mutex.cxx src/mutex.h src/log.h
.temp/ep2.o: src/ep2.cxx src/ep2.h src/graph.h src/path.h \
 src/log.h
.temp/thread.o: src/thread.cxx src/thread.h src/log.h
.temp/main.o: src/main.cxx src/ep2.h src/thread.h
.temp/barrier.o: src/barrier.cxx src/barrier.h src/thread.h src/log.h
.temp/graph.o: src/graph.cxx src/graph.h src/path.h
.temp/path.o: src/path.cxx src/path.h
.temp/log.o: src/log.cxx src/log.h
