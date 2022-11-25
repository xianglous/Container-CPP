#pragma once
#include <exception>
#include <string>
#include <format>


namespace Containers {
	class ContainerException : public std::exception {
	public:
		ContainerException(const char* container, const char* format)
			: container(container), format(format) {
			message = std::format("{} for {}\n", format, container);
		}
		const char* what() const noexcept override {
			return message.c_str();
		}
	protected:
		const char* container;
		const char* format;
		std::string message;
	};

	class InvalidIteratorException : public ContainerException {
	public:
		InvalidIteratorException(const char* container) :
			ContainerException(container, "Invalid Iterator") {}
	};

	class OutOfRangeException : public ContainerException {
	public:
		OutOfRangeException(const char* container) :
			ContainerException(container, "Out of Range") {}
	};
}
