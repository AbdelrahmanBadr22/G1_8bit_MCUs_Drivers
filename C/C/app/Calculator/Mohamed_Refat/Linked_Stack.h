#ifndef LINKED_STACK_H
#define LINKED_STACK_H

typedef f32_t STACK_DATA_TYPE;
typedef struct Node_t
{
	STACK_DATA_TYPE  Entry;
	struct Node_t *Next;
}Node_t;

typedef struct stack
{
	Node_t *Top;
	uint32_t kStackSize;
}Stack_t;
/* @brief: This function is used to creat Linked stack
 * @para : *stack ::
 * 					pointer to the stack that data will be bushed in.
 *
 * @ret  : None
 * @note :This function must be used every time you want to creat Linked stack.
 *
 * */
void LinkedStack_creatStack(Stack_t *stack);

/* @brief: This function is used to push the data to the linked stack
 * @para : *stack ::
 * 					pointer to the stack that data will be bushed in.
 *
 * 			Data  ::
 *					The data that will be pushed to the stack
 * @ret  : None
 * @note : This function must be used every time you want to
 * 			push the data to the stack.
 *
 * */
void LinkedStack_Push(Stack_t *stack, STACK_DATA_TYPE Data);


/* @brief: This function is used to return the last data at the linked stack
 * @para : *stack ::
 * 					pointer to the stack that you want to
 * 						read the last data  from it (from linked stack)
 * @ret  : STACK_DATA_TYPE :: Top of the stack
 *
 * */
STACK_DATA_TYPE LinkedStack_GetTop(Stack_t *stack );

/* @brief: This function is used to pop data from the stack
 * @para : *stack ::
 * 				pointer to the stack that the data will be popped out from it.
 * @ret  : STACK_DATA_TYPE :: Last data poped  from the stack
 *
 * */
STACK_DATA_TYPE LinkedStack_Pop(Stack_t *stack);


/* @brief: This function is used to check if stack empty or not
 * @para : stack ::
 * 				Copy from the stack that you want to check if it empty or not
 *
 * @ret  : Return 1 --> if the stack is empty
 *  	   Return 0 --> if the stack is not empty
 *
 * @note : Type of return is uint8_t
 *
 * */
uint8_t LinkedStack_IsEmpty(Stack_t *stack);


/* @brief: This function is used to check if stack full or not
 * @para : stack ::
 * 					Copy from  the stack that you want to check if it full or not
 *
 * @ret  : Return 1 --> if the stack is full
 *  	   Return 0 --> if the stack is not full
 *
 * @note : Type of return is uint8_t
 *
 * */
uint8_t LinkedStack_IsFull (Stack_t stack);


/* @brief: This function is used to get the size of the linked stack
 * @para : *stack:
 * 					pointer to the stack that you want to know the size of it
 *
 * @ret  : Size of the stack
 * @note : None
 *
 **/
uint32_t LinkedStack_GetSize(Stack_t *pStack );


/* @brief: This function is used to traverse each element in the stack
 * @para : *stack ::
 * 					pointer to the stack that you want to traverse it
 *
 *		   void (*ptr)(STACK_DATA_TYPE Data)::
 *					ptr is a pointer to function which take one argument of
 * 					the stack type and return nothing
 * @ret  : None
 * @note : None
 *
 * */
void LinkedStack_Traverse(Stack_t *pStack, void (*pFun)(STACK_DATA_TYPE data));

#endif /* LINKED_STACK_H*/
