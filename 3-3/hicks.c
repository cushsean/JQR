static treenode_t* tree_node_new(void* data)
{
        treenode_t* node = (treenode_t*)malloc(sizeof(treenode_t));
        node->left_child = NULL;
        node->right_child = NULL;
        node->data = data;
        return node;
}
static void _tree_insert(tree_t* tree, treenode_t** leaf, void* data)
{
        if ( *leaf == NULL) {
                *leaf = tree_node_new(data);
                tree->nnodes++;
                debug_print("Inserting %d; now %zu nodes\n", *(int*)data, tree->nnodes);
                return;
        }
        int cmp = tree->cmp_f(data, (*leaf)->data);
        if (cmp == -1) {
                debug_print("%d < %d - %s", *(int*)data, *(int*)(*leaf)->data, "going left\n");
                _tree_insert(tree, &(*leaf)->left_child, data);
        } else if (cmp == 1) {
                debug_print("%d > %d - %s", *(int*)data, *(int*)(*leaf)->data, "going right\n");
                _tree_insert(tree, &(*leaf)->right_child, data);
        } else if (cmp == 0) {
                debug_print("Encountered duplicate, skipping insertion: %d\n", *(int*)data);
        } else {
                debug_print("Skipping non-null leaf: %d\n", *(int*)data);
        } // do nothing if equal - don't insert duplicates
}
void tree_insert(tree_t* tree, void* data)
{
        _tree_insert(tree, &(tree->root), data);
}