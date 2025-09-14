#include <gtest/gtest.h>
#include "MultiSets.hpp"

// Конструкторы и базовые состояния
TEST(MultiSetDefault, DefaultConstructorCreatesEmptyMultiSet) { //1
    MultiSet MultiSet;
    EXPECT_TRUE(MultiSet.isVoid());
}

TEST(MultiSetDefault, EmptyMultiSetHasZeroSize) { //2
    MultiSet MultiSet;
    EXPECT_FALSE(MultiSet.getElInMultiSet().size());
}

TEST(MultiSetDefault, MultiSetWithOnlySpacesIsEmpty) { //3
    MultiSet MultiSet;
    MultiSet = "{          }";
    EXPECT_TRUE(MultiSet.isVoid());
}

// Мощность мультимножеств
TEST(MultiSetCardinality, ComplexNestedMultiSetHasCardinality6) { //4
    MultiSet MultiSet;
    MultiSet = "{a, b, d, qqq, {sfd,sdsd}, {54, {123, 543, asd}}}";
    EXPECT_TRUE(MultiSet.getCardinality() == 6);
}

TEST(MultiSetCardinality, DeeplyNestedMultiSetHasCardinality1) { //5
    MultiSet MultiSet;
    MultiSet = "{{{{{}}}}}";
    EXPECT_TRUE(MultiSet.getCardinality() == 1);
}

TEST(MultiSetCardinality, EmptyMultiSetHasCardinality0) { //6
    MultiSet MultiSet;
    MultiSet = "{}";
    EXPECT_TRUE(MultiSet.getCardinality() == 0);
}

TEST(MultiSetCardinality, MultiSetWithNestedSetHasCardinality3) { //7
    MultiSet MultiSet;
    MultiSet = "{Cat, Dog, {Cat, Dog}}";
    EXPECT_TRUE(MultiSet.getCardinality() == 3);
}

TEST(MultiSetCardinality, MultiSetWithDuplicatesHasCardinality9) { //8
    MultiSet MultiSet;
    MultiSet = "{Cat, Dog, {Cat, Dog}, Cat, Dog, Cat, Dog, Mouse, {Cat, Mouse}}";
    EXPECT_TRUE(MultiSet.getCardinality() == 9);
}

TEST(MultiSetCardinality, MultiSetWithSameElementsHasCorrectCounts) { //9
    MultiSet MultiSet;
    MultiSet = "{Cat, Cat, Cat, Cat, Cat, Cat, Cat, Cat}";
    EXPECT_TRUE(MultiSet.getCardinality() == 8);
    EXPECT_TRUE(MultiSet.getDistinctCount() == 1);
    EXPECT_TRUE(MultiSet.getCount("Cat") == 8);
}

// Валидность строк
TEST(MultiSetValidation, QuadrupleNestedMultiSetIsValid) { //10
    MultiSet MultiSet;
    MultiSet = "{{{{}}}}";
    EXPECT_TRUE(MultiSet["{{{}}}"]);
}

TEST(MultiSetValidation, MultiSetWithTrailingCommaIsInvalid) { //11
    MultiSet MultiSet;
    MultiSet = "{adasd, 123123,}";
    EXPECT_TRUE(MultiSet.getCardinality() == 0);
}

TEST(MultiSetValidation, MultiSetWithSpacesIsValid) { //12
    MultiSet MultiSet;
    MultiSet = "{    adasd,      123123           }";
    EXPECT_TRUE(MultiSet["adasd"] && MultiSet["123123"]);
}

TEST(MultiSetValidation, MultiSetWithNestedElementsIsValid) { //13
    MultiSet MultiSet;
    MultiSet = "{a, b, {c, d}}";
    EXPECT_TRUE(MultiSet["a"] && MultiSet["b"] && MultiSet["{c,d}"]);
}

TEST(MultiSetValidation, MultiSetWithUnbalancedBracesIsInvalid) { //14
    MultiSet MultiSet;
    MultiSet = "{a, b, {c, d}}}";
    EXPECT_TRUE(MultiSet.isVoid());
}

