#include <iostream>
#include <list>
#include <fstream>
#include <math.h>

using namespace std;

class Node{
    public:
        Node* l;
        Node* r;
        Node* p;
        string val;
        int info;
        int h;
        int bV;
        
        Node(){
            l = NULL;
            r = NULL;
            p = NULL;
            val = "";
            info = 0;
            h = -1;
        }
        
        ~Node(){
            l = NULL;
            r = NULL;
            p = NULL;
            val = "";
            info = 0;
            h = -1;
        }
};

class AVL{
    private:
    //int size;
    Node* root;
    void rebalance(Node* curr);
    
    void RRRebalance(Node* curr);
    void LLRebalance(Node* curr);
    void LRRebalance(Node* curr);
    void RLRebalance(Node* curr);
    int getHeight(Node* current);
    void setHeight(Node* current);
    //static int compare(string a, string b);
    
    void updateParent(Node* current);   //Check balance factor
    
    void updateParentAll(Node* current);
    
    void recurInsert(Node* tempRoot, string s, int info);
    
    string recurRemove(Node* tempRoot, string s);
    
    static int recurFind(Node* tempRoot, string s);
    
    Node* nodeFind(Node* tempRoot, string s);
    
    //Node* hashNodeFind(string s);
    
    list<string> recurInOrderTraversal(list<string> &allWords, Node* current);
    
    void DFS(Node* current);
    
    public:
    int size;
        int treeSize();
        AVL();
        ~AVL();
        void insert(string s, int info);
        void insertAll(list<string> input);
        int remove(string s);
        int find (string s);
        list<string> findAll(list<string> input);
        list<string> inOrderTraversal();
        void print();
};

/*==============================================================================
AVL Private Functions
==============================================================================*/

int AVL::getHeight(Node* current){
    if(current == NULL){
        return 0;
    }
    return current->h;
}

//Assume not NULL
void AVL::setHeight(Node* current){
    //cout << endl << "Setting height" << endl;
    //cout << "Current Node: " << current->val << endl;
    //cout << "Current's old height: " << current->h << endl;
    //cout << "Current Node's left height: " << getHeight(current->l) << endl;
    //cout << "Current Node's right height: " << getHeight(current->r) << endl;
    int newHeight = 1+ max(getHeight(current->r), getHeight(current->l));
    current->h = newHeight;
    //cout << "Current's new height: " << current->h << endl;
}


//RR rebalance function
void AVL::RRRebalance(Node* curr){
    Node* toMove = curr->r->l;
    Node* newRoot = curr->r;
    newRoot->p = curr->p;
    if(curr->p == NULL){
        root = newRoot;
    }
    else{
        if(curr->p->r == curr){
            //cout << "Current is right child" << endl;
            newRoot->p->r = newRoot;
        }
        else{
            newRoot->p->l = newRoot;
        }
    }
    curr->p = newRoot;
    newRoot->l = curr;
    curr->r = toMove; //May be NULL
    if(toMove != NULL){
        toMove->p = curr;
    }
    setHeight(curr);
    setHeight(curr->p);
}

//LL Rebalance function
void AVL::LLRebalance(Node*curr){
    Node* toMove = curr->l->r;
    Node* newRoot = curr->l;
    newRoot->p = curr->p;
    if(curr->p == NULL){
        root = newRoot;
    }
    else{
        if(curr->p->l == curr){
            //cout << "Current is right child" << endl;
            newRoot->p->l = newRoot;
        }
        else{
            newRoot->p->r = newRoot;
        }
    }
    curr->p = newRoot;
    newRoot->r = curr;
    curr->l = toMove; //May be NULL
    if(toMove != NULL){
        toMove->p = curr;
    }
    setHeight(curr);
    setHeight(curr->p);
}

//LR Rebalance Function
void AVL::LRRebalance(Node*curr){
    RRRebalance(curr->l);
    LLRebalance(curr);
}

//RL rebalance FUnction
void AVL::RLRebalance(Node*curr){
    LLRebalance(curr->r);
    RRRebalance(curr);
}

