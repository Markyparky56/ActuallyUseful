module;
#include <functional> // For invoke
export module autl.algo.transform;

export namespace autl
{
  template<class InArrayType, class OutArrayType, typename Pred, typename TransformOp>
  void TransformIf(const InArrayType& inArray, OutArrayType& outArray, Pred predicate, TransformOp transformOp)
  {
    for (auto& item : inArray)
    {
      if (std::invoke(predicate, item))
      {
        outArray.push_back(std::invoke(transformOp, item));
      }
    }
  }

  template<class InArrayType, class OutArrayType, typename TransformOp>
  void Transform(const InArrayType& inArray, OutArrayType& outArray, TransformOp transformOp)
  {
    for (auto& item : inArray)
    {
      outArray.push_back(std::invoke(transformOp, item));
    }
  }
}

