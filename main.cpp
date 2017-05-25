// 1. 二维数组中的查找
#if 0
#include <iostream>
#include <vector>
using namespace std;

bool Find(int target, vector<vector<int>> array) {
	if (array.empty())
		return false;
	int row = array.size() - 1;	   //行数 - 1
	int col = array[0].size() - 1; // 列数 - 1

	int i = 0, j = col;

	int temp = array[i][j];
	while (i <= row && j >= 0) {
		if (target == array[i][j])
			return true;
		else if (array[i][j] < target) {
			++i;
		}
		else if (array[i][j] > target) {
			--j;
		}
	}
	return false;
}

int main() {
	vector<vector<int>> array = { { 1, 2, 3, 4 }, { 5, 6, 7, 8 }, { 9, 10, 11, 12 }, {10, 14, 15, 16} };
	cout << Find(13, array) << endl;
	return 0;
}
#endif

// 2. 替换空格
#if 0
#include <iostream>
#include <string>
#include <cstdio>
#include <cstdlib>
using namespace std;

void replaceSpace(char *str, int length) {
	if (str == nullptr || length <= 0)
		return;
	int i = 0;
	int NumsOfSpace = 0;
	int originalOflength = 0;
	while (str[i] != '\0') {
		++originalOflength;
		if (str[i] == ' ')
			++NumsOfSpace;
		++i;
	}

	int NewLength = originalOflength + 2 * NumsOfSpace;
	if (NewLength > length)
		return;

	int right = NewLength;			// str[right] = '\0' 表示结束符
	int left = originalOflength;

	while (right > left && left >= 0) {
		if (str[left] == ' ') {
			str[right--] = '0';
			str[right--] = '2';
			str[right--] = '%';
		}
		else {
			str[right--] = str[left];
		}
		--left;
	}

}

int main() {
	char *str = new char[100];

	gets(str);
	
	replaceSpace(str, 50);

	cout << str << endl;
	
	system("pause");
	return 0;
}
#endif

// 3. 从尾到头打印链表
#if 0
#include <iostream>
#include <cstdlib>
#include <vector>
#include <stack>
using namespace std;

struct ListNode{
	int val;
	ListNode *next;
	ListNode(int x) : val(x), next(NULL){}
};

ListNode* generate(vector<int> &nums) {
	if (nums.empty())
		return NULL;
	ListNode *dummy = new ListNode(INT_MIN);
	ListNode *head = new ListNode(nums[0]);
	dummy->next = head;
	for (int i = 1; i < nums.size(); ++i) {
		ListNode *tmp = new ListNode(nums[i]);
		head->next = tmp;
		head = head->next;
	}
	return dummy->next;
}

vector<int> printListFromTailToHead(ListNode* head) {
	vector<int> res = {};
	if (!head)
		return res;
	stack<int> sta;
	ListNode *tmp = head;
	while (tmp != NULL) {
		sta.push(tmp->val);
		tmp = tmp->next;
	}
	while (!sta.empty()) {
		res.push_back(sta.top());
		sta.pop();
	}
	return res;
}

void Print(vector<int>& res) {
	for (int ele : res) {
		cout << ele << " ";
	}
	cout << endl;
}

int main() {
	vector<int> nums = { 3, 1, 5, 2, 7, 9 };
	ListNode* head = generate(nums);
	Print(printListFromTailToHead(head));
	return 0;
}
#endif

// 4. 重建二叉树
#if 0
#include <iostream>
#include <queue>
#include <vector>
using namespace std;

struct TreeNode{
	int val;
	TreeNode *left, *right;
	TreeNode(int x) : val(x), left(NULL), right(NULL){}
};

template <typename Iter>
TreeNode* build(Iter pre_beg, Iter pre_end, Iter vin_beg, Iter vin_end) {
	if (pre_beg == pre_end || vin_beg == vin_end)
		return NULL;
	TreeNode *root = new TreeNode(*pre_beg);
	Iter iter = find(vin_beg, vin_end, *pre_beg);

	int cnt = iter - vin_beg;
	if (iter != vin_end) {
		root->left = build(pre_beg + 1, pre_beg + cnt + 1, vin_beg, iter);
		root->right = build(pre_beg + cnt + 1, pre_end, iter + 1, vin_end);
	}
	return root;
}

TreeNode* reConstructBinaryTree(vector<int> pre, vector<int> vin) {
	if (pre.empty() || vin.empty())
		return NULL;
	return build(pre.begin(), pre.end(), vin.begin(), vin.end());
}

void Print(TreeNode* root) {
	if (!root)
		return;
	Print(root->left);
	Print(root->right);
	cout << root->val << " ";
}

int main() {
	vector<int> pre = { 1, 2, 4, 7, 3, 5, 6, 8 };
	vector<int> vin = { 4, 7, 2, 1, 5, 3, 8, 6 };
	TreeNode* root = reConstructBinaryTree(pre, vin);
	Print(root);
	return 0;
}
#endif

// 5. 用两个栈实现队列
#if 0
#include <iostream>
#include <queue>
#include <stack>
using namespace std;

class Solution{
public:
	void push(int node) {
		while (!stack1.empty()) {
			stack2.push(stack1.top());
			stack1.pop();
		}
		stack1.push(node);
		while (!stack2.empty()) {
			stack1.push(stack2.top());
			stack2.pop();
		}
	}

	int pop() {
		int res = stack1.top();
		stack1.pop();
		cout << res << endl;
		return res;
	}

private:
	stack<int> stack1, stack2;
};

int main() {
	Solution a;
	a.push(2);
	a.push(6);
	a.pop();
	a.push(9);
	int s;
	return 0;
}
#endif

// 6. 旋转数组的最小数字
#if 0
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

// 暴力解决
int minNumberInRotateArray(vector<int> & rotateArray) {
	if (rotateArray.empty())
		return 0;
	sort(rotateArray.begin(), rotateArray.end());
	return rotateArray[0];
}

