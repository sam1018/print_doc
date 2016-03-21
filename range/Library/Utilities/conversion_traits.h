#pragma once

#include "remove_cvref.h"

#include <boost/numeric/conversion/conversion_traits.hpp>

#include <boost/mpl/if.hpp>
#include <boost/mpl/vector.hpp>
#include <boost/mpl/transform_view.hpp>
#include <boost/mpl/zip_view.hpp>
#include <boost/mpl/unpack_args.hpp>
#include <boost/mpl/equal.hpp>
#include <boost/mpl/min_element.hpp>

#include <type_traits>

// Use as type of constructor arguments that are required for enabling / disabling constructor through SFINAE.
// To be replaced by template parameter default when Visual C++ supports template parameter defaults for functions.
struct unused_arg {};

/////////////
// conversion traits

namespace tc {
	// Both boost::is_base_of<X,X> and std::is_base_of<X,X> inherit from true_type if and only if X is a class type.
	// Also, std::is_base_of requires Base and Derived to be complete.
	template<typename Base, typename Derived>
	struct is_base_of :
		boost::mpl::or_<
			std::is_same< std::remove_cv_t<Base>, std::remove_cv_t<Derived> >,
			std::is_base_of<Base, Derived>
		>::type
	{};

	// true, if type can be converted without loss of precision
	// - conversion of builtin numeric type to user-defined type is allowed
	// - conversion of user-defined type to builtin numeric type is forbidden
	// if you want to enable conversion from a specific udt into a builtin,
	// specialize is_lossless_convertible
	template<typename TSource, typename TTarget>
	struct is_lossless_convertible : std::integral_constant<bool,
		// cannot use VC's std::is_convertible, because it seems to be broken (is_convertible<int&, int> returns false)
		// Note: Still using std::is_convertible won't reduce compilation times anyway.
		std::is_convertible<TSource, TTarget>::value &&
		!boost::numeric::conversion_traits<
			std::remove_reference_t< TTarget >,
			std::remove_reference_t< TSource >
		>::subranged::value
	> {};

	// do not allow initialization of an A{const}& member by B{{const}&}, unless A is same or base of B
	// conversion would create a reference to a temporary object
	template<typename TSource, typename TTarget>
	struct creates_no_reference_to_temporary : std::integral_constant<bool,
		!std::is_reference<TTarget>::value ||
		tc::is_base_of< 
			tc::remove_cvref_t<TTarget>,
			tc::remove_cvref_t<TSource>
		>::value
	> {};
}

////////////////////////////////////////////////
// initialization of TTarget by TSource

using forbidden_initialization_tag = boost::mpl::int_<0>; // would initialize a reference to a temporary
using explicit_initialization_tag = boost::mpl::int_<1>;
using implicit_initialization_tag = boost::mpl::int_<3>; // we want to bit-and these values in order to find the minimum

template<typename TTarget, typename TSource>
struct initialization_tag {
	using type=std::conditional_t<
		tc::creates_no_reference_to_temporary< TSource, TTarget >::value,
		std::conditional_t<
			// Only true_, if implicit conversion exists.
			tc::is_lossless_convertible<TSource, TTarget>::value &&
			// in expressions like ((condition) ? (expression of type T&) : (expression of type T))
			// prefer conversion from T& to T over conversion from T to T& 
			(!std::is_reference<TTarget>::value || std::is_reference<TSource>::value)
			, implicit_initialization_tag
			, explicit_initialization_tag
		>,
		forbidden_initialization_tag
	>;
};


