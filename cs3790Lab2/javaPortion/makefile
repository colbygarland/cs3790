#
# Makefile for the java portion of lab 2
#
# Written by Colby Garland ID# 5034957
#
#

JCC = javac

JFLAGS = -g

default: Prime.class Threads.class

Prime.class: Threads.java
	$(JCC) $(JFLAGS) Threads.java

Threads.class: Threads.java
	$(JCC) $(JFLAGS) Threads.java

clean:
	$(RM) *.class