TEST(MultiSetValidation, MultiSetWithTrailingCommaInNestedSetIsInvalid) { //15
    MultiSet MultiSet;
    MultiSet = "{a, b, {c, d,}}";
    EXPECT_TRUE(MultiSet.isVoid());
}

TEST(MultiSetValidation, MixedValidAndInvalidOperations) { //16
    MultiSet MultiSet;
    MultiSet += "{a}";
    MultiSet += "{b}";
    MultiSet += "{asd, asdasd ,asdasds,}";
    EXPECT_TRUE(MultiSet.getCardinality() == 2);
}

TEST(MultiSetValidation, StringWithoutBracesIsInvalid) { //17
    MultiSet MultiSet;
    MultiSet = "a, b, c";
    EXPECT_TRUE(MultiSet["a"] && MultiSet["b"] && MultiSet["c"]);
}

TEST(MultiSetValidation, MixedStringWithoutBracesIsInvalid) { //18
    MultiSet MultiSet;
    MultiSet = "a, b, {c,d}";
    EXPECT_TRUE(MultiSet["a"] && MultiSet["b"] && MultiSet["{c,d}"]);
}

// Операции над мультимножествами
TEST(MultiSetOperations, CopyConstructorCreatesEqualMultiSet) { //19
    MultiSet MultiSetOne;
    MultiSetOne = "{a, b, c}";
    MultiSet MultiSetTwo = MultiSetOne;
    EXPECT_TRUE(MultiSetOne == MultiSetTwo);
}

TEST(MultiSetOperations, IntersectionOfTwoMultiSets) { //20
    MultiSet MultiSetOne;
    MultiSetOne = "{a, b, c}";
    MultiSet MultiSetTwo;
    MultiSetTwo = "{b, c, d}";
    MultiSetOne *= MultiSetTwo;
    EXPECT_TRUE(!MultiSetOne["a"] && MultiSetOne["b"] && MultiSetOne["c"]);
}

TEST(MultiSetOperations, UnionAssignmentOperatorWithCounts) { //21
    MultiSet MultiSetOne;
    MultiSetOne = "{a, b, c}";
    MultiSet MultiSetTwo;
    MultiSetTwo = "{b, c, d}";
    MultiSetOne += MultiSetTwo;
    EXPECT_TRUE(MultiSetOne["a"] && MultiSetOne["d"] && MultiSetOne["b"] && MultiSetOne["c"]);
    EXPECT_TRUE(MultiSetOne.getCount("b") == 2);
    EXPECT_TRUE(MultiSetOne.getCount("c") == 2);
}

TEST(MultiSetOperations, UnionOperatorCreatesNewMultiSet) { //22
    MultiSet MultiSetOne;
    MultiSetOne = "{a, b, c}";
    MultiSet MultiSetTwo;
    MultiSetTwo = "{b, c, d}";
    MultiSet MultiSetThree = MultiSetOne + MultiSetTwo;
    EXPECT_TRUE(MultiSetThree["a"] && MultiSetThree["d"] && MultiSetThree["b"] && MultiSetThree["c"]);
    EXPECT_TRUE(MultiSetThree.getCount("b") == 2);
    EXPECT_TRUE(MultiSetThree.getCount("c") == 2);
}

TEST(MultiSetOperations, IntersectionOperatorWithCounts) { //23
    MultiSet MultiSetOne;
    MultiSetOne = "{a, b, c}";
    MultiSet MultiSetTwo;
    MultiSetTwo = "{b, c, d}";
    MultiSet MultiSetThree = MultiSetOne * MultiSetTwo;
    EXPECT_TRUE(!MultiSetThree["a"] && !MultiSetThree["d"] && MultiSetThree["b"] && MultiSetThree["c"]);
    EXPECT_TRUE(MultiSetThree.getCount("b") == 1);
    EXPECT_TRUE(MultiSetThree.getCount("c") == 1);
}

TEST(MultiSetOperations, DifferenceOperatorWithCounts) { //24
    MultiSet MultiSetOne;
    MultiSetOne = "{a, b, c, b}";
    MultiSet MultiSetTwo;
    MultiSetTwo = "{b, c, d}";
    MultiSet MultiSetThree = MultiSetOne - MultiSetTwo;
    EXPECT_TRUE(MultiSetThree["a"] && !MultiSetThree["d"] && MultiSetThree["b"] && !MultiSetThree["c"]);
    EXPECT_TRUE(MultiSetThree.getCount("b") == 1);
}

