
#include "..\cprime_lib.h"
#include <string.h>
#include <stdio.h>

void print_enum(const char* fileName, const char* enumName)
{
    struct SyntaxTree ast = SYNTAXTREE_INIT;

    if (BuildSyntaxTreeFromFile(fileName, "", &ast))
    {
        struct EnumSpecifier* pEnumSpecifier = SymbolMap_FindCompleteEnumSpecifier(&ast.GlobalScope, enumName);
        if (pEnumSpecifier)
        {
            printf("const char* tostring(enum %s e)\n", enumName);
            printf("{\n");
            printf("  switch (e)\n");
            printf("  {\n");
            struct Enumerator* pEnumerator = pEnumSpecifier->EnumeratorList.pHead;
            while (pEnumerator)
            {
                printf("    case %s: return \"%s\";\n", pEnumerator->Name, pEnumerator->Name);
                pEnumerator = pEnumerator->pNext;
            }
            printf("    default: break;\n");
            printf("  }\n");
            printf("  return \"\";\n");
            printf("}\n");
        }
    }

    SyntaxTree_Destroy(&ast);
}

/*
  Given a filename and enum name, this program generates
  a function to convert the enum value to string.
*/
int main(int argc, char* argv[])
{
    const char* fileName = argv[1];
    const char* enumName = argv[2];
    print_enum(fileName, enumName);
}