/*==============================================================================
AVL Rebalance FUnction
==============================================================================*/
void AVL::rebalance(Node* curr){
    //cout << endl << "58: Beginning of rebalance function" << endl;
    //cout << "Current Node: " << curr->val << endl;
    int currBV = curr->bV;
    int rightBV;
    int leftBV;
    if(curr->l != NULL){
        leftBV = curr->l->bV;
    }
    else{
        leftBV = 0;
    }
    if(curr->r != NULL){
        rightBV = curr->r->bV;
    }
    else{
        rightBV = 0;
    }
    if(curr->l != NULL){
        //cout << "79: Left val: " << curr->l->val << endl;
    }
    else{
        //cout << "82: Left val: NULL" << endl;
    }
    //cout << "84: Left balance value: " << leftBV << endl;
    if(curr->r != NULL){
        //cout << "86: Right val: " << curr->r->val << endl;
    }
    else{
        //cout << "89: Right val: NULL" << endl;
    }
    //cout << "Left balance value: " << leftBV << endl;
    //cout << "Right balance value: " << rightBV << endl;
    
    if(currBV == 2 && rightBV >= 0){
        //cout << "R-R Rotation required" << endl;
        RRRebalance(curr);
    }
    else if(currBV == 2 && rightBV < 0){
        //cout << "R-L Rotation required" << endl;

    }
    else if(currBV == -2 && leftBV <= 0){
        //cout << "L-L Rotation required" << endl;

    }
    else if(currBV == -2 && leftBV > 0){
        //cout << "L-R ROtation required" << endl;

    }
    else{
        //cout << "NO rebalancing required" << endl;
    }
}

/*==============================================================================
AVL BalanceFactor Function
==============================================================================*/
int BalanceFactor(Node* current){
    //cout << endl << "FINDING BALANCE FACTOR" << endl;
    if(current == NULL){
        current->bV = 0;
        return 0;
    }
    int left = 0;
    int right = 0;
    if(current->r != NULL){

        right = current->r->h;
    }
    if(current->l != NULL){
        left = current->l->h;
    }
    current->bV = right - left;
    return right - left;
}

/*==============================================================================
AVL UpdateParent Function
==============================================================================*/
void AVL::updateParent(Node* current){
    //cout << endl << "Updating Parent" << endl;
    if(current == NULL){
        return;
    }
    //cout << "Current val: " << current->val << endl;
    int oldHeight = current->h;
    int oldHeightP;
    setHeight(current);
    if(current->p != NULL){
        oldHeightP = current->p->h;
        setHeight(current->p);
    }
    //cout << "current val: " << current->val << endl;
    //cout << "balanceVal: " << BalanceFactor(current) << endl;
    if(BalanceFactor(current) == 2 && BalanceFactor(current->r) >= 0){
        //cout << endl << "RR rebalance" << endl;
        RRRebalance(current);
    }
    else if(BalanceFactor(current) == 2 && BalanceFactor(current->r) < 0){
        //cout << endl << "RL rebalance" << endl;
        RLRebalance(current);
    }
    else if(BalanceFactor(current) == -2 && BalanceFactor(current->l) <= 0){
        //cout << endl << "LL rebalance" << endl;
        LLRebalance(current);
    }
    else if(BalanceFactor(current) == -2 && BalanceFactor(current->l) > 0){
        //cout << endl << "LR rebalance" << endl;
        LRRebalance(current);
    }
    if(getHeight(current) != oldHeight || getHeight(current->p) != oldHeightP){
        //cout << "Height of Current does not == OLD HEIGHT" << endl;
        updateParent(current->p);
    }
    //cout << "Height of Current == OLD HEIGHT" << endl;
}


