#include "fakeit.hpp"
using namespace fakeit;


class MockExternalClass {
    public:
        int i = 1;
        static MockExternalClass *_mc;
        static MockExternalClass& getInstance() {
            return *MockExternalClass::_mc;
        }
        virtual void doSomething(){
            i++;
        };
};
MockExternalClass *MockExternalClass::_mc;

Mock<MockExternalClass> fakeMockExternalClass;
MockExternalClass &MyInstance = fakeMockExternalClass.get();

class TestClass {
    public:
        void myFunc() {
            MockExternalClass &test = MockExternalClass::getInstance();
            test.doSomething();
        }
        void myFunc2() {
            MyInstance.doSomething();
        }
};


void test_one() {
    Mock<MockExternalClass> mockTest;
    When(Method(mockTest, doSomething)).AlwaysReturn();
    MockExternalClass &mc = mockTest.get();
    MockExternalClass::_mc = &mc;
    TestClass t;
    t.myFunc();
    Verify(Method(mockTest, doSomething)).Once();
}

void test_two() {
    When(Method(fakeMockExternalClass, doSomething)).AlwaysReturn();
    TestClass t;
    t.myFunc2();
    Verify(Method(fakeMockExternalClass, doSomething)).Once();
}

int main() {
    test_two();

}
