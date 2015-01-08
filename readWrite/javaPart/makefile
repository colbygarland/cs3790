#
# Makefile for the java portion of assignment 2
#
# Written by Colby Garland ID# 5034957
#
#

JCC = javac
JFLAGS = -g

default: Writer.class Reader.class ReadWrite.class

Writer.class: ReadWrite.java
	$(JCC) $(JFLAGS) ReadWrite.java

Reader.class: ReadWrite.java
	$(JCC) $(JFLAGS) ReadWrite.java

ReadWrite.class: ReadWrite.java
	$(JCC) $(JFLAGS) ReadWrite.java

clean:
	$(RM) *.class
