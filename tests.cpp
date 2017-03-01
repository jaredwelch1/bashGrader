#include <cstdlib>
#include <iostream>
#include <new>
#include <vector>

using std::vector;
using std::string;

#include <gtest/gtest.h>

unsigned int score;
unsigned int total;

class GradeEnvironment : public testing::Environment {
  public:
    virtual void SetUp() {

        score = 0;
        
        total = 140;

    }

    virtual void TearDown() {
        ::testing::Test::RecordProperty("points_given", score);
        ::testing::Test::RecordProperty("points_total", total);
        std::cout << "SCORE: " << score << '/' << total << std::endl;
    }
};


TEST(testA, add_to_score) {
	score += 140;
}



int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    ::testing::AddGlobalTestEnvironment(new GradeEnvironment);
    return RUN_ALL_TESTS();
}
