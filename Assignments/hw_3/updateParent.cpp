void AVL::updateParent(Node* current){
    cout << endl << "Beginning of updateParent function" << endl;
    int bV;
    //out << endl << "Current Node: " << current->val << endl;
    if(current->l == NULL && current->r == NULL){
        cout << "Node has no children" << endl;
        current->h = 1;
        bV = 0;
        if(current->p == NULL){
            cout << "Node has no parent" << endl;
            return;
            }
    }
    else if(current->l != NULL && current->r == NULL){
        cout << "current->l->val: " << current->l->val << endl;
        cout << "Left not NULL, Right NULL" << endl;
        cout << "Left's height: " << current->l->h << endl;
        cout << "Current's old height: " << current->h << endl;
        current->h = current->l->h + 1;
        cout << "Current's new height: " << current->h << endl;
        bV = 0 - current->l->h;
        current->bV = bV;
    }
    else if(current->l == NULL && current->r != NULL){
        cout << "current->r->val: " << current->r->val << endl;
        cout << "Left NULL, Right not NULL" << endl;
        cout << "Right's height: " << current->r->h << endl;
        cout << "Current's old height: " << current->h << endl;
        current->h = current->r->h + 1;
        cout << "Current's new height: " << current->h << endl;
        bV = current->r->h - 0;
        current->bV = bV;
    }
    else{
        cout << "Left not NULL, Right not NULL" << endl;
        cout << "current->l->val: " << current->l->val << endl;
        cout << "current->r->val: " << current->r->val << endl;
        cout << "Left Height: " << current->l->h << endl;
        cout << "Right Height: " << current->r->h << endl;
        if(current->l->h >= current->r->h){
            cout << "Left Height >= Right Height" << endl;
            cout << "Current's old height: " << current->h << endl;
            current->h = current->l->h + 1;
            cout << "Current's new height: " << current->h << endl;
        }
        else{
            cout << "Left Height < Right Height" << endl;
            cout << "Current's old height: " << current->h << endl;
            current->h = current->r->h + 1;
            cout << "Current's new height: " << current->h << endl;
        }
        bV = current->r->h - current->l->h;
        current->bV = bV;
    }
    cout << "Current balance value: " << bV << endl;
    if((bV == 2) || (bV == -2)){
        cout << "REBALANCE REQUIRED" << endl;
        rebalance(current);
        //Goes to bottom of tree and updates parents
        ///////////////////////////////////////////
    }
    //Calculate balance Value
    if(current->p != NULL){
        cout << "Current node's parent is NOT NULL" << endl;
        cout << "Calling updateParent on PARENT" << endl;
        updateParent(current->p);
    }
    else{
        root = current;
    }
}
