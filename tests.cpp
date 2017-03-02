#include <cstdlib>
#include <iostream>
#include <fstream>
#include <new>
#include <vector>

using std::vector;
using std::string;

#include <gtest/gtest.h>


extern "C" {
	double* read_file(FILE* file, int length);
	void write_to_file(FILE* fp, double val);
	double* sort_asc(double*, int);
	double* sort_desc(double*, int);
}

unsigned int score;
unsigned int total;

class GradeEnvironment : public testing::Environment {
  public:
    virtual void SetUp() {

        score = 0;
        
        total = 40;

    }

    virtual void TearDown() {
        ::testing::Test::RecordProperty("points_given", score);
        ::testing::Test::RecordProperty("points_total", total);
        std::cout << "SCORE: " << score << '/' << total << std::endl;
    }
};

/* 
	double* read_file(FILE* file, int length);
	void write_to_file(FILE* fp, double val);
	double* sort_asc(double*, int);
	double* sort_desc(double*, int);

*/


TEST(TestRead, test_all_ints) {
    //input file:
    /*
        1
        2
        3
        4
    */

    //free point!
	score++;

    double master [5] = {1, 2, 3, 4, 5};

    FILE *fp = fopen("in_file1.txt", "r");

    if (!fp)
        std::cout << "Did not open"; 
    
    double *student = read_file(fp, 5);

    for(int i = 0; i < 5; i++)
        ASSERT_EQ(master[i], student[i]);

    fclose(fp);
    score+=5;
}

TEST(TestRead, test_all_doubles){

    double master [5] = {2.32, 1.41, 124.12, 123114.12, 909.123};
    FILE *fp = fopen("in_file2.txt", "r");

    if (!fp)
        std::cout << "did not open file 2";

    double *student = read_file(fp, 5);

    for(int i = 0; i < 5; i++)
        ASSERT_EQ(master[i], student[i]);
    
    score+=10;
    fclose(fp);
}

TEST(TestWrite, test_valid_writes){
    FILE *fp = fopen("test_out.txt", "w");

    double vals [5] = {1.1, 2.2, 3.3, 4.4, 5.5};

    for (int i = 0; i < 5; i++){
        write_to_file(fp, vals[i]);
    } 
    
    fclose(fp);

    FILE *fp2 = fopen("test_out.txt", "r");

    ASSERT_NE(fp2, (FILE *)NULL);

    double temp;
    
    for( int i = 0; i < 5; i++){
        fscanf(fp2, "%lf", &temp);
        ASSERT_EQ(vals[i], temp);
    }

    fclose(fp2);
    score+=10;

}

TEST(TestSortASC, sort_test){

    double array [9] = {9.9, 8.8, 7.7, 6.6, 5.5, 4.4, 3.3, 2.2, 1.1};
    int i;
    double sorted [9] = {1.1, 2.2, 3.3, 4.4, 5.5, 6.6, 7.7, 8.8, 9.9};
    sort_asc(array, 9);

    for( i = 0; i < 9; i++){
        ASSERT_EQ( (int)array[i], (int)sorted[i]);
    }
    score+=3;

    for( i = 0; i < 9; i++){
        ASSERT_EQ( array[i], sorted[i]);
    }
    score+=4;
}

TEST(TestSortDESC, sort_test){

    double sorted [9]= {9.9, 8.8, 7.7, 6.6, 5.5, 4.4, 3.3, 2.2, 1.1};
    int i;
    double array [9] = {1.1, 2.2, 3.3, 4.4, 5.5, 6.6, 7.7, 8.8, 9.9};
    sort_desc(array, 9);

    for(i = 0; i < 9; i++){
        ASSERT_EQ( (int)array[i], (int)sorted[i]);
    }
    score+=3;

    for(i = 0; i < 9; i++){
        ASSERT_EQ( array[i], sorted[i]);
    }
    score+=4;
}



int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    ::testing::AddGlobalTestEnvironment(new GradeEnvironment);
    return RUN_ALL_TESTS();
}
