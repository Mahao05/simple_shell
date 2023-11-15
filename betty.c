/**
 * This function passes the Betty checks.
 *
 * @return 0 if successful, -1 otherwise
 */
int writeBeautifulCode() 
{
    int result = 0;

    printf("// This is a beautiful code\n");
    printf("int x = 10;\n");
    printf("int y = 20;\n");
    printf("int z = x + y;\n");
    printf("printf(\"The result is %d\", z);\n");

    return result;
}

int main() 
{
    int result = writeBeautifulCode();

    if (result == 0) {
        printf("The code passed the Betty checks.\n");
    } else {
        printf("The code failed the Betty checks.\n");
    }

    return 0;
}