// 二分法，通过移动left和right，逐渐逼近最小元素
int minNumberInRotateArray1(vector<int>& rotateArray) {
	if (rotateArray.empty())
		return 0;
	int length = rotateArray.size();
	int left = 0, right = length - 1;
	int mid = left;			// 当旋转0个元素时，即数组本身已经排好序，第一个元素就是最小的元素
	while (rotateArray[left] >= rotateArray[right]) {
		if (right - left == 1) {
			mid = right;
			break;
		}
		mid = left + (right - left) / 2;
		if (rotateArray[mid] >= rotateArray[right])
			left = mid;
		else if (rotateArray[mid] <= rotateArray[right])
			right = mid;

	}
	return rotateArray[mid];
}

// 提高二分法的鲁棒性。出现left,right, mid 指向的元素值均相同的情况，则按照顺序查找最小值

int Min(vector<int> &rotateArray, int left, int right) {
	int res = rotateArray[left];
	while (left <= right) {
		if (rotateArray[left] < res)
			res = rotateArray[left];
		++left;
	}
	return res;
}

int minNumberInRotateArray2(vector<int>& rotateArray) {
	if (rotateArray.empty())
		return 0;
	int length = rotateArray.size();
	int left = 0, right = length - 1;
	int mid = left;			// 当旋转0个元素时，即数组本身已经排好序，第一个元素就是最小的元素
	while (rotateArray[left] >= rotateArray[right]) {
		if (right - left == 1) {
			mid = right;
			break;
		}
		mid = left + (right - left) / 2;
		if (rotateArray[left] == rotateArray[right] && rotateArray[left] == rotateArray[mid])
			return Min(rotateArray, left, right);
		if (rotateArray[mid] >= rotateArray[right])
			left = mid;
		else if (rotateArray[mid] <= rotateArray[right])
			right = mid;

	}
	return rotateArray[mid];
}

int main() {
	vector<int> rotateArray = { 1, 1, 1, 1, 0, 1 };
	cout << minNumberInRotateArray2(rotateArray) << endl;
	return 0;
}
#endif

// 7. 菲波那切数列
#if 0
#include <iostream>
#include <vector>
using  namespace std;

int Fibonacci(int n) {
	int res[2] = { 0, 1 };
	if (n < 2)
		return res[n];
	int fibfirst = 0, fibsecond = 1;
	int fibnums = 0;
	for (int i = 2; i <= n; ++i) {
		fibnums = fibfirst + fibsecond;
		fibfirst = fibsecond;
		fibsecond = fibnums;
	}
	return fibnums;
}

int main() {
	cout << Fibonacci(2) << endl;
	return 0;
}


#endif

// 8. 跳台阶
#if 0
#include <iostream>
using namespace std;

int jumpFloor1(int number) {
	if (number <= 0)
		return 0;
	if (number == 1)
		return 1;
	if (number == 2)
		return 2;
	return jumpFloor1(number - 1) + jumpFloor1(number - 2);
}

int jumpFloor(int number) {
	int res[3] = { 0, 1, 2 };
	if (number < 3)
		return res[number];
	int jumpfirst = 1, jumpsecond = 2;
	int jumpres = 0;
	for (int i = 3; i <= number; ++i) {
		jumpres = jumpfirst + jumpsecond;
		jumpfirst = jumpsecond;
		jumpsecond = jumpres;
	}
	return jumpres;
}

int main() {
	cout << jumpFloor1(5) << endl;
	return 0;
}
#endif

// 9. 变态跳台阶
#if 0
#include <iostream>
using namespace std;

int jumpFloorII(int number) {
	int res[3] = { 0, 1, 2 };
	if (number < 3)
		return res[number];
	return jumpFloorII(number - 1) * 2;
}

int jumpFloorII2(int number) {
	int res[3] = { 0, 1, 2 };
	if (number < 3)
		return res[number];
	int jumpnum = 2;
	for (int i = 3; i <= number; ++i) {
		jumpnum *= 2;
	}
	return jumpnum;
}

int main() {
	cout << jumpFloorII2(4) << endl;
	return 0;
}
#endif

// 10. 矩形覆盖
#if 0
#include <iostream>
using namespace std;

int rectCover(int number) {
	int res[3] = { 0, 1, 2 };
	if (number < 3)
		return res[number];
	int first = 1, second = 2;
	int rectnums = 0;
	for (int i = 3; i <= number; ++i) {
		rectnums = first + second;
		first = second;
		second = rectnums;
	}
	return rectnums;
}

int main() {
	cout << rectCover(10) << endl;
	return 0;
}
#endif

// 11. 二进制数中的1
#if 0
#include <iostream>
using namespace std;

int NumberOf1(int n) {
	int cnt = 0;
	while (n) {
		++cnt;
		n = (n - 1) & n;
	}
	return cnt;
}

int main() {
	cout << NumberOf1(7) << endl;
	return 0;
}
#endif

// 12. 数值的整数次方
#if 0
#include <iostream>
#include <cstdlib>
using namespace std;

// 更鲁棒的写法

bool g_InvalidInput = false;

double PowerWithUnsigned(double base, int absExponent) {
	if (absExponent == 0)
		return 1;
	if (absExponent == 1)
		return base;
	double res = PowerWithUnsigned(base, absExponent >> 1);
	res *= res;
	if (absExponent & 0x1 == 1)
		res *= base;
	return res;
}

double Power1(double base, int exponent) {
	g_InvalidInput = false;
	
	if (abs(base - 0.0) < 1e-8 && exponent < 0) {
		g_InvalidInput = true;
		return 0.0;
	}

	unsigned int absExponent = (unsigned int)exponent;
	if (exponent < 0)
		absExponent = (unsigned int)(-exponent);
	double res = PowerWithUnsigned(base, absExponent);
	if (exponent < 0)
		res = 1.0 / res;
	return res;
}

