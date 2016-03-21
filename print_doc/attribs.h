#pragma once

#include <boost/property_tree/ptree.hpp>
#include "doc_tags.h"

namespace items
{
	struct attribs
	{
		int width = 80;
	};

	attribs create_attribute(const boost::property_tree::ptree& tree, attribs att = attribs{})
	{
		att.width = tree.get(doc_tags::width, att.width);

		return att;
	}
}
