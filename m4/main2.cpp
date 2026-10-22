// Uncomment the next line to use precompiled headers
//#include "pch.h"
// uncomment the next line if you do not use precompiled headers
#include "gtest/gtest.h"
//
// the global test environment setup and tear down
// you should not need to change anything here
class Environment : public ::testing::Environment
{
public:
  ~Environment() override {}

  // Override this to define how to set up the environment.
  void SetUp() override
  {
    //  initialize random seed
    srand(time(nullptr));
  }

  // Override this to define how to tear down the environment.
  void TearDown() override {}
};

// create our test class to house shared data between tests
// you should not need to change anything here
class CollectionTest : public ::testing::Test
{
protected:
  // create a smart point to hold our collection
  std::unique_ptr<std::vector<int>> collection;

  void SetUp() override
  { // create a new collection to be used in the test
    collection.reset( new std::vector<int>);
  }

  void TearDown() override
  { //  erase all elements in the collection, if any remain
    collection->clear();
    // free the pointer
    collection.reset(nullptr);
  }

  // helper function to add random values from 0 to 99 count times to the collection
  void add_entries(int count)
  {
    assert(count > 0);
    for (auto i = 0; i < count; ++i)
      collection->push_back(rand() % 100);
  }
};

// When should you use the EXPECT_xxx or ASSERT_xxx macros?
// Use ASSERT when failure should terminate processing, such as the reason for the test case.
// Use EXPECT when failure should notify, but processing should continue

// Test that a collection is empty when created.
// Prior to calling this (and all other TEST_F defined methods),
//  CollectionTest::StartUp is called.
// Following this method (and all other TEST_F defined methods),
//  CollectionTest::TearDown is called
TEST_F(CollectionTest, CollectionSmartPointerIsNotNull)
{
  // is the collection created
  ASSERT_TRUE(collection);

  // if empty, the size must be 0
  ASSERT_NE(collection.get(), nullptr);
}

// Test that a collection is empty when created.
TEST_F(CollectionTest, IsEmptyOnCreate)
{
  // is the collection empty?
  ASSERT_TRUE(collection->empty());

  // if empty, the size must be 0
  ASSERT_EQ(collection->size(), 0);
}

/* Comment this test out to prevent the test from running
 * Uncomment this test to see a failure in the test explorer */
// TEST_F(CollectionTest, AlwaysFail)
// {
//   FAIL();
// }

TEST_F(CollectionTest, CanAddToEmptyVector)
{
  // is the collection empty?
  // if empty, the size must be 0

  add_entries(1);

  // is the collection still empty?
  ASSERT_NE(collection->size(), 0);
  // if not empty, what must the size be?
  ASSERT_EQ(collection->size(), 1);
}

TEST_F(CollectionTest, CanAddFiveValuesToVector)
{
  add_entries(5);

  ASSERT_NE(collection->size(), 0);
  ASSERT_EQ(collection->size(), 5);
}

TEST_F(CollectionTest, MaxSizeIsGreaterThanOrEqualToSize)
{
  ASSERT_GE(collection->max_size(), collection->size());

  add_entries(1);
  ASSERT_GE(collection->max_size(), collection->size());

  add_entries(4); // total entries now 5
  ASSERT_GE(collection->max_size(), collection->size());

  add_entries(5); // total entries now 10
  ASSERT_GE(collection->max_size(), collection->size());
}

TEST_F(CollectionTest, CapacityIsGreaterThanOrEqualToSize)
{
  ASSERT_GE(collection->capacity(), collection->size());

  add_entries(1);
  ASSERT_GE(collection->capacity(), collection->size());

  add_entries(4); // total entries now 5
  ASSERT_GE(collection->capacity(), collection->size());

  add_entries(5); // total entries now 10
  ASSERT_GE(collection->capacity(), collection->size());
}

TEST_F(CollectionTest, ResizeIncreasesCollection)
{
  add_entries(5);
  collection->resize(10);
  ASSERT_EQ(collection->size(), 10);
}

TEST_F(CollectionTest, ResizeDecreasesCollection)
{
  add_entries(10);
  collection->resize(5);
  ASSERT_EQ(collection->size(), 5);
}

TEST_F(CollectionTest, ResizeToZero)
{
  add_entries(5);
  collection->resize(0);
  ASSERT_EQ(collection->size(), 0);
}

TEST_F(CollectionTest, ClearErasesCollection)
{
  add_entries(5);
  collection->clear();
  ASSERT_EQ(collection->size(), 0);
  ASSERT_TRUE(collection->empty());
}

TEST_F(CollectionTest, EraseBeginEndErasesCollection)
{
  add_entries(5);
  collection->erase(collection->begin(), collection->end());
  ASSERT_EQ(collection->size(), 0);
  ASSERT_TRUE(collection->empty());
}

TEST_F(CollectionTest, ReserveIncreasesCapacityButNotSize)
{
  add_entries(5);
  size_t old_size = collection->size();
  size_t old_capacity = collection->capacity();

  collection->reserve(old_capacity + 10);

  ASSERT_EQ(collection->size(), old_size);
  ASSERT_GT(collection->capacity(), old_capacity);
}

// NOTE: This is a negative test
TEST_F(CollectionTest, AtThrowsOutOfRangeException)
{
  add_entries(5);
  ASSERT_THROW(collection->at(10), std::out_of_range);
}

// TODO: Create 2 unit tests of your own to test something on the collection - do 1 positive & 1 negative
TEST_F(CollectionTest, CanAccessElementsUsingAt)
{
  add_entries(5);
  for (size_t i = 0; i < collection->size(); ++i)
  {
    ASSERT_NO_THROW(collection->at(i));
  }
}

TEST_F(CollectionTest, CannotSetNegativeSize)
{
  add_entries(5);
  ASSERT_THROW(collection->resize(-1), std::length_error);
}