// my
double Power(double base, int exponent) {
	
	if (exponent < 0)
		return 1 / Power(base, abs(exponent)); 

	if (exponent == 0)
		return (double)1;
	if (exponent == 1)
		return base;

	double res = base;

	for (int i = 1; i < exponent; ++i) {
		res *= base;
	}
	return res;
}

int main() {
	cout << Power(2, -3) << endl;
	return 0;
}
#endif

// 13. 调整数组顺序使奇数位于偶数前面
#if 0
#include <iostream>
#include <vector>
using namespace std;

// 可扩展性更强，更优秀的代码,但更新之后，相对位置发生了变化

bool isEven(int n) {

	return (n & 1) == 0;
}

void Reorder(vector<int>& array, bool(*func)(int)) {
	if (array.empty())
		return;
	int length = array.size();
	int left = 0;
	int right = length - 1;
	while (left < right) {
		while (left < right && !func(array[left]))
			++left;
		while (left < right && func(array[right]))
			--right;
		if (left < right) {
			int temp = array[left];
			array[left] = array[right];
			array[right] = temp;
		}//if
	}//while
}

void reOrderArray1(vector<int> &array) {
	if (array.empty())
		return;
	Reorder(array, isEven);
}

// My code
void reOrderArray(vector<int> &array) {
	if (array.empty())
		return;
	int sz = array.size();
	if (sz == 1)
		return;
	int cnt_even = 0;	// 偶数个数
	for (int i = 0; i < sz; ++i) {
		if ((array[i] & 1) == 0)
			++cnt_even;
	}

	int cnt_odd = sz - cnt_even;	// 奇数个数

	// 奇数在前，偶数在后
	vector<int> tmp = array;
	int beg_odd = 0, beg_even = cnt_odd;
	for (int i = 0; i < sz; ++i) {
		if ((tmp[i] & 1) == 0) {	// 偶数
			array[beg_even++] = tmp[i];
		}
		else                        // 奇数
			array[beg_odd++] = tmp[i];
	}

}

// optimization
void reOrderArray2(vector<int> &array) {
	if (array.empty())
		return;
	vector<int> newarray(array);
	int sz = array.size();

	int odd = 0;
	for (int i = 0; i < sz; ++i) {
		if ((array[i] & 1) != 0)	// 奇数
			newarray[odd++] = array[i];
	}

	for (int i = 0; i < sz; ++i) {
		if ((array[i] & 1) == 0)	// 偶数
			newarray[odd++] = array[i];
	}
	array = newarray;
}

// Print
void Print(vector<int>& array) {
	for (auto ele : array) {
		cout << ele << " ";
	}
	cout << endl;
}

int main() {
	vector<int> array = { 4, 7, 9, 8, 6, 3, 1, 5, 2, 11 };
	reOrderArray2(array);
	Print(array);
	return 0;
}
#endif

// 14. 链表倒数第K个结点
#if 0
#include <iostream>
#include <vector>
using namespace std;

struct ListNode {
	int val;
	ListNode *next;
	ListNode(int x) : val(x), next(NULL){}
};

ListNode* generate(vector<int> &nums) {
	if (nums.empty())
		return NULL;
	ListNode* dummy = new ListNode(INT_MIN);

	ListNode* root = new ListNode(nums[0]);
	dummy->next = root;
	int sz = nums.size();
	for (int i = 1; i < sz; ++i) {
		ListNode* temp = new ListNode(nums[i]);
		root->next = temp; 
		root = temp;
	}
	return dummy->next;
}


// my ac codes
ListNode* FindKthToTail(ListNode* pListHead, unsigned int k) {
	if (pListHead == NULL || k == 0)		// note: k == 0也要进行加入判断
		return NULL;
	int length = 0;
	ListNode* tmp = pListHead;
	while (tmp) {
		tmp = tmp->next;
		++length;
	}	
	if (k > length)							// note: k > length则越界，需要进行边界处理
		return NULL;
	int step = length - k;
	ListNode* res = pListHead;
	for (int i = 0; i < step; ++i) {
		res = res->next;
	}
	return res;
}

// optimization
ListNode* FindKthToTail1(ListNode* pListHead, unsigned int k) {
	if (pListHead == NULL || k == 0)
		return NULL;
	ListNode *pAhead = pListHead;
	ListNode *pBhead = pListHead;
	for (int i = 0; i < k - 1; ++i) {
		if (pAhead->next != NULL) {	// Note: 此处判断条件为pAhead->next != NULL,并非pAhead, 因为在循环中用到了pAhead->next,同时							防止越界
			pAhead = pAhead->next;
		}
		else                     // 此时k值大于链表长度，产生超过链表的指针
			return NULL;
	}

	while (pAhead->next != NULL) {	// Note: 此处判断条件为pAhead->next != NULL 时，并非是pAhead,
		pAhead = pAhead->next;
		pBhead = pBhead->next;
	}
	return pBhead;
}

void Print(ListNode* res) {
	if (!res) {
		cout << "fails" << endl;
		return;
	}
	else {
		cout << res->val << endl;
	}
}

int main() {
	vector<int> nums = { 1, 2, 3, 4, 5, 6 };
	Print(FindKthToTail1(generate(nums), 3));
	return 0;
}
#endif

// 15. 翻转链表
#if 0
#include <iostream>
#include <vector>
using namespace std;

struct ListNode{
	int val;
	ListNode* next;
	ListNode(int x) : val(x), next(NULL){}
};

ListNode* generate(vector<int>& nums) {
	if (nums.empty())
		return NULL;
	ListNode* dummy = new ListNode(INT_MIN);
	ListNode* root = new ListNode(nums[0]);
	dummy->next = root;
	for (int i = 1; i < nums.size(); ++i) {
		ListNode* temp = new ListNode(nums[i]);
		root->next = temp;
		root = root->next;
	}
	return dummy->next;
}

