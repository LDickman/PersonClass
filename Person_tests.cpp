// Person_test.cpp
// Student: Lauren Dickman
// Date: Tuesday, January 29, 2020

// Unit tests for Person class, CS 223 Lab 1
// Introducing: Google Test for C++
// Barb Wahl, 1-27-2017

#include <sstream>
#include <iostream>
#include <string>
#include "Person.h"
#include "gtest/gtest.h"  // declares the testing framework

using namespace std;

namespace {

// constructor, getFirstName, getLastName, getAge

TEST(TestConstructorANDGetters, ThreeArguments)
{
   Person p1("Mary", "Poppins", 10);
   EXPECT_EQ("Mary", p1.getFirstName());
   EXPECT_EQ("Poppins", p1.getLastName());
   EXPECT_EQ(10, p1.getAge());
}

TEST(TestConstructorANDGetters, TwoArguments)
{
   Person p1("Mary", "Poppins");
   EXPECT_EQ("Mary", p1.getFirstName());
   EXPECT_EQ("Poppins", p1.getLastName());
   EXPECT_EQ(0, p1.getAge());
}

TEST(TestConstructorANDGetters, OneArgument)
{
   Person p1("Mary");
   EXPECT_EQ("Mary", p1.getFirstName());
   EXPECT_EQ("Doe", p1.getLastName());
   EXPECT_EQ(0, p1.getAge());
}

TEST(TestConstructorANDGetters, Default)
{
   Person p1;
   EXPECT_EQ("J", p1.getFirstName());
   EXPECT_EQ("Doe", p1.getLastName());
   EXPECT_EQ(0, p1.getAge());
}

// setFirstName, setLastName, setAge

TEST(TestSetters, SetFirstName)
{
   // first make sure the default constructor works
   // end the test if it doesn't
   Person p1;
   ASSERT_EQ("J", p1.getFirstName());
   ASSERT_EQ("Doe", p1.getLastName());
   ASSERT_EQ(0, p1.getAge());
   p1.setFirstName("Monty");
   EXPECT_EQ(p1.getFirstName(), "Monty");
}

TEST(TestSetters, SetLastName)
{
   // first make sure the default constructor works
   // end the test if it doesn't
   Person p1;
   ASSERT_EQ("J", p1.getFirstName());
   ASSERT_EQ("Doe", p1.getLastName());
   ASSERT_EQ(0, p1.getAge());
   p1.setLastName("Python");
   EXPECT_EQ(p1.getLastName(), "Python");
}

TEST(TestSetters, SetAge)
{
   // first make sure the default constructor works
   // end the test if it doesn't
   Person p1;
   ASSERT_EQ("J", p1.getFirstName());
   ASSERT_EQ("Doe", p1.getLastName());
   ASSERT_EQ(0, p1.getAge());
   p1.setAge(100);
   EXPECT_EQ(p1.getAge(), 100);
}

// getFullName

TEST(TestGetFullName, DefaultPerson)
{
   Person p1;
   EXPECT_EQ(p1.getFullName(), "J Doe");
}

TEST(TestGetFullName, SpecificPerson)
{
   Person p1("Monty", "Python", 100);
   EXPECT_EQ(p1.getFullName(), "Monty Python");
}

// agePerson

TEST(TestAgePerson, CurrentAgeZero)
{
   Person p1("Monty", "Python", 0);
   p1.agePerson();
   EXPECT_EQ(1, p1.getAge());
}

TEST(TestAgePerson, CurrentAgePositive)
{
   Person p1("Monty", "Python", 10);
   p1.agePerson();
   EXPECT_EQ(11, p1.getAge());
}

// test == and != operators together

TEST(TestEqualNotequal, DifferentLastNames)
{
   Person p1("Monty", "Python", 10);
   Person p2("Albert", "Smith", 55);
   EXPECT_TRUE(p1 != p2);
   EXPECT_FALSE(p1 == p2);
}

TEST(TestEqualNotequal, SameLast_DifferentFirstNames)
{
   Person p1("Monty", "Python", 10);
   Person p2("Xavier", "Python", 55);
   EXPECT_TRUE(p1 != p2);
   EXPECT_FALSE(p1 == p2);
}

TEST(TestEqualNotequal, SameFull_DifferentAges)
{
   Person p1("Xavier", "Python", 10);
   Person p2("Xavier", "Python", 55);
   EXPECT_TRUE(p1 != p2);
   EXPECT_FALSE(p1 == p2);
}

TEST(TestEqualNotequal, SameFull_SameAge)
{
   Person p1("Xavier", "Python", 55);
   Person p2("Xavier", "Python", 55);
   EXPECT_TRUE(p1 == p2);
   EXPECT_FALSE(p1 != p2);
}

TEST(TestEqualNotequal, SameFirst_SameAge_NotEqual)
{
   Person p1("Xavier", "Anderson", 55);
   Person p2("Xavier", "Python", 55);
   EXPECT_TRUE(p1 != p2);
   EXPECT_FALSE(p1 == p2);
}

TEST(TestEqualNotequal, SameAge_LnamePer1BEFORELnamePer2_FnamePer1BEFOREFnamePer2)
{
   Person p1("Polly", "Anderson", 55);
   Person p2("Xavier", "Python", 55);
   EXPECT_TRUE(p1 != p2);
   EXPECT_FALSE(p1 == p2);
}

TEST(TestEqualNotequal, DiffAges_LnamePer1BEFORELnamePer2_FnamePer1AFTERFnamePer2)
{
   Person p1("Polly", "Anderson", 50);
   Person p2("Andy", "Python", 55);
   EXPECT_TRUE(p1 != p2);
   EXPECT_FALSE(p1 == p2);
}

TEST(TestEqualNotequal, DiffAges_LnamePer1AFTERLnamePer2_FnamePer1BEFOREFnamePer2)
{
   Person p1("Amy", "Anderson", 50);
   Person p2("Jim", "Aardvark", 55);
   EXPECT_TRUE(p1 != p2);
   EXPECT_FALSE(p1 == p2);
}

// operator+, Person addition

TEST(TestAddition, Typical)
{
   Person p1("Alex", "Allain", 50);
   Person p2("Michael", "Main", 40);
   Person p3 = p1 + p2;
   // Baby Allain-Main has age 0
   EXPECT_EQ(p3.getFirstName(), "Baby");
   EXPECT_EQ(p3.getLastName(), "Allain-Main");
   EXPECT_EQ(p3.getAge(), 0);
}

// operator<<, stream output of Person objects

TEST(TestStreamOutput, Typical)
{
   // 1. Create local variables:
   //  - a stringstream for output, called out
   //  - a string for storing the expected message, called correct
   //  - a Person with specific name and age, called p
   stringstream out;
   string correct;
   Person p("Mr. Grey", "Davis", 10);
   // 2. Store the expected message in the string variable `correct`
   // Get it exactly right!
   correct = "Person: Mr. Grey Davis, age 10";
   // 3. Use the output stream variable `out` and the operator `<<` to
   // (hopefully) put the expected message for person `p` into the stream
   out << p;
   // 4. Test whether the `out.str()` result equals the expected message string.
   EXPECT_EQ(out.str(), correct);
}

TEST(TestStreamOutput, Chaining)
{
   // 1. Create local variables:
   //  - a stringstream for output, called out2
   //  - a string for storing the expected message, called correct
   //  - two Person objects
   stringstream out2;
   string correct;
   Person g("Mr. Grey", "Davis", 10);
   Person x("Xerea", "Davis", 5);
   // 2. Store the expected message in the string variable `correct`
   // Get it exactly right!
   correct = "Person: Mr. Grey Davis, age 10\nPerson: Xerea Davis, age 5";
   // 3. Use the output stream variable `out` and the operator `<<` to
   // (hopefully) put the expected message for person `p` into the stream
   out2 << g << endl << x;
   // 4. Test whether the `out.str()` result equals the expected message string.
   EXPECT_EQ(out2.str(), correct);
}

// operator>>, stream input of Person objects

TEST(TestStreamInput, Typical)
{
   // 1. Create local variables:
   //  - a stringstream for input, called in
   //  - a string for storing the input to be read, called instring
   //  - a Person with specific name and age, called p
   stringstream in;
   Person p("Mr. Grey", "Davis", 10);
   // 2. Store the another person's info into stringstream `in`.
   in << "Person: Ziggy Wilson, Age 6\n";
   // 3. Take the info from stringstream `in` and use it to change person `p`
   // using the stream extraction operator, `>>`.
   in >> p;
   // 4. Test whether the `p` information now equals the expected result.
   EXPECT_EQ(p.getFirstName(), "Ziggy");
   EXPECT_EQ(p.getLastName(), "Wilson");
   EXPECT_EQ(p.getAge(), 6);
}

TEST(TestStreamInput, Chaining)
{
   // 1. Create local variables:
   //  - a stringstream for input, called in2
   //  - a string for storing the input to be read, called instring
   //  - two Person objects
   stringstream in2;
   Person g("Mr. Grey", "Davis", 10);
   Person x("Xerea", "Davis", 5);
   // 2. Store the two other persons' info into stringstream `in`.
   in2 << "Person: Ziggy Wilson, Age 6\nPerson: Ruthie Wilson, Age 1";
   // 3. Take the info from stringstream `in` and use it to change
   // the two person objects using the stream extraction operator, `>>`.
   in2 >> g >> x;
   // 4. Test whether the `g` and `x` information now equals the expected
   // result.
   EXPECT_EQ(g.getFirstName(), "Ziggy");
   EXPECT_EQ(g.getLastName(), "Wilson");
   EXPECT_EQ(g.getAge(), 6);
   EXPECT_EQ(x.getFirstName(), "Ruthie");
   EXPECT_EQ(x.getLastName(), "Wilson");
   EXPECT_EQ(x.getAge(), 1);
}

// operator<, the less-than operator

// ******** STUDENT NEEDS TO PROVIDE A SET OF TESTS HERE FOR OPERATOR< ********
// Use StudentTestLessThan as the test suite name. For example:
//
// TEST(StudentTestLessThan, DiffLastNames_AlessthanB_ReturnTrue) for the test
// case where two persons have different last names and Person A < Person B.

TEST(StudentTestLessThan, DiffLastNames_AlessthanB_ReturnTrue)
{
   Person p1("Zoe", "Anderson", 14);
   Person p2("Zoe", "Python", 14);
   EXPECT_TRUE(p1 < p2);
   EXPECT_FALSE(p2 < p1);
}

TEST(StudentTestLessThan, DiffFirstNames_AlessthanB_ReturnTrue)
{
   Person p1("Alex", "Stark", 20);
   Person p2("Tony", "Stark", 20);
   EXPECT_TRUE(p1 < p2);
   EXPECT_FALSE(p2 < p1);
}

TEST(StudentTestLessThan, DiffAges_AlessthanB_ReturnTrue)
{
   Person p1("Steve", "Rogers", 20);
   Person p2("Steve", "Rogers", 77);
   EXPECT_TRUE(p1 < p2);
   EXPECT_FALSE(p2 < p1);
}

TEST(StudentTestLessThan, DiffAges_DiffFirstNames_DiffLastNames_AlessthanB_ReturnTrue)
{
   Person p1("Link", "Elf", 33);
   Person p2("Mario", "Plumber", 36);
   EXPECT_TRUE(p1 < p2);
   EXPECT_FALSE(p2 < p1);
}

TEST(StudentTestLessThan, SameAges_SameFirstNames_SameLastNames_AlessthanB_ReturnFalse)
{
   Person p1("Clark", "Kent", 45);
   Person p2("Clark", "Kent", 45);
   EXPECT_FALSE(p1 < p2);
   EXPECT_FALSE(p2 < p1);
}

} // namespace

// main() for testing -- boilerplate
int main(int argc, char* argv[]){
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
