#include <vector>
using namespace std;


bool containsDuplicate(vector<int>& nums) {

	for (unsigned int i = 0; i < nums.size(); i++) {
		for (unsigned int n = 1; n < nums.size(); n++) {
			if (nums[i] == nums[n] && i != n) {
				return true;
			}
		}
	}

	return false;
}