ListNode* ReverseList(ListNode* pHead) {
	if (!pHead)
		return NULL;
	ListNode* temp = pHead->next;
	pHead->next = NULL;
	ListNode* tempOfnext;
	while (temp) {
		tempOfnext = temp->next;
		temp->next = pHead;
		pHead = temp;
		temp = tempOfnext;
	}
	return pHead;
}

void Print(ListNode* res) {
	if (!res)
		return;
	while (res) {
		cout << res->val << " ";
		res = res->next;
	}
}

int main() {
	vector<int> nums = { 2, 3 };
	ListNode* root = generate(nums);
	ListNode* res = ReverseList(root);
	Print(res);
	return 0;
}
#endif

// 16. 合并两个排序的链表
#if 0
#include <iostream>
#include <vector>
using namespace std;

struct ListNode{
	int val;
	ListNode* next;
	ListNode(int x) : val(x), next(NULL){}
};

ListNode* generate(vector<int> &nums) {
	if (nums.empty())
		return NULL;
	int sz = nums.size();
	ListNode* dummy = new ListNode(INT_MIN);
	ListNode* root = new ListNode(nums[0]);
	dummy->next = root;
	for (int i = 1; i < sz; ++i) {
		ListNode* temp = new ListNode(nums[i]);
		root->next = temp;
		root = temp;
	}
	return dummy->next;
}

// My Muttimes repair points
ListNode* Merge(ListNode* pHead1, ListNode* pHead2) {
	if (!pHead1)
		return pHead2;
	if (!pHead2)
		return pHead1;

	ListNode* dummy = new ListNode(INT_MIN);
	ListNode* pHead3 = dummy;
	
	while (pHead1 && pHead2) {				// Note: 

		if(pHead1->val <= pHead2->val) {
			pHead3->next = pHead1;
			pHead1 = pHead1->next;
		}
		else if(pHead1->val >= pHead2->val)
		{
			pHead3->next = pHead2;
			pHead2 = pHead2->next;
		}
		pHead3 = pHead3->next;
	}
	if (pHead1)
		pHead3->next = pHead1;
	if (pHead2)
		pHead3->next = pHead2;
	return dummy->next;
}

// Recursion and concise
ListNode* Merge1(ListNode* pHead1, ListNode* pHead2) {
	if (!pHead1)
		return pHead2;
	if (!pHead2)
		return pHead1;
	ListNode* dummy = NULL;
	if (pHead1->val < pHead2->val) {
		dummy = pHead1;
		dummy->next = Merge1(pHead1->next, pHead2);
	}
	else {
		dummy = pHead2;
		dummy->next = Merge1(pHead1, pHead2->next);
	}
	return dummy;
}

void Print(ListNode* res) {
	if (!res)
		return;
	while (res) {
		cout << res->val << " ";
		res = res->next;
	}
}

int main() {
	vector<int> nums1 = { 1, 3, 5 };
	vector<int> nums2 = { 2, 4, 6 };
	ListNode* pHead1 = generate(nums1);
	ListNode* pHead2 = generate(nums2);
	ListNode* res = Merge1(pHead1, pHead2);
	Print(res);
	return 0;
}
#endif

// 17. 树的子结构
#if 0
#include <iostream>
#include <vector>
#include <queue>
using namespace std;

const int flag = INT_MIN;

struct TreeNode{
	int val;
	TreeNode* left, *right;
	TreeNode(int x) : val(x), left(NULL), right(NULL){}
};

bool DosTree1HaveTree2(TreeNode* pRoot1, TreeNode* pRoot2) {
	if (pRoot2 == NULL)
		return true;
	if (pRoot1 == NULL)
		return false;
	if (pRoot1->val != pRoot2->val)
		return false;
	return DosTree1HaveTree2(pRoot1->left, pRoot2->left) && DosTree1HaveTree2(pRoot1->right, pRoot2->right);
}

bool HasSubtree(TreeNode* pRoot1, TreeNode* pRoot2) {
	bool res = false;

	if (pRoot1 && pRoot2) {
		if (pRoot1->val == pRoot2->val)
			res = DosTree1HaveTree2(pRoot1, pRoot2);
		if (!res)
			res = HasSubtree(pRoot1->left, pRoot2);
		if (!res)
			res = HasSubtree(pRoot1->right, pRoot2);
	}
	return res;
}

TreeNode* generate(vector<int> &nums) {
	if (nums.empty())
		return NULL;
	TreeNode* root = new TreeNode(nums[0]);
	int sz = nums.size();
	queue<TreeNode*> que;
	que.push(root);

	for (int i = 1; i < sz; i += 2) {
		TreeNode* left = NULL, *right = NULL;
		TreeNode* temp = que.front();
		que.pop();
		if (nums[i] != flag) {
			left = new TreeNode(nums[i]);
			que.push(left);
		}
		if ((i + 1 < sz) && nums[i + 1] != flag) {
			right = new TreeNode(nums[i + 1]);
			que.push(right);
		}
		temp->left = left;
		temp->right = right;
	}
	return root;
}

int main() {
	vector<int> nums1 = { 5, 3, 9, flag, 4, 7, 6, flag, flag, flag, 8, flag, flag, flag, flag };
	vector<int> nums2 = { 9, 7, flag, flag, 8, flag, flag };
	TreeNode* pRoot1 = generate(nums1);
	TreeNode* pRoot2 = generate(nums2);
	cout << HasSubtree(pRoot1, pRoot2) << endl;
	return 0;
}
#endif 

// 18. 二叉树的镜像
#if 0
#include <iostream>
#include <queue>
#include <vector>
using namespace std;
const int flag = INT_MIN;

struct TreeNode{
	int val;
	TreeNode* left, *right;
	TreeNode(int x) : val(x), left(NULL), right(NULL){}
};

