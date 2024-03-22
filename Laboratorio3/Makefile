lab3:		lab3.c string arraydin dynamiclib.so
			gcc lab3.c -o lab3 -Wall -Werror -pedantic
string:	 	string.c
			gcc string.c -o string -Wall -Werror -pedantic
arraydin:	arraydin.c
			gcc arraydin.c -o arraydin -Wall -Werror -pedantic
dynamiclib.so:	dynamiclib.c
			gcc -fPIC -shared dynamiclib.c -o dynamiclib.so -Wall -Werror -pedantic
.PHONY:		clean
clean:
			rm -rf *.o *.so string arraydin lab3
