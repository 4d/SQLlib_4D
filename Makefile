all: lib4d_sql/lib4d_sql.a testLib4d/testLib4d


lib4d_sql/lib4d_sql.a:
	@(cd lib4d_sql && $(MAKE))
testLib4d/testLib4d:lib4d_sql/lib4d_sql.a
	@(cd testLib4d && $(MAKE))
	
test:
	./testLib4d/testLib4d
clean:
	@(cd lib4d_sql && $(MAKE) $@)
	@(cd testLib4d && $(MAKE) $@)
