#include <gtest/gtest.h>
#include "Sets.hpp"

// Конструкторы и базовые состояния
TEST(SetDefault, DefaultConstructorCreatesEmptySet) { //1
    Set set;
    EXPECT_TRUE(set.isVoid());
}

TEST(SetDefault, EmptySetHasZeroSize) { //2
    Set set;
    EXPECT_FALSE(set.getElInSet().size());
}

TEST(SetDefault, SetWithOnlySpacesIsEmpty) { //3
    Set set;
    set = "{          }";
    EXPECT_TRUE(set.isVoid());
}

// Мощность множеств
TEST(SetCardinality, ComplexNestedSetHasCardinality6) { //4
    Set set;
    set = "{a, b, d, qqq, {sfd,sdsd}, {54, {123, 543, asd}}}";
    EXPECT_TRUE(set.getCardinality() == 6);
}

TEST(SetCardinality, DeeplyNestedSetHasCardinality1) { //5
    Set set;
    set = "{{{{{}}}}}";
    EXPECT_TRUE(set.getCardinality() == 1);
}

TEST(SetCardinality, EmptySetHasCardinality0) { //6
    Set set;
    set = "{}";
    EXPECT_TRUE(set.getCardinality() == 0);
}

TEST(SetCardinality, SetWithNestedSetHasCardinality3) { //7
    Set set;
    set = "{Cat, Dog, {Cat, Dog}}";
    EXPECT_TRUE(set.getCardinality() == 3);
}

TEST(SetCardinality, SetWithDuplicatesHasCardinality5) { //8
    Set set;
    set = "{Cat, Dog, {Cat, Dog}, Cat, Dog, Cat, Dog, Mouse, {Cat, Mouse}}";
    EXPECT_TRUE(set.getCardinality() == 5);
}

TEST(SetCardinality, SetWithSameElementsHasCardinality1) { //9
    Set set;
    set = "{Cat, Cat, Cat, Cat, Cat, Cat, Cat, Cat}";
    EXPECT_TRUE(set.getCardinality() == 1);
}

// Валидность строк
TEST(SetValidation, QuadrupleNestedSetIsValid) { //10
    Set set;
    set = "{{{{}}}}";
    EXPECT_TRUE(set["{{{}}}"]);
}

TEST(SetValidation, SetWithTrailingCommaIsInvalid) { //11
    Set set;
    set = "{adasd, 123123,}";
    EXPECT_TRUE(set.getCardinality() == 0);
}

TEST(SetValidation, SetWithSpacesIsValid) { //12
    Set set;
    set = "{    adasd,      123123           }";
    EXPECT_TRUE(set["adasd"] && set["123123"]);
}

TEST(SetValidation, SetWithNestedElementsIsValid) { //13
    Set set;
    set = "{a, b, {c, d}}";
    EXPECT_TRUE(set["a"] && set["b"] && set["{c,d}"]);
}

TEST(SetValidation, SetWithUnbalancedBracesIsInvalid) { //14
    Set set;
    set = "{a, b, {c, d}}}";
    EXPECT_TRUE(set.isVoid());
}

TEST(SetValidation, SetWithTrailingCommaInNestedSetIsInvalid) { //15
    Set set;
    set = "{a, b, {c, d,}}";
    EXPECT_TRUE(set.isVoid());
}

TEST(SetValidation, MixedValidAndInvalidOperations) { //16
    Set set;
    set += "{a}";
    set += "{b}";
    set += "{asd, asdasd ,asdasds,}";
    EXPECT_TRUE(set.getCardinality() == 2);
}

TEST(SetValidation, StringWithoutBracesIsInvalid) { //17
    Set set;
    set = "a, b, c";
    EXPECT_TRUE(set["a"] && set["b"] && set["c"]);
}

TEST(SetValidation, MixedStringWithoutBracesIsInvalid) { //18
    Set set;
    set = "a, b, {c,d}";
    EXPECT_TRUE(set["a"] && set["b"] && set["{c,d}"]);
}