TreeNode* generate(vector<int> &nums) {
	if (nums.empty())
		return NULL;
	TreeNode* root = new TreeNode(nums[0]);
	queue<TreeNode*> que;
	que.push(root);
	
	int sz = nums.size();

	for (int i = 1; i < sz; i += 2) {
		TreeNode* left = NULL, *right = NULL;
		TreeNode* temp = que.front();
		que.pop();

		if (nums[i] != flag) {
			left = new TreeNode(nums[i]);
			que.push(left);
		}
		if (i + 1 < sz && nums[i + 1] != flag) {
			right = new TreeNode(nums[i + 1]);
			que.push(right);
		}
		temp->left = left;
		temp->right = right;
	}
	return root;
}

void Mirror(TreeNode* pRoot) {
	if (!pRoot)
		return;
	if (!pRoot->left && !pRoot->right)
		return;
	if (pRoot->left || pRoot->right) {
		TreeNode* temp;
		temp = pRoot->left;
		pRoot->left = pRoot->right;
		pRoot->right = temp;
	}
	if (pRoot->left)
		Mirror(pRoot->left);
	if (pRoot->right)
		Mirror(pRoot->right);
 
}

int main() {
	vector<int> nums = { 8, 6, 10, 5, 7, 9, 11, flag, flag, flag, flag, flag, flag, flag, flag };
	TreeNode* root = generate(nums);
	Mirror(root);

	return 0;
}

#endif

// 19. 顺时针打印矩阵
#if 0
#include <iostream>
#include <vector>
using namespace std;

vector<int> printMatrix(vector<vector<int>> matrix) {
	if (matrix.empty())
		return vector<int>();
	int rows = matrix.size();
	int cols = matrix[0].size();

	vector<int> res;

	int left = 0, right = cols - 1, top = 0, bottom = rows - 1;
	while (left <= right && top <= bottom) {

		// left to right
		for (int i = left; i <= right; ++i)
			res.push_back(matrix[top][i]);

		// top to bottom
		for (int j = top+1; j <= bottom; ++j)
			res.push_back(matrix[j][right]);

		if (top != bottom)
		// right to left
		for (int i = right - 1; i >= left; --i)
			res.push_back(matrix[bottom][i]);
		
		if (left != right)
		// bottom to top
		for (int j = bottom - 1; j > top; --j)
			res.push_back(matrix[j][left]);
		++left; --right; ++top; --bottom;
	}
	return res;
}

void Print(vector<int> &res) {
	if (res.empty())
		return;
	for (auto ele : res)
		cout << ele << " ";
	cout << endl;
}

int main() {

	vector<vector<int>> matrix = { { 1, 2, 3, 4 }, { 5, 6, 7, 8 }, { 9, 10, 11, 12 }, {13, 14, 15, 16} };
	vector<int> res = printMatrix(matrix);
	Print(res);

	return 0;
}
#endif

// 20. 包含min函数的栈
#if 0
#include <iostream>
#include <stack>
#include <cstdlib>
#include <assert.h>
using namespace std;

// use assert
class Solution{
public:
	void push(int value) {
		data.push(value);
		if (mindata.empty())
			mindata.push(value);
		else if (value < mindata.top())
			mindata.push(value);
	}

	void pop() {
		assert(data.size() > 0 && mindata.size() > 0);
		data.pop();
		mindata.pop();
	}

	int top() {
		assert(data.size() > 0 && mindata.size() > 0);
		return data.top();
	}

	int min() {
		assert(data.size() > 0 && mindata.size() > 0);
		return mindata.top();
	}

private:
	stack<int> data, mindata;
};

// 
class Solution1{
public:

	void push(int value) {
		data.push(value);
		if (mindata.empty())
			mindata.push(value);
		if (value < mindata.top())
			mindata.push(value);
	}

	void pop() {
		if (data.empty())
			return;
		if (data.top() == mindata.top())
			return mindata.pop();
		data.pop();
	}

	int top() {
		if (data.empty())
			throw "this stack is empty.";
		return data.top();
	}

	int min() {
		if (mindata.empty())
			throw "this stack is empty";
		return mindata.top();
	}

private:
	stack<int> data, mindata;
};

int main() {
	Solution1 s;
	s.push(1);
	cout << s.min() << endl;
	s.push(3);
	cout << s.min() << endl;
	s.push(4);
	cout << s.min() << endl;
	s.push(0);
	cout << s.min() << endl;
	return 0;
}

#endif

// 21.栈的压入、弹出序列
#if 0
#include <iostream>
#include <stack>
#include <vector>
using namespace std;

bool IsPopOrder(vector<int> pushV, vector<int> popV) {
	if (pushV.empty() || popV.empty() || pushV.size() != popV.size())
		return false;
	
	int len = pushV.size();
	
	vector<int>::iterator pointTopushV = pushV.begin(), pointTopopV = popV.begin();

	stack<int> s;

	while (pointTopopV != popV.end()) {
		while (s.empty() || s.top() != *pointTopopV) {
			if (pointTopushV == pushV.end())
				break;
			s.push(*pointTopushV);
			pointTopushV++;
		}
		if (s.top() != *pointTopopV)
			break;
		s.pop();
		pointTopopV++;
	}//while
	if (s.empty() && pointTopopV == popV.end())
		return true;
	return false;
}

int main() {
	vector<int> pushV = { 1, 2, 3, 4, 5 }, popV = { 5, 4, 3, 2, 1 };
	cout << IsPopOrder(pushV, popV) << endl;
	return 0;
}

#endif

// 22. 从上往下打印二叉树
#if 0
#include <iostream>
#include <queue>
using namespace std;

const int flag = INT_MIN;

struct TreeNode{
	int val;
	TreeNode *left, *right;
	TreeNode(int x) : val(x), left(NULL), right(NULL){}
};

