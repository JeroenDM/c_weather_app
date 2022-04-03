#include <stdio.h>


typedef struct MaybeTag {
    void* value;
    int has_value;
} Maybe;

// Maybe maybe_some(void* value)
// {
//     Maybe m = {value, 1};
//     return m;
// }

#define maybe_some(value)\
({\
    Maybe ret = {(void*) value, 1};\
    ret;\
})

Maybe maybe_none()
{
    Maybe m = {NULL, 0};
    return m;
}

#define maybe_unwrap(type, m)\
({\
    type ret;\
    ret = *((type*) m.value);\
    ret;\
})

Maybe try_add(int a) {
    int* value = (int*) malloc(sizeof(int));
    *value += a;
    if (a < 5) {
        return maybe_some(value);
    }
    else {
        return maybe_none();
    }
}

int main() {


    Maybe num = try_add(3);
    if (num.has_value) {
        printf("num = %i\n", maybe_unwrap(int, num));
    }
    else{
        printf("no value\n");
    }
    
    num = try_add(6);
    if (num.has_value)
        printf("num = %i\n", maybe_unwrap(int, num));
    else
        printf("no value\n");

    return 0;
}
