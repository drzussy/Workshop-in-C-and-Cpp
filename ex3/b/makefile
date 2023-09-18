tweets: markov_chain.o tweets_generator.o linked_list.o
	gcc markov_chain.o tweets_generator.o linked_list.o -o tweets_generator

linked_list.o: linked_list.c linked_list.h
	gcc -c linked_list.c

markov_chain.o: markov_chain.c markov_chain.h
	gcc -c markov_chain.c linked_list.c

tweets_generator.o: tweets_generator.c
	gcc -c tweets_generator.c

snake: markov_chain.o snakes_and_ladders.o linked_list.o
	gcc markov_chain.o snakes_and_ladders.o linked_list.o -o snakes_and_ladders

snakes_and_ladders.o: snakes_and_ladders.c
	gcc -c snakes_and_ladders.c
