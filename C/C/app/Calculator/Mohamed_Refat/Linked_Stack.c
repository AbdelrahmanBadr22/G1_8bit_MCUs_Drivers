#include <stdlib.h>
#include "../../common/Types.h"
#include "Linked_Stack.h"

void LinkedStack_creatStack(Stack_t *stack)
{
	stack->Top = NULL_PTR;
	stack->kStackSize=0;

}

void LinkedStack_Push(Stack_t *stack, STACK_DATA_TYPE Data)
{
	Node_t *pNode = (Node_t *)malloc(sizeof(Node_t));
	pNode->Entry = Data;
	pNode->Next = stack->Top;
	stack->Top = pNode;
	stack->kStackSize++;
}

STACK_DATA_TYPE LinkedStack_GetTop(Stack_t *stack )
{
	return stack->Top->Entry;

}

STACK_DATA_TYPE LinkedStack_Pop(Stack_t *stack)
{
	STACK_DATA_TYPE DeletedData = stack->Top->Entry;
	Node_t *pLocalNode = stack->Top;
	stack->Top=pLocalNode->Next;
	free(pLocalNode);
	stack->kStackSize--;
	return DeletedData;
}

uint8_t LinkedStack_IsEmpty(Stack_t *stack)
{
	uint8_t localReturn;
	if (NULL_PTR==stack->Top)
	{
		localReturn=1;
	}else if (NULL_PTR!=stack->Top)
	{
		localReturn=0;
	}else
	{
		/*Do Nothing*/
	}

	return localReturn;
}

uint8_t LinkedStack_IsFull (Stack_t stack)
{
	return 0; /*The linked stack will never be full*/
}

uint32_t LinkedStack_GetSize(Stack_t *pStack )
{

	return pStack->kStackSize;
}

void LinkedStack_Traverse(Stack_t *pStack, void (*pFun)(STACK_DATA_TYPE data))
{
	Node_t *Local_pTop = pStack->Top;
	while (Local_pTop !=NULL_PTR)
	{
		pFun(Local_pTop->Entry);
		Local_pTop = Local_pTop->Next;
	}
}
