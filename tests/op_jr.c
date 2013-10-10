

int main() {
    asm(
    "la $v0,__after\n"
    "jr $v0\n"
    "nop\n"
    "__forever:\n"
    "j __forever\n"
    "__after:\n"
    ::: "v0"
    );
    return 0;
}
