typedef int MyInt;
typedef MyInt *MyIntPtr;
typedef MyIntPtr *MyIntPtrPtr;

int f()
{
    MyInt value = 42;
    MyIntPtr pValue = &value;

    *pValue = *pValue + 10;
    return value;
}
