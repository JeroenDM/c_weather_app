#define OPTION(type) struct{\
type value;\
int has_value;\
}

#define SOME(type, name, value) struct{\
type value;\
int has_value;\
} name = {value, 1}

#define NONE(type, name) struct{\
type value;\
int has_value;\
} name;\
name.has_value = 0


OPTION(int) try_add(int a)
{
    if (a < 5){
        SOME(int, result, a + 5);
        return result;
    } else {
        NONE(int, result);
        return result;
    }
}

int main()
{
    
    OPTION(int) a = try_add(3);

    if (a.has_value) {
        int b = a.value;
    }

    // struct {double a; double b;} s = {1, 2};

    return 0;
}
