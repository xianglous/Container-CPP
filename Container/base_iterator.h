#pragma once

namespace Containers {
	template<typename T>
	class BaseIterator {
	public:

		virtual bool operator==(const BaseIterator&) const = 0;

		virtual bool operator!=(const BaseIterator& other) const { return !(*this == other); }

		virtual BaseIterator& operator++() = 0;

		virtual BaseIterator operator++(int) {
			BaseIterator it = *this;
			++(*this);
			return it;
		}

		virtual BaseIterator operator+(int) const = 0;

		virtual BaseIterator& operator+=(int) = 0;

		virtual BaseIterator& operator--() = 0;

		virtual BaseIterator operator--(int) {
			BaseIterator it = *this;
			--(*this);
			return it;
		}

		virtual BaseIterator operator-(int) const = 0;

		virtual BaseIterator& operator-=(int) = 0;

		virtual size_t operator-(const BaseIterator&) const = 0;

		virtual T& operator*() = 0;

		virtual const T& operator*() const = 0;

		virtual T* operator->() = 0;

		virtual const T* operator->() const = 0;
	};

//protected:
//	virtual bool equals(const BaseIterator&) = 0;
}