TreeNode* generate(vector<int> &nums) {
	if (nums.empty())
		return NULL;
	TreeNode* root = new TreeNode(nums[0]);
	queue<TreeNode*> que;
	que.push(root);

	int sz = nums.size();
	for (int i = 1; i < sz; i += 2) {
		TreeNode *left = NULL, *right = NULL;
		TreeNode *temp = que.front();
		que.pop();

		if (nums[i] != flag) {
			left = new TreeNode(nums[i]);
			que.push(left);
		}
		if (i + 1 < sz && nums[i + 1] != flag) {
			right = new TreeNode(nums[i + 1]);
			que.push(right);
		}
		temp->left = left;
		temp->right = right;
	}
	return root;
}


vector<int> PrintFromTopToBottom(TreeNode* root) {
	vector<int> res;
	if (!root)
		return res;
	queue<TreeNode*> que;

	que.push(root);

	while (!que.empty()){
		TreeNode* temp = que.front();

		res.push_back(temp->val);

		if (temp->left)
			que.push(temp->left);
		if (temp->right)
			que.push(temp->right);
	
		que.pop();
	}

	return res;	
}

void Print(vector<int> res) {
	if (res.empty())
		return;
	for (auto ele : res) {
		cout << ele << " ";
	}
	cout << endl;
}

int main() {
	vector<int> nums = { 3, 1, 5, 6, 9, 4, 7, flag, flag, 8, flag, flag, flag, 11, flag };
	TreeNode* root = generate(nums);
	vector<int> res = PrintFromTopToBottom(root);
	Print(res);
	return 0;
}

#endif

// 23. 二叉搜索树的后序遍历序列
#if 0
#include <iostream>
#include <vector>
using namespace std;

bool VerifySquenceOfBST(vector<int> sequence) {
	
	if (sequence.empty())
		return false;
	if (sequence.size() == 1)
		return true;
	vector<int>::iterator beg = sequence.begin(), second_beg = sequence.begin(), end = sequence.end() - 1;

	vector<int> left, right;

	while (*beg < *end) {
		left.push_back(*beg);
		++beg;
	}

	second_beg = beg;

	while (*beg != *end) {
		if (*beg < *end)
			return false;
		right.push_back(*beg);
		++beg;

	}

	bool l = true, r = true;

	if (!left.empty())
		l = VerifySquenceOfBST(left);
	if (!right.empty())
		r = VerifySquenceOfBST(right);

	return l && r;

}


int main() {
	vector<int> sequence = { 7, 4, 6, 5 };
	cout << VerifySquenceOfBST(sequence) << endl;
	return 0;
}
#endif

// 24. 二叉树中和为某一值的路径
#if 0
#include <iostream>
#include <vector>
#include <queue>
const int flag = INT_MIN;

using namespace std;

struct TreeNode{
	int val;
	TreeNode *left, *right;
	TreeNode(int x) : val(x), left(NULL), right(NULL){}
};

TreeNode* generate(vector<int>& nums) {
	if (nums.empty())
		return NULL;
	TreeNode *root = new TreeNode(nums[0]);
	queue<TreeNode*> que;
	que.push(root);

	int sz = nums.size();

	for (int i = 1; i < sz; i += 2) {
		TreeNode* left = NULL, *right = NULL;
		TreeNode* temp = que.front();
		que.pop();

		
		if (nums[i] != flag) {
			left = new TreeNode(nums[i]);
			que.push(left);
		}
		if (i + 1 < sz && nums[i + 1] != flag) {
			right = new TreeNode(nums[i + 1]);
			que.push(right);
		}
		temp->left = left;
		temp->right = right;
	}

	return root;

}

vector<vector<int>> Path(TreeNode* root, int expectNumber, int currentNumber, vector<int>& path, 

	// 将当前节点值，保存在当前遍历路径中
	vector<vector<int>> &res) {
	
	path.push_back(root->val);

	currentNumber += root->val;

	// 若是叶节点且路径和为目标值，则保存当前路径
	if (!root->left && !root->right && currentNumber == expectNumber)
		res.push_back(path);

	if (root->left)
		Path(root->left, expectNumber, currentNumber, path, res);
	if (root->right)
		Path(root->right, expectNumber, currentNumber, path, res);

	//否则，弹出当前节点，返回父节点----回溯到父节点去找另一条路径的过程中，需要首先将当前节点弹出
	path.pop_back();
	return res;
}

vector<vector<int>> FindPath(TreeNode* root, int expectNumber) {
	vector<vector<int>> res;
	if (!root)
		return res;
	vector<int> path;
	return Path(root, expectNumber, 0, path, res);
}

void Print(vector<vector<int>> &res) {
	if (res.empty())
		return;
	int rows = res.size();
	int cols = res[0].size();

	for (int i = 0; i < rows; ++i) {
		cout << "( ";
		for (int j = 0; j < cols; ++j) {
			cout << res[i][j] << " ";
		}
		cout << " )" << endl;
	}
}

int main() {
	vector<int> nums = { 10, 5, 12, 4, 7, flag, flag };
	TreeNode* root = generate(nums);
	vector<vector<int>> res = FindPath(root, 22);
	Print(res);
	return 0;
}
#endif

// 25. 复杂链表的复制
#if 0
#include <iostream>
#include <cstdlib>
#include <vector>
using namespace std;

struct RandomListNode{
	int label;
	RandomListNode *next, *random;
	RandomListNode(int x) : label(x), next(NULL), random(NULL){}
};

RandomListNode* Clonelabel(RandomListNode* pHead) {
	RandomListNode *pNode = pHead;
	while (pNode != NULL) {
		RandomListNode *pCloned;
		pCloned->label = pNode->label;
		pCloned->next = pNode->next;
		pCloned->random = NULL;

		pNode->next = pCloned;
		pNode = pNode->next;
	}
}

