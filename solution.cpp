#include <iostream>
#include <tuple>
#include <stack>
#include <vector>
using namespace std;

/* takeaways
   - we can think of this as a two pointers problem
     - both trees are BST meaning they are sorted
     - so you can actually think them as two sorted vectors
       tree1 = [2,1,4] => {1,2,4} 
       tree2 = [1,0,3] => {0,1,3}
     - so p1 (first pointer) starts with "1" the 
       smallest in tree1 while p2 (second pointer) starts 
       with "3" the biggest in tree2
     - if the target is 5 
       - the first pair {1,3} is not a match
         - the sum 1 + 3 < 5
         - p1 must move to get a bigger number
         - p2 stays put
       - the second pair is {2, 3}
         - this is a match as 2+3=5 
         - both p1 and p2 can move to the next
       - the third pair is {4,1}
         - it's a match again; move both pointers
       - there is no 4th pair as tree1 has run out
 
   - tree traversal
     - we use inorder traversal on tree1 to visit the
       nodes in an ascending order
     - and use reverse inorder traversal on tree2 to
       visit the nodes in a descending order
   
   - exit condition
     - since p1 and p2 might advance at a different pace
       so either tree can run out first even when they
       both have the same number of nodes  

*/

struct Node
{
  int val;
  Node *left;
  Node *right;
  Node(int _val)
  {
    val = _val;
    left = nullptr;
    right = nullptr;
  }
};

class Solution
{
private:
public:
  bool pairExist(Node *tree1, Node *tree2, int target)
  {
    if (tree1 == nullptr || tree2 == nullptr)
      return false;

    /* 
      - for tree traversal 
      - record the path of the traversal 
    */
    stack<Node *> t1, t2;

    /* 
      - pointers to the top of each stack
        used for tree traversal
      - this represents the node we are
        visiting from tree1 and tree2
      - we then form a pair of nodes from 
        tree1 and tree2

    */
    Node *cur1, *cur2;
    /* 
      - keep track of the pairs
      - not really necessary but just
        to show how to find all the
        pairs         
    */
    vector<vector<int>> pairs;

    while (true)
    {
      /* visit the left child to find the smallest node of tree1 */
      while (tree1 != nullptr)
      {
        t1.push(tree1);
        /* inorder traversal */
        tree1 = tree1->left;
      }
      /* visit the right child - do the opposite on tree2 to find the largest */
      while (tree2 != nullptr)
      {
        t2.push(tree2);
        /* reverse inorder traversal */
        tree2 = tree2->right;
      }

      /* exit condition 
         - if either tree running out first we can't
           go any further 
      */
      if (t1.empty() || t2.empty())
        break;

      /* visit the node!
         - start checking node without removing
           them from the stack
      */
      cur1 = t1.top();
      cur2 = t2.top();
      /* found a pair */
      if ((cur1->val + cur2->val == target))
      {
        pairs.push_back({cur1->val, cur2->val});
        //done visiting the nodes
        t1.pop();
        t2.pop();

        /* 
          - inorder for tree1 
            - we done visiting the left, and the node.
            - it's time to visit the right  

        */
        tree1 = cur1->right;
        /* 
          - reverse inorder for tree2 
            - we done visiting the right, and the node.
            - it's time to visit the left  

        */
        tree2 = cur2->left;
      }
      else if (cur1->val + cur2->val < target)
      {
        /* 
          - we need something bigger from tree1
          - it's a BST tree and we are performing
            a inorder traversal so the next node
            from tree1 will be bigger 
        */
        t1.pop();
        tree1 = cur1->right;
      }
      else
      {
        /* 
          - the opposite we need something smaller from
            tree2  
        */
        t2.pop();
        /* reverse inorder */
        tree2 = tree2->left;
      }
    }

    return pairs.size() > 0;
  }
};

/*
  Input: root1 = [2,1,4], root2 = [1,0,3], target = 5
  Output: true
  Explanation: 2 and 3 sum up to 5.
*/

tuple<Node *, Node *, int> testFixture1()
{
  auto *tree1 = new Node(2);
  tree1->left = new Node(1);
  tree1->right = new Node(4);

  auto *tree2 = new Node(1);
  tree2->left = new Node(0);
  tree2->right = new Node(3);

  return make_tuple(tree1, tree2, 5);
}

/*
  Input: root1 = [0,-10,10], root2 = [5,1,7,0,2], target = 18
  Output: false
*/

tuple<Node *, Node *, int> testFixture2()
{
  auto *tree1 = new Node(0);
  tree1->left = new Node(-10);
  tree1->right = new Node(10);

  auto *tree2 = new Node(5);
  tree2->left = new Node(1);
  tree2->left->left = new Node(0);
  tree2->left->right = new Node(2);
  tree2->right = new Node(7);

  return make_tuple(tree1, tree2, 18);
}

void test1()
{
  auto fixture = testFixture1();
  Solution sol;
  cout << "Test 1 - expect to see 1" << endl;
  cout << sol.pairExist(get<0>(fixture), get<1>(fixture), get<2>(fixture));
  cout << endl;
}

void test2()
{
  auto fixture = testFixture2();
  Solution sol;
  cout << "Test 2 - expect to see 0" << endl;
  cout << sol.pairExist(get<0>(fixture), get<1>(fixture), get<2>(fixture));
  cout << endl;
}

main()
{
  test1();
  test2();
  return 0;
}