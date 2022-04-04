#include <gtest/gtest.h>

#include "Tester.hpp"

CHASE::Tester tester;

TEST(EPSTest, OVERVOLT) {
    tester.overvoltTest();
}

TEST(EPSTest, UNDERVOLT) {
    tester.undervoltTest();
}

TEST(EPSTest, OVERCURRENT) {
    tester.overcurrentTest();
}

TEST(EPSTest, switch) {
    tester.switchTest();
}

int main(int argc, char* argv[]) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