RandomListNode* Clonerandom(RandomListNode* pHead) {
	RandomListNode* pNode = pHead;

	while (pNode != NULL) {
		RandomListNode* pCloned = pNode->next;
		if (pNode->random != NULL) {
			pCloned->random = pNode->random->next;
		}
		pNode = pCloned->next;
	}
}

RandomListNode* ReconnectNodes(RandomListNode* pHead) {
	RandomListNode* pNode = pHead;
	RandomListNode* pClonedHead = NULL;
	RandomListNode* pClonedNode = NULL;

	if (pNode != NULL) {
		pClonedHead = pClonedNode = pNode;
		pNode->next = pClonedNode->next;
		pNode = pNode->next;
	}

	while (pNode != NULL) {
		pClonedNode->next = pNode->next;
		pClonedNode = pClonedNode->next;

		pNode->next = pClonedNode->next;
		pNode = pNode->next;
	}
	return pClonedHead;
}


RandomListNode* Clone(RandomListNode* pHead) {
	Clonelabel(pHead);
	Clonerandom(pHead);
	return ReconnectNodes(pHead);
}

RandomListNode* generate(vector<int>& nums) {

}

int main() {


	return 0;
}
#endif

// 26. 二叉搜索树与双向链表
#if 0
#include <iostream>
#include<queue>
#include <vector>
#include <cstdlib>
using namespace std;
const int flag = INT_MIN;
struct TreeNode{
	int val;
	TreeNode*left, *right;
	TreeNode(int x) : val(x), left(NULL), right(NULL){}
};

void ConvertNode(TreeNode* pRootOfTree, TreeNode **last) {
	if (pRootOfTree == NULL)
		return;

	TreeNode* pCurrent = pRootOfTree;

	if (pCurrent->left != NULL)
		ConvertNode(pCurrent->left, last);

	pCurrent->left = *last; 
	if (*last != NULL) {
		(*last)->right = pCurrent;
	}

	*last = pCurrent;

	if (pCurrent->right != NULL)
		ConvertNode(pCurrent->right, last);
}

TreeNode* Convert(TreeNode* pRootOfTree) {
	TreeNode *last = NULL;
	ConvertNode(pRootOfTree, &last);

	TreeNode *pHeadOfList = last;
	while (pHeadOfList != NULL&& pHeadOfList->left != NULL) {
		pHeadOfList = pHeadOfList->left;
	}
	return pHeadOfList;
}

TreeNode* generate(vector<int> &nums) {
	if (nums.empty())
		return NULL;
	TreeNode* root = new TreeNode(nums[0]);
	queue<TreeNode*> que;
	que.push(root);

	int sz = nums.size();
	for (int i = 1; i < sz; i += 2) {
		TreeNode* left = NULL, *right = NULL;
		TreeNode *temp = que.front();
		que.pop();
		if (nums[i] != flag) {
			left = new TreeNode(nums[i]);
			que.push(left);
		}
		if (i + 1 < sz && nums[i + 1] != flag) {
			right = new TreeNode(nums[i + 1]);
			que.push(right);
		}
		temp->left = left;
		temp->right = right;
	}
	return root;
}

void Print(TreeNode* reroot) {
	if (!reroot)
		return;
	cout << reroot->val << ", ";

	Print(reroot->left);
	Print(reroot->right);


}

int main() {
	vector<int> nums = { 10, 6, 14, 4, 8, 12, 16, flag, flag, flag, flag, flag, flag, flag, flag };
	TreeNode* root = generate(nums);
	TreeNode* reroot = Convert(root);
	Print(reroot);
	system("pause");
	return 0;
}
#endif

// 26. sunwei
#if 0
#include <iostream>
using namespace std;

struct TreeNode{
	int val;
	TreeNode *left, *right;
	TreeNode(int x) : val(x), left(NULL), right(NULL){}
};

TreeNode* createTree(){
	TreeNode *T;
	int data;
	cin >> data;
	if (data == 0){
		T = NULL;
	}
	else{
		T = new TreeNode(data);
		T->left = createTree();
		T->right = createTree();
	}
	return T;
}

void convert(TreeNode* root, TreeNode *&last){
	if (!root) return;

	TreeNode *p = root;
	convert(p->left, last);
	//left, last means the one right before the node
	p->left = last;
	if (last != NULL)
		last->right = p;
	//right
	last = p;
	convert(p->right, last);
}

int main()
{
	int n;
	cin >> n;
	while (n--){
		TreeNode *root = createTree();
		TreeNode *last = NULL;
		convert(root, last);
		//now last point to the root
		if (!last) continue;
		while (last->left)
			last = last->left;
		while (last){
			cout << last->val << " ";
			last = last->right;
		}
		cout << endl;
	}
	return 0;
}
#endif

// 27. 字符串的排列----递归法(不考虑重复字符情况)
#if 0
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

void Permutation(string &str, int k, vector<string>& res) {
	if (str.empty())
		return;
	int sz = str.size();

	if (k == sz - 1)
		res.push_back(str);

	for (int i = k; i < sz; ++i) {
		if (i != k && str[i] == str[k])
			continue;
		swap(str[i], str[k]);
		Permutation(str, k + 1, res);
		swap(str[i], str[k]);
	}
}

vector<string> Permutation(string str) {
	if (str.empty())
		return vector<string>();
	vector<string> res;
	Permutation(str, 0, res);
	sort(res.begin(), res.end());
	return res;
}

void Print(vector<string> &res) {
	if (res.empty())
		return;
	for (auto ele : res) {
		cout << ele << " ";
	}
	cout << endl;
}

int main() {
	string str = "abc";
	vector<string> res = Permutation(str);
	Print(res);
	return 0;
}
#endif

// 27.test
#if 0
#include <iostream>
using namespace std;

void Permutation(char *str, char *beg) {
	
	if (*beg == '\0')
		cout << str << endl;
	else {
		for (char *ch = beg; *ch != '\0'; ++ch) {
			char temp = *ch;
			*ch = *beg;
			*beg = temp;

			Permutation(str, beg + 1);

			temp = *ch;
			*ch = *beg;
			*beg = temp;
		}//for
	}//else if
}

