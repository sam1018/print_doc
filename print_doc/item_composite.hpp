#pragma once

#include "attribs.hpp"
#include "item_text.hpp"
#include "item_common.hpp"

namespace items
{
	struct make_item
	{
	public:
		any_item operator()(const string_type& item_name, const boost::property_tree::ptree& tree) const
		{
			any_item item;

			if (item_name == doc_tags::text)
				item = item_text(tree);
			else
				throw std::invalid_argument("Invalid item name: " + item_name);

			return item;
		}

		any_item operator()(const ptree_const_iter_value_type& v) const
		{
			return operator()(v.first, v.second);
		}
	};

	typedef boost::transform_iterator<
		make_item,
		ptree_const_iter> item_composite_iterator;

	typedef boost::iterator_range<item_composite_iterator> item_composite_base;

	class item_composite : public item_composite_base
	{
	public:
		item_composite(const ptree& tree, const attribs& _att) :
			item_composite_base(
				item_composite_iterator(tree.begin()), 
				item_composite_iterator(tree.end()))
		{}
	};
}
