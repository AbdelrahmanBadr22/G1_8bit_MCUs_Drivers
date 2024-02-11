#ifndef STACK_MACROS_H_
#define STACK_MACROS_H_
// -------------------------------
// Stack Configurations
// -------------------------------

/**
 * @brief Macro that used to define MAX size of the stack
 * @note  Stack size shouldn't exceed this value
 */
#define STACK_MAX_SIZE  (10)
#define STACK_SUCCESS   (1)
#define STACK_FAILURE   (-1)


// -------------------------------
// Stack Generic Macros
// -------------------------------

/**
 * @brief Generic macro which is used to define stack
 *        with a certain type.
 *
 * @note
 *
 *
 *
 * @example Stack_t(int) will be expanded to intStack_t
 */
#define Stack_t(type_)          typedef struct\
                                {\
                                    type_  stackArr[STACK_MAX_SIZE];\
                                    uint32_t size;\
                                    uint32_t top;\
                                }type_##Stack_t;

/**
 * @brief Generic macro which is used to define stack_Init
 *        with a certain type.
 *
 * @note  1]
 *
 *
 *
 *        2] We have to use also DEC_Stack_Init macro to declare in header
 *           file.
 *
 * @example Stack_Init(int) will expanded to void intStack_Init(Stack_t* S)
 */
#define DEC_Stack_Init(type_)   void type_##Stack_Init(type_##Stack_t* S);
#define Stack_Init(type_)       void type_##Stack_Init(type_##Stack_t* S)\
                                {\
                                    S->size = 0;\
                                    S->top = 0;\
                                }
/**
 * @brief Generic macro which is used to define Stack_Push
 *        with a certain type.
 *
 * @note
 *
 *
 *
 * @example Stack_Push(int) will expanded to void intStack_Push

 */
#define DEC_Stack_Push(type_) uint32_t type_##Stack_Push(type_##Stack_t* S,\
                                                       type_ D);

#define Stack_Push(type_)   uint32_t type_##Stack_Push(type_##Stack_t* S, \
                                                       type_ D) \
                            { \
                                if (S != NULL && S->size >= S->top) \
                                { \
                                    S->stackArr[S->top] = D; \
                                    S->top++; \
                                    S->size++;\
                                    return STACK_SUCCESS; \
                                }\
                                return STACK_FAILURE; \
                            }

/**
 * @brief Generic macro which is used to define stack_pop
 *        with a certain type.
 *
 * @note
 *
 *
 */
#define DEC_Stack_Pop(type_)   type_ type_##Stack_Pop(type_##Stack_t* S);
#define Stack_Pop(type_)       type_ type_##Stack_Pop(type_##Stack_t* S)\
                                {\
                                    if (S != NULL)\
                                    {\
                                        S->top--;\
                                        S->size--;\
                                        return S->stackArr[S->top];\
                                    }\
                                    return STACK_FAILURE;\
                                }

/**
 * @brief Generic macro which is used to define stack_GetSize
 *        with a certain type.
 *
 * @note
 *
 *
 */
#define DEC_Stack_GetSize(type_)    uint32_t \
                                    type_##Stack_GetSize(type_##Stack_t* S);

#define Stack_GetSize(type_)    uint32_t \
                                type_##Stack_GetSize(type_##Stack_t* S)\
                                {\
                                    if (S != NULL)\
                                    {\
                                        return S->size;\
                                    }\
                                    return STACK_FAILURE;\
                                }

/**
 * @brief Generic macro which is used to define stack_GetTop
 *        with a certain type.
 *
 * @note
 *
 */
#define DEC_Stack_GetTop(type_) type_ type_##Stack_GetTop(type_##Stack_t* S);
#define Stack_GetTop(type_)     type_ type_##Stack_GetTop(type_##Stack_t* S)\
                                {\
                                    if (S != NULL)\
                                    {\
                                        return S->stackArr[(S->top) - 1];\
                                    }\
                                    return STACK_FAILURE;\
                                }
/**
 * @brief Generic macro which is used to define stack_clear
 *        with a certain type.
 *
 * @note
 *
 *
 */
#define DEC_Stack_Clear(type_)   type_ type_##Stack_Clear(type_##Stack_t* S);
#define Stack_Clear(type_)       type_ type_##Stack_Clear(type_##Stack_t* S)\
                                {\
                                    if (S != NULL)\
                                    {\
                                        S->top=0;\
                                        S->size=0;\
                                        return STACK_SUCCESS;\
                                    }\
                                    return STACK_FAILURE;\
                                }

#endif /*STACK_MACROS_H_*/
