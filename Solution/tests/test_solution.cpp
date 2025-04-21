#include <gtest/gtest.h>
#include "solution.h"

class SolutionTest : public ::testing::Test {
protected:
    solution sl;
};

TEST_F(SolutionTest, ApplyFilterWithKnownData) {
    sl.set_yValues({1, 2, 3, 4, 5});
    sl.set_xValues({0, 1, 2, 3, 4}); 
    int window_size = 3;
    sl.apply_filter(window_size);

    std::vector<double> expected_filtered = {
        (1 + 2 + 3) / 3.0,
        (2 + 3 + 4) / 3.0,
        (3 + 4 + 5) / 3.0,
        (4 + 5) / 2.0,
        (4 + 5) / 2.0
    };
    std::vector<double> filtered_yvalues = sl.get_filtered_yValues();

    for (size_t i = 0; i < expected_filtered.size(); ++i) {
        EXPECT_EQ(filtered_yvalues[i], expected_filtered[i]);
    }
}

TEST_F(SolutionTest, ApplyFilterNofiltering) {
    sl.set_yValues({1, 2, 3, 4, 5});
    sl.set_xValues({0, 1, 2, 3, 4});
    int window_size = 1;
    sl.apply_filter(window_size);

    std::vector<double> filtered_yvalues = sl.get_filtered_yValues();

    // No filtering should occur, so the filtered data should be the same as original
    for (size_t i = 0; i < filtered_yvalues.size(); ++i) {
        EXPECT_EQ(filtered_yvalues[i], sl.get_yValues()[i]);
    }
}

TEST_F(SolutionTest, CheckDeltasNoThresholdExceeded) {
    std::vector<double> filtered_yvalues = {1, 1.5, 2, 2.5, 3};
    sl.set_filtered_yValues(filtered_yvalues);
    int threshold = 1;
    int window_size = 3;

    sl.check_deltas(threshold, window_size);
    std::vector<double> smoothed_yvalues = sl.get_filtered_yValues();

    // No jump events should be triggered, as no delta exceeds the threshold
    EXPECT_EQ(sl.get_filtered_yValues(), smoothed_yvalues);
}

TEST_F(SolutionTest, JumpEventSmoothing) {
    std::vector<double> filtered_yvalues = {1, 2, 4, 4, 5};    
    int threshold = 1.0;
    int window_size = 3;
    sl.set_filtered_yValues(filtered_yvalues);

    sl.check_deltas(threshold, window_size);
    std::vector<double> smoothed_yvalues = sl.get_filtered_yValues();

    // No jump events should be triggered, as no delta exceeds the threshold
    EXPECT_EQ(filtered_yvalues, smoothed_yvalues);
}
