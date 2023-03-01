module;
export module autl.concepts.convertibleto;

import autl.type_traits.convertible;
import autl.utility.declval;

export namespace autl
{
  /*
  * Specifies that an expression of the same type and value category as those of Declval<From>() can be implicitly and explicitly converted to the type To, and the two conversions are equivalent
  */
  template<typename From, typename To>
  concept ConvertibleTo = 
       IsConvertible_v<From, To> 
    && requires{ static_cast<To>(Declval<From>()); };
}
