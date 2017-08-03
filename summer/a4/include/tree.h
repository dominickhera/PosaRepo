#ifndef STUDENT_TREE_API_
#define STUDENT_TREE_API_

#define TAXABLE 1
#define NONTAXABLE 0
#define TAX_TYPE unsigned char
// #include "balancedTreeAPI.h"
 #include <stdio.h>
 #include <stdlib.h>
 #include <string.h>

/*You may add anything to this .h file that you need to add to your tree ADT*/

//YOU MUST LEAVE THESE TYPEDEFS AS IS. 
/**typedef for struct name*/
typedef struct BalancedBinTreeNode TreeNode;

/**typedef for struct name*/
typedef struct BalancedBinTree Tree;




/*complete the struct definitions.  You can change the existing parts if you wish.
*/
struct BalancedBinTree {
  //define your tree here.  You can change these if you need to but your tree must be abstract.
    TreeNode *root; ///< pointer to generic data that is to be stored in the tree
    int (*compareFP) (void *data1, void *data2); ///< function pointer to a comparison function for the purpose of inserting and deleting elements
    void (*destroyFP) (void *data); ///< function pointer to a function to free a single pointer that is deleted from the tree
    void *(*copyFP)(void *toBeCopy); ///< function pointer to a function that copies pointer data

  };



struct BalancedBinTreeNode{
    void *proID; ///< pointer to generic data that is to be stored in the heap
    void *prodName;
    void *publisher;
    void *genre;
    TAX_TYPE taxType;
    void *price;
    // void *quantity

    TreeNode *left; ///< pointer to left tree node of current node. Null if empty.
    TreeNode *right; ///< pointer to right tree node of current node. Null if empty.
    
    //Add additional structure elements here
    int height;
    int quantity;
};

//add function prototypes as necessary
int balanceHeight(TreeNode * node);
int getHeight(TreeNode *node);
TreeNode * balanceTreeNode(TreeNode * node);
void balanceTree(Tree *theTree);
TreeNode * leftRotation(TreeNode * node);
TreeNode * rightRotation(TreeNode * node);
TreeNode * leftRightRotation(TreeNode * node);
TreeNode * rightLeftRotation(TreeNode * node);
void printData(void * data);
int compareFunction(void *first,void *second);
void *copyFunction(void *toBeCopy);
int hashData(size_t hashSize, char * dataKey);
void stockCheck(TreeNode *node);
void inorder(TreeNode *node);
void preorder(TreeNode *node);
void postorder(TreeNode *node);


#endif
