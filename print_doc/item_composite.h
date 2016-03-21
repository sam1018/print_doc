#pragma once

#include <boost/property_tree/ptree.hpp>
#include "attribs.h"

namespace items { namespace detail {

	typedef boost::property_tree::ptree ptree;
	typedef boost::property_tree::ptree::const_iterator ptree_const_iter;
	typedef boost::property_tree::ptree::const_iterator::value_type ptree_const_iter_value_type;

	class item_text
	{
	public:
		item_text(const boost::property_tree::ptree&) {}
	};

	struct make_item
	{
	public:
		boost::any operator()(const std::string& item_name, const boost::property_tree::ptree& tree) const
		{
			boost::any item;

			if (item_name == doc_tags::text)
				item = item_text(tree);

			return item;
		}

		boost::any operator()(const detail::ptree_const_iter_value_type& v) const
		{
			return operator()(v.first, v.second);
		}
	};

	typedef boost::transform_iterator<
		make_item,
		ptree_const_iter,
		boost::any&,
		boost::any> item_composite_iterator;

	typedef boost::iterator_range<item_composite_iterator> item_composite_base;

} }

namespace items
{
	class item_composite : public detail::item_composite_base
	{
	public:
		item_composite(const detail::ptree& tree, const attribs& _att) :
			detail::item_composite_base(
				detail::item_composite_iterator(tree.begin()), 
				detail::item_composite_iterator(tree.end()))
		{}
	};
}
