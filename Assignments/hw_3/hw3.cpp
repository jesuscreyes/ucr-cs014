#include <iostream>
#include <list>
#include <fstream>

using namespace std;

class Node{
    public:
        Node* l;
        Node* r;
        Node* p;
        string val;
        int h;
        int bV;
        
        Node(){
            l = NULL;
            r = NULL;
            p = NULL;
            val = "";
            h = -1;
        }
        
        ~Node(){
            l = NULL;
            r = NULL;
            p = NULL;
            val = "";
            h = -1;
        }
};

class AVL{
    private:
    
    Node* root;
    int size;

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
    
    void recurInsert(Node* tempRoot, string s);
    
    string recurRemove(Node* tempRoot, string s);
    
    static string recurFind(Node* tempRoot, string s);
    
    Node* nodeFind(Node* tempRoot, string s);
    
    list<string> recurInOrderTraversal(list<string> &allWords, Node* current);
    
    void DFS(Node* current);
    
    public:
        AVL();
        ~AVL();
        void insert(string s);
        void insertAll(list<string> input);
        string remove(string s);
        string find (string s);
        list<string> findAll(list<string> input);
        list<string> inOrderTraversal();
        void outputSize();
        void print();
};

/*==============================================================================
AVL Private Functions
==============================================================================*/

void AVL::outputSize(){
    cout << "SIZE: " << size << endl;
}

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

//rebalance
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

//int BalanceFactor FUnction
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

//updateParent
//IN CLASS UPDATE PARENT

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


//String Comparison
//int AVL::compare(string a, string b){
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

//AVL insert
void AVL::insert(string s){
    //cout << endl << "////////////////////INSERTING " << s << endl;
    if(root == NULL){
        //cout << "Root is NULL" << endl;
        //cout << "Input word: " << s << endl;
        root = new Node();
        root->val = s;
        root->h = 1;
        size++;
        return;
    }
    //cout << "Root is not NULL" << endl;
    recurInsert(root, s);
}

/*==============================================================================
AVL Insert Helper Function (Allows recursion for insertion)
==============================================================================*/



void AVL::recurInsert(Node* tempRoot, string s){
    //if input word is same as root word
    //cout << endl << "IN RecurINSERT" << endl;
    //cout << "Current root value: " << tempRoot->val << endl;
    //cout << "Current bV: " << tempRoot->bV << endl;
    if(compare(s, tempRoot->val) == 0){
        //cout << "S: " << s << endl;
        //cout << "Current root: " << tempRoot->val << endl;
        //cout << "String already in tree." << endl;
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
            recurInsert(tempRoot, s);
        }
    }
    //Else if input word is less than root word
    else if(compare(s,tempRoot->val) == -1){
        //cout << "Input word is less than root word" << endl;
        if(tempRoot->l == NULL){
            //cout << "Root's left child is NULL" << endl;
            Node* templ = new Node();
            templ->h = 1;
            templ->val = s;
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
            recurInsert(tempRoot, s);
        }
    }
}

//AVL insertAll
void AVL::insertAll(list<string> input){
    
    while(!input.empty()){
        string temp = input.front();
        insert(temp);
        input.pop_front();
    }
    return;
}

//AVL remove
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

string AVL::remove(string s){
    string temp;
    //cout << endl << "TOP OF REMOVE" << endl;
    //cout << "Trying to remove: " << s << endl;
    Node* toDelete = nodeFind(root, s);
    //cout << "Node to delete is: " << toDelete->val << endl;
    //cout << "toDelete's right: " << toDelete->r->val << endl;
    if(toDelete == NULL){
        return string();
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
            return temp;
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
                return temp;
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
                    return temp;
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
                    return temp;
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
            return temp;
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
                return temp;
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
                    return temp;
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
                    return temp;
                }
            }
        }
    }
    return temp;
}


//AVL removeAll

//AVL find
string AVL::find(string s){
    return recurFind(root, s);
}

/*==============================================================================
AVL Find Helper Function (Allows recursion for find)
==============================================================================*/
string AVL::recurFind(Node* tempRoot, string s){
    //If tree is empty
    if(tempRoot == NULL){
        //cout << "Current node is NULL" << endl;
        return string();
    }
    //cout << "Current node is NOT NULL" << endl;
    //If Current word matches input word
    //cout << "Current word: " << tempRoot->val << endl;
    //cout << "Input word; " << s << endl;
    if(tempRoot->val == s){
        //cout << "Current word matches input word" << endl << endl;
        return tempRoot->val;
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
    return string();
}


//AVL findAll
list<string> AVL::findAll(list<string> input){
    string temp;
    while(!input.empty()){
        temp = find(input.front());
        if(temp == ""){
            input.clear();
            return input;
        }
        else{
            return input;
        }
    }
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
    cout << "SIZE: " << size << endl;
    return recurInOrderTraversal(allWords, root);
}

//AVL print
void AVL::print(){

    DFS(root);

    return;
}

void AVL::DFS(Node* current){
    cout << current->val << " " << current->bV << endl;
    if(current->l != NULL){
        DFS(current->l);
    }
    if(current->r != NULL){
        DFS(current->r);
    }
}

class Test{
    
    public:
    void testInsert(list<string> D);
    void testInsertAll(list<string> D);
    void testFind(list<string> D);
    void testRemove(list<string> D);
    void testFindAll(list<string> D);
    void testInOrderTraversal(list<string> D);

};

//test insert
void Test::testInsert(list<string> D){
    AVL testTree;
    cout << "Testing Insert" << endl;
    //INSERT dictionary into AVL tree
    //cout << "D size: " << D.size() << endl;
    while(!D.empty()){
        string temp = D.front();
        testTree.insert(temp);
        D.pop_front();
    }
    
    //testTree.insert("parlour");
    //testTree.insert("lawyer");
    //testTree.insert("athletics");
    //testTree.insert("magazine");
    //testTree.insert("wire");
    //testTree.insert("alarm");
    //testTree.insert("taxi");
    //testTree.insert("tent");
    //testTree.insert("rebel");
    
    //DO inOrderTraversal and check that all balance values are in range:
    // -2 < balVal < 2
    //if Balance value is ever out of range, cout ERROR
    list<string> orderList;
    
    //testTree.outputSize();
    orderList = testTree.inOrderTraversal();
    
    //cout << "orderList size: " << orderList.size() << endl;
    
    if(orderList.empty()){
        cerr << "ERROR: testInsert: tree is unbalanced" << endl;
    }
}

//testInsertAll
void Test::testInsertAll(list<string> D){
    AVL testTree;
    cout << "Testing insertAll" << endl;
    testTree.insertAll(D);

    list<string> orderList;
    
    orderList = testTree.inOrderTraversal();
    
    if(orderList.empty()){
        cerr << "ERROR: testInsertAll" << endl;
    }
}

//testFind
void Test::testFind(list<string> D){
    AVL testTree;
    cout << "Testing Find" << endl;
    //INSERT dictionary into AVL tree
    while(!D.empty()){
        string temp = D.front();
        testTree.insert(temp);
        D.pop_front();
    }
    string temp;
    temp = testTree.find("calif");
    if(temp == ""){
        cerr << "Error: testFind" << endl;
    }
    temp = testTree.find("calla");
    if(temp == ""){
        cerr << "Error: testFind" << endl;
    }
    temp = testTree.find("saith");
    if(temp == ""){
        cerr << "Error: testFind" << endl;
    }
    temp = testTree.find("vapor");
    if(temp == ""){
        cerr << "Error: testFind" << endl;
    }
    
    temp = testTree.find("california");
    if(temp != ""){
        cerr << "Error: testFind" << endl;
    }
    temp = testTree.find("call");
    if(temp != ""){
        cerr << "Error: testFind" << endl;
    }
    temp = testTree.find("saiht");
    if(temp != ""){
        cerr << "Error: testFind" << endl;
    }

    list<string> orderList;
    
    orderList = testTree.inOrderTraversal();
    
    if(orderList.empty()){
        cerr << "ERROR: testFind" << endl;
    }
}

//testFindAll
void Test::testFindAll(list<string> D){
    AVL testTree;
    cout << "Testing FindAll" << endl;
    //INSERT dictionary into AVL tree
    while(!D.empty()){
        string temp = D.front();
        testTree.insert(temp);
        D.pop_front();
    }
    
    list<string> temp;
    temp.push_front("abaca");
    temp.push_front("twins");
    temp.push_front("toffy");
    temp.push_front("often");
    temp.push_front("palea");
    temp.push_front("giddy");
    temp.push_front("yummy");
    
    if(testTree.findAll(temp).empty()){
        cerr << "Error:findAll" << endl;
    }
    
    temp.push_front("yabadabadoo");
    
    if(!testTree.findAll(temp).empty()){
        cerr << "Error: findAll" << endl;
    }
    
    list<string> orderList;
    
    orderList = testTree.inOrderTraversal();
    
    if(orderList.empty()){
        cerr << "ERROR: findAll" << endl;
    }
}

//testRemove
void Test::testRemove(list<string> D){
    AVL testTree;
    cout << "Testing Remove" << endl;
    //INSERT dictionary into AVL tree
    while(!D.empty()){
        string temp = D.front();
        testTree.insert(temp);
        D.pop_front();
    }
    
    testTree.remove("bongo");
    testTree.remove("favor");
    testTree.remove("saint");
    testTree.remove("ember");
    testTree.remove("torso");
    testTree.remove("torso");
    testTree.remove("wings");
    testTree.remove("chewy");
    
    //DO inOrderTraversal and check that all balance values are in range:
    // -2 < balVal < 2
    //if Balance value is ever out of range, cout ERROR
    list<string> orderList;
    
    orderList = testTree.inOrderTraversal();
    
    if(orderList.empty()){
        cerr << "ERROR: testRemove" << endl;
    }
}

//testInOrderTraversal
void Test::testInOrderTraversal(list<string> D){
    cout << "Testing inOrderTraversal" << endl;
    AVL testTree;
    while(!D.empty()){
        string temp = D.front();
        testTree.insert(temp);
        D.pop_front();
    }
    
    list<string> orderList;
    
    orderList = testTree.inOrderTraversal();
    
    while(!orderList.empty()){
        string temp2 = orderList.front();
        orderList.pop_front();
        if(!orderList.empty()){
            if(compare(temp2, orderList.front()) != -1){
                cerr << "Error: testInOrderTraversal" << endl;
            }
        }
    }
}

int main(int argc, char* argv[]){
    
    
    
    if(argc != 2){
        cout << "Error: Incorrect number of arguments" << endl;
        return 0;
    }
    
    string line;
    list<string> D;
    ifstream myfile (argv[1]);
    if(myfile.is_open()){
        while(getline(myfile,line)){
            //cout << "line: " << line << endl;
        //cout << "Root's right child: ";
                //Enqueues dictionary words onto Queue
            D.push_back(line);
        }
        myfile.close();
    }

///////LIST OF TESTS///////
    Test uTest;
    cout << endl;
    //testInsert
    uTest.testInsert(D);
    
    //testInsertAll
    //uTest.testInsertAll(D);
    
    //testFind
    //uTest.testFind(D);
    
    //testRemove
    //uTest.testRemove(D);
    
    //testFindAll
    //uTest.testFindAll(D);
    
    //testInOrderTraversal
    //uTest.testInOrderTraversal(D);
    
    cout << endl << "Finished test" << endl;
    
    return 0;
}
