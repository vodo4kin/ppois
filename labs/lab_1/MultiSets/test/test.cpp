#include <gtest/gtest.h>
#include "MultiSets.hpp"

//default
TEST(test_default, test_voidOne){ //1
    MultiSet MultiSet;
    EXPECT_TRUE(MultiSet.isVoid());
}

TEST(test_default, test_voidTwo){ //2
    MultiSet MultiSet;
    EXPECT_FALSE(MultiSet.getElInMultiSet().size());
}

TEST(test_default, test_voidTree){ //3
    MultiSet MultiSet;
    MultiSet = "{          }";
    EXPECT_TRUE(MultiSet.isVoid());
}

//мощность множеств
TEST(test_cardinality, test_one){ //4
    MultiSet MultiSet;
    MultiSet = "{a, b, d, qqq, {sfd,sdsd}, {54, {123, 543, asd}}}";
    EXPECT_TRUE(MultiSet.getCardinality() == 6);
}

TEST(test_cardinality, test_two){ //5
    MultiSet MultiSet;
    MultiSet = "{{{{{}}}}}";
    EXPECT_TRUE(MultiSet.getCardinality() == 1);
}

TEST(test_cardinality, test_three){ //6
    MultiSet MultiSet;
    MultiSet = "{}";
    EXPECT_TRUE(MultiSet.getCardinality() == 0);
}

TEST(test_cardinality, test_four){ //7
    MultiSet MultiSet;
    MultiSet = "{Cat, Dog, {Cat, Dog}}";
    EXPECT_TRUE(MultiSet.getCardinality() == 3);
}

TEST(test_cardinality, test_five){ //8
    MultiSet MultiSet;
    MultiSet = "{Cat, Dog, {Cat, Dog}, Cat, Dog, Cat, Dog, Mouse, {Cat, Mouse}}";
    EXPECT_TRUE(MultiSet.getCardinality() == 9); // Все элементы считаются, включая повторяющиеся
}

TEST(test_cardinality, test_six){ //9
    MultiSet MultiSet;
    MultiSet = "{Cat, Cat, Cat, Cat, Cat, Cat, Cat, Cat}";
    EXPECT_TRUE(MultiSet.getCardinality() == 8); // 8 повторяющихся элементов
    EXPECT_TRUE(MultiSet.getDistinctCount() == 1); // 1 уникальный элемент
    EXPECT_TRUE(MultiSet.getCount("Cat") == 8); // Cat встречается 8 раз
}

//валидность

TEST(test_valid, test_one){ //10
    MultiSet MultiSet;
    MultiSet = "{{{{}}}}";
    EXPECT_TRUE(MultiSet["{{{}}}"]);
}

TEST(test_valid, test_two) { //11
    MultiSet MultiSet;
    MultiSet= "{adasd, 123123,}";
    EXPECT_TRUE(MultiSet.getCardinality() == 0);
}

TEST(test_valid, test_three){ //12
    MultiSet MultiSet;
    MultiSet= "{    adasd,      123123           }";
    EXPECT_TRUE(MultiSet["adasd"] && MultiSet["123123"]);
}

TEST(test_valid, test_four){ //13
    MultiSet MultiSet;
    MultiSet= "{a, b, {c, d}}";
    EXPECT_TRUE(MultiSet["a"] && MultiSet["b"] && MultiSet["{c,d}"]);
}

TEST(test_valid, test_five){ //14
    MultiSet MultiSet;
    MultiSet= "{a, b, {c, d}}}";
    EXPECT_TRUE(MultiSet.isVoid());
}

TEST(test_valid, test_sex){ //15
    MultiSet MultiSet;
    MultiSet= "{a, b, {c, d,}}";
    EXPECT_TRUE(MultiSet.isVoid());
}

TEST(test_valid, test_seven){ //16
    MultiSet MultiSet;
    MultiSet+= "{a}";
    MultiSet+= "{b}";
    MultiSet+= "{asd, asdasd ,asdasds,}";
    EXPECT_TRUE(MultiSet.getCardinality() == 2);
}

