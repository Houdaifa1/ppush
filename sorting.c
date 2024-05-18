#include "push_swap.h"

void *count_best_push(int index_a, int index_b, int count_a, int count_b, int reset, t_infos *infos)
{
    static int small_cost;
    static int node_index;
    static int target_node_index;
    int check_a;
    int check_b;

    check_a = 0;
    check_b = 0;
    if (index_a > (count_a / 2) + 1)
    {
        index_a = count_a - index_a + 2;
        check_a = 1;
    }
    if (index_b > (count_b / 2) + 1)
    {
        index_b = count_b - index_b + 2;
        check_b = 1;
    }
    if (reset == 0)
    {
        small_cost = index_a + index_b - 2;
        if (check_a == 1)
            index_a = (count_a + 2) - index_a;
        node_index = index_a;
        if (check_b == 1)
            index_b = (count_b + 2) - index_b;
        target_node_index = index_b;
    }
    if (index_a + index_b - 2 < small_cost)
    {
        small_cost = index_a + index_b - 2;
        if (check_a == 1)
            index_a = (count_a + 2) - index_a;
        node_index = index_a;
        if (check_b == 1)
            index_b = (count_b + 2) - index_b;
        target_node_index = index_b;
    }
    infos->index = node_index;
    infos->target_num_index = target_node_index;
    infos->cost = small_cost;
}

int found_the_target(int a_number, stack *b, int big_num_index)
{
    int check;
    int target_num;
    int target_num_index;

    target_num = b->number;
    target_num_index = b->index;
    check = 0;
    while (b->next != NULL)
    {
        b = b->next;            
        if (target_num > a_number)
        {
            target_num = b->number;
            target_num_index = b->index;
        }
        else if (b->number < a_number && b->number > target_num)
        {
            target_num = b->number;
            target_num_index = b->index;
            check = 1;
        }
    }
    if (check == 0 && target_num > a_number)
        target_num_index = big_num_index;
    return (target_num_index);
}
void rotate_the_stack(int index, int count, stack **a, stack **b, char c)
{
    if (index <= (count / 2) + 1)
    {
        while(index > 1)
        {
            if (c == 'a')
                rotate_a(a);
            if (c == 'b')
                rotate_b(b);
            index--;
        }
    }
    else
    {
        while (index <= count)
        {
            if (c == 'a')
                rrotate_a(a);
            if (c == 'b')
                rrotate_b(b);
            index++;
        }
    }

}
void push_to_a(int index_a, int index_b, stack **a, stack **b)
{
    int count_a;
    int count_b;

    count_a = count_stack(a);
    count_b = count_stack(b);
            numbers_index(b);
        numbers_index(a);
    rotate_the_stack(index_a, count_a, a,b, 'a');
    rotate_the_stack(index_b, count_b, a,b, 'b');
    push_b(a, b);
    
}
void find_target(stack **a, stack **b)
{
    stack *tempa;
    stack *tempb;
    int i;
    int target_num_index;
    int count_a;
    int count_b;
    int reset;
    int big_num_index;
    t_infos infos;

    tempb = *b;
    tempa = *a;
    count_b = count_stack(b);
    count_a = count_stack(a);
    big_num_index = get_big_num(b, 1);
    reset = 0;
    i = 0;
    while (i < count_a)
    {
        // numbers_index(b);
        // numbers_index(a);
        tempb = *b;
        target_num_index = found_the_target(tempa->number, tempb, big_num_index);
        //printf("%d                %d\n", tempb->number ,target_num_index);
        count_best_push(tempa->index, target_num_index, count_a, count_b, reset, &infos);
        tempa = tempa->next;
        reset = 1;
        i++;
    }
    //printf("%d                %d                %d\n", infos.index ,infos.target_num_index, infos.cost);
    push_to_a(infos.index, infos.target_num_index, a, b);
}