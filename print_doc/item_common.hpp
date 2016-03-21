#pragma once

#include <boost/mpl/vector.hpp>
#include <boost/type_erasure/any.hpp>
#include <boost/type_erasure/member.hpp>
#include <boost/property_tree/ptree.hpp>

BOOST_TYPE_ERASURE_MEMBER((items)(has_begin), begin)
BOOST_TYPE_ERASURE_MEMBER((items)(has_end), end)

namespace items
{
	// ptree helper typedefs
	typedef boost::property_tree::ptree ptree;
	typedef boost::property_tree::ptree::const_iterator ptree_const_iter;
	typedef boost::property_tree::ptree::const_iterator::value_type ptree_const_iter_value_type;

	// string type
	typedef boost::property_tree::ptree::key_type string_type;
	typedef typename string_type::const_iterator const_string_iter_type;

	// boost::any item
	typedef boost::type_erasure::any<
		boost::mpl::vector<
		boost::type_erasure::copy_constructible<>,
		boost::type_erasure::relaxed,
		has_begin<const_string_iter_type(void), const boost::type_erasure::_self>,
		has_end<const_string_iter_type(void), const boost::type_erasure::_self>
		>,
		boost::type_erasure::_self
	> any_item;

}