TEST(test_valid, test_eight){ //17
    MultiSet MultiSet;
    MultiSet= "a, b, c";
    EXPECT_TRUE(MultiSet["a"] && MultiSet["b"] && MultiSet["c"]);
}

TEST(test_valid, test_nine){ //18
    MultiSet MultiSet;
    MultiSet = "a, b, {c,d}";
    EXPECT_TRUE(MultiSet["a"] && MultiSet["b"] && MultiSet["{c,d}"]);
}

//операции

TEST(test_operations, test_one){ //19
    MultiSet MultiSetOne;
    MultiSetOne = "{a, b, c}";
    MultiSet MultiSetTwo = MultiSetOne;
    EXPECT_TRUE(MultiSetOne == MultiSetTwo);
}

TEST(test_operations, test_two){ //20
    MultiSet MultiSetOne;
    MultiSetOne = "{a, b, c}";
    MultiSet MultiSetTwo;
    MultiSetTwo = "{b, c, d}";
    MultiSetOne*=MultiSetTwo;
    EXPECT_TRUE(!MultiSetOne["a"] && MultiSetOne["b"] && MultiSetOne["c"]);
}

TEST(test_operations, test_three){ //21
    MultiSet MultiSetOne;
    MultiSetOne = "{a, b, c}";
    MultiSet MultiSetTwo;
    MultiSetTwo = "{b, c, d}";
    MultiSetOne+=MultiSetTwo;
    EXPECT_TRUE(MultiSetOne["a"] && MultiSetOne["d"] && MultiSetOne["b"] && MultiSetOne["c"]);
    EXPECT_TRUE(MultiSetOne.getCount("b") == 2); // b встречается 2 раза
    EXPECT_TRUE(MultiSetOne.getCount("c") == 2); // c встречается 2 раза
}

TEST(test_operations, test_four){ //22
    MultiSet MultiSetOne;
    MultiSetOne = "{a, b, c}";
    MultiSet MultiSetTwo;
    MultiSetTwo = "{b, c, d}";
    MultiSet MultiSetThree = MultiSetOne + MultiSetTwo;
    EXPECT_TRUE(MultiSetThree["a"] && MultiSetThree["d"] && MultiSetThree["b"] && MultiSetThree["c"]);
    EXPECT_TRUE(MultiSetThree.getCount("b") == 2);
    EXPECT_TRUE(MultiSetThree.getCount("c") == 2);
}

TEST(test_operations, test_five){ //23
    MultiSet MultiSetOne;
    MultiSetOne = "{a, b, c}";
    MultiSet MultiSetTwo;
    MultiSetTwo = "{b, c, d}";
    MultiSet MultiSetThree = MultiSetOne * MultiSetTwo;
    EXPECT_TRUE(!MultiSetThree["a"] && !MultiSetThree["d"] && MultiSetThree["b"] && MultiSetThree["c"]);
    EXPECT_TRUE(MultiSetThree.getCount("b") == 1); // пересечение: берется минимум
    EXPECT_TRUE(MultiSetThree.getCount("c") == 1);
}

TEST(test_operations, test_six){ //24
    MultiSet MultiSetOne;
    MultiSetOne = "{a, b, c, b}"; // b встречается 2 раза
    MultiSet MultiSetTwo;
    MultiSetTwo = "{b, c, d}";
    MultiSet MultiSetThree = MultiSetOne - MultiSetTwo;
    EXPECT_TRUE(MultiSetThree["a"] && !MultiSetThree["d"] && MultiSetThree["b"] && !MultiSetThree["c"]);
    EXPECT_TRUE(MultiSetThree.getCount("b") == 1); // было 2, вычли 1
}

TEST(test_operations, test_seven){ //25
    MultiSet MultiSetOne;
    MultiSetOne = "{a, b, c}";
    MultiSet MultiSetTwo;
    MultiSetTwo = "{b, c, d}";
    MultiSet MultiSetThree = MultiSetOne = MultiSetTwo;
    EXPECT_TRUE(!MultiSetThree["a"] && MultiSetThree["d"] && MultiSetThree["b"] && MultiSetThree["c"] 
        && MultiSetOne["b"] && MultiSetOne["c"] && MultiSetOne["d"]);
}

