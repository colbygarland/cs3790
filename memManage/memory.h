#include <cstdlib>
#include <iostream>
#include <queue>
#include <time.h>

using namespace std;

struct range {
	int start; // the starting address of the range
	int size; // size of the range
};

struct freeNode {
	struct range hole;
};

struct compare_free {
	bool operator()(freeNode &a, freeNode &b) {
	return a.hole.start > b.hole.start;
	}
};

struct allocNode {
	struct range allocated;
	int leaseExpiry; // time at which this block will be returned to free list
};

struct compare_alloc {
	bool operator()(allocNode &a, allocNode &b) {
	return a.leaseExpiry > b.leaseExpiry;
	}
};

typedef priority_queue<freeNode, vector<freeNode>,compare_free> FREE;
typedef priority_queue<allocNode, vector<allocNode>,compare_alloc> ALLOC;
