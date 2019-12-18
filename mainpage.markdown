cppUX
======
\mainpage cppUX

Introduction
============
The cppUX library is a self contained rendering system that works
precisely with the c++ standard library. The library provides the building 
of document object models for GUI visualization. The syntax for programs appear
very much like a typical JavaScript implementation.

The library is written as a template
interface. The interface syntax of the library while using templates makes the
source code of a c++ GUI application very readable. Because of the c++ template
syntax, document elements that are derived from standard W3C names can appear
within the <> template parameters. The library depends on the c++ 17 and greater
language standard.

To include the library within your project, you simply have to include the
viewManager.hpp header file. This header file encapsulates all of the necessary
api declarations to utilize the rendering system. While the rendering system is
much like a web browser, that is using a document object model, the base system
does not depend on a full web browser but includes its own rendering and font
system.

Platform Support
================
The system is provided to compile programs written once for multiple 
platforms. The vc, g++ and clang compilers are supported.


Windows
-------
To compile programs using the Microsoft Windows visual
studio, the language standard must be set to c++17 or above.
When creating the project, create a windows 32bit or windows 64bit
application. 

As well, additional dependancies are required.
The direct X d2d1 library is required. The freetype
library from freetype.org is also required. When the 
program is running, the freetype.dll must be within
the program or environment search path. The following 
libraries must be linked:

- d2d1.lib
- freetype.lib
- freetype.dll

Linux
-----
To compile programs for linux, the stdc++, m, x11-xcb, xcb-image 
xcb-keysyms, freetype2, and fontconfig libraries must be linked. 
An example of the makefile is listed below.

\code
#CC=clang
CC=g++
CFLAGS=-std=c++17 -Os
INCLUDES=-I/projects/guidom `pkg-config --cflags x11-xcb freetype2 fontconfig`
LFLAGS=`pkg-config --libs x11-xcb freetype2 xcb-image fontconfig`

debug: CFLAGS += -g
debug: guidom.out

release: LFLAGS += -s
release: guidom.out


guidom.out: main.o viewManager.o
        $(CC) -o guidom.out main.o viewManager.o -lstdc++ -lm -lxcb-keysyms $(LFLAGS) 
main.o: main.cpp viewManager.hpp
        $(CC) $(CFLAGS) $(INCLUDES) -c main.cpp -o main.o

viewManager.o: viewManager.cpp viewManager.hpp
        $(CC) $(CFLAGS) $(INCLUDES) -c viewManager.cpp -o viewManager.o

clean:
        rm *.o *.out
\endcode	

Examples
========
Some examples of how to write complete GUI applications are listed below. The
following example is a GUI program that can be compiled for multiple platforms
that displays the message "Hello World" within a window.

Hello World
-----------
\snippet examples.cpp Hello World

The viewManager rendering system depends on the main Viewer object being created. This
object supplies the connection with the target operating system and provides the
root of the document object model. The attributes set here, as well as the tree,
hierarchy dependency, create the inherited attributes when used for rendering.

Document elements can be easily added using the API commands described within
the documentation. Each document entity created is derived from the main
Element base class. This class provides the stream operator <<, append,
appendChild, ingestMarkup, print and printf. By default, the stream operators
such as printf, <<, and print insert the supplied text directly into the textual
data of the referenced element. However, markup that is similar to HTML can lso
be parsed. By setting the Boolean flag element.ingestMarkup = true, information
within the given string passed to these stream routine will parsed the
information for markup. This makes adding elements much easier, but requires a
two phase parse.

Markup Example
--------------
\snippet examples.cpp Markup

The parsing document format is much simpler than HTML but supports the same
basic functionality. The parser is a fast one in that it is specifically coded
for the format. A great feature is that it supports a parser context so that
entity tags can be listed on separate inputs of the stream. This makes the
process of string building much easier as complete tags do not have to be
included into one call. That is the input can be broken apart and on separate
lines for ease of maintenance.

\ref markupInputFormat

UX Control Library
------------------
Creating user interface controls is very easy, The system has several base 
controls included that are derrived from the w3C standard. For example,
text, password, multiline, pushButton, date, and dateTime are included.

\snippet examples.cpp UXcontrols

\see UXcontrols