/*==============================================================================
AVL String COmparator
==============================================================================*/
int compare(string a, string b){
    if(a.size() < b.size()){
        for(unsigned int i = 0; i < a.size(); i++){
            //if current letter in A is less than current letter in B
            //or if we've reached the end of A
            if((a.at(i) < b.at(i)) || ((i + 1) == a.size())){
                return -1;
            }
            else if(a.at(i) > b.at(i)){
                return 1;
            }
            return -1;
        }
    }
    else if(a.size() > b.size()){
        for(unsigned int i = 0; i < b.size(); i++){
            if((a.at(i) < b.at(i)) || ((i + 1) == b.size())){
                return -1;
            }
            else if(a.at(i) > b.at(i)){
                return 1;
            }
            return 1;
        }
    }
    else if(a.size() == b.size()){
        //Checks if both words are the same
        for(unsigned int i = 0; i < a.size(); i++){
            if(a.at(i) < b.at(i)){
                return -1;
            }
            else if(b.at(i) < a.at(i)){
                return 1;
            }
        }
        return 0;
    }
    return 0;
}

/*==============================================================================
AVL Public Functions
==============================================================================*/
//AVL constructor
    AVL::AVL()
    {
        root = NULL;
        size = 0;
    }

//AVL destructor
    AVL::~AVL()
    {
        //Remove all function
    }

/*==============================================================================
AVL getter for Size (Used for Hashmap)
==============================================================================*/
int AVL::treeSize(){
    //scout << endl << "IN treeSize Function" << endl << endl;
    if(root == NULL){
        //cout << "root is NULL" << endl;
        return 0;
    }
    //cout << "root ! NULL " << endl;
    return size;
}

/*==============================================================================
AVL Insert Function
==============================================================================*/
void AVL::insert(string s, int info){
    //cout << endl << "////////////////////INSERTING " << s << endl;
    if(root == NULL){
        //cout << "Root is NULL" << endl;
        //cout << "Input word: " << s << endl;
        root = new Node();
        root->val = s;
        root->h = 1;
        root->info = info;
        size++;
        //cout << "Size: " << size << endl;
        return;
    }else{
        return recurInsert(root, s, info);
    }
}

/*==============================================================================
AVL Insert Helper Function (Allows recursion for insertion)
==============================================================================*/
void AVL::recurInsert(Node* tempRoot, string s, int info){
    //if input word is same as root word
    //cout << endl << "IN RecurINSERT" << endl;
    //cout << "Current root value: " << tempRoot->val << endl;
    //cout << "Current bV: " << tempRoot->bV << endl;
    if(compare(s, tempRoot->val) == 0){
        //cout << "S: " << s << endl;
        //cout << "Current root: " << tempRoot->val << endl;
        //cout << "String already in tree." << endl;
        tempRoot->info = info;
        return;
    }
    //If input word is greater than root word
    if(compare(s, tempRoot->val) == 1){
        //cout << "Input word: " << s << endl;
        //cout << "Input word is greater than root word" << endl;
        if(tempRoot->r == NULL){
            //cout << "Root's right child is NULL" << endl;
            //cout << "Current root: " << tempRoot->val << endl;
            //cout << "Input word: " << s << endl;
            Node* tempr = new Node();
            tempr->h = 1;
            tempr->val = s;
            tempr->info = info;
            tempRoot->r = tempr;
            //cout << "Current root's right child: " << tempRoot->r->val << endl;
            tempr->p = tempRoot->r;
            if(tempr->r == NULL){
                //cout << "NULL!!!!" << endl;
            }
            else{
                //cout << "NOT NULL!!!" << endl;
            }
            size++;
            updateParent(tempr);
            return;
        }
        else{  
            //cout << "Root's right child is NOT NULL" << endl;
            //cout << "Root's right child: ";
            //cout << tempRoot->r->val << endl;
            tempRoot = tempRoot->r;
            recurInsert(tempRoot, s, info);
        }
    }
    //Else if input word is less than root word
    else if(compare(s,tempRoot->val) == -1){
        cout << "Input word is less than root word" << endl;
        if(tempRoot->l == NULL){
            cout << "Root's left child is NULL" << endl;
            Node* templ = new Node();
            templ->h = 1;
            templ->val = s;
            templ->info = info;
            tempRoot->l = templ;
            templ->p = tempRoot->l;
            size++;
            updateParent(templ);
            //cout << "templ val: " << templ->val << endl;
            //cout << "templ parent: " << templ->p->val << endl;
            //cout << "templ parent: " << templ->p->p->val << endl;
            return;
        }
        else{
            tempRoot = tempRoot->l;
            recurInsert(tempRoot, s, info);
        }
    }
}

