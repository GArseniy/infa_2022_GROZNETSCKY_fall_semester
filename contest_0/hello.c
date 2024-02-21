#define BEBRA 5
#define BEBRA_CHAR 'i'

int main(void){
    char a[BEBRA+1];

    a[0] = BEBRA_CHAR;

    a[BEBRA] = 0;

    return 0;
}
