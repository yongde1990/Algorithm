//写一个函数，输入一个二叉树，树中每个节点存放了一个整数值，函数返回这颗二叉树中相差最大的两个节点间的差值绝对值。
#include<iostream>
#include<stack>
using namespace std;
struct treenode
{
	int value;
	treenode *left;
	treenode *right;
};
//前序非递归
/*
首先把根节点入栈，然后在每次循环中执行以下操作：
此时栈顶元素即为当前的根节点，弹出并打印当前的根节点。
把当前根节点的右儿子和左儿子分别入栈（注意是右儿子先入栈左儿子后入栈，这样的话下次出栈的元素才是左儿子，这样才符合前序遍历的顺序要求：根节点->左儿子->右儿子）。
*/
int sortBeforOfMinMax(treenode *root){
	if (root == NULL){
		return;
	}
	treenode *p = NULL;
	int min = 99999;
	int max = -99999;
	stack<treenode*> st;
	st.push(root);
	while (!st.empty())
	{
		p = st.top();
		st.pop();
		if (p->value > max){ max = p->value; }
		if (p->value < min){ min = p->value; }
		if (p->right) st.push(p->right);
		if (p->left) st.push(p->left);
	}
	return max - min;
}

/*
后序遍历
因为后序遍历的顺序是：左子树->右子树->根节点，于是我们在前序遍历的代码中，当访问完当前节点后，先把当前节点的左子树入栈，再把右子树入栈，这样最终得到的顺序为：根节点->右子树->左子树，刚好是后序遍历倒过来的版本，于是把这个结果做一次翻转即为真正的后序遍历。
*/
int sortAfterOfMinMax(treenode *root){
	if (root == NULL){
		return;
	}
	treenode *p = NULL;
	int min = 99999;
	int max = -99999;
	stack<treenode*> st ;
	stack<treenode*> stOver ;
	st.push(root);
	while (!st.empty())
	{
		p = st.top();
		st.pop();
		stOver.push(p);
		if (p->left) st.push(p->left);
		if (p->right) st.push(p->right);
	}

	while (!stOver.empty())
	{
		p = stOver.top();
		stOver.pop();
		if (p->value > max){ max = p->value; }
		if (p->value < min){ min = p->value; }
	}

	return max - min;
}


/*
中序遍历稍微复杂，使用一个指针p指向下一个待访问的节点，p初始化为根节点。在每次循环中执行以下操作：

如果p非空，则把p入栈，p变为p的左儿子。
如果p为空，说明已经向左走到尽头了，弹出当前栈顶元素，进行访问，并把p更新为其右儿子。
*/
int sortMidMaxMin(treenode* root){
	if (root == NULL){
		return;
	}
	treenode*p = root;
	int max = p->value;
	int min = p->value;
	stack<treenode*> st;
	
	while (p!=NULL || !st.empty())
	{
		if (p != NULL){
			st.push(p);
			p = p->left;
		}
		else{
			p = st.top();
			st.pop();
			if (p->value > max){ max = p->value; }
			if (p->value < min){ min = p->value; }
			p = p->right;
		}
	}
}