//AVL insertAll
//void AVL::insertAll(list<string> input){
    
    //while(!input.empty()){
        //string temp = input.front();
        //insert(temp);
        //input.pop_front();
    //}
    //return;
//}

/*==============================================================================
AVL Remove Helper FUnction
==============================================================================*/
Node* AVL::nodeFind(Node* tempRoot, string s){
    //cout << endl << "NODE FIND FUNCTION" << endl;
    if(tempRoot == NULL){
        return NULL;
    }
    //cout << "CUrrent root value: " << tempRoot->val << endl;
    //cout << "INput VALUE: " << s << endl;
    if(tempRoot->val == s){
        //cout << "CURRENT VAL SAME AS INPUT VAL" << endl;
        //cout << "Returning node with this val: " << tempRoot->val << endl;
        return tempRoot;
    }
    else if(compare(s, tempRoot->val) == -1){
        //cout << "INPUT WORD is less than current word" << endl;
        return nodeFind(tempRoot->l, s);
    }
    else{
        //cout << "INPUT WORD is greater than current word" << endl;
        return nodeFind(tempRoot->r, s);
    }
}

/*==============================================================================
AVL Remove Function
==============================================================================*/
int AVL::remove(string s){
    string temp;
    int info;
    //cout << endl << "TOP OF REMOVE" << endl;
    //cout << "Trying to remove: " << s << endl;
    Node* toDelete = nodeFind(root, s);
    //cout << "Node to delete is: " << toDelete->val << endl;
    //cout << "toDelete's right: " << toDelete->r->val << endl;
    if(toDelete == NULL){
        return 0;
    }
    else{
        info = toDelete->info;
    }
    //cout << "toDelete NOT NULL" << endl;
    //BASED ON THE HEIGHTS OF THE CHILDREN
    //THIS CASE, THE LEFT CHILD IS ASSUMED TO MOVE UP
    //cout << "toDelete leftChild height: " << getHeight(toDelete->l) << endl;
    //cout << "toDelete rightChild height: " << getHeight(toDelete->r) << endl;
    if(getHeight(toDelete->l) >= getHeight(toDelete->r)){
        //cout << endl << "toDelete's left child will move up" << endl;
        //cout << "newRoot becomes toDelete's left child" << endl;
        Node* newRoot = toDelete->l;
        if(newRoot == NULL){
            //cout << "YO! NEW ROOT IS NULL YO" << endl;
        }
        ////
        //cout << "check if toDelete == root" << endl;
        ////
        if(root != toDelete){
            //cout << "root is not the same as toDelete" << endl;
            if(toDelete->p->l == toDelete){
                //cout << "toDelete is a left child" << endl;
                toDelete->p->l = newRoot;
            }
            else{
                //cout << "toDelete is a right child" << endl;
                toDelete->p->r = newRoot;
            }
            //cout << "Line 481" << endl;
            if(newRoot != NULL){
                //cout << "toDelete's parent: " << toDelete->p->val << endl;
                //cout << "NewRoot: " << newRoot->val << endl;
                newRoot->p = toDelete->p;
            }
            //cout << "Line 482" << endl;
        }
        else{
            //cout << "toDelete is the root" << endl;
            root = toDelete->l;
        }
        if(newRoot == NULL){
            //cout << "toDelete's has no children" << endl;
            //cout << "Save word that is going to removed into string" << endl;
            temp = toDelete->val;
            //cout << "Update the heights of the tree starting from the parent of the toDelete node" << endl;
            updateParent(toDelete->p);
            //cout << "Finally delete toDelete node" << endl;
            delete toDelete;
            //cout << "Update Size" << endl;
            size--;
            return info;
        }
        else{
            //cout << "newRoot is NOT NULL" << endl;
            if(toDelete->r == NULL){
                //cout << "toDelete's right child is NULL" << endl;
                //cout << "toDelete only has a left child" << endl;
                toDelete->l->p = toDelete->p;
                //cout << "Update parent starting from left child of toDelete" << endl;
                updateParent(toDelete->l);
                //cout << "Save word that is going to be removed into string" << endl;
                temp = toDelete->val;
                //cout << "Finally delete toDelete node" << endl;
                delete toDelete;
                //cout << "Update Size" << endl;
                size--;
                return info;
            }
            else{
                //cout << "toDelete's right child is not NULL" << endl;
                //cout << "Need to make newRoot's rightmost Child the parent of toDelete's right child" << endl;
                Node* toMove = toDelete->r;
                if(toMove == NULL){
                    //cout << "toDelete has no right child" << endl;
                    //cout << "updateParent starting from newRoot" << endl;
                    updateParent(newRoot);
                    //cout << "Save word that is going to be removed into string" << endl;
                    temp = toDelete->val;
                    //cout << "Finally delete toDelete node" << endl;
                    delete toDelete;
                    //cout << "Update size" << endl;
                    size--;
                    return info;
                }
                else {
                    //cout << "newRoot has a right child" << endl;
                    Node* rightMost = newRoot;
                    //cout << "Starting from the right child of the toDelete Node" << endl;
                    //cout << "Iterate down to the right most child" << endl;
                    while(rightMost->r != NULL){
                        rightMost = rightMost->r;
                    }
                    //cout << "Make that rightMostchild's right child be the parent of toDelete's right child" << endl;
                    rightMost->r = toMove;
                    toMove->p = rightMost;
                    //cout << "UpdateParent starting from node that was moved" << endl;
                    //cout << "toMove val: " << toMove->val << endl;
                    updateParent(toMove);
                    //cout << "Save word that is going to be removed into string" << endl;
                    temp = toDelete->val;
                    //cout << "Finally delete toDElete Node" << endl;
                    delete toDelete;
                    size--;
                    return info;
                }
            }
        }
    }
    ///////////////////////////////////////////////////////////////////
    else if(getHeight(toDelete->l) >= getHeight(toDelete->r)){
        //New Root is the right child
        //cout << endl << "toDelete's right child will move up" << endl;
        //newRoot becomes toDelete's right child
        Node* newRoot = toDelete->r;
        ////
        //check if toDelete == root
        ////
        if(root != toDelete){
            //root is not the same as toDelete
            if(toDelete->p->l == toDelete){
                //toDelete is a left child
                toDelete->p->l = newRoot;
            }
            else{
                //toDelete is a right child
                toDelete->p->r = newRoot;
            }
            newRoot->p = toDelete->p;
        }
        else{
            //toDelete is the root
            root = toDelete->r;
        }
        if(newRoot == NULL){
            //toDelete's has no children
            //Save word that is going to removed into string
            temp = toDelete->val;
            //Update the heights of the tree starting from the parent of the
            //toDelete node
            updateParent(toDelete->p);
            //Finally delete toDelete node
            delete toDelete;
            //Update Size
            size--;
            return info;
        }
        else{
            //newRoot is NOT NULL
            if(toDelete->l == NULL){
                //toDelete's left child is NULL
                //toDelete only has a right child
                //Update parent starting from right child of toDelete
                updateParent(toDelete->l);
                //Save word that is going to be removed into string
                temp = toDelete->val;
                //Finally delete toDelete node
                delete toDelete;
                //Update Size
                size--;
                return info;
            }
            else{
                //toDelete's left child is not NULL
                //Need to make newRoot's leftMost Child the parent of toDelete's left child
                Node* toMove = toDelete->l;
                if(toMove == NULL){
                    //toDelete has no left child
                    //updateParent starting from newRoot
                    updateParent(newRoot);
                    //Save word that is going to be removed into string
                    temp = toDelete->val;
                    //Finally delete toDelete node
                    delete toDelete;
                    //Update size
                    size--;
                    return info;
                }
                else {
                     //newRoot has a left child
                    Node* leftMost = newRoot;
                    //Starting from the right child of the toDelete Node
                    //Iterate down to the left most child
                    while(leftMost->l != NULL){
                        leftMost = leftMost->l;
                    }
                    //Make that leftMostchild's left child be the parent of toDelete's left child
                    leftMost->l = toMove;
                    toMove->p = leftMost;
                    //UpdateParent starting from node that was moved
                    updateParent(toMove);
                    //Save word that is going to be removed into string
                    temp = toDelete->val;
                    //Finally delete toDElete Node
                    delete toDelete;
                    size--;
                    return info;
                }
            }
        }
    }
    return info;
}

