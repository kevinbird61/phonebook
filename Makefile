CC ?= gcc
CFLAGS_common ?= -Wall -std=gnu99
CFLAGS_orig = -O0
CFLAGS_opt  = -O0

EXEC = phonebook_orig phonebook_opt phonebook_strcp
all: $(EXEC)

SRCS_common = main.c

phonebook_orig: $(SRCS_common) phonebook_orig.c phonebook_orig.h
	$(CC) $(CFLAGS_common) $(CFLAGS_orig) \
		-DIMPL="\"$@.h\"" -o $@ \
		$(SRCS_common) $@.c

phonebook_opt: $(SRCS_common) phonebook_opt.c phonebook_opt.h
	$(CC) $(CFLAGS_common) $(CFLAGS_opt) \
		-DIMPL="\"$@.h\"" -o $@ \
		$(SRCS_common) $@.c

phonebook_strcp: $(SRCS_common) phonebook_strcp.c phonebook_strcp.h
	$(CC) $(CFLAGS_common) $(CFLAGS_opt) \
		-DIMPL="\"$@.h\"" -o $@ \
		$(SRCS_common) $@.c

run: $(EXEC)
	echo 3 | sudo tee /proc/sys/vm/drop_caches
	watch -d -t "./phonebook_orig && echo 3 | sudo tee /proc/sys/vm/drop_caches"

cache-test: $(EXEC)
	echo 1 | sudo tee /proc/sys/vm/drop_caches # Drop the cache
	perf stat --repeat 100 \
		-e cache-misses,cache-references,instructions,cycles \
		./phonebook_orig > /dev/null
	echo 1 | sudo tee /proc/sys/vm/drop_caches # Drop the cache
	perf stat --repeat 100 \
		-e cache-misses,cache-references,instructions,cycles \
		./phonebook_opt > /dev/null
	echo 1 | sudo tee /proc/sys/vm/drop_caches # Drop the cache
	perf stat --repeat 100 \
		-e cache-misses,cache-references,instructions,cycles \
		./phonebook_strcp > /dev/null

cache-record: $(EXEC)
	echo 1 | sudo tee /proc/sys/vm/drop_caches # Drop the cache
	3>perf_orig.log perf stat --repeat 100 \
		-e cache-misses \
		-x cache-misses \
		--log-fd 3 \
		./phonebook_orig > /dev/null
	echo 1 | sudo tee /proc/sys/vm/drop_caches # Drop the cache
	3>perf_opt.log perf stat --repeat 100 \
		-e cache-misses \
		-x cache-misses \
		--log-fd 3 \
		./phonebook_opt > /dev/null
	echo 1 | sudo tee /proc/sys/vm/drop_caches # Drop the cache
	3>perf_strcp.log perf stat --repeat 100 \
		-e cache-misses \
		-x cache-misses \
		--log-fd 3 \
		./phonebook_strcp > /dev/null


output.txt: cache-test calculate
	./calculate

cache.txt: cache-record calculate_cache
	./calculate_cache

plot: output.txt cache.txt
	gnuplot scripts/runtime.gp
	gnuplot scripts/cache.gp

calculate: calculate.c
	$(CC) $(CFLAGS_common) $^ -o $@

calculate_cache: calculate_cache.c
	$(CC) $(CFLAGS_common) $^ -o $@

.PHONY: clean
clean:
	$(RM) $(EXEC) *.o perf.* \
	      	calculate orig.txt opt.txt opt_strCompress.txt output.txt runtime.png \
					calculate_cache perf_orig.log perf_opt.log perf_strcp.log output_cache.txt cache.png
