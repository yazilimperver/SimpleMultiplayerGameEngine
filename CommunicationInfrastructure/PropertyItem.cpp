#include <PropertyItem.h>

PropertyItem::PropertyItem() : mName{ "" }
{

}

PropertyItem::PropertyItem(const std::string& name, const std::any& value) 
	: mName{ name }
    , mValue{ value }
{

}
