#include "memory.h"

FREE freeList;
ALLOC allocList;

#define REQUEST_INTERVAL 10
#define MIN_LEASE 40
#define MAX_LEASE 70
#define MIN_SIZE 50
#define MAX_SIZE 350
#define TIME_LIMIT 1000
#define MEMORY_SIZE 1000

int total_number_requests;         // total number of requests
int number_satisfied;              // number of requests satisfied
int number_unsatisfied;            // number of requests unsatisfied
int smallest_blocksize = MAX_SIZE; // smallest blocksize requested
int largest_blocksize;             // largest blocksize requested
vector<int> blocksize;             // to hold the values of the blocksizes 
float average_blocksize;           // average blocksize requested
int shortest_lease = MAX_LEASE;    // shortest lease duration
int longest_lease;                 // longest lease duration
vector<int> leaseTime;             // to hold the lease times
float average_lease;               // average lease duration
int number_merged;                 // number of times merging was done

int size, lease, mytime;

void dump(){
	cout << "----------------------FREELISTS----------------------\n";

	while (!freeList.empty()) {
		cout << "Start: " << freeList.top().hole.start << " "
		<< "Size: " << freeList.top().hole.size <<endl;
		freeList.pop();
	}

	cout << "----------------------ALLOCLISTS----------------------\n";

	while (!allocList.empty()) {
		cout << "Lease Expiry: " << allocList.top().leaseExpiry << " "
		<< "Start: " << allocList.top().allocated.start << " "
		<< "Size: " << allocList.top().allocated.size << endl;
		allocList.pop();
	}

	cout << endl;
	cout << "Total Number of Requests: " << total_number_requests;
	cout << "\nNumber Satisfied: " << number_satisfied;
	cout << "\nNumber Unsatisfied: " << number_unsatisfied;
	cout << "\nSmallest Blocksize: " << smallest_blocksize;
	cout << "\nLargest Blocksize: " << largest_blocksize;

	for (int i = 0; i < blocksize.size(); i++) average_blocksize = blocksize[i] + average_blocksize;
	average_blocksize = average_blocksize / blocksize.size();

	cout << "\nAverage Blocksize: " << average_blocksize;
	cout << "\nShortest Lease: " << shortest_lease;
	cout << "\nLongest Lease: " << longest_lease;

	for (int i = 0; i < leaseTime.size(); i++) average_lease = leaseTime[i] + average_lease;
	average_lease = average_lease / leaseTime.size();

	cout << "\nAverage Lease: " << average_lease;
	cout << "\nNumber Merged: " << number_merged << endl;
}

int main(){

	srand(time(NULL));

	freeNode p = {{0, 1000}};
	freeList.push(p);

	for (mytime = 0; mytime < TIME_LIMIT; mytime++){

		FREE tmp;

		if (mytime % REQUEST_INTERVAL == 0){
		
			size = rand() % (MAX_SIZE - MIN_SIZE) + MIN_SIZE;
			blocksize.push_back(size);
			if (size <= smallest_blocksize) smallest_blocksize = size;
			if (size > largest_blocksize) largest_blocksize = size;

			lease = rand() % (MAX_LEASE - MIN_LEASE) + MIN_LEASE;
			leaseTime.push_back(lease);
			if (lease < shortest_lease) shortest_lease = lease;
			if (lease > longest_lease) longest_lease = lease;

			while (!freeList.empty() && freeList.top().hole.size < size){
				tmp.push(freeList.top());
				freeList.pop();
			}

			if (freeList.empty()){ // merge holes and try again
				number_merged++;
				while (!tmp.empty()){
					freeNode p = tmp.top();
					tmp.pop();
					if (p.hole.start + p.hole.size == tmp.top().hole.start){
						p.hole.size += tmp.top().hole.size;
						tmp.pop();
						tmp.push(p);
						number_merged++;
					} else freeList.push(p);
				}	
			}
			total_number_requests++;
		}
		
		while (!freeList.empty() && freeList.top().hole.size < size){
			tmp.push(freeList.top());
			freeList.pop();
		}

		if (freeList.empty()){
			freeList = tmp;
		} else {
			freeNode p = {{freeList.top().hole.start+size, freeList.top().hole.size-size}};
			allocNode q = {{freeList.top().hole.start,size}, mytime + lease};
			freeList.pop();
			freeList.push(p);
			allocList.push(q);
			number_satisfied++; // allocated

			while (!tmp.empty()){
				freeList.push(tmp.top());
				tmp.pop();
			}
		}
	}
	// check and seee if a lease has expired
	while (!allocList.empty() && allocList.top().leaseExpiry == mytime){
		freeNode p = {allocList.top().allocated.start, allocList.top().allocated.size};
		freeList.push(p);
		allocList.pop();
		if (allocList.top().leaseExpiry < shortest_lease) shortest_lease = allocList.top().leaseExpiry;
		if (allocList.top().leaseExpiry > longest_lease) longest_lease = allocList.top().leaseExpiry;
	}

	dump();

	return 0;
}
