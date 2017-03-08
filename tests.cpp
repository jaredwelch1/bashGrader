#include <cstdlib>
#include <iostream>
#include <fstream>
#include <new>
#include <vector>

using std::vector;
using std::string;

#include <gtest/gtest.h>


extern "C" {
    
    typedef struct list_node {
        int num;
        struct list_node *next;
    } node;

    node* add_node(node *head,  int *number);
    node* delete_node(node *head);
    int sum_list(node *head);
    void free_list(node *head);
}

unsigned int score;
unsigned int total;
bool create_list;
bool first_node_check;
bool more_nodes_added;
bool sum_equal_one;
bool sum_error_2;
bool sum_error_3;
bool sum_error_4;
bool delete_error1;
bool delete_error2;
bool error_1;
bool error_2;


std::string commments = "";


class GradeEnvironment : public testing::Environment {
  public:
    virtual void SetUp() {

        score = 0;
        
        total = 40;

        create_list = true;
        first_node_check = true;
        more_nodes_added = true;
        sum_equal_one = true;
        sum_error_2 = true;
        sum_error_3 = true;
        sum_error_4 = true;
        delete_error1 = true;
        delete_error2 = true;
}

    virtual void TearDown() {
        ::testing::Test::RecordProperty("points_given", score);
        ::testing::Test::RecordProperty("points_total", total);
        
        if (create_list)
            commments+="add node fails when given NULL | ";

        if (first_node_check)
            commments+="failed to add node | ";

        if (more_nodes_added)
            commments+="failed to add more than 1 node | ";
        
        if(sum_equal_one)
            commments+="sum did not work | ";

        if(sum_error_2)
            commments+="sum of whole list failed | ";

        if(sum_error_3)
            commments+="sum failed with negative number in node | ";

        if(sum_error_4)
            commments+="sum does not return -1 if head NULL | ";

        if(delete_error1)
            commments+="deleting node failed | ";

        if(delete_error2)
            commments+="delete does not return NULL when list is fully deleted | ";

        ::testing::Test::RecordProperty("comments", commments);

        std::cout << "SCORE: " << score << '/' << total << std::endl;
    }
};

TEST(add_node, create_list){


    score+=5; //they get 5 free points for free

    int a = 1;

    node *list = add_node((node*)NULL, &a);
    ASSERT_NE(list, (node*)NULL);    
    score+=3;
    //3 points for creating the list from a null pointer
    create_list = false;

    ASSERT_EQ((list->num), 1);
    score+=2;
    //2 points for having first value in list of 1

    first_node_check = false;

    free_list(list);
}


TEST(add_node, create_list_size_4){

    int b[4] = {1, 2, 3, 4};

    node *list = add_node((node*)NULL, (b+0));

    for( int i = 1; i < 4; i++){
        list = add_node(list, (b+i));
    }

    ASSERT_EQ(list->next->num, 2);
    ASSERT_EQ(list->next->next->num, 3);
    ASSERT_EQ(list->next->next->next->num, 4);

    //5 points for adding values in correct order
    score+=5;
    more_nodes_added = false;

    free_list(list);
}

TEST(sum_list, sum_tests){
    int b[4] = {1, 2, 3, 4};

    node *list = (node*)malloc(sizeof(node));
    list->num = b[0];
    list->next = NULL;

    ASSERT_EQ(sum_list(list), 1);

    score+=3;

    sum_equal_one = false;

    list->next = (node*)malloc(sizeof(node));
    list->next->num = b[1];
    list->next->next = (node*)malloc(sizeof(node));
    list->next->next->num = b[2];
    list->next->next->next = (node*)malloc(sizeof(node));
    list->next->next->next->num = b[3];
    list->next->next->next->next = NULL;


    ASSERT_EQ(sum_list(list), 10);
    score+=2;

    sum_error_2 = false;

    int c = -5;

    list->next->next->next->next = (node*)malloc(sizeof(node));
    list->next->next->next->next->num = c;
    list->next->next->next->next->next = NULL;

    ASSERT_EQ(sum_list(list), 5);

    score+=2;

    sum_error_3 = false;

    ASSERT_EQ(sum_list((node*)NULL), -1);
    score+=3;

    sum_error_4 = false;

    free_list(list);
}

TEST(delete_node_test, remove_nodes){

    node *list = (node*)malloc(sizeof(node));

    list->num = 1;

    list->next = (node*)malloc(sizeof(node));

    list->next->num = 9;
    list->next->next = NULL;

    list = delete_node(list);

    int sum = 0;
        node *curr = list;
        sum += curr->num;

        while(curr->next != NULL){
            curr = curr->next;
            sum += curr->num;
        }

    ASSERT_EQ(sum, 1);
    score+=5;

    delete_error1 = false;

    list = delete_node(list);

    ASSERT_EQ((node*)NULL, list);

    score+=5;

    delete_error2 = false;
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    ::testing::AddGlobalTestEnvironment(new GradeEnvironment);
    return RUN_ALL_TESTS();
}
