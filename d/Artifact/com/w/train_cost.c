#include "/d/Artifact/artifact.h"

inherit CMD_MODULE;

static int
main(string arg)
{
    int i, len, sum;
    object *arr;
    sum = 0;
    arr = ART_D_SLIVER->query_slivers();
    arr = filter_array(arr, "has_train_cost");
    arr = sort_array(arr, "cmp_train_cost");
    for (i = 0, len = sizeof(arr); i < len; ++i) {
        int cost;
        cost = arr[i]->query_train_cost() / 1000; 
        sum += cost;
        printf("%-30s%10d000%10d000\n", arr[i]->query_name(), cost, sum);
    }
    return 1;
}

static int 
has_train_cost(object obj)
{
    return obj->query_train_cost() > 0;
}

static int
cmp_train_cost(object lhs, object rhs)
{
    return lhs->query_train_cost() - rhs->query_train_cost();
}
       
