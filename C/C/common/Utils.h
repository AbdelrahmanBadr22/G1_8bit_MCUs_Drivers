#ifndef UTILS_H
#define UTILS_H

#define SET_BIT(_Reg, _BitNum) ( _Reg |=  (1<<_BitNum))
#define CLR_BIT(_Reg, _BitNum) ( _Reg &= ~(1<<_BitNum))
#define TOG_BIT(_Reg, _BitNum) ( _Reg ^=  (1<<_BitNum))
#define GET_BIT(_Reg, _BitNum) ((_Reg & (1<<_BitNum))>>_BitNum)
#endif /* _UTILS_H_ */
