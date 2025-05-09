#include <lib.h>

#define os_assert(cond, err, args...)                                                              \
	do {                                                                                       \
		test_count++;                                                                      \
		if (!(cond)) {                                                                     \
			user_halt("^@^@^ERROR^#^#^Checkpoint #%d: " err "\n", test_count, args);   \
		} else {                                                                           \
			debugf("Passed #%2d: " #cond "\n", test_count);                            \
		}                                                                                  \
	} while (0)

static int test_count = 0;

static void os_ok() {
	debugf("^@^@^OSTEST_OK^#^#^\n");
}

int main() {
	int r, i;
	r = shm_free(3);
	os_assert(r == -15,
		  "you close a shm which has not been opened ever, return %d, expected -15", r);
	for (i = 1; i <= 8; i++) {
		r = shm_new(i);
		os_assert(r == i - 1, "fail to create the #%d shm, return %d, expected %d", i, r,
			  i - 1);
	}
	r = shm_new(4);
	os_assert(r == -14,
		  "you open a shm when all eight shms has been opened, return %d, "
		  "expected -14",
		  r);

	for (i = 0; i < 4; i++) {
		r = shm_free(i * 2);
		os_assert(!r, "fail to free shm#%d, return %d", i * 2, r);
	}

	for (i = 0; i < 4; i++) {
		r = shm_free(i * 2);
		os_assert(r == -15, "you free the closed shm#%d, return %d, expected -15", i * 2,
			  r);
		shm_new(2);
	}

	shm_free(5); // The only freed shm
	r = shm_new(8);
	os_assert(r == 5, "fail to create the shm#5 which is the only no-open shm, return %d", r);

	for (int i = 0; i < 8; i++) {
		shm_free(i);
	}

	shm_new(8);

	u_int envid = syscall_getenvid();
	void *addr = (void *)0x500000;
	while (syscall_mem_alloc(envid, addr, 0) != -4) {
		addr += 4096;
	}

	// Now we have no pages, shm #0 has 8 pages
	r = shm_new(1);
	os_assert(r == -4,
		  "you create a shm when no physical pages available, return %d, expect -4", r);

	shm_free(0);
	r = shm_new(7);
	os_assert(r >= 0, "maybe you forgot to free pages when doing shm_free", r);

	shm_free(r);
	// Now we have 8 pages available
	for (i = 0; i < 8; i++) {
		r = shm_new(1);
		os_assert(r >= 0,
			  "do not set the 'open' field if you cannot find enough available "
			  "pages, return %d, expected >= 0",
			  r);
	}
	for (i = 0; i < 8; i++) {
		r = shm_free(i);
		os_assert(r == 0, "cannot free the shm, returned %d", r);
	}

	// Use 4 pages!
	r = shm_new(4);
	os_assert(
	    r == 0,
	    "cannot new a shm with 4 pages when we have 8 pages available, return %d, expected 0",
	    r);

	r = shm_new(5); // cannot assign pages
	os_assert(r == -4,
		  "you create a shm with 5 pages when we have only 4 pages available, return %d, "
		  "expected -4",
		  r);

	// So, we have 4 pages now
	for (int i = 4; i < 8; i++) {
		r = shm_new(1);
		os_assert(r > 0,
			  "you shall free the allocated pages at shm_new if you found there were "
			  "no enough pages available, returned %d, expected > 0",
			  r);
	}

	// Now we have no pages!
	r = shm_new(1);
	os_assert(r == -4,
		  "maybe you do page_free twice, check the page_decref!, shm_new returned %d when "
		  "no pages available",
		  r);

	os_ok();

	return 0;
}

#undef os_assert
