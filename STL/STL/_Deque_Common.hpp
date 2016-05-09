#ifndef XF_DEQUE_COMMON_HPP
#define XF_DEQUE_COMMON_HPP

static size_t& DequeSegmentLength()
{
	static size_t DequeSegmentLength = 64U;
	return DequeSegmentLength;
}

#endif