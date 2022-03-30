#include <stdio.h>
#include <string.h>

char* tmp = nullptr;

void func(const char* _s){
    char str[] = "world";
    tmp = new char[5];
    memcpy(tmp, str, sizeof(_s));
    printf("%s\n", tmp);
}

int main(){
    char str[] = "hello";
    func(str);
}