/*==============================================================================
AVL Find Function
==============================================================================*/
int AVL::find(string s){
    //cout << endl << "In AVL find function" << endl;
    //cout << "LIne 721" << endl;
    if(root == NULL){
        //cout << "ROOT NULL" << endl;
    }
    else{
        //cout << "ROOT NOT NULL" << endl;
    }
    //cout << root << endl;
    return recurFind(root, s);
}

/*==============================================================================
AVL Find Helper Function (Allows recursion for find)
==============================================================================*/
int AVL::recurFind(Node* tempRoot, string s){
    //cout << "In AVL recurFind function" << endl;
    //If tree is empty
    if(tempRoot == NULL){
        //cout << "Current node is NULL" << endl;
        return 0;
    }
    //cout << "Current node is NOT NULL" << endl;
    //If Current word matches input word
    //cout << "Current word: " << tempRoot->val << endl;
    //cout << "Input word; " << s << endl;
    if(tempRoot->val == s){
        //cout << "Current word matches input word" << endl << endl;
        return tempRoot->info;
    }
    //If input word is less than root word
    if(compare(s, tempRoot->val) == -1){
        //cout << "Input word is less than root word" << endl;
        //If left child is not NULL
        if(tempRoot->l != NULL){
            //cout << "Left child is not NULL" << endl;
            //Call find function on left child of current node
            return recurFind(tempRoot->l, s);
        }
    }
    //Else if input word is greater than root word
    else if(compare(s, tempRoot->val) == 1){
        //cout << "Input word is greater than root word" << endl;
        //If right child is not NULL
        if(tempRoot->r != NULL){
            //cout << "Right child is not NULL" << endl;
            //Call find function on right child of current node
            return recurFind(tempRoot->r, s);
        }
    }
    return 0;
}


