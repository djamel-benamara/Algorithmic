CC=g++ -std=c++17
#FLAGS= -W -Wall -lm 
SRC= apb.cpp 
OBJ=$(SRC:%.c=%.o)

apb:	$(OBJ) eleve.hpp fac.hpp 
		$(CC) $^ -o $@ $(FLAGS) 

%.o:	%.c
	$(CC) -c -o $@ $^ $(FLAGS) 

clean:	
	rm -f apb
	
	
