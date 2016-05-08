#ifndef XF_LIST_ITEM_HPP
#define XF_LIST_ITEM_HPP

namespace xf
{
	enum PTR_POS{PREV_POS = 0, NEXT_POS = 1};

	template<class T>
	class list_item
	{
	public:

		list_item(enum PTR_POS prev_pos, list_item *prev, enum PTR_POS next_pos, list_item *next) : val_()
		{
			item_ptr_[prev_pos] = prev;
			item_ptr_[next_pos] = next;
		}
		list_item(const T &_Value, enum PTR_POS prev_pos, list_item *prev, enum PTR_POS next_pos, list_item *next) : val_(_Value)
		{
			item_ptr_[prev_pos] = prev;
			item_ptr_[next_pos] = next;
		}
		~list_item()
		{
			item_ptr_[0] = NULL;
			item_ptr_[1] = NULL;
		}
		T val_;
		list_item<T> *item_ptr_[2];
	};
}

#endif