#include <gtest/gtest.h>
#include "mymap.h"

//this function was taken from stackoverflow to make randomly generated strings of a specifed length
string gen_random(const int len) {
    static const char alphanum[] =
        "0123456789"
        "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
        "abcdefghijklmnopqrstuvwxyz";
    string tmp_s;
    tmp_s.reserve(len);

    for (int i = 0; i < len; ++i) {
        tmp_s += alphanum[rand() % (sizeof(alphanum) - 1)];
    }
    
    return tmp_s;
}


TEST(Access, Test_1) {
    mymap<int, int> testMe;
    map<int, int> correct;
    int value = 10;
    int value2 = 5;
    correct.emplace(value, value2);
    testMe.put(value,value2);
    EXPECT_EQ(true, testMe.contains(value));
    EXPECT_EQ(testMe.get(value), correct[value]);
    EXPECT_EQ(testMe[value], correct[value]);
}

//tries with different types
TEST(Access, Test_2) {
    mymap<int, string> testMe;
    map<int, string> correct;
    int value = 10;
    string value2 = "hello";
    correct.emplace(value, value2);
    testMe.put(value,value2);
    EXPECT_EQ(true, testMe.contains(value));
    EXPECT_EQ(testMe.get(value), correct[value]);
    EXPECT_EQ(testMe[value], correct[value]);
}

//tries with different types
TEST(Access, Test_3) {
    mymap<string, int> testMe;
    map<string, int> correct;
    string value = "world";
    int value2 = 5;
    correct.emplace(value, value2);
    testMe.put(value,value2);
    EXPECT_EQ(true, testMe.contains(value));
    EXPECT_EQ(testMe.get(value), correct[value]);
    EXPECT_EQ(testMe[value], correct[value]);
}

//checks for existing value with some elements
TEST(Access, Test_4) {
    mymap<int, int> testMe;
    map<int, int> correct;
    
    int n = 30;
    int value = 14;

    for (int i = 0; i < n; i++) {
        correct.emplace(i, i);
        testMe.put(i, i);
    }
    EXPECT_EQ(true, testMe.contains(value));
    EXPECT_EQ(testMe.get(value), correct[value]);
    EXPECT_EQ(testMe[value], correct[value]);
}


TEST(Access, Test_5) {
    mymap<int, int> testMe;
    map<int, int> correct;
    
    int n = 30;
    int value = 14;

    for (int i = 0; i < n; i++) {
        correct.emplace(i, i + 10);
        testMe.put(i, i + 10);
    }
    EXPECT_EQ(true, testMe.contains(value));
    EXPECT_EQ(testMe.get(value), correct[value]);
    EXPECT_EQ(testMe[value], correct[value]);
}


//empty tree accessing an element that doesn't exist
TEST(Access, Test_6) {
    mymap<int, int> testMe;
    map<int, int> correct;

    int value = 5;
    EXPECT_EQ(false, testMe.contains(value));
    EXPECT_EQ(testMe.get(value), correct[value]);
    EXPECT_EQ(testMe[value], correct[value]);
}

//very large randomly generated tree
TEST(StressTesting, Test_1) {
    mymap<int, int> testMe;
    map<int, int> correct;
    int savedValue1;
    for (int i = 0; i < 100000; i++) {
        int randomValue1 = rand();
        int randomValue2 = rand();

        correct.emplace(randomValue1, randomValue2);
        testMe.put(randomValue1, randomValue2);

        if (i == 500) {
            savedValue1 = randomValue1;
        }
    }
    EXPECT_EQ(true, testMe.contains(savedValue1));
    EXPECT_EQ(testMe.get(savedValue1), correct[savedValue1]);
    EXPECT_EQ(testMe[savedValue1], correct[savedValue1]);
}

TEST (Access_Strings, Test_1) {
    mymap<string, int> testMe;
    map<string, int> correct;

    int n = 500;
    string savedValue1;
    for (int i = 0; i < n; i++) {
        string random = gen_random(10);
        testMe.put(random, i);
        correct.emplace(random, i);
        if (i == n/2) {
            savedValue1 = random;
        }
    }
    EXPECT_EQ(true, testMe.contains(savedValue1));
    EXPECT_EQ(testMe.get(savedValue1), correct[savedValue1]);
    EXPECT_EQ(testMe[savedValue1], correct[savedValue1]);
}

//test the tostring function
TEST(StringStream, Test_1) {
    mymap<int, int> testMe;
    
    stringstream dump;
    int n = 30;

    for (int i = 0; i < n; i++) {
        testMe.put(i, i);

        dump << "key: " << i << " value: " << i << "\n";
    }

    ASSERT_EQ(dump.str(), testMe.toString());
}

TEST(StringStream, Test_2) {
    mymap<int, int> testMe;
    
    stringstream dump;
    int n = 30;

    for (int i = n; i > 0; i--) {
        testMe.put(i, i);

        dump << "key: " << n - i + 1 << " value: " << n - i + 1 << "\n";
    }

    ASSERT_EQ(dump.str(), testMe.toString());
}