TEST(MultiSetOperations, AssignmentOperator) { //25
    MultiSet MultiSetOne;
    MultiSetOne = "{a, b, c}";
    MultiSet MultiSetTwo;
    MultiSetTwo = "{b, c, d}";
    MultiSet MultiSetThree = MultiSetOne = MultiSetTwo;
    EXPECT_TRUE(!MultiSetThree["a"] && MultiSetThree["d"] && MultiSetThree["b"] && MultiSetThree["c"] 
        && MultiSetOne["b"] && MultiSetOne["c"] && MultiSetOne["d"]);
}

TEST(MultiSetOperations, DifferenceAssignmentOperatorWithCounts) { //26
    MultiSet MultiSetOne;
    MultiSetOne = "{a, b, c, b}";
    MultiSet MultiSetTwo;
    MultiSetTwo = "{b, d, g, {b, g, d}, b}";
    MultiSetTwo -= MultiSetOne;
    EXPECT_TRUE(!MultiSetTwo["b"] && MultiSetTwo["d"] && MultiSetTwo["g"] && MultiSetTwo["{b,g,d}"] 
        && !MultiSetTwo["a"] && !MultiSetTwo["c"]);
}

// Булеан
TEST(MultiSetBoolean, BooleanOfSingleElementMultiSet) { //27
    MultiSet Set;
    Set = "{a}";
    MultiSet bylean = Set.getBoolean();
    EXPECT_TRUE(bylean["{a}"] && bylean["{}"]);
}

TEST(MultiSetBoolean, BooleanOfMultiSetWithNestedElement) { //28
    MultiSet Set;
    Set = "{a, {a, b}}";
    MultiSet bylean = Set.getBoolean();
    EXPECT_TRUE(bylean["{a,{a,b}}"] && bylean["{}"] && bylean["{a}"] 
        && bylean["{{a,b}}"]);
}

TEST(MultiSetBoolean, BooleanOfThreeElementMultiSet) { //29
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

TEST(MultiSetBoolean, BooleanOfLargeMultiSetHasCorrectCardinality) { //30
    MultiSet Set;
    Set = "{a, b, c, d, e, f, g, h}";
    MultiSet bylean = Set.getBoolean();
    EXPECT_EQ(bylean.getCardinality(), 1 << 8);
}

// Специфичные тесты для мультимножеств
TEST(MultiSetSpecific, RepeatedElementsHaveCorrectCounts) { //31
    MultiSet MultiSet;
    MultiSet = "{a, a, a, b, b, c}";
    EXPECT_TRUE(MultiSet.getCardinality() == 6);
    EXPECT_TRUE(MultiSet.getDistinctCount() == 3);
    EXPECT_TRUE(MultiSet.getCount("a") == 3);
    EXPECT_TRUE(MultiSet.getCount("b") == 2);
    EXPECT_TRUE(MultiSet.getCount("c") == 1);
}

TEST(MultiSetSpecific, RemoveSpecificElements) { //32
    MultiSet MultiSet;
    MultiSet = "{a, a, a, b}";
    MultiSet.remove("a");
    EXPECT_TRUE(MultiSet.getCount("a") == 2);
    MultiSet.removeAll("a");
    EXPECT_TRUE(MultiSet.getCount("a") == 0);
    EXPECT_TRUE(MultiSet.getCount("b") == 1);
}

TEST(MultiSetSpecific, IntersectionWithRepeatedElements) { //33
    MultiSet MultiSetOne;
    MultiSetOne = "{a, a, b, c}";
    MultiSet MultiSetTwo;
    MultiSetTwo = "{a, b, b, d}";
    MultiSet result = MultiSetOne * MultiSetTwo;
    EXPECT_TRUE(result.getCount("a") == 1);
    EXPECT_TRUE(result.getCount("b") == 1);
    EXPECT_TRUE(result.getCount("c") == 0);
    EXPECT_TRUE(result.getCount("d") == 0);
}