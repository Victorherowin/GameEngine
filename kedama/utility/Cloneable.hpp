//
// Created by moe on 2017-07-14.
//

#ifndef KEDAMA_CLONEABLE_HPP
#define KEDAMA_CLONEABLE_HPP

#endif //KEDAMA_CLONEABLE_HPP

namespace Kedama::Utility
{
    template <typename T>
    class ICloneable
    {
    public:
        virtual T Clone()=0;
    };
}