TEST(StringStream, Test_3) {
    mymap<int, int> testMe;
    int array[] = {8,15,20,25,28,30,40,50,60,70};
    stringstream dump;

    testMe.put(30, 6);
    testMe.put(15, 2);
    testMe.put(50, 8);
    testMe.put(8, 1);
    testMe.put(25, 4);
    testMe.put(70, 10);
    testMe.put(20, 3);
    testMe.put(28, 5);
    testMe.put(40, 7);
    testMe.put(60, 9);

    for (int i = 0; i < 10; i++) {
        dump << "key: " << array[i] << " value: " << i + 1 << "\n";
    }

    ASSERT_EQ(dump.str(), testMe.toString());
}

TEST(SizeTest, Test_1) {
    mymap<int, int> testMe;
    
    int n = 30;

    for (int i = 0; i < n; i++) {
        testMe.put(i, i);
    }

    ASSERT_EQ(n, testMe.Size());
}

//testing size for empty tree
TEST(SizeTest, Test_2) {
    mymap<int, int> testMe;
    
    int n = 0;

    ASSERT_EQ(n, testMe.Size());
}

TEST(SizeTest, Test_3) {
    mymap<int, int> testMe;
    map<int, int> correct;

    int n = 100000;
    for (int i = 0; i < n; i++) {
        int randomValue1 = rand();
        int randomValue2 = rand();

        correct.emplace(randomValue1, randomValue2);
        testMe.put(randomValue1, randomValue2);
    }
    ASSERT_EQ(correct.size(), testMe.Size());
}


TEST (Milestone_3, Test_1) {
    mymap<int, int> testMe;
    map<int, int> correct;

    int n = 100000;
    for (int i = 0; i < n; i++) {
        int randomValue1 = rand();
        int randomValue2 = rand();

        correct.emplace(randomValue1, randomValue2);
        testMe.put(randomValue1, randomValue2);
    }
    stringstream ss;
    for (int key : testMe) {
        ss << "key: " << key << " value: " << testMe[key] << endl;
    }
    stringstream dump;
    for (auto const x: correct) {
        dump << "key: " << x.first << " value: " << x.second << endl;
    }
    EXPECT_EQ(ss.str(), testMe.toString());
    EXPECT_EQ(dump.str(), testMe.toString());
}


TEST(Milestone_3, Test_2) {
    mymap<int, int> testMe;
    

    testMe.put(30, 6);
    testMe.put(15, 2);
    testMe.put(50, 8);
    testMe.put(8, 1);
    testMe.put(25, 4);
    testMe.put(70, 10);
    testMe.put(20, 3);
    testMe.put(28, 5);
    testMe.put(40, 7);
    testMe.put(60, 9);

    stringstream ss;
    for (int key : testMe) {
        ss << "key: " << key << " value: " << testMe[key] << endl;
        //cout << "key: " << key << " value: " << testMe[key] << endl;
    }
    EXPECT_EQ(ss.str(), testMe.toString());
}

TEST (Clear, Test_1) {
    mymap<int, int> testMe;
    

    testMe.put(30, 6);
    testMe.put(15, 2);
    testMe.put(50, 8);
    testMe.put(8, 1);
    testMe.put(25, 4);
    testMe.put(70, 10);
    testMe.put(20, 3);
    testMe.put(28, 5);
    testMe.put(40, 7);
    testMe.put(60, 9);

    testMe.clear();
    
    EXPECT_EQ(0, testMe.Size());
    EXPECT_EQ(false, testMe.contains(30));
}

TEST (Clear, Test_2) {
    mymap<int, int> testMe;
    map<int, int> correct;
    int savedValue;

    int n = 100000;
    for (int i = 0; i < n; i++) {
        int randomValue1 = rand();
        int randomValue2 = rand();

        correct.emplace(randomValue1, randomValue2);
        testMe.put(randomValue1, randomValue2);
        if (i == n/2) {
            savedValue = randomValue1;
        }
    }
    testMe.clear();
    EXPECT_EQ(0, testMe.Size());
    EXPECT_EQ(false, testMe.contains(savedValue));
}

TEST (CopyConstructor, stress_test) {
    mymap<int, int> testMe;

    int n = 100000;
    for (int i = 0; i < n; i++) {
        int randomValue1 = rand();
        int randomValue2 = rand();

        testMe.put(randomValue1, randomValue2);
        
    }

    mymap<int, int> testMe2(testMe);

    EXPECT_EQ(testMe2.Size(), testMe.Size());
    EXPECT_EQ(testMe2.toString(), testMe.toString());
}