// Операции над множествами
TEST(SetOperations, CopyConstructorCreatesEqualSet) { //19
    Set setOne;
    setOne = "{a, b, c}";
    Set setTwo = setOne;
    EXPECT_TRUE(setOne == setTwo);
}

TEST(SetOperations, IntersectionOfTwoSets) { //20
    Set setOne;
    setOne = "{a, b, c}";
    Set setTwo;
    setTwo = "{b, c, d}";
    setOne *= setTwo;
    EXPECT_TRUE(!setOne["a"] && setOne["b"] && setOne["c"]);
}

TEST(SetOperations, UnionAssignmentOperator) { //21
    Set setOne;
    setOne = "{a, b, c}";
    Set setTwo;
    setTwo = "{b, c, d}";
    setOne += setTwo;
    EXPECT_TRUE(setOne["a"] && setOne["d"] && setOne["b"] && setOne["c"]);
}

TEST(SetOperations, UnionOperatorCreatesNewSet) { //22
    Set setOne;
    setOne = "{a, b, c}";
    Set setTwo;
    setTwo = "{b, c, d}";
    Set setThree = setOne + setTwo;
    EXPECT_TRUE(setThree["a"] && setThree["d"] && setThree["b"] && setThree["c"]);
}

TEST(SetOperations, IntersectionOperator) { //23
    Set setOne;
    setOne = "{a, b, c}";
    Set setTwo;
    setTwo = "{b, c, d}";
    Set setThree = setOne * setTwo;
    EXPECT_TRUE(!setThree["a"] && !setThree["d"] && setThree["b"] && setThree["c"]);
}

TEST(SetOperations, DifferenceOperator) { //24
    Set setOne;
    setOne = "{a, b, c}";
    Set setTwo;
    setTwo = "{b, c, d}";
    Set setThree = setOne - setTwo;
    EXPECT_TRUE(setThree["a"] && !setThree["d"] && !setThree["b"] && !setThree["c"]);
}

TEST(SetOperations, AssignmentOperator) { //25
    Set setOne;
    setOne = "{a, b, c}";
    Set setTwo;
    setTwo = "{b, c, d}";
    Set setThree = setOne = setTwo;
    EXPECT_TRUE(!setThree["a"] && setThree["d"] && setThree["b"] && setThree["c"] 
        && setOne["b"] && setOne["c"] && setOne["d"]);
}

TEST(SetOperations, DifferenceAssignmentOperator) { //26
    Set setOne;
    setOne = "{a, b, c}";
    Set setTwo;
    setTwo = "{b, d, g, {b, g, d}}";
    setTwo -= setOne;
    EXPECT_TRUE(!setTwo["b"] && setTwo["d"] && setTwo["g"] && setTwo["{b,g,d}"] 
        && !setTwo["a"] && !setTwo["c"]);
}

// Булеан
TEST(SetBoolean, BooleanOfSingleElementSet) { //27
    Set set;
    set = "{a}";
    Set boolean = set.getBoolean();
    EXPECT_TRUE(boolean["{a}"] && boolean["{}"]);
}

TEST(SetBoolean, BooleanOfSetWithNestedElement) { //28
    Set set;
    set = "{a, {a, b}}";
    Set boolean = set.getBoolean();
    EXPECT_TRUE(boolean["{a,{a,b}}"] && boolean["{}"] && boolean["{a}"] 
        && boolean["{{a,b}}"]);
}

TEST(SetBoolean, BooleanOfThreeElementSet) { //29
    Set set;
    set = "{a, {a, b}, c}";
    Set boolean = set.getBoolean();
    EXPECT_TRUE(boolean["{}"] &&
                boolean["{a}"] &&
                boolean["{{a,b}}"] &&
                boolean["{c}"] &&
                boolean["{a,{a,b}}"] &&
                boolean["{a,c}"] &&
                boolean["{{a,b},c}"] &&
                boolean["{a,{a,b},c}"]);
}

TEST(SetBoolean, BooleanOfLargeSetHasCorrectCardinality) { //30
    Set set;
    set = "{a, b, c, d, e, f, g, h}";
    Set boolean = set.getBoolean();
    EXPECT_EQ(boolean.getCardinality(), 1 << 8);
}