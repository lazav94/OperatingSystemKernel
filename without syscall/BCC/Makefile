SRC = ..\*.cpp 
INCLUDES = ..\*.h 
LIBS = ..\*.lib 
INCLUDEPATH = E:\bc31\include;..\;
LIBSPATH = E:\bc31\lib;..\;
TARGET = KernelPa.exe
$(TARGET):	$(SRC) $(INCLUDES) configuration.xmi
	bcc.exe -mh -v -e$(TARGET) -I$(INCLUDEPATH) -L$(LIBSPATH) $(SRC) $(LIBS)
all:	$(TARGET)
clean:
	-del *.obj
	-del $(TARGET)
	-del *.asm
configuration.xmi:	
	configuration.xmi