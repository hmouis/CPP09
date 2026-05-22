Name= RPN

CC= c++ 
CFLAGS= -Wall -Wextra -Werror -std=c++98
src= main.cpp RPN.cpp
obj= $(src:.cpp=.o)
 
all: $(Name)

$(Name): $(obj)
	$(CC) $(CFLAGS) -o $@ $^

%.o: %.cpp
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(obj)

fclean:clean
	rm -f $(Name)

re: fclean all