TEST (CopyConstructor, small_tree) {
    mymap<int, int> testMe;
    

    testMe.put(30, 6);
    testMe.put(15, 2);
    testMe.put(50, 8);
    testMe.put(8, 1);
    testMe.put(25, 4);
    testMe.put(70, 10);
    testMe.put(20, 3);
    testMe.put(28, 5);
    testMe.put(40, 7);
    testMe.put(60, 9);

    mymap<int, int> testMe2(testMe);

    EXPECT_EQ(testMe2.Size(), testMe.Size());
    EXPECT_EQ(testMe2.toString(), testMe.toString());
}

TEST (EqualOperator, prefilled) {
    mymap<int, int> testMe;
    

    testMe.put(30, 6);
    testMe.put(15, 2);
    testMe.put(50, 8);
    testMe.put(8, 1);
    testMe.put(25, 4);
    testMe.put(70, 10);
    testMe.put(20, 3);
    testMe.put(28, 5);
    testMe.put(40, 7);
    testMe.put(60, 9);

    mymap<int, int> testMe2;

    testMe2.put(25, 4);
    testMe2.put(70, 10);
    testMe2.put(20, 3);
    testMe2.put(28, 5);
    testMe2.put(40, 7);
    testMe2.put(60, 9);

    testMe2 = testMe;

    EXPECT_EQ(testMe2.Size(), testMe.Size());
    EXPECT_EQ(testMe2.toString(), testMe.toString());
}

TEST (EqualOperator, stress_test) {
    mymap<int, int> testMe;

    int n = 100000;
    for (int i = 0; i < n; i++) {
        int randomValue1 = rand();
        int randomValue2 = rand();

        testMe.put(randomValue1, randomValue2);
        
    }

    mymap<int, int> testMe2;
    testMe2 = testMe;

    EXPECT_EQ(testMe2.Size(), testMe.Size());
    EXPECT_EQ(testMe2.toString(), testMe.toString());
}

TEST (EqualOperator, settingEqualToEmptyTree) {
    mymap<int, int> testMe;

    int n = 100000;
    for (int i = 0; i < n; i++) {
        int randomValue1 = rand();
        int randomValue2 = rand();

        testMe.put(randomValue1, randomValue2);
        
    }

    mymap<int, int> testMe2;
    testMe = testMe2;

    EXPECT_EQ(testMe2.Size(), testMe.Size());
    EXPECT_EQ(testMe2.toString(), testMe.toString());
}

//commented out because tests no longer have correct reference as I changed the return vector value from keyType, valueType to NODE*
/*
TEST (toVectorTest, small_tree) {
    mymap<int, int> testMe;
    
    testMe.put(30, 6);
    testMe.put(15, 2);
    testMe.put(50, 8);
    testMe.put(8, 1);
    testMe.put(25, 4);
    testMe.put(70, 10);
    testMe.put(20, 3);
    testMe.put(28, 5);
    testMe.put(40, 7);
    testMe.put(60, 9);

    stringstream ss;

    
    vector<pair<int, int>> testVector = testMe.toVector();

    for (int i = 0; i < testVector.size(); i++) {
        ss << "key: " << testVector.at(i).first << " value: " << testVector.at(i).second << endl;
    }
    EXPECT_EQ(ss.str(), testMe.toString());
    EXPECT_EQ(testVector.size(), testMe.Size());
}

TEST (toVectorTest, empty_tree) {
    mymap<int, int> testMe;
    vector<pair<int, int>> testVector = testMe.toVector();
    EXPECT_EQ(testMe.Size(), testVector.size());
}

TEST (toVectorTest, stress_test) {
    mymap<int, int> testMe;
    
    int n = 100000;
    for (int i = 0; i < n; i++) {
        int randomValue = rand();
        testMe.put(randomValue, i);
    }

    stringstream ss;
    vector<pair<int, int>> testVector = testMe.toVector();

    for (int i = 0; i < testVector.size(); i++) {
        ss << "key: " << testVector.at(i).first << " value: " << testVector.at(i).second << endl;
    }
    EXPECT_EQ(ss.str(), testMe.toString());
    EXPECT_EQ(testVector.size(), testMe.Size());
}
*/

TEST(StressTestAssertions, Test1) {
    mymap<int, int> testMe;
    map<int, int> correct;

    int n = 100000;
    for (int i = 0; i < n; i++) {
        int randomValue1 = rand() % 1000;
        int randomValue2 = rand() % 1000;

        correct.emplace(randomValue1, randomValue2);
        testMe.put(randomValue1, randomValue2);
        ASSERT_EQ(correct.size(), testMe.Size());
    }
}

TEST(StressTestAssertions, Test2) {
    mymap<int, int> testMe;
    map<int, int> correct;

    int n = 100000;
    for (int i = 0; i < n; i++) {
        int randomValue1 = rand() % 1000;
        int randomValue2 = rand() % 1000;

        correct.emplace(randomValue1, randomValue2);
        testMe.put(randomValue1, randomValue2);
        ASSERT_EQ(testMe.get(randomValue1), randomValue2);
        ASSERT_EQ(testMe.contains(randomValue1), correct.count(randomValue1));
    }
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
// TO DO: write lots of tests here.