/*==============================================================================
AVL FindAll Function
==============================================================================*/
list<string> AVL::findAll(list<string> input){
    string temp;
    while(!input.empty()){
        temp = find(input.front());
        if(temp == ""){
            input.clear();
            return input;
        }
    }
    return input;
}

//AVL traverse
list<string> AVL::recurInOrderTraversal(list<string> &allWords, Node* current){
    if(current == NULL){
        return allWords;
    }
    if(current->l != NULL){
        recurInOrderTraversal(allWords, current->l);
    }
    //cout << endl << "Push this value: " << current->val << endl;
    allWords.push_back(current->val);
    //cout << "allWords size: " << allWords.size() << endl;
    if(current->bV >= 2 || current->bV <= -2){
        //cout << "Current val: " << current->val << endl;
        //cout << "Current bV: " << current->bV << endl;
        //cout << "bV out of range" << endl;
        allWords.clear();
        return allWords;
    }
    if(current->r != NULL){
        recurInOrderTraversal(allWords, current->r);
    }
    return allWords;
}

list<string> AVL::inOrderTraversal(){
    list<string> allWords;
    return recurInOrderTraversal(allWords, root);
}

/*==============================================================================
 ==============================================================================
Hashmap class
 ==============================================================================
==============================================================================*/
class Hashmap{
    private:
        AVL** table;
        int tableSize;
    public:
        int hash(string s);
        //Inserts value to corresponding inputted key
        void put(string key, int value);
        //Removes string key from array
        //returns NULL if could not remove
        int remove(string key);
        //returns value corresponding to input key
        //returns 0 if string is not in AVL tree
        int get(string key);
        //returns NULL if could not find ALL input elements
        list<int> getAll(list<string> keys);
        //Constructor?
        Hashmap(int tableSizeInput){
            table = new AVL*[tableSizeInput];
            for(int i = 0; i < tableSizeInput; i++){
                table[i] = NULL;
            }
            tableSize = tableSizeInput;
        }
        ~Hashmap(){
            tableSize = 0;
        }
        double average();
        double standardDeviation();
};

