//
// Created by Luis Rodrigues on 08/05/2018.
//

#ifndef FORMIGA_STATIC_TEST_HPP
#define FORMIGA_STATIC_TEST_HPP

using namespace std;

class StaticTest {
    public:
        StaticTest() {}
        void setFoo(int value);
        int getFoo();
        void setV8Engine(const shared_ptr<V8Engine> &v8_engine);

    private:
        int value;

};

void StaticTest::setFoo(int v) {
    this->value = v;
}

int StaticTest::getFoo() {
    return this->value;
}

#endif //FORMIGA_STATIC_TEST_HPP
