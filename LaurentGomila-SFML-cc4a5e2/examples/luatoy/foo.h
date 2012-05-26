class Foo {
  public:
    Foo(lua_State *L) {
      printf("in constructor\n");
    }

    int foo(lua_State *L) {
      printf("in foo\n");
    }

    ~Foo() {
      printf("in destructor\n");
    }

    static const char className[];
    static const Luna<Foo>::RegType Register[];
};

const char Foo::className[] = "Foo";
const Luna<Foo>::RegType Foo::Register[] = {
  { "foo", &Foo::foo },
  { 0 }
};