int Hashmap::hash(string s){
    int result = 0;
    for(unsigned int i = 0; i < s.size(); ++i){
        result += ((int)s.at(i)) * pow(31,i);
    }
    //cout << "hash value: " << abs(result % tableSize) << endl;;
    return abs(result % tableSize);
}

void Hashmap::put(string key, int info){
    /*go to positition in array where key should be
     * find node that has key
     * if node found
     *  overwrite value
     * else
     *  insert key with value*/
     //cout << endl << "PUTTING: " << key << endl;
     //cout << "With INFO: " << info << endl;
     int pos = hash(key);
     //cout << "POSITION: " << pos << endl;
     AVL* currentTree = table[pos];
     if (currentTree == NULL) {
        table[pos] = new AVL();
        currentTree = table[pos];
    }
    
    //cout << "Entering AVL INsert function" << endl;
    currentTree->insert(key, info);
    //cout << "Size of CurrentTree: " << currentTree->treeSize() << endl;
}

int Hashmap::get(string key){
    //cout << endl << "GETTING INFO FROM: " << key << endl;
    //go to position in array where key should be
    int pos = hash(key);
    //cout << "Position in array will be: " << pos << endl;
    AVL* currentTree = table[pos];
    if (currentTree == NULL) {
        //cout << "CurrentTree is NULL" << endl;
        table[pos] = new AVL();
        currentTree = table[pos];
    }
    //cout << "currentTree is NOT NULL" << endl;
    //cout << "CurrentTree: " << currentTree << endl;
    //Call find function for key in AVL tree
    int currentCount= currentTree->find(key);
    //cout << "Outside of AVL find function" << endl;
    //cout << "currentCount: " << currentCount << endl;
    //cout << "Size of CurrentTree: " << currentTree->treeSize() << endl;
    return currentCount;
}

int Hashmap::remove(string key){
    //cout << "REMOVING: " << key << endl;
    //go to position in array where key should be
    int pos = hash(key);
    AVL* currentTree = table[pos];
    if (currentTree == NULL) {
        table[pos] = new AVL();
        currentTree = table[pos];
    }
    //Call find function for key in AVL tree
    return currentTree->remove(key);
}

list<int> Hashmap::getAll(list<string> keys){
    list<int> infos;
    while(!keys.empty()){
        int info = get(keys.front());
        if(info == 0){
            infos.clear();
            return infos;
        }
        infos.push_back(info);
        keys.pop_front();
    }
    return infos;
}

double Hashmap::average(){
    //cout << endl << "FINDING AVERAGE" << endl;
    double sizeSum = 0;
    int count = 0;
    //AVL* currentTree = table[214];
    //cout << "Current tree size: " << currentTree->treeSize() << endl;
    for(int i = 0; i < tableSize; i++){
        AVL* currentTree = table[i];
        if(currentTree != NULL){
            sizeSum += currentTree->treeSize();
            count++;
        }
    }
    return sizeSum / count;
}

double Hashmap::standardDeviation(){
    //cout << "Finding standard Deviation" << endl;
    double avg = average();
    double sizeSum = 0;
    int count = 0;
    for(int i = 0; i < tableSize; i++){
        AVL* currentTree = table[i];
        if(currentTree != NULL){
            double currentNum = 0;
            currentNum = currentTree->treeSize() - avg;
            count++;
            sizeSum += pow(currentNum,2);
        }
    }
    return sqrt(sizeSum / (count - 1));
}

