#ifndef _SCHEME_CALCULATOR_UNITTEST_CPP_
#define _SCHEME_CALCULATOR_UNITTEST_CPP_ 1


#include "gtest/gtest.h"
#include "scheme_calculator.hpp"
#include <string>
#include <vector>


namespace {

    struct ExpResult
    {
        ExpResult(const std::string& s, int v) : exp(s), result(v) { }
        std::string exp;
        int result;
    };

    TEST(scheme_calculator, scheme_calculator_add)
    {
        std::vector<ExpResult> v;
        v.push_back(ExpResult("(+ 1 2)", 3));
        v.push_back(ExpResult("(+ 1 2 3 4 5)", 15));
        v.push_back(ExpResult("(+ 1 (+ 2 3) (+ 4 5))", 15));
        v.push_back(ExpResult("(+ (+ 1 2) (+ 3 (+ 4 (+ 5 6))))", 21));

        for (size_t i = 0; i < v.size(); ++i)
        {
            const std::string& s = v[i].exp;
            scheme::SchemeValue* exp = scheme::read(s);
            scheme::SchemeValue* result = scheme::calculator::eval(exp);
            int value = scheme::calculator::get_eval_value(result);
            scheme::free_single_obj(result);
            scheme::free_obj(exp);
            ASSERT_EQ(value, v[i].result);
        }
    }

    TEST(scheme_calculator, scheme_calculator_sub)
    {
        std::vector<ExpResult> v;
        v.push_back(ExpResult("(- 100 64)", 36));
        v.push_back(ExpResult("(- 100 22 33 44 55)", -54));
        v.push_back(ExpResult("(- 100 (- 26 12) (- 94 85))", 77));
        v.push_back(ExpResult("(- (- 666 250) (- 333 (- 40 (- 51 30))))", 102));

        for (size_t i = 0; i < v.size(); ++i)
        {
            const std::string& s = v[i].exp;
            scheme::SchemeValue* exp = scheme::read(s);
            scheme::SchemeValue* result = scheme::calculator::eval(exp);
            int value = scheme::calculator::get_eval_value(result);
            scheme::free_single_obj(result);
            scheme::free_obj(exp);
            ASSERT_EQ(value, v[i].result);
        }
    }

    TEST(scheme_calculator, scheme_calculator_mul)
    {
        std::vector<ExpResult> v;
        v.push_back(ExpResult("(* 2 3)", 6));
        v.push_back(ExpResult("(* 1 2 3 4 5)", 120));
        v.push_back(ExpResult("(* 2 (* 3 4))", 24));
        v.push_back(ExpResult("(* 2 (* 3 4) (* 5 (* 6 7)))", 5040));

        for (size_t i = 0; i < v.size(); ++i)
        {
            const std::string& s = v[i].exp;
            scheme::SchemeValue* exp = scheme::read(s);
            scheme::SchemeValue* result = scheme::calculator::eval(exp);
            int value = scheme::calculator::get_eval_value(result);
            scheme::free_single_obj(result);
            scheme::free_obj(exp);
            ASSERT_EQ(value, v[i].result);
        }
    }

    TEST(scheme_calculator, scheme_calculator_div)
    {
        std::vector<ExpResult> v;
        v.push_back(ExpResult("(/ 6 2)", 3));
        v.push_back(ExpResult("(/ 9 2)", 4));
        v.push_back(ExpResult("(/ 100 2 5 10)", 1));
        v.push_back(ExpResult("(/ 200 (/ 12 3))", 50));
        v.push_back(ExpResult("(/ 666 (/ 30 10) (/ 555 (/ 60 12)))", 2));

        for (size_t i = 0; i < v.size(); ++i)
        {
            const std::string& s = v[i].exp;
            scheme::SchemeValue* exp = scheme::read(s);
            scheme::SchemeValue* result = scheme::calculator::eval(exp);
            int value = scheme::calculator::get_eval_value(result);
            scheme::free_single_obj(result);
            scheme::free_obj(exp);
            ASSERT_EQ(value, v[i].result);
        }
    }

    TEST(scheme_calculator, scheme_calculator_cal)
    {
        std::vector<ExpResult> v;
        v.push_back(ExpResult("(* (+ 1 2) (+ 3 4))", 21));
        v.push_back(ExpResult("(* (- 2 1) (+ 3 4))", 7));
        v.push_back(ExpResult("(+ (* 2 1) (+ 3 4) (- 10 2) (/ 8 2))", 21));
        v.push_back(ExpResult("(* (/ 10 3) (+ 5 1) (- 9 7))", 36));
        v.push_back(ExpResult("(+ (* 2 3 (- 4 2 (/ 6 3))) (* 111 6))", 666));

        for (size_t i = 0; i < v.size(); ++i)
        {
            const std::string& s = v[i].exp;
            scheme::SchemeValue* exp = scheme::read(s);
            scheme::SchemeValue* result = scheme::calculator::eval(exp);
            int value = scheme::calculator::get_eval_value(result);
            scheme::free_single_obj(result);
            scheme::free_obj(exp);
            ASSERT_EQ(value, v[i].result);
        }
    }

}


#endif
