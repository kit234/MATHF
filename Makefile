#makefile
cc = g++
obj = main.o operation_number.o common.o operation_string.o
exe = MATHF.exe

$(exe):$(obj)
		 $(cc) $(obj) -Wall -o $(exe)
main.o:main.cpp common.h operation.h
		 $(cc) -c $<
common.o:common.cpp common.h
		 $(cc) -c $<
operation_number.o:operation_number.cpp operation.h common.h
		 $(cc) -c $<
operation_string.o:operation_string.cpp operation.h common.h
		 $(cc) -c $<

.PHONY:clean
clean:
	-del $(exe) $(obj)