int main(int argc, char* argv[]){
    
    if(argc != 2){
        cout << "Error: Incorrect number of arguments" << endl;
        return 0;
    }
    string line;
    list<string> D;
    list<string> D2;
    list<string> D3;
    list<string> D4;
    list<string> D5;
    list<string> D6;
    list<string> D7;
    list<string> D8;
    ifstream myfile (argv[1]);
    if(myfile.is_open()){
        while(getline(myfile,line)){
            //cout << "line: " << line << endl;
        //cout << "Root's right child: ";
                //Enqueues dictionary words onto Queue
            D.push_back(line);
            D2.push_back(line);
            D3.push_back(line);
            D4.push_back(line);
            D5.push_back(line);
            D6.push_back(line);
            D7.push_back(line);
            D8.push_back(line);
        }
        myfile.close();
    }
    //unsigned int tableSize = 500;
    Hashmap map(500);
    //cout << "Testing Put" << endl;
    //INSERT dictionary into Hashmap
    while(!D.empty()){
        string key = D.front();
        map.put(key, map.get(key) + 1);
        D.pop_front();
    }
    
    cout << endl << "Table size: 500" << endl;
    cout << "Average of map: " << map.average() << endl;
    cout << "Standard Deviation of map: " << map.standardDeviation() << endl;
////
    Hashmap map2(1000);
    //cout << "Testing Put" << endl;
    //INSERT dictionary into Hashmap
    while(!D2.empty()){
        string key = D2.front();
        map2.put(key, map2.get(key) + 1);
        D2.pop_front();
    }
    
    cout << endl << "Table size: 1000" << endl;
    cout << "Average of map: " << map2.average() << endl;
    cout << "Standard Deviation of map: " << map2.standardDeviation() << endl;

////
    Hashmap map3(1500);
    //cout << "Testing Put" << endl;
    //INSERT dictionary into Hashmap
    while(!D3.empty()){
        string key = D3.front();
        map3.put(key, map3.get(key) + 1);
        D3.pop_front();
    }
    
    cout << endl << "Table size: 1500" << endl;
    cout << "Average of map: " << map3.average() << endl;
    cout << "Standard Deviation of map: " << map3.standardDeviation() << endl;

////
    Hashmap map4(2000);
    //cout << "Testing Put" << endl;
    //INSERT dictionary into Hashmap
    while(!D4.empty()){
        string key = D4.front();
        map4.put(key, map4.get(key) + 1);
        D4.pop_front();
    }
    
    cout << endl << "Table size: 2000" << endl;
    cout << "Average of map: " << map4.average() << endl;
    cout << "Standard Deviation of map: " << map4.standardDeviation() << endl;

////
    Hashmap map5(2500);
    //cout << "Testing Put" << endl;
    //INSERT dictionary into Hashmap
    while(!D5.empty()){
        string key = D5.front();
        map5.put(key, map5.get(key) + 1);
        D5.pop_front();
    }
    
    cout << endl << "Table size: 2500" << endl;
    cout << "Average of map: " << map5.average() << endl;
    cout << "Standard Deviation of map: " << map5.standardDeviation() << endl;

////
    Hashmap map6(3000);
    //cout << "Testing Put" << endl;
    //INSERT dictionary into Hashmap
    while(!D6.empty()){
        string key = D6.front();
        map6.put(key, map6.get(key) + 1);
        D6.pop_front();
    }
    
    cout << endl << "Table size: 3000" << endl;
    cout << "Average of map: " << map6.average() << endl;
    cout << "Standard Deviation of map: " << map6.standardDeviation() << endl;

////
    Hashmap map7(3500);
    //cout << "Testing Put" << endl;
    //INSERT dictionary into Hashmap
    while(!D7.empty()){
        string key = D7.front();
        map7.put(key, map7.get(key) + 1);
        D7.pop_front();
    }
    
    cout << endl << "Table size: 3500" << endl;
    cout << "Average of map: " << map7.average() << endl;
    cout << "Standard Deviation of map: " << map7.standardDeviation() << endl;

////
    Hashmap map8(4000);
    //cout << "Testing Put" << endl;
    //INSERT dictionary into Hashmap
    while(!D8.empty()){
        string key = D8.front();
        map8.put(key, map8.get(key) + 1);
        D8.pop_front();
    }
    
    cout << endl << "Table size: 4000" << endl;
    cout << "Average of map: " << map8.average() << endl;
    cout << "Standard Deviation of map: " << map8.standardDeviation() << endl;

    return 0;
}
