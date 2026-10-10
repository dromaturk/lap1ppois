#include <iostream>
#include <sstream>
#ifdef USE_UNITTEST
#include <UnitTest++/UnitTest++.h>
#endif
#include "set.h"

#ifdef USE_UNITTEST
SUITE(SetTestSuite) {

    TEST(DefaultConstructor_Empty) {
        Set s;
        CHECK(s.isEmpty());
        CHECK_EQUAL(0, s.size());
        CHECK_EQUAL("{}", s.toString());
    }

    TEST(StringConstructor_Basic) {
        Set s("{a, b, c}");
        CHECK_EQUAL(3, s.size());
    }

    TEST(CharPtrConstructor) {
        Set s("{x, y}");
        CHECK_EQUAL(2, s.size());
    }

    TEST(CopyConstructor) {
        Set a("{a, b}");
        Set b(a);
        CHECK(a == b);
        b.add("c");
        CHECK(a != b);
    }
    TEST(ParseAndPrint) {
        Set s("{b, a, {b, a}, {}}");
        CHECK_EQUAL("{a, b, {a, b}, {}}", s.toString());
    }

    TEST(ParseNested) {
        Set s("{{a, b}, {c}}");
        CHECK_EQUAL(2, s.size());
        CHECK(s["{a, b}"]);
        CHECK(s["{c}"]);
    }

    TEST(DuplicatesIgnored) {
        Set s("{a, a, {a, b}, {b, a}}");
        CHECK_EQUAL(2, s.size());
    }

    TEST(TrimAndWhitespace) {
        Set s("   { a ,  b }   ");
        CHECK_EQUAL("{a, b}", s.toString());
    }

    TEST(AddAndRemove) {
        Set s;
        s.add("a");
        s.add("{x, y}");
        CHECK_EQUAL(2, s.size());
        s.remove("a");
        CHECK(!s["a"]);
        CHECK(s["{y, x}"]);
    }

    TEST(AddDuplicate_NoChange) {
        Set s("{a}");
        s.add("a");
        CHECK_EQUAL(1, s.size());
    }

    TEST(AddEmpty_Ignored) {
        Set s;
        s.add("   ");
        CHECK(s.isEmpty());
    }

    TEST(RemoveNonExistent_NoChange) {
        Set s("{a}");
        s.remove("z");
        CHECK_EQUAL(1, s.size());
    }
    TEST(MembershipOperator) {
        Set s("{a, {b, c}}");
        CHECK(s["a"]);
        CHECK(s["{c, b}"]);
        CHECK(!s["z"]);
    }

    TEST(UnionOperators) {
        Set a("{a, b}");
        Set b("{b, c}");
        CHECK_EQUAL("{a, b, c}", (a + b).toString());
        a += b;
        CHECK_EQUAL(3, a.size());
    }

    TEST(IntersectionOperators) {
        Set a("{a, b}");
        Set b("{b, c}");
        CHECK_EQUAL("{b}", (a * b).toString());
        a *= b;
        CHECK_EQUAL(1, a.size());
    }

    TEST(DifferenceOperators) {
        Set a("{a, b}");
        Set b("{b, c}");
        CHECK_EQUAL("{a}", (a - b).toString());
        a -= b;
        CHECK(a["a"]);
    }

    TEST(UnionWithEmpty) {
        Set a("{a}");
        Set b;
        CHECK_EQUAL("{a}", (a + b).toString());
    }

    TEST(PowerSet_Empty) {
        Set s;
        Set p = s.powerSet();
        CHECK_EQUAL(1, p.size());
        CHECK(p["{}"]);
    }

    TEST(PowerSet) {
        Set s("{a, b}");
        Set p = s.powerSet();
        CHECK_EQUAL(4, p.size());
        CHECK(p["{}"]);
        CHECK(p["{a}"]);
        CHECK(p["{b}"]);
        CHECK(p["{a, b}"]);
    }

    TEST(PowerSet_ThreeElements) {
        Set s("{a, b, c}");
        CHECK_EQUAL(8, s.powerSet().size());
    }

    TEST(ComparisonAndAssignmentOperators) {
        Set a("{a, b}");
        Set b("{b, a}");
        Set c;
        CHECK(a == b);
        CHECK(a != c);
        c = a;
        CHECK(c == a);
        c = c;               
        CHECK(c == a);
    }

    TEST(StreamOperators) {
        std::stringstream ss;
        Set in("{a, {b}}");
        ss << in;
        Set out;
        ss >> out;
        CHECK(in == out);
    }

    TEST(StreamOperator_EmptySet) {
        std::stringstream ss;
        ss << "{}";
        Set s;
        ss >> s;
        CHECK(s.isEmpty());
    }
}
#endif

void interactiveMode() {}

int main() {}
