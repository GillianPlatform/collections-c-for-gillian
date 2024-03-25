#include <stdlib.h>

// === From common ===

enum cc_stat {
    CC_OK                   = 0,

    CC_ERR_ALLOC            = 1,
    CC_ERR_INVALID_CAPACITY = 2,
    CC_ERR_INVALID_RANGE    = 3,
    CC_ERR_MAX_CAPACITY     = 4,
    CC_ERR_KEY_NOT_FOUND    = 6,
    CC_ERR_VALUE_NOT_FOUND  = 7,
    CC_ERR_OUT_OF_RANGE     = 8,

    CC_ITER_END             = 9,
};


// === From header ===

#define RB_BLACK 1
#define RB_RED   0

/**
 * Red-Black tree node.
 *
 * @note Modifying this structure may invalidate the table.
 */
typedef struct rbnode_s {
    /**
     * Key in the table. */
    void *key;

    /**
     * Value associated with the key */
    void *value;

    /**
     * The color of this node */
    char  color;

    /**
     * Parent of this node */
    struct rbnode_s *parent;

    /**
     * Left child node */
    struct rbnode_s *left;

    /**
     * Right child node */
    struct rbnode_s *right;
} RBNode;

/**
 * An ordered key-value map. TreeTable supports logarithmic time
 * insertion, removal and lookup of values.
 */
typedef struct treetable_s {
    RBNode *root;
    RBNode *sentinel;
    size_t  size;

    int    (*cmp) (const void *k1, const void *k2);
} TreeTable;


// === From source ===

/**
 * Performs a left rotation on the specified table's RB tree at root <code>
 * x</code>
 *
 * @param[in] table the table on which this operation is performed
 * @param[in] x the node around which this operation is performed
 */
static void rotate_left(TreeTable *table, RBNode *x)
{
    RBNode *y = x->right;

    x->right = y->left;

    if (y->left != table->sentinel)
        y->left->parent = x;

    y->parent = x->parent;

    if (x->parent == table->sentinel)
        table->root = y;
    else if (x == x->parent->left)
        x->parent->left = y;
    else
        x->parent->right = y;

    y->left   = x;
    x->parent = y;
}

/**
 * Performs a right rotation on the specified table's RB tree at root <code>
 * x</code>
 *
 * @param[in] table the table on which this operation is performed
 * @param[in] x the node around which this operation is performed
 */
static void rotate_right(TreeTable *table, RBNode *x)
{
    RBNode *y = x->left;

    x->left = y->right;

    if (y->right != table->sentinel)
        y->right->parent = x;

    y->parent = x->parent;

    if (x->parent == table->sentinel)
        table->root = y;
    else if (x == x->parent->right)
        x->parent->right = y;
    else
        x->parent->left = y;

    y->right  = x;
    x->parent = y;
}

/**
 * Rebalances the tale after an insert.
 *
 * @param[in] table TreeTable that is being rebalanced
 * @param[in] z Node that was inserted
 */
static void rebalance_after_insert(TreeTable *table, RBNode *z)
{
    RBNode *y;

    while (z->parent->color == RB_RED) {
        if (z->parent == z->parent->parent->left) {
            y = z->parent->parent->right;
            if (y->color == RB_RED) {
                z->parent->color         = RB_BLACK;
                y->color                 = RB_BLACK;
                z->parent->parent->color = RB_RED;
                z = z->parent->parent;
            } else {
                if (z == z->parent->right) {
                    z = z->parent;
                    rotate_left(table, z);
                }
                z->parent->color         = RB_BLACK;
                z->parent->parent->color = RB_RED;
                rotate_right(table, z->parent->parent);
            }
        } else {
            y = z->parent->parent->left;
            if (y->color == RB_RED) {
                z->parent->color         = RB_BLACK;
                y->color                 = RB_BLACK;
                z->parent->parent->color = RB_RED;
                z = z->parent->parent;
            } else {
                if (z == z->parent->left) {
                    z = z->parent;
                    rotate_right(table, z);
                }
                z->parent->color         = RB_BLACK;
                z->parent->parent->color = RB_RED;
                rotate_left(table, z->parent->parent);
            }
        }
    }
    table->root->color = RB_BLACK;
}

/**
 * Creates a new key-value mapping in the specified TreeTable. If the unique key
 * is already mapped to a value in this table, that value is replaced with the
 * new value. This operation may fail if the space allocation for the new entry
 * fails.
 *
 * @param[in] table the table to which this new key-value mapping is being added
 * @param[in] key a tree table key used to access the specified value
 * @param[in] val a value that is being stored in the table
 *
 * @return CC_OK if the operation was successful, or CC_ERR_ALLOC if the memory
 * allocation for the new element failed.
 */
enum cc_stat treetable_add(TreeTable *table, void *key, void *val)
{
    RBNode *y = table->sentinel;
    RBNode *x = table->root;

    int cmp;
    while (x != table->sentinel) {
        cmp = table->cmp(key, x->key);
        y   = x;

        if (cmp < 0) {
            x = x->left;
        } else if (cmp > 0) {
            x = x->right;
        } else {
            x->value = val;
            return CC_OK;
        }
    }
    RBNode *n = malloc(sizeof(RBNode));

    if (!n)
        return CC_ERR_ALLOC;

    n->value  = val;
    n->key    = key;
    n->parent = y;
    n->left   = table->sentinel;
    n->right  = table->sentinel;

    table->size++;

    if (y == table->sentinel) {
        table->root = n;
        n->color    = RB_BLACK;
    } else {
        n->color = RB_RED;
        if (table->cmp(key, y->key) < 0) {
            y->left = n;
        } else {
            y->right = n;
        }
        rebalance_after_insert(table, n);
    }
    return CC_OK;
}
