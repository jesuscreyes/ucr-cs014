string AVL::recurRemove(Node* tempRoot, string s){
    string temp;
    //cout << endl << "Beginning of recurRemove function" << endl;
    if(tempRoot == NULL){
        return string();
    }
    //cout << "Current node is not NULL" << endl;
    //If current word matches input word
    //cout << "Current word: " << tempRoot->val << endl;
    if(tempRoot->p != NULL){
        //cout << "Current parent: " << tempRoot->p->val << endl;
    }
    //cout << "Inputword: " << s << endl;
    if(tempRoot->val == s){
        //cout << "Current word matches input word" << endl;
        temp = tempRoot->val;
        if(tempRoot->p != NULL){
            //cout << "Current node's parent is NOT NULL" << endl;
            //cout << "Current node's parent: " << tempRoot->p->val << endl;
            if(tempRoot->p->l == tempRoot){
                //cout << "Current node is left child of parent" << endl;
                //cout << "Current node's parent: " << tempRoot->p->val << endl;
                if(tempRoot->r != NULL){
                    //cout << "Right child" << endl;
                    if(tempRoot->l != NULL){
                        //cout << "Right child and Left child" << endl;
                        if(tempRoot->r->l != NULL){
                            //cout << "Current node's right child's left child is NOT NULL" << endl;
                            Node* tempNode = tempRoot->r;
                            //While loop iterates through all left children
                            while(tempNode->l != NULL){
                                tempNode = tempNode->l;
                            }
                            tempNode->l = tempRoot->l;
                            tempRoot->l->p = tempNode;
                            //Current Node's left child now properly attached
                            tempRoot->l = NULL;
                            //Current Node disconnected from left child
                            tempRoot->r->p = tempRoot->p;
                            //Current node's right child's parent is now
                            //CUrrent node's parents
                            tempRoot->p->l = tempRoot->r;
                            //Current Node's parent's left child is now
                            //Current Node's right child
                            tempRoot->r = NULL;
                            updateParent(tempRoot->p);
                            //Current Node disconnected to right child
                            tempRoot->p = NULL;
                            temp = tempRoot->val;
                            delete tempRoot;
                            size--;
                            return temp;
                            //Current Node disconnected from parent
                        }
                        else{
                            //cout << "Current Node's right child's left child is NULL" << endl;
                            tempRoot->l->p = tempRoot->r;
                            tempRoot->r->l = tempRoot->l;
                            tempRoot->l = NULL;
                            tempRoot->r->p = tempRoot->p;
                            tempRoot->p->l = tempRoot->r;
                            tempRoot->r = NULL;
                            updateParent(tempRoot->p);
                            tempRoot->p = NULL;
                            temp = tempRoot->val;
                            delete tempRoot;
                            size--;
                            return temp;
                        }
                    }
                    else{
                        //cout << "Right child, no Left child" << endl;
                        tempRoot->r->p = tempRoot->p;
                        tempRoot->p->l = tempRoot->r;
                        tempRoot->r = NULL;
                        updateParent(tempRoot->p);
                        tempRoot->p = NULL;
                        temp = tempRoot->val;
                        delete tempRoot;
                        size--;
                        return temp;
                    }
                }
                else{
                    //cout << "No right child" << endl;
                    //cout << "Current node's parent: " << tempRoot->p->val << endl;
                    if(tempRoot->l != NULL){
                        //cout << "No right child, left child" << endl;
                        //cout << "Current node's parent: " << tempRoot->p->val << endl;
                        tempRoot->p->l = NULL;
                        //cout << "Parent no longer points to current node" << endl;
                        updateParent(tempRoot->p);
                        tempRoot->p = NULL;
                        temp = tempRoot->val;
                        delete tempRoot;
                        size--;
                        return temp;
                    }
                    else{
                        //cout << "No right child, no left child" << endl;
                        tempRoot->p->l = NULL;
                        //cout << "Current Node's parent point to NULL instead" << endl;
                        updateParent(tempRoot->p);
                        tempRoot->p = NULL;
                        temp = tempRoot->val;
                        delete tempRoot;
                        size--;
                        return temp;
                    }
                }
            }
            else if(tempRoot->p->r == tempRoot){
                //cout << "Current node is right child of parent" << endl;
                if(tempRoot->r != NULL){
                    //cout << "Right child" << endl;
                    if(tempRoot->l != NULL){
                        //cout << "Right child and Left child" << endl;
                        if(tempRoot->r->l != NULL){
                            //cout << "Current node's right child's left child is NOT NULL" << endl;
                            Node* tempNode = tempRoot->r;
                            //While loop iterates through all left children
                            while(tempNode->l != NULL){
                                tempNode = tempNode->l;
                            }
                            tempNode->l = tempRoot->l;
                            tempRoot->l->p = tempNode;
                            //Current Node's left child now properly attached
                            tempRoot->l = NULL;
                            //Current Node disconnected from left child
                            tempRoot->r->p = tempRoot->p;
                            //Current node's right child's parent is now
                            //CUrrent node's parents
                            tempRoot->p->r = tempRoot->r;
                            //Current Node's parent's right child is now
                            //Current Node's right child
                            tempRoot->r = NULL;
                            //Current Node disconnected to right child
                            updateParent(tempRoot->p);
                            tempRoot->p = NULL;
                            temp = tempRoot->val;
                            delete tempRoot;
                            size--;
                            return temp;
                            //Current Node disconnected from parent
                        }
                        else{
                            //cout << "Current Node's right child's left child is NULL" << endl;
                            tempRoot->l->p = tempRoot->r;
                            tempRoot->r->l = tempRoot->l;
                            tempRoot->l = NULL;
                            tempRoot->r->p = tempRoot->p;
                            tempRoot->p->r = tempRoot->r;
                            tempRoot->r = NULL;
                            updateParent(tempRoot->p);
                            tempRoot->p = NULL;
                            temp = tempRoot->val;
                            delete tempRoot;
                            size--;
                            return temp;
                        }
                    }
                    else{
                        //cout << "Right child, no Left child" << endl;
                        tempRoot->r->p = tempRoot->p;
                        tempRoot->p->r = tempRoot->r;
                        tempRoot->r = NULL;
                        updateParent(tempRoot->p);
                        tempRoot->p = NULL;
                        temp = tempRoot->val;
                        delete tempRoot;
                        size--;
                        return temp;
                    }
                }
                else{
                    //cout << "No right child" << endl;
                    if(tempRoot->l != NULL){
                        //cout << "No right child, left child" << endl;
                        tempRoot->p->r = NULL;
                        updateParent(tempRoot->p);
                        tempRoot->p = NULL;
                        temp = tempRoot->val;
                        delete tempRoot;
                        size--;
                        return temp;
                    }
                    else{
                        //cout << "No right child, No left child" << endl;
                        tempRoot->p->r = NULL;
                        updateParent(tempRoot->p);
                        tempRoot->p = NULL;
                        temp = tempRoot->val;
                        delete tempRoot;
                        size--;
                        return temp;
                    }
                }
            }
        }
        else{
            //cout << "Current Node's parent is NULL" << endl;
            if(tempRoot->r != NULL){
                //cout << "Right child" << endl;
                if(tempRoot->l != NULL){
                    //cout << "Right child, left child" << endl;
                    if(tempRoot->r->l != NULL){
                        //cout << "Current node's right child's left child is NOT NULL" << endl;
                        Node* tempNode = tempRoot->r;
                        //While loop iterates through all left children
                        while(tempNode->l != NULL){
                            tempNode = tempNode->l;
                        }
                        tempNode->l = tempRoot->l;
                        tempRoot->l->p = tempNode;
                        //Current Node's left child now properly attached
                        tempRoot->r->p = NULL;
                        //Current node's right child's parent is now NULL
                        root = tempRoot->r;
                        //Current ROOT is now the right child
//NEED TO TEST UPDATE PARAENT FOR THIS CASE
//UPDATEPARENT FROM THE LOWEST NODE PAST TEMPNODE!
                        cout << endl << "WEIRD CASE" << endl;
                        Node* tempNode2 = tempNode->l;
                        cout << "Old tempNode2: " << tempNode2->val << endl;
                        while(tempNode2->l != NULL){
                            tempNode2 = tempNode2->l;
                            //cout << "Next tempNode2: " << tempNode2->val << endl;
                        }
                        cout << "New tempNode2: " << tempNode2->val << endl;
                        updateParent(tempNode2);
                        tempRoot->l = NULL;
                        //Current Node disconnected from left child
                        tempRoot->r = NULL;
                        //Current Node disconnected to right child
                        temp = tempRoot->val;
                        delete tempRoot;
                        size--;
                        return temp;
                        //Current Node disconnected from parent
                    }
                    else{
                        //cout << "Current node's right child's left child is NULL" << endl;
                        tempRoot->l->p = tempRoot->r;
                        tempRoot->r->l = tempRoot->l;
                        tempRoot->r->p = NULL;
                        root = tempRoot->r;
//NEED TO TEST UPDATE PARAENT FOR THIS CASE
                        Node* tempNode3 = tempRoot->l;
                        while(tempNode3->l != NULL){
                            tempNode3 = tempNode3->l;
                        }
                        updateParent(tempNode3);
                        tempRoot->l = NULL;
                        tempRoot->r = NULL;
                        temp = tempRoot->val;
                        delete tempRoot;
                        size--;
                        return temp;
                    }
                }
                else{
                    //cout << "Right child, no left child" << endl;
                    root = tempRoot->r;
                    tempRoot->r->p = NULL;
                    updateParent(tempRoot->r);
                    tempRoot->r = NULL;
                    temp = tempRoot->val;
                    delete tempRoot;
                    size--;
                    return temp;
                }
            }
            else{
                //cout << "No right Child" << endl;
                if(tempRoot->l != NULL){
                    //cout << "No right child, no left child" << endl;
                    root = NULL;
                    temp = tempRoot->val;
                    delete tempRoot;
                    size--;
                    return temp;
                }
                else{
                    //cout << "No right child, left child" << endl;
                    root = tempRoot->l;
                    tempRoot->l->p = NULL;
                    updateParent(tempRoot->l);
                    tempRoot->l = NULL;
                    temp = tempRoot->val;
                    delete tempRoot;
                    size--;
                    return temp;
                }
            }
        }
    }
    else{
        //cout << "Current word does not match input word" << endl;
        if(compare(s, tempRoot->val) == -1){
            //cout << "Input word < Current word" << endl;
            return recurRemove(tempRoot->l, s);
        }
        else{
            //cout << "Input word > Current word" << endl;
            return recurRemove(tempRoot->r, s);
        }
    }
}
