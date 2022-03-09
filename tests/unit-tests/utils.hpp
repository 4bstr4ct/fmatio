#ifndef ANETIO_TESTS_UNIT_TESTS_UTILS_HPP
#define ANETIO_TESTS_UNIT_TESTS_UTILS_HPP

#include <iostream>
#include <string>
#include <vector>

class UnitTest
{
private:
	::std::string title;
	bool expression;
	::std::string expressionString;
	::std::string onSuccess;
	::std::string onFailure;

public:
	UnitTest(const ::std::string& title,
			 bool expression,
			 const ::std::string& expressionString,
			 const ::std::string& onSuccess,
			 const ::std::string& onFailure)
		: title(title)
		, expression(expression)
		, expressionString(expressionString)
		, onSuccess(onSuccess)
		, onFailure(onFailure)
	{ }

public:
	void perform() const
	{
		if (expression)
		{
			::std::cout << "\033[1;32m[" << title << "] [SUCCESS] (" << expressionString << ") : " << onSuccess << "\033[0m" << ::std::endl;
		}
		else
		{
			::std::cerr << "\033[1;31m[" << title << "] [FAILURE] (" << expressionString << ") : " << onFailure << "\033[0m" << ::std::endl;
		}
	}
};

class UnitTestPool
{
private:
	unsigned int length;
	::std::vector<UnitTest> tests;

public:
	UnitTestPool(const ::std::string& title)
		: tests(), length((unsigned int)title.size())
	{
		::std::cout << "\033[1;33m[ " << title << " ]\033[0m" << ::std::endl;
	}

	~UnitTestPool()
	{
		::std::cout << "\033[1;33m[ ";

		for (unsigned int i = 0; i < this->length; i++)
			::std::cout << "-";

		::std::cout << " ]\033[0m" << ::std::endl;
	}

public:
	void addTest(const ::std::string& title,
				 bool expression,
				 const ::std::string& expressionString,
				 const ::std::string& onSuccess,
				 const ::std::string& onFailure)
	{
		this->tests.push_back(UnitTest(title, expression, expressionString, onSuccess, onFailure));
	}

	void addTest(const UnitTest& test)
	{
		this->tests.push_back(test);
	}

	void performAll()
	{
		for (const auto& test : this->tests)
			test.perform();
	}
};

#define BEGIN_UNIT_TEST(title) \
{ \
	UnitTestPool pool = UnitTestPool(title);

#define END_UNIT_TEST() \
	pool.performAll(); \
}

#define ADD_TEST(title, expression, onSuccess, onFailure) \
	pool.addTest(title, expression, #expression, onSuccess, onFailure);

#define ADD_LINE_BREAK() \
	::std::cout << ::std::endl;

#define TEST_TRUE(title, value, onSuccess, onFailure) \
	pool.addTest(title, value == true, "Empty", onSuccess, onFailure);

#define TEST_FALSE(title, value, onSuccess, onFailure) \
	pool.addTest(title, value == false, "Empty", onSuccess, onFailure);

#define TEST_EQUAL(title, value, other, onSuccess, onFailure) \
	pool.addTest(title, value == other, "Empty", onSuccess, onFailure);

#define TEST_NOT_EQUAL(title, value, other, onSuccess, onFailure) \
	pool.addTest(title, value != other, "Empty", onSuccess, onFailure);

#define TEST_IS_NULLPTR(title, value, onSuccess, onFailure) \
	pool.addTest(title, value == nullptr, "Empty", onSuccess, onFailure);

#define TEST_IS_NOT_NULLPTR(title, value, onSuccess, onFailure) \
	pool.addTest(title, value != nullptr, "Empty", onSuccess, onFailure);

#define TEST_IS_NULL(title, value, onSuccess, onFailure) \
	pool.addTest(title, value == NULL, "Empty", onSuccess, onFailure);

#define TEST_IS_NOT_NULL(title, value, onSuccess, onFailure) \
	pool.addTest(title, value != NULL, "Empty", onSuccess, onFailure);

#endif
