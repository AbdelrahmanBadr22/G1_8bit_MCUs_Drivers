#include "../../../common/Types.h"
#include "../../../common/Utils.h"
#include "../../../common/Config.h"
#include "../../../common/Registes.h"
#include "../../../common/test.h"
#include "../../../utils/stack/stack.h"


int main()
{
    // ------------- CHAR STACK
    charStack_t cS;
    
    print_str("Char Stack:\n");
    charStack_Init(&cS);
    
    print_str("sizeof stack member:");
    print_num(sizeof(cS.stackArr[0])); // 1byte
    
    print_str("\nsize: ");
    print_num(charStack_GetSize(&cS)); // Expected 0
    print_str("\ntop: ");
    print_num(cS.top);  // Expected 0
    
    charStack_Push(&cS, 'a');
    charStack_Push(&cS, 'b');
    charStack_Push(&cS, 'c');
    
    print_str("\nsize: ");
    print_num(charStack_GetSize(&cS)); // Expected 3
    print_str("\ntop-val: ");
    print_char(charStack_GetTop(&cS));  // Expected 'c'
    
    charStack_Pop(&cS);
    print_str("\nsize: ");
    print_num(charStack_GetSize(&cS)); // Expected 2
    print_str("\ntop-val: ");
    print_char(charStack_GetTop(&cS));  // Expected 'b'

    charStack_Pop(&cS);
    print_str("\nsize: ");
    print_num(charStack_GetSize(&cS)); // Expected 1
    print_str("\ntop-val: ");
    print_char(charStack_GetTop(&cS));  // Expected 'a'

    charStack_Pop(&cS);
    print_str("\nsize: ");
    print_num(charStack_GetSize(&cS)); // Expected 0

    charStack_Push(&cS, 'm');
    print_str("\nsize: ");
    print_num(charStack_GetSize(&cS)); // Expected 1
    print_str("\ntop-val: ");
    print_char(charStack_GetTop(&cS));  // Expected 'm'

    print_str("\n");

    // ------------- INT STACK
    uint32_tStack_t iS;
    print_str("\nINT Stack:\n");
    uint32_tStack_Init(&iS);
    print_str("sizeof stack member:");
    print_num(sizeof(iS.stackArr[0])); // 4byte
    print_str("\nStack members\n");
    print_str("size: ");
    print_num(uint32_tStack_GetSize(&iS)); // Expected 0
    print_str("\ntop: ");
    print_num(iS.top);  // Expected 0
    
    uint32_tStack_Push(&iS, 100);
    uint32_tStack_Push(&iS, 200);
    uint32_tStack_Push(&iS, 230);
    
    print_str("\nsize: ");
    print_num(uint32_tStack_GetSize(&iS)); // Expected 3
    print_str("\ntop-val: ");
    print_num(uint32_tStack_GetTop(&iS));  // Expected '230'
    
    uint32_tStack_Pop(&iS);
    print_str("\nsize: ");
    print_num(uint32_tStack_GetSize(&iS)); // Expected 2
    print_str("\ntop-val: ");
    print_num(uint32_tStack_GetTop(&iS));  // Expected '200'

    uint32_tStack_Pop(&iS);
    print_str("\nsize: ");
    print_num(uint32_tStack_GetSize(&iS)); // Expected 1
    print_str("\ntop-val: ");
    print_num(uint32_tStack_GetTop(&iS));  // Expected '100'

    uint32_tStack_Pop(&iS);
    print_str("\nsize: ");
    print_num(uint32_tStack_GetSize(&iS)); // Expected 0
}