void Permutation(char *str) {
	if (str == NULL)
		return;
	Permutation(str, str); //  first str is the string, second str is the begin of string.
}

int main() {
	char str[] = "abb";
	Permutation(str);
	system("pause");
	return 0;
}
#endif

// 28. 数组中出现次数超过一半的数字
#if 0
#include <iostream>
#include <vector>
#include <unordered_map>
using namespace std;

// my
int MoreThanHalfNum_Solution(vector<int> numbers) {
	int sz = numbers.size();
	if (sz < 1)
		return 0;
	if (sz == 1)
		return numbers[0];

	int halfsize = sz / 2;

	unordered_map<int, int> um;

	//create hash
	for (int i = 0; i < sz; ++i) {
		++um[numbers[i]];
	}

	// find the result number
	for (int i = 0; i < sz; ++i) {
		if (um[numbers[i]] > halfsize)
			return numbers[i];
	}
	return 0;
}

bool check(vector<int> numbers, int result) {
	int times = 0;
	for (int i = 0; i < numbers.size(); ++i) {
		if (numbers[i] == result)
			++times;
	}
	if (times * 2 > numbers.size())
		return true;
	else
		return false;
}

// book optimization
int MoreThanHalfNum_Solution1(vector<int> numbers) {
	int sz = numbers.size();
	if (sz <= 1)
		return 0;

	int times = 1;
	int result = numbers[0];

	for (int i = 1; i < sz; ++i) {
		if (times == 0) {
			result = numbers[i];
			times = 1;
		}
		else if (numbers[i] == result) {
			++times;
		}
		else
			--times;
	}
	
	if (check(numbers, result)) {
		return result;
	}
	else
		return 0;
}

int main() {
	vector<int> numbers = { 1, 2, 3, 2, 2, 2, 5, 4, 2 };
	cout << MoreThanHalfNum_Solution1(numbers) << endl;
	return 0;
}

#endif

// 29. 最小的K个数------红黑树处理海量数据排序问题
#if 0
#include <iostream>
#include <vector>
#include <set>
#include <functional>
#include <algorithm>
using namespace std;

typedef multiset<int, greater<int>> intset;
typedef multiset<int, greater<int>>::iterator setiterator;


vector<int> GetLeastNumbers_Solution(vector<int> input, int k) {
	int sz = input.size();
	if (k < 0 || k > sz)
		return vector<int>();
	intset leastNumbers;
	vector<int>::const_iterator iter = input.begin();
	for (; iter != input.end(); ++iter) {
		if (leastNumbers.size() < k)
			leastNumbers.insert(*iter);
		else {
			setiterator iterGreater = leastNumbers.begin();
			if (*iter < *(leastNumbers.begin())) {
				leastNumbers.erase(iterGreater);
				leastNumbers.insert(*iter);
			}//if
		}//else
	}//for
	vector<int> res(leastNumbers.begin(), leastNumbers.end());
	reverse(res.begin(), res.end());
	return res;
}

void Print(vector<int> numbers) {
	if (numbers.empty())
		return;
	for (auto ele : numbers) {
		cout << ele << " ";
	}
	cout << endl;
}

int main() {
	vector<int> numbers = { 4, 5, 1, 6, 2, 7, 3, 8 };
	Print(GetLeastNumbers_Solution(numbers, 3));
	return 0;
}
#endif

// 30. 连续子数组的最大和
#if 0
#include <iostream>
#include <vector>
using namespace std;

int FindGreatestSumOfSubArray(vector<int> array) {
	if (array.empty())
		return 0;
	int sz = array.size();
	if (sz == 1)
		return array[0];
	
	int curSum = 0;
	int greatestSum = INT_MIN;
	for (int i = 0; i < sz; ++i) {
		
		// 如果当前值之和出现负数，则从i重新开始
		if (curSum <= 0)
			curSum = array[i];
		// 继续添加新的元素
		else
			curSum += array[i];

		// 更新最新的最大值
		if (curSum > greatestSum)
			greatestSum = curSum;
	}
	return greatestSum;

}

int main() {
	vector<int> array = { 6, -3, -2, 7, -15, 1, 2, 2 };
	cout << FindGreatestSumOfSubArray(array) << endl;

	return 0;
}
#endif

// 31. 整数中1出现的次数(从1到n整数中1出现的次数)
#if 0
#include <iostream>

using namespace std;

int PowerBase10(unsigned int n) {
	int result = 1;
	for (unsigned int i = 0; i < n; ++i) {
		result *= 10;
	}
	return result;
}

int NumbersOf1(const char *str) {
	if (!str || *str < '0' || *str > '9' || *str == '\0')
		return 0;

	// 首位
	int first = *str - '0';

	// 位数
	unsigned int length = static_cast<unsigned int>(strlen(str));

	if (length == 1 && first == 0)
		return 0;

	if (length == 1 && first > 0)
		return 1;

	//首位是1的个数
	int firstNumberOf1 = 0;
	if (first > 1)
		firstNumberOf1 = PowerBase10(length - 1);
	else if (first == 1)
		firstNumberOf1 = atoi(str + 1) + 1;

	// 第二位是1的个数
	int secondNumberOf1 = first * (length - 1) * PowerBase10(length - 2);

	// 迭代后续位是1的个数
	int recursiveNumberOf1 = NumbersOf1(str + 1);

	return firstNumberOf1 + secondNumberOf1 + recursiveNumberOf1;
	
}

int NumberOf1Between1AndN_Solution(int n) {
	if (n <= 0)
		return 0;
	char str[50];
	sprintf(str, "%d", n);
	return NumbersOf1(str);
}

int main() {
	cout << NumberOf1Between1AndN_Solution(3232) << endl;
	return 0;
}

#endif