//
// Created by Matthew McCall on 1/31/25.
//

#ifndef COMMON_HPP
#define COMMON_HPP


#ifdef OASIS_IO_ENABLED
#include "Oasis/InFixSerializer.hpp"
inline     Oasis::InFixSerializer __serializer;
#define OASIS_CAPTURE_WITH_SERIALIZER(__expr) \
__expr.Accept(__serializer);                        \
auto __expr_str = __serializer.getResult();          \
INFO(#__expr << " := " << __expr_str);
#else
#define OASIS_CAPTURE_WITH_SERIALIZER(__serializer, __expr)
#endif

#endif //COMMON_HPP
