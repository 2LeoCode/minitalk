NAME =	client\
		server

all: $(NAME)

bonus:
	$(MAKE) bonus -C client_sources
	$(MAKE) bonus -C server_sources
	cp client_sources/client .
	cp server_sources/server .

$(NAME):
	$(MAKE) -C client_sources
	$(MAKE) -C server_sources
	cp client_sources/client .
	cp server_sources/server .

clean:
	$(MAKE) clean -C client_sources
	$(MAKE) clean -C server_sources

fclean:
	$(MAKE) fclean -C client_sources
	$(MAKE) fclean -C server_sources
	rm -f client server

re: fclean all