TEST(test_operations, test_eight){ //26
    MultiSet MultiSetOne;
    MultiSetOne = "{a, b, c, b}"; // b встречается 2 раза
    MultiSet MultiSetTwo;
    MultiSetTwo = "{b, d, g, {b, g, d}, b}"; // b встречается 2 раза
    MultiSetTwo-=MultiSetOne;
    EXPECT_TRUE(!MultiSetTwo["b"] && MultiSetTwo["d"] && MultiSetTwo["g"] && MultiSetTwo["{b,g,d}"] 
        && !MultiSetTwo["a"] && !MultiSetTwo["c"]);
    // Было 2 b, вычли 2 b (минимум из 2 и 2) = 0
}

//булеан

TEST(test_bylean, test_one){ // 27
    MultiSet Set;
    Set = "{a}";
    MultiSet bylean = Set.getBoolean();
    EXPECT_TRUE(bylean["{a}"] && bylean["{}"]);
}

TEST(test_bylean, test_two){ // 28
    MultiSet Set;
    Set = "{a, {a, b}}";
    MultiSet bylean = Set.getBoolean();
    EXPECT_TRUE(bylean["{a,{a,b}}"] && bylean["{}"] && bylean["{a}"] 
        && bylean["{{a,b}}"]);
}

TEST(test_bylean, test_three){ // 29
    MultiSet Set;
    Set = "{a, {a, b}, c}";
    MultiSet bylean = Set.getBoolean();
    EXPECT_TRUE(bylean["{}"] &&
                bylean["{a}"] &&
                bylean["{{a,b}}"] &&
                bylean["{c}"] &&
                bylean["{a,{a,b}}"] &&
                bylean["{a,c}"] &&
                bylean["{{a,b},c}"] &&
                bylean["{a,{a,b},c}"]);
}

TEST(test_bylean, test_four){ // 30
    MultiSet Set;
    Set = "{a, b, c, d, e, f, g, h}"; //2^8
    MultiSet bylean = Set.getBoolean();
    EXPECT_EQ(bylean.getCardinality(), 1<<8);
}

// дополнительные тесты для мультимножеств
TEST(test_multiset_specific, test_repeated_elements){ // 31
    MultiSet MultiSet;
    MultiSet = "{a, a, a, b, b, c}";
    EXPECT_TRUE(MultiSet.getCardinality() == 6);
    EXPECT_TRUE(MultiSet.getDistinctCount() == 3);
    EXPECT_TRUE(MultiSet.getCount("a") == 3);
    EXPECT_TRUE(MultiSet.getCount("b") == 2);
    EXPECT_TRUE(MultiSet.getCount("c") == 1);
}

TEST(test_multiset_specific, test_remove_specific){ // 32
    MultiSet MultiSet;
    MultiSet = "{a, a, a, b}";
    MultiSet.remove("a");
    EXPECT_TRUE(MultiSet.getCount("a") == 2);
    MultiSet.removeAll("a");
    EXPECT_TRUE(MultiSet.getCount("a") == 0);
    EXPECT_TRUE(MultiSet.getCount("b") == 1);
}

TEST(test_multiset_specific, test_intersection_with_repeats){ // 33
    MultiSet MultiSetOne;
    MultiSetOne = "{a, a, b, c}";
    MultiSet MultiSetTwo;
    MultiSetTwo = "{a, b, b, d}";
    MultiSet result = MultiSetOne * MultiSetTwo;
    EXPECT_TRUE(result.getCount("a") == 1); // минимум(2, 1)
    EXPECT_TRUE(result.getCount("b") == 1); // минимум(1, 2)
    EXPECT_TRUE(result.getCount("c") == 0);
    EXPECT_TRUE(result.getCount("d") == 0